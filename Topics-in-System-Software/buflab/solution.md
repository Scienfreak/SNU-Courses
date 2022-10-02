## level 0

just put smoke function's address into the stack's return address.<br>

## level 1

In fizz function, it checks cookie and such value in specific address.<br>
I found the address and it was 8 bytes after the address of stack's return address.<br>
So, I added two more word-size lines consist of cookie value.<br>

> Changing stack's original return value into buffer's address is essential for the code injection attack.<br>

## level 2

Before return to bang function, I initiated global_value with cookie value.<br>
I had to find global_value's address, then put a code that stores the cookie value into the address.<br>
After that, the code in the stack must have return address which goes to bang function.<br>

> Changing stack's original return value into buffer's address is essential for the code injection attack.<br>

## level 3

I had to restore the stack status, especially the original ebx value of the caller, stored at the callee's fuction prolog.<br>
I added original ebx value into my injecting code, and made my code to move my cookie value to register %eax0.<br>

## level 4


## level 5 (RTL - Return-to-libc attack)

### *REQUIREMENTS*

- We should print "HOLYMOLY: my cookie is 0x<your cookie>\."
 [After printing, we should return to original return address in testr.]: #
 [At the time, `%eax == 0x22` and `%ebp == origianl ebp` are required.]: #
- Return to after the checking wheter %eax's value is 0x22 or not.
  
### *Exploit code*
  
> "pad: 44 Bytes" + "call printf function (4Byte)" + "gadget: pop 2 times and return" + "printf's arg1 (address of string)" + "printf's arg2 (my cookie value)" + "RET to testr"
