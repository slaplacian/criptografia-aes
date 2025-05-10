#include "include/classes/Blocks.h"
#include <chrono>

int main(int argc, char **argv) {

    unsigned char key[32] = {
        0x00,0x01,0x02,0x03,
        0x04,0x05,0x06,0x07,
        0x08,0x09,0x0A,0x0B,
        0x0C,0x0D,0x0E,0x0F,
        0x10,0x11,0x12,0x13,
        0x14,0x15,0x16,0x17,
        0x18,0x19,0x1A,0x1B,
        0x1C,0x1D,0x1E,0x1F
    };

    std::string message = get_message_from_file(argv[1]);

    Blocks blocks(message,key);

    std::cout << "====    Plain Text     ====" << std::endl;
    
    std::cout << blocks << std::endl;

    std::cout << "==== End of Plain Text ====" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    blocks.encrypt();
    
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "***Time to Encrypt: " << duration.count() << " ms" << std::endl;
    
    std::cout << "===    Cipher Text     ===" << std::endl;
    
    std::cout << blocks << std::endl;

    std::cout << "=== End of Cipher Text ===" << std::endl;

    start = std::chrono::high_resolution_clock::now();

    blocks.decrypt();
    
    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "***Time to Decrypt: " << duration.count() << " ms" << std::endl;

    std::cout << "====    Plain Text     ==== (Again)" << std::endl;
    
    std::cout << blocks << std::endl;

    std::cout << "==== End of Plain Text ==== (Again)" << std::endl;

    return 0;
}