/*
 * This file is part of the SIM900 Arduino Shield library.
 * Copyright (c) 2023 Nathanne Isip
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <Arduino.h>
#include "microlzw.h"

typedef struct {
    int prefix;
    char character;
} mlzw_entry;

void mlzw_compress(char *input, int *compressed, size_t *comp_size, int dict_size) {
    mlzw_entry dictionary[dict_size];
    int next_code = 256, current_code = input[0], index = 1;

    while(input[index] != '\0') {
        uint8_t current_ch = input[index];
        int code = (current_code << 8) + current_ch;

        int i = 0;
        for(; i < next_code; ++i)
            if(dictionary[i].prefix == code)
                break;

        if(i == next_code) {
            compressed[(*comp_size)++] = current_code;
            if(next_code < dict_size) {
                dictionary[next_code].prefix = code;
                dictionary[next_code].character = current_ch;

                next_code++;
            }

            current_code = current_ch;
        }
        else current_code = i;
        index++;
    }

    compressed[(*comp_size)++] = current_code;
}

void mlzw_decompress(int *compressed, size_t comp_size, char *output, int dict_size) {
    mlzw_entry dictionary[dict_size];
    int next_code = 256, idx = 0,
        current_code = compressed[idx++],
        output_idx = 1;

    output[0] = current_code;
    while(idx < comp_size) {
        int code = compressed[idx++];

        if(code < next_code) {
            int entry_idx = code;

            while(entry_idx >= 256) {
                output[output_idx++] = dictionary[entry_idx].character;
                entry_idx = dictionary[entry_idx].prefix;
            }

            output[output_idx++] = entry_idx;
            if (next_code < dict_size) {
                dictionary[next_code].prefix = current_code;
                dictionary[next_code].character = entry_idx;

                next_code++;
            }

            current_code = code;
        }
        else {
            int entry_idx = current_code;
            while(entry_idx >= 256) {
                output[output_idx++] = dictionary[entry_idx].character;
                entry_idx = dictionary[entry_idx].prefix;
            }

            output[output_idx++] = entry_idx;
            if(next_code < dict_size) {
                dictionary[next_code].prefix = current_code;
                dictionary[next_code].character = entry_idx;

                next_code++;
            }

            current_code = code;
        }
    }

    int entry_idx = current_code;
    while(entry_idx >= 256) {
        output[output_idx++] = dictionary[entry_idx].character;
        entry_idx = dictionary[entry_idx].prefix;
    }

    output[output_idx++] = entry_idx;
    output[output_idx] = '\0';
}