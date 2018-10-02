/*
** EPITECH PROJECT, 2018
** babel
** File description:
** TcpConnection
*/

#ifndef TCPCONNECTION_HPP_
	#define TCPCONNECTION_HPP_

#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "Message.hpp"

class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
private:
	boost::asio::ip::tcp::socket _socket;
	std::string _username;
	unsigned short _port;
	unsigned int _id;
	char _msg[1024];

	TcpConnection(boost::asio::io_service &ioService, unsigned int id) : _socket(ioService), _username(""), _id(id), _port(0) {}
	void writeHandler(const boost::system::error_code &error) {
		if (error)
			std::cerr << "Error in async_write : " << std::endl;
	}
	void readHandler(const boost::system::error_code &error, boost::shared_ptr<TcpConnection> con, std::vector<Message *> *queue, boost::asio::deadline_timer *timer) {
		if (error == boost::asio::error::eof) {
			con = nullptr;
			delete this;
		}
		if (!error) {
			queue->push_back(new Message(_msg, con));
			timer->expires_at(boost::posix_time::pos_infin);
			read(con, queue, timer);
		}
	}
public:
	static boost::shared_ptr<TcpConnection> create(boost::asio::io_service &ioService, unsigned int id) {
		return boost::shared_ptr<TcpConnection>(new TcpConnection(ioService, id));
	}
	boost::asio::ip::tcp::socket &getSocket() {
		return _socket;
	}
	void write(const std::string &message) {
		boost::asio::async_write(_socket, boost::asio::buffer(message), boost::bind(&TcpConnection::writeHandler, this, boost::asio::placeholders::error));
	}
	void read(boost::shared_ptr<TcpConnection> con, std::vector<Message *> *queue, boost::asio::deadline_timer *timer) {
		std::memset(_msg, 0, sizeof(_msg));
		_socket.async_receive(boost::asio::buffer(_msg, 1024), boost::bind(&TcpConnection::readHandler, this, boost::asio::placeholders::error, con, queue, timer));
	}
	void setUsername(const std::string &username) {
		_username = username;
	}
	void setPort(const unsigned short &port) {
		_port = port;
	}
	const std::string &getUsername() const {
		return _username;
	}
	const unsigned int getId() const {
		return _id;
	}
	const unsigned short getPort() const {
		return _port;
	}
};

#endif /* !TCPCONNECTION_HPP_ */
