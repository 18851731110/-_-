// SetDynamicOC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "USV.h"
#include "USVDoc.h"
#include "USVView.h"
#include "SetDynamicOC.h"
#include "afxdialogex.h"
#include "SetStaticObstacleCircle.h"
#include "math.h"
#include <afxdb.h>

extern DynamicOC dynamicoc[20];
extern StartGoalPOINT startgoalp;
extern bool state_dynamicOC;//Բ�ζ�̬�ϰ���״̬
extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���

SetStaticObstacleCircle calculate_PA;

// SetDynamicOC �Ի���

IMPLEMENT_DYNAMIC(SetDynamicOC, CDialogEx)

SetDynamicOC::SetDynamicOC(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetDynamicOC::IDD, pParent)
	, DynamicOC_X(0)
	, DynamicOC_Y(0)
	, DynamicOC_R(0)
	, DynamicOC_DA(0)
	, DynamicOC_V(0)
{

}

SetDynamicOC::~SetDynamicOC()
{
}

void SetDynamicOC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DynamicOC_X, DynamicOC_X);
	DDV_MinMaxUInt(pDX, DynamicOC_X, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOC_Y, DynamicOC_Y);
	DDV_MinMaxUInt(pDX, DynamicOC_Y, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOC_R, DynamicOC_R);
	DDV_MinMaxUInt(pDX, DynamicOC_R, 0, 2000);
	DDX_Text(pDX, IDC_DynamicOC_DA, DynamicOC_DA);
	//DDV_MinMaxUInt(pDX, DynamicOC_DA, 0.0, 360.0);
	DDX_Text(pDX, IDC_DynamicOC_V, DynamicOC_V);
	//DDV_MinMaxUInt(pDX, DynamicOC_V, 0.0, 200.0);
	DDX_Control(pDX, IDC_LIST_DynamicOC, LIST_DynamicOC);
}


BEGIN_MESSAGE_MAP(SetDynamicOC, CDialogEx)
	ON_BN_CLICKED(IDAddDynamicOC, &SetDynamicOC::OnBnClickedAddDynamicoc)
	ON_BN_CLICKED(IDDeleteDynamicOC, &SetDynamicOC::OnBnClickedDeletedynamicoc)
	ON_BN_CLICKED(IDOK, &SetDynamicOC::OnBnClickedOk)
	ON_BN_CLICKED(IDSDynamicOCIutput, &SetDynamicOC::OnBnClickedSdynamicociutput)
	ON_BN_CLICKED(IDSDynamicOCOutputC, &SetDynamicOC::OnBnClickedSdynamicocoutputc)
END_MESSAGE_MAP()


// SetDynamicOC ��Ϣ�������


BOOL SetDynamicOC::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString Field[6] = { "���", "X����", "Y����", "�����", "�����", "�ٶ�" };	//�б��ӵı�ͷ
	LIST_DynamicOC.InsertColumn(0, Field[0], LVCFMT_CENTER, 40);
	for (int j = 1; j<6; j++)
	{
		LIST_DynamicOC.InsertColumn(j, Field[j], LVCFMT_CENTER, 61);				//�����ͷ����
	}
	//��ʼ�������	
	DynamicOC_X = 0;
	DynamicOC_Y = 0;
	DynamicOC_R = 0;
	DynamicOC_DA = 0.0;
	DynamicOC_V = 0.0;

	//���뾲̬�ϰ��Բ������--���ʼĩ����ĺ�� ���������� ����
	for (UINT i = 0; i < 20; i++)
	{
		if (dynamicoc[i].r != 0)
		{
			UpdateData(TRUE);

			int num = LIST_DynamicOC.GetItemCount();

			CString stemp[6];
			stemp[0].Format("%d", num + 1);
			stemp[1].Format("%d", dynamicoc[i].x);
			stemp[2].Format("%d", dynamicoc[i].y);
			stemp[3].Format("%d", dynamicoc[i].r);
			stemp[4].Format("%0.3f", dynamicoc[i].Da);
			stemp[5].Format("%0.3f", dynamicoc[i].V);

			LIST_DynamicOC.InsertItem(num, stemp[0]);		//������
			for (int j = 1; j < 6; j++)
			{
				LIST_DynamicOC.SetItemText(num, j, stemp[j]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
			}
			UpdateData(false);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SetDynamicOC::OnBnClickedAddDynamicoc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (DynamicOC_R != 0)
	{
		int num = LIST_DynamicOC.GetItemCount();

		CString stemp[6];
		stemp[0].Format("%d", num + 1);
		stemp[1].Format("%d", DynamicOC_X);
		stemp[2].Format("%d", DynamicOC_Y);
		stemp[3].Format("%d", DynamicOC_R);
		stemp[4].Format("%0.3f", DynamicOC_DA);
		stemp[5].Format("%0.3f", DynamicOC_V);

		LIST_DynamicOC.InsertItem(num, stemp[0]);		//������
		for (int i = 1; i<6; i++)
		{
			LIST_DynamicOC.SetItemText(num, i, stemp[i]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
		}
		DynamicOC_X = 0;
		DynamicOC_Y = 0;
		DynamicOC_R = 0;
		DynamicOC_DA = 0.0;
		DynamicOC_V = 0.0;
	}

	UpdateData(false);
}

void SetDynamicOC::OnBnClickedDeletedynamicoc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int num = LIST_DynamicOC.GetItemCount();
	while (LIST_DynamicOC.DeleteItem(num - 1));
}

void SetDynamicOC::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���

	int num = LIST_DynamicOC.GetItemCount();

	for (int i = 0; i < 20; i++)
	{
		dynamicoc[i] = { 0 };//����
	}
	//���б�������ӽ�����staticoc[]
	for (int i = 0; i < num; i++)
	{
		dynamicoc[i].x = atoi(LIST_DynamicOC.GetItemText(i, 1));
		dynamicoc[i].y = atoi(LIST_DynamicOC.GetItemText(i, 2));
		dynamicoc[i].r = atoi(LIST_DynamicOC.GetItemText(i, 3));
		dynamicoc[i].Da = atof(LIST_DynamicOC.GetItemText(i, 4));
		dynamicoc[i].V = atof(LIST_DynamicOC.GetItemText(i, 5));

		dynamicoc[i].pm = sqrt(pow((float)abs(int(startgoalp.sx - dynamicoc[i].x)), 2) + pow((float)abs(int(startgoalp.sy - dynamicoc[i].y)), 2));//����
		dynamicoc[i].pa = calculate_PA.calculate_PolarAngle((float)dynamicoc[i].x, (float)dynamicoc[i].y);//����
	}

	//��staticoc���鰴����ֵ  ���д�С��������
	for (int j = 0; j < num - 1; j++)
	{
		for (int i = 0; i < num - 1 - j; i++)
		{
			DynamicOC temp;
			if (dynamicoc[i].pm>dynamicoc[i + 1].pm)
			{
				temp = dynamicoc[i];
				dynamicoc[i] = dynamicoc[i + 1];
				dynamicoc[i + 1] = temp;
			}
		}
	}

	if (dynamicoc[0].r != 0)
	{
		state_dynamicOC = 1;
	}

	CDialogEx::OnOK();
}


void SetDynamicOC::OnBnClickedSdynamicociutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE, //TRUE��FALSE��TRUEΪ���ļ���FALSEΪ�����ļ�
		"xls", //Ϊȱʡ����չ��
		"FileList", //Ϊ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Ϊ�Ի�����һ��ΪOFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,������ֻ��ѡ��͸��������ļ�ǰ��ʾ�� 
		"Excel �ļ�(*.xls)|*.xls||"//Ϊ�����б�������ʾ�ļ�����
		);
	dlg.m_ofn.lpstrTitle = "���붯̬�ϰ��Բ������";

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
	LIST_DynamicOC.DeleteAllItems();

	//AfxMessageBox("OK");
	/* sSql = "SELECT ѧ��,����,�ɼ� "
	"FROM EXCELDEMO";      */
	// "ORDER BY ����";
	sSql.Format("SELECT ���,X����,Y����,�����, �����, �ٶ� ,����, ���� FROM ��̬�ϰ��Բ������");
	pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
	while (!pset.IsEOF())
	{
		pset.GetFieldValue("���", arr[0]);//ǰ���ֶα�������е���ͬ���������
		pset.GetFieldValue("X����", arr[1]);
		pset.GetFieldValue("Y����", arr[2]);
		pset.GetFieldValue("�����", arr[3]);
		pset.GetFieldValue("�����", arr[4]);
		pset.GetFieldValue("�ٶ�", arr[5]);

		int count = LIST_DynamicOC.GetItemCount();//���뵽ListCtrl��
		LIST_DynamicOC.InsertItem(count, arr[0]);
		LIST_DynamicOC.SetItemText(count, 1, arr[1]);
		LIST_DynamicOC.SetItemText(count, 2, arr[2]);
		LIST_DynamicOC.SetItemText(count, 3, arr[3]);
		LIST_DynamicOC.SetItemText(count, 4, arr[4]);
		LIST_DynamicOC.SetItemText(count, 5, arr[5]);

		pset.MoveNext();
	}
	db.Close();

	MessageBox("Excel���ݳɹ�����ϵͳ!", "����ɹ�");

}

void SetDynamicOC::OnBnClickedSdynamicocoutputc()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (LIST_DynamicOC.GetItemCount() <= 0)
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
	dlg.m_ofn.lpstrTitle = "��̬�ϰ��Բ���������Ϊ";

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

			iColumnNum = LIST_DynamicOC.GetHeaderCtrl()->GetItemCount();
			iRowCount = LIST_DynamicOC.GetItemCount();

			sSql = " CREATE TABLE ��̬�ϰ��Բ������ ( ";
			strInsert = " INSERT INTO ��̬�ϰ��Բ������ ( ";
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for (i = 0; i< iColumnNum; i++)
			{
				if (!(LIST_DynamicOC.GetColumn(i, &lvCol)))
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
					LIST_DynamicOC.GetItemText(j, i, chTemp, 33);
					if (i < (iColumnNum - 1))
					{
						sSql = sSql + "'" + chTemp + "' , ";
					}
					else
					{
						//sSql = sSql + "'" + chTemp + "' ) ";
						
						tempx = atoi(LIST_DynamicOC.GetItemText(j, 1));
						tempy = atoi(LIST_DynamicOC.GetItemText(j, 2));
						tempPm = sqrt(pow((float)abs(int(startgoalp.sx - tempx)), 2) + pow((float)abs(int(startgoalp.sy - tempy)), 2));//����
						tempPa = calculate_PA.calculate_PolarAngle((float)tempx, (float)tempy);//����
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

		AfxMessageBox("���涯̬�ϰ��Բ������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}
