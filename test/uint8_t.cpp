//
// Created by Ghost Gloomy on 2021/5/9.
//

#include <QByteArray>
#include <QDebug>

int main() {
    QByteArray array;
    array[0] = 0x30;
    array[1] = 0xe1;
    array[2] = 0xf2;
    array[3] = 0xeff5;
    auto a = reinterpret_cast<uint8_t *>( array.data());
3    qDebug() << a;
}