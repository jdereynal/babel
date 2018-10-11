/*
** EPITECH PROJECT, 2018
** babel
** File description:
** Udp
*/

#ifndef UDP_HPP_
	#define UDP_HPP_

#include <iostream>
#include <QtNetwork/QUdpSocket>
#include <boost/circular_buffer.hpp>
#include "Sound.hpp"
#include "ACodec.hpp"

class Udp : public QObject {
Q_OBJECT
private:
	QUdpSocket *_socket;
	boost::circular_buffer<float> *_buffer;
	quint16 _sendPort;
	QHostAddress _address;
	ACodec _codec;
public:
	Udp(quint16 port, boost::circular_buffer<float> *buffer, QObject *parent = nullptr);
	Udp(QString sendAddress, quint16 sendPort, QObject *parent = nullptr);
	virtual ~Udp();
public slots:
	void handleRead();
	void sendAudio(void *, int);
};

#endif /* !UDP_HPP_ */
