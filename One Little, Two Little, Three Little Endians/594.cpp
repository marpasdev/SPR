#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

std::array<unsigned char, 4> convertToBytes(int num) {
    std::array<unsigned char, 4> bytes;
    for (size_t i = 0; i < bytes.size(); ++i) {
        bytes[i] = static_cast<unsigned char>((num & (0x000000ff << (i * 8))) >> (i * 8));
    }
    return bytes;
}

// converts to opposite endianity
int convert(int num) {
    std::array<unsigned char, 4> bytes = convertToBytes(num);
    std::reverse(bytes.begin(), bytes.end());

    int converted = 0x00000000;
    for (size_t i = 0; i < bytes.size(); ++i) {
        converted |= bytes[i] << (i * 8);
    }
    return converted;
}

// One Little, Two Little, Three Little Endians
int main() {
    std::vector<int> input;

    int num = 0;
    while (std::cin >> num) {
        input.push_back(num);
    }

    for (int in : input) {
        int converted = convert(in);
        std::cout << in << " converts to " << converted << '\n';
    }

    return 0;
}