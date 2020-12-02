LeerChar:
    enter 0,0
    pusha
    mov eax, 3
    mov ebx, 0
    mov ecx, [EBP + 8]
    mov edx, 1
    int 80h
    popa
    leave
    ret

EscreverChar:
    enter 0,0
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, [EBP + 8]
    mov edx, 1
    int 80h
    popa
    leave
    ret

LeerString:
    enter 0,0
    pusha
    mov eax,0
    mov edx, [EBP + 8]
    add edx, 1 ; edx = Tamanho máximo da string + 1
LeerStringLoop:
    mov ecx,[EBP + 12]
    mov ebx,eax ; 0
    add ecx,ebx
    push ecx
    call LeerChar
    add esp,4
    inc eax
    cmp dword [ecx], 0xa ; Comparar com o enter
    je  LeerStringOut
    cmp eax, edx; Comparar com o tamanho
    jne LeerStringLoop
LeerStringOut:
    mov dword [ecx], 0
    popa
    add esp, 4
    leave
    ret

EscreverString:
    enter 0,0
    mov eax, 4
    mov ebx, 1
    mov ecx, [EBP + 12]
    mov edx, [EBP + 8]
    int 80h
    leave
    ret

LerInteiro:
    enter 0,0
    mov eax, 3 ; Leitura
    mov ebx, 0 ; STDIN
    mov ecx, [EBP + 8] ; Referência do ponteiro
    mov edx, 3 ; Tamanho em Bytes
    int 80h
    mov eax, [ecx + 2]; eax = '2''lixo'
    mov bl, al ; ebx =  char(2)
    sub ebx, '0'; ebx = 2
    mov eax, [ecx + 1]; eax = '5''lixo'
    mov dl, al ; edx = char(5)
    sub edx, '0'; edx = 5
    mov eax, 10
    imul edx;
    add ebx, eax;
    mov eax, [ecx]; eax = '1''lixo'
    mov dl, al ; edx = char(1)
    sub edx, '0'; edx = 1
    mov eax, 100
    imul edx; eax = 100
    add ebx, eax; ebx = 152
    leave
    ret 4

EscreverInteiro:
    enter 0,0
    mov eax, 4 ; Código de escrita
    mov ebx, 1
    mov ecx, [EBP + 8]
    mov edx, 3 ; Tamanho em Bytes
    int 80h
    leave
    ret 4