.section .data
.section .text
.global _start
_start:
    push %rbp	 #ALLOCATE STACK SPACE
    movq %rsp, %rbp
    addq $-4, %rsp
    call fun0_g
    addq $0, %rsp
    movl %eax, %eax   #HERE: MOVE LONG, LONG
    movq %rbp, %rdi
    movl %eax, -4(%rdi)
    movq %rax, %rdi
    movq $60, %rax
    syscall


.type fun0_g, @function
fun0_g:
    push %rbp	 #ALLOCATE STACK SPACE
    movq %rsp, %rbp
    subq $4, %rsp
    movl $3, %eax
    movl %eax, (%rsp)
    jmp endfun0_g
endfun0_g:
    movl (%rsp), %eax
    addq $4, %rsp
    movq %rbp, %rsp
    pop %rbp
    ret