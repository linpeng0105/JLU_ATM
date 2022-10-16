#pragma once


// Admin 对话框

class Admin : public CDialogEx
{
	DECLARE_DYNAMIC(Admin)

public:
	Admin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Admin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedChangepd();
	afx_msg void OnBnClickedNum();
	afx_msg void OnBnClickedloss();
	afx_msg void OnBnClickedLoss();
	afx_msg void OnBnClickedLoss1();
	afx_msg void OnBnClickedNewNum();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOverhaul();
	afx_msg void OnBnClickedManage();
};
