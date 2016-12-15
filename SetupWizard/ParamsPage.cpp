#include "ParamsPage.h"
#include <QHeaderView>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>
#include <TitleLabel.h>
#include "SetupWidget.h"

ParamsPage::ParamsPage(SetupWidget *setupWidget, QWidget *parent):
    QWidget(parent),
    _tableRowCount(0),
    _calWidget(setupWidget)
{
    _title = new TitleLabel(tr("Parameters"));

    _refreshBtn = new QPushButton(tr("Refresh"));
    _loadBtn = new QPushButton(tr("Load from file"));
    _saveBtn = new QPushButton(tr("Save to file"));

    _searchBtn = new QPushButton(tr("search"));
    _searchLineEdit = new QLineEdit();

    QHBoxLayout *btnLayout = new QHBoxLayout;

    btnLayout->addWidget(_refreshBtn);
    btnLayout->addWidget(_loadBtn);
    btnLayout->addWidget(_saveBtn);
    btnLayout->addStretch(2);
    btnLayout->addWidget(_searchLineEdit);
    btnLayout->addWidget(_searchBtn);

    QVBoxLayout *layout = new QVBoxLayout;
    //QSplitter* splitter = new QSplitter();
    QHBoxLayout * splitter = new QHBoxLayout;

    _groupList = new QListView();
    _groupModel = new QStandardItemModel();
    _groupList->setModel(_groupModel);

    connect(_groupList,&QListView::clicked,this,&ParamsPage::showGroupTable);

    _paramTable = new QTableView();
    _paramTable->verticalHeader()->hide();
    //when select, the whole row selected
    _paramTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _paramTable->setSortingEnabled(true);

    splitter->addWidget(_groupList,1);
    splitter->addWidget(_paramTable,3);

    layout->addWidget(_title);
    layout->addLayout(btnLayout,1);
    layout->addLayout(splitter,3);
    layout->setSpacing(10);

    this->setLayout(layout);

    connect(_refreshBtn,&QPushButton::clicked,_calWidget,&SetupWidget::loadParamFactMetaDataFile);
    connect(_searchBtn,&QPushButton::clicked,this,&ParamsPage::search);
    connect(_loadBtn,&QPushButton::clicked,this,&ParamsPage::loadFromFile);
    connect(_saveBtn,&QPushButton::clicked,this,&ParamsPage::saveToFile);
}

ParamsPage::~ParamsPage()
{

}

void ParamsPage::showParams(QMap<QString, FactMetaData *> mapParameterName2FactMetaData)
{
 qDebug()<<"ParamsPage: showParams ";
 //_infoLabel->setText(metaData->name());
    QString  group;
    _groupStringList.clear();
    if(!mapParameterName2FactMetaData.isEmpty()) {
        _mapParameterName2FactMetaData = mapParameterName2FactMetaData;
        foreach (const QString paramName,_mapParameterName2FactMetaData.keys()) {
            group = _mapParameterName2FactMetaData[paramName]->group();
            if(!_groupStringList.contains(group)) {
                _groupStringList.append(group);
                QStandardItem* item = new QStandardItem(group);
                _groupModel->appendRow(item);
                _groupModel->sort(0);
            }
            if(!_mapGroup2FactMetaData[group].contains(paramName)) {
                _mapGroup2FactMetaData[group].insert(paramName,_mapParameterName2FactMetaData[paramName]);
            }
        }
    }
}

void ParamsPage::showGroupTable(const QModelIndex &index)
{

   FactMetaData* metaData = NULL;
   QString group;
   _tableRowCount = 0;

   if(!_mapGroup2FactMetaData.isEmpty()) {

       _paramModel = new QStandardItemModel();

       _paramModel->setHorizontalHeaderItem(0,new QStandardItem(tr("name")));
       _paramModel->setHorizontalHeaderItem(1,new QStandardItem(tr("default value")));
       _paramModel->setHorizontalHeaderItem(2,new QStandardItem(tr("unit")));
       _paramModel->setHorizontalHeaderItem(3,new QStandardItem(tr("description")));

       group = index.data().toString();
       foreach (QString paramName, _mapGroup2FactMetaData[group].keys()) {
           metaData = _mapGroup2FactMetaData[group][paramName];
           Q_ASSERT(metaData);
           addParamItem(metaData);
       }
   }
   else {
       qDebug()<<"_mapGroup2FactMetaData is empty";
   }
}

 void ParamsPage::addParamItem(FactMetaData* metaData)
 {
     _paramModel->setItem(_tableRowCount,0,new QStandardItem(metaData->name()));
     if(metaData->defaultValueAvailable()) {
         QVariant rawValue = metaData->rawDefaultValue();
         _paramModel->setItem(_tableRowCount, 1,new QStandardItem(rawValue.toString()));
     }
     _paramModel->setItem(_tableRowCount, 2,new QStandardItem(metaData->rawUnit()));
     _paramModel->setItem(_tableRowCount, 3,new QStandardItem(metaData->shortDescription()));

     _tableRowCount++;
     _paramModel->sort(0);

     _paramTable->setWordWrap(true);
     _paramTable->resizeColumnsToContents();
     _paramTable->resizeRowsToContents();
     _paramTable->setModel(_paramModel);
 }

 void ParamsPage::searchParams(QString &searchText)
 {
     FactMetaData* metaData = NULL;
     QStringList matchParams;
     _tableRowCount = 0;

     foreach (QString paramName, _mapParameterName2FactMetaData.keys()) {
         if(paramName.contains(searchText,Qt::CaseInsensitive)) {
             matchParams<<paramName;
         }
     }
     if(!matchParams.isEmpty()) {
         matchParams.sort();
         _paramModel = new QStandardItemModel();

         _paramModel->setHorizontalHeaderItem(0,new QStandardItem(tr("name")));
         _paramModel->setHorizontalHeaderItem(1,new QStandardItem(tr("default value")));
         _paramModel->setHorizontalHeaderItem(2,new QStandardItem(tr("unit")));
         _paramModel->setHorizontalHeaderItem(3,new QStandardItem(tr("description")));

         for(int i = 0; i<matchParams.count();i++) {
         metaData = _mapParameterName2FactMetaData[matchParams.at(i)];
         addParamItem(metaData);
         }
     }
     else {
         QMessageBox::warning(this,tr("Warning"),tr("No parameter matches."),QMessageBox::Cancel);
     }
 }

 void ParamsPage::search(void)
 {
     if(!_searchLineEdit->text().isEmpty()) {
        searchParams(_searchLineEdit->text());
     }
     else {
         QMessageBox::warning(this,tr("Warning"),tr("No parameter entered. \n\nPlease input parameter name..."),QMessageBox::Cancel);
     }
 }

 void ParamsPage::saveToFile(void)
 {
     QString fileName = QFileDialog::getSaveFileName(this,tr("Save Parameters"),"E:/untitled.params",tr("Parameter Files (*.params)"));


     if(!fileName.isEmpty()) {
         QFile file(fileName);

         if(!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
             QMessageBox::warning(this,tr("Warning"),QString("Unable to create file: %1").arg(fileName),QMessageBox::Cancel);
             return;
         }

         QTextStream stream(&file);
         stream << "# Onboard parameters for vehicle " << "\n";
         stream << "#\n";
         stream << "# MAV ID  COMPONENT ID  PARAM NAME  VALUE (FLOAT)\n";
         stream<<"hello world";
         stream << "hello world";

         stream.flush();

     }
 }

 void ParamsPage::loadFromFile(void)
 {
     QString fileName = QFileDialog::getOpenFileName(this,tr("Open Parameter File"),"E:/",tr( "Parameter Files (*.params)"));
     if(!fileName.isEmpty()) {
         QFile file(fileName);

         if(!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
             QMessageBox::warning(this,tr("Warning"),QString("Unable to open file: %1").arg(fileName),QMessageBox::Cancel);
             return;
         }

         while(file.atEnd()) {
             qDebug()<<"file is empty";
         }
        QTextStream stream(&file);
        while(!stream.atEnd()) {
            qDebug()<<"read stream";
            QString line = stream.readLine();
            if(!line.startsWith("#")) {
                qDebug()<<line;
            }
        }
     }
 }
