// SetDynamicOR.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "SetDynamicOR.h"
#include "afxdialogex.h"
#include "SetStaticObstacleCircle.h"
#include "SetStaticObstacleRectangle.h"
#include "afxdialogex.h"
#include "USVDoc.h"
#include "USVView.h"
#include "math.h"
#include <afxdb.h>

extern DynamicOR dynamicor[20];
extern StartGoalPOINT startgoalp;
extern bool state_dynamicOR;//���ξ�̬�ϰ���״̬
extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���

// SetDynamicOR �Ի���

IMPLEMENT_DYNAMIC(SetDynamicOR, CDialogEx)

SetDynamicOR::SetDynamicOR(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetDynamicOR::IDD, pParent)
	, DynamicOR_X(0)
	, DynamicOR_Y(0)
	, DynamicOR_HL(0)
	, DynamicOR_HW(0)
	, DynamicOR_DA(0)
	, DynamicOR_V(0)
{

}

SetDynamicOR::~SetDynamicOR()
{
}

void SetDynamicOR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DynamicOR_X, DynamicOR_X);
	DDV_MinMaxUInt(pDX, DynamicOR_X, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOR_Y, DynamicOR_Y);
	DDV_MinMaxUInt(pDX, DynamicOR_Y, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOR_HL, DynamicOR_HL);
	DDV_MinMaxUInt(pDX, DynamicOR_HL, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOR_HW, DynamicOR_HW);
	DDV_MinMaxUInt(pDX, DynamicOR_HW, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOR_DA, DynamicOR_DA);
	DDV_MinMaxFloat(pDX, DynamicOR_DA, 0, 360);
	DDX_Text(pDX, IDC_DynamicOR_V, DynamicOR_V);
	DDV_MinMaxFloat(pDX, DynamicOR_V, 0, 200);
	DDX_Control(pDX, IDC_LIST_DynamicOR, LIST_DynamicOR);
}


BEGIN_MESSAGE_MAP(SetDynamicOR, CDialogEx)
	ON_BN_CLICKED(IDAddDynamicOR, &SetDynamicOR::OnBnClickedAdddynamicOR)
	ON_BN_CLICKED(IDDeleteDynamicOR, &SetDynamicOR::OnBnClickedDeletedynamicOR)
	ON_BN_CLICKED(IDOK, &SetDynamicOR::OnBnClickedOk)
	ON_BN_CLICKED(IDSDynamicORInput, &SetDynamicOR::OnBnClickedSdynamicorinput)
	ON_BN_CLICKED(IDSDynamicOROutput, &SetDynamicOR::OnBnClickedSdynamicoroutput)
END_MESSAGE_MAP()


// SetDynamicOR ��Ϣ�������


BOOL SetDynamicOR::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString Field[7] = { "���", "���ĵ�X", "���ĵ�Y", "�볤", "���", "�����", "�ٶ�" };//�б��ӵı�ͷ
	LIST_DynamicOR.InsertColumn(0, Field[0], LVCFMT_CENTER, 41);
	for (int j = 1; j<7; j++)
	{
		LIST_DynamicOR.InsertColumn(j, Field[j], LVCFMT_CENTER, 63);				//�����ͷ����
	}
	//��ʼ�������	
	DynamicOR_X = 0;
	DynamicOR_Y = 0;
	DynamicOR_HL = 0;
	DynamicOR_HW = 0;
	DynamicOR_DA = 0;
	DynamicOR_V = 0;

	//���뾲̬�ϰ����������--���ʼĩ����ĺ�� ���������� ����
	for (UINT i = 0; i < 20; i++)
	{
		if (dynamicor[i].CenterPm != 0)
		{
			UpdateData(TRUE);

			int num = LIST_DynamicOR.GetItemCount();

			CString stemp[7];
			stemp[0].Format("%d", num + 1);
			stemp[1].Format("%d", dynamicor[i].CenterX);
			stemp[2].Format("%d", dynamicor[i].CenterY);
			stemp[3].Format("%d", dynamicor[i].HalfL);
			stemp[4].Format("%d", dynamicor[i].HalfW);
			stemp[5].Format("%0.3f", dynamicor[i].Da);
			stemp[6].Format("%0.3f", dynamicor[i].V);
			LIST_DynamicOR.InsertItem(num, stemp[0]);		//������
			for (int j = 1; j < 7; j++)
			{
				LIST_DynamicOR.SetItemText(num, j, stemp[j]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
			}
			UpdateData(false);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SetDynamicOR::OnBnClickedAdddynamicOR()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if (DynamicOR_HL != 0)
	{
		int num = LIST_DynamicOR.GetItemCount();
		dynamicor[num].CenterX = DynamicOR_X;
		dynamicor[num].CenterY = DynamicOR_Y;
		dynamicor[num].HalfL = DynamicOR_HL;
		dynamicor[num].HalfW = DynamicOR_HW;
		dynamicor[num].Da = DynamicOR_DA;
		dynamicor[num].V = DynamicOR_V;

		CalculateDynamicOR(num);//���㷽���ϰ�������

		CString stemp[7];
		stemp[0].Format("%d", num + 1);
		stemp[1].Format("%d", DynamicOR_X);
		stemp[2].Format("%d", DynamicOR_Y);
		stemp[3].Format("%d", DynamicOR_HL);
		stemp[4].Format("%d", DynamicOR_HW);
		stemp[5].Format("%0.3f", DynamicOR_DA);
		stemp[6].Format("%0.3f", DynamicOR_V);

		LIST_DynamicOR.InsertItem(num, stemp[0]);		//������
		for (int i = 1; i<7; i++)
		{
			LIST_DynamicOR.SetItemText(num, i, stemp[i]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
		}

		DynamicOR_X = 0;
		DynamicOR_Y = 0;
		DynamicOR_HL = 0;
		DynamicOR_HW = 0;
		DynamicOR_DA = 0;
		DynamicOR_V = 0;
	}

	UpdateData(false);
}

void SetDynamicOR::OnBnClickedDeletedynamicOR()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int num = LIST_DynamicOR.GetItemCount();
	while (LIST_DynamicOR.DeleteItem(num - 1));
	dynamicor[num - 1] = { 0 };
}

void SetDynamicOR::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���

	int num = LIST_DynamicOR.GetItemCount();

	//��dynamicor���鰴���ĵ㼫��ֵ  ���д�С��������
	for (int j = 0; j < num - 1; j++)
	{
		for (int i = 0; i < num - 1 - j; i++)
		{
			DynamicOR temp;
			if (dynamicor[i].CenterPm>dynamicor[i + 1].CenterPm)
			{
				temp = dynamicor[i];
				dynamicor[i] = dynamicor[i + 1];
				dynamicor[i + 1] = temp;
			}
		}
	}

	if (dynamicor[0].HalfL != 0)
	{
		state_dynamicOR = 1;
	}
	
	CDialogEx::OnOK();
}

void SetDynamicOR::CalculateDynamicOR(int i)//���㷽���ϰ�������
{
	SetStaticObstacleCircle temp;
	dynamicor[i].CenterPm = sqrt(pow((float)abs(int(startgoalp.sx - dynamicor[i].CenterX)), 2) + pow((float)abs(int(startgoalp.sy - dynamicor[i].CenterY)), 2));//����
	dynamicor[i].CenterPa = temp.calculate_PolarAngle((float)dynamicor[i].CenterX, (float)dynamicor[i].CenterY);//����

	int tempX, tempY;
	float tempPA = 0.0 - dynamicor[i].Da * 2 * pi / 360;
	//�ֲ�����ϵ��0�Ķ���(��ʱ������)
	tempX = dynamicor[i].HalfL;
	tempY = dynamicor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[0].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[0].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[0].Pm = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[0].x), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[0].y), 2));//����;
	dynamicor[i].Peak[0].Pa = temp.calculate_PolarAngle(dynamicor[i].Peak[0].x, dynamicor[i].Peak[0].y);//����

	//�ֲ�����ϵ��0�Ķ���(��չ����)
	tempX = dynamicor[i].HalfL + safe_expandT;
	tempY = dynamicor[i].HalfW + safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[0].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[0].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[0].yEX), 2));//����;
	dynamicor[i].Peak[0].PaEX = temp.calculate_PolarAngle(dynamicor[i].Peak[0].xEX, dynamicor[i].Peak[0].yEX);//����

	//�ֲ�����ϵ��1�Ķ���
	tempX = dynamicor[i].HalfL;
	tempY = 0 - dynamicor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[1].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[1].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[1].x), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[1].y), 2));//����;
	dynamicor[i].Peak[1].Pa = temp.calculate_PolarAngle(dynamicor[i].Peak[1].x, dynamicor[i].Peak[1].y);//����

	//�ֲ�����ϵ��1�Ķ���(��չ����)
	tempX = dynamicor[i].HalfL + safe_expandT;
	tempY = 0 - dynamicor[i].HalfW - safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[1].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[1].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[1].yEX), 2));//����;
	dynamicor[i].Peak[1].PaEX = temp.calculate_PolarAngle(dynamicor[i].Peak[1].xEX, dynamicor[i].Peak[1].yEX);//����

	//�ֲ�����ϵ��2�Ķ���
	tempX = 0 - dynamicor[i].HalfL;
	tempY = 0 - dynamicor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[2].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[2].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[2].Pm = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[2].x), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[2].y), 2));//����;
	dynamicor[i].Peak[2].Pa = temp.calculate_PolarAngle(dynamicor[i].Peak[2].x, dynamicor[i].Peak[2].y);//����

	//�ֲ�����ϵ��2�Ķ���(��չ����)
	tempX = 0 - dynamicor[i].HalfL - safe_expandT;
	tempY = 0 - dynamicor[i].HalfW - safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[2].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[2].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[2].yEX), 2));//����;
	dynamicor[i].Peak[2].PaEX = temp.calculate_PolarAngle(dynamicor[i].Peak[2].xEX, dynamicor[i].Peak[2].yEX);//����

	//�ֲ�����ϵ��3�Ķ���
	tempX = 0 - dynamicor[i].HalfL;
	tempY = dynamicor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[3].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[3].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[3].x), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[3].y), 2));//����;
	dynamicor[i].Peak[3].Pa = temp.calculate_PolarAngle(dynamicor[i].Peak[3].x, dynamicor[i].Peak[3].y);//����

	//�ֲ�����ϵ��3�Ķ���(��չ����)
	tempX = 0 - dynamicor[i].HalfL - safe_expandT;
	tempY = dynamicor[i].HalfW + safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	dynamicor[i].Peak[3].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)dynamicor[i].CenterX;
	dynamicor[i].Peak[3].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)dynamicor[i].CenterY;
	dynamicor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - dynamicor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - dynamicor[i].Peak[3].yEX), 2));//����;
	dynamicor[i].Peak[3].PaEX = temp.calculate_PolarAngle(dynamicor[i].Peak[3].xEX, dynamicor[i].Peak[3].yEX);//����

	//���ĸ����㰴pm��������
	//�ҳ���Сֵ���±�
	float min = 0.0;
	int flag = 0;
	for (int m = 0; m < 4; m++)
	{
		if (m == 0)
		{
			min = dynamicor[i].Peak[0].Pm;
			flag = 0;
		}
		else
		{
			if (min>dynamicor[i].Peak[m].Pm)
			{
				min = dynamicor[i].Peak[m].Pm;
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
		tempPeak = dynamicor[i].Peak[0];
		dynamicor[i].Peak[0] = dynamicor[i].Peak[1];
		dynamicor[i].Peak[1] = dynamicor[i].Peak[2];
		dynamicor[i].Peak[2] = dynamicor[i].Peak[3];
		dynamicor[i].Peak[3] = tempPeak;
	}
	else if (flag == 2)
	{
		tempPeak = dynamicor[i].Peak[0];
		dynamicor[i].Peak[0] = dynamicor[i].Peak[2];
		dynamicor[i].Peak[2] = tempPeak;
		tempPeak = dynamicor[i].Peak[3];
		dynamicor[i].Peak[3] = dynamicor[i].Peak[1];
		dynamicor[i].Peak[1] = tempPeak;
	}
	else if (flag == 3)
	{
		tempPeak = dynamicor[i].Peak[0];
		dynamicor[i].Peak[0] = dynamicor[i].Peak[3];
		dynamicor[i].Peak[3] = dynamicor[i].Peak[2];
		dynamicor[i].Peak[2] = dynamicor[i].Peak[1];
		dynamicor[i].Peak[1] = tempPeak;
	}
}

void SetDynamicOR::OnBnClickedSdynamicorinput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, //TRUE��FALSE��TRUEΪ���ļ���FALSEΪ�����ļ�
		"xls", //Ϊȱʡ����չ��
		"FileList", //Ϊ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Ϊ�Ի�����һ��ΪOFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,������ֻ��ѡ��͸��������ļ�ǰ��ʾ�� 
		"Excel �ļ�(*.xls)|*.xls||"//Ϊ�����б�������ʾ�ļ�����
		);
	dlg.m_ofn.lpstrTitle = "���붯̬�ϰ����������";

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
	LIST_DynamicOR.DeleteAllItems();

	//AfxMessageBox("OK");
	/* sSql = "SELECT ѧ��,����,�ɼ� "
	"FROM EXCELDEMO";      */
	// "ORDER BY ����";
	sSql.Format("SELECT ���,���ĵ�X, ���ĵ�Y, �볤, ���, �����, �ٶ� FROM ��̬�ϰ����������");
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

		int count = LIST_DynamicOR.GetItemCount();//���뵽ListCtrl��
		LIST_DynamicOR.InsertItem(count, arr[0]);
		LIST_DynamicOR.SetItemText(count, 1, arr[1]);
		LIST_DynamicOR.SetItemText(count, 2, arr[2]);
		LIST_DynamicOR.SetItemText(count, 3, arr[3]);
		LIST_DynamicOR.SetItemText(count, 4, arr[4]);
		LIST_DynamicOR.SetItemText(count, 5, arr[5]);
		LIST_DynamicOR.SetItemText(count, 6, arr[6]);

		pset.MoveNext();
	}
	db.Close();

	int num = LIST_DynamicOR.GetItemCount();

	for (int i = 0; i < 20; i++)
	{
		dynamicor[i] = { 0 };//����
	}
	//���б�������ӽ�����dynamicor[]
	for (int i = 0; i < num; i++)
	{
		dynamicor[i].CenterX = atoi(LIST_DynamicOR.GetItemText(i, 1));
		dynamicor[i].CenterY = atoi(LIST_DynamicOR.GetItemText(i, 2));
		dynamicor[i].HalfL = atoi(LIST_DynamicOR.GetItemText(i, 3));
		dynamicor[i].HalfW = atoi(LIST_DynamicOR.GetItemText(i, 4));
		dynamicor[i].Da = atof(LIST_DynamicOR.GetItemText(i, 5));
		dynamicor[i].V = atof(LIST_DynamicOR.GetItemText(i, 6));
		CalculateDynamicOR(i);//���㷽���ϰ�������
	}

	MessageBox("Excel���ݳɹ�����ϵͳ!", "����ɹ�");
}

void SetDynamicOR::OnBnClickedSdynamicoroutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (LIST_DynamicOR.GetItemCount() <= 0)
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
	dlg.m_ofn.lpstrTitle = "USV��̬�ϰ�������������Ϊ";

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

			iColumnNum = LIST_DynamicOR.GetHeaderCtrl()->GetItemCount();
			iRowCount = LIST_DynamicOR.GetItemCount();

			sSql = " CREATE TABLE ��̬�ϰ���������� ( ";
			strInsert = " INSERT INTO ��̬�ϰ���������� ( ";
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for (i = 0; i< iColumnNum; i++)
			{
				if (!(LIST_DynamicOR.GetColumn(i, &lvCol)))
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
					LIST_DynamicOR.GetItemText(j, i, chTemp, 33);
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

		AfxMessageBox("���涯̬�ϰ����������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}

PointInRC SetDynamicOR::calculate_pointInDRC(int m, float x, float y)//������ھ��ε��Ǹ�λ�ã���9����
{
	float y01, y12, y23, y30, tempX1, tempX2, tempY1, tempY2;
	PointInRC pointInRC;

	//��ʾ����ϵ�¼��㣬���ؼ�����ϵ��ֵ
	//01
	tempX1 = dynamicor[m].Peak[0].xEX;
	tempX2 = dynamicor[m].Peak[1].xEX;
	tempY1 = dynamicor[m].Peak[0].yEX;
	tempY2 = dynamicor[m].Peak[1].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y01 = x - tempX1;
	}
	else
	{
		y01 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//12
	tempX1 = dynamicor[m].Peak[1].xEX;
	tempX2 = dynamicor[m].Peak[2].xEX;
	tempY1 = dynamicor[m].Peak[1].yEX;
	tempY2 = dynamicor[m].Peak[2].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y12 = x - tempX1;
	}
	else
	{
		y12 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//23
	tempX1 = dynamicor[m].Peak[2].xEX;
	tempX2 = dynamicor[m].Peak[3].xEX;
	tempY1 = dynamicor[m].Peak[2].yEX;
	tempY2 = dynamicor[m].Peak[3].yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y23 = x - tempX1;
	}
	else
	{
		y23 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//30
	tempX1 = dynamicor[m].Peak[3].xEX;
	tempX2 = dynamicor[m].Peak[0].xEX;
	tempY1 = dynamicor[m].Peak[3].yEX;
	tempY2 = dynamicor[m].Peak[0].yEX;
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