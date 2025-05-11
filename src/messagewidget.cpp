#include "messagewidget.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>

MessageWidget::MessageWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    messageHistory_ = new QTextEdit();
    messageHistory_->setReadOnly(true);

    QHBoxLayout *inputLayout = new QHBoxLayout();
    messageInput_ = new QLineEdit();
    sendButton_ = new QPushButton("Send");

    inputLayout->addWidget(messageInput_);
    inputLayout->addWidget(sendButton_);

    layout->addWidget(messageHistory_);
    layout->addLayout(inputLayout);

    connect(sendButton_, &QPushButton::clicked, [this]() {
        QString text = messageInput_->text();
        if (!text.isEmpty()) {
            messageHistory_->append("Вы: " + text);
            messageInput_->clear();
            emit msgSend(text);
        }
    });
}

void MessageWidget::setCurrentChat(const ChatListWidget::Chat &chat) {
    currentChat_ = chat;
    messageHistory_->clear();
    qDebug() << "in messagewidget:";
    currentChat_.Print();
}

// add setupstyles with setStyleSheet
