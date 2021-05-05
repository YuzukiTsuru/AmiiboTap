//
// Created by YuzukiTsuru on 2021/5/5.
//

#include "PN532Tool.h"

PN532Tool::PN532Tool() {
    checkAvailablePortsList();
}

void PN532Tool::checkAvailablePortsList() {
    availablePortList = QSerialPortInfo::availablePorts();
}
