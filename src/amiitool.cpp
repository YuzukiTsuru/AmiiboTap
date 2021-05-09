#include "logging.hpp"
#include "amiitool.hpp"

#include <QFile>
#include <QByteArray>

Amiitool::Amiitool(const char *key_file_path) {
    if (!nfc3d_amiibo_load_keys(&amiibo_keys, key_file_path)) {
        qFatal("Could not load keys from %s", key_file_path);
    }
}

Amiitool::~Amiitool() {
    amiibo_keys = {};
    delete[]modified_amiibo;
}

void Amiitool::print_hex(const uint8_t *pbt_data, size_t sz_bytes) {
    for (int i = 0; i < sz_bytes; i++) {
        qInfo("%02x  ", pbt_data[i]);
    }
}

uint8_t *Amiitool::load_amiibo_data(const char *file_path) {
    auto *amiibo = new uint8_t[AMIIBO_SIZE];

    QFile amiibo_file(file_path);
    if (!amiibo_file.open(QIODevice::ReadOnly)) {
        qFatal("Could not open file: %s", file_path);
    }

    auto amiibo_file_data = amiibo_file.readAll();
    amiibo_file.close();

    if (amiibo_file_data.size() < NFC3D_AMIIBO_SIZE) {
        qFatal("Could not read from input: %s", file_path);
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
        qFatal("!!! WARNING !!!: Tag signature was NOT valid");
    }
}

uint8_t *Amiitool::get_amiibo_data() {
    return modified_amiibo;
}