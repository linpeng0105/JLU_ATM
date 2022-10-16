// Cancel_loss.cpp: 实现文件
//

#include "pch.h"
#include "ATM.h"
#include "Cancel_loss.h"
#include "afxdialogex.h"
#include "Show_num.h"


// Cancel_loss 对话框

IMPLEMENT_DYNAMIC(Cancel_loss, CDialogEx)

Cancel_loss::Cancel_loss(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Cancel_loss, pParent)
	, cancel_loss_id(_T(""))
{

}

Cancel_loss::~Cancel_loss()
{
}

void Cancel_loss::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, cancel_loss_id);
}


BEGIN_MESSAGE_MAP(Cancel_loss, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &Cancel_loss::OnBnClickedOk)
END_MESSAGE_MAP()


// Cancel_loss 消息处理程序


HBRUSH Cancel_loss::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


void Cancel_loss::OnPaint()
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


void Cancel_loss::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

    //声明标识符
    USES_CONVERSION;
    UpdateData(TRUE);
    CATMApp* app = (CATMApp*)AfxGetApp();
    char* s;
    s = W2A(cancel_loss_id);
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
		app->user[flag].flag = 1;
		app->Save();
		MessageBox(TEXT("解除挂失成功！"));
		CDialogEx::OnOK();
		app->flag = flag;
		app->flag_jump = true;
		Show_num dlg;
		dlg.DoModal();
    }
}
