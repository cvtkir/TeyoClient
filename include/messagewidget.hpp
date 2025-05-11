#ifndef MESSAGEWIDGET_HPP
#define MESSAGEWIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "chatlistwidget.hpp"


class MessageWidget : public QWidget {
    Q_OBJECT
public:
    MessageWidget(QWidget *parent = nullptr);

public slots:
    void setCurrentChat(const ChatListWidget::Chat &chat);

signals:
    void msgSend(const QString &text);

private:
    ChatListWidget::Chat currentChat_;
    QTextEdit *messageHistory_;
    QLineEdit *messageInput_;
    QPushButton *sendButton_;
};

#endif // MESSAGEWIDGET_HPP