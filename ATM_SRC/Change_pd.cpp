// Change_pd.cpp: 实现文件
//

#include "pch.h"
#include "ATM.h"
#include "Change_pd.h"
#include "afxdialogex.h"
#include "Admin.h"
#include "New_pd.h"
#include "Show_num.h"


// Change_pd 对话框

IMPLEMENT_DYNAMIC(Change_pd, CDialogEx)

Change_pd::Change_pd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Change_pd, pParent)
	, change_id(_T(""))
{

}

Change_pd::~Change_pd()
{
}

void Change_pd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, change_id);
}


BEGIN_MESSAGE_MAP(Change_pd, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDCANCEL, &Change_pd::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &Change_pd::OnBnClickedOk)
END_MESSAGE_MAP()


// Change_pd 消息处理程序


BOOL Change_pd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Change_pd::OnPaint()
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


HBRUSH Change_pd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void Change_pd::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	Admin dlg;
	dlg.DoModal();
}


void Change_pd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
    //声明标识符
    USES_CONVERSION;
    UpdateData(TRUE);
    CATMApp* app = (CATMApp*)AfxGetApp();
    char* s;
    s = W2A(change_id);
    int flag = 0;
    for (int i = 1; i <= app->UserNumber; i++)
    {
        if (strcmp(s, app->user[i].name) == 0)
        {
            flag = i;
            break;
        }
    }
    if (flag == 0)
    {
        MessageBox(TEXT("用户不存在！"));
    }
    else if (app->user[flag].d == 1)
    {
        MessageBox(TEXT("管理员账户，无权查看！"));
    }
    else
    {
        MessageBox(TEXT("查询成功！"));
        app->flag = flag;
        CDialogEx::OnOK();
		app->flag_jump = false;
		Show_num dlg1;
        dlg1.DoModal();
        New_pd dlg2;
        dlg2.DoModal();
        
    }
}
