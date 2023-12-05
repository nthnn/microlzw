#ifndef MICROLZW_H
#define MICROLZW_H

void mlzw_compress(
    char *input,
    int *compressed,
    size_t *comp_size,
    int dict_size
);

void mlzw_decompress(
    int *compressed,
    size_t comp_size,
    char *output,
    int dict_size
);

#endif