#ifndef AMIIBOTAP_NFCHANDLER_H
#define AMIIBOTAP_NFCHANDLER_H

#include <iostream>
#include <exception>

#ifdef __cplusplus
extern "C" {
#endif
#include <nfc/nfc-types.h>
#include <nfc/nfc.h>
#ifdef __cplusplus
}
#endif

#include "amiibo_static.h"
#include "amiibo.h"
#include "exception.h"

class NFCHandler {
public:
    NFCHandler();

    void read_tag_UUID(AMIIBIN *uuidBuffer);

    void write_amiibo(Amiibo amiibo);

private:
    nfc_target target = {};
    nfc_context *context = nullptr;
    nfc_device *device = nullptr;

    const AMIIBIN dynamic_lock_bytes[4] = {0x01, 0x00, 0x0f, 0xbd};
    const AMIIBIN static_lock_bytes[4] = {0x00, 0x00, 0x0f, 0xe0};

    const nfc_modulation nmMifare = {
            .nmt = NMT_ISO14443A,
            .nbr = NBR_106,
    };

    void write_buffer(const AMIIBIN *buffer);

    void write_page(AMIIBIN page, const AMIIBIN *buffer);

    void write_data_pages(const AMIIBIN *buffer);

    void write_dynamic_lock_bytes();

    void write_static_lock_bytes();
};

#endif //AMIIBOTAP_NFCHANDLER_H