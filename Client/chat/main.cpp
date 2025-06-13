#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include "global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/style/style_sheet.qss");
    if (qss.open(QFile::ReadOnly)){
        qDebug() << "open success";
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else qDebug() << "open failed";

    QString fileName = "config.ini";
    //获取application的路径
    QString a_path = QCoreApplication::applicationDirPath();
    //separator为分隔符 \ /
    QString config_path = QDir::toNativeSeparators(a_path + QDir::separator() + fileName);

    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;

    w.show();
    return a.exec();
}
