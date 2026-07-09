#ifndef IO_FUNC_H
#define IO_FUNC_H

#include <QStandardPaths>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include"log.h"

void saveResultToDesktop(const QString &res_str)
{
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopPath + "/calculation_result.txt";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // 直接用 write() 写入 QByteArray，无额外流开销
        file.write(res_str.toUtf8());
        file.write("\n");
        file.close();
        addLogLine(INFO, "Wrote long result to text file");
    } else {
        addLogLine(ERROR, "Failed to write long result to text file");
    }

}

#endif // IO_FUNC_H