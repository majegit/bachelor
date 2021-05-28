.section .data
.section .text
.global _start
_start:
    push %rbp	 #ALLOCATE STACK SPACE
    movq %rsp, %rbp
    addq $-8, %rsp
    subq $1, %rsp
    movb $1, %al
    movb %al, (%rsp)
    call printBOOLEAN
    addq $1, %rsp
    call printNewline
    subq $1, %rsp
    movb $0, %al
    movb %al, (%rsp)
    call printBOOLEAN
    addq $1, %rsp
    call printNewline
    subq $4, %rsp
    movl $-1212, %eax
    movl %eax, (%rsp)
    call printINT
    addq $4, %rsp
    call printNewline
    movq doubleconst_0, %rax
    push %rax
    call printDOUBLE
    addq $8, %rsp
    call printNewline
    subq $4, %rsp
    movl $0, %eax
    movl %eax, (%rsp)
    cvtsi2sd (%rsp), %xmm0
    addq $4, %rsp
    movq %xmm0, %rax
    push %rax
    pop %rax
    movq %rax, %rax
    movq %rax, %rax
    movq %rax, -8(%rbp)
    movq %rbp, %rdi
    movq -8(%rdi), %rax
    push %rax
    call printDOUBLE
    addq $8, %rsp
    call printNewline
    movq %rax, %rdi
    movq $60, %rax
    syscall

doubleconst_0:
    .long 858993459
    .long 1079202611

.type printBOOLEAN, @function
printBOOLEAN:
    movq $1, %rax
    movq $1, %rdi
    cmpb $1, 8(%rsp)
    je printBOOLEANtrue
    movq $0x00000065736c6166, %rbx
    push %rbx
    movq $5, %rdx
    jmp printBOOLEANend
printBOOLEANtrue:
    push $0x65757274
    movq $4, %rdx
printBOOLEANend:
    movq %rsp, %rsi
    syscall
    addq $8, %rsp
    ret

.type printINT, @function
printINT:
    xor %rdx, %rdx
    xor %r10, %r10   #counter
    movq $10, %r12  #divisor
    movl 8(%rsp), %eax  #int stored here
    cmpl $0, %eax
    jg printINTpushDecimals
    je printINTzero
    push %rax   #Save int
    push $45    #Push '-'
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall     #Print '-'
    addq $8, %rsp
    pop %rax    #Restore int
    cltq
    neg %rax
    jmp printINTpushDecimals
printINTzero:
    push $48    #Push '0'
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall     #Print '0'
    addq $8, %rsp
    jmp printINTend
printINTpushDecimals:
    cmpl $0, %eax
    je printINTprint
    movl $0, %edx   #Positive sign extension
    idivl %r12d
    addq $48, %rdx
    push %rdx
    inc %r10
    jmp printINTpushDecimals
printINTprint:
    cmp $0, %r10
    je printINTend
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall
    dec %r10
    addq $8, %rsp
    jmp printINTprint
printINTend:
    ret

.type printDOUBLE, @function
printDOUBLE:
    movq 8(%rsp), %rbx  #Double stored here
    cmp $0, %rbx        #If double is 0, just print 0
    jg printDOUBLEpos
    je printDOUBLEzero
    push $45            #Push '-'
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall             #Print '-'
    addq $8, %rsp
    jmp printDOUBLEpos
printDOUBLEzero:
    push $48            #Push '0'
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall             #Print '0'
    addq $8, %rsp
    ret
printDOUBLEpos:
    push $0x5e3228      #Push "(2^"
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $3, %rdx
    syscall             #Print "(2^"
    addq $8, %rsp
    shr $52, %rbx       #Push out mantissa
    and $0x7ff, %rbx    #Set sign bit to 0,
                        #Now the biased exponent is in lower 11 bits of rbx
    subl $1023, %ebx    #Subtract bias from exponent
    subq $4, %rsp       #Push the unbiased exponent on stack and print it
    movl %ebx, (%rsp)
    call printINT
    addq $4, %rsp

    push $0x29          #Print ')'
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall             #Print ')'
    addq $8, %rsp

    movq 8(%rsp), %rbx  #Double stored in RBX again
    and _dc_getMantissa, %rbx   #Only mantissa is left in rbx
    cmp $0, %rbx        #If mantissa = 0
    je printDOUBLEend   #Then dont print fractional part
    push $0x2e312a      #Push "*1."
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $3, %rdx
    syscall             #Print "*1."
    addq $8, %rsp

    or _dc_exp1023, %rbx        #set the exponent to 1023
    movq %rbx, %xmm0
    addsd _dc_neg1, %xmm0       #add -1 to xmm0
    movq $10, %rbx              #Counter = 10
printDOUBLEloop:
    comisd _dc_0, %xmm0
    je printDOUBLEend
    mulsd _dc_10, %xmm0         #multiply fraction by 10
    comisd _dc_1, %xmm0         #Check if fraction < 1
    jb printDOUBLEpushZero      #Print zero
    cvttsd2si %xmm0, %rax       #Get the integer part
    cvtsi2sd %rax, %xmm1
    subsd %xmm1, %xmm0
    addq $48, %rax
    push %rax
    jmp printDOUBLEprint
printDOUBLEpushZero:
    push $48
printDOUBLEprint:
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall
    addq $8, %rsp
    dec %rbx
    cmp $0, %rbx
    jne printDOUBLEloop
printDOUBLEend:
    ret

_dc_0:
    .long 0x00000000
    .long 0x00000000

_dc_1:
    .long 0x00000000
    .long 0x3ff00000

_dc_getMantissa:
    .long 0xffffffff
    .long 0x000fffff

_dc_exp1023:
    .long 0x00000000
    .long 0x3ff00000

_dc_neg1:
    .long 0x00000000
    .long 0xbff00000

_dc_10:
    .long 0x00000000
    .long 0x40240000

.type printNewline, @function
printNewline:
    push $10
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall
    addq $8, %rsp
    ret
