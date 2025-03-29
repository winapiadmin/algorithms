//-funroll-loops -ffast-math -O3 -march=native -mtune=native -pipe -flto -fwhole-program -fwhole-file -fomit-frame-pointer -faggressive-loop-optimizations
#include <vector>
#include <iostream>
#include <iomanip>
#include <array>
#include <cstring>
#include <cstdint>
#include <cstdio>
using namespace std;

#define ROTRIGHT(word, bits) (((word) >> (bits)) | ((word) << (32 - (bits))))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define EP0(x) (ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22))
#define EP1(x) (ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25))
#define SIG0(x) (ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ ((x) >> 3))
#define SIG1(x) (ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ ((x) >> 10))
static const uint32_t k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

class SHA256 {
public:
    static string hash(const string &input) {
        uint8_t digest[32];
        computeHash(digest, reinterpret_cast<const uint8_t*>(input.c_str()), input.size());

        char output[65]={0};
        for (int i = 0; i < 32; i++)
            snprintf(output + i * 2, 3, "%02x", digest[i]);

        return string(output);
    }

private:
    static void transform(uint32_t state[8], const uint8_t data[]);
    static void computeHash(uint8_t *hash, const uint8_t *input, size_t len);
};

void SHA256::transform(uint32_t state[8], const uint8_t data[]) {
    uint32_t a, b, c, d, e, f, g, h, t1, t2, m[64];
    for (int i = 0, j = 0; i < 16; i++, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) | (data[j + 2] << 8) | (data[j + 3]);
    for (int i = 16; i < 64; i++)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];
    
    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];
    
    for (int i = 0; i < 64; i++) {
        t1 = h + EP1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h = g; g = f; f = e; e = d + t1;
        d = c; c = b; b = a; a = t1 + t2;
    }
    
    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

void SHA256::computeHash(uint8_t *hash, const uint8_t *input, size_t len) {
    uint32_t state[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 
                         0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    // Ensure padding buffer is large enough
    size_t block_size = 64;
    size_t padded_size = ((len + 9 + block_size - 1) / block_size) * block_size;
    uint8_t data[padded_size];
	memset(data,0,padded_size);
    // Safe memory copy
    size_t copy_len = std::min(len, padded_size);
    memcpy(data, input, copy_len);

    // Padding
    data[len] = 0x80;

    // Append length in last 8 bytes
    uint64_t bit_len = len * 8;
    for (int i = 0; i < 8; i++) {
        data[padded_size - 8 + i] = (bit_len >> (56 - i * 8)) & 0xFF;
    }

    // Process each 512-bit block
    for (size_t i = 0; i < padded_size; i += 64) {
        transform(state, &data[i]);
    }

    // Convert state to output hash
    for (int i = 0; i < 8; i++) {
        hash[i * 4 + 0] = (state[i] >> 24) & 0xff;
        hash[i * 4 + 1] = (state[i] >> 16) & 0xff;
        hash[i * 4 + 2] = (state[i] >> 8) & 0xff;
        hash[i * 4 + 3] = (state[i]) & 0xff;
    }
}

int main(int argc, char **argv) {
    if (argc == 1) printf("%s <inpstring>\n", argv[0]);
    else printf("%s: %s\n", argv[1], SHA256::hash(argv[1]).c_str());
    return 0;
}
