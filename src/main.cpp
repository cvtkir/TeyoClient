#include <QApplication>
#include <QDir>
#include <QDebug>
#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
    
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}