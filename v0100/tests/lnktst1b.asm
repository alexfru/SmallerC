; Part of lnktst1.asm test.

bits 16

extern msg

section .text

    global func
func:
    mov dx, msg
    mov ah, 9
    int 0x21

    ret
