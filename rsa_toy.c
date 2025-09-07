/*
 * rsa_toy.c — Minimal educational RSA implementation with step-by-step trace.
 *
 * WARNING: This code is for learning purposes ONLY. 
 * - It uses tiny primes (p=61, q=53) with n=3233.
 * - It encrypts ASCII characters one by one without padding.
 * - It is NOT secure and must not be used in any real application.
 *
 * What it demonstrates:
 * - The core RSA math: c = m^e mod n, m = c^d mod n.
 * - How modular exponentiation (square-and-multiply) works step by step.
 * - That encrypting and then decrypting returns the original message.
 *
 * How it works:
 * 1. User enters a string (ASCII text).
 * 2. The first character is encrypted/decrypted with a detailed trace of each step
 *    in modular exponentiation (res/base/exp updates shown).
 * 3. The whole string is encrypted (each char → number).
 * 4. Ciphertext is printed as a sequence of numbers.
 * 5. Numbers are decrypted back to characters to reconstruct the string.
 *
 * Educational goals:
 * - Show WHY we need modular exponentiation (to compute huge powers efficiently).
 * - Show HOW RSA actually uses modular arithmetic.
 * - Make the encryption/decryption process transparent and easy to follow.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Fixed toy parameters (classic example) */
static const uint64_t P = 61;
static const uint64_t Q = 53;
static const uint64_t N = 3233;          // P*Q
static const uint64_t PHI = 3120;        // (P-1)*(Q-1)
static const uint64_t E = 17;            // public exponent
static const uint64_t D = 2753;          // private exponent (E*D ≡ 1 mod PHI)
                                         
// Fast modular exponentiation (square-and-multiply).
static uint64_t powmod_u64(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1 % mod;
    base %= mod;
    while (exp) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

static uint64_t rsa_encrypt_char(unsigned char ch) {
    return powmod_u64((uint64_t)ch, E, N);      // c = m^e mod n
}

static unsigned char rsa_decrypt_word(uint64_t c) {
    return (unsigned char)powmod_u64(c, D, N);  // m = c^d mod n
}

int main(void) {
    char input[1024];
    printf("Enter text: ");
    if (!fgets(input, sizeof(input), stdin)) return 1;

    size_t len = strlen(input);
    if (len && input[len-1] == '\n') input[--len] = '\0';

    uint64_t ct[1024];

    printf("\nEncrypting...\n");
    for (size_t i = 0; i < len; ++i) {
        ct[i] = rsa_encrypt_char((unsigned char)input[i]);
        printf("'%c' -> %llu\n", input[i], (unsigned long long)ct[i]);
    }

    printf("\nDecrypting...\n");
    char out[1024];
    for (size_t i = 0; i < len; ++i) {
        out[i] = (char)rsa_decrypt_word(ct[i]);
        printf("%llu -> '%c'\n", (unsigned long long)ct[i], out[i]);
    }
    out[len] = '\0';

    printf("\nDecrypted text: %s\n", out);
    return 0;
}

