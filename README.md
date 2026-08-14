# Nyx-16

Nyx-16 is a virtual 16-bit computer implemented in C.

The project was created to study how a computer works from the lowest software-visible level, including registers, memory, machine instructions, arithmetic and logical operations, and the fetch-decode-execute cycle.

Nyx-16 is the final project of the **BASE Saga**, bringing together concepts from C programming, data structures, memory management and computer architecture.

---

## Project Objective

The main goal of Nyx-16 is to build a small but complete virtual computer capable of executing programs represented directly as machine instructions.

The project explores how:

* instructions are represented as binary values;
* instructions and data are stored in memory;
* the Program Counter identifies the next instruction;
* the CPU fetches and decodes instructions;
* the ALU performs arithmetic and logical operations;
* registers store values and intermediate results;
* flags describe the result of operations;
* jumps modify program execution flow;
* the CPU continuously executes the fetch-decode-execute cycle.

The first version focuses on the essential components required to execute simple machine-code programs.

---

## Nyx-16 v1.0

Nyx-16 v1.0 will contain:

* 16-bit words;
* 16-bit machine instructions;
* 16-bit memory addresses;
* 65,536 word-addressable memory locations;
* 128 KiB of simulated RAM;
* eight general-purpose registers;
* Program Counter;
* Instruction Register;
* Status Register;
* Arithmetic Logic Unit;
* Zero, Negative, Carry and Overflow flags;
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
│   ├── 16-bit words
│   ├── machine instructions
│   └── program data
│
├── CPU
│   ├── General-purpose registers
│   ├── Program Counter
│   ├── Instruction Register
│   ├── Status Register
│   ├── Arithmetic Logic Unit
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

## CPU Registers

Nyx-16 v1.0 contains eight general-purpose registers:

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

They are used to store operands, intermediate values and operation results.

The CPU also contains three special registers:

```text
PC — Program Counter
IR — Instruction Register
SR — Status Register
```

### Program Counter

The Program Counter stores the address of the next instruction to be fetched.

During normal execution, the PC advances after an instruction is fetched.

Jump instructions can replace its value and redirect program execution.

### Instruction Register

The Instruction Register stores the instruction currently being decoded and executed.

During the fetch stage:

```text
IR = RAM[PC]
```

### Status Register

The Status Register stores CPU flags produced by relevant operations.

Nyx-16 v1.0 uses four flags:

```text
Z — Zero
N — Negative
C — Carry
V — Overflow
```

Each flag occupies one bit inside the Status Register.

The flags are used to describe operation results and support conditional execution.

---

## RAM

Nyx-16 uses a unified virtual memory for both machine instructions and program data.

Memory addresses are 16 bits wide:

```text
2¹⁶ = 65,536 addresses
```

Each address stores one 16-bit word.

This results in:

```text
65,536 × 2 bytes = 128 KiB
```

of simulated memory.

---

## Arithmetic Logic Unit

The Arithmetic Logic Unit, or `ALU`, performs arithmetic and logical operations on 16-bit values.

The initial ALU is expected to support operations such as:

```text
ADD
SUB
AND
OR
XOR
NOT
```

Relevant operations may update the Status Register flags.

---

## Instruction Decoder

Machine instructions are stored as 16-bit values.

The instruction decoder interprets the bits stored in the Instruction Register and extracts the information required to execute the instruction.

Depending on the instruction format, this may include:

* opcode;
* destination register;
* source register;
* immediate value;
* memory address.

The exact instruction encoding will be defined as part of the Nyx-16 ISA.

---

## Control Unit

The control unit coordinates CPU execution.

It determines:

* which registers are read;
* which ALU operation is performed;
* where results are stored;
* whether memory is read or written;
* whether flags are updated;
* whether the Program Counter advances or changes;
* whether the CPU continues running or halts.

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

The instruction decoder interprets the instruction stored in the IR and determines what operation must be performed.

### Execute

The control unit performs the instruction behavior.

This may modify:

* registers;
* memory;
* CPU flags;
* the Program Counter;
* the CPU execution state.

```text
FETCH
  ↓
DECODE
  ↓
EXECUTE
  ↓
FETCH
```

The cycle continues until a `HALT` instruction stops the processor.

---

## Initial Instruction Set

Nyx-16 v1.0 will use a small Instruction Set Architecture containing only the operations required to execute basic programs.

### Data Movement

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

### Control Flow

```text
JMP
JZ
HALT
```

The final instruction formats, opcode values and behavior will be documented separately in the ISA specification.

---

## Project Structure

```text
nyx16/
├── docs/
├── include/
├── src/
├── tests/
├── programs/
└── README.md
```

### `docs/`

Architecture and technical documentation.

### `include/`

Public C header files.

### `src/`

Implementation of the virtual computer.

### `tests/`

Tests for individual components and CPU behavior.

### `programs/`

Machine-code programs used to test the architecture.

---

## Current Status

Nyx-16 is currently under active development.

The register subsystem is implemented, including:

* eight 16-bit general-purpose registers;
* Program Counter;
* Instruction Register;
* Status Register;
* Zero, Negative, Carry and Overflow flags.

The register module currently supports register initialization, general-purpose register access, Program Counter manipulation, Instruction Register loading and individual flag manipulation.

The next major CPU component is the **Arithmetic Logic Unit**.

RAM, the instruction format, ISA, decoder, control unit and complete fetch-decode-execute cycle will be implemented as the architecture continues to evolve.

---

## Version 1.0

Nyx-16 v1.0 will be considered complete when it can:

* store instructions and data in virtual RAM;
* fetch instructions using the Program Counter;
* decode 16-bit machine instructions;
* execute arithmetic and logical operations;
* store results in registers and memory;
* update and read CPU flags;
* perform conditional and unconditional jumps;
* repeatedly execute the fetch-decode-execute cycle;
* stop execution through `HALT`;
* execute different programs by changing the machine instructions stored in memory.

At that point, Nyx-16 will function as a complete minimal virtual computer.

---

## Future Development

Later versions may expand the architecture with:

* Nyx Assembly;
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

The long-term goal is to progressively build a complete software stack on top of the Nyx-16 architecture.

```text
Nyx Source Code
      ↓
Compiler
      ↓
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
Input / Output
      ↓
System Calls
      ↓
Operating System
```

Nyx-16 v1.0 provides the foundation for everything that comes after it.
