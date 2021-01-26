; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSreenServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SreenServer.h"

ClassCount=5
Class1=CSreenServerApp
Class2=CSreenServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CListenSock
Class5=CClientSock
Resource3=IDD_SREENSERVER_DIALOG

[CLS:CSreenServerApp]
Type=0
HeaderFile=SreenServer.h
ImplementationFile=SreenServer.cpp
Filter=N

[CLS:CSreenServerDlg]
Type=0
HeaderFile=SreenServerDlg.h
ImplementationFile=SreenServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CSreenServerDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=SreenServerDlg.h
ImplementationFile=SreenServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SREENSERVER_DIALOG]
Type=1
Class=CSreenServerDlg
ControlCount=6
Control1=IDC_BUTTON_START,button,1342242816
Control2=IDC_BUTTON_SAVEBMP,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_TCPPORT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_FILENAME,edit,1350631552

[CLS:CListenSock]
Type=0
HeaderFile=ListenSock.h
ImplementationFile=ListenSock.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CListenSock

[CLS:CClientSock]
Type=0
HeaderFile=ClientSock.h
ImplementationFile=ClientSock.cpp
BaseClass=CSocket
Filter=N
LastObject=CClientSock
VirtualFilter=uq

