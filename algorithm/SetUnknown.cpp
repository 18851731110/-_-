// SetUnknown.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "SetUnknown.h"
#include "afxdialogex.h"
#include "USVDoc.h"
#include "USVView.h"

extern Unknown unknown;//�ֲ�δ֪����

// SetUnknown �Ի���

IMPLEMENT_DYNAMIC(SetUnknown, CDialogEx)

SetUnknown::SetUnknown(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetUnknown::IDD, pParent)
	, UnknownR(0)
	, UnknownT(0)
{

}

SetUnknown::~SetUnknown()
{
}

void SetUnknown::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_UnknownR, UnknownR);
	DDX_Text(pDX, IDC_UnknownL, UnknownT);
}


BEGIN_MESSAGE_MAP(SetUnknown, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetUnknown::OnBnClickedOk)
END_MESSAGE_MAP()

// SetUnknown ��Ϣ�������

void SetUnknown::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);//���޴˸��£�д����ֵΪ�ϴε�ֵ

	unknown.UnknownR = UnknownR;
	unknown.UnknownT = UnknownT;

	UpdateData(FALSE);

	CDialogEx::OnOK();
}
