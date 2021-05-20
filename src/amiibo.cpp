#include <iostream>

#include <ColorCout.hpp>

#include "amiibo.h"

Amiibo::Amiibo(const char *keyFilePath, const char *file_path) : Amiitool(keyFilePath) {
    auto data = load_amiibo_data(file_path);
    amiibo_decryption(data);
    buffer = get_amiibo_data();
}

void Amiibo::set_UUID(const uint8_t *uuid) {
    std::cout << cc::cyan << "Updating bin for new UID:" << cc::reset << std::endl;

    // Credit: https://gist.githubusercontent.com/ShoGinn/d27a726296f4370bbff0f9b1a7847b85/raw/aeb425e8b1708e1c61f78c3e861dad03c20ca8ab/Arduino_amiibo_tool.bash
    replace_with_UUID(uuid);
    replace_password(uuid);
    set_defaults(uuid);
    amiibo_encryption(buffer);

    std::cout << cc::cyan << "Finished updating bin" << cc::reset << std::endl;
}

void Amiibo::replace_with_UUID(const uint8_t *uuid) {
    uint8_t bcc[2];

    bcc[0] = 0x88 ^ uuid[0] ^ uuid[1] ^ uuid[2];
    bcc[1] = uuid[3] ^ uuid[4] ^ uuid[5] ^ uuid[6];

    std::cout << cc::cyan << "Replacing UID:" << cc::reset;
    for (auto i :bcc) {
        std::cout << cc::yellow << " " << +i;
    }
    std::cout << cc::reset << std::endl;

    int i = 0;
    for (; i < 3; i++) {
        buffer[UUID_OFFSET + i] = uuid[i];
    }

    buffer[UUID_OFFSET + i++] = bcc[0];

    for (; i < 8; i++) {
        buffer[UUID_OFFSET + i] = uuid[i - 1];
    }
}

void Amiibo::replace_password(const uint8_t *uuid) {
    uint8_t password[PASSWORD_SIZE] = {0, 0, 0, 0};

    std::cout << cc::cyan << "Updating password" << cc::reset;

    password[0] = 0xAA ^ uuid[1] ^ uuid[3];
    password[1] = 0x55 ^ uuid[2] ^ uuid[4];
    password[2] = 0xAA ^ uuid[3] ^ uuid[5];
    password[3] = 0x55 ^ uuid[4] ^ uuid[6];

    // display password
    for (auto i: password) {
        std::cout << cc::yellow << " " << +i;
    }
    std::cout << cc::reset << std::endl;

    for (int i = 0; i < PASSWORD_SIZE; i++) {
        buffer[PASSWORD_OFFSET + i] = password[i];
    }
}

void Amiibo::set_defaults(const uint8_t *uuid) {
    std::cout << cc::cyan << "Writing magic bytes" << cc::reset << std::endl;

    // Same as bcc[1]
    buffer[0] = uuid[3] ^ uuid[4] ^ uuid[5] ^ uuid[6];

    // All of these are magic values
    buffer[536] = 0x80;
    buffer[537] = 0x80;

    buffer[520] = 0;
    buffer[521] = 0;
    buffer[522] = 0;

    buffer[2] = 0;
    buffer[3] = 0;
}

Amiibo::~Amiibo() {
    delete buffer;
}
