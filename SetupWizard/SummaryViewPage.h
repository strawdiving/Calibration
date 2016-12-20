#ifndef SUMMARYVIEWPAGE_H
#define SUMMARYVIEWPAGE_H

#include <QWidget>
#include <QModelIndex>
#include <QMap>

class SetupWidget;

namespace Ui {
class SummaryViewPage;
}

class SummaryViewPage : public QWidget
{
    Q_OBJECT

public:
    explicit SummaryViewPage(SetupWidget *calWidget, QWidget *parent = 0);
    ~SummaryViewPage();

signals:
    void showPanel(QString compName);

public slots:
    void _setupCompleteChanged(bool setupComplete);
    void _setupCompleteStatus(QMap<QString, bool> mapSetupCompleteStatus);
    void _showPanel(QModelIndex);

private:
    Ui::SummaryViewPage *ui;
    SetupWidget* _calWidget;
    const QString setupCompleteText = "Below you'll find a summary of the settings for your vehicle."
                                      "To the left are the setup menus for each component";
    const QString needSetupText = "WARNING: Your vehicle requires setup prior to flight.Please resolve"
                                  " the items marked in red using the menu on the left.";

    QMap<QString,bool>_mapSetupCompleteStatus;
    QMap<QString,QString> _components;
};

#endif // SUMMARYVIEWPAGE_H
