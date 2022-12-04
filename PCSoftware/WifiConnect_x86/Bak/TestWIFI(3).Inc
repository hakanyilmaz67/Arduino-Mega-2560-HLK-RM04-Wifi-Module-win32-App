
include windows.inc
include kernel32.inc
include user32.inc
include Comctl32.inc
include shell32.inc
;include wsock32.inc
;include ws2_32.inc



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





literal MACRO quoted_text:VARARG
        LOCAL local_text
        .data
          local_text db quoted_text,0
        align 4
        .code
        EXITM <local_text>
      ENDM
    ; --------------------------------
    ; string address in INVOKE format
    ; --------------------------------
      SADD MACRO quoted_text:VARARG
        EXITM <ADDR literal(quoted_text)>
      ENDM
    ; --------------------------------
    ; string OFFSET for manual coding
    ; --------------------------------
      CTXT MACRO quoted_text:VARARG
        EXITM <offset literal(quoted_text)>
      ENDM

    ; -----------------------------------------------------
    ; string address embedded directly in the code section
    ; -----------------------------------------------------
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


FIRST_IPADDRESS macro x
	exitm <(( x  shr  24 )  and ( 0ffh ) )>
	endm
SECOND_IPADDRESS macro x
	exitm <( ( x  shr  16 )  and  (0ffh ) )>
	endm
THIRD_IPADDRESS macro x
	exitm <( ( x  shr  8 )  and ( 0ffh ) ) >
	endm
FOURTH_IPADDRESS macro x
	exitm <( x  and  0ffh ) >
	endm





.const
	IDD_DIALOG1				equ 101
	IDC_IPDATA				equ	4000
	IDC_PORTDATA			equ	4001
	IDC_CONNECTBTN			equ	4002
	LED1					equ	4003
	LED2					equ	4004
	LED3					equ	4005
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