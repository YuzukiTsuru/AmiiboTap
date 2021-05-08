#include <iostream>

#ifdef __cplusplus
extern "C" {
#include <nfc3d/amiibo.h>
}
#endif

#include "amiibo_static.hpp"

class Amiitool {
public:
    explicit Amiitool(const char *key_file_path);

    ~Amiitool();

    /*
     * Read Amiibo bin file to uint8_t array.
     * @IN: const char *file_path
     * @RET: void
     * @SELF: original_amiibo
     */
    void load_amiibo_data(const char *file_path);

    void amiibo_encryption();

    void amiibo_decryption();

    uint8_t *get_modified_amiibo_data();

    static void print_hex(const uint8_t *pbt_data, size_t sz_bytes);

private:
    nfc3d_amiibo_keys amiibo_keys = {};
    uint8_t *original_amiibo = new uint8_t[AMIIBO_SIZE];
    uint8_t *modified_amiibo = new uint8_t[NFC3D_AMIIBO_SIZE];

    template<class T>
    int arr_length(T &arr) {
        return sizeof(arr) / sizeof(arr[0]);
    }
};
