#pragma once
#include "afxwin.h"


// SetDoPSO �Ի���

class SetDoPSO : public CDialogEx
{
	DECLARE_DYNAMIC(SetDoPSO)

public:
	SetDoPSO(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetDoPSO();

// �Ի�������
	enum { IDD = IDD_SetDoPSO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT PSOgenerationsDO;
	UINT PSOparticle_numDO;
	BOOL PSOchangeDO;
	CEdit PSOchangeV;
	UINT PSOchangeVdo;
	CEdit PSOchangeDa;
	UINT PSOchangeDado;
	afx_msg void OnBnClickedPsochangedo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
