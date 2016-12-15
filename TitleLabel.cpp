#include "TitleLabel.h"

TitleLabel::TitleLabel(const QString& text,QWidget* parent)
    :QLabel(text,parent)
{
    QFont ft("Microsoft YaHei",14,25);
    setFixedHeight(30);
    setFont(ft);
    setAlignment(Qt::AlignTop);
}

TitleLabel::~TitleLabel()
{

}

