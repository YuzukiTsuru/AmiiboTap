#include "amiibo.hpp"
#include "nfchandler.hpp"
#include "logging.hpp"

int main(int argc, char **argv) {
    // init log message handler
    qInstallMessageHandler(logging_message);

    // Para error handler
    if (argc != 3 && argc != 1) {
        q:
        qFatal("Incorrect number of arguments\nUsage\n\tamiibo-tap keyfile binfile");
    }

    // CLI or GUI
    if (argc == 3) {
        // CLI Usage
        Amiibo amiibo(argv[1], argv[2]);
        NFCHandler nfc;
        nfc.write_amiibo(amiibo);

    } else {
        // GUI Usage
        // TODO: QT UI
        goto q;
    }
}
