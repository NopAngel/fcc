# FCC Generated Assembly
# Source: test/hello.c

.file "test/hello.c"
.text
.globl main
.type main, @function

main:
    # Prologue
    pushq %rbp
    movq %rsp, %rbp

    # Basic program body
    movl $10, %eax    # x = 10
    movl $20, %ebx    # y = 20
    addl %ebx, %eax  # z = x + y

    # Epilogue
    movl $0, %eax     # return 0
    popq %rbp
    ret

.size main, .-main
