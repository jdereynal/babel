/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
	#define MESSAGE_HPP_

#include <string>
#include <boost/asio.hpp>
#include "TcpConnection.hpp"

class TcpConnection;

class Message {
private:
	const std::string _message;
	const boost::shared_ptr<TcpConnection> _ptr;
public:
	Message(const std::string &message, const boost::shared_ptr<TcpConnection> ptr) :
	_message(message), _ptr(ptr) {};
	~Message();
	std::string getMessage() const {
		return _message;
	}
	const boost::shared_ptr<TcpConnection> getPtr() const {
		return _ptr;
	}

};

#endif /* !MESSAGE_HPP_ */
