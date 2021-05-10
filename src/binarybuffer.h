//
// Created by Ghost Gloomy on 2021/5/10.
//
#pragma once

#ifndef AMIIBOTAP_BINARYBUFFER_H
#define AMIIBOTAP_BINARYBUFFER_H

#include <iostream>
#include <fstream>
#include <vector>

class binarybuffer {
public:
    explicit binarybuffer(const std::string &file);

    [[nodiscard]] std::size_t get_size() const;

    [[nodiscard]] uint8_t *get_data();

private:
    std::vector<uint8_t> buff;
    std::basic_ifstream<char> amiibo;
};

#endif //AMIIBOTAP_BINARYBUFFER_H
