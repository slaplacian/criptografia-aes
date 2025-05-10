#ifndef BLOCK_H

#define BLOCK_H

#include <array>
#include <string>
#include <iostream>

class Block {
    private:
        std::array<std::array<unsigned char, 4>, 4> data_block;

    public:
        Block(std::string data);
        Block(unsigned char *data);
        std::array<unsigned char, 4> &operator[](int index);

        friend std::ostream &operator<<(std::ostream &oss, Block &block);

        void sub_bytes();
        void inv_sub_bytes();
        void shift_rows();
        void inv_shift_rows();
        void mix_columns();
        void inv_mix_columns();
        unsigned char mix_columns_line_zero(int columns_index);
        unsigned char inv_mix_columns_line_zero(int columns_index);
        unsigned char mix_columns_line_one(int columns_index);
        unsigned char inv_mix_columns_line_one(int columns_index);
        unsigned char mix_columns_line_two(int columns_index);
        unsigned char inv_mix_columns_line_two(int columns_index);
        unsigned char mix_columns_line_three(int columns_index);
        unsigned char inv_mix_columns_line_three(int columns_index);
        void add_round_key(Block round_key);
};

#endif /* BLOCK_H */