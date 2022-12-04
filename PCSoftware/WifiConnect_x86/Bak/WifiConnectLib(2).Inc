include windows.inc
include user32.inc
include kernel32.inc
include comctl32.inc
include wsock32.inc
include ws2_32.inc
include RADbg.inc

includelib user32.lib
includelib kernel32.lib
includelib comctl32.lib
includelib wsock32.lib
includelib ws2_32.lib



literal MACRO quoted_text:VARARG
        LOCAL local_text
        .data
          local_text db quoted_text,0
        align 4
        .code
        EXITM <local_text>
      ENDM
 
      SADD MACRO quoted_text:VARARG
        EXITM <ADDR literal(quoted_text)>
      ENDM

      CTXT MACRO quoted_text:VARARG
        EXITM <offset literal(quoted_text)>
      ENDM

      CADD MACRO quoted_text:VARARG
        LOCAL vname,lbl
          jmp lbl
            vname db quoted_text,0
          align 4
          lbl:
        EXITM <ADDR vname>
      ENDM


 _Text macro p1, p2
      local l
        ifb <p2>; ?????? ??? ?????
            .data
                l   db p1, 0
            .code
            exitm   <addr l>
       else    ; ?????? ? ??????
            .data
                l   db p1, 0
            .code
            exitm   <offset l>
        endif
    endm
    
LOWORD	MACRO 	bigword	;; Retrieves the low word from double word argument

	mov	eax,bigword
	and	eax,0FFFFh	;; Set to low word 
	ENDM

HIWORD	MACRO   bigword	;; Retrieves the high word from double word argument

	mov	ebx,bigword
	shr	ebx,16		;; Shift 16 for high word to set to high word
				
	ENDM
	
MAKEIPADDRESS macro b1,b2,b3,b4
	exitm <( ( ( ( b1 )  shl  24 ) + ( ( b2 )  shl  16 ) + ( ( b3 )  shl  8 ) + ( ( b4 ) ) ) ) >	
endm	
	
INFO struct
	id 	DD	?
	name_	db 45	dup(?)
INFO ends

.const
wVer							equ	0202h
WM_SOCKET						equ WM_USER+100

WSABASEERR              		EQU	10000
WSAEINTR               	 		EQU (WSABASEERR+4)
WSAEBADF                		EQU (WSABASEERR+9)
WSAEACCES               		EQU (WSABASEERR+13)
WSAEFAULT               		EQU (WSABASEERR+14)
WSAEINVAL               		EQU (WSABASEERR+22)
WSAEMFILE               		EQU (WSABASEERR+24)
WSAEWOULDBLOCK          		EQU	(WSABASEERR+35)
WSAEINPROGRESS          		EQU	(WSABASEERR+36)
WSAEALREADY             		EQU	(WSABASEERR+37)
WSAENOTSOCK             		EQU	(WSABASEERR+38)
WSAEDESTADDRREQ         		EQU	(WSABASEERR+39)
WSAEMSGSIZE             		EQU	(WSABASEERR+40)
WSAEPROTOTYPE           		EQU (WSABASEERR+41)
WSAENOPROTOOPT          		EQU	(WSABASEERR+42)
WSAEPROTONOSUPPORT      		EQU	(WSABASEERR+43)
WSAESOCKTNOSUPPORT      		EQU	(WSABASEERR+44)
WSAEOPNOTSUPP           		EQU	(WSABASEERR+45)
WSAEPFNOSUPPORT         		EQU	(WSABASEERR+46)
WSAEAFNOSUPPORT         		EQU	(WSABASEERR+47)
WSAEADDRINUSE           		EQU	(WSABASEERR+48)
WSAEADDRNOTAVAIL        		EQU	(WSABASEERR+49)
WSAENETDOWN             		EQU	(WSABASEERR+50)
WSAENETUNREACH          		EQU	(WSABASEERR+51)
WSAENETRESET            		EQU	(WSABASEERR+52)
WSAECONNABORTED         		EQU	(WSABASEERR+53)
WSAECONNRESET           		EQU	(WSABASEERR+54)
WSAENOBUFS              		EQU	(WSABASEERR+55)
WSAEISCONN              		EQU	(WSABASEERR+56)
WSAENOTCONN             		EQU	(WSABASEERR+57)
WSAESHUTDOWN            		EQU	(WSABASEERR+58)
WSAETOOMANYREFS         		EQU	(WSABASEERR+59)
WSAETIMEDOUT            		EQU	(WSABASEERR+60)
WSAECONNREFUSED         		EQU	(WSABASEERR+61)
WSAELOOP                		EQU	(WSABASEERR+62)
WSAENAMETOOLONG         		EQU	(WSABASEERR+63)
WSAEHOSTDOWN            		EQU	(WSABASEERR+64)
WSAEHOSTUNREACH         		EQU (WSABASEERR+65)
WSAENOTEMPTY            		EQU	(WSABASEERR+66)
WSAEPROCLIM             		EQU	(WSABASEERR+67)
WSAEUSERS               		EQU	(WSABASEERR+68)
WSAEDQUOT               		EQU	(WSABASEERR+69)
WSAESTALE               		EQU	(WSABASEERR+70)
WSAEREMOTE              		EQU	(WSABASEERR+71)
WSAEDISCON              		EQU	(WSABASEERR+101)

WSASYSNOTREADY          		EQU	(WSABASEERR+91)
WSAVERNOTSUPPORTED				EQU (WSABASEERR+92)
WSANOTINITIALISED       		EQU	(WSABASEERR+93)

WSAHOST_NOT_FOUND				EQU (WSABASEERR+1001)
HOST_NOT_FOUND 					EQU  WSAHOST_NOT_FOUND
WSATRY_AGAIN 					EQU (WSABASEERR+1002)
TRY_AGAIN						EQU  WSATRY_AGAIN
WSANO_RECOVERY 					EQU (WSABASEERR+1003)
NO_RECOVERY             		EQU	 WSANO_RECOVERY
WSANO_DATA              		EQU	(WSABASEERR+1004)
NO_DATA                 		EQU	WSANO_DATA
WSANO_ADDRESS           		EQU	WSANO_DATA
NO_ADDRESS              		EQU WSANO_ADDRESS

.data 
	dwPort      dd 		8090
	buffer		db		254 dup(?)
	hSocket		DD			0


.data?
	hInstance			dd 			?
	;hSocket				DD			?
	hClient				DD			?
	WSAData     		WSADATA 	<>
	SockAddrIn  		sockaddr_in <>
	RemoteAddr			sockaddr_in <>
	pBuf				db 			2048		dup(?)
	pAddrIP				DD			?
	bilgi				INFO<>
	hIPCtrl				DWORD		?
	sonuc				DB			?


	
