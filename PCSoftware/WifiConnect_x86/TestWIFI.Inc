
include windows.inc
include kernel32.inc
include user32.inc
include Comctl32.inc
include shell32.inc


includelib kernel32.lib
includelib user32.lib
includelib Comctl32.lib
includelib shell32.lib
includelib WifiConnectLib.lib


DlgProc			PROTO	:HWND,:UINT,:WPARAM,:LPARAM
WIFIConnect 	PROTO 	:DWORD,:DWORD,:DWORD
WIFIInit		PROTO	
WIFIRemove		PROTO
WIFIClose		PROTO
WIFIPutData		PROTO :DWORD


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


.const
	IDD_DIALOG1				equ 101
	IDC_IPDATA				equ	4000
	IDC_PORTDATA			equ	4001
	IDC_CONNECTBTN			equ	4002
	LED1					equ	4003
	LED2					equ	4004
	LED3					equ	4005
	STATUS_CONNECT			equ	4006
.data
	dwPort      dd 		8090
	buffer		db		254 dup(?)
		
	
.data?
	hInstance			dd 			?
	hIPCtrl				DWORD		?
	sonuc				DB			?
	InitCtrls			INITCOMMONCONTROLSEX		<>
	IPAddrBuff	DD		?
	IPAdr		DD		?