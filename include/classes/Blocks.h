#ifndef BLOCKS_H

#define BLOCKS_H

#include "Block.h"
#include "KeyBlock.h"
#include <vector>



class Blocks {
    private:
        std::vector<Block> data_blocks;
        KeyBlock key_block;

    public:
        Blocks(std::string data, unsigned char *key_data);
        void encrypt();
        void decrypt();

        friend std::ostream &operator<<(std::ostream &oss, Blocks blocks);
};

#endif /* BLOCKS_H */