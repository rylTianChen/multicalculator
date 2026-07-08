#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载翻译（强制使用简体中文）
    QTranslator translator;
    // 固定加载中文翻译文件
    if (translator.load(":/translations/calculator_zh_CN.qm")) {
        a.installTranslator(&translator);
    } else {
        // 如果嵌入式资源加载失败，尝试从文件系统加载（调试用）
        if (translator.load("translations/calculator_zh_CN.qm")) {
            a.installTranslator(&translator);
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}