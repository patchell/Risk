; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRiskGameDoc
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "riskgame.h"
LastPage=0

ClassCount=10
Class1=CHorzScrollBar
Class2=CMainFrame
Class3=CNumEdit
Class4=CPlayerSetupDlg
Class5=CRiskGameApp
Class6=CAboutDlg
Class7=CRiskGameDoc
Class8=CRiskGameView
Class9=CStaticBitmap

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDD_DIALOG_AIPARAMS
Resource3=IDD_SETUP_PLAYERS_DLG
Class10=CAiParamEditDlg
Resource4=IDR_MAINFRAME

[CLS:CHorzScrollBar]
Type=0
BaseClass=CScrollBar
HeaderFile=HorzScrollBar.h
ImplementationFile=HorzScrollBar.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CNumEdit]
Type=0
BaseClass=CEdit
HeaderFile=NumEdit.h
ImplementationFile=NumEdit.cpp

[CLS:CPlayerSetupDlg]
Type=0
BaseClass=CDialog
HeaderFile=PlayerSetupDlg.h
ImplementationFile=PlayerSetupDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=CPlayerSetupDlg

[CLS:CRiskGameApp]
Type=0
BaseClass=CWinApp
HeaderFile=RiskGame.h
ImplementationFile=RiskGame.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=RiskGame.cpp
ImplementationFile=RiskGame.cpp

[CLS:CRiskGameDoc]
Type=0
BaseClass=CDocument
HeaderFile=RiskGameDoc.h
ImplementationFile=RiskGameDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CRiskGameDoc

[CLS:CRiskGameView]
Type=0
BaseClass=CView
HeaderFile=RiskGameView.h
ImplementationFile=RiskGameView.cpp
Filter=C
VirtualFilter=VWC
LastObject=CRiskGameView

[CLS:CStaticBitmap]
Type=0
BaseClass=CStatic
HeaderFile=StaticBitmap.h
ImplementationFile=StaticBitmap.cpp

[DLG:IDD_SETUP_PLAYERS_DLG]
Type=1
Class=CPlayerSetupDlg
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308864
Control4=IDC_EDIT_PLAYER_TOTAL,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_STATIC_PLAYER_CUR,static,1350697472
Control7=IDC_SCROLLBAR_PLAYER_CUR,scrollbar,1342177280
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_PLAYER_NAME,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC_PLAYER_COLOR,static,1342177543
Control13=IDC_LIST_PLAYER_TYPE,listbox,1352728833
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_PLAYER_INITARMIES,edit,1350631552
Control16=IDC_BUTTON_SETUPPLAYERS_EDIT_AI_PARAMS,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_MENU_EDIT_SETUPPLAYER
Command8=ID_MENU_EDIT_ADDAI
Command9=ID_MENU_PLAY_START
Command10=ID_MENU_PLAY_TEST
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_MENU_VIEW_OCCUPIED
Command14=ID_APP_ABOUT
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIALOG_AIPARAMS]
Type=1
Class=CAiParamEditDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_AIPARM_PLACE_ENME_WT,edit,1350631552
Control7=IDC_EDIT_AIPARM_PLACE_ATTR_WT,edit,1350631552

[CLS:CAiParamEditDlg]
Type=0
HeaderFile=AiParamEditDlg.h
ImplementationFile=AiParamEditDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CAiParamEditDlg

