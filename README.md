# Simple Compiler

A basic compiler implementation in C that demonstrates the fundamental concepts of compilation:
1. Lexical Analysis (Scanner/Tokenizer)
2. Syntax Analysis (Parser)
3. Semantic Analysis
4. Code Generation

## Building
Requires:
- C compiler (gcc/clang)
- Make

## Project Structure
- `src/lexer.c` - Lexical analyzer implementation
- `src/lexer.h` - Lexical analyzer header
- `src/parser.c` - Parser implementation
- `src/parser.h` - Parser header
- `src/main.c` - Main compiler driver

## Usage
```bash
make
./compiler <input_file>
```
