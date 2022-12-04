.686
.model flat,stdcall
option casemap:none

include WifiConnectLib.inc

.code

DllEntry proc hInst:HINSTANCE, reason:DWORD, reserved1:DWORD

    push    hInst
    pop     hInstance
	;invoke CreateClass
    mov     eax,TRUE
    ret

DllEntry Endp

WIFIInit PROC
	
	invoke WSAStartup, wVer,ADDR WSAData
	.if EAX!=NO_ERROR
		invoke MessageBox,NULL,_Text("WSAStartup baþlatýlamýyor!"),_Text("Hata"),MB_ICONERROR
		MOV EAX,0
		ret
	.ENDIF
	ret

WIFIInit endp

WIFIRemove PROC
	invoke	WSACleanup
WIFIRemove endp


WIFIClose PROC 

	invoke shutdown,hSocket,1
	invoke	closesocket,hSocket
	mov	hSocket,0
	ret

WIFIClose endp

WIFIConnect PROC hWndX:DWORD,IPAdr:DWORD ,PortW:DWORD
		
	invoke RtlZeroMemory,offset RemoteAddr,sizeof RemoteAddr
;	invoke inet_addr,IPAdr
;	.if	eax ==	INADDR_NONE
;		invoke MessageBox,hWndX,_Text("Geçersiz IP Adresi!"),_Text("Hata"),MB_ICONERROR
;		ret 
;	.endif
;	mov RemoteAddr.sin_addr,eax
	MOV ECX,IPAdr
	mov RemoteAddr.sin_addr,ecx
	MOV RemoteAddr.sin_family,AF_INET
	INVOKE htons,PortW
	MOV RemoteAddr.sin_port, AX
		
	invoke socket,AF_INET, SOCK_STREAM,IPPROTO_TCP
		.if EAX==INVALID_SOCKET
			invoke WSACleanup
			invoke MessageBox,hWndX,_Text("Soket hatasý var!"),_Text("Hata"),MB_ICONERROR
			MOV EAX,0
			ret
		.ENDIF
	mov hSocket,eax
	
	
	invoke connect,hSocket,addr RemoteAddr,sizeof  RemoteAddr
	.if EAX==0
		MOV EAX,TRUE
	.else
			
	.endif
;	.if	eax ==	SOCKET_ERROR
;			invoke	WSAGetLastError
;			
;			.if eax != WSAEWOULDBLOCK
;				invoke	closesocket,hSocket
;				mov	hSocket,0
;				mov eax,FALSE
;				ret
;			.endif
;		.endif
;		
	
		
	MOV EAX,TRUE
	
	ret


WIFIConnect endp


WIFIDisconnect PROC 

	.if hSocket!=INVALID_SOCKET
		invoke shutdown,hSocket,1
		invoke closesocket,hSocket
		MOV eax,TRUE
	.else
		MOV EAX,FALSE
	.endif
					
	ret

WIFIDisconnect endp

WIFIGetData PROC
	
	
	ret

WIFIGetData endp

WIFIPutData PROC  lampData:DWORD
	
	invoke lstrcpy, addr bilgi.name_,lampData
	invoke send,hSocket,addr bilgi,sizeof bilgi,0
	
	ret

WIFIPutData endp

End DllEntry
