# Nyx-16

Nyx-16 is a virtual 16-bit computer implemented in C.

The project aims to simulate the essential behavior of a computer architecture, including memory, registers, machine instructions, arithmetic and logical operations, and the fetch-decode-execute cycle.

Nyx-16 is being developed as the final project of the **BASE Saga**, applying concepts from C programming, data structures, memory management, computer architecture, assembly and operating systems.

---

## Project Objective

The main objective of Nyx-16 is to understand how a computer executes a program from the lowest software-visible level.

The project will demonstrate how:

1. a program is represented as machine instructions;
2. instructions are stored in memory;
3. the Program Counter identifies the next instruction;
4. the CPU fetches the instruction;
5. the decoder interprets its bits;
6. the control unit coordinates execution;
7. the ALU performs arithmetic or logical operations;
8. registers and memory store the resulting state.

The first version focuses only on creating a small but complete virtual computer capable of executing machine-code programs stored directly in memory.

---

## Nyx-16 v1.0

Nyx-16 v1.0 will be the first functional version of the architecture.

It will include:

* 16-bit words;
* 16-bit machine instructions;
* 16-bit memory addresses;
* word-addressed virtual RAM;
* 65,536 memory positions;
* 128 KiB of simulated memory;
* eight general-purpose registers;
* Program Counter;
* Instruction Register;
* Arithmetic Logic Unit;
* Zero and Negative flags;
* instruction decoder;
* control unit;
* minimal Instruction Set Architecture;
* fetch-decode-execute cycle;
* conditional and unconditional jumps;
* CPU halt behavior.

Programs will initially be inserted directly into virtual memory through C.

---

## Architecture Overview

```text
NYX-16
│
├── RAM
│   ├── 65,536 addresses
│   ├── 16-bit word per address
│   ├── machine instructions
│   └── program data
│
├── CPU
│   ├── General-purpose registers
│   ├── Program Counter
│   ├── Instruction Register
│   ├── Arithmetic Logic Unit
│   ├── Flags
│   ├── Instruction Decoder
│   ├── Control Unit
│   └── Execution state
│
├── Instruction Set Architecture
│   ├── Instruction formats
│   ├── Opcodes
│   ├── Register encoding
│   └── Instruction behavior
│
└── Execution Cycle
    ├── Fetch
    ├── Decode
    └── Execute
```

---

## Core Components

### RAM

Stores both machine instructions and program data.

Nyx-16 v1.0 uses 16-bit addresses, allowing:

```text
2¹⁶ = 65,536 addresses
```

Each address stores one 16-bit word.

---

### Registers

The CPU contains eight general-purpose registers:

```text
R0
R1
R2
R3
R4
R5
R6
R7
```

Each register stores one 16-bit value.

Registers hold operands, intermediate values and operation results.

---

### Program Counter

The Program Counter, or `PC`, stores the address of the next instruction.

During normal execution, the PC advances after each instruction is fetched.

Jump instructions can replace its value and change the program execution flow.

---

### Instruction Register

The Instruction Register, or `IR`, stores the instruction currently being decoded and executed.

During the fetch stage:

```text
IR = RAM[PC]
```

---

### Arithmetic Logic Unit

The Arithmetic Logic Unit, or `ALU`, performs arithmetic and logical operations.

Initial operations may include:

```text
ADD
SUB
AND
OR
XOR
NOT
```

---

### Flags

Flags store information about the result of the latest relevant operation.

Nyx-16 v1.0 will initially contain:

```text
Z — Zero Flag
N — Negative Flag
```

These flags allow conditional instructions to control program execution.

---

### Instruction Decoder

The decoder interprets the bits of the instruction stored in the IR.

It extracts information such as:

* opcode;
* destination register;
* source register;
* immediate value;
* memory address.

---

### Control Unit

The control unit coordinates the behavior of the CPU.

It determines:

* which registers are read;
* which ALU operation is executed;
* where results are stored;
* whether RAM is read or written;
* whether flags are updated;
* whether the PC advances or jumps;
* whether the processor stops.

---

## Fetch-Decode-Execute Cycle

Nyx-16 executes programs through a repeated three-stage cycle.

### Fetch

The CPU retrieves the next instruction from memory.

```text
IR = RAM[PC]
PC = PC + 1
```

### Decode

The decoder interprets the instruction bits and identifies the required operation and operands.

### Execute

The control unit performs the instruction behavior, updating registers, flags, memory or the Program Counter.

```text
FETCH
  ↓
DECODE
  ↓
EXECUTE
  ↓
FETCH
```

---

## Initial Instruction Set

The first instruction set is expected to contain a small group of essential instructions.

### Data movement

```text
LOADI
LOAD
STORE
MOV
```

### Arithmetic

```text
ADD
SUB
```

### Logic

```text
AND
OR
XOR
NOT
```

### Control flow

```text
JMP
JZ
HALT
```

The exact instruction formats and opcode values will be defined in the ISA documentation.

---

## Project Structure

```text
nyx16/
├── docs/
│   └── architecture.md
├── include/
├── src/
├── tests/
├── programs/
└── README.md
```

### `docs/`

Contains the technical documentation and architecture specifications.

### `include/`

Contains the public header files of the project.

### `src/`

Contains the C implementation of the virtual computer.

### `tests/`

Contains isolated tests for memory, CPU components and instructions.

### `programs/`

Contains machine-code and future Nyx Assembly programs used to test the architecture.

---

## Documentation

The complete architecture specification is available in:

* [Nyx-16 Architecture](docs/architecture.md)

Future documentation may include:

```text
docs/
├── architecture.md
├── memory.md
├── cpu.md
├── isa.md
├── instruction-format.md
└── execution-cycle.md
```

---

## Development Status

Nyx-16 is currently in the architecture and design phase.

Current progress:

* [x] Define the project objective
* [x] Define the initial architecture scope
* [x] Define the core computer components
* [x] Create the initial architecture documentation
* [ ] Define the C project structure
* [ ] Implement 16-bit architecture types
* [ ] Implement virtual RAM
* [ ] Implement CPU registers
* [ ] Implement the Program Counter
* [ ] Implement the Instruction Register
* [ ] Implement the ALU
* [ ] Implement CPU flags
* [ ] Define the instruction format
* [ ] Define the initial ISA
* [ ] Implement the instruction decoder
* [ ] Implement the control unit
* [ ] Implement the fetch-decode-execute cycle
* [ ] Execute the first machine-code program

---

## Version 1.0 Completion Criteria

Nyx-16 v1.0 will be complete when:

* instructions and data can be stored in RAM;
* the CPU can fetch instructions using the Program Counter;
* the decoder can interpret 16-bit machine instructions;
* the ALU can perform arithmetic and logical operations;
* registers and memory can store operation results;
* flags can control conditional jumps;
* the CPU can repeatedly execute the fetch-decode-execute cycle;
* the `HALT` instruction can stop execution;
* different programs can be executed by changing the instructions stored in RAM.

---

## Future Versions

Future versions of Nyx-16 may include:

* Nyx Assembly language;
* assembler;
* binary executable format;
* binary loader;
* stack;
* Stack Pointer;
* `PUSH` and `POP`;
* `CALL` and `RET`;
* calling convention;
* terminal input and output;
* memory-mapped devices;
* system calls;
* interrupts;
* kernel;
* processes;
* context switching;
* scheduler;
* filesystem;
* high-level programming language;
* compiler.

---

## Long-Term Architecture

```text
Nyx Assembly
      ↓
Assembler
      ↓
Nyx Binary
      ↓
Loader
      ↓
Virtual RAM
      ↓
Nyx-16 CPU
      ↓
Input and Output
      ↓
System Calls
      ↓
Minimal Operating System
```

Nyx-16 v1.0 provides the foundation on which all future versions will be built.
