//
// Created by Ghost Gloomy on 2021/5/7.
//

#include <QDebug>
#include "logging.h"

void logging_message(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QMutex mutex;

    mutex.lock();

    QString text;
    switch (type) {
        case QtDebugMsg:
            text = QString("Amiibo-Tap | Debug:");
            break;
        case QtWarningMsg:
            text = QString("Amiibo-Tap | Warning:");
            break;
        case QtCriticalMsg:
            text = QString("Amiibo-Tap | Critical:");
            break;
        case QtFatalMsg:
            text = QString("Amiibo-Tap | Fatal:");
            break;
        case QtInfoMsg:
            text = QString("Amiibo-Tap | Info:");
            break;
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file), QString::number(context.line));
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh:mm:ss");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text, context_info, msg, current_date);

    // Print to screen
    qDebug() << msg;

    // Print to log file
    QFile file(QString("AmiiboTap-%1.log").arg(current_date_time));
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\n";
    file.flush();
    file.close();
    mutex.unlock();
}