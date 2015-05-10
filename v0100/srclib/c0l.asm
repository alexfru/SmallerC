;
;  Copyright (c) 2014-2015, Alexey Frunze
;  2-clause BSD license.
;
bits 32

    extern ___start__

section .text

    global __start
__start:
    pop     eax ; argc
    push    esp ; argv
    push    eax ; argc
    call    ___start__ ; __start__(arc, argv) will call exit(main(argc, argv))

section .bss
    resd    1
