/*
** EPITECH PROJECT, 2018
** babel
** File description:
** TcpServer
*/

#ifndef TCPSERVER_HPP_
	#define TCPSERVER_HPP_

#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include "TcpConnection.hpp"

class TcpServer {
private:
	boost::asio::ip::tcp::acceptor _acceptor;
	boost::asio::deadline_timer _timer;
	std::vector<boost::shared_ptr<TcpConnection>> _connections;
	std::vector<Message *> _queue;
	std::unordered_map<unsigned int, unsigned int> _callreqs;
	std::unordered_map<unsigned int, unsigned int> _calls;

	void start_accept() {
		static int id;
		boost::shared_ptr<TcpConnection> newConnection = TcpConnection::create(_acceptor.get_io_service(), ++id);
		_acceptor.async_accept(newConnection->getSocket(),
		boost::bind(&TcpServer::acceptHandler, this, newConnection, boost::asio::placeholders::error));
	}
	void start_message() {
		_timer.async_wait(boost::bind(&TcpServer::messageHandler, this, boost::asio::placeholders::error));
	}
	void acceptHandler(boost::shared_ptr<TcpConnection> newConnection, const boost::system::error_code &error) {
		if (!error) {
			std::cout << "new connection" << std::endl;
			_connections.push_back(newConnection);
			newConnection->write("ID " + std::to_string(newConnection->getId()) + "\n");
			newConnection->write("CONTACTS " + getContacts() + "\n");
			newConnection->read(newConnection, &_queue, &_timer);
			start_accept();
		}
	}
	void changeUsername(std::vector<std::string> &arr, const boost::shared_ptr<TcpConnection> &client) {
		client->setUsername(arr[1]);
		client->write("USER ok\n");
		for (auto con : _connections)
			if (con->getId() != client->getId())
				con->write("CONTACTS " + getContacts() + "\n");
	}
	void changePort(std::vector<std::string> &arr, const boost::shared_ptr<TcpConnection> &client) {
		unsigned short port = std::stoi(arr[1]);
		client->setPort(port);
		client->write("PORT ok\n");
	}
	void initCall(const boost::shared_ptr<TcpConnection> &client1, const boost::shared_ptr<TcpConnection> &client2) {
		auto addr1 = client1->getSocket().remote_endpoint().address().to_string();
		auto addr2 = client2->getSocket().remote_endpoint().address().to_string();

		client1->write("CALL " + std::to_string(client2->getId()) + " " + addr2 + " " + std::to_string(client2->getPort()) + "\n");
		client2->write("CALL " + std::to_string(client1->getId()) + " " + addr1 + " " + std::to_string(client1->getPort()) + "\n");
		_calls.insert(std::make_pair(client1->getId(), client2->getId()));
	}
	void callRequest(std::vector<std::string> &arr, const boost::shared_ptr<TcpConnection> &client) {
		int id = std::stoi(arr[1]);
		boost::shared_ptr<TcpConnection> client2 = nullptr;

		for (auto con : _connections) {
			if (con->getId() == id) {
				client2 = con;
				break ;
			}
		}
		if (client2 == nullptr) {
			client->write("CALLREQ -1\n");
			return ;
		}
		client2->write("CALLREQ " + std::to_string(client->getId()) + "\n");
		_callreqs.insert(std::pair<unsigned int, unsigned int>(client->getId(), client2->getId()));
		for (auto it1 = _callreqs.begin(); it1 != _callreqs.end(); it1++) {
			for (auto it2 = _callreqs.begin(); it2 != _callreqs.end(); it2++) {
				if (it1 == it2)
					continue ;
				if (it1->first == it2->second && it1->second == it2->first) {
					_callreqs.erase(it1);
					_callreqs.erase(it2);
					return initCall(client, client2);
				}
			}
		}
	}
	void endCall(std::vector<std::string> &arr, const boost::shared_ptr<TcpConnection> &client) {
		for (auto pair = _calls.begin(); pair != _calls.end(); pair++) {
			if ((pair->first == client->getId() && pair->second == std::stoi(arr[1])) || (pair->second == client->getId() && pair->first == std::stoi(arr[1]))) {
				_calls.erase(pair);
				for (auto con : _connections)
					if (con->getId() == std::stoi(arr[1]))
						con->write("ENDCALL " + std::to_string(client->getId()) + "\n");
			}
		}
	}
	void messageHandler(const boost::system::error_code &error) {
		int i = 0;
		for (auto it : _connections) {
			if (it->getStatus() == true) {
				it->close();
				_connections.erase(_connections.begin() + i);
			}
			i++;
		}
		for (auto it = _queue.begin(); it != _queue.end(); it++) {
			auto message = (*it)->getMessage();
			std::cout << "[" << message << "]" << std::endl;
			std::istringstream iss(message);
			std::vector<std::string> arr((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
			if (!arr.size())
				continue;
			if (arr[0] == "USER" && arr.size() > 1 && arr[1] != "")
				changeUsername(arr, (*it)->getPtr());
			if (arr[0] == "CONTACTS")
				(*it)->getPtr()->write("CONTACTS " + getContacts() + "\n");
			if (arr[0] == "CALLREQ" && arr.size() > 1 && arr[1] != "")
				callRequest(arr, (*it)->getPtr());
			if (arr[0] == "ENDCALL" && arr.size() > 1 && arr[1] != "")
				endCall(arr, (*it)->getPtr());
			if (arr[0] == "PORT" && arr.size() > 1 && arr[1] != "")
				changePort(arr, (*it)->getPtr());
		}
		_queue.clear();
		start_message();
	}
	const std::string getContacts() const {
		std::string ret = "";
		for (auto it : _connections) {
			if (it->getUsername() != "")
				ret += it->getUsername() + "," + std::to_string(it->getId()) + " ";
		}
		return ret;
	}
public:
	TcpServer(boost::asio::io_service &ioService, unsigned short port) :
	_acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
	_timer(ioService) {
		_timer.expires_at(boost::posix_time::pos_infin);
		start_accept();
		start_message();
	}
	~TcpServer() {
		_timer.cancel();
	}
};

#endif /* !TCPSERVER_HPP_ */
