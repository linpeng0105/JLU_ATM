// Admin.cpp: 实现文件
//

#include "pch.h"
#include "ATM.h"
#include "Admin.h"
#include "afxdialogex.h"
#include "Change_pd.h"
#include "Find_num.h"
#include "Report_loss.h"
#include "Cancel_loss.h"
#include "New_num.h"
#include "ATMDlg.h"
#include "Overhaul.h"
#include "Manage.h"


// Admin 对话框

IMPLEMENT_DYNAMIC(Admin, CDialogEx)

Admin::Admin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMIN, pParent)
{

}

Admin::~Admin()
{
}

void Admin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Admin, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ChangePd, &Admin::OnBnClickedChangepd)
	ON_BN_CLICKED(FIND_NUM, &Admin::OnBnClickedNum)
	ON_BN_CLICKED(REPORT_LOSS, &Admin::OnBnClickedLoss)
	ON_BN_CLICKED(CANCEL_LOSS1, &Admin::OnBnClickedLoss1)
	ON_BN_CLICKED(ID_NEW_NUM, &Admin::OnBnClickedNewNum)
	ON_BN_CLICKED(IDCANCEL, &Admin::OnBnClickedCancel)
	ON_BN_CLICKED(ID_OVERHAUL, &Admin::OnBnClickedOverhaul)
	ON_BN_CLICKED(ID_MANAGE, &Admin::OnBnClickedManage)
END_MESSAGE_MAP()


// Admin 消息处理程序


BOOL Admin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Admin::OnPaint()
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
		bmpBackground.LoadBitmap(IDB_BITMAP2);  //对话框的背景图片  

		BITMAP   bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}


HBRUSH Admin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		pDC->SetTextColor(RGB(0, 0, 0));//设置字体为黑色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void Admin::OnBnClickedChangepd()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Change_pd dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedNum()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Find_num dlg;
	dlg.DoModal();
}

void Admin::OnBnClickedLoss()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Report_loss dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedLoss1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Cancel_loss dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedNewNum()
{
	// TODO: 在此添加控件通知处理程序代码
	CATMApp* app = (CATMApp*)AfxGetApp();
	int id = app->UserNumber + 1;
	while (1)
	{

		for (int i = 0; i < 11; i++)
		{
			app->user[id].name[i] = rand() % 9 + 1 + '0';
		}
		app->user[id].name[11] = '\0';
		int flag = 0;
		for (int i = 1; i <= app->UserNumber; i++)
		{
			if (strcmp(app->user[id].name, app->user[i].name) == 0)
			{
				flag = i;
				break;
			}
		}
		if (!flag)break;
	}
	CDialogEx::OnOK();
	New_num dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CATMApp* app = (CATMApp*)AfxGetApp();
	app->Save();
	CDialogEx::OnCancel();
	CATMDlg dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedOverhaul()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Overhaul dlg;
	dlg.DoModal();
}


void Admin::OnBnClickedManage()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	Manage dlg;
	dlg.DoModal();
}
