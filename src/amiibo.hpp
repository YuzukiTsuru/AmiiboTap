#ifndef AMIIBOTAP_AMIIBO_HPP
#define AMIIBOTAP_AMIIBO_HPP

#include <iostream>
#include <cstdint>

#include "amiitool.hpp"
#include "amiibo_static.hpp"

class Amiibo : public Amiitool {
public:
    Amiibo(const char *keyFilePath, const char *file_path);

    ~Amiibo();

    void set_UUID(const uint8_t *uuid);

private:
    uint8_t *buffer = nullptr;

    void replace_with_UUID(const uint8_t *uuid);

    void replace_password(const uint8_t *uuid);

    void set_defaults(const uint8_t *uuid);
};

#endif //AMIIBOTAP_AMIIBO_HPP