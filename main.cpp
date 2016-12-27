
#include "mainwindow.h"
#include "QuadApplication.h"
#include "Toolbox.h"
#include "linkmanager.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QuadApplication *a = new QuadApplication(argc, argv);

    Q_CHECK_PTR(a);
    int exitcode = 0;
    {
        if(!a->_initForNormalAppBoot()) {
            return -1;
        }
        exitcode = a->exec();
    }
    delete a;

    qDebug() << "After app delete";
    return exitcode;
}
