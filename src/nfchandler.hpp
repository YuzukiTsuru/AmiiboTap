#ifndef AMIIBOTAP_NFCHANDLER_HPP
#define AMIIBOTAP_NFCHANDLER_HPP

#include <iostream>
#include <nfc/nfc-types.h>

#include "amiibo_static.hpp"

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

    void write_buffer(const uint8_t *buffer);

    void write_page(uint8_t page, const uint8_t *buffer);

    void write_data_pages(const uint8_t *buffer);

    void write_dynamic_lock_bytes();

    void write_static_lock_bytes();
};

#endif //AMIIBOTAP_NFCHANDLER_HPP