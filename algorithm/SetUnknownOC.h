#pragma once
#include "afxcmn.h"


// SetUnknownOC �Ի���

class SetUnknownOC : public CDialogEx
{
	DECLARE_DYNAMIC(SetUnknownOC)

public:
	SetUnknownOC(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetUnknownOC();

	void calculate_unknownOC();//����δ֪�ϰ�Բ������

// �Ի�������
	enum { IDD = IDD_SetUnknownOC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LIST_UnknownOC;

	UINT UnknownOC_X;
	UINT UnknownOC_Y;
	UINT UnknownOC_R;
	float UnknownOC_DA;
	float UnknownOC_V;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAddunknownoc();
	afx_msg void OnBnClickedDeleteunknownoc();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSunknownociutput();
	afx_msg void OnBnClickedSunknownocoutput();
};
