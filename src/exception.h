//
// Created by Ghost Gloomy on 2021/5/10.
//

#ifndef AMIIBOTAP_EXCEPTION_H
#define AMIIBOTAP_EXCEPTION_H

#include <stdexcept>
#include <string>

class file_open_error : public std::runtime_error {
public:
    explicit file_open_error(const std::string &what) : std::runtime_error("Fail to open file: " + what + ".") {};
};

class amiibo_file_size_error : public std::runtime_error {
public:
    explicit amiibo_file_size_error(const std::string &what) : std::runtime_error(
            "Read Amiibo bin file: " + what + " fail, wrong size.") {};
};

#endif //AMIIBOTAP_EXCEPTION_H
