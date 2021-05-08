#include "amiibo_static.h"

class Amiitool {
public:
    explicit Amiitool(const char *key_file_path);

    void load_amiibo_data(uint8_t amiibo);

    void load_amiibo_data(QString file_path);

    void load_amiibo_data(std::string file_path);

    static void print_hex(const uint8_t *pbtData, size_t szBytes);

private:
    nfc3d_amiibo_keys amiibo_keys = {};
    uint8_t original_amiibo[AMIIBO_SIZE] = {};
    uint8_t modified_amiibo[NFC3D_AMIIBO_SIZE] = {};


};
