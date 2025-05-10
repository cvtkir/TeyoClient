#ifndef STARTWIDGET_HPP
#define STARTWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class StartWidget : public QWidget {
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);

signals:
    void loginRequested();
    void signupRequested();

private:
    QLabel *titleLabel_;
    QLabel *subtitleLabel_;
    QPushButton *loginButton_;
    QPushButton *signupButton_;

    void setupUI();
    void setupStyles();
};

#endif