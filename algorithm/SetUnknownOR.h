#pragma once
#include "afxcmn.h"
#include "SetStaticObstacleRectangle.h"

// SetUnknownOR �Ի���

class SetUnknownOR : public CDialogEx
{
	DECLARE_DYNAMIC(SetUnknownOR)

public:
	SetUnknownOR(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetUnknownOR();

// �Ի�������
	enum { IDD = IDD_SetUnknownOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl LIST_UnknownOR;
	UINT UnknownOR_X;
	UINT UnknownOR_Y;
	UINT UnknownOR_HL;
	UINT UnknownOR_HW;
	float UnknownOR_DA;
	float UnknownOR_V;

	void CalculateUnknownOR(int i);//���㷽���ϰ�������
	PointInRC calculate_pointInDRC(int m, float x, float y);//������ھ��ε��Ǹ�λ�ã���9����

	afx_msg void OnBnClickedAddunknownor();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDeleteunknownor();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSunknownorinput();
	afx_msg void OnBnClickedSunknownoroutput();
};
