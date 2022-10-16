
// ATM.cpp: 定义应用程序的类行为。
//

#include "pch.h"
#include "framework.h"
#include "ATM.h"
#include "ATMDlg.h"
#include "afxdialogex.h"
#include <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CATMApp

BEGIN_MESSAGE_MAP(CATMApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CATMApp 构造

CATMApp::CATMApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

CATMApp::~CATMApp()
{
	Save();
}


// 唯一的 CATMApp 对象

CATMApp theApp;


// CATMApp 初始化

BOOL CATMApp::InitInstance()
{
	userID = 0;
	UserNumber = 0;
	v = -1;
	flag_jump = true;
	//Save();
	FILE* fp;
	FILE* fp2;
	fp = fopen("user.txt", "r"); 	//已只读的方式进入文件 
	if (feof(fp) != 0) {			//如果文件为空，则写入默认管理员账号及密码 
		init();
	}
	
	if (_access("all.txt", 0) != 0) {			//如果文件为空，则写入默认金额
		fp2 = fopen("all.txt", "w");
		all = 600000;
		fwrite(&all, sizeof(int), 1, fp2);
		fclose(fp2);
	}
	else
	{
		fp2 = fopen("all.txt", "r"); 	//已只读的方式进入文件 
		fread(&all, sizeof(int), 1, fp2);
		fclose(fp2);
	}
		
	srand((int)time(0));        //产生随机数种子

	TiQu();//加载用户信息

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CATMDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

void CATMApp::TiQu() 		//提取用户信息
{
	UserNumber = 0;
	FILE* fp;
	if ((fp = fopen("user.txt", "r")) != NULL)
	{
		while (!feof(fp))
		{
			fread(&user[++UserNumber], sizeof(struct user), 1, fp);
		}
		fclose(fp);
	}
	else
		//MessageBox(TEXT("用户信息加载失败！"));
		;
	UserNumber--;    //

}

void CATMApp::Save()  		//更新用户信息
{
	FILE* fp;
	if ((fp = fopen("user.txt", "w")) != NULL)
	{
		for (int i = 1; i <= UserNumber; i++)
		{
			fwrite(&user[i], sizeof(struct user), 1, fp);
		}
		fclose(fp);
	}
	else
		//printf("\n\t\t\t\t\t\t用户信息更新失败");
		;
}

void CATMApp::Save_Num()  		//更新ATM信息
{
	FILE* fp;
	if ((fp = fopen("all.txt", "w")) != NULL)
	{
		fwrite(&all, sizeof(int), 1, fp);
		fclose(fp);
	}
	else
		//printf("\n\t\t\t\t\t\t信息更新失败");
		;
}

void CATMApp::init()
{
	UserNumber = 1;
	strcpy(user[1].name, "2019");
	strcpy(user[1].key, "123456");
	user[1].money = 1.00;
	user[1].flag = 1;
	user[1].d = 1;
	Save();
	return;
}