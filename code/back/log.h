#ifndef LOG_H
#define LOG_H

#include <QFile>          // 文件操作
#include <QFileInfo>      // 文件信息（获取目录）
#include <QDir>           // 目录操作
#include <QDateTime>      // 时间戳
#include <QCoreApplication> // 获取 exe 路径
#include <QString>

constexpr int INFO = 101;
constexpr int DEBUG = 102;
constexpr int ERROR = 103;

QString logPath;
QString version = "1.2.0";

void initLog(){
    logPath = QCoreApplication::applicationDirPath() + "/log/log.txt";
    // 确保目录存在
    QFileInfo fileInfo(logPath);
    QDir dir = fileInfo.dir();
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    QFile file(logPath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QString content = "multicalculator" + version + "\n\n";
        file.write(content.toUtf8());
        file.close();
    }
}

void addLogLine(int type, const QString &message){
    QString type_str;
    switch(type){
    case INFO: type_str = "INFO"; break;
    case DEBUG: type_str = "DEBUG"; break;
    case ERROR: type_str = "ERROR"; break;
    }
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString line = QString("[%1] [%2] %3\n").arg(timestamp).arg(type_str).arg(message);
    QFile file(logPath);
    if(file.open(QIODevice::Append | QIODevice::Text)){
        file.write(line.toUtf8());
        file.close();
    }
}

#endif // LOG_H
