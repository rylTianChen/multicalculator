#include"log.h"


void initLog(){
    static QString logPath = QCoreApplication::applicationDirPath() + "/log/log.txt";
    static QString version = "1.2.0";

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
    static QString logPath = QCoreApplication::applicationDirPath()+"/log/log.txt";

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