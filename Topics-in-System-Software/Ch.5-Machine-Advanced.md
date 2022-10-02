### 목차

- [Memory Layout](#1)
- [Buffer Overflow](#2)
  + [Vulnerability](#3)
    * [Stack Smashing](#4)
    * [Code Injection](#5)
  + [Protection](#6)
    * [Avoid overflow vulnerabilities](#7)
    * [Employ system-level protections](#8)
    * [Hava compiler use "stack canaries"](#9)
  + [Return-Oriented Programming](#10)

---

<a id="1"></a>

## Memory Layout

### x86-64 Linux Memory Layout

- **Text**            : Executable machine instructions / *Read Only*
- **Data, BSS**       : Statically allocated data (e.g. Global vars, **static** vars, string constants)<br>
  + Data  : Initialized vars<br>
  + BSS   : Uninitialized vars<br>
- **Heap**            : Dynamically allocated as needed (When call **malloc(), calloc(), new()**
- **Shared Library**  : Executable machine instructions from dynamic library
- **Stack**           : Runtime stack (e.g. Local vars)
- Kernel Area         : Allocated for kernel (User is not available to access here.)

> 시험에 나올 수도 있음: For given C code, match each variable and function to appropriate Memory area.

---

<a id="2"></a>

## Buffer Overflow

<a id="3"></a>

### Buffer Overflow Vulnerability

- BOF : When exceeding the memory size allocated for an array
- Why a big deal?
  + It's major technical cause of security vulnerabilities.
  + #1 overall cause is social engineering / user ignorance
- Most common form
  + Unchecked lengths on string inputs
  + Particularaly for bounded character arrays on the stack

### Exploits Based on Buffer Overflows

- ***BOF can allow remote machines to execute arbitrary code on victim machines.***
- Surprisingly common in real programs.
  + Recent mitigation techniqus make these attacks much more difficult.
- [Examples across the decades](Examples-across-the-decades.md)

### String Library Codes which are weak of BOF

- *gets, strcpy, strcat*  : Copy strings of arbitrary length
- *scanf, fscanf, sscanf* : When given **%s** conversion specification

### Buffer Overflow Stack Example

    void echo()
    {
        char buf[4]; /* Way too small! */
        gets(buf);
        puts(buf);
    }
    
    void call_echo()
    {
        echo();
    }

- When call_echo() invokes echo(), invoking echo(), the return address is filled up.<br>
  + *return addr. == %rip (at call inst.) == next inst. addr. of call inst.*
  + `call <echo>` == `push %rip; jmp <echo>`
- If input string is too long, it overwrites the return address in stack, bring out **Segmentation fault**.
  + Segmentation fault occurs when access to the memory which is not mapped, and exception occurs.

<a id="4"></a>

### 1. Stack Smashing Attacks

> Overwrite the return value in stack into the address that attacker intended to execute.

- Use the code that already in the memory.
- Attacker must know the target code's address.
  + This can be pretended by changing the address of the code for every run.
- Write Hex string, and hexify it into charater string, then give it to the program.

<a id="5"></a>

### 2. Code Injection Attacks

> Inject executable code into stack, and overwrite return addr. into addr. of buffer.

- Attacker must know the buffer address.
  + Also pretended by Randomization.
- Can write the code over the pad.

---

<a id="6"></a>

## What to do about BOF Attacks

<a id="7"></a>

### 1. Avoid Overflow Vulnerabilities in Code (!)

> Secure Coding!

    void echo()
    {
        char buf[4];
        fgets(buf, 4, stdin);
        puts(buf);
    }

- Use library routines that limit string lengths
  + **fgets** instead of *gets*
  + **strncpy** instead of *strcpy*
  + Don't use *scanf* with *%s* conversion specification
    * Use **fgets** to read the string

<a id="8"></a>

### 2. System-Level Protections

> Address Space Layout Randomization : ASLR

- **Randomized Stack Offsets** (Kernel Solution?)
  + At start of program, **allocate random amount of space** on stack
  + Shifts stack addresses for entire program
  + Makes it difficult for hacker to predict beginning of inserted code
  + Stack is repositioned each time program executes.
  + **But**, still other memory area's address is deterministic(?).

> Data Executuin Prevention : DEP

- **Nonexecutable code segments** (OS, Linker Solution?)
  + In traditional x86, can mark region of memory as either *"read-only"* or *"writealbe"*
    * Can execute anything readable
  + x86-64 added explicit "execute" permission
  + Stack marked as **non-executable**
  + **But**, still code's in text region is executable, attackers can use ROP attacks.

<a id="9"></a>

### 3. Stack Canaries

> Place special value "canary" on stack just beyond buffer, and check for corruption before exiting function.

- GCC Implementation
  + -fstack-protector (basically used in GCC)
  + The global canary is initialized with a random value when the program is loaded.
  + `%fs:0x28` is a read-only storage, storing a global canary.
  + **But**, attacker can access over the canary by pointer.
    * Canary assumes the linear access.

---

<a id="10"></a>

## Return-Oriented Programming Attacks

> 시험에 나올 수도 있음

- Challenge (for hackers)
  + Marking stack nonexecutable makes it hard to insert binary code.
- Alternative Strategy
  + Use existing code
    * e.g., library code from stdlib (called **"RTL : Return-To-Libc**)
  + Chain those fragments to achieve overall desired outcome
- Construct "attack logic" from ***gadgets***
  + Gadget: any sequence of instructions ending in **ret**
    * **ret** : an instruction encoded by single byte **`0xc3`**

### ROP Execution

- Trigger with *ret* instruction, which will start executing Gadget 1
  + Also can return to library code
    * If it needs arguments, it must in the stack.
    * To return to next gadget, attacker must find `pop` instruction to eliminate arguments which ends with `ret`.
- Final *ret* in each gadget will start next one
  + **ret** : 1) pop address from stack and 2) jump to that address

