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

class amiibo_write_error : public std::runtime_error {
public:
    explicit amiibo_write_error(const std::string &what) : std::runtime_error(
            "Write Amiibo to TAG error: " + what + ", this TAG may aleady locked! ") {};
};

class nfc_not_found : public std::runtime_error {
public:
    explicit nfc_not_found() : std::runtime_error("Could not open the nfc devices") {};
};

class nfc_init_fault : public std::runtime_error {
public:
    explicit nfc_init_fault() : std::runtime_error("Could not init NFC library (malloc)") {};
};

#endif //AMIIBOTAP_EXCEPTION_H
