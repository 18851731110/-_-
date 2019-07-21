#pragma once
#include "afxvslistbox.h"
#include "resource.h"
#include "afxcmn.h"
#include "USVDoc.h"
#include "USVView.h"

// SetStaticObstacleRectangle �Ի���

struct PointInRC//���ھ����е�λ�ýṹ��
{
	int point, min, max;//��ʱ�뷽��ȡmin��max
};

class SetStaticObstacleRectangle : public CDialogEx
{
	DECLARE_DYNAMIC(SetStaticObstacleRectangle)

public:
	SetStaticObstacleRectangle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetStaticObstacleRectangle();
	void CalculateStaticOR(int i);//���㷽���ϰ�������
	PointInRC calculate_pointInRC(REC Peak0, REC Peak1, REC Peak2, REC Peak3, float x, float y);//������ھ��ε��Ǹ�λ�ã���9����

// �Ի�������
	enum { IDD = IDD_SetStaticObstacleRectangle };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnStnClicked65535();
	virtual BOOL OnInitDialog();
	CListCtrl LIST_StaticObstacleRec;
	UINT CenterX;
	UINT CenterY;
	float DirectionA;
//	UINT PeakX;
//	UINT PeakY;
	UINT HalfLength;
	UINT HalfWidth;
	afx_msg void OnBnClickedAddobstacler();
	afx_msg void OnBnClickedDeleteobstacler();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSobstaclecinputr();
	afx_msg void OnBnClickedSobstaclecoutputr();
};
