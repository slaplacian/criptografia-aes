#include "../../include/classes/Block.h"
#include "../../include/utils.h"
#include <stdexcept>

Block::Block(std::string data) {
    if(data.size() != 16) {
        throw std::range_error("Data Block must have 16 bytes.");
    }

    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            data_block[i][j] = (unsigned char) data[j+4*i];
        }
    }
}

Block::Block(unsigned char *data) {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            data_block[i][j] = data[j+4*i];
        }
    }
}

std::array<unsigned char,4> &Block::operator[](int index) {
    return data_block[index];
}

std::ostream &operator<<(std::ostream &oss, Block &block) {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            if(block.data_block[i][j] != '\x00')
                oss << block.data_block[i][j]; 
        }
    }
    return oss;
}

void Block::sub_bytes() {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            data_block[i][j] = sbox[data_block[i][j]];
        }
    }
}

void Block::inv_sub_bytes() {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            data_block[i][j] = inv_sbox[data_block[i][j]];
        }
    }
}

void Block::shift_rows() {
    std::swap(data_block[3][0],data_block[3][1]);
    std::swap(data_block[3][0],data_block[3][2]);
    std::swap(data_block[3][0],data_block[3][3]);
    
    std::swap(data_block[2][0],data_block[2][2]);
    std::swap(data_block[2][1],data_block[2][3]);
    
    std::swap(data_block[1][0],data_block[1][3]);
    std::swap(data_block[1][0],data_block[1][2]);
    std::swap(data_block[1][0],data_block[1][1]);
}

void Block::inv_shift_rows() {
    std::swap(data_block[1][0],data_block[1][1]);
    std::swap(data_block[1][0],data_block[1][2]);
    std::swap(data_block[1][0],data_block[1][3]);

    std::swap(data_block[2][0],data_block[2][2]);
    std::swap(data_block[2][1],data_block[2][3]);

    std::swap(data_block[3][0],data_block[3][3]);
    std::swap(data_block[3][0],data_block[3][2]);
    std::swap(data_block[3][0],data_block[3][1]);
}

void Block::mix_columns() {
    for(int i=0;i<4;i++) {
        unsigned char s0 = this->mix_columns_line_zero(i);
        unsigned char s1 = this->mix_columns_line_one(i);
        unsigned char s2 = this->mix_columns_line_two(i);
        unsigned char s3 = this->mix_columns_line_three(i);

        data_block[0][i] = s0;
        data_block[1][i] = s1;
        data_block[2][i] = s2;
        data_block[3][i] = s3;
    }
}

void Block::inv_mix_columns() {
    for(int i=0;i<4;i++) {
        unsigned char s0 = this->inv_mix_columns_line_zero(i);
        unsigned char s1 = this->inv_mix_columns_line_one(i);
        unsigned char s2 = this->inv_mix_columns_line_two(i);
        unsigned char s3 = this->inv_mix_columns_line_three(i);

        data_block[0][i] = s0;
        data_block[1][i] = s1;
        data_block[2][i] = s2;
        data_block[3][i] = s3;
    }
}

unsigned char Block::mix_columns_line_zero(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x02,s0)^galois_multiply(0x03,s1)^s2^s3);
}

unsigned char Block::inv_mix_columns_line_zero(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x0E,s0)^galois_multiply(0x0B,s1)^galois_multiply(0x0D,s2)^galois_multiply(0x09,s3));
}

unsigned char Block::mix_columns_line_one(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x02,s1)^galois_multiply(0x03,s2)^s0^s3);
}

unsigned char Block::inv_mix_columns_line_one(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x09,s0)^galois_multiply(0x0E,s1)^galois_multiply(0x0B,s2)^galois_multiply(0x0D,s3));
}

unsigned char Block::mix_columns_line_two(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x02,s2)^galois_multiply(0x03,s3)^s0^s1);
}

unsigned char Block::inv_mix_columns_line_two(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x0D,s0)^galois_multiply(0x09,s1)^galois_multiply(0x0E,s2)^galois_multiply(0x0B,s3));
}

unsigned char Block::mix_columns_line_three(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x02,s3)^galois_multiply(0x03,s0)^s1^s2);
}

unsigned char Block::inv_mix_columns_line_three(int columns_index) {
    unsigned char s0 = data_block[0][columns_index];
    unsigned char s1 = data_block[1][columns_index];
    unsigned char s2 = data_block[2][columns_index];
    unsigned char s3 = data_block[3][columns_index];

    return (galois_multiply(0x0B,s0)^galois_multiply(0x0D,s1)^galois_multiply(0x09,s2)^galois_multiply(0x0E,s3));
}

void Block::add_round_key(Block round_key) {
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            data_block[j][i] ^= round_key[j][i];
        }
    }
}