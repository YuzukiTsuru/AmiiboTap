#include <QFile>
#include <QByteArray>

#include <ColorCout.hpp>

#include "amiitool.hpp"

Amiitool::Amiitool(const char *key_file_path) {
    if (!nfc3d_amiibo_load_keys(&amiibo_keys, key_file_path)) {
        std::cout << cc::red << "Could not load keys from " << key_file_path << cc::reset << std::endl;
    }
}

uint8_t *Amiitool::load_amiibo_data(const char *file_path) {
    auto *amiibo = new uint8_t[AMIIBO_SIZE];

    QFile amiibo_file(file_path);
    if (!amiibo_file.open(QIODevice::ReadOnly)) {
        std::cout << cc::red << "Could not open file: " << file_path << cc::reset << std::endl;
    }

    auto amiibo_file_data = amiibo_file.readAll();
    amiibo_file.close();

    if (amiibo_file_data.size() < NFC3D_AMIIBO_SIZE) {
        std::cout << cc::red << "Could not read from input: %s" << file_path << cc::reset << std::endl;
    }
    for (int i = 0; i < amiibo_file_data.size(); ++i) {
        amiibo[i] = static_cast<uint8_t>(amiibo_file_data[i]);
    }
    return amiibo;
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