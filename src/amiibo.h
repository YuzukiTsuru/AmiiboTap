#ifndef AMIIBOTAP_AMIIBO_H
#define AMIIBOTAP_AMIIBO_H

#include <iostream>
#include <cstdint>

#include "amiitool.h"
#include "amiibo_static.h"


class Amiibo : public Amiitool {
public:
    Amiibo(const char *keyFilePath, const char *file_path);

    ~Amiibo();

    void set_UUID(const AMIIBIN *uuid);

private:
    AMIIBIN *buffer = nullptr;

    void replace_with_UUID(const AMIIBIN *uuid);

    void replace_password(const AMIIBIN *uuid);

    void set_defaults(const AMIIBIN *uuid);
};

#endif //AMIIBOTAP_AMIIBO_H