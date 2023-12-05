# microlzw

![Arduino CI](https://github.com/nthnn/microlzw/actions/workflows/arduino_ci.yml/badge.svg) ![Arduino Lint](https://github.com/nthnn/microlzw/actions/workflows/arduino_lint.yml/badge.svg) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/nthnn/microlzw/blob/main/LICENSE)

**microlzw** is a lightweight and embeddable Micro Lempel-Ziv-Welch (MLZW) compression library designed specifically for Arduino projects. It provides efficient string compression and decompression functionalities, catering to scenarios where memory and storage resources are limited.

- **Memory-Friendly:** Designed to work within the constraints of Arduino projects, ensuring efficient use of memory resources.
- **Easy Integration:** Simple and straightforward API for easy integration into your Arduino projects.
- **Comprehensive Documentation:** The header file includes detailed comments to guide developers in using the library effectively.

## Usage

See the easy to follow full example usage [here](examples/full_example/full_example.ino).

## API Documentation

```c
void mlzw_compress(
    char *input,
    int *compressed,
    size_t *comp_size,
    int dict_size
);
```

Compresses a string using the Micro Lempel-Ziv-Welch algorithm.

**Description:**

This function takes an input string and compresses it using the Micro Lempel-Ziv-Welch (MLZW) algorithm. The compressed output, compressed size, and dictionary size are returned through the parameters.

**Parameters:**

- `input` - The input string to be compressed.
- `compressed` - A pointer to an array that will store the compressed data.
- `comp_size` - A pointer to a variable that will store the size of the compressed data.
- `dict_size` - The size of the dictionary to be used in the compression.

---

```c
void mlzw_decompress(
    int *compressed,
    size_t comp_size,
    char *output,
    int dict_size
);
```

Decompresses a string that was compressed using Micro Lempel-Ziv-Welch algorithm.

**Description:**

This function takes a compressed input, decompresses it using the Micro Lempel-Ziv-Welch (MLZW) algorithm, and stores the decompressed output in the provided output buffer.

**Parameters:**

- `compressed` - A pointer to an array containing the compressed data.
- `comp_size` - The size of the compressed data.
- `output` - A pointer to an array that will store the decompressed output.
- `dict_size` - The size of the dictionary used in the compression.

## License

Copyright 2023 - Nathanne Isip

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.