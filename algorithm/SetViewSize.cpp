// SetViewSize.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "USVDoc.h"
#include "USVView.h"
#include "SetViewSize.h"
#include "afxdialogex.h"

extern ViewSize viewsize;//��ͼ��С

// SetViewSize �Ի���

IMPLEMENT_DYNAMIC(SetViewSize, CDialogEx)

SetViewSize::SetViewSize(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetViewSize::IDD, pParent)
	, setviewL(0)
	, setviewW(0)
	, SetViewChange(FALSE)
{
}

SetViewSize::~SetViewSize()
{
}

void SetViewSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SetViewLength, setviewL);
	DDX_Text(pDX, IDC_SetViewWidth, setviewW);
	DDX_Check(pDX, IDC_Change, SetViewChange);
	DDX_Control(pDX, IDC_SetViewLength, setviewLC);
	DDX_Control(pDX, IDC_SetViewWidth, setviewWC);
}


BEGIN_MESSAGE_MAP(SetViewSize, CDialogEx)
	ON_BN_CLICKED(IDOK, &SetViewSize::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Change, &SetViewSize::OnBnClickedChange)
END_MESSAGE_MAP()


// SetViewSize ��Ϣ�������


void SetViewSize::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);//���޴˸��£�д����ֵΪ�ϴε�ֵ

	viewsize.W = setviewL ;
	viewsize.H = setviewW ;
	viewsize.change=SetViewChange;
	UpdateData(FALSE);
	
	CDialogEx::OnOK();
}


void SetViewSize::OnBnClickedChange()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
		
	if (SetViewChange)
	{
		SetViewChange = FALSE;
	}
	else
	{
		SetViewChange = TRUE;
	}
	if (SetViewChange)
	{
		setviewLC.EnableWindow(FALSE);
		setviewWC.EnableWindow(FALSE);
	}
	if (!SetViewChange)
	{
		setviewLC.EnableWindow(TRUE); 
		setviewWC.EnableWindow(TRUE);
	}
}


BOOL SetViewSize::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	if (SetViewChange)
	{
		setviewLC.EnableWindow(FALSE);
		setviewWC.EnableWindow(FALSE);
	}
	if (!SetViewChange)
	{
		setviewLC.EnableWindow(TRUE);
		setviewWC.EnableWindow(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
