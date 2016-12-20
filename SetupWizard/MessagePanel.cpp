#include "MessagePanel.h"
#include <QGridLayout>

MessagePanel::MessagePanel(QWidget *parent):
    QWidget(parent)
{
    _messageText = new QLabel(this);
    _messageText->setText(_disconnectedVehicleText);

    _messageText->setWordWrap(true);
    _messageText->setAlignment(Qt::AlignCenter);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(_messageText);
    this->setLayout(layout);
}

MessagePanel::~MessagePanel()
{


}

void MessagePanel::_showMessage(const QString text)
{
    _messageText->setText(text);
}
