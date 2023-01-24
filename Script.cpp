#include <iostream>
#include <vector>
#include <bitset>

std::vector<int> encode(const std::vector<int>& data) {
    int r = 0;
    while ((1 << r) < (data.size() + r + 1)) {
        ++r;
    }

    std::vector<int> encoded(data.size() + r);
    for (int i = 0, k = 0; i < encoded.size(); ++i) {
        if ((i + 1) & (i + 1) - 1) {
            encoded[i] = data[k++];
        }
    }

    for (int i = 0; i < r; ++i) {
        int parity = 0;
        for (int j = 0; j < encoded.size(); ++j) {
            if (j & (1 << i)) {
                parity ^= encoded[j];
            }
        }
        encoded[(1 << i) - 1] = parity;
    }

    return encoded;
}

std::vector<int> decode(const std::vector<int>& encoded) {
    std::vector<int> errors;
    for (int i = 0; i < encoded.size(); ++i) {
        if ((i + 1) & (i + 1) - 1) {
            continue;
        }
        int parity = 0;
        for (int j = 0; j < encoded.size(); ++j) {
            if (j & (1 << (i + 1))) {
                parity ^= encoded[j];
            }
        }
        if (parity) {
            errors.push_back(i);
        }
    }

    if (errors.empty()) {
        return encoded;
    }

    std::vector<int> decoded(encoded.size() - errors.size());
    for (int i = 0, k = 0; i < encoded.size(); ++i) {
        if ((i + 1) & (i + 1) - 1) {
            decoded[k++] = encoded[i];
        }
    }

    if (errors.size() > 1 || errors[0] >= decoded.size()) {
        std::cout << "Unable to correct errors" << std::endl;
        return {};
    }

    int flipBit = errors[0];
    decoded[flipBit] ^= 1;

    return decoded;
}

int main() {
    std::vector<int> data = { 1, 0, 0, 1 };
    std::vector<int> encoded = encode(data);
    std::cout << "Encoded data: ";
    for (const auto& bit : encoded) {
        std::cout << bit;
    }
    std::cout << std::endl;

    encoded[3] ^= 1; // introduce an error
    std::vector<int> decoded = decode(encoded);
    if (decoded.empty()) {
        return 0;
    }
    std::cout << "Decoded data: ";
    for (const auto& bit : dec
