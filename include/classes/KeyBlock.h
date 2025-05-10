#ifndef KEYBLOCK_H

#define KEYBLOCK_H

#include <array>
#include "Block.h"
#include "../utils.h"

class KeyBlock {
    
    private:
        std::array<std::array<unsigned char, 60>, 4> key_block;

    public:

        KeyBlock();
        KeyBlock(std::string key_data);
        KeyBlock(unsigned char *block);

        std::array<unsigned char, 60> &operator[](int index);
        void rot_word(std::array<unsigned char,4> &temp);
        void sub_bytes(std::array<unsigned char,4> &temp);
        void expand_round_keys();
        Block get_round_key(int index);
};

#endif /* KEYBLOCK_H */