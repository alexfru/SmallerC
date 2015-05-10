;
;  Copyright (c) 2014-2015, Alexey Frunze
;  2-clause BSD license.
;
bits 32

    extern ___start__

section .text

    global __start
__start:
    jmp     ___start__ ; __start__() will set up argc and argv for main() and call exit(main(argc, argv))


section .bss
    resd    1
