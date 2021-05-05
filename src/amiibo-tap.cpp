#include <iostream>
#include <QWidget>
#include <QApplication>

#include "amiibo.h"
#include "amiitool.h"

#include "mainwindow.h"

void printUsage() {
    std::cout << "AmiiboTap keyfile binfile" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Incorrect number of arguments, to the GUI Interface" << std::endl;
        printUsage();
    } else {
        Amiitool::setKeyPath(argv[1]);
        Amiibo amiibo(argv[2]);
    }

    QApplication amiibo_tap(argc, argv);
    mainwindow _mainwindow;
    _mainwindow.show();
    return QApplication::exec();
}
