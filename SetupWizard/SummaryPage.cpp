#include "SummaryPage.h"
#include <QGridLayout>


SummaryPage::SummaryPage(SetupWidget *calWidget, QWidget *parent)
    : QWidget(parent),
      _calWidget(calWidget)
{
  _title = new TitleLabel("Vehicle Summary");
  _label= new QLabel(needSetupText);
  _label->setStyleSheet("font: 25 11pt 'Microsoft Yahei';color: red");
  _label->setAlignment(Qt::AlignTop);
  _label->setFixedHeight(50);
  _label->setWordWrap(true);

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(_label);
  this->setLayout(layout);
}

SummaryPage::~SummaryPage()
{

}

void SummaryPage::_setupCompleteChanged(bool setupComplete)
{
    if(!setupComplete) {
        _label->setStyleSheet("color:black");
        _label->setText(setupCompleteText);
    }
}
