#pragma once
#include <vector>
#include <random>

std::vector<uint32_t> generate_random_vector(size_t n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<uint32_t> values(n);
    std::uniform_int_distribution<> dis(uint32_t(0));
    std::generate(values.begin(), values.end(), [&](){ return dis(gen); });
    return values;
}

void make_strict(std::vector<uint32_t> &vec){
    for (size_t i = 1; i < vec.size(); ++i)
    {
        vec[i] += vec[i-1];
    }
}