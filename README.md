# AmiiboTap

[![CMake](https://github.com/YuzukiTsuru/AmiiboTap/actions/workflows/cmake.yml/badge.svg)](https://github.com/YuzukiTsuru/AmiiboTap/actions/workflows/cmake.yml) 

AmiiboTap is a tool for clone amiibo NFC tags using PN532 NFC reader/writer with [libnfc](http://nfc-tools.org/index.php/Libnfc). 

> This project is for learning and testing purposes only, This project is not responsible for any infringement behavior.

## Build from source 

### Linux
1. Clone this repository with submodules:

    ```
    git clone --recurse-submodules https://github.com/YuzukiTsuru/AmiiboTap.git
    ```

2. Install `libnfc-dev`, `cmake`:

    ```
    sudo apt-get update && sudo apt-get install libnfc-dev cmake
    ```

3. Compile sources. 

    ```
    mkdir build
    cd build
    cmake -DENABLE_TESTING=Off -DCMAKE_BUILD_TYPE=Release  ..
    make AmiiboTapCLI
    ```

## Getting the required files
> **We do not provide downloads of related files**
> **Cloning amiibo probably is infringement or illegal.**

After you have followed the above setup, you just need two more files to start making your own amiibo: an amiibo dump, and the key file.

### Amiibo Dump
Amiibo dumps are not hard to get. Amiibo are 540 bytes and usually stored in a `.bin` (binary) file. This application only **assuming you are simply cloning your own legitimate amiibo**, you can use any dumping tool to dump it to a `.bin` file. Otherwise, that's probably copyright infringement or something.

### Key file
This is the file containing Nintendo's key, which they use to encrypt/decrypt data on the amiibo. It is **probably also copyrighted content**. it's a `160` byte `.bin` file.

## Usage

Start the program:
```
./AmiiboTap path-to-key-file path-to-amiibo-file
```

Once you see `Scan TAG`, place and hold your blank NFC tag on the reader/writer. You should then see messages scrolling past with each data page as it begins writing them. ***Do not remove your tag until the write is finished.*** When you see `Finished writing tag`, it is safe to remove your tag and enjoy your new amiibo!

## Common Problems

* Failed to initialize adapter
  ```
  Initializing NFC adapter
  error	libnfc.bus.i2c	Error: wrote only -1 bytes (10 expected).
  ```
  Your device could not find your NFC device. Double check your config file and try again.

* Failed to write a page
  ```
  Failed to write to tag
  Write: RF Transmission Error
  ```
  This means your tag is already locked. The NTAG 21x spec declares locking bits which permanently prevent certain parts of a tag from being written to once they are set. Therefore once the locking bits are set, you cannot rewrite this tag to another amiibo. All amiibo are required to have certain locking bits sets, so you cannot change a tag once you've used it.

    If this happened anywhere other than page 4, it probably means that your device lost connection to the tag. Try again while keeping the tag closer to your device. In most cases such errors will not cause the card to be locked.

## Reference
- http://nfc-tools.org/index.php/Libnfc
- http://nfc-tools.org/index.php/ISO14443A
- https://github.com/Normola/pimiibo
- https://github.com/socram8888/amiitool
