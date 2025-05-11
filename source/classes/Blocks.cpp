#include "../../include/classes/Blocks.h"
#include <chrono>

Blocks::Blocks(std::string data, unsigned char *key_data) {
    int lasting_zeros = (16 - data.size() % 16) % 16;
    while(lasting_zeros--) data += '\x00';
    for(int i=0;i<data.size();i+=16) {
        data_blocks.push_back(Block(
            data.substr(i,16)        
        ));
    }

    key_block = KeyBlock(key_data);

    auto start = std::chrono::high_resolution_clock::now();

    key_block.expand_round_keys();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "***Time to Key Expand: "<< duration.count() << " us" << std::endl;

}

void Blocks::encrypt() {

    for(std::vector<Block>::iterator data_block = data_blocks.begin();
        data_block != data_blocks.end();
        data_block++) {

        data_block->add_round_key(key_block.get_round_key(0));

        for(int i=1;i<14;i++) {
            data_block->sub_bytes();
            data_block->shift_rows();
            data_block->mix_columns();
            data_block->add_round_key(key_block.get_round_key(i));
        }

        data_block->sub_bytes();
        data_block->shift_rows();
        data_block->add_round_key(key_block.get_round_key(14));
    }

}

void Blocks::decrypt() {

    for(std::vector<Block>::iterator data_block = data_blocks.begin();
        data_block != data_blocks.end();
        data_block++) {

        data_block->add_round_key(key_block.get_round_key(14));


        for(int i=1;i<14;i++) {
            data_block->inv_shift_rows();
            data_block->inv_sub_bytes();
            data_block->add_round_key(key_block.get_round_key(14-i));
            data_block->inv_mix_columns();
        }

        data_block->inv_shift_rows();
        data_block->inv_sub_bytes();
        data_block->add_round_key(key_block.get_round_key(0));
    }
}

std::ostream &operator<<(std::ostream &oss, Blocks blocks) {
    for(std::vector<Block>::iterator data_block = blocks.data_blocks.begin();
        data_block != blocks.data_blocks.end();
        data_block++) {
            oss << *data_block;
        }
        
        return oss;
}