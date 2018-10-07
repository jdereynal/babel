/*
** EPITECH PROJECT, 2018
** Display
** File description:
** Display
*/

#include <QtWidgets/QMessageBox>
#include <QListWidget>
#include <sstream>
#include <iostream>
#include "Display.h"
#include "ui_Display.h"

Display::Display(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::Display)
{
	ui->setupUi(this);
	_currentCall = 0;
	this->setWindowTitle("Babel ~ Application de contact");
	_socket = new QTcpSocket(this);
	QObject::connect(_socket, SIGNAL(connected()), this, SLOT(connectedHandler()));
	QObject::connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnectedHandler()));
	QObject::connect(_socket, SIGNAL(readyRead()), this, SLOT(readHandler()));
}

Display::~Display()
{
	_socket->close();
	delete ui;
}

void Display::connectedHandler()
{
	ui->stackedWidget->setCurrentIndex(1);
	this->setFixedSize(320, 400);
	std::string tmp = "USER " + _username + "\n";
	_socket->write(tmp.c_str());
	tmp = "PORT " + _port + "\n";
	_socket->write(tmp.c_str());
}

void Display::disconnectedHandler()
{
	ui->stackedWidget->setCurrentIndex(0);
	this->setFixedSize(600, 350);
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
		if (split[0] == "CONTACTS" && split.size() > 1 && split[1] != "")
			for (int i = 1; i < split.size(); i++) {
				std::istringstream ss(split[i]);
				std::string username;
				std::string id;
				std::getline(ss, username, ',');
				std::getline(ss, id, ',');
				_contacts.insert(std::make_pair(std::stoi(id), username));
			}
		if (split[0] == "CALLREQ" && split.size() > 1 && split[1] != "") {
			unsigned int id = std::stoi(split[1]);
			if (id < 0)
				return ;
			auto it = _contacts.find(id);
			if (it == _contacts.end())
				return ;
			std::string tmp = _contacts[id] + " vous appelle. Répondre ?";
			if (QMessageBox::Yes == QMessageBox::question(this, "Appel entrant", QString::fromStdString(tmp))) {
				std::string tmp = "CALLREQ " + std::to_string(it->first) + "\n";
				_socket->write(tmp.c_str());
				_currentCall = it->first;
				ui->stackedWidget->setCurrentIndex(2);
			}
		}
		if (split[0] == "ENDCALL" && split.size() > 1 && split[1] != "")
			on_pushButtonQuitCall_clicked();
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
	if (username.trimmed().isEmpty() || serverAddr.trimmed().isEmpty() || serverPort.trimmed().isEmpty() || clientPort.trimmed().isEmpty())
		return ;
	if (clientPort.toInt() <= 0 || serverPort.toInt() <= 0)
		return ;
	_username = username.toStdString();
	_port = clientPort.toStdString();
	_socket->connectToHost(serverAddr.trimmed(), serverPort.toInt());
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

void Display::fillContactList()
{
    ui->listWidget->clear();
    for (std::map<std::string, unsigned int>::iterator it = this->_contacts.begin(); it != this->_contacts.end(); ++it) {
	    ui->listWidget->addItem(QString::number(it->second) + " " + QString(it->second));
    }
}

void Display::on_buttunCall_clicked()
{
	//lancement appelle
    QListWidgetItem *item = this->ui->listWidget->currentItem();
    if (item == nullptr)
        return ;
    QMessageBox::information(this, "Appelle", "Vous essayez d'appeler " + item->text() + ".");
    ui->stackedWidget->setCurrentIndex(2);
}

void Display::on_pushButtonQuitCall_clicked()
{
	//quitter un appelle
	if (_currentCall) {
		std::string tmp = "ENDCALL " + std::to_string(_currentCall) + "\n";
		_socket->write(tmp.c_str());
	}
	_currentCall = 0;
	ui->stackedWidget->setCurrentIndex(1);
}
