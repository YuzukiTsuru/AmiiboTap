#include <iostream>

#include <ColorCout.hpp>

#include "amiibo.hpp"
#include "nfchandler.hpp"

int main(int argc, char **argv) {
    // Para error handler
    if (argc != 3 && argc != 1) {
        q:
        std::cout << cc::red
                  << "Incorrect number of arguments\n"
                  << "Usage\n"
                  << "\tamiibo-tap keyfile binfile"
                  << cc::reset
                  << std::endl;
    }

    // CLI or GUI
    if (argc == 3) {
        // CLI Usage
        Amiibo amiibo(argv[1], argv[2]);
        NFCHandler nfc;
        nfc.write_amiibo(amiibo);
        return 0;
    } else {
        // GUI Usage
        // TODO: QT UI
        goto q;
    }
}
