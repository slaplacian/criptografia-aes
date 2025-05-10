#ifndef UTILS_H

#define UTILS_H

#include <string>

extern const unsigned char sbox[256];
extern const unsigned char inv_sbox[256];
extern const unsigned char rcon[11];

unsigned char galois_multiply(unsigned char a, unsigned char b);
std::string get_message_from_file(std::string filename);

#endif /* UTILS_H */