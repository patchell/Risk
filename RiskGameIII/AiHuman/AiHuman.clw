; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COccupy
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "aihuman.h"
LastPage=0

ClassCount=6
Class1=CAiHumanApp
Class2=CAttackDlg
Class3=CChoseDlg
Class4=CDefendDlg
Class5=CPlaceDlg

ResourceCount=5
Resource1=IDD_DIALOG_DEFEND
Resource2=IDD_DIALOG_PLACE
Resource3=IDD_DIALOG_ATTACK
Resource4=IDD_DIALOG_CHOOSE
Class6=COccupy
Resource5=IDD_DIALOG_OCCUPY

[CLS:CAiHumanApp]
Type=0
BaseClass=CWinApp
HeaderFile=AiHuman.h
ImplementationFile=AiHuman.cpp

[CLS:CAttackDlg]
Type=0
BaseClass=CDialog
HeaderFile=AttackDlg.h
ImplementationFile=AttackDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_ATTACK_STRAT

[CLS:CChoseDlg]
Type=0
BaseClass=CDialog
HeaderFile=ChoseDlg.h
ImplementationFile=ChoseDlg.cpp

[CLS:CDefendDlg]
Type=0
BaseClass=CDialog
HeaderFile=DefendDlg.h
ImplementationFile=DefendDlg.cpp
LastObject=CDefendDlg

[CLS:CPlaceDlg]
Type=0
BaseClass=CDialog
HeaderFile=PlaceDlg.h
ImplementationFile=PlaceDlg.cpp
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOG_ATTACK]
Type=1
Class=CAttackDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHECK_ATTACK_SURRENDER,button,1342242819
Control4=IDC_COMBO_ATTACK_STRAT,combobox,1344340226

[DLG:IDD_DIALOG_CHOOSE]
Type=1
Class=CChoseDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_PLACE]
Type=1
Class=CPlaceDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC_PLACE_ARMIES,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_PLACE_ARMIES,edit,1350631552
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_DEFEND]
Type=1
Class=CDefendDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG_OCCUPY]
Type=1
Class=COccupy
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDC_STATIC_OCCUPY,static,1350696960
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:COccupy]
Type=0
HeaderFile=Occupy.h
ImplementationFile=Occupy.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

