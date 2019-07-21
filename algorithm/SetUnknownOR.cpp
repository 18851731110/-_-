// SetUnknownOR.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "SetUnknownOR.h"
#include "afxdialogex.h"
#include "SetStaticObstacleCircle.h"
#include "SetStaticObstacleRectangle.h"
#include "afxdialogex.h"
#include "USVDoc.h"
#include "USVView.h"
#include "math.h"
#include <afxdb.h>

extern UnknownOR unknownor[20];
extern StartGoalPOINT startgoalp;
extern bool state_unknownOR;//����δ֪�ϰ���״̬
extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���
extern Unknown unknown;//�ֲ�δ֪����

// SetUnknownOR �Ի���

IMPLEMENT_DYNAMIC(SetUnknownOR, CDialogEx)

SetUnknownOR::SetUnknownOR(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetUnknownOR::IDD, pParent)
	, UnknownOR_X(0)
	, UnknownOR_Y(0)
	, UnknownOR_HL(0)
	, UnknownOR_HW(0)
	, UnknownOR_DA(0)
	, UnknownOR_V(0)
{

}

SetUnknownOR::~SetUnknownOR()
{
}

void SetUnknownOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UnknownOR, LIST_UnknownOR);
	DDX_Text(pDX, IDC_UnknownOR_X, UnknownOR_X);
	DDV_MinMaxUInt(pDX, UnknownOR_X, 0, 2000);
	DDX_Text(pDX, IDC_UnknownOR_Y, UnknownOR_Y);
	DDV_MinMaxUInt(pDX, UnknownOR_Y, 0, 2000);
	DDX_Text(pDX, IDC_UnknownOR_HL, UnknownOR_HL);
	DDV_MinMaxUInt(pDX, UnknownOR_HL, 0, 2000);
	DDX_Text(pDX, IDC_UnknownOR_HW, UnknownOR_HW);
	DDV_MinMaxUInt(pDX, UnknownOR_HW, 0, 2000);
	DDX_Text(pDX, IDC_UnknownOR_DA, UnknownOR_DA);
	DDX_Text(pDX, IDC_UnknownOR_V, UnknownOR_V);
}


BEGIN_MESSAGE_MAP(SetUnknownOR, CDialogEx)
	ON_BN_CLICKED(IDAddUnknownOR, &SetUnknownOR::OnBnClickedAddunknownor)
	ON_BN_CLICKED(IDDeleteUnknownOR, &SetUnknownOR::OnBnClickedDeleteunknownor)
	ON_BN_CLICKED(IDOK, &SetUnknownOR::OnBnClickedOk)
	ON_BN_CLICKED(IDSUnknownORInput, &SetUnknownOR::OnBnClickedSunknownorinput)
	ON_BN_CLICKED(IDSUnknownOROutput, &SetUnknownOR::OnBnClickedSunknownoroutput)
END_MESSAGE_MAP()


// SetUnknownOR ��Ϣ�������

BOOL SetUnknownOR::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString Field[7] = { "���", "���ĵ�X", "���ĵ�Y", "�볤", "���", "�����", "�ٶ�" };//�б��ӵı�ͷ
	LIST_UnknownOR.InsertColumn(0, Field[0], LVCFMT_CENTER, 41);
	for (int j = 1; j<7; j++)
	{
		LIST_UnknownOR.InsertColumn(j, Field[j], LVCFMT_CENTER, 63);				//�����ͷ����
	}
	//��ʼ�������	
	UnknownOR_X = 0;
	UnknownOR_Y = 0;
	UnknownOR_HL = 0;
	UnknownOR_HW = 0;
	UnknownOR_DA = 0;
	UnknownOR_V = 0;

	//���뾲̬�ϰ����������--���ʼĩ����ĺ�� ���������� ����
	for (UINT i = 0; i < 20; i++)
	{
		if (unknownor[i].CenterPm != 0)
		{
			UpdateData(TRUE);

			int num = LIST_UnknownOR.GetItemCount();

			CString stemp[7];
			stemp[0].Format("%d", num + 1);
			stemp[1].Format("%d", unknownor[i].CenterX);
			stemp[2].Format("%d", unknownor[i].CenterY);
			stemp[3].Format("%d", unknownor[i].HalfL);
			stemp[4].Format("%d", unknownor[i].HalfW);
			stemp[5].Format("%0.3f", unknownor[i].Da);
			stemp[6].Format("%0.3f", unknownor[i].V);
			LIST_UnknownOR.InsertItem(num, stemp[0]);		//������
			for (int j = 1; j < 7; j++)
			{
				LIST_UnknownOR.SetItemText(num, j, stemp[j]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
			}
			UpdateData(false);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void SetUnknownOR::OnBnClickedAddunknownor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if (UnknownOR_HL != 0)
	{
		int num = LIST_UnknownOR.GetItemCount();
		unknownor[num].CenterX = UnknownOR_X;
		unknownor[num].CenterY = UnknownOR_Y;
		unknownor[num].HalfL = UnknownOR_HL;
		unknownor[num].HalfW = UnknownOR_HW;
		unknownor[num].Da = UnknownOR_DA;
		unknownor[num].V = UnknownOR_V;

		CalculateUnknownOR(num);//���㷽���ϰ�������

		CString stemp[7];
		stemp[0].Format("%d", num + 1);
		stemp[1].Format("%d", UnknownOR_X);
		stemp[2].Format("%d", UnknownOR_Y);
		stemp[3].Format("%d", UnknownOR_HL);
		stemp[4].Format("%d", UnknownOR_HW);
		stemp[5].Format("%0.3f", UnknownOR_DA);
		stemp[6].Format("%0.3f", UnknownOR_V);

		LIST_UnknownOR.InsertItem(num, stemp[0]);		//������
		for (int i = 1; i<7; i++)
		{
			LIST_UnknownOR.SetItemText(num, i, stemp[i]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
		}

		UnknownOR_X = 0;
		UnknownOR_Y = 0;
		UnknownOR_HL = 0;
		UnknownOR_HW = 0;
		UnknownOR_DA = 0;
		UnknownOR_V = 0;
	}

	UpdateData(false);
}

void SetUnknownOR::OnBnClickedDeleteunknownor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int num = LIST_UnknownOR.GetItemCount();
	while (LIST_UnknownOR.DeleteItem(num - 1));
	unknownor[num - 1] = { 0 };
}

void SetUnknownOR::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���

	int num = LIST_UnknownOR.GetItemCount();

	//��unknownor���鰴���ĵ㼫��ֵ  ���д�С��������
	for (int j = 0; j < num - 1; j++)
	{
		for (int i = 0; i < num - 1 - j; i++)
		{
			UnknownOR temp;
			if (unknownor[i].CenterPm>unknownor[i + 1].CenterPm)
			{
				temp = unknownor[i];
				unknownor[i] = unknownor[i + 1];
				unknownor[i + 1] = temp;
			}
		}
	}

	if (unknownor[0].HalfL != 0)
	{
		state_unknownOR = 1;
	}

	CDialogEx::OnOK();
}

void SetUnknownOR::CalculateUnknownOR(int i)//���㷽���ϰ�������
{
	float tempL = unknownor[i].V * unknown.UnknownT * drawscale * Kn_ms;
	SetStaticObstacleCircle temp;
	unknownor[i].CenterPm = sqrt(pow((float)abs(int(startgoalp.sx - unknownor[i].CenterX)), 2) + pow((float)abs(int(startgoalp.sy - unknownor[i].CenterY)), 2));//����
	unknownor[i].CenterPa = temp.calculate_PolarAngle((float)unknownor[i].CenterX, (float)unknownor[i].CenterY);//����

	float tempX, tempY;
	float tempPA = 0.0 - unknownor[i].Da * 2 * pi / 360;
	//�ֲ�����ϵ��0�Ķ���(��ʱ������)
	tempX = (float)unknownor[i].HalfL;
	tempY = (float)unknownor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[0].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[0].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[0].Pm = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].x), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].y), 2));//����;
	unknownor[i].Peak[0].Pa = temp.calculate_PolarAngle(unknownor[i].Peak[0].x, unknownor[i].Peak[0].y);//����

	//�ֲ�����ϵ��0�Ķ���(��չ����)
	tempX = (float)unknownor[i].HalfL + tempL;
	tempY = (float)unknownor[i].HalfW + tempL;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[0].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[0].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
	unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

	//�ֲ�����ϵ��1�Ķ���
	tempX = (float)unknownor[i].HalfL;
	tempY = 0.0 - (float)unknownor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[1].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[1].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].x), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].y), 2));//����;
	unknownor[i].Peak[1].Pa = temp.calculate_PolarAngle(unknownor[i].Peak[1].x, unknownor[i].Peak[1].y);//����

	//�ֲ�����ϵ��1�Ķ���(��չ����)
	tempX = (float)unknownor[i].HalfL + tempL;
	tempY = 0.0 - (float)unknownor[i].HalfW - tempL;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[1].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[1].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
	unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����

	//�ֲ�����ϵ��2�Ķ���
	tempX = 0.0 - (float)unknownor[i].HalfL;
	tempY = 0.0 - (float)unknownor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[2].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[2].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[2].Pm = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].x), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].y), 2));//����;
	unknownor[i].Peak[2].Pa = temp.calculate_PolarAngle(unknownor[i].Peak[2].x, unknownor[i].Peak[2].y);//����

	//�ֲ�����ϵ��2�Ķ���(��չ����)
	tempX = 0.0 - (float)unknownor[i].HalfL - tempL;
	tempY = 0.0 - (float)unknownor[i].HalfW - tempL;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[2].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[2].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
	unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

	//�ֲ�����ϵ��3�Ķ���
	tempX = 0.0 - (float)unknownor[i].HalfL;
	tempY = (float)unknownor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[3].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[3].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].x), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].y), 2));//����;
	unknownor[i].Peak[3].Pa = temp.calculate_PolarAngle(unknownor[i].Peak[3].x, unknownor[i].Peak[3].y);//����

	//�ֲ�����ϵ��3�Ķ���(��չ����)
	tempX = 0.0 - (float)unknownor[i].HalfL - tempL;
	tempY = (float)unknownor[i].HalfW + tempL;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	unknownor[i].Peak[3].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)unknownor[i].CenterX;
	unknownor[i].Peak[3].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)unknownor[i].CenterY;
	unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
	unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����

	//���ĸ����㰴pm��������
	//�ҳ���Сֵ���±�
	float min = 0.0;
	int flag = 0;
	for (int m = 0; m < 4; m++)
	{
		if (m == 0)
		{
			min = unknownor[i].Peak[0].Pm;
			flag = 0;
		}
		else
		{
			if (min>unknownor[i].Peak[m].Pm)
			{
				min = unknownor[i].Peak[m].Pm;
				flag = m;
			}
		}
	}
	//��������
	REC tempPeak;
	if (flag == 0)
	{
	}
	else if (flag == 1)
	{
		tempPeak = unknownor[i].Peak[0];
		unknownor[i].Peak[0] = unknownor[i].Peak[1];
		unknownor[i].Peak[1] = unknownor[i].Peak[2];
		unknownor[i].Peak[2] = unknownor[i].Peak[3];
		unknownor[i].Peak[3] = tempPeak;
	}
	else if (flag == 2)
	{
		tempPeak = unknownor[i].Peak[0];
		unknownor[i].Peak[0] = unknownor[i].Peak[2];
		unknownor[i].Peak[2] = tempPeak;
		tempPeak = unknownor[i].Peak[3];
		unknownor[i].Peak[3] = unknownor[i].Peak[1];
		unknownor[i].Peak[1] = tempPeak;
	}
	else if (flag == 3)
	{
		tempPeak = unknownor[i].Peak[0];
		unknownor[i].Peak[0] = unknownor[i].Peak[3];
		unknownor[i].Peak[3] = unknownor[i].Peak[2];
		unknownor[i].Peak[2] = unknownor[i].Peak[1];
		unknownor[i].Peak[1] = tempPeak;
	}

	//����ĩ����չ��
	float k1, k2;
	if ((0 < unknownor[i].Da) && (unknownor[i].Da <90))
	{
		k1 = (unknownor[i].Peak[3].yEX - unknownor[i].Peak[0].yEX) / (unknownor[i].Peak[3].xEX - unknownor[i].Peak[0].xEX);
		unknownor[i].Peak[0].xEX = (k1*(k1*unknownor[i].Peak[0].xEX - unknownor[i].Peak[0].yEX) + unknownor[i].Peak[0].x + k1*unknownor[i].Peak[0].y) / (1 + k1*k1);
		unknownor[i].Peak[0].yEX = (-1.0/k1) * (unknownor[i].Peak[0].xEX - unknownor[i].Peak[0].x) + unknownor[i].Peak[0].y;
		unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
		unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

		k2 = (unknownor[i].Peak[1].yEX - unknownor[i].Peak[2].yEX) / (unknownor[i].Peak[1].xEX - unknownor[i].Peak[2].xEX);
		unknownor[i].Peak[1].xEX = (k2*(k2*unknownor[i].Peak[1].xEX - unknownor[i].Peak[1].yEX) + unknownor[i].Peak[1].x + k1*unknownor[i].Peak[1].y) / (1 + k2*k2);
		unknownor[i].Peak[1].yEX = (-1.0 / k2) * (unknownor[i].Peak[1].xEX - unknownor[i].Peak[1].x) + unknownor[i].Peak[1].y;
		unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
		unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����
	}
	else if (unknownor[i].Da ==0)
	{
		if (unknownor[i].CenterY < startgoalp.sy)
		{
			unknownor[i].Peak[0].xEX = unknownor[i].Peak[0].x;
			unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
			unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

			unknownor[i].Peak[3].xEX = unknownor[i].Peak[3].x;
			unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
			unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����
		}
		else
		{
			unknownor[i].Peak[0].xEX = unknownor[i].Peak[0].x;
			unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
			unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

			unknownor[i].Peak[1].xEX = unknownor[i].Peak[1].x;
			unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
			unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����
		}		
	}
	else if ((90 < unknownor[i].Da) && (unknownor[i].Da <180))
	{
		k1 = (unknownor[i].Peak[3].yEX - unknownor[i].Peak[2].yEX) / (unknownor[i].Peak[3].xEX - unknownor[i].Peak[2].xEX);
		unknownor[i].Peak[2].xEX = (k1*(k1*unknownor[i].Peak[2].xEX - unknownor[i].Peak[2].yEX) + unknownor[i].Peak[2].x + k1*unknownor[i].Peak[2].y) / (1 + k1*k1);
		unknownor[i].Peak[2].yEX = (-1.0 / k1) * (unknownor[i].Peak[2].xEX - unknownor[i].Peak[2].x) + unknownor[i].Peak[2].y;
		unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
		unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

		k2 = (unknownor[i].Peak[1].yEX - unknownor[i].Peak[0].yEX) / (unknownor[i].Peak[1].xEX - unknownor[i].Peak[0].xEX);
		unknownor[i].Peak[1].xEX = (k2*(k2*unknownor[i].Peak[1].xEX - unknownor[i].Peak[1].yEX) + unknownor[i].Peak[1].x + k1*unknownor[i].Peak[1].y) / (1 + k2*k2);
		unknownor[i].Peak[1].yEX = (-1.0 / k2) * (unknownor[i].Peak[1].xEX - unknownor[i].Peak[1].x) + unknownor[i].Peak[1].y;
		unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
		unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����
	}
	else if (unknownor[i].Da == 90)
	{
		if (unknownor[i].CenterY < startgoalp.sy)
		{
			unknownor[i].Peak[0].yEX = unknownor[i].Peak[0].y;
			unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
			unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

			unknownor[i].Peak[1].yEX = unknownor[i].Peak[1].y;
			unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
			unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����
		}
		else
		{
			unknownor[i].Peak[2].yEX = unknownor[i].Peak[2].y;
			unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
			unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

			unknownor[i].Peak[1].yEX = unknownor[i].Peak[1].y;
			unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
			unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����
		}		
	}
	else if ((180 < unknownor[i].Da) && (unknownor[i].Da <270))
	{
		k1 = (unknownor[i].Peak[1].yEX - unknownor[i].Peak[2].yEX) / (unknownor[i].Peak[1].xEX - unknownor[i].Peak[2].xEX);
		unknownor[i].Peak[2].xEX = (k1*(k1*unknownor[i].Peak[2].xEX - unknownor[i].Peak[2].yEX) + unknownor[i].Peak[2].x + k1*unknownor[i].Peak[2].y) / (1 + k1*k1);
		unknownor[i].Peak[2].yEX = (-1.0 / k1) * (unknownor[i].Peak[2].xEX - unknownor[i].Peak[2].x) + unknownor[i].Peak[2].y;
		unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
		unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

		k2 = (unknownor[i].Peak[3].yEX - unknownor[i].Peak[0].yEX) / (unknownor[i].Peak[3].xEX - unknownor[i].Peak[0].xEX);
		unknownor[i].Peak[3].xEX = (k2*(k2*unknownor[i].Peak[3].xEX - unknownor[i].Peak[3].yEX) + unknownor[i].Peak[3].x + k1*unknownor[i].Peak[3].y) / (1 + k2*k2);
		unknownor[i].Peak[3].yEX = (-1.0 / k2) * (unknownor[i].Peak[3].xEX - unknownor[i].Peak[3].x) + unknownor[i].Peak[3].y;
		unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
		unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����
	}
	else if (unknownor[i].Da == 180)
	{
		if (unknownor[i].CenterY < startgoalp.sy)
		{
			unknownor[i].Peak[2].xEX = unknownor[i].Peak[2].x;
			unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
			unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

			unknownor[i].Peak[1].xEX = unknownor[i].Peak[1].x;
			unknownor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[1].yEX), 2));//����;
			unknownor[i].Peak[1].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);//����
		}
		else
		{
			unknownor[i].Peak[2].xEX = unknownor[i].Peak[2].x;
			unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
			unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

			unknownor[i].Peak[3].xEX = unknownor[i].Peak[3].x;
			unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
			unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����
		}		
	}
	else if ((270 < unknownor[i].Da) && (unknownor[i].Da < 360))
	{
		k1 = (unknownor[i].Peak[1].yEX - unknownor[i].Peak[0].yEX) / (unknownor[i].Peak[1].xEX - unknownor[i].Peak[0].xEX);
		unknownor[i].Peak[0].xEX = (k1*(k1*unknownor[i].Peak[0].xEX - unknownor[i].Peak[0].yEX) + unknownor[i].Peak[0].x + k1*unknownor[i].Peak[0].y) / (1 + k1*k1);
		unknownor[i].Peak[0].yEX = (-1.0 / k1) * (unknownor[i].Peak[0].xEX - unknownor[i].Peak[0].x) + unknownor[i].Peak[0].y;
		unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
		unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

		k2 = (unknownor[i].Peak[3].yEX - unknownor[i].Peak[2].yEX) / (unknownor[i].Peak[3].xEX - unknownor[i].Peak[2].xEX);
		unknownor[i].Peak[3].xEX = (k2*(k2*unknownor[i].Peak[3].xEX - unknownor[i].Peak[3].yEX) + unknownor[i].Peak[3].x + k1*unknownor[i].Peak[3].y) / (1 + k2*k2);
		unknownor[i].Peak[3].yEX = (-1.0 / k2) * (unknownor[i].Peak[3].xEX - unknownor[i].Peak[3].x) + unknownor[i].Peak[3].y;
		unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
		unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����
	}
	else if (unknownor[i].Da == 270)
	{
		if (unknownor[i].CenterY < startgoalp.sy)
		{
			unknownor[i].Peak[2].yEX = unknownor[i].Peak[2].y;
			unknownor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[2].yEX), 2));//����;
			unknownor[i].Peak[2].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);//����

			unknownor[i].Peak[3].yEX = unknownor[i].Peak[3].y;
			unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
			unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����
		}
		else
		{
			unknownor[i].Peak[0].yEX = unknownor[i].Peak[0].y;
			unknownor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[0].yEX), 2));//����;
			unknownor[i].Peak[0].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);//����

			unknownor[i].Peak[3].yEX = unknownor[i].Peak[3].y;
			unknownor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - unknownor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - unknownor[i].Peak[3].yEX), 2));//����;
			unknownor[i].Peak[3].PaEX = temp.calculate_PolarAngle(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);//����
		}		
	}
}


void SetUnknownOR::OnBnClickedSunknownorinput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, //TRUE��FALSE��TRUEΪ���ļ���FALSEΪ�����ļ�
		"xls", //Ϊȱʡ����չ��
		"FileList", //Ϊ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Ϊ�Ի�����һ��ΪOFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,������ֻ��ѡ��͸��������ļ�ǰ��ʾ�� 
		"Excel �ļ�(*.xls)|*.xls||"//Ϊ�����б�������ʾ�ļ�����
		);
	dlg.m_ofn.lpstrTitle = "����δ֪�ϰ����������";

	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	//����ļ�·����
	strFilePath = dlg.GetPathName();
	//�ж��ļ��Ƿ��Ѿ����ڣ���������ļ�
	DWORD dwRe = GetFileAttributes(strFilePath);
	if (dwRe != (DWORD)-1)
	{
		//ShellExecute(NULL, NULL, strFilePath, NULL, NULL, SW_RESTORE); 
	}
	else return;

	CDatabase db;//���ݿ����Ҫ����ͷ�ļ� #include <afxdb.h>
	CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel����
	CString sSql, arr[7];

	sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", sDriver, strFilePath, strFilePath);
	if (!db.OpenEx(sSql, CDatabase::noOdbcDialog))//��������ԴDJB��xls
	{
		MessageBox("��EXCEL�ļ�ʧ��!", "����");
		return;
	}
	//��EXCEL��
	CRecordset pset(&db);
	LIST_UnknownOR.DeleteAllItems();

	//AfxMessageBox("OK");
	/* sSql = "SELECT ѧ��,����,�ɼ� "
	"FROM EXCELDEMO";      */
	// "ORDER BY ����";
	sSql.Format("SELECT ���,���ĵ�X, ���ĵ�Y, �볤, ���, �����, �ٶ� FROM δ֪�ϰ����������");
	pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
	while (!pset.IsEOF())
	{
		pset.GetFieldValue("���", arr[0]);//ǰ���ֶα�������е���ͬ���������
		pset.GetFieldValue("���ĵ�X", arr[1]);
		pset.GetFieldValue("���ĵ�Y", arr[2]);
		pset.GetFieldValue("�볤", arr[3]);
		pset.GetFieldValue("���", arr[4]);
		pset.GetFieldValue("�����", arr[5]);
		pset.GetFieldValue("�ٶ�", arr[6]);

		int count = LIST_UnknownOR.GetItemCount();//���뵽ListCtrl��
		LIST_UnknownOR.InsertItem(count, arr[0]);
		LIST_UnknownOR.SetItemText(count, 1, arr[1]);
		LIST_UnknownOR.SetItemText(count, 2, arr[2]);
		LIST_UnknownOR.SetItemText(count, 3, arr[3]);
		LIST_UnknownOR.SetItemText(count, 4, arr[4]);
		LIST_UnknownOR.SetItemText(count, 5, arr[5]);
		LIST_UnknownOR.SetItemText(count, 6, arr[6]);

		pset.MoveNext();
	}
	db.Close();

	int num = LIST_UnknownOR.GetItemCount();

	for (int i = 0; i < 20; i++)
	{
		unknownor[i] = { 0 };//����
	}
	//���б�������ӽ�����unknownor[]
	for (int i = 0; i < num; i++)
	{
		unknownor[i].CenterX = atoi(LIST_UnknownOR.GetItemText(i, 1));
		unknownor[i].CenterY = atoi(LIST_UnknownOR.GetItemText(i, 2));
		unknownor[i].HalfL = atoi(LIST_UnknownOR.GetItemText(i, 3));
		unknownor[i].HalfW = atoi(LIST_UnknownOR.GetItemText(i, 4));
		unknownor[i].Da = atof(LIST_UnknownOR.GetItemText(i, 5));
		unknownor[i].V = atof(LIST_UnknownOR.GetItemText(i, 6));
		CalculateUnknownOR(i);//���㷽���ϰ�������
	}

	MessageBox("Excel���ݳɹ�����ϵͳ!", "����ɹ�");
}

void SetUnknownOR::OnBnClickedSunknownoroutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (LIST_UnknownOR.GetItemCount() <= 0)
	{
		AfxMessageBox("�б���û�м�¼��Ҫ���棡");
		return;
	}
	//�����Ϊ�Ի��� ����Ҫ���� #include <Afxdlgs.h>
	CFileDialog dlg(FALSE,
		"xls",
		"FileList",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Excel �ļ�(*.xls)|*.xls||");
	dlg.m_ofn.lpstrTitle = "USVδ֪�ϰ�������������Ϊ";

	if (dlg.DoModal() != IDOK)
		return;
	CString strFilePath;
	//����ļ�·����
	strFilePath = dlg.GetPathName();
	//�ж��ļ��Ƿ��Ѿ����ڣ�������ɾ���ؽ�
	DWORD dwRe = GetFileAttributes(strFilePath);
	if (dwRe != (DWORD)-1)
	{
		DeleteFile(strFilePath);
	}

	CDatabase database;//���ݿ����Ҫ����ͷ�ļ� #include <afxdb.h>
	CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel����
	CString sSql, strInsert;

	TRY
	{
		// �������д�ȡ���ַ���
		sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", sDriver, strFilePath, strFilePath);

		// �������ݿ� (��Excel����ļ�)
		if (database.OpenEx(sSql, CDatabase::noOdbcDialog))
		{
			//����б��������
			int iColumnNum, iRowCount;
			LVCOLUMN lvCol;
			CString strColName; //���ڱ����б�������
			int i, j; //�С���ѭ������

			iColumnNum = LIST_UnknownOR.GetHeaderCtrl()->GetItemCount();
			iRowCount = LIST_UnknownOR.GetItemCount();

			sSql = " CREATE TABLE δ֪�ϰ���������� ( ";
			strInsert = " INSERT INTO δ֪�ϰ���������� ( ";
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for (i = 0; i< iColumnNum; i++)
			{
				if (!(LIST_UnknownOR.GetColumn(i, &lvCol)))
					return;
				if (i<iColumnNum - 1)
				{
					sSql = sSql + lvCol.pszText + " TEXT , ";
					strInsert = strInsert + lvCol.pszText + " , ";
				}
				else
				{
					sSql = sSql + lvCol.pszText + " TEXT ) ";
					strInsert = strInsert + lvCol.pszText + " )  VALUES ( ";
				}
			}
			//����Excel����ļ�
			database.ExecuteSQL(sSql);

			//ѭ����ȡ��¼�����뵽EXCEL��
			sSql = strInsert;
			char chTemp[33];
			for (j = 0; j<iRowCount; j++)
			{
				memset(chTemp, 0, 33);
				for (i = 0; i<iColumnNum; i++)
				{
					LIST_UnknownOR.GetItemText(j, i, chTemp, 33);
					if (i < (iColumnNum - 1))
					{
						sSql = sSql + "'" + chTemp + "' , ";
					}
					else
					{
						sSql = sSql + "'" + chTemp + "' ) ";
					}
				}
				//����¼���뵽�����
				database.ExecuteSQL(sSql);
				sSql = strInsert;
			}

			sSql = " CREATE TABLE ʼĩ�� ( ���X TEXT , ���Y TEXT , �յ�X TEXT , �յ�Y TEXT ) ";
			//����Excel����ļ�
			database.ExecuteSQL(sSql);

			CString stemp[4];
			stemp[0].Format("%d", startgoalp.sx);
			stemp[1].Format("%d", startgoalp.sy);
			stemp[2].Format("%d", startgoalp.gx);
			stemp[3].Format("%d", startgoalp.gy);
			strInsert = " INSERT INTO ʼĩ�� (���X , ���Y , �յ�X , �յ�Y )  VALUES ( ";
			strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "') ";
			database.ExecuteSQL(strInsert);
		}

		// �ر�Excel����ļ�
		database.Close();

		AfxMessageBox("����δ֪�ϰ����������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}

PointInRC SetUnknownOR::calculate_pointInDRC(int m, float x, float y)//������ھ��ε��Ǹ�λ�ã���9����
{
	float y01, y12, y23, y30, tempX1, tempX2, tempY1, tempY2;
	PointInRC pointInRC;

	//��ʾ����ϵ�¼��㣬���ؼ�����ϵ��ֵ
	//01
	tempX1 = unknownor[m].Peak[0].xEX;
	tempX2 = unknownor[m].Peak[1].xEX;
	tempY1 = unknownor[m].Peak[0].yEX;
	tempY2 = unknownor[m].Peak[1].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y01 = x - tempX1;
	}
	else
	{
		y01 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//12
	tempX1 = unknownor[m].Peak[1].xEX;
	tempX2 = unknownor[m].Peak[2].xEX;
	tempY1 = unknownor[m].Peak[1].yEX;
	tempY2 = unknownor[m].Peak[2].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y12 = x - tempX1;
	}
	else
	{
		y12 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//23
	tempX1 = unknownor[m].Peak[2].xEX;
	tempX2 = unknownor[m].Peak[3].xEX;
	tempY1 = unknownor[m].Peak[2].yEX;
	tempY2 = unknownor[m].Peak[3].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y23 = x - tempX1;
	}
	else
	{
		y23 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//30
	tempX1 = unknownor[m].Peak[3].xEX;
	tempX2 = unknownor[m].Peak[0].xEX;
	tempY1 = unknownor[m].Peak[3].yEX;
	tempY2 = unknownor[m].Peak[0].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y30 = x - tempX1;
	}
	else
	{
		y30 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	if ((y01 >= 0) & (y12 >= 0) & (y30 <= 0) & (y23 <= 0))
	{
		pointInRC.point = 5;//�ھ����ڲ�
	}
	else if ((y01 < 0) & (y30 > 0))
	{
		pointInRC.point = 0;
		pointInRC.min = 1;
		pointInRC.max = 3;
	}
	else if ((y01 < 0) & (y12 < 0))
	{
		pointInRC.point = 1;
		pointInRC.min = 2;
		pointInRC.max = 0;
	}
	else if ((y12 < 0) & (y23 > 0))
	{
		pointInRC.point = 2;
		pointInRC.min = 3;
		pointInRC.max = 1;
	}
	else if ((y23 > 0) & (y30 > 0))
	{
		pointInRC.point = 3;
		pointInRC.min = 0;
		pointInRC.max = 2;
	}
	else if ((y01 < 0) & (y12 >= 0) & (y30 <= 0))
	{
		pointInRC.point = 10;
		pointInRC.min = 1;
		pointInRC.max = 0;
	}
	else if ((y01 >= 0) & (y12 < 0) & (y23 <= 0))
	{
		pointInRC.point = 12;
		pointInRC.min = 2;
		pointInRC.max = 1;
	}
	else if ((y12 >= 0) & (y23 > 0) & (y30 <= 0))
	{
		pointInRC.point = 23;
		pointInRC.min = 3;
		pointInRC.max = 2;
	}
	else if ((y01 >= 0) & (y23 <= 0) & (y30 > 0))
	{
		pointInRC.point = 30;
		pointInRC.min = 0;
		pointInRC.max = 3;
	}
	return pointInRC;
}