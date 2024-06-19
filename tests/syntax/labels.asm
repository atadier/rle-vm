# test with labels
        mov r0, 1
label1: add r0, 1
label2: cmp r0, 5
        jne label1
        sub r0, 2
        cmp r0, 0
        jge label2
