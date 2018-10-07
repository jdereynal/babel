/*
** EPITECH PROJECT, 2018
** Display
** File description:
** Display
*/

#include <QtWidgets/QMessageBox>
#include <sstream>
#include <iostream>
#include "Display.h"
#include "ui_Display.h"

Display::Display(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::Display)
{
	ui->setupUi(this);
	this->setWindowTitle("Babel ~ Application de contact");
	_socket = new QTcpSocket(this);
	QObject::connect(_socket, SIGNAL(connected()), this, SLOT(connectedHandler()));
	QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readHandler()));
}

Display::~Display()
{
	delete ui;
}

void Display::connectedHandler()
{
	ui->stackedWidget->setCurrentIndex(1);
	this->setFixedSize(320, 400);
}

void Display::readHandler()
{
	QByteArray data = _socket->readAll();
	std::string str = data.toStdString();
	std::vector<std::string> arr;
	std::stringstream ss(str);
	std::string tmp;
	std::cout << str << std::endl;
	while (std::getline(ss, tmp, '\n'))
		arr.push_back(tmp);
	for (auto str : arr) {
		std::istringstream iss(str);
		std::vector<std::string> split((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
		if (split[0] == "ID" && split.size() > 1 && split[1] != "")
			_id = std::stoi(split[1]);
		if (split[0] == "CONTACTS" && split.size() > 1 && split[1] != "") {
			for (int i = 1; i < split.size(); i++) {
				std::istringstream ss(split[i]);
				std::string username;
				std::string id;
				std::getline(ss, username, ',');
				std::getline(ss, id, ',');
				_contacts.insert(std::make_pair(username, std::stoi(id)));
			}
		}
	}
}

void Display::on_pushButton_connexion_clicked()
{
	QString username = ui->input_name->text();
	QString serverPort = ui->input_port_server->text();
	QString clientPort = ui->input_port_client->text();
	QString serverAddr = ui->input_addr->text();

//	 QMessageBox::information(this, "Connexion", "Vous allez vous connecter!");
	//connexion au serveur
//	 std::cout << serverAddr.toUtf8().constData() << std::endl;
//	 std::cout << serverPort.toInt() << std::endl;
	_socket->connectToHost(serverAddr, serverPort.toInt());
	// auto client = new TcpClient(serverAddr, serverPort);
}

void Display::on_pushButton_deconnexion_clicked()
{
	//deconnexion du client
	if (QMessageBox::Yes == QMessageBox::question(this, "Deconnexion", "Êtes-vous sûr de vouloir vous déconnecter?")) {
		_socket->disconnectFromHost();
		ui->stackedWidget->setCurrentIndex(0);
		this->setFixedSize(600, 350);
	}
}

void Display::on_buttunCall_clicked()
{
	//lancement appelle
	ui->stackedWidget->setCurrentIndex(2);
}

void Display::on_pushButtonQuitCall_clicked()
{
	//quitter un appelle
	ui->stackedWidget->setCurrentIndex(1);
}
