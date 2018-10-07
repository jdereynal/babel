/*
** EPITECH PROJECT, 2018
** Display
** File description:
** Display
*/

#include "Display.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Display w;
    w.show();

    return a.exec();
}
