#include <iostream>

#include <ColorCout.hpp>

#include "amiibo.h"
#include "nfchandler.h"

int main(int argc, char **argv) {
    // Para error handler
    if (argc != 3) {
        std::cout << cc::red
                  << "Incorrect number of arguments\n"
                  << "Usage\n"
                  << "\tamiibo-tap keyfile binfile"
                  << cc::reset
                  << std::endl;
        return 0;
    }
    try {
        Amiibo amiibo(argv[1], argv[2]);
        NFCHandler nfc;
        nfc.write_amiibo(amiibo);
    } catch (const std::runtime_error &e) {
        std::cout << cc::red << e.what() << cc::reset << std::endl;
        return -1;
    }
    return 0;
}
