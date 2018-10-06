/*
** EPITECH PROJECT, 2018
** Display
** File description:
** Display
*/

#include "Display.h"
#include <QtWidgets/QMessageBox>
#include "ui_Display.h"

Display::Display(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
    this->setWindowTitle("Babel ~ Application de contact");
}

Display::~Display()
{
    delete ui;
}

void Display::on_pushButton_connexion_clicked()
{
    QString username = ui->input_name->text();
    QString server_port = ui->input_port_server->text();
    QString client_port = ui->input_port_client->text();
    QString serveur_addr = ui->input_addr->text();

    QMessageBox::information(this, "Connexion", "Vous allez vous connecter!");
    //connexion au serveur
    ui->stackedWidget->setCurrentIndex(1);
    this->setFixedSize(320, 400);
}

void Display::on_pushButton_deconnexion_clicked()
{
    //deconnexion du client
    if (QMessageBox::Yes == QMessageBox::question(this, "Deconnexion", "Êtes-vous sûr de vouloir vous déconnecter?")) {
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
