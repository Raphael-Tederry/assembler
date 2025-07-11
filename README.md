# Final Project – System Programming Lab (MMN14)

**Course:** 20465 – Spring 2025, Open University of Israel  
**Student Name:** [Your Full Name]  
**ID:** [Your Student ID]

---

## 🔧 Project Overview

This project implements a **two-pass assembler** for a simplified assembly language, as part of the course "System Programming Lab." The assembler will process `.as` files (assembly source files), and convert them into machine code output in `.ob`, `.ent`, and `.ext` files.

---

## 📌 Key Goals

- Develop a working assembler in **ANSI C (C90 standard)** compatible with a basic Linux environment
- Understand the core concepts of parsing, symbol table management, and binary encoding
- Use only standard libraries and avoid any modern C features or external tools

---

## 🧠 Planned Project Structure

| Module | Description |
|--------|-------------|
| `main()` | Coordinates the process: preprocessing, first pass, second pass |
| `preproc.c/.h` | Macro expansion before actual parsing |
| `first_pass.c/.h` | Parses lines, builds symbol and label tables, validates input |
| `second_pass.c/.h` | Resolves symbols, generates machine code, writes output |
| `code_conversion.c/.h` | Converts instructions and arguments into binary/base64 |
| `table.c/.h` | Manages symbol tables and label data |
| `util.c/.h` | Utility functions: memory handling, string processing, error management |
| `Errors.c/.h` | Centralized error handling and messages |

---

## 💻 Output Files

- **`.ob`** – Base64 encoded object file
- **`.ent`** – Table of entry labels  
- **`.ext`** – Table of external references

---

## 📎 Development Constraints

**For Your C Code:**
- Must compile using `gcc -Wall -ansi -pedantic`
- ANSI C (C90 standard) compatibility required
- No global variables unless required and documented
- Full memory cleanup is mandatory (no leaks)

**For Input Assembly Files Your Assembler Must Handle:**
- Line length limit: **80 characters** (input `.as` files)
- Label length limit: **31 characters** (in assembly code)
- Must handle macros (`mcro ... endmcro`)

---

## 📁 Planned File Input/Output

**Input:** `.as` files (assembly code with possible macro definitions)

**Output:** `.ob`, `.ent`, `.ext` files with processed and encoded machine code

---

## ✅ Milestones

- [ ] Setup project folder structure and Makefile
- [ ] Implement macro expansion logic
- [ ] Implement first pass (symbol resolution and validation)
- [ ] Implement second pass (code generation and output)
- [ ] Full memory cleanup and error handling
- [ ] Test on various `.as` inputs and validate outputs

---

> **Note:** This file will evolve as the project progresses to include implementation notes, bugs, and usage examples.
> 
> Let me know if you want a version saved as a file or edited to include your name/student ID. 


