#include <iostream>
#include <nfc/nfc.h>

#include "amiibo_static.h"
#include "nfchandler.h"
#include "amiitool.h"
#include "amiibo.h"
#include "logging.h"


const uint8_t dynamic_lock_bytes[4] = {0x01, 0x00, 0x0f, 0xbd};
const uint8_t static_lock_bytes[4] = {0x00, 0x00, 0x0F, 0xE0};

const nfc_modulation nmMifare = {
        .nmt = NMT_ISO14443A,
        .nbr = NBR_106,
};

NFCHandler::NFCHandler() {
    qInfo("Initializing NFC adapter");

    nfc_init(&context);

    if (!context) {
        qFatal("Unable to init libnfc (malloc)");
    }

    device = nfc_open(context, nullptr);

    if (device == nullptr) {
        qFatal("Unable to open NFC device.");
    }

    if (nfc_initiator_init(device) < 0) {
        nfc_perror(device, "nfc_initiator_init");
    }

    qInfo("NFC Reader: OPENED, DO NOT DISCONNECT");
}

void NFCHandler::read_tag_UUID(uint8_t uuidBuffer[]) {
    qInfo("Scaning TAG...");

    if (nfc_initiator_select_passive_target(device, nmMifare, nullptr, 0, &target) > 0) {
        qInfo("Read UID: ");
        size_t uidSize = target.nti.nai.szUidLen;
        // Amiitool::shared()->printHex(target.nti.nai.abtUid, uidSize);

        if (UUID_SIZE != uidSize) {
            qFatal("Read wrong size UID");
        }

        for (int i = 0; i < UUID_SIZE; ++i) {
            uuidBuffer[i] = target.nti.nai.abtUid[i];
        }
    }
}

void NFCHandler::write_amiibo(Amiibo *amiibo) {
    uint8_t uuid[UUID_SIZE];
    read_tag_UUID(uuid);

    amiibo->set_UUID(uuid);
    write_buffer(amiibo->encrypted_buffer);
}

void NFCHandler::write_buffer(const uint8_t *buffer) {
    qInfo("Writing tag...");
    write_data_pages(buffer);
    write_dynamic_lock_bytes();
    write_static_lock_bytes();
    qInfo("Finished writing tag.");
}

void NFCHandler::write_data_pages(const uint8_t *buffer) {
    qInfo("Writing encrypted bin...");
    for (uint8_t i = 3; i < PAGE_COUNT; i++) {
        write_page(i, buffer + (i * 4));
    }
    qInfo("Writing encrypted bin done.");
}

void NFCHandler::write_dynamic_lock_bytes() {
    qInfo("Writing dynamic lock bytes...");
    write_page(130, dynamic_lock_bytes);
    qInfo("Writing dynamic lock bytes done.");
}

void NFCHandler::write_static_lock_bytes() {
    qInfo("Writing static lock bytes...");
    write_page(2, static_lock_bytes);
    qInfo("Writing static lock bytes done.");
}

void NFCHandler::write_page(uint8_t page, const uint8_t *buffer) {
    qInfo("Writing to %d: %02x %02x %02x %02x...", page, buffer[0], buffer[1], buffer[2], buffer[3]);

    uint8_t sendData[6] = {WRITE_COMMAND, page, buffer[0], buffer[1], buffer[2], buffer[3]};

    int responseCode = nfc_initiator_transceive_bytes(device, sendData, 6, nullptr, 0, 0);

    if (responseCode == 0) {
        qInfo("Done.");
    } else {
        qWarning("Failed > try to write the tag");
        nfc_perror(device, "Write");
        qFatal("Write Failed");
    }
}
