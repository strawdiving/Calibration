#ifndef SUMMARYPAGE_H
#define SUMMARYPAGE_H

#include <QWidget>
#include <QLabel>
#include "TitleLabel.h"

class SetupWidget;

class SummaryPage: public QWidget
{
    Q_OBJECT

public:
    SummaryPage(SetupWidget *calWidget, QWidget *parent = 0);
    ~SummaryPage();

public slots:
    void _setupCompleteChanged(bool setupComplete);

private:
    SetupWidget* _calWidget;
    QLabel* _label;
    TitleLabel* _title;
    const QString setupCompleteText = "Below you'll find a summary of the settings for your vehicle."
                                      "To the left are the setup menus for each component";
    const QString needSetupText = "WARNING: Your vehicle requires setup prior to flight.Please resolve"
                                  "the items marked in red using the menu on the left.";

};

#endif // SUMMARYPAGE_H
