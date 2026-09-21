# NYX-16

<p align="center">
  <strong>A virtual 16-bit computer built from scratch in C.</strong>
</p>

<p align="center">
  <em>Registers. Memory. Machine code. ALU. ISA. Fetch. Decode. Execute.</em>
</p>

---

## About

**NYX-16** is a virtual 16-bit computer architecture implemented from scratch in C.

The project was created to explore how a computer works below the application level: how instructions are represented as bits, stored in memory, decoded by the CPU, executed, and used to modify registers, memory, and machine state.

Instead of emulating an existing processor, NYX-16 defines its own instruction set and architecture.

The goal is to build a complete and understandable computer where the entire path from machine code to execution can be followed.

---

## Architecture

NYX-16 currently uses:

- 16-bit words
- 16-bit memory addresses
- 8 general-purpose registers
- fixed 32-bit instructions
- 2 words per instruction
- 65,536 word-addressed memory locations
- unified memory for instructions and data
- arithmetic and logical status flags
- direct memory addressing
- stack operations
- conditional and unconditional jumps

### CPU Overview

```text
                    NYX-16 CPU
                         │
        ┌────────────────┼────────────────┐
        │                │                │
    Registers           ALU         Control Unit
        │                │                │
     R0-R7          ADD / SUB             │
     PC / SP         AND / OR             │
     IR / SR         XOR / NOT            │
        │                │                │
        └────────────────┼────────────────┘
                         │
                      Decoder
                         │
                         ▼
                       Memory
```

---

## Instruction Set

NYX-16 v1.0 defines 19 machine instructions.

| Category | Instructions |
|---|---|
| System | `NOP`, `HALT` |
| Data movement | `MOV`, `LDI` |
| Memory | `LOAD`, `STORE` |
| Arithmetic | `ADD`, `SUB` |
| Logic | `AND`, `OR`, `XOR`, `NOT` |
| Comparison | `CMP` |
| Control flow | `JMP`, `JZ`, `JNZ`, `JN` |
| Stack | `PUSH`, `POP` |

---

## Instruction Encoding

Every instruction occupies two 16-bit words.

```text
WORD 1

15        11 10      8 7       5 4       0
┌──────────┬──────────┬─────────┬─────────┐
│ Opcode   │   Reg1   │  Reg2   │ Reserved│
│ 5 bits   │ 3 bits   │ 3 bits  │ 5 bits │
└──────────┴──────────┴─────────┴─────────┘


WORD 2

15                                      0
┌────────────────────────────────────────┐
│                Payload                 │
│                16 bits                 │
└────────────────────────────────────────┘
```

The payload may represent an immediate value, memory address, jump target, or remain unused depending on the instruction.

---

## Memory

NYX-16 uses **word-addressed memory**.

Each address stores one complete 16-bit word.

```text
0x0000
┌─────────────────────────────┐
│ Code + Static Data          │
│                             │
0x1FFF
├─────────────────────────────┤
0x2000
│ Heap                        │
│ ↓                           │
│                             │
│        Free Memory          │
│                             │
│                           ↑ │
│ Stack                       │
│                             │
0xFFFF
└─────────────────────────────┘
```

The complete address space contains:

```text
65,536 words
128 KiB
```

---

## Fetch — Decode — Execute

Programs are executed through the classic instruction cycle:

```text
Machine Code
     │
     ▼
   Memory
     │
     ▼
   Fetch
     │
     ▼
   Decode
     │
     ▼
  Execute
     │
     ▼
Registers / Memory / Flags
```

A normal instruction fetch reads:

```text
RAM[PC]     → Word 1
RAM[PC + 1] → Word 2
```

The Program Counter then advances to the next instruction.

---

## Current Status

| Component | Status |
|---|---|
| Registers | ✅ Complete |
| ALU | ✅ Complete |
| ALU Tests | ✅ Complete |
| ISA | ✅ v1.0 defined |
| Instruction Encoding | ✅ Complete |
| Memory Architecture | ✅ Defined |
| Memory Implementation | 🚧 In progress |
| Decoder | ⏳ Planned |
| Control Unit | ⏳ Planned |
| CPU Execution Cycle | ⏳ Planned |
| Loader | ⏳ Planned |
| Assembler | ⏳ Planned |

---

## NYX-16 v1.0

The first complete version of NYX-16 will be able to:

1. load machine code into memory;
2. fetch instructions using the Program Counter;
3. decode NYX-16 instructions;
4. execute arithmetic and logical operations;
5. read and write memory;
6. perform conditional and unconditional jumps;
7. use a stack;
8. update CPU status flags;
9. continuously execute instructions;
10. stop when `HALT` is reached.

The complete scope is documented in:

[`docs/v1.0.md`](docs/v1.0.md)

---

## Documentation

More detailed documentation is available in the `docs` directory.

- [`architecture.md`](docs/architecture.md) — architecture and machine behavior
- [`v1.0.md`](docs/v1.0.md) — scope of the first complete version

---

## Project Structure

```text
NYX-16/
│
├── include/
│   ├── alu.h
│   ├── registers.h
│   ├── isa.h
│   └── ...
│
├── src/
│   ├── alu.c
│   ├── registers.c
│   ├── isa.c
│   └── ...
│
├── tests/
│
├── docs/
│   ├── architecture.md
│   └── v1.0.md
│
└── README.md
```

The project structure will evolve as the CPU implementation progresses.

---

## Why NYX-16?

Modern computers hide enormous amounts of complexity behind layers of abstraction.

NYX-16 takes the opposite approach.

The project builds those layers manually in order to understand how they connect:

```text
Machine Code
     ↓
Memory
     ↓
CPU
     ↓
Fetch
     ↓
Decode
     ↓
Execute
     ↓
Registers / ALU / Memory
```

The objective is not to create the fastest processor.

The objective is to understand one completely.

---

## References

NYX-16 is being developed alongside the study of computer architecture, systems programming, and low-level software.

Main references include:

- *Computer Organization and Architecture* — William Stallings
- *The Elements of Computing Systems* — Nisan & Schocken
- *Computer Systems: A Programmer's Perspective* — Bryant & O'Hallaron
- *Operating Systems: Three Easy Pieces* — Remzi H. Arpaci-Dusseau & Andrea C. Arpaci-Dusseau