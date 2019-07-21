// SetPSO.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "USVDoc.h"
#include "USVView.h"
#include "SetPSO.h"
#include "afxdialogex.h"


// SetPSO �Ի���

extern PSO pso;//����Ⱥ����
extern int thisPSOnum;//����pso���Դ���

IMPLEMENT_DYNAMIC(SetPSO, CDialogEx)

SetPSO::SetPSO(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetPSO::IDD, pParent)
	, PSOgenerations(0)
	, PSOparticle_num(0)
	, PSOsetV_numMAX(0)
	, PSOsetInitialV(0)
{

}

SetPSO::~SetPSO()
{
}

void SetPSO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PSOgenerations, PSOgenerations);
	DDV_MinMaxInt(pDX, PSOgenerations, 0, 10000);
	DDX_Text(pDX, IDC_PSOparticle_num, PSOparticle_num);
	DDV_MinMaxInt(pDX, PSOparticle_num, 0, 10000);
	DDX_Text(pDX, IDC_PSOsetV_numMAX, PSOsetV_numMAX);
	DDV_MinMaxInt(pDX, PSOsetV_numMAX, 0, 10000);
	//  DDX_Text(pDX, IDC_PSOsetInitialV, PSOsetInitialV);
	//  DDV_MinMaxFloat(pDX, PSOsetInitialV, 0, 1000);
	DDX_Text(pDX, IDC_PSOsetInitialV, PSOsetInitialV);
	DDV_MinMaxInt(pDX, PSOsetInitialV, 0, 1000);
}


BEGIN_MESSAGE_MAP(SetPSO, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetPSO::OnBnClickedOk)
END_MESSAGE_MAP()


// SetPSO ��Ϣ�������


void SetPSO::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//���޴˸��£�д����ֵΪ�ϴε�ֵ
	
	thisPSOnum = 0;//����pso���Դ���

	pso.PSOgenerations = PSOgenerations;
	pso.PSOparticle_num = PSOparticle_num;
	pso.PSOsetInitialV = PSOsetInitialV;
	pso.PSOsetV_numMAX = PSOsetV_numMAX;

	UpdateData(FALSE);

	CDialogEx::OnOK();
}
