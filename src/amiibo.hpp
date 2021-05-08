#include <iostream>
#include <cstdint>

#include "amiibo_static.hpp"

class Amiibo {
public:
    explicit Amiibo(const char *file_path);

    void set_UUID(const uint8_t *uuid);

    uint8_t encrypted_buffer[AMIIBO_SIZE] = {};

private:
    uint8_t buffer[AMIIBO_SIZE] = {};

    static void read_file_into_buffer(const char *file_path, uint8_t *buffer, size_t size);

    void replace_with_UUID(const uint8_t *uuid);

    void replace_password(const uint8_t *uuid);

    void set_defaults(const uint8_t *uuid);
};
