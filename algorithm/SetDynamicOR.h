#pragma once
#include "afxcmn.h"
#include "SetStaticObstacleRectangle.h"

/*
struct PointInRC//���ھ����е�λ�ýṹ��
{
	int point, min, max;//��ʱ�뷽��ȡmin��max
};*/

// SetDynamicOR �Ի���

class SetDynamicOR : public CDialogEx
{
	DECLARE_DYNAMIC(SetDynamicOR)

public:
	SetDynamicOR(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetDynamicOR();

// �Ի�������
	enum { IDD = IDD_SetDynamicOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	UINT DynamicOR_X;
	UINT DynamicOR_Y;
	UINT DynamicOR_HL;
	UINT DynamicOR_HW;
	float DynamicOR_DA;
	float DynamicOR_V;
	virtual BOOL OnInitDialog();
	CListCtrl LIST_DynamicOR;
	afx_msg void OnBnClickedAdddynamicOR();

	void CalculateDynamicOR(int i);//���㷽���ϰ�������
	PointInRC calculate_pointInDRC(int m, float x, float y);//������ھ��ε��Ǹ�λ�ã���9����

	afx_msg void OnBnClickedDeletedynamicOR();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSdynamicorinput();
	afx_msg void OnBnClickedSdynamicoroutput();
};
