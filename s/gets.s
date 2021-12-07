.extern "C" _getchar

.global _getsA              # char* getsA(char* s)
_getsA:
    pushl %ebp              # save old %ebp
    movl %esp, %ebp         # set %ebp as frame pointer
    subl $4, %esp           # allocate 4 bytes on stack
    pushl %ebx              # save callee save register %ebx

    movl 8(%ebp),%ecx       # ecx = address
    movl %ecx, -4(%ebp)     # -4(%ebp) = *dest = curr address
    movl $0, %ebx           # ebx = gotchar = 0

WHILE:
    call _getchar           # eax = c = getchar()

    cmpl $10, %eax          # eax - 10 = 0 ? => compare c to '\n'
    je ADDNULL              # if '\n' jump to ADDNULL

    testl %eax, %eax        # eax & eax => eax = 0 ? => compare c to EOF
    je ADDNULL              # if null jump to ADDNULL

    movl -4(%ebp), %ecx     # ecx = curr address
    movb %al, (%ecx)        # *dest = c
    incl -4(%ebp)           # *dest++

    movl $1, %ebx           # edx = gotchar = 1
    jmp WHILE               # jump to WHILE

ADDNULL:
    movl -4(%ebp), %ecx     # ecx = curr address
    movb $0, (%ecx)         # *dest = '\0'
    incl -4(%ebp)           # *dest++

IF:
    testl %eax, %eax        # eax & eax => eax = 0 ? => compare c to EOF
    jne RETURNS             # if not null jump to RETURNS
    testl %ebx, %ebx        # edx & edx => edx = 0 ? => compare gotchar to zero
    jne RETURNS             # if gotchar jump to RETURNS
    xorl %eax, %eax         # eax = null = return value

DONE:
    leal -8(%ebp),%esp      # restore %esp
    popl %ebx               # restore %ebx
    addl $4, %esp           # deallocate 4 bytes from stack
    popl %ebp               # restore %ebp
    ret                     # return result

RETURNS:
    movl 8(%ebp), %eax      # get address in eax, eax = s = return value
    jmp DONE                # jump to DONE


# equivalent c++ code:

# char* getsCPP(char *s) {
#     int c;
#    char *dest = s;
#    int gotchar = 0;
#    while ((c = getchar()) != '\n' && c != EOF) {
#         *dest++ = c;
#          gotchar = 1;
#    }
#    *dest++ = '\0';
#    if (c == EOF && !gotchar)
#        return NULL;
#    return s;
#}

