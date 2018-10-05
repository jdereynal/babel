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

class Udp : public QObject {
Q_OBJECT
private:
	QUdpSocket *_socket;
public:
	Udp(quint16 port, QObject *parent = nullptr);
	virtual ~Udp();
public slots:
	void handleRead();
};

#endif /* !UDP_HPP_ */
