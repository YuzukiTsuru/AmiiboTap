#ifndef AMIIBOTAP_AMIITOOL_H
#define AMIIBOTAP_AMIITOOL_H

#include <iostream>

#ifdef __cplusplus
extern "C" {
#include <nfc3d/amiibo.h>
}
#endif

#include "amiibo_static.h"

class Amiitool {
public:
    explicit Amiitool(const char *key_file_path);

    void amiibo_encryption(AMIIBIN *amiibo);

    void amiibo_decryption(AMIIBIN *amiibo);

    AMIIBIN *get_amiibo_data();

    /*
     * Read Amiibo bin file to AMIIBIN array.
     * @IN: const char *file_path
     * @RET: void
     * @SELF: original_amiibo
     */
    static AMIIBIN *load_amiibo_data(const char *file_path);

private:
    nfc3d_amiibo_keys amiibo_keys = {};
    AMIIBIN *modified_amiibo = new AMIIBIN[NFC3D_AMIIBO_SIZE];
};

#endif //AMIIBOTAP_AMIITOOL_H