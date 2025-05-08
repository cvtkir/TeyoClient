#include <QApplication>
#include <QDebug>
#include "mainwindow.hpp"

int main(int argc, char *argv[]) {
    QApplication::setStyle("Fusion");
    QApplication a(argc, argv);
    a.setStyleSheet(R"(
        QWidget {
            background-color:rgb(43, 41, 46);
        }
    )");
    
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}