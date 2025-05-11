#ifndef CHATWIDGET_HPP
#define CHATWIDGET_HPP

#include <QWidget>
#include <QSplitter>
#include "chatlistwidget.hpp"
#include "messagewidget.hpp"

class ChatWidget : public QWidget {
    Q_OBJECT
public:
    ChatWidget(QWidget *parent = nullptr);

private:
    QSplitter *splitter_;
    ChatListWidget *chatList_;
    MessageWidget *messageArea_;
};

#endif // CHATWIDGET_HPP