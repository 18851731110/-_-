#pragma once
#include "afxwin.h"
#include "resource.h"


// Set_start_goal_Position �Ի���


class Set_start_goal_Position : public CDialogEx
{
	DECLARE_DYNAMIC(Set_start_goal_Position)

public:
	Set_start_goal_Position(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Set_start_goal_Position();

// �Ի�������
	enum { IDD = IDD_Set_start_goal_Position };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	CEdit StartX;
	UINT StartX;
	afx_msg void OnEnChangeStartx();
	UINT StartY;
	UINT GoalY;
	UINT GoalX;
//	afx_msg void OnBnClickedOk();
	afx_msg void OnSetSGPosionOk();
	float V_Kn;
};
