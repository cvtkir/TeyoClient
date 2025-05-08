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
    QLabel *m_titleLabel;
    QLabel *m_subtitleLabel;
    QPushButton *m_loginButton;
    QPushButton *m_signupButton;

    void setupUI();
    void setupStyles();
};

#endif