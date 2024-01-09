#ifndef NYT_RND_hpp
#define NYT_RND_hpp

#include <stdint.h>

uint16_t getHash(uint16_t s) {
  // https://en.wikipedia.org/wiki/Jenkins_hash_function
  uint32_t hash = s + 1;
  hash += hash << 10;
  hash ^= hash >> 6;
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;

  return hash & 0xFFFF;
}

uint16_t getRandomNumber(uint16_t s, uint16_t b) {
  return getHash(s) % b;
}

#endif
