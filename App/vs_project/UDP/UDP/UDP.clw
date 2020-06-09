; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUDPDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "UDP.h"

ClassCount=4
Class1=CUDPApp
Class2=CUDPDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CUdpSocket
Resource3=IDD_UDP_DIALOG

[CLS:CUDPApp]
Type=0
HeaderFile=UDP.h
ImplementationFile=UDP.cpp
Filter=N

[CLS:CUDPDlg]
Type=0
HeaderFile=UDPDlg.h
ImplementationFile=UDPDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_DATATOSEND

[CLS:CAboutDlg]
Type=0
HeaderFile=UDPDlg.h
ImplementationFile=UDPDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_UDP_DIALOG]
Type=1
Class=CUDPDlg
ControlCount=11
Control1=IDC_BTNSENDDATA,button,1476460544
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PEERPORTNUM,edit,1350631552
Control5=IDC_PEERIPADDR,SysIPAddress32,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_LOCALPORTNUM,edit,1350631552
Control9=IDC_LOCALIPADDR,SysIPAddress32,1342242816
Control10=IDC_BTNCTRLCONN,button,1342242816
Control11=IDC_DATATOSEND,edit,1484849280

[CLS:CUdpSocket]
Type=0
HeaderFile=UdpSocket.h
ImplementationFile=UdpSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CUdpSocket
VirtualFilter=uq

