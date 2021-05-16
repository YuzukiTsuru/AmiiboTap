#include <QApplication>

#include "../amiibo.h"
#include "../nfchandler.h"

#include "mainwindow.h"

int main(int argc, char **argv) {
    QApplication amiibo_tap(argc, argv);
    MainWindow window;

    window.show();

    //Amiibo amiibo(argv[1], argv[2]);
    //NFCHandler nfc;
    //nfc.write_amiibo(amiibo);

    return QApplication::exec();
}
