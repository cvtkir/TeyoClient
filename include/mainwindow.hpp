#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include "loginwidget.hpp"



class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private:
    LoginWidget *m_loginWidget;
    // QTabWidget *tabWidget; // Uncomment if you want to use tab widget
    // QToolBar *toolBar; // Uncomment if you want to use tool bar

    // Add other UI components and methods as needed
};

#endif
