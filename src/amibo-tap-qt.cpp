#include "amiibo.hpp"
#include "nfchandler.hpp"

int main(int argc, char **argv) {
    Amiibo amiibo(argv[1], argv[2]);
    NFCHandler nfc;
    nfc.write_amiibo(amiibo);
    return 0;
}
