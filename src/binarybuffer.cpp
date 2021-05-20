//
// Created by Ghost Gloomy on 2021/5/10.
//

#include "binarybuffer.h"

#include "exception.h"

binarybuffer::binarybuffer(const std::string &file) {
    amiibo.open(file, std::ios::in | std::ios::binary);
    if (!amiibo.is_open()) {
        throw file_open_error(file);
    }
    buff = std::vector<AMIIBIN>(std::istreambuf_iterator<char>(amiibo), std::istreambuf_iterator<char>());
    amiibo.close();
}


std::size_t binarybuffer::get_size() const {
    return buff.size();
}

AMIIBIN *binarybuffer::get_data() {
    return buff.data();
}