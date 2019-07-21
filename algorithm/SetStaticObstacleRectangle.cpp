// SetStaticObstacleRectangle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "SetStaticObstacleRectangle.h"
#include "SetStaticObstacleCircle.h"
#include "afxdialogex.h"
#include "USVDoc.h"
#include "USVView.h"
#include "math.h"
#include <afxdb.h>


// SetStaticObstacleRectangle �Ի���

extern StaticOR staticor[20];

extern StartGoalPOINT startgoalp;
extern bool state_staticOR;//���ξ�̬�ϰ���״̬

extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���

IMPLEMENT_DYNAMIC(SetStaticObstacleRectangle, CDialogEx)

SetStaticObstacleRectangle::SetStaticObstacleRectangle(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetStaticObstacleRectangle::IDD, pParent)
	, CenterX(0)
	, CenterY(0)
	, DirectionA(0)
	, HalfLength(0)
	, HalfWidth(0)
{

}

SetStaticObstacleRectangle::~SetStaticObstacleRectangle()
{
}

void SetStaticObstacleRectangle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_StaticObstacleaRectangle, LIST_StaticObstacleRec);
	DDX_Text(pDX, IDC_StaticObstacleCX, CenterX);
	DDV_MinMaxUInt(pDX, CenterX, 0, 1200);
	DDX_Text(pDX, IDC_StaticObstacleCY, CenterY);
	DDV_MinMaxUInt(pDX, CenterY, 0, 800);
	DDX_Text(pDX, IDC_StaticObstacleDA, DirectionA);
	DDV_MinMaxFloat(pDX, DirectionA, 0, 360);
	DDX_Text(pDX, IDC_StaticObstacleHL, HalfLength);
	DDV_MinMaxUInt(pDX, HalfLength, 0, 1200);
	DDX_Text(pDX, IDC_StaticObstacleHW, HalfWidth);
	DDV_MinMaxUInt(pDX, HalfWidth, 0, 800);
}


BEGIN_MESSAGE_MAP(SetStaticObstacleRectangle, CDialogEx)
	ON_BN_CLICKED(IDAddObstacleR, &SetStaticObstacleRectangle::OnBnClickedAddobstacler)
	ON_BN_CLICKED(IDDeleteObstacleR, &SetStaticObstacleRectangle::OnBnClickedDeleteobstacler)
	ON_BN_CLICKED(IDOK, &SetStaticObstacleRectangle::OnBnClickedOk)
	ON_BN_CLICKED(IDSObstacleCInputR, &SetStaticObstacleRectangle::OnBnClickedSobstaclecinputr)
	ON_BN_CLICKED(IDSObstacleCOutputR, &SetStaticObstacleRectangle::OnBnClickedSobstaclecoutputr)
END_MESSAGE_MAP()


// SetStaticObstacleRectangle ��Ϣ�������




BOOL SetStaticObstacleRectangle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString Field[6] = { "���", "���ĵ�X", "���ĵ�Y","�볤", "���","�����" };//�б��ӵı�ͷ
	LIST_StaticObstacleRec.InsertColumn(0, Field[0], LVCFMT_CENTER, 41);
	for (int j = 1; j<6; j++)
	{
		LIST_StaticObstacleRec.InsertColumn(j, Field[j], LVCFMT_CENTER, 60);				//�����ͷ����
	}
	//��ʼ�������	
	CenterX = 0;
	CenterY = 0;
	DirectionA = 0;
	HalfLength = 0;
	HalfWidth = 0;
	
	//���뾲̬�ϰ����������--���ʼĩ����ĺ�� ���������� ����
	for (UINT i = 0; i < 20; i++)
	{
		if (staticor[i].CenterPm != 0)
		{
			UpdateData(TRUE);

			int num = LIST_StaticObstacleRec.GetItemCount();

			CString stemp[6];
			stemp[0].Format("%d", num + 1);
			stemp[1].Format("%d", staticor[i].CenterX);
			stemp[2].Format("%d", staticor[i].CenterY);
			stemp[3].Format("%d", staticor[i].HalfL);
			stemp[4].Format("%d", staticor[i].HalfW);
			stemp[5].Format("%0.3f", staticor[i].Da);
			LIST_StaticObstacleRec.InsertItem(num, stemp[0]);		//������
			for (int j = 1; j < 6; j++)
			{
				LIST_StaticObstacleRec.SetItemText(num, j, stemp[j]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
			}
			UpdateData(false);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SetStaticObstacleRectangle::OnBnClickedAddobstacler()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (HalfLength != 0)
	{
		int num = LIST_StaticObstacleRec.GetItemCount();
		staticor[num].CenterX = CenterX;
		staticor[num].CenterY = CenterY;
		staticor[num].HalfL = HalfLength;
		staticor[num].HalfW = HalfWidth;
		staticor[num].Da = DirectionA;

		CalculateStaticOR(num);//���㷽���ϰ�������
		
		CString stemp[6];
		stemp[0].Format("%d", num + 1);
		stemp[1].Format("%d", CenterX);
		stemp[2].Format("%d", CenterY);
		stemp[3].Format("%d", HalfLength);
		stemp[4].Format("%d", HalfWidth);
		stemp[5].Format("%0.3f", DirectionA);

		LIST_StaticObstacleRec.InsertItem(num, stemp[0]);		//������
		for (int i = 1; i<6; i++)
		{
			LIST_StaticObstacleRec.SetItemText(num, i, stemp[i]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
		}
		
		CenterX = 0;
		CenterY = 0;
		DirectionA = 0;
		HalfLength = 0;
		HalfWidth = 0;
	}

	UpdateData(false);

}


void SetStaticObstacleRectangle::OnBnClickedDeleteobstacler()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int num = LIST_StaticObstacleRec.GetItemCount();
	while (LIST_StaticObstacleRec.DeleteItem(num - 1));
	staticor[num-1] = { 0 };
}


void SetStaticObstacleRectangle::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���
	
	int num = LIST_StaticObstacleRec.GetItemCount();

	//��staticor���鰴���ĵ㼫��ֵ  ���д�С��������
	for (int j = 0; j < num - 1; j++)
	{
		for (int i = 0; i < num - 1 - j; i++)
		{
			StaticOR temp;
			if (staticor[i].CenterPm>staticor[i + 1].CenterPm)
			{
				temp = staticor[i];
				staticor[i] = staticor[i + 1];
				staticor[i + 1] = temp;
			}
		}
	}

	if (staticor[0].HalfL != 0)
	{
		state_staticOR = 1;
	}
	CDialogEx::OnOK();
}


void SetStaticObstacleRectangle::CalculateStaticOR(int i)//���㷽���ϰ�������
{
	SetStaticObstacleCircle temp;
	staticor[i].CenterPm = sqrt(pow((float)abs(int(startgoalp.sx - staticor[i].CenterX)), 2) + pow((float)abs(int(startgoalp.sy - staticor[i].CenterY)), 2));//����
	staticor[i].CenterPa = temp.calculate_PolarAngle((float)staticor[i].CenterX, (float)staticor[i].CenterY);//����

	int tempX, tempY;
	float tempPA = 0.0 - staticor[i].Da * 2 * pi / 360;
	//�ֲ�����ϵ��0�Ķ���(��ʱ������)
	tempX = staticor[i].HalfL;
	tempY = staticor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[0].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[0].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[0].Pm = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[0].x), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[0].y), 2));//����;
	staticor[i].Peak[0].Pa = temp.calculate_PolarAngle(staticor[i].Peak[0].x, staticor[i].Peak[0].y);//����

	//�ֲ�����ϵ��0�Ķ���(��չ����)
	tempX = staticor[i].HalfL + safe_expandT;
	tempY = staticor[i].HalfW + safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[0].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[0].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[0].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[0].xEX), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[0].yEX), 2));//����;
	staticor[i].Peak[0].PaEX = temp.calculate_PolarAngle(staticor[i].Peak[0].xEX, staticor[i].Peak[0].yEX);//����

	//�ֲ�����ϵ��1�Ķ���
	tempX = staticor[i].HalfL;
	tempY = 0 - staticor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[1].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[1].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[1].x), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[1].y), 2));//����;
	staticor[i].Peak[1].Pa = temp.calculate_PolarAngle(staticor[i].Peak[1].x, staticor[i].Peak[1].y);//����

	//�ֲ�����ϵ��1�Ķ���(��չ����)
	tempX = staticor[i].HalfL + safe_expandT;
	tempY = 0 - staticor[i].HalfW - safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[1].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[1].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[1].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[1].yEX), 2));//����;
	staticor[i].Peak[1].PaEX = temp.calculate_PolarAngle(staticor[i].Peak[1].xEX, staticor[i].Peak[1].yEX);//����

	//�ֲ�����ϵ��2�Ķ���
	tempX = 0 - staticor[i].HalfL;
	tempY = 0 - staticor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[2].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[2].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[2].Pm = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[2].x), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[2].y), 2));//����;
	staticor[i].Peak[2].Pa = temp.calculate_PolarAngle(staticor[i].Peak[2].x, staticor[i].Peak[2].y);//����

	//�ֲ�����ϵ��2�Ķ���(��չ����)
	tempX = 0 - staticor[i].HalfL - safe_expandT;
	tempY = 0 - staticor[i].HalfW - safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[2].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[2].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[2].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[2].xEX), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[2].yEX), 2));//����;
	staticor[i].Peak[2].PaEX = temp.calculate_PolarAngle(staticor[i].Peak[2].xEX, staticor[i].Peak[2].yEX);//����

	//�ֲ�����ϵ��3�Ķ���
	tempX = 0 - staticor[i].HalfL;
	tempY = staticor[i].HalfW;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[3].x = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[3].y = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[3].x), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[3].y), 2));//����;
	staticor[i].Peak[3].Pa = temp.calculate_PolarAngle(staticor[i].Peak[3].x, staticor[i].Peak[3].y);//����

	//�ֲ�����ϵ��3�Ķ���(��չ����)
	tempX = 0 - staticor[i].HalfL - safe_expandT;
	tempY = staticor[i].HalfW + safe_expandT;
	//�Ӿֲ�����ϵת����ȫ������ϵ
	staticor[i].Peak[3].xEX = (float)tempX * cos(tempPA) - (float)tempY * sin(tempPA) + (float)staticor[i].CenterX;
	staticor[i].Peak[3].yEX = (float)tempX * sin(tempPA) + (float)tempY * cos(tempPA) + (float)staticor[i].CenterY;
	staticor[i].Peak[3].PmEX = sqrt(pow((float)abs((float)startgoalp.sx - staticor[i].Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - staticor[i].Peak[3].yEX), 2));//����;
	staticor[i].Peak[3].PaEX = temp.calculate_PolarAngle(staticor[i].Peak[3].xEX, staticor[i].Peak[3].yEX);//����

	//���ĸ����㰴pm��������
	//�ҳ���Сֵ���±�
	float min = 0.0;
	int flag = 0;
	for (int m = 0; m < 4; m++)
	{
		if (m == 0)
		{
			min = staticor[i].Peak[0].Pm;
			flag = 0;
		}
		else
		{
			if (min>staticor[i].Peak[m].Pm)
			{
				min = staticor[i].Peak[m].Pm;
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
		tempPeak = staticor[i].Peak[0];
		staticor[i].Peak[0] = staticor[i].Peak[1];
		staticor[i].Peak[1] = staticor[i].Peak[2];
		staticor[i].Peak[2] = staticor[i].Peak[3];
		staticor[i].Peak[3] = tempPeak;
	}
	else if (flag == 2)
	{
		tempPeak = staticor[i].Peak[0];
		staticor[i].Peak[0] = staticor[i].Peak[2];
		staticor[i].Peak[2] = tempPeak;
		tempPeak = staticor[i].Peak[3];
		staticor[i].Peak[3] = staticor[i].Peak[1];
		staticor[i].Peak[1] = tempPeak;
	}
	else if (flag == 3)
	{
		tempPeak = staticor[i].Peak[0];
		staticor[i].Peak[0] = staticor[i].Peak[3];
		staticor[i].Peak[3] = staticor[i].Peak[2];
		staticor[i].Peak[2] = staticor[i].Peak[1];
		staticor[i].Peak[1] = tempPeak;
	}
}

void SetStaticObstacleRectangle::OnBnClickedSobstaclecinputr()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE, //TRUE��FALSE��TRUEΪ���ļ���FALSEΪ�����ļ�
		"xls", //Ϊȱʡ����չ��
		"FileList", //Ϊ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Ϊ�Ի�����һ��ΪOFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,������ֻ��ѡ��͸��������ļ�ǰ��ʾ�� 
		"Excel �ļ�(*.xls)|*.xls||"//Ϊ�����б�������ʾ�ļ�����
		);
	dlg.m_ofn.lpstrTitle = "���뾲̬�ϰ����������";

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
	CString sSql, arr[6];

	sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", sDriver, strFilePath, strFilePath);
	if (!db.OpenEx(sSql, CDatabase::noOdbcDialog))//��������ԴDJB��xls
	{
		MessageBox("��EXCEL�ļ�ʧ��!", "����");
		return;
	}
	//��EXCEL��
	CRecordset pset(&db);
	LIST_StaticObstacleRec.DeleteAllItems();

	//AfxMessageBox("OK");
	/* sSql = "SELECT ѧ��,����,�ɼ� "
	"FROM EXCELDEMO";      */
	// "ORDER BY ����";
	sSql.Format("SELECT ���,���ĵ�X, ���ĵ�Y, �볤, ���, ����� FROM ��̬�ϰ����������"); 
	pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
	while (!pset.IsEOF())
	{
		pset.GetFieldValue("���", arr[0]);//ǰ���ֶα�������е���ͬ���������
		pset.GetFieldValue("���ĵ�X", arr[1]);
		pset.GetFieldValue("���ĵ�Y", arr[2]);
		pset.GetFieldValue("�볤", arr[3]);
		pset.GetFieldValue("���", arr[4]);
		pset.GetFieldValue("�����", arr[5]);

		int count = LIST_StaticObstacleRec.GetItemCount();//���뵽ListCtrl��
		LIST_StaticObstacleRec.InsertItem(count, arr[0]);
		LIST_StaticObstacleRec.SetItemText(count, 1, arr[1]);
		LIST_StaticObstacleRec.SetItemText(count, 2, arr[2]);
		LIST_StaticObstacleRec.SetItemText(count, 3, arr[3]);
		LIST_StaticObstacleRec.SetItemText(count, 4, arr[4]);
		LIST_StaticObstacleRec.SetItemText(count, 5, arr[5]);

		pset.MoveNext();
	}
	db.Close();

	int num = LIST_StaticObstacleRec.GetItemCount();

	for (int i = 0; i < 20; i++)
	{
	staticor[i] = { 0 };//����
	}
	//���б�������ӽ�����staticor[]
	for (int i = 0; i < num; i++)
	{
	staticor[i].CenterX = atoi(LIST_StaticObstacleRec.GetItemText(i, 1));
	staticor[i].CenterY = atoi(LIST_StaticObstacleRec.GetItemText(i, 2));
	staticor[i].HalfL = atoi(LIST_StaticObstacleRec.GetItemText(i, 3));
	staticor[i].HalfW = atoi(LIST_StaticObstacleRec.GetItemText(i, 4));
	staticor[i].Da = atof(LIST_StaticObstacleRec.GetItemText(i, 5));
	CalculateStaticOR(i);//���㷽���ϰ�������
	}

	MessageBox("Excel���ݳɹ�����ϵͳ!", "����ɹ�");
}


void SetStaticObstacleRectangle::OnBnClickedSobstaclecoutputr()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (LIST_StaticObstacleRec.GetItemCount() <= 0)
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

			iColumnNum = LIST_StaticObstacleRec.GetHeaderCtrl()->GetItemCount();
			iRowCount = LIST_StaticObstacleRec.GetItemCount();

			sSql = " CREATE TABLE ��̬�ϰ���������� ( ";
			strInsert = " INSERT INTO ��̬�ϰ���������� ( ";
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for (i = 0; i< iColumnNum; i++)
			{
				if (!(LIST_StaticObstacleRec.GetColumn(i, &lvCol)))
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
					LIST_StaticObstacleRec.GetItemText(j, i, chTemp, 33);
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

		AfxMessageBox("���澲̬�ϰ����������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}

PointInRC SetStaticObstacleRectangle::calculate_pointInRC(REC Peak0, REC Peak1, REC Peak2, REC Peak3, float x, float y)//������ھ��ε��Ǹ�λ�ã���9����
{
	float y01, y12, y23, y30, tempX1, tempX2, tempY1, tempY2;
	PointInRC pointInRC = {};

	//��ʾ����ϵ�¼��㣬���ؼ�����ϵ��ֵ
	//01
	tempX1 = Peak0.xEX;
	tempX2 = Peak1.xEX;
	tempY1 = Peak0.yEX;
	tempY2 = Peak1.yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y01 = x - tempX1;
	}
	else
	{
		y01 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//12
	tempX1 = Peak1.xEX;
	tempX2 = Peak2.xEX;
	tempY1 = Peak1.yEX;
	tempY2 = Peak2.yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y12 = x - tempX1;
	}
	else
	{
		y12 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//23
	tempX1 = Peak2.xEX;
	tempX2 = Peak3.xEX;
	tempY1 = Peak2.yEX;
	tempY2 = Peak3.yEX;
	if ((tempX1 - tempX2) == 0)
	{
		y23 = x - tempX1;
	}
	else
	{
		y23 = (tempY1 - tempY2) / (tempX1 - tempX2) * (x - tempX1) + tempY1 - y;
	}

	//30
	tempX1 = Peak3.xEX;
	tempX2 = Peak0.xEX;
	tempY1 = Peak3.yEX;
	tempY2 = Peak0.yEX;
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
