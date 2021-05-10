#include <iostream>

#include <ColorCout.hpp>

#include "amiibo.hpp"
#include "nfchandler.hpp"

int main(int argc, char **argv) {
    // Para error handler
    if (argc != 3) {
        std::cout << cc::red
                  << "Incorrect number of arguments\n"
                  << "Usage\n"
                  << "\tamiibo-tap keyfile binfile"
                  << cc::reset
                  << std::endl;
    }
    Amiibo amiibo(argv[1], argv[2]);
    NFCHandler nfc;
    nfc.write_amiibo(amiibo);
    return 0;
}
