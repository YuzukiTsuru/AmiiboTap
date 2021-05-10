//
// Created by Ghost Gloomy on 2021/5/10.
//

#include "binarybuffer.h"

#include "exception.hpp"

binarybuffer::binarybuffer(const std::string &file) {
    amiibo.open(file, std::ios::binary);
    if (!amiibo.is_open()) {
        throw file_open_error(file);
    }
    buff = std::vector<uint8_t>(std::istreambuf_iterator<char>(amiibo), std::istreambuf_iterator<char>());
    amiibo.close();
}


std::size_t binarybuffer::get_size() const {
    return buff.size();
}

uint8_t *binarybuffer::get_data() {
    return buff.data();
}