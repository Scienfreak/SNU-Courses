### 목차

- Memory Layout
  
- Buffer Overflow
  + Vulnerability
  + Protection

---

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

## Buffer Overflow

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
