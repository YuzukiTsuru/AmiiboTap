#include "amiibo.h"
#include "amiitool.h"
#include "nfchandler.h"
#include "logging.h"

int main(int argc, char **argv) {
    if (argc != 3 && argc != 1) {
        qFatal("Incorrect number of arguments\nUsage\n\tamiibo-tap keyfile binfile");
    }

    // TODO: Until Finish UI
    if (argc == 1) {
        qFatal("Only support CLI");
    }

    // Amiitool::setKeyPath(argv[1]);
    qInstallMessageHandler(logging_message);

    auto *amiibo = new Amiibo(argv[2]);

    auto *nfc = new NFCHandler();
    nfc->write_amiibo(amiibo);
}
