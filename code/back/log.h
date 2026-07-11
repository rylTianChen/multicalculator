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

void initLog();
void addLogLine(int type, const QString &message);



#endif // LOG_H
