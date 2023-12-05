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
#include <microlzw.h>

void setup() {
    Serial.begin(9600);

    const char *input = "Wubba Lubba dub-dub";
    // Declare compression dictionary size
    // and buffer size.
    const int dict_size = 4096, buffer_size = 256;

    int compressed[dict_size];
    int comp_size = 0;

    // Compress the input string via LZW algorithm,
    // then pass the output to th `compressed`
    // variable.
    mlzw_compress(input, compressed, &comp_size, dict_size);

    Serial.print("Compressed: ");
    // Iterate to print all the compression output
    // integer values.
    for(uint8_t i = 0; i < comp_size; ++i) {
        Serial.print(compressed[i]);
        Serial.print(" ");
    }
    Serial.println();

    // Decompress the compressed output
    // then pass the decompressed string
    // to the variable `decompressed`.
    char decompressed[buffer_size];
    mlzw_decompress(compressed, comp_size, decompressed, dict_size);

    Serial.print("Decompressed: ");
    // Finally, print the decompressed string to the terminal.
    Serial.println(decompressed);
}

void loop() {}