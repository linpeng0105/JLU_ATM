
// ATM.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CATMApp:
// 有关此类的实现，请参阅 ATM.cpp
//

class CATMApp : public CWinApp
{
public:
	CATMApp();
	~CATMApp();

// 重写
public:
	virtual BOOL InitInstance();
	/*flagI标记当前登录账户，flagN标记当前转账的账户*/
	int flag;
	bool flag_jump;
	int flagI;
	int flagN;
	int userID;
	int UserNumber;
	int v;
	int all;
	struct user user[10000];
	void Save_Num();
	void TiQu();
	void Save();
	void init();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CATMApp theApp;
