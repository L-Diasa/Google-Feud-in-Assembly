.extern "C" _strcmpA
.extern "C" _strlen

.global _checkA             # int checkA(char *strg1, char *strg2);
_checkA:
    pushl %ebp              # save old %ebp
    movl %esp, %ebp         # set %ebp as frame pointer
    pushl %ebx              # save callee save register %ebx
    pushl %edi              # save callee save register %edi

    movl 8(%ebp),%ecx       # ecx = curr word
    movl $1, %edi           # edi = ans index + 1 = i = 1
    movl $10, %ebx          # ebx = max edi = 10

COMP:
    pushl 12(%ebp)          # pass the first param
    pushl %ecx              # pass the second param
    call _strcmpA           # compare strings
    popl %ecx               # restore ecx
    leal 4(%esp),%esp       # restore esp

    cmpl $0, %eax           # check if guess was right
    jne FOUND               # if it was jump to FOUND

    cmpl %ebx, %edi         # check if it was the last word
    je NOTFOUND             # if it was jump to NOTFOUND
    incl %edi               # i++

    pushl %ecx              # pass the curr word
    call _strlen            # compute length
    popl %ecx               # restore ecx
    incl %eax               # length++
    addl %eax, %ecx         # ecx = next word
    jmp COMP                # jump to COMP

NOTFOUND:
    xorl %eax, %eax         # %eax = 0 = return value
    jmp DONE                # jump to DONE

FOUND:
    movl %edi, %eax         # %eax = i

DONE:
    leal -8(%ebp),%esp      # restore %esp
    popl %edi               # restore %ebx
    popl %ebx               # restore %ebx
    popl %ebp               # and ebp
    ret                     # return

