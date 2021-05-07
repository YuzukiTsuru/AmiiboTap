//
// Created by Ghost Gloomy on 2021/5/7.
//
#include "logging.h"

void logging_message(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch (type) {
        case QtDebugMsg:
            text = QString("Debug:");
            break;
        case QtWarningMsg:
            text = QString("Warning:");
            break;
        case QtCriticalMsg:
            text = QString("Critical:");
            break;
        case QtFatalMsg:
            text = QString("Fatal:");
            break;
        case QtInfoMsg:
            text = QString("Info:");
            break;
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file), context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text, context_info, msg, current_date);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\n";
    file.flush();
    file.close();
    mutex.unlock();
};