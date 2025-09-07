# RSA Toy Implementation

⚠️ **WARNING: This project is for learning purposes only.**  
It uses very small primes and does not include padding or any real security measures.  
**Do not use this implementation in practice.**

---

## Overview
This is a minimal RSA implementation written in C to demonstrate the core mathematics of the algorithm:

- Encryption:  
c = m^e mod n

- Decryption:  
m = c^d mod n


where:
- `n = p * q` is the modulus,
- `e` is the public exponent,
- `d` is the private exponent (chosen such that `e*d ≡ 1 (mod φ(n))`),
- `φ(n) = (p-1)*(q-1)` is Euler’s totient function.

---

## How It Works
1. Fixed toy parameters are used:  
 - `p = 61`, `q = 53`  
 - `n = 3233`, `φ(n) = 3120`  
 - `e = 17`, `d = 2753`  

2. The user enters a text string.  
3. Each character (ASCII value) is encrypted individually into a number.  
4. The encrypted numbers are printed.  
5. The numbers are then decrypted back into the original characters.  

The project also demonstrates **fast modular exponentiation (square-and-multiply)**, which makes RSA possible in practice.

