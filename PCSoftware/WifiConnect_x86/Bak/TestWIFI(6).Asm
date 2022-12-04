.686
.model flat, stdcall  ;32 bit memory model
option casemap :none  ;case sensitive

include TestWIFI.inc
include RADbg.inc



.code

start:

	invoke GetModuleHandle,NULL
	mov		hInstance,eax
	invoke 	WIFIInit
	
	mov InitCtrls.dwSize, sizeof InitCtrls
	mov InitCtrls.dwICC, ICC_STANDARD_CLASSES OR ICC_WIN95_CLASSES OR ICC_INTERNET_CLASSES
	invoke InitCommonControlsEx, addr InitCtrls	
    invoke InitCommonControls
	invoke 	DialogBoxParam,hInstance,IDD_DIALOG1,NULL,addr DlgProc,NULL
	invoke  WIFIRemove
	invoke 	ExitProcess,0

ActivateLEDS PROC hWin:DWORD
	invoke GetDlgItem,hWin,LED1
	invoke EnableWindow,EAX,TRUE
	invoke GetDlgItem,hWin,LED2
	invoke EnableWindow,EAX,TRUE
	invoke GetDlgItem,hWin,LED3
	invoke EnableWindow,EAX,TRUE
	ret

ActivateLEDS endp

PasifLEDS PROC hWin:DWORD
	invoke GetDlgItem,hWin,LED1
	invoke EnableWindow,EAX,FALSE
	invoke GetDlgItem,hWin,LED2
	invoke EnableWindow,EAX,FALSE
	invoke GetDlgItem,hWin,LED3
	invoke EnableWindow,EAX,FALSE
	ret

PasifLEDS endp


GetIPAdressData	PROC hWin:DWORD
	
	invoke SendDlgItemMessage,hWin,IDC_IPDATA,IPM_GETADDRESS,0,offset IPAdr
	.if EAX==4
		MOV EAX,IPAdr
		bswap eax
	.else
		MOV eax,0
	.endif
	


	ret

GetIPAdressData endp

GetPortData	PROC hWin:DWORD
LOCAL PortX:DWORD
	
	invoke GetDlgItemInt,hWin,IDC_IPDATA,0, 0
	
	
	ret

GetPortData endp



DlgProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	mov		eax,uMsg
	.if eax==WM_INITDIALOG
		invoke SendDlgItemMessage,hWin,IDC_IPDATA,IPM_SETADDRESS,0,MAKEIPADDRESS(192,168,43,128)
		invoke SetDlgItemText,hWin,IDC_PORTDATA,_Text("8090")
	
	.elseif eax==WM_COMMAND
		mov eax,wParam
		.if AX==IDC_CONNECTBTN
			invoke SendDlgItemMessage,hWin,IDC_CONNECTBTN,BM_GETCHECK,0,0
		  	.if EAX
		  		invoke GetIPAdressData,hWin
		  		MOV ESI,eax
		  		invoke GetPortData,hWin
		  		
		  		
		  		invoke WIFIConnect,hWin,esi,8090	
		  		.if (EAX>0)
		 			invoke ActivateLEDS,hWin
		 			invoke SendDlgItemMessage,hWin,IDC_CONNECTBTN,WM_SETTEXT,0,_Text("Kapat")
		 			invoke SetDlgItemText,hWin,STATUS_CONNECT,_Text("Baðlandý")
		 		.else
		 			invoke PasifLEDS,hWin
		 			invoke WIFIClose
		 			invoke SendDlgItemMessage,hWin,IDC_CONNECTBTN,WM_SETTEXT,0,_Text("Baðlan")
		 			invoke SetDlgItemText,hWin,STATUS_CONNECT,_Text("Baðlandý Yok")
		 		.endif
;		 		
		  	.else
		  		invoke PasifLEDS,hWin
		  		invoke WIFIPutData,CTXT("A0") 
		  		invoke WIFIPutData,CTXT("B0") 
		  		invoke WIFIPutData,CTXT("C0") 
		  		invoke WIFIClose
		  		invoke SendDlgItemMessage,hWin,IDC_CONNECTBTN,WM_SETTEXT,0,_Text("Baðlan")
		  		invoke SetDlgItemText,hWin,STATUS_CONNECT,_Text("Baðlandý Yok")
		  		
		  	.endif
		.elseif AX==LED1
			invoke SendDlgItemMessage,hWin,LED1,BM_GETCHECK,0,0
			.if EAX
				invoke WIFIPutData,CTXT("A1") 
			.else
				invoke WIFIPutData,CTXT("A0") 
			.endif
			
			
		.elseif AX==LED2
			invoke SendDlgItemMessage,hWin,LED2,BM_GETCHECK,0,0
			.if EAX
				invoke WIFIPutData,CTXT("B1") 
			.else
				invoke WIFIPutData,CTXT("B0") 
			.endif
		
		
		.elseif AX==LED3
			invoke SendDlgItemMessage,hWin,LED3,BM_GETCHECK,0,0
			.if EAX
				invoke WIFIPutData,CTXT("C1") 
			.else
				invoke WIFIPutData,CTXT("C0") 
			.endif
		.endif	
	
	
	
	.elseif eax==WM_CLOSE
		invoke WIFIClose
		invoke EndDialog,hWin,0
	.else
		mov		eax,FALSE
		ret
	.endif
	mov		eax,TRUE
	ret

DlgProc endp



end start
