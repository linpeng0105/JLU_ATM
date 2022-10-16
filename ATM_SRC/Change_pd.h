#pragma once


// Change_pd 对话框

class Change_pd : public CDialogEx
{
	DECLARE_DYNAMIC(Change_pd)

public:
	Change_pd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Change_pd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Change_pd };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString change_id;
};
