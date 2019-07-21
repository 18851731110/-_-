// SetStaticObstacleCircle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SetStaticObstacleCircle.h"
#include "afxdialogex.h"
#include "USVDoc.h"
#include "USVView.h"
#include "math.h"
#include <afxdb.h>

// SetStaticObstacleCircle �Ի���

extern StaticOC staticoc[20];
extern StartGoalPOINT startgoalp;
extern bool state_staticOC;//Բ�ξ�̬�ϰ���״̬

extern int testNum;//���Դ���
extern int thisPSOnum;//����pso���Դ���


IMPLEMENT_DYNAMIC(SetStaticObstacleCircle, CDialogEx)

SetStaticObstacleCircle::SetStaticObstacleCircle(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetStaticObstacleCircle::IDD, pParent)
	, StaticObstacleX(0)
	, StaticObstacleY(0)
	, StaticObstacleR(0)
{

}

SetStaticObstacleCircle::~SetStaticObstacleCircle()
{
}

void SetStaticObstacleCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_StaticObstacle, LIST_StaticObstacle);
	DDX_Text(pDX, IDC_StaticObstacleX, StaticObstacleX);
	DDV_MinMaxUInt(pDX, StaticObstacleX, 0, 1200);
	DDX_Text(pDX, IDC_StaticObstacleY, StaticObstacleY);
	DDV_MinMaxUInt(pDX, StaticObstacleY, 0, 800);
	DDX_Text(pDX, IDC_StaticObstacleR, StaticObstacleR);
	DDV_MinMaxUInt(pDX, StaticObstacleR, 0, 1200);
}


BEGIN_MESSAGE_MAP(SetStaticObstacleCircle, CDialogEx)

	ON_BN_CLICKED(IDAddObstacleC, &SetStaticObstacleCircle::OnBnClickedAddobstaclec)
	ON_BN_CLICKED(IDDeleteObstacleC, &SetStaticObstacleCircle::OnBnClickedDeleteobstaclec)
	ON_BN_CLICKED(IDOK, &SetStaticObstacleCircle::OnBnClickedOk)
	ON_EN_CHANGE(IDC_StaticObstacleY, &SetStaticObstacleCircle::OnEnChangeStaticobstacley)
	ON_BN_CLICKED(IDSObstacleCInput, &SetStaticObstacleCircle::OnBnClickedSobstaclecinput)
	ON_BN_CLICKED(IDSObstacleCOutput, &SetStaticObstacleCircle::OnBnClickedSobstaclecoutput)
END_MESSAGE_MAP()


// SetStaticObstacleCircle ��Ϣ�������



BOOL SetStaticObstacleCircle::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CString Field[6] = { "���", "X����", "Y����", "�����","����","����" };						//�б��ӵı�ͷ
	LIST_StaticObstacle.InsertColumn(0, Field[0], LVCFMT_CENTER, 41);
	for (int j = 1; j<6; j++)
	{
		LIST_StaticObstacle.InsertColumn(j, Field[j], LVCFMT_CENTER, 60);				//�����ͷ����
	}
	//��ʼ�������	
	StaticObstacleX = 0;
	StaticObstacleY = 0;
	StaticObstacleR = 0;

	//���뾲̬�ϰ��Բ������--���ʼĩ����ĺ�� ���������� ����
	for (UINT i = 0; i < 20; i++)
	{
		if (staticoc[i].r != 0)
		{
			UpdateData(TRUE);

			int num = LIST_StaticObstacle.GetItemCount();

			CString stemp[6];
			stemp[0].Format("%d", num+1);
			stemp[1].Format("%d", staticoc[i].x);
			stemp[2].Format("%d", staticoc[i].y);
			stemp[3].Format("%d", staticoc[i].r);
			float pm = sqrt(pow((float)abs(int(startgoalp.sx - staticoc[i].x)), 2) + pow((float)abs(int(startgoalp.sy - staticoc[i].y)), 2));//����
			float pa = calculate_PolarAngle((float)staticoc[i].x, (float)staticoc[i].y);//����
			stemp[4].Format("%0.3f", pm);
			stemp[5].Format("%0.3f", pa);
			LIST_StaticObstacle.InsertItem(num, stemp[0]);		//������
			for (int j = 1; j < 6; j++)
			{
				LIST_StaticObstacle.SetItemText(num, j, stemp[j]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
			}
			UpdateData(false);
		}
	}
	return TRUE;
	// return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void SetStaticObstacleCircle::OnBnClickedAddobstaclec()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	if (StaticObstacleR!=0)
	{
		int num = LIST_StaticObstacle.GetItemCount();
		
		float temp = sqrt(pow((float)abs(int(startgoalp.sx - StaticObstacleX)), 2) + pow((float)abs(int(startgoalp.sy - StaticObstacleY)), 2));//����

		CString stemp[6];
		stemp[0].Format("%d", num + 1);
		stemp[1].Format("%d", StaticObstacleX);
		stemp[2].Format("%d", StaticObstacleY);
		stemp[3].Format("%d", StaticObstacleR);
		stemp[4].Format("%0.3f", temp);
		stemp[5].Format("%0.3f", calculate_PolarAngle((float)StaticObstacleX, (float)StaticObstacleY));

		LIST_StaticObstacle.InsertItem(num, stemp[0]);		//������
		for (int i = 1; i<6; i++)
		{
			LIST_StaticObstacle.SetItemText(num, i, stemp[i]);					//���ø��еĲ�ͬ�е���ʾ�ַ�
		}
		StaticObstacleX = 0;
		StaticObstacleY = 0;
		StaticObstacleR = 0;
	}
	/*else
	{
		AfxMessageBox("�����Ӧ����0��");
		return;
	}*/
	UpdateData(false);
}


void SetStaticObstacleCircle::OnBnClickedDeleteobstaclec()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int num = LIST_StaticObstacle.GetItemCount();
	while (LIST_StaticObstacle.DeleteItem(num-1));
}


void SetStaticObstacleCircle::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	testNum = 0;//���Դ���
	thisPSOnum = 0;//����pso���Դ���

	int num = LIST_StaticObstacle.GetItemCount();

	for (int i = 0; i < 20; i++)
	{
		staticoc[i] = { 0 };//����
	}
	//���б�������ӽ�����staticoc[]
	for (int i = 0; i < num; i++)
	{
		staticoc[i].x = atoi(LIST_StaticObstacle.GetItemText(i, 1));
		staticoc[i].y = atoi(LIST_StaticObstacle.GetItemText(i, 2));
		staticoc[i].r = atoi(LIST_StaticObstacle.GetItemText(i, 3));
		staticoc[i].pm = atof(LIST_StaticObstacle.GetItemText(i, 4));
		staticoc[i].pa = atof(LIST_StaticObstacle.GetItemText(i, 5));
	}
	
	//��staticoc���鰴����ֵ  ���д�С��������
	for (int j = 0; j < num-1; j++)
	{
		for (int i = 0; i < num - 1-j; i++)
		{
			StaticOC temp;
			if (staticoc[i].pm>staticoc[i+1].pm)
			{
				temp = staticoc[i];
				staticoc[i] = staticoc[i + 1];
				staticoc[i + 1] = temp;
			}
		}
	}

	if (staticoc[0].r != 0)
	{
		state_staticOC = 1;
	}
	CDialogEx::OnOK();
}


void SetStaticObstacleCircle::OnEnChangeStaticobstacley()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void SetStaticObstacleCircle::OnBnClickedSobstaclecinput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CFileDialog dlg(TRUE, //TRUE��FALSE��TRUEΪ���ļ���FALSEΪ�����ļ�
		"xls", //Ϊȱʡ����չ��
		"FileList", //Ϊ��ʾ���ļ�����Ͽ�ı༭����ļ�����һ���ѡNULL 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,//Ϊ�Ի�����һ��ΪOFN_HIDEREADONLY   |   OFN_OVERWRITEPROMPT,������ֻ��ѡ��͸��������ļ�ǰ��ʾ�� 
		"Excel �ļ�(*.xls)|*.xls||"//Ϊ�����б�������ʾ�ļ�����
		);
	dlg.m_ofn.lpstrTitle = "���뾲̬�ϰ��Բ������";

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
	LIST_StaticObstacle.DeleteAllItems();

	//AfxMessageBox("OK");
	/* sSql = "SELECT ѧ��,����,�ɼ� "
	"FROM EXCELDEMO";      */
	// "ORDER BY ����";
	sSql.Format("SELECT ���,X����,Y����,�����,����,���� FROM ��̬�ϰ��Բ������");
	pset.Open(CRecordset::forwardOnly, sSql, CRecordset::readOnly);
	while (!pset.IsEOF())
	{
		pset.GetFieldValue("���", arr[0]);//ǰ���ֶα�������е���ͬ���������
		pset.GetFieldValue("X����", arr[1]);
		pset.GetFieldValue("Y����", arr[2]);
		pset.GetFieldValue("�����", arr[3]);

		UINT staticOCX = atoi(arr[1]);
		UINT staticOCY = atoi(arr[2]);
		float pm = sqrt(pow((float)abs(int(startgoalp.sx - staticOCX)), 2) + pow((float)abs(int(startgoalp.sy - staticOCY)), 2));//����
		float pa = calculate_PolarAngle((float)staticOCX, (float)staticOCY);//����
		arr[4].Format("%0.3f", pm);
		arr[5].Format("%0.3f", pa);

		int count = LIST_StaticObstacle.GetItemCount();//���뵽ListCtrl��
		LIST_StaticObstacle.InsertItem(count, arr[0]);
		LIST_StaticObstacle.SetItemText(count, 1, arr[1]);
		LIST_StaticObstacle.SetItemText(count, 2, arr[2]);
		LIST_StaticObstacle.SetItemText(count, 3, arr[3]);
		LIST_StaticObstacle.SetItemText(count, 4, arr[4]);
		LIST_StaticObstacle.SetItemText(count, 5, arr[5]);
		
		pset.MoveNext();
	}
	db.Close();
	
	MessageBox("Excel���ݳɹ�����ϵͳ!", "����ɹ�");
}


void SetStaticObstacleCircle::OnBnClickedSobstaclecoutput()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ж��б�����Ƿ��м�¼
	if (LIST_StaticObstacle.GetItemCount() <= 0)
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

			iColumnNum = LIST_StaticObstacle.GetHeaderCtrl()->GetItemCount();
			iRowCount = LIST_StaticObstacle.GetItemCount();

			sSql = " CREATE TABLE ��̬�ϰ��Բ������ ( ";
			strInsert = " INSERT INTO ��̬�ϰ��Բ������ ( ";
			//����б�������
			lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
			lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
			lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
			//���������������ú����ͨ�� GetColumn()��������б��������
			for (i = 0; i< iColumnNum; i++)
			{
				if (!(LIST_StaticObstacle.GetColumn(i, &lvCol)))
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
					LIST_StaticObstacle.GetItemText(j, i, chTemp, 33);
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

		AfxMessageBox("���澲̬�ϰ��Բ������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}


float SetStaticObstacleCircle::calculate_PolarAngle(float StaticObstacleX, float StaticObstacleY)//��ʾ�����µ�ת��
{
	float temp2 = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
	float temp3, temp4;
	temp3 = atan(abs(float(((float)StaticObstacleY - (float)startgoalp.sy)) / (abs((float)StaticObstacleX - (float)startgoalp.sx))));//GDI�Ƕ�

	float k1 = (float(startgoalp.gy - startgoalp.sy) / (startgoalp.gx - startgoalp.sx));//ʼĩ��б��

	if (k1 == 0)
	{
		if (StaticObstacleY > startgoalp.sy)//��ʼĩ��֮��
		{
			if (StaticObstacleX >= startgoalp.sx)//��������
			{
				temp4 = 2 * pi - temp3;
			}
			else//��������
			{
				temp4 = pi + temp3;
			}

		}
		else//��ʼĩ��֮��
		{
			if (StaticObstacleX >= startgoalp.sx)//��һ����
			{
				temp4 = temp3;
			}
			else//�ڶ�����
			{
				temp4 = pi - temp3;
			}
		}
	}
	else
	{
		float k2 = -1 / k1;//��ֱ��б��

		if (StaticObstacleY > (k1*(StaticObstacleX - startgoalp.sx) + startgoalp.sy))//��ʼĩ��֮��
		{
			if (StaticObstacleY >= (k2*(StaticObstacleX - startgoalp.sx) + startgoalp.sy))//��������
			{
				temp4 = 2 * pi - temp3 - temp2;
			}
			else//��������
			{
				temp4 = pi + temp3 + temp2;
			}

		}
		else//��ʼĩ��֮��
		{
			if (StaticObstacleY >= (k2*(StaticObstacleX - startgoalp.sx) + startgoalp.sy))//��һ����
			{
				temp4 = temp3 + temp2;
			}
			else//�ڶ�����
			{
				temp4 = pi - temp3 - temp2;
			}
		}
	}
	return temp4;
}
