#ifndef IO_FUNC_H
#define IO_FUNC_H

void saveResultToDesktop(QString &res_str){
    // 获取桌面路径
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString filePath = desktopPath + "/calculation_result.txt";

    // qDebug() << res_str << "\n";

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << res_str << "\n";
        file.close();
    } else {
        // qDebug() << "❌ Failed to save result!";
    }
}

#endif // IO_FUNC_H
