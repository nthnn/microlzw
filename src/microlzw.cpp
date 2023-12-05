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