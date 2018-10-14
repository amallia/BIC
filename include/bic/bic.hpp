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

namespace bic {

class bic {

    /*
     * You are responsible for allocating the memory.
     */
    static void encode(uint32_t const *in, size_t n, std::vector<uint8_t> &out);

    /*
     * You are responsible for allocating the memory.
     */
    static const uint8_t *decode(uint8_t const *in, uint32_t *out, size_t n);
};

} // namespace bic