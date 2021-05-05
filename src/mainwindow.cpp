//
// Created by YuzukiTsuru on 2021/5/5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_mainwindow.h"


mainwindow::mainwindow(QWidget *parent) : QWidget(parent), ui(new Ui::mainwindow) {
    ui->setupUi(this);
}

mainwindow::~mainwindow() {
    delete ui;
}

