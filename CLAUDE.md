# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Development Workflow

**Building the Project:**
The core library and associated components can be built using `make`. While a single universal 'build' target is not explicitly defined, running commands like `make test` ensures necessary object files and libraries (`libarcfour.exp`) are compiled for testing.

**Linting Codebase:**
No specific linter command or configuration file was found in the repository to enforce linting.

**Running Tests (Main Suite):**
The primary test suite is executed via:
```bash
make test
```
This command runs `test_nist_arcfour`, which compiles and executes a comprehensive set of tests for the RC4 implementation against NIST standards.

**Running Isolated Test Cases:**
No explicit target exists in the Makefile to run only an isolated unit test case; the main suite provides the full coverage check.

## Architecture

The project structure centers around implementing the RC4 encryption algorithm, primarily contained within `arcfour.c` and its public interface defined by `arcfour.h`.

*   **Core Library:** The fundamental logic resides in the files related to `arcfour.*`, handling the cryptographic implementation.
*   **Testing Module:** A dedicated testing framework is implemented in `test_nist_arcfour.c`. This module utilizes the core library and compiles against it to verify compliance with industry standards (NIST).
*   **Examples/Usage:** The `example.c` file provides a working demonstration of how the RC4 library can be integrated into a larger application.

## Development Rules and Notes

This code is considered **experimental**. Developers should use this project at their own risk, as noted in the `README.md`. It was created primarily to explore building shared libraries on both MacOS and Linux platforms, making it suitable for educational purposes rather than production use.