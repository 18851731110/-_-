// Set_start_goal_Position.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Set_start_goal_Position.h"
#include "afxdialogex.h"
#include "USVDoc.h"
#include "USVView.h"

extern bool state_sgposition;//ʼĩ��״̬
extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���
extern StartGoalPOINT startgoalp;//ʼĩ��״̬

// Set_start_goal_Position �Ի���

IMPLEMENT_DYNAMIC(Set_start_goal_Position, CDialogEx)


Set_start_goal_Position::Set_start_goal_Position(CWnd* pParent /*=NULL*/)
	: CDialogEx(Set_start_goal_Position::IDD, pParent)
	, StartX(0)
	, StartY(0)
	, GoalY(0)
	, GoalX(0)
	, V_Kn(0)
{

}

Set_start_goal_Position::~Set_start_goal_Position()
{
}

void Set_start_goal_Position::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_StartX, StartX);
	DDX_Text(pDX, IDC_StartX, StartX);
	DDV_MinMaxUInt(pDX, StartX, 0, 2000);
	DDX_Text(pDX, IDC_StartY, StartY);
	DDV_MinMaxUInt(pDX, StartY, 0, 2000);
	DDX_Text(pDX, IDC_GoalY, GoalY);
	DDV_MinMaxUInt(pDX, GoalY, 0, 2000);
	DDX_Text(pDX, IDC_GoalX, GoalX);
	DDV_MinMaxUInt(pDX, GoalX, 0, 2000);
	DDX_Text(pDX, IDC_GoalY2, V_Kn);
	DDV_MinMaxFloat(pDX, V_Kn, 0, 150);
}


BEGIN_MESSAGE_MAP(Set_start_goal_Position, CDialogEx)
	ON_EN_CHANGE(IDC_StartX, &Set_start_goal_Position::OnEnChangeStartx)
	ON_BN_CLICKED(IDOK, &Set_start_goal_Position::OnSetSGPosionOk)
END_MESSAGE_MAP()


// Set_start_goal_Position ��Ϣ�������


void Set_start_goal_Position::OnEnChangeStartx()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Set_start_goal_Position::OnSetSGPosionOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���

	UpdateData(TRUE);//���޴˸��£�д����ֵΪ�ϴε�ֵ
	state_sgposition = 1;
	Set_start_goal_Position setstartgoalp;
	startgoalp.sx = StartX;
	startgoalp.sy = StartY;
	startgoalp.gx = GoalX;
	startgoalp.gy = GoalY;
	startgoalp.v_kn = V_Kn;
	startgoalp.v_ms = startgoalp.v_kn * Kn_ms;
	UpdateData(FALSE);
	CDialogEx::OnOK();
}
