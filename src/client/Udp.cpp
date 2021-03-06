/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Udp
*/

#include "Udp.hpp"

Udp::Udp(quint16 port, boost::circular_buffer<float> *buffer, QObject *parent) {
	_socket = new QUdpSocket();
	_buffer = buffer;
	_socket->bind(QHostAddress::Any, port);
	QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(handleRead()));
};

Udp::Udp(QString sendAddress, quint16 sendPort, QObject *parent)
{
	_socket = new QUdpSocket();
	QHostAddress addr(sendAddress);
	_address = addr;
	_sendPort = sendPort;
};

Udp::~Udp()
{
}

void Udp::handleRead() {
	QByteArray buffer;
	buffer.resize(_socket->pendingDatagramSize());

	QHostAddress sender;
	_socket->readDatagram(buffer.data(), buffer.size(), &sender);
	std::cout << "Received packet of size " << buffer.size() << std::endl;
	float *ptr = new float[CHANNEL * FRAMESIZE * 1];
	unsigned char *data = (unsigned char *)buffer.data();
	int size = _codec.decodeData(data, buffer.size(), ptr);
	std::cout << "Decoded packet size : " << size << std::endl << std::endl;
	for (int i = 0; i < size; i++) {
		_buffer->push_back(ptr[i]);
	}
}

void Udp::sendAudio(void *encoded, int size) {
	auto buf = QByteArray::fromRawData((char *)encoded, size);
	// std::cout << size << std::endl;
	// Uncomment to test audio. :(
	// float *ptr = new float[CHANNEL * FRAMESIZE * 1];
	// unsigned char *data = (unsigned char *)buf.data();
	// int decodedSize = _codec.decodeData(data, buf.size(), ptr);
	// for (int i = 0; i < decodedSize; i++)
	// 	_buffer->push_back(ptr[i]);
	qDebug() << _address;
	qDebug() << _sendPort;
	std::cout << "Sending packet of size " << _socket->writeDatagram(buf, size, _address, _sendPort) << std::endl << std::endl;
}