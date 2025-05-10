#include "../../include/classes/KeyBlock.h"

KeyBlock::KeyBlock() {}

KeyBlock::KeyBlock(unsigned char *block) {
    for(int i=0;i<8;i++) {
        for(int j=0;j<4;j++) {
            key_block[j][i] = block[j+4*i];
        }
    }
}

KeyBlock::KeyBlock(std::string key_data) {
    if(key_data.size() != 32) {
        throw std::range_error("Key Block must have 32 bytes.");
    }

    for(int i=0;i<8;i++) {
        for(int j=0;j<4;j++) {
            key_block[i][j] = (unsigned char) key_data[j+4*i];
        }
    }
}

std::array<unsigned char, 60> &KeyBlock::operator[](int index) {
    return key_block[index];
}

void KeyBlock::rot_word(std::array<unsigned char,4> &temp) {
    std::swap(temp[0],temp[3]);
    std::swap(temp[0],temp[2]);
    std::swap(temp[0],temp[1]);
}

void KeyBlock::sub_bytes(std::array<unsigned char,4> &temp) {
    for(int i=0;i<4;i++) {
        temp[i] = sbox[temp[i]];
    }
}

void KeyBlock::expand_round_keys() {
    std::array<unsigned char,4> temp;

    for(int i=8;i<60;i++) {
        temp = {
            key_block[0][i-1],key_block[1][i-1],key_block[2][i-1],key_block[3][i-1]
        };

        if(i%8==0) {
            rot_word(temp);
            sub_bytes(temp);
            temp[0] ^= rcon[i/8];
        } else if(i%8==4) {
            sub_bytes(temp);
        }

        key_block[0][i] = (temp[0] ^ key_block[0][i-8]);
        key_block[1][i] = (temp[1] ^ key_block[1][i-8]);
        key_block[2][i] = (temp[2] ^ key_block[2][i-8]);
        key_block[3][i] = (temp[3] ^ key_block[3][i-8]);
    }
}

Block KeyBlock::get_round_key(int index) {
    unsigned char round_key[16] = {
        key_block[0][4*index+0],key_block[1][4*index+0],key_block[2][4*index+0],key_block[3][4*index+0],
        key_block[0][4*index+1],key_block[1][4*index+1],key_block[2][4*index+1],key_block[3][4*index+1],
        key_block[0][4*index+2],key_block[1][4*index+2],key_block[2][4*index+2],key_block[3][4*index+2],
        key_block[0][4*index+3],key_block[1][4*index+3],key_block[2][4*index+3],key_block[3][4*index+3]
    };
    
    return Block(round_key);
}
