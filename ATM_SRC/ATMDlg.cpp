
// ATMDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ATM.h"
#include "ATMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Admin.h"
#include "User.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CATMDlg 对话框



CATMDlg::CATMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ATM_DIALOG, pParent)
	, user_id(_T(""))
	, password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CATMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, user_id);
	DDX_Text(pDX, IDC_EDIT2, password);
}

BEGIN_MESSAGE_MAP(CATMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CATMDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CATMDlg 消息处理程序

BOOL CATMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	count = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CATMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CATMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC   dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC   dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);  //对话框的背景图片  

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CATMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CATMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case   VK_RETURN://屏蔽回车  
				//   OnKeyDown(VK_SPACE,   LOWORD(pMsg   ->lParam),   HIWORD(pMsg->lParam));    
			return   TRUE;
		case   VK_ESCAPE://屏蔽Esc  
			return   TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


HBRUSH CATMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		pDC->SetTextColor(RGB(0, 0, 0));//设置字体为黄色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CATMDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//声明标识符
	USES_CONVERSION;
	UpdateData(TRUE);
	CATMApp* app = (CATMApp*)AfxGetApp();
	char* a;
	char* b;
	int i, flag = 0;

	a = W2A(user_id);
	b = W2A(password);

	int fff = 0;
	for (int i = 1; i <= app->UserNumber; i++)
	{
		if (strcmp(a, app->user[i].name) == 0 && strcmp(b, app->user[i].key) == 0)
		{
			fff = 1;
			app->userID = i;
		}
	}


	if (!fff) {
		MessageBox(TEXT("用户名或者密码输入错误！请重新输入！"));
		count++;
	}
	else if (app->user[app->userID].flag == 3) {
		MessageBox(TEXT("该用户已经挂失，请重新登录！"));
	}
	else if (app->user[app->userID].flag == 2) {
		MessageBox(TEXT("该用户已经冻结，请重新登录！"));
	}
	else
	{
		CDialogEx::OnOK();
		if (app->user[app->userID].d == 2)
		{ 
			User dlg;
			dlg.DoModal();
		}
		else if (app->user[app->userID].d == 1)
		{
			Admin dlg;
			dlg.DoModal();
		}
	}
	if (count == 3)
	{
		MessageBox(TEXT("您输入错误已超过三次, 系统已退出！\n"));
		app->Save();
		CDialogEx::OnOK();
	}
}
