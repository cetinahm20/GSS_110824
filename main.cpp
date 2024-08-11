#include "mainwindow.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QFile>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
    QFile styleSheetFile(":/Genetive.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    */

    MainWindow w;
    w.show();
    return a.exec();
}
