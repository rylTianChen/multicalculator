#include <QApplication>
#include <QTranslator>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    // ===== 使用 INI 文件存储设置 =====
    QString iniPath = QCoreApplication::applicationDirPath() + "/settings.ini";
    QSettings settings(iniPath, QSettings::IniFormat);
    settings.sync();

    QString lang = settings.value("Language", "zh_CN").toString();

    QTranslator translator;
    QString appPath = QCoreApplication::applicationDirPath();
    QString qmFile = appPath + "/calculator_" + lang + ".qm";

    if (translator.load(qmFile)) {
        a.installTranslator(&translator);
    } else {
    }

    MainWindow w;
    w.show();
    return a.exec();
}