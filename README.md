# ARC4 Stream Cipher Library

This project implements a demonstration of the RC4 stream cipher algorithm as a shared library for educational purposes on MacOS and Linux. It was created to explore building cross-platform shared libraries.

## ⚠️ SECURITY WARNING (READ BEFORE USE)

**CRITICAL:** The RC4 cipher is cryptographically broken and should **NEVER** be used in any production, commercial, or security-sensitive environment. Its use exposes data to known attacks due to biases in its keystream. This library is strictly for academic study and educational demonstrations only. For real-world cryptography, please use modern standards like AES-256 (GCM mode) or ChaCha20-Poly1305.

## 📚 Usage Guide & Setup

### Prerequisites
*   A C compiler (e.g., GCC on Linux, Clang on macOS).
*   The `make` utility.

### Building the Project
To compile the core library and associated test modules, run:
```bash
make
```

### Running Tests
The main suite validates the implementation against NIST standards:
```bash
make test
```
This command compiles and runs `test_nist_arcfour`, confirming adherence to industry benchmarks.

### Using Examples
To see how the library can be integrated into a larger application, compile and run the example file:
```bash
# Compile (if not already handled by 'make')
# gcc -o example example.c arcfour.o 
./example
```

## Version History

- **0.1 Initial Release:** Implements core RC4 logic. Compiles and passes NIST tests on MacOS Arm and Linux (Ubuntu) x64.

## License

This project is licensed under the [MIT] License - see the LICENSE.md file for details

