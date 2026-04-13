.global gdt_flush

gdt_flush:
    movl 4(%esp), %eax
    lgdt (%eax)

    movl $0x10, %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ljmp $0x08, $.flush
.flush:
    ret
