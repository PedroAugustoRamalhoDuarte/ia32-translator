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

    push ebx
    push ecx
    push edx

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

    push edx
    push ecx
    push ebx

    dec eax; Devolve os caracteres lidos

    add esp, 4
    leave
    ret

EscreverString:
    enter 0,0
    pusha
    mov eax, 4
    mov ebx, 1
    mov ecx, [EBP + 12]
    mov edx, [EBP + 8]
    int 80h
    popa
    leave
    ret

LeerInteiro:
    enter 0,0
    push ebx
    push ecx
    push edx
    push edi

    mov eax, 3
    mov ebx, 0
    mov ecx, BUFFER_IN
    mov edx, BUFFER_IN_SIZE
    int 80h

    xor ecx, ecx
    xor eax, eax
    mov ebx, BUFFER_IN

    LoopLeerInteiro:
    mov dl, 0x0a
    cmp dl, [ebx + ecx]
    je ri32_cont
    push eax
    shl eax, 3
    add eax, [esp]
    add eax, [esp]
    mov dl, 0x2d
    cmp dl, [ebx + ecx]
    je sinal_negativo
    sub edx, edx
    mov dl, [ebx + ecx]
    sub edx, 0x30
    add eax, edx
    sinal_negativo:
    inc ecx
    jmp LoopLeerInteiro
    ri32_cont:
    mov dl, 0x2d
    cmp byte dl, [ebx]
    jne sinal_positivo
    push eax
    xor eax, eax
    sub eax, [esp]
    add esp, 4
    sinal_positivo:

    ; Coloca o valor de eax no endereço passado de parametro
    mov edx, [EBP+8]
    mov [edx], eax

    pop edi
    pop edx
    pop ecx
    pop ebx
    leave
    ret

; ====================================

EscreverInteiro:
    enter 0,0
    pusha
    xor eax, eax
    xor edx, edx
    xor ecx, ecx
    xor edi, edi
    mov ebx, BUFFER_IN
    mov eax, [ebp + 8]
    cmp eax, 0
    jne print_sinal_negativo
    mov dl, 0
    add dl, 0x30
    mov byte [ebx], dl
    mov dl, [ebx]
    inc ecx
    jmp print_contador3
    print_sinal_negativo:
    test eax, 0x80000000
    je print_sinal_positivo
    xor eax, eax
    sub eax, [ebp + 8]
    mov byte [ebx], 0x2d
    inc ebx
    mov edi, 1
    jmp PrintLoopLeerInteiro
    print_sinal_positivo:
    mov eax, [ebp + 8]
    PrintLoopLeerInteiro:
    xor edx, edx
    push ebx
    mov ebx, 10
    div ebx
    pop ebx
    cmp eax, 0
    jne print_contador
    cmp edx, 0
    je print_contador3
    print_contador:
    add edx, 0x30
    push ecx
    pi32_shift_r:
    cmp ecx, 0
    je print_contador2
    mov byte dh, [ebx + ecx - 1]
    mov byte [ebx + ecx], dh
    dec ecx
    jmp pi32_shift_r
    print_contador2:
    mov byte [ebx], dl
    pop ecx
    inc ecx
    jmp PrintLoopLeerInteiro
    print_contador3:
    cmp edi, 1
    jne print
    inc ecx
    dec ebx
    print:
    push ebx
    push ecx
    call EscreverString
    add esp, 8
    popa
    leave
    ret

PrintMensagem:
    enter 0,0

    push msg_init
    push 12
    call EscreverString

    push eax
    call EscreverInteiro

    push msg_end
    push 12
    call EscreverString


    leave
    ret