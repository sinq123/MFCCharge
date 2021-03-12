; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyComboBox
LastTemplate=CComboBox
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TestC.h"

ClassCount=5
Class1=CTestCApp
Class2=CTestCDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMyListCtrl
Class5=CMyComboBox
Resource3=IDD_TESTC_DIALOG

[CLS:CTestCApp]
Type=0
HeaderFile=TestC.h
ImplementationFile=TestC.cpp
Filter=N

[CLS:CTestCDlg]
Type=0
HeaderFile=TestCDlg.h
ImplementationFile=TestCDlg.cpp
Filter=D
LastObject=IDC_LIST2
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=TestCDlg.h
ImplementationFile=TestCDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TESTC_DIALOG]
Type=1
Class=CTestCDlg
ControlCount=1
Control1=IDC_LIST2,SysListView32,1350631425

[CLS:CMyListCtrl]
Type=0
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC

[CLS:CMyComboBox]
Type=0
HeaderFile=MyComboBox.h
ImplementationFile=MyComboBox.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC

