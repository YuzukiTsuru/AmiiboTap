//
// Created by YuzukiTsuru on 2021/5/5.
//

#ifndef AMIIBOTAP_PN532TOOL_H
#define AMIIBOTAP_PN532TOOL_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

class PN532Tool {
public:
    PN532Tool();

private:
    QList<QSerialPortInfo> availablePortList;

    void checkAvailablePortsList();
};


#endif //AMIIBOTAP_PN532TOOL_H
