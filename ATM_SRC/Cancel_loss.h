#pragma once


// Cancel_loss 对话框

class Cancel_loss : public CDialogEx
{
	DECLARE_DYNAMIC(Cancel_loss)

public:
	Cancel_loss(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cancel_loss();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Cancel_loss };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	CString cancel_loss_id;
};
