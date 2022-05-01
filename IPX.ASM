
;-------------------------------------------------------------------------------
; Copyright (c) David Welch, 1995
;-------------------------------------------------------------------------------

.model large
.data
public _ipxentry
_ipxentry dd 0

.code

public _reverseword
_reverseword:
    push bp
    mov bp,sp
    mov ax,[bp+6]
    xchg ah,al
    pop bp
    retf

public _ipxinit
_ipxinit:
    push di
    push es
    mov ax,7A00h
    int 2Fh
    cmp al,0FFh
    jnz _ipxinit0
    mov word ptr [_ipxentry+0],di
    mov word ptr [_ipxentry+2],es
_ipxinit0:
    mov dx,word ptr [_ipxentry+2]
    mov ax,word ptr [_ipxentry+0]
    pop es
    pop di
    retf

public _ipxgetaddress
_ipxgetaddress:
    push bp
    mov bp,sp
    mov bx,0009h
    mov si,[bp+6]
    mov es,[bp+8]
    call [_ipxentry]
    pop bp
    retf

public _ipxgetmaxpacketsize
_ipxgetmaxpacketsize:
    mov bx,001Ah
    call [_ipxentry]
    retf

public _ipxopensocket
_ipxopensocket:
    push bp
    mov bp,sp
    push ds
    mov al,[bp+6]
    mov bx,[bp+8]
    mov ds,[bp+10]
    mov dx,[bx]
    pop ds
    mov bx,0000h
    call [_ipxentry]
    push ds
    mov bx,[bp+8]
    mov ds,[bp+10]
    mov [bx],dx
    mov ah,00h
    pop ds
    pop bp
    retf

public _ipxclosesocket
_ipxclosesocket:
    push bp
    mov bp,sp
    mov bx,0001h
    mov dx,[bp+6]
    call [_ipxentry]
    pop bp
    retf

public _ipxlistenforpacket
_ipxlistenforpacket:
    push bp
    mov bp,sp
    push si
    push es
    mov bx,0004h
    mov si,[bp+6]
    mov es,[bp+8]
    call [_ipxentry]
    mov ah,00h
    pop es
    pop si
    pop bp
    retf

public _ipxsendpacket
_ipxsendpacket:
    push bp
    mov bp,sp
    push si
    push es
    mov bx,0003h
    mov si,[bp+6]
    mov es,[bp+8]
    call [_ipxentry]
    pop es
    pop si
    pop bp
    retf

public _ipxrelenquishcontrol
_ipxrelenquishcontrol:
    mov bx,000Ah
    call [_ipxentry]
    retf

end

;-------------------------------------------------------------------------------
; Copyright (c) David Welch, 1995
;-------------------------------------------------------------------------------

