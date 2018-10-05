/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Udp
*/

#include "Udp.hpp"

Udp::Udp(quint16 port, QObject *parent) {
	_socket = new QUdpSocket();
	_socket->bind(QHostAddress::LocalHost, port);

	QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(handleRead()));
};

Udp::~Udp()
{
}

void Udp::handleRead() {
	QByteArray buffer;
	buffer.resize(_socket->pendingDatagramSize());

	QHostAddress sender;
	_socket->readDatagram(buffer.data(), buffer.size(), &sender);
	qDebug() << buffer;
}