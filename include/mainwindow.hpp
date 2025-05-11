#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>
#include "authwidget.hpp"
#include "chatwidget.hpp"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    AuthWidget *authWidget_;
    ChatWidget *chatWidget_; 

};

#endif
