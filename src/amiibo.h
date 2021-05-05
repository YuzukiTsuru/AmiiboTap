#ifndef _AMIIBO_H_
#define _AMIIBO_H_

#define AMIIBO_SIZE 540

#include <cstdlib>
#include <cstdint>

class Amiibo {
public:
  explicit Amiibo(const char *filePath);

    [[maybe_unused]] void setUUID(const uint8_t uuid[]);

  uint8_t encryptedBuffer[AMIIBO_SIZE]{};

private:
  uint8_t buffer[AMIIBO_SIZE]{};

  static void readFileIntoBuffer(const char *filePath, uint8_t *buffer, size_t size);

  void replaceWithUUID(const uint8_t uuid[]);
  void replacePassword(const uint8_t uuid[]);
  void setDefaults(const uint8_t uuid[]);
};

#endif //_AMIIBO_H_