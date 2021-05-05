//
// Created by YuzukiTsuru on 2021/5/5.
//

#ifndef AMIIBOTAP_MAINWINDOW_H
#define AMIIBOTAP_MAINWINDOW_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE

class mainwindow : public QWidget {
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);

    ~mainwindow() override;

private:
    Ui::mainwindow *ui;
};


#endif //AMIIBOTAP_MAINWINDOW_H
