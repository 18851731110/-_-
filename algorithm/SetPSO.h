#pragma once
#include "resource.h"

// SetPSO �Ի���

class SetPSO : public CDialogEx
{
	DECLARE_DYNAMIC(SetPSO)

public:
	SetPSO(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetPSO();

// �Ի�������
	enum { IDD = IDD_SetPSO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int PSOgenerations;
	int PSOparticle_num;
	int PSOsetV_numMAX;
	int PSOsetInitialV;
	afx_msg void OnBnClickedOk();

};
