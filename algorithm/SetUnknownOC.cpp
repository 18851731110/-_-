// SetUnknownOC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "SetUnknownOC.h"
#include "USVDoc.h"
#include "USVView.h"
#include "SetDynamicOC.h"
#include "afxdialogex.h"
#include "SetStaticObstacleCircle.h"
#include "math.h"
#include <afxdb.h>

extern UnknownOC unknownoc[20];
extern StartGoalPOINT startgoalp;
extern bool state_unknownOC;//Բ��δ֪�ϰ���״̬
extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���
extern Unknown unknown;//�ֲ�δ֪����

SetStaticObstacleCircle calculate_PA1;

// SetUnknownOC �Ի���

IMPLEMENT_DYNAMIC(SetUnknownOC, CDialogEx)

SetUnknownOC::SetUnknownOC(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetUnknownOC::IDD, pParent)
	, UnknownOC_X(0)
	, UnknownOC_Y(0)
	, UnknownOC_R(0)
	, UnknownOC_DA(0)
	, UnknownOC_V(0)
{

}

SetUnknownOC::~SetUnknownOC()
{
}

void SetUnknownOC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_UnknownOC, LIST_UnknownOC);
	DDX_Text(pDX, IDC_UnknownOC_X, UnknownOC_X);
	DDV_MinMaxUInt(pDX, UnknownOC_X, 0, 2000);
	DDX_Text(pDX, IDC_UnknownOC_Y, UnknownOC_Y);
	DDV_MinMaxUInt(pDX, UnknownOC_Y, 0, 2000);
	DDX_Text(pDX, IDC_Unknown_R, UnknownOC_R);
	DDV_MinMaxUInt(pDX, UnknownOC_R, 0, 2000);
	DDX_Text(pDX, IDC_Unknown_DA, UnknownOC_DA);
	DDX_Text(pDX, IDC_Unknown_V, UnknownOC_V);
}


BEGIN_MESSAGE_MAP(SetUnknownOC, CDialogEx)
	ON_BN_CLICKED(IDAddUnknownOC, &SetUnknownOC::OnBnClickedAddunknownoc)
	ON_BN_CLICKED(IDDeleteUnknownOC, &SetUnknownOC::OnBnClickedDeleteunknownoc)
	ON_BN_CLICKED(IDOK, &SetUnknownOC::OnBnClickedOk)
	ON_BN_CLICKED(IDSUnknownOCIutput, &SetUnknownOC::OnBnClickedSunknownociutput)
	ON_BN_CLICKED(IDSUnknownOCOutput, &SetUnknownOC::OnBnClickedSunknownocoutput)
END_MESSAGE_MAP()


// SetUnknownOC ��Ϣ�������


BOOL SetUnknownOC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString Field[6] = { "���", "X����", "Y����", "�����", "�����", "�ٶ�" };	//�б��ӵı�ͷ
	LIST_UnknownOC.InsertColumn(0, Field[0], LVCFMT_CENTER, 40);
	for (int j = 1; j<6; j++)
	{
		LIST_UnknownOC.InsertColumn(j, Field[j], LVCFMT_CENTER, 61);				//�����ͷ����
	}
	//��ʼ�������	
	UnknownOC_X = 0;
	UnknownOC_Y = 0;
	UnknownOC_R = 0;
	UnknownOC_DA = 0.0;
	UnknownOC_V = 0.0;

	//���뾲̬�ϰ��Բ������--���ʼĩ����ĺ�� ���������� ����
	for (UINT i = 0; i < 20; i++)
	{
		if (unknownoc[i].r != 0)
		{
			UpdateData(TRUE);

			int num = LIST_UnknownOC.GetItemCount();

			CString stemp[6];
			stemp[0].Format("%d", num + 1);
			stemp[1].Format("%d", unknownoc[i].x);
			stemp[2].Format("%d", unknownoc[i].y);
			stemp[3].Format("%d", unknownoc[i].r);
			stemp[4].Format("%0.3f", unknownoc[i].Da);
			stemp[5].Format("%0.3f", unknownoc[i].V);

			LIST_UnknownOC.InsertItem(num, stemp[0]);		//������
			for (int j = 1; j < 6; j++)
			{
				LIST_UnknownOC.SetItemText(num, j, stemp[j]);	//���ø��еĲ�ͬ�е���ʾ�ַ�
			}
			UpdateData(false);
		}
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SetUnknownOC::OnBnClickedAddunknownoc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (UnknownOC_R != 0)
	{
		int num = LIST_UnknownOC.GetItemCount();

		CString stemp[6];
		stemp[0].Format("%d", num + 1);
		stemp[1].Format("%d", UnknownOC_X);
		stemp[2].Format("%d", UnknownOC_Y);
		stemp[3].Format("%d", UnknownOC_R);
		stemp[4].Format("%0.3f", UnknownOC_DA);
		stemp[5].Format("%0.3f", UnknownOC_V);

		LIST_UnknownOC.InsertItem(num, stemp[0]);		//������
		for (int i = 1; i<6; i++)
		{
			LIST_UnknownOC.SetItemText(num, i, stemp[i]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
		}
		UnknownOC_X = 0;
		UnknownOC_Y = 0;
		UnknownOC_R = 0;
		UnknownOC_DA = 0.0;
		UnknownOC_V = 0.0;
	}

	UpdateData(false);
}


void SetUnknownOC::OnBnClickedDeleteunknownoc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int num = LIST_UnknownOC.GetItemCount();
	while (LIST_UnknownOC.DeleteItem(num - 1));
}


void SetUnknownOC::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���

	int num = LIST_UnknownOC.GetItemCount();

	for (int i = 0; i < 20; i++)
	{
		unknownoc[i] = { 0 };//����
	}
	//���б�������ӽ�����staticoc[]
	for (int i = 0; i < num; i++)
	{
		unknownoc[i].x = atoi(LIST_UnknownOC.GetItemText(i, 1));
		unknownoc[i].y = atoi(LIST_UnknownOC.GetItemText(i, 2));
		unknownoc[i].r = atoi(LIST_UnknownOC.GetItemText(i, 3));
		unknownoc[i].Da = atof(LIST_UnknownOC.GetItemText(i, 4));
		unknownoc[i].V = atof(LIST_UnknownOC.GetItemText(i, 5));

		unknownoc[i].pm = sqrt(pow((float)abs(int(startgoalp.sx - unknownoc[i].x)), 2) + pow((float)abs(int(startgoalp.sy - unknownoc[i].y)), 2));//����
		unknownoc[i].pa = calculate_PA1.calculate_PolarAngle((float)unknownoc[i].x, (float)unknownoc[i].y);//����
	}

	//��staticoc���鰴����ֵ  ���д�С��������
	for (int j = 0; j < num - 1; j++)
	{
		for (int i = 0; i < num - 1 - j; i++)
		{
			UnknownOC temp;
			if (unknownoc[i].pm>unknownoc[i + 1].pm)
			{
				temp = unknownoc[i];
				unknownoc[i] = unknownoc[i + 1];
				unknownoc[i + 1] = temp;
			}
		}
	}

	if (unknownoc[0].r != 0)
	{
		state_unknownOC = 1;
	}

	calculate_unknownOC();

	CDialogEx::OnOK();
}

void SetUnknownOC::calculate_unknownOC()//����δ֪�ϰ�Բ������
{
	float tempL;
	for (int i = 0; unknownoc[i].r != 0; i++)
	{
		tempL = unknownoc[i].V * unknown.UnknownT * drawscale * Kn_ms;
		unknownoc[i].xEX = unknownoc[i].x + tempL * cos(unknownoc[i].Da*pi / 180) / 2;
		unknownoc[i].yEX = unknownoc[i].y - tempL * sin(unknownoc[i].Da*pi / 180) / 2;
		unknownoc[i].rEX = unknownoc[i].r + tempL;
		unknownoc[i].pmEX = sqrt(pow(abs((float)startgoalp.sx - unknownoc[i].xEX), 2) + pow(abs((float)startgoalp.sy - unknownoc[i].yEX), 2));//����;
	}
}

void SetUnknownOC::OnBnClickedSunknownociutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE, //TRUE��FALSE��TRUEΪ���ļ���FALSEΪ�����ļ�
		"xls", //Ϊȱʡ����չ��
		"FileList", //Ϊ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Ϊ�Ի�����һ��ΪOFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,������ֻ��ѡ��͸��������ļ�ǰ��ʾ�� 
		"Excel �ļ�(*.xls)|*.xls||"//Ϊ�����б�������ʾ�ļ�����
		);
	dlg.m_ofn.lpstrTitle = "����δ֪�ϰ��Բ������";

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
	LIST_UnknownOC.DeleteAllItems();

	//AfxMessageBox("OK");
	/* sSql = "SELECT ѧ��,����,�ɼ� "
	"FROM EXCELDEMO";      */
	// "ORDER BY ����";
	sSql.Format("SELECT ���,X����,Y����,�����, �����, �ٶ� ,����, ���� FROM δ֪�ϰ��Բ������");
	pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
	while (!pset.IsEOF())
	{
		pset.GetFieldValue("���", arr[0]);//ǰ���ֶα�������е���ͬ���������
		pset.GetFieldValue("X����", arr[1]);
		pset.GetFieldValue("Y����", arr[2]);
		pset.GetFieldValue("�����", arr[3]);
		pset.GetFieldValue("�����", arr[4]);
		pset.GetFieldValue("�ٶ�", arr[5]);

		int count = LIST_UnknownOC.GetItemCount();//���뵽ListCtrl��
		LIST_UnknownOC.InsertItem(count, arr[0]);
		LIST_UnknownOC.SetItemText(count, 1, arr[1]);
		LIST_UnknownOC.SetItemText(count, 2, arr[2]);
		LIST_UnknownOC.SetItemText(count, 3, arr[3]);
		LIST_UnknownOC.SetItemText(count, 4, arr[4]);
		LIST_UnknownOC.SetItemText(count, 5, arr[5]);

		pset.MoveNext();
	}
	db.Close();

	MessageBox("Excel���ݳɹ�����ϵͳ!", "����ɹ�");
}


void SetUnknownOC::OnBnClickedSunknownocoutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (LIST_UnknownOC.GetItemCount() <= 0)
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
	dlg.m_ofn.lpstrTitle = "δ֪�ϰ��Բ���������Ϊ";

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

			iColumnNum = LIST_UnknownOC.GetHeaderCtrl()->GetItemCount();
			iRowCount = LIST_UnknownOC.GetItemCount();

			sSql = " CREATE TABLE δ֪�ϰ��Բ������ ( ";
			strInsert = " INSERT INTO δ֪�ϰ��Բ������ ( ";
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for (i = 0; i< iColumnNum; i++)
			{
				if (!(LIST_UnknownOC.GetColumn(i, &lvCol)))
					return;
				if (i<iColumnNum - 1)
				{
					sSql = sSql + lvCol.pszText + " TEXT , ";
					strInsert = strInsert + lvCol.pszText + " , ";
				}
				else
				{
					sSql = sSql + lvCol.pszText + " TEXT , " + "���� TEXT," + "���� TEXT)";
					strInsert = strInsert + lvCol.pszText + ", ���� ," + "���� " + " )  VALUES ( ";
				}
			}

			//����Excel����ļ�
			database.ExecuteSQL(sSql);

			//ѭ����ȡ��¼�����뵽EXCEL��
			sSql = strInsert;
			char chTemp[33];
			int tempx, tempy;
			float tempPm, tempPa;
			for (j = 0; j<iRowCount; j++)
			{
				memset(chTemp, 0, 33);
				for (i = 0; i<iColumnNum; i++)
				{
					LIST_UnknownOC.GetItemText(j, i, chTemp, 33);
					if (i < (iColumnNum - 1))
					{
						sSql = sSql + "'" + chTemp + "' , ";
					}
					else
					{
						//sSql = sSql + "'" + chTemp + "' ) ";

						tempx = atoi(LIST_UnknownOC.GetItemText(j, 1));
						tempy = atoi(LIST_UnknownOC.GetItemText(j, 2));
						tempPm = sqrt(pow((float)abs(int(startgoalp.sx - tempx)), 2) + pow((float)abs(int(startgoalp.sy - tempy)), 2));//����
						tempPa = calculate_PA1.calculate_PolarAngle((float)tempx, (float)tempy);//����
						CString stemp[2];
						stemp[0].Format("%f", tempPm);
						stemp[1].Format("%f", tempPa);

						sSql = sSql + "'" + chTemp + "' , " + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' ) ";
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

		AfxMessageBox("����δ֪�ϰ��Բ������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}
