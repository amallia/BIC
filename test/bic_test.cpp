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
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>

#include "bic/bic.hpp"
#include "util.hpp"

using ::testing::ContainerEq;

TEST(bic, fuzzy) {
    size_t n = 10000;
    std::vector<uint8_t> buf(n);
    std::vector<uint32_t> values = generate_random_vector(n);
    make_strict(values);
    bic::encode(buf.data(), values.data(), n);
    std::vector<uint32_t> decoded_values(n);
    bic::decode(decoded_values.data(), buf.data(), n);
    EXPECT_EQ(decoded_values.size(), values.size());
    EXPECT_THAT(decoded_values, ContainerEq(values));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
