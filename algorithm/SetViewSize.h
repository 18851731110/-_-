#pragma once
#include "afxwin.h"


// SetViewSize �Ի���

class SetViewSize : public CDialogEx
{
	DECLARE_DYNAMIC(SetViewSize)

public:
	SetViewSize(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetViewSize();

// �Ի�������
	enum { IDD = IDD_SetViewSize };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT setviewL;
	UINT setviewW;
	afx_msg void OnBnClickedOk();
	BOOL SetViewChange;
	afx_msg void OnBnClickedChange();
	CEdit setviewLC;
	CEdit setviewWC;
	virtual BOOL OnInitDialog();
};
