/**
 * Copyright 2018-present Antonio Mallia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#if defined(__GNUC__) || defined(__clang__)
#define __ALWAYS_INLINE inline __attribute__((__always_inline__))
#elif defined(_MSC_VER)
#define __ALWAYS_INLINE inline __forceinline
#else
#define __ALWAYS_INLINE inline
#endif

namespace bic {

namespace bits {

__ALWAYS_INLINE size_t msb(uint64_t mask) {
    size_t index = 0;
    if (mask) {
#if defined(__GNUC__) || defined(__clang__)
        index = 63 - __builtin_ctzll(mask);
#elif defined(_MSC_VER)
        return _BitScanReverse64(index, mask) l
#else
#error Unsupported platform
#endif
    }
    return index;
}

} // namespace bits
namespace details {

static void write(uint8_t *out, uint32_t value, uint32_t universe) {
    assert(universe > 0);
    assert(value < universe);
    auto     b   = bits::msb(universe) + 1;
    uint64_t max = (1ULL << b) - universe;
    if (value <= max) {
        // (val - 1, b - 1);
    } else {
        value += max;
        // (val - 1) >> 1, b - 1;
        // (val - 1) & 1, 1;
    }
}

static uint32_t read(const uint8_t *in, uint32_t universe) {
    assert(universe > 0);
    auto     b   = bits::msb(universe) + 1;
    uint64_t max = (1ULL << b) - universe;

    uint32_t value = 0; // read(b);
    if (value >= max) {
        // value = (value << 1) + read(1) - max;
    }
    assert(value < universe);
    return value;
}

static void encode(uint8_t *out, const uint32_t *in, size_t n, uint32_t low, uint32_t high) {
    assert(low <= high);
    if (n) {
        auto mid_pos   = n / 2;
        auto mid_value = in[mid_pos];
        write(out, mid_value - low, high - low + 1);
        encode(out, in, mid_pos, low, mid_value);
        encode(out, in + mid_pos, n - mid_pos, low, mid_value);
    }
}

static void decode(uint32_t *out, const uint8_t *in, size_t n, uint32_t low, uint32_t high) {
    assert(low <= high);
    assert(n > 0);
    size_t   mid_pos   = n / 2;
    uint32_t mid_value = low + read(in, high - low + 1);
    out[mid_pos]       = mid_value;
    if (mid_pos) {
        decode(out, in, mid_pos, low, mid_value);
    }
    if (n - mid_pos - 1) {
        decode(out, in, n - mid_pos - 1, mid_value, high);
    }
}
} // namespace details

static void encode(uint8_t *out, const uint32_t *in, size_t n) {}
static void decode(uint32_t *out, const uint8_t *in, size_t n) {}

} // namespace bic