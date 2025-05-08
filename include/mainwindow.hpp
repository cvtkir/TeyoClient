#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>
#include "startwidget.hpp"
#include "loginwidget.hpp"
#include "signupwidget.hpp"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    StartWidget *m_startWidget = nullptr;
    LoginWidget *m_loginWidget = nullptr;
    SignupWidget *m_signupWidget = nullptr;

};

#endif
