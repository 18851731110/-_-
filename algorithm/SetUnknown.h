#pragma once


// SetUnknown �Ի���

class SetUnknown : public CDialogEx
{
	DECLARE_DYNAMIC(SetUnknown)

public:
	SetUnknown(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetUnknown();

// �Ի�������
	enum { IDD = IDD_Set_Unknown };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float UnknownR;
	float UnknownT;
	afx_msg void OnBnClickedOk();
};
