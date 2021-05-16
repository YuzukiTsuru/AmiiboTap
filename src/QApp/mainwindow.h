//
// Created by Ghost Gloomy on 2021/5/13.
//

#ifndef AMIIBOTAP_MAINWINDOW_H
#define AMIIBOTAP_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //AMIIBOTAP_MAINWINDOW_H
