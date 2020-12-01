LeerChar:
    enter 0,0
    mov eax, 3
    mov ebx, 0
    mov ecx, [EBP + 8]
    mov edx, 1
    int 80h
    leave
    ret 4

EscreverChar:
    enter 0,0
    mov eax, 4
    mov ebx, 1
    mov ecx, [EBP + 8]
    mov edx, 1
    int 80h
    leave
    ret 4