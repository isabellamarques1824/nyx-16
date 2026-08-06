# Nyx-16 Architecture

## Overview

Nyx-16 is a virtual 16-bit computer implemented in C.

The project simulates the essential structure and behavior of a simple computer, including a central processing unit, memory, registers, machine instructions and the fetch-decode-execute cycle.

Nyx-16 does not simulate individual electronic components or electrical signals. Instead, it reproduces the logical behavior of the computer architecture using C structures, arrays, functions and bitwise operations.

The first version focuses on the smallest complete architecture capable of storing and executing a machine program.

---

## Version 1.0

Nyx-16 v1.0 is the first functional version of the virtual computer.

This version will be capable of:

* storing machine instructions in virtual memory;
* storing program data in virtual memory;
* reading instructions sequentially;
* decoding 16-bit machine instructions;
* executing arithmetic and logical operations;
* transferring values between registers and memory;
* changing the execution flow through jump instructions;
* stopping the processor through a `HALT` instruction.

Programs will initially be written directly as 16-bit machine instructions and inserted into memory by the C implementation.

Nyx-16 v1.0 will not yet include an assembly language, assembler, binary loader, stack, system calls or operating system.

---

# Architecture Summary

Nyx-16 v1.0 is composed of two main parts:

```text
NYX-16
├── CPU
└── RAM
```

The CPU contains:

```text
CPU
├── General-purpose registers
├── Program Counter
├── Instruction Register
├── Arithmetic Logic Unit
├── Flags
├── Instruction Decoder
├── Control Unit
└── Execution state
```

The computer also requires:

```text
Instruction Set Architecture
├── Instruction formats
├── Opcodes
├── Register encoding
└── Instruction behavior
```

These components work together through the fetch-decode-execute cycle.

---

# 16-Bit Architecture

Nyx-16 is based on 16-bit words.

A word is the primary unit of information used by the architecture.

Each word contains exactly 16 bits:

```text
0000 0000 0000 0000
```

A 16-bit word can represent:

* an unsigned integer;
* a signed integer;
* a memory address;
* a machine instruction;
* program data;
* bit flags.

The same sequence of bits may have different meanings depending on how it is being used.

For example:

```text
0000 0000 0000 0101
```

This word may represent:

```text
Unsigned integer: 5
Signed integer:   5
Instruction data: depends on the instruction format
```

Nyx-16 will use fixed-width integer types from `<stdint.h>` to guarantee that architecture values always contain the expected number of bits.

---

# Numeric Range

A 16-bit unsigned value can represent:

```text
0 to 65,535
```

A 16-bit signed value using two's complement can represent:

```text
-32,768 to 32,767
```

Registers and memory positions store only bits.

Whether a value is interpreted as signed or unsigned depends on the operation being executed.

---

# Memory Architecture

## Memory Organization

Nyx-16 v1.0 uses word-addressed memory.

This means that every memory address refers to one complete 16-bit word.

Conceptually:

```text
RAM[address] = 16-bit word
```

Examples:

```text
RAM[0x0000] = 16-bit instruction
RAM[0x0001] = 16-bit instruction
RAM[0x0100] = 16-bit program data
```

The RAM stores both instructions and data.

There is no separate instruction memory and data memory in version 1.0.

---

## Address Space

Nyx-16 uses 16-bit memory addresses.

A 16-bit address can represent:

```text
2¹⁶ = 65,536 different addresses
```

The valid address range is:

```text
0x0000 to 0xFFFF
```

Therefore, Nyx-16 contains:

```text
65,536 memory positions
```

Each position stores one 16-bit word.

Since one 16-bit word contains two bytes, the total simulated memory capacity is:

```text
65,536 words × 2 bytes
```

Result:

```text
131,072 bytes
```

Equivalent to:

```text
128 KiB
```

The C implementation can represent this memory as a fixed-size array of 16-bit values.

---

## Memory Responsibilities

The memory component is responsible for:

* storing machine instructions;
* storing program data;
* returning the word stored at an address;
* writing a word to an address;
* resetting memory to its initial state.

Conceptually, it provides the following operations:

```text
Read memory
Write memory
Reset memory
```

---

## Initial Memory State

When the Nyx-16 computer is initialized, all memory positions must contain zero.

```text
RAM[0x0000] = 0
RAM[0x0001] = 0
RAM[0x0002] = 0
...
RAM[0xFFFF] = 0
```

Programs will later be copied into selected memory positions before execution begins.

---

# Central Processing Unit

The CPU is responsible for reading and executing machine instructions.

The CPU contains the state required to continue program execution from one cycle to the next.

Its main components are:

```text
CPU
├── General-purpose registers
├── Program Counter
├── Instruction Register
├── Flags
├── ALU
├── Decoder
├── Control Unit
└── Halted state
```

---

# General-Purpose Registers

Registers are small storage locations located inside the CPU.

They hold values currently being used by instructions.

Registers are used to:

* store arithmetic operands;
* store logical operands;
* store calculation results;
* temporarily hold values read from RAM;
* hold values before writing them to RAM;
* transfer values between instructions.

Nyx-16 v1.0 will contain eight general-purpose registers:

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

Each register stores one 16-bit word.

Example CPU state:

```text
R0 = 0x0005
R1 = 0x0007
R2 = 0x0000
R3 = 0x0000
R4 = 0x0000
R5 = 0x0000
R6 = 0x0000
R7 = 0x0000
```

After an addition between `R0` and `R1`:

```text
R0 = R0 + R1
```

The CPU state becomes:

```text
R0 = 0x000C
R1 = 0x0007
```

All registers must contain zero when the CPU is initialized.

---

# Program Counter

The Program Counter, abbreviated as `PC`, is a special 16-bit register.

It stores the memory address of the next instruction that the CPU must fetch.

Example:

```text
PC = 0x0000
```

The CPU reads the instruction stored at:

```text
RAM[0x0000]
```

After fetching the instruction, the PC normally advances:

```text
PC = PC + 1
```

The next instruction is then fetched from:

```text
RAM[0x0001]
```

This process creates sequential program execution.

Jump instructions can replace the current PC value with another address.

Example:

```text
JMP 0x0100
```

Result:

```text
PC = 0x0100
```

The Program Counter makes the following behaviors possible:

* sequential execution;
* conditional execution;
* loops;
* branches;
* future function calls.

The PC begins at address `0x0000` in Nyx-16 v1.0.

---

# Instruction Register

The Instruction Register, abbreviated as `IR`, stores the 16-bit instruction currently being processed by the CPU.

During the fetch stage:

```text
IR = RAM[PC]
```

The decoder reads the bits stored in the IR to identify:

* the opcode;
* the instruction format;
* registers;
* immediate values;
* memory addresses.

The IR preserves the current instruction while the CPU decodes and executes it.

The Instruction Register contains zero when the CPU is initialized.

---

# Arithmetic Logic Unit

The Arithmetic Logic Unit, abbreviated as `ALU`, performs arithmetic and logical operations.

The ALU receives input values, applies an operation and produces a 16-bit result.

Example:

```text
Input A:   0x0005
Input B:   0x0007
Operation: ADD
Result:    0x000C
```

Nyx-16 v1.0 may support operations such as:

```text
ADD
SUB
AND
OR
XOR
NOT
```

The ALU also provides information used to update the CPU flags.

Because Nyx-16 is implemented in software, the ALU does not need to recreate individual logic gates.

Its behavior can be implemented using C arithmetic and bitwise operators while preserving 16-bit results.

---

# CPU Flags

Flags store information about the result of the most recently executed operation.

Nyx-16 v1.0 contains two basic flags:

```text
Z — Zero Flag
N — Negative Flag
```

## Zero Flag

The Zero Flag is active when the result of an operation is zero.

```text
Z = 1 when result == 0
Z = 0 otherwise
```

Example:

```text
5 - 5 = 0
```

Result:

```text
Z = 1
```

---

## Negative Flag

The Negative Flag is active when the result represents a negative 16-bit signed value.

In two's complement, the most significant bit indicates whether the value is negative.

```text
N = 1 when the most significant bit is 1
N = 0 otherwise
```

Example:

```text
1111 1111 1111 1111
```

This represents `-1` as a signed 16-bit value.

Result:

```text
N = 1
```

Flags are used by conditional jump instructions.

---

# Instruction Set Architecture

The Instruction Set Architecture, abbreviated as `ISA`, defines the machine language understood by the Nyx-16 CPU.

The ISA determines:

* which instructions exist;
* the numeric opcode assigned to each instruction;
* how instruction bits are organized;
* which registers are used;
* how memory is accessed;
* how flags are modified;
* how jumps modify the Program Counter.

The ISA is the interface between software and the processor.

Programs must follow the ISA specification to be executed correctly.

---

# Instruction Format

Every Nyx-16 machine instruction occupies one 16-bit word.

The 16 bits are divided into fields.

Different instruction categories may interpret the remaining bits differently.

A register-based instruction may use a format similar to:

```text
OOOO DDDD SSSS XXXX
```

Where:

```text
OOOO = opcode
DDDD = destination register
SSSS = source register
XXXX = additional instruction data
```

An instruction containing an immediate value may use:

```text
OOOO RRRR IIIIIIII
```

Where:

```text
OOOO     = opcode
RRRR     = register
IIIIIIII = immediate value
```

The exact formats and opcode values will be defined in the Nyx-16 ISA specification.

---

# Instruction Decoder

The instruction decoder interprets the bits stored in the Instruction Register.

Its responsibilities include:

* extracting the opcode;
* identifying the instruction format;
* extracting register indexes;
* extracting immediate values;
* extracting memory addresses;
* selecting the behavior that must be executed.

Example instruction:

```text
0010 0001 0010 0000
```

The decoder may interpret the fields as:

```text
Opcode:               0010
Destination register: 0001
Source register:      0010
Additional bits:      0000
```

The instruction fields are extracted using bit masks and bit shifts.

The decoder does not perform the final operation. It determines what the instruction means and provides the decoded information to the control logic.

---

# Control Unit

The control unit coordinates the components of the CPU during instruction execution.

It uses the decoded instruction to determine:

* which registers must be read;
* which ALU operation must be performed;
* where the result must be stored;
* whether RAM must be read;
* whether RAM must be written;
* whether flags must be updated;
* whether the PC must continue sequentially;
* whether the PC must jump;
* whether the CPU must stop.

In the C implementation, the control unit will be represented by the instruction execution logic.

It will connect the decoder output to the behavior of the CPU, ALU, registers and RAM.

---

# Execution State

The CPU contains a halted state indicating whether execution is active.

```text
halted = false
```

means that the CPU may continue executing instructions.

```text
halted = true
```

means that execution has stopped.

The `HALT` instruction changes this state.

The main CPU loop continues only while the halted state is false.

---

# Virtual Clock

Physical processors use an electronic clock to synchronize state changes.

Nyx-16 is a software simulation and therefore does not require a physical clock signal.

Each iteration of the execution loop represents one virtual machine cycle.

During a cycle, the CPU:

```text
Fetches an instruction
Decodes the instruction
Executes the instruction
Updates the machine state
```

The virtual clock is therefore represented by repeated execution of the CPU cycle.

---

# Fetch-Decode-Execute Cycle

Nyx-16 executes programs through the fetch-decode-execute cycle.

## Fetch

The CPU retrieves the next instruction from RAM.

```text
IR = RAM[PC]
PC = PC + 1
```

At the end of the fetch stage:

* the IR contains the current instruction;
* the PC points to the next sequential instruction.

---

## Decode

The decoder examines the instruction stored in the IR.

It extracts:

* the opcode;
* register identifiers;
* immediate values;
* addresses;
* instruction-specific fields.

The decoder determines which operation must be executed.

---

## Execute

The control unit performs the instruction behavior.

Depending on the instruction, execution may:

* modify a register;
* perform an ALU operation;
* read from RAM;
* write to RAM;
* update flags;
* change the PC;
* halt the processor.

After execution, the cycle starts again.

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

# Initial Instruction Set

The first Nyx-16 instruction set should remain small while still allowing the execution of useful programs.

## Data Instructions

```text
LOADI
```

Loads a constant value directly into a register.

```text
LOAD
```

Loads a word from RAM into a register.

```text
STORE
```

Stores a register value in RAM.

```text
MOV
```

Copies a value from one register to another.

---

## Arithmetic Instructions

```text
ADD
```

Adds two register values.

```text
SUB
```

Subtracts one register value from another.

---

## Logical Instructions

```text
AND
OR
XOR
NOT
```

Perform bitwise logical operations.

---

## Control Flow Instructions

```text
JMP
```

Changes the Program Counter unconditionally.

```text
JZ
```

Changes the Program Counter when the Zero Flag is active.

```text
HALT
```

Stops CPU execution.

The final instruction list may be adjusted during the ISA design stage.

---

# Program Storage

Nyx-16 programs are stored in RAM as sequences of 16-bit machine instructions.

Example:

```text
Address     Content

0x0000      First instruction
0x0001      Second instruction
0x0002      Third instruction
0x0003      HALT instruction
```

The CPU begins execution with:

```text
PC = 0x0000
```

It reads and executes the instructions until reaching `HALT`.

In version 1.0, the machine instructions will be inserted into RAM directly by the host C program.

This allows the CPU to be developed and tested before the assembler and binary loader exist.

---

# Complete Version 1.0 Structure

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
│   ├── R0–R7
│   ├── Program Counter
│   ├── Instruction Register
│   ├── Zero Flag
│   ├── Negative Flag
│   ├── Arithmetic Logic Unit
│   ├── Instruction Decoder
│   ├── Control Unit
│   └── Halted state
│
├── Instruction Set Architecture
│   ├── 16-bit instructions
│   ├── instruction formats
│   ├── opcodes
│   ├── register encoding
│   └── instruction behavior
│
└── Execution Engine
    ├── fetch
    ├── decode
    └── execute
```

---

# What Makes Nyx-16 a Computer?

Nyx-16 v1.0 is considered a computer because it contains:

* memory capable of storing programs and data;
* a processor capable of executing instructions;
* registers capable of preserving internal state;
* an ALU capable of processing values;
* an instruction set defining machine behavior;
* a Program Counter controlling program execution;
* conditional and unconditional control flow;
* a repeated instruction execution cycle.

A specific test program may perform an addition or another simple operation, but Nyx-16 itself is not a calculator.

It is a general machine capable of executing different programs composed from its supported instructions.

---

# Version 1.0 Scope

Nyx-16 v1.0 includes:

* 16-bit architecture;
* word-addressed RAM;
* 65,536 memory positions;
* 128 KiB of simulated memory;
* eight general-purpose registers;
* Program Counter;
* Instruction Register;
* Zero and Negative flags;
* arithmetic and logical operations;
* instruction decoding;
* control logic;
* a minimal instruction set;
* fetch-decode-execute cycle;
* direct program loading through C;
* execution until `HALT`.

---

# Future Components

The following components are not part of Nyx-16 v1.0:

* Nyx Assembly language;
* assembler;
* executable binary format;
* binary loader;
* Stack Pointer;
* stack;
* `PUSH`;
* `POP`;
* `CALL`;
* `RET`;
* calling convention;
* terminal input and output;
* memory-mapped devices;
* interrupts;
* system calls;
* kernel;
* processes;
* scheduler;
* filesystem;
* compiler.

These features will be built on top of the architecture established by version 1.0.

---

# Version 1.0 Completion Criteria

Nyx-16 v1.0 is complete when:

1. RAM can store 16-bit instructions and data.
2. The CPU can read an instruction from the address stored in the PC.
3. The PC advances after an instruction is fetched.
4. The IR preserves the current instruction.
5. The decoder correctly extracts instruction fields.
6. The control unit selects the correct instruction behavior.
7. The ALU performs the required operation.
8. Registers can store and receive results.
9. RAM can be read and modified by instructions.
10. Flags are updated after relevant operations.
11. Jump instructions can modify the PC.
12. The CPU repeatedly executes the fetch-decode-execute cycle.
13. The `HALT` instruction stops execution.
14. Different machine programs can be executed by changing the instructions stored in RAM.
