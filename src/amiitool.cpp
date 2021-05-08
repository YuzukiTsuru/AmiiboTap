#include <iostream>

#include <nfc3d/amiibo.h>

#include "logging.h"
#include "amiitool.h"
#include "amiibo.h"


Amiitool::Amiitool(const char *key_file_path) {
    if (!nfc3d_amiibo_load_keys(&amiibo_keys, key_file_path)) {
        qFatal("Could not load keys from %s", key_file_path);
    }
}

void Amiitool::print_hex(const uint8_t *pbtData, size_t szBytes) {
    size_t szPos;
    for (szPos = 0; szPos < szBytes; szPos++) {
        printf("%02x  ", pbtData[szPos]);
    }
    printf("\n");
}

void Amiitool::load_amiibo_data(uint8_t amiibo) {

}

void Amiitool::load_amiibo_data(QString file_path) {

}

void Amiitool::load_amiibo_data(std::string file_path) {

}

