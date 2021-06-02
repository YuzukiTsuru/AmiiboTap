//
// Created by Ghost Gloomy on 2021/5/10.
//
#pragma once

#ifndef AMIIBOTAP_BINARYBUFFER_H
#define AMIIBOTAP_BINARYBUFFER_H

#include <iostream>
#include <fstream>
#include <vector>

#include "amiibo_static.h"

class binarybuffer {
public:
    explicit binarybuffer(const std::string &file);

    [[nodiscard]] std::size_t get_size() const;

    [[nodiscard]] AMIIBIN *get_data();

private:
    std::vector<AMIIBIN> buff;
    std::basic_ifstream<char> amiibo;
};

#endif //AMIIBOTAP_BINARYBUFFER_H
