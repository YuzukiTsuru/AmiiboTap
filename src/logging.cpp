//
// Created by Ghost Gloomy on 2021/5/7.
//

#include <QDebug>
#include <iostream>
#include "logging.hpp"

void logging_message(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QMutex mutex;

    mutex.lock();

    QString text;
    switch (type) {
        case QtDebugMsg:
            text = QString("Amiibo-Tap | Debug");
            break;
        case QtWarningMsg:
            text = QString("Amiibo-Tap | Warning");
            break;
        case QtCriticalMsg:
            text = QString("Amiibo-Tap | Critical");
            break;
        case QtFatalMsg:
            text = QString("Amiibo-Tap | Fatal");
            break;
        case QtInfoMsg:
            text = QString("Amiibo-Tap | Info");
            break;
    }

    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString current_date = QString("| %1 |").arg(current_date_time);
    QString message = QString("%1 %2 %3").arg(text, current_date, msg);

    std::cout << msg.toStdString() << std::endl;

    // Print to log file
    QFile file(QString("AmiiboTap.log"));
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream text_stream(&file);
    text_stream << message << "\n";
    file.flush();
    file.close();
    mutex.unlock();
}