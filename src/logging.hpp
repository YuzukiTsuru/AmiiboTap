//
// Created by Ghost Gloomy on 2021/5/7.
//
#pragma once

#ifndef AMIIBOTAP_LOGGING_HPP
#define AMIIBOTAP_LOGGING_HPP

#include <QMutex>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

// logger
void logging_message(QtMsgType type, const QMessageLogContext &context, const QString &msg);

#endif //AMIIBOTAP_LOGGING_HPP
