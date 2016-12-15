#ifndef PARAMSPAGE_H
#define PARAMSPAGE_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableView>
#include <QListView>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QMap>
#include "FactMetaData.h"
class SetupWidget;

//class CalWidget;
class TitleLabel;

class ParamsPage: public QWidget
{
    Q_OBJECT
public:
    ParamsPage(SetupWidget *setupWidget, QWidget*parent = 0);
    ~ParamsPage();

    void addParamItem(FactMetaData* metaData);
    void searchParams(QString &searchText);
    void showParams(QMap<QString, FactMetaData*> mapParameterName2FactMetaData);

public slots:

    void showGroupTable(const QModelIndex &index);
    void search(void);
    void saveToFile(void);
    void loadFromFile(void);

private:
    //CalWidget* _calWidget;
    SetupWidget* _calWidget;
    QPushButton *_refreshBtn;
    QPushButton *_loadBtn;
    QPushButton *_saveBtn;
    TitleLabel* _title;

    QLineEdit *_searchLineEdit;
    QPushButton *_searchBtn;

    QTableView * _paramTable;
    QStandardItemModel * _paramModel;

    QListView* _groupList;
    QStandardItemModel* _groupModel;

    QStringList _groupStringList;
    QMap<QString, QMap<QString, FactMetaData *>> _mapGroup2FactMetaData;
    QMap<QString, FactMetaData *> _mapParameterName2FactMetaData;

    uint _tableRowCount;
};

#endif // PARAMSPAGE_H
