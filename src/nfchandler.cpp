#include <ColorCout.hpp>

#include "nfchandler.h"

NFCHandler::NFCHandler() {
    std::cout << cc::cyan << "Initializing NFC adapter" << cc::reset << std::endl;
    // init nfc
    nfc_init(&context);

    if (!context) {
        std::cout << cc::red << "Unable to init libnfc (malloc)" << cc::reset << std::endl;
        throw nfc_init_fault();
    }

    device = nfc_open(context, nullptr);

    if (device == nullptr) {
        std::cout << cc::red << "Unable to open NFC device." << cc::reset << std::endl;
        throw nfc_not_found();
    }

    nfc_initiator_init(device);

    std::cout << cc::green << "NFC Reader: OPENED, DO NOT DISCONNECT" << cc::reset << std::endl;
}

void NFCHandler::read_tag_UUID(AMIIBIN uuidBuffer[]) {
    std::cout << cc::cyan << "Scaning TAG..." << cc::reset << std::endl;

    if (nfc_initiator_select_passive_target(device, nmMifare, nullptr, 0, &target) > 0) {
        size_t uidSize = target.nti.nai.szUidLen;
        std::cout << cc::cyan << "Read UID: " << cc::yellow;
        for (int i = 0; i < uidSize; i++) {
            std::cout << " " << +target.nti.nai.abtUid[i];
        }
        std::cout << cc::reset << std::endl;

        if (UUID_SIZE != uidSize) {
            std::cout << cc::red << "Read wrong size UID" << cc::reset << std::endl;
        }

        for (int i = 0; i < UUID_SIZE; ++i) {
            uuidBuffer[i] = target.nti.nai.abtUid[i];
        }
    }
}

void NFCHandler::write_amiibo(Amiibo amiibo) {
    AMIIBIN uuid[UUID_SIZE];
    read_tag_UUID(uuid);

    amiibo.set_UUID(uuid);
    write_buffer(amiibo.get_amiibo_data());
}

void NFCHandler::write_buffer(const AMIIBIN *buffer) {
    std::cout << cc::cyan << "Writing tag..." << cc::reset << std::endl;
    write_data_pages(buffer);
    write_dynamic_lock_bytes();
    write_static_lock_bytes();
    std::cout << cc::cyan << "Finished writing tag." << cc::reset << std::endl;
}

void NFCHandler::write_data_pages(const AMIIBIN *buffer) {
    std::cout << cc::cyan << "Writing encrypted bin..." << cc::reset << std::endl;
    for (AMIIBIN i = 3; i < PAGE_COUNT; i++) {
        write_page(i, buffer + (i * 4));
    }
    std::cout << cc::cyan << "Writing encrypted bin done." << cc::reset << std::endl;
}

void NFCHandler::write_dynamic_lock_bytes() {
    std::cout << cc::cyan << "Writing dynamic lock bytes..." << cc::reset << std::endl;
    write_page(130, dynamic_lock_bytes);
    std::cout << cc::cyan << "Writing dynamic lock bytes done." << cc::reset << std::endl;
}

void NFCHandler::write_static_lock_bytes() {
    std::cout << cc::cyan << "Writing static lock bytes..." << cc::reset << std::endl;
    write_page(2, static_lock_bytes);
    std::cout << cc::cyan << "Writing static lock bytes done." << cc::reset << std::endl;
}

void NFCHandler::write_page(AMIIBIN page, const AMIIBIN *buffer) {

    // +page http://cpp.indi.frih.net/blog/2014/09/tippet-printing-numeric-values-for-chars-and-AMIIBIN/
    std::cout << cc::cyan << "Writing to "
              << cc::magenta << +page << cc::reset;

    std::cout << " " << cc::yellow << +buffer[0] << " " << +buffer[1]
              << " " << +buffer[2] << " " << +buffer[3] << cc::reset << std::endl;

    AMIIBIN sendData[6] = {WRITE_COMMAND, page, buffer[0], buffer[1], buffer[2], buffer[3]};

    if (!nfc_initiator_transceive_bytes(device, sendData, 6, nullptr, 0, 0)) {
        std::cout << cc::green << "done." << cc::reset << std::endl;
    } else {
        throw amiibo_write_error(nfc_strerror(device));
    }
}
