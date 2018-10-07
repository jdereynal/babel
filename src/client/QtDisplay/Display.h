/*
** EPITECH PROJECT, 2018
** Display
** File description:
** Display
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtWidgets/QMainWindow>
#include <QtNetwork/QTcpSocket>
#include <string>
#include <map>

namespace Ui {
class Display;
}

class Display : public QMainWindow
{
	Q_OBJECT

public:
	explicit Display(QWidget *parent = nullptr);
	~Display();

private slots:
	void on_pushButton_connexion_clicked();
	void on_pushButton_deconnexion_clicked();
	void on_buttunCall_clicked();
	void on_pushButtonQuitCall_clicked();
	void connectedHandler();
	void readHandler();
	void disconnectedHandler();

private:
	Ui::Display *ui;
	QTcpSocket *_socket;
	unsigned int _id;
	std::string _username;
	std::string _port;
	unsigned int _currentCall;
	std::map<unsigned int, std::string> _contacts;
};

#endif // DISPLAY_H
