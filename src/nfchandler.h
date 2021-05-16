#ifndef AMIIBOTAP_NFCHANDLER_H
#define AMIIBOTAP_NFCHANDLER_H

#include <iostream>
#include <exception>
#include <nfc/nfc-types.h>

#include "amiibo_static.h"

class Amiibo;

class NFCHandler {
public:
    NFCHandler();

    void read_tag_UUID(uint8_t *uuidBuffer);

    void write_amiibo(Amiibo amiibo);

private:
    nfc_target target = {};
    nfc_context *context = nullptr;
    nfc_device *device = nullptr;

    const uint8_t dynamic_lock_bytes[4] = {0x01, 0x00, 0x0f, 0xbd};
    const uint8_t static_lock_bytes[4] = {0x00, 0x00, 0x0f, 0xe0};

    const nfc_modulation nmMifare = {
            .nmt = NMT_ISO14443A,
            .nbr = NBR_106,
    };

    void write_buffer(const uint8_t *buffer);

    void write_page(uint8_t page, const uint8_t *buffer);

    void write_data_pages(const uint8_t *buffer);

    void write_dynamic_lock_bytes();

    void write_static_lock_bytes();
};

#endif //AMIIBOTAP_NFCHANDLER_H