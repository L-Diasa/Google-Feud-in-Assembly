.global _incA            # void incA(int* p, int val);
_incA:
push     %ebp            # save old %ebp
movl     %esp,%ebp       # set %ebp as frame pointer

movl     8(%ebp),%eax    # eax = p
movl     12(%ebp), %edx  # edx = a
testl    %eax, %eax      # eax & eax => check if p is null
je       done            # if null jump to done
testl    %edx, %edx      # edx & edx => if a = 0
jle      done            # if less than or equal jump to done
addl     %edx, (%eax)    # eax = *p + a

done:
movl %ebp, %esp          # restore esp
popl %ebp                # and ebp
ret                      # return


# equivalent c code:

# void incC(int a, int *p) {
#     if (p && a > 0)
#     *p += a;
# }
