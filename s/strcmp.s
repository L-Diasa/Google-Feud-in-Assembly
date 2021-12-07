.global _strcmpA                # int my_strcmpA(char *strg1, char *strg2)
_strcmpA:
pushl %ebp                      # save old %ebp
movl %esp, %ebp                 # set %ebp as frame pointer

WHILE:
    movl 8(%ebp), %eax          # eax = strg1
    cmpb $0,(%eax)              # compare *strg1 : '\0'
    je IF                       # if null jump to IF
    movl 12(%ebp), %ecx         # ecx = strg2
    cmpb $0,(%ecx)              # compare *strg2 : '\0'
    je IF                       # if null jump to IF
    movb (%ecx), %dl            # dl = *strg2
    cmpb (%eax), %dl            # compare *strg1 : *strg2
    jne ELSE                    # if not equal jump to ELSE

    incl 8(%ebp)                # strg1++
    incl 12(%ebp)               # strg2++
    jmp WHILE                   # jump to WHILE

IF:
    movl 8(%ebp), %eax          # eax = strg1
    movl 12(%ebp), %ecx         # ecx = strg2
    movb (%ecx), %dl            # dl = *strg2
    cmpb (%eax), %dl            # compare *strg1 : *strg2
    jne ELSE                    # if not equal jump to ELSE
    movl $1,%eax                # eax = 1 = return value
    jmp DONE                    # jump to DONE

ELSE:
    xorl %eax,%eax              # eax = 0 = return value

DONE:
    movl %ebp, %esp             # restore esp
    popl %ebp                   # and ebp
    ret                         # return

# equivalent c code:

# int strcmpC(char *strg1, char *strg2)
# {
#     while( ( *strg1 != '\0' && *strg2 != '\0' ) && *strg1 == strg2 )
#     {
#         strg1++;
#         strg2++;
#     }

#     if(strg1 == *strg2)
#        return 1;

#     else
#         return 0;
# }

