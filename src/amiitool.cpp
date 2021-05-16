#include <fstream>
#include <vector>

#include <ColorCout.hpp>

#include "amiitool.h"
#include "binarybuffer.h"
#include "exception.h"

Amiitool::Amiitool(const char *key_file_path) {
    if (!nfc3d_amiibo_load_keys(&amiibo_keys, key_file_path)) {
        std::cout << cc::red << "Could not load keys from " << key_file_path << cc::reset << std::endl;
    }
}

uint8_t *Amiitool::load_amiibo_data(const char *file_path) {
    binarybuffer buffer(file_path);
    if (buffer.get_size() < AMIIBO_SIZE) {
        throw amiibo_file_size_error(file_path);
    }
    return buffer.get_data();
}

void Amiitool::amiibo_encryption(uint8_t *amiibo) {
    nfc3d_amiibo_pack(&amiibo_keys, amiibo, modified_amiibo);
}

void Amiitool::amiibo_decryption(uint8_t *amiibo) {
    if (!nfc3d_amiibo_unpack(&amiibo_keys, amiibo, modified_amiibo)) {
        std::cout << cc::red << "!!! WARNING !!!: Tag signature was NOT valid" << cc::reset << std::endl;
    }
}

uint8_t *Amiitool::get_amiibo_data() {
    return modified_amiibo;
}