#ifndef TITLELABEL_H
#define TITLELABEL_H

#include <QLabel>

class TitleLabel : public QLabel
{
    Q_OBJECT
public:
    TitleLabel(const QString& text,QWidget *parent = 0);
    ~TitleLabel();
};

#endif // TITLELABEL_H
