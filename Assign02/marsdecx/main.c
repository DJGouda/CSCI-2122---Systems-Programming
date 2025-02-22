#include <stdio.h>
#include <stdint.h>

// Function to extract bits from a byte array
uint64_t extract_bits(const uint8_t *bytes, int bit_position, int num_bits) {
    uint64_t value = 0;
    for (int i = 0; i < num_bits; i++) {
        int byte_index = (bit_position + i) / 8;
        int bit_index = 7 - ((bit_position + i) % 8); // Bits are packed MSB first
        value = (value << 1) | ((bytes[byte_index] >> bit_index) & 0x01);
    }
    return value;
}

void process_line(int line_number) {
    int B;
    if (scanf("%d", &B) != 1) return;

    if (B == 0) return; // No integer to unpack

    uint8_t bytes[100]; // Allow for up to 100 bytes per line
    for (int i = 0; i < B; i++) {
        if (scanf("%hhx", &bytes[i]) != 1) return;
    }

    int total_bits = B * 8; // Total bits in the bitstream
    int bit_position = 0;   // Current bit position in the bitstream
    int integer_count = 1;  // Counter for the number of integers unpacked

    while (bit_position + 5 < total_bits) { // Ensure at least 6 bits remain
        // Extract L (first 5 bits from current position)
        int L = extract_bits(bytes, bit_position, 5);
        bit_position += 5; // Move bit position forward by 5 bits

        if (L == 0) break; // Stop if L is 0

        // Ensure there are enough bits left for the L-bit integer
        if (bit_position + L > total_bits) break;

        // Extract L-bit signed integer
        uint64_t extracted_value = extract_bits(bytes, bit_position, L);

        // Proper Sign Extension
        if (extracted_value & (1ULL << (L - 1))) { // Check if the sign bit is set
            extracted_value |= (-1ULL << L); // Extend the sign properly
        }

        // Print the extracted value
        printf("Line %d, integer %d: %lld\n", line_number, integer_count, (long long)extracted_value);

        // Move bit position forward by L bits
        bit_position += L;
        integer_count++; // Increment integer counter
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 1;

    for (int i = 1; i <= N; i++) {
        process_line(i);
    }

    return 0;
}