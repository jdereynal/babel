/*
** EPITECH PROJECT, 2018
** Display
** File description:
** Display
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <QtWidgets/QMainWindow>

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

private:
    Ui::Display *ui;
};

#endif // DISPLAY_H
