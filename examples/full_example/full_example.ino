#include <microlzw.h>

void setup() {
    Serial.begin(9600);

    const char *input = "Wubba Lubba dub-dub";
    const int dict_size = 4096, buffer_size = 256;

    int compressed[dict_size];
    int comp_size = 0;
    mlzw_compress(input, compressed, &comp_size, dict_size);

    Serial.print("Compressed: ");
    for(uint8_t i = 0; i < comp_size; ++i) {
        Serial.print(compressed[i]);
        Serial.print(" ");
    }
    Serial.println();

    char decompressed[buffer_size];
    mlzw_decompress(compressed, comp_size, decompressed, dict_size);

    Serial.print("Decompressed: ");
    Serial.println(decompressed);
}

void loop() {}