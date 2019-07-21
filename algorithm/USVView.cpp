// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// USVView.cpp : USVView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "USV.h"
#endif

#include "USVDoc.h"
#include "USVView.h"
#include "MainFrm.h"
#include "Set_start_goal_Position.h"
#include "Setstaticobstaclecircle.h"
#include "SetStaticObstacleRectangle.h"
#include "SetDynamicOC.h"
#include "SetDynamicOR.h"
#include "SetUnknownOC.h"
#include "SetUnknownOR.h"
#include "SetPSO.h"
#include "SetDoPSO.h"
#include "SetViewSize.h"
#include "SetUnknown.h"
#include "resource.h"
#include "Pathpoint.h"
#include "Particle.h"
#include "ParticleDO.h"
#include "Afxdlgs.h"
#include <afxdb.h>
#include "windows.h"
#include "float.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

Set_start_goal_Position set_start_goal_Position;
SetStaticObstacleCircle Setstaticobstaclecircle;
SetStaticObstacleRectangle Setstaticobstaclerectangle;
SetDynamicOC SetdynamicOC;
SetDynamicOR SetdynamicOR;
SetUnknownOC SetunknownOC;
SetUnknownOR SetunknownOR;
SetUnknown Setunknown;
SetPSO setpso;
SetDoPSO setdopso;
SetViewSize setviewsize;

extern bool state_sgposition=0;//ʼĩ��״̬
extern bool state_staticOC = 0;//Բ�ξ�̬�ϰ���״̬
extern bool state_staticOR = 0;//���ξ�̬�ϰ���״̬
extern bool state_dynamicOC = 0;//Բ�ζ�̬�ϰ���״̬
extern bool state_dynamicOR = 0;//���ζ�̬�ϰ���״̬
extern bool state_unknownOC = 0;//Բ��δ֪�ϰ���״̬
extern bool state_unknownOR = 0;//����δ֪�ϰ���״̬

extern ViewSize viewsize{800,1200};//��ͼ��С

extern StartGoalPOINT startgoalp{}, previous{};

extern StaticOC staticoc[20]{};

extern DynamicOC dynamicoc[20]{};

extern UnknownOC unknownoc[20]{};

extern StaticOR staticor[20]{};

extern DynamicOR dynamicor[20]{};

extern UnknownOR unknownor[20]{};

extern ForbidA forbidThisDimA[20]{};//Բ�α�ά�����
//extern ForbidA forbidThisRcDimA[20]{};//���α�ά�����

extern PSO pso{};//��̬����Ⱥ����

extern PSO_DO pso_do{};//����Ⱥ����

extern Unknown unknown{};//�ֲ�δ֪����

extern UnknownO unknownO[30]{};//�ֲ�δ֪���� ����

extern int allp_un = 0;//δ֪�ϰ������

extern float unknownPA[30]{};//δ֪�ϰ������߽Ƕ�

bestFitnessLIST bestFitness_list[1000]{};//ÿ����Ӧ��ֵ
bestFitnessLIST bestFitness_listDO[20][1000]{};//ÿ����Ӧ��ֵ

bestEachGenerations best_eachGenerations[3000]{};//��������
extern int testNum=0;//���Դ���
extern int thisPSOnum = 0;//����pso���Դ���

extern SOBSTICLE SObsticle_num[30]{};//�ϰ������飬һάΪ��ά�ȼ������򣬶�άΪ��Բ�жϣ�1ΪԲ��2Ϊ�������ڸ��ϰ�������Ĵ���0��ʼ��

extern DOBSTICLE DObsticle_num[20]{};//��̬�ϰ��Բ�ͷ����Ƿ���USV��ײ����Ϣ����

int COMBOstartgoal, COMBOsoc, COMBOdo, COMBOdoun, COMBOPathPoint, COMBOview; //ʼĩ����ʾ��ʽ,��̬Բ��ʾ��ʽ,·���ڵ���ʾ��ʽ
bool doview=true;//��̬��ʾ��̬�ϰ���

extern Pathpoint gpathBest[50]{};  //��̬ȫ������·����
extern PathpointDO gpathBestDO[30]{};//��̬ȫ������·����
int bestIndex = 0;//��̬���Ŵ���
float gbestFitness = FLT_MAX;//float���ֵ; //��̬��õ���Ӧ��
float gbestFitness_OptimizePATH = 0.0; //��̬·���Ż���õ���Ӧ��
float gbestFitness_DynamicPSO = 0.0; //��̬·���Ż����·������
extern int allp = 0;//��̬�ϰ������

int bestIndexDO = 0;//��̬���Ŵ���
float gbestFitnessDO = FLT_MAX;//float���ֵ; //��̬��õ���Ӧ��
int allp_do = 0;//��̬�ϰ������
extern DoCalNum docalNUM[20]{};//��Ҫ���㶯̬�ϰ��Ĵ���

DWORD UsedTimeInMs;//����ʱ��
DWORD UsedTimeInMs_OptimizePATH;//����ʱ��
DWORD UsedTimeInMs_DynamicPSO;//����ʱ��

// USVView

IMPLEMENT_DYNCREATE(USVView, CView)

BEGIN_MESSAGE_MAP(USVView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &USVView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CalculatePSO, &USVView::OnCalculatePSO)
	ON_COMMAND(ID_Set_start_goal_Position, &USVView::OnSet_start_goal_Position)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SetStaticObstacleCircle, &USVView::OnSetstaticobstaclecircle)
	ON_COMMAND(ID_COMBOstartgoal, &USVView::OnCombostartgoal)
	ON_COMMAND(ID_COMBO_SOC, &USVView::OnComboSoc)
	ON_COMMAND(ID_DataOUTPUT, &USVView::OnDataoutput)
	ON_COMMAND(ID_COMBO_PathPoint, &USVView::OnComboPathpoint)
	ON_COMMAND(ID_BT_setPSO, &USVView::OnBtsetpso)
	ON_COMMAND(ID_OptimizePath, &USVView::OnOptimizepath)
	ON_COMMAND(ID_CalculateAndOptimize, &USVView::OnCalculateandoptimize)
	ON_COMMAND(ID_SetStaticObstacleRectangle, &USVView::OnSetstaticobstaclerectangle)
	ON_COMMAND(ID_SetViewSize, &USVView::OnSetviewsize)
	ON_COMMAND(ID_SetDynamicOC, &USVView::OnSetdynamicOC)
	ON_COMMAND(ID_SetDynamicOR, &USVView::OnSetdynamicOR)
	ON_COMMAND(ID_COMBO_ViewInformation, &USVView::OnComboViewinformation)
	ON_COMMAND(ID_COMBO_DO, &USVView::OnComboDo)
	ON_COMMAND(ID_COMBO_DOun, &USVView::OnComboDoun)
	ON_COMMAND(ID_CalculateDO_PSO, &USVView::OnCalculatedoPso)
	ON_COMMAND(ID_setPSOdo, &USVView::Onsetpsodo)
	ON_COMMAND(ID_VIEWdo, &USVView::OnViewdo)
	ON_COMMAND(ID_SetUnknownOC, &USVView::OnSetunknownoc)
	ON_COMMAND(ID_SetUnknownOR, &USVView::OnSetunknownor)
	ON_COMMAND(ID_SetUNKNOWN, &USVView::OnSetunknown)
	ON_COMMAND(ID_CalculateUnknown, &USVView::OnCalculateunknown)
END_MESSAGE_MAP()

// USVView ����/����

USVView::USVView()
{
	// TODO:  �ڴ˴���ӹ������

	//��̬pso������ʼ��
	pso.PSOgenerations = 100;
	pso.PSOparticle_num = 50;
	pso.PSOsetInitialV = 32;
	pso.PSOsetV_numMAX = 100;

	//��̬pso������ʼ��
	pso_do.PSOgenerations = 50;
	pso_do.PSOparticle_num = 50;
	pso_do.WeightV = 1;
	pso_do.WeightDa = 70;
	pso_do.changeWeight = FALSE;

	//δ֪��̬���ϴ�����Ұ�뾶���н�����
	unknown.UnknownR = 200;//��Ұ�뾶
	unknown.UnknownT = 2;//���ϼ��	

	//��·��ֵ����ֵ0
}

USVView::~USVView()
{
}

BOOL USVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);
}

// USVView ����

void USVView::OnDraw(CDC* /*pDC*/)
{
	USVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���

//-------------------------------------------------------------------------------------------------------------------------------------------	
	//��ʼĩԲ   ��ť�������ȫ�ֱ�����TRUE�ͻ���FALSE�Ͳ�������ʼ��False
	if (state_sgposition) 
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;

		//ʼĩ������
		newpen.CreatePen(PS_DASHDOT, 1, RGB(49, 33, 132));
		oldpen = dc.SelectObject(&newpen);
		dc.MoveTo(startgoalp.sx, startgoalp.sy);
		dc.LineTo(startgoalp.gx, startgoalp.gy);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();
		
		//��ʼĩ��
		dc.SetPixel(startgoalp.sx, startgoalp.sy, RGB(49, 33, 132));
		dc.SetPixel(startgoalp.gx, startgoalp.gy, RGB(241, 50, 42));
		//���Բ
		newpen.CreatePen(PS_SOLID, 3, RGB(241, 50, 42));
		oldpen = dc.SelectObject(&newpen);
		dc.Ellipse(startgoalp.sx - 5, startgoalp.sy - 5, startgoalp.sx + 5, startgoalp.sy + 5);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();
		//�յ�Բ
		newpen.CreatePen(PS_SOLID, 3, RGB(49, 33, 132));
		oldpen = dc.SelectObject(&newpen);
		dc.Ellipse(startgoalp.gx - 5, startgoalp.gy - 5, startgoalp.gx + 5, startgoalp.gy + 5);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//������ͼ��ʾ��Ϣ
	switch (COMBOview)
	{
	case 0:
	{
			  //д����Ⱥ��Ϣ����Ӧ��ֵ
			  CClientDC dc(this);
			  SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			  dc.SetTextColor(RGB(0, 0, 0));

			  CRect rc;
			  int x, y;
			  GetClientRect(&rc);//��û����ľ��δ�С
			  x = rc.right;
			  y = rc.bottom;

			  CString psoTEXT1 = "Generations:", psoTEXT2 = "Particle_num:", psoTEXT3 = "SetV_numMAX:",
				  psoTEXT4 = "SetInitialV:", psoTEXT5 = "BestFitness_CalculatePSO:", psoTEXT6 = "UsedTime(S):", 
				  psoTEXT7 = "ThisPSO_Num:", psoTEXT8 = "Test_Num:", psoTEXT9 = "StaticPSO_BestIndex:", psoTEXT10 = "BestFitness_OptimizePath:", ctemp, ctemp1,
				  psoTEXT11 = "WeightDa:", psoTEXT12 = "WeightV:", psoTEXT13 = "(D):", psoTEXT14 = "BestFitness_DynamicPSO:";

			  //������Ļ
			  dc.TextOutA(x - 70, 10, "Scale:1:4");
			  
			  //����Ļ
			  ctemp.Format("%d", pso.PSOgenerations);
			  psoTEXT1 = psoTEXT1 + ctemp;
			  dc.TextOutA(x - 130, y - 65, psoTEXT1);

			  ctemp.Format("%d", pso.PSOparticle_num);
			  psoTEXT2 = psoTEXT2 + ctemp;
			  dc.TextOutA(x - 130, y - 65 + 15 * 1, psoTEXT2);

			  ctemp.Format("%d", pso.PSOsetV_numMAX);
			  psoTEXT3 = psoTEXT3 + ctemp;
			  dc.TextOutA(x - 130, y - 65 + 15 * 2, psoTEXT3);

			  ctemp.Format("%d", pso.PSOsetInitialV);
			  psoTEXT4 = psoTEXT4 + ctemp;
			  dc.TextOutA(x - 130, y - 65 + 15 * 3, psoTEXT4);

			  dc.TextOutA(x - 110, y - 65 - 15 * 1,"StaticPSO" );

			  ctemp.Format("%d", pso_do.WeightDa);
			  psoTEXT11 = psoTEXT11 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 2, psoTEXT11);

			  ctemp.Format("%d", pso_do.WeightV);
			  psoTEXT12 = psoTEXT12 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 3, psoTEXT12);

			  psoTEXT1 = "Generations:", psoTEXT2 = "Particle_num:";

			  ctemp.Format("%d", pso_do.PSOparticle_num);
			  psoTEXT2 = psoTEXT2 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 4, psoTEXT2);

			  ctemp.Format("%d", pso_do.PSOgenerations);
			  psoTEXT1 = psoTEXT1 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 5, psoTEXT1);

			  dc.TextOutA(x - 110, y - 75 - 15 * 6, "DynamicPSO");



			  //����Ļ
			  ctemp.Format("%.3f", gbestFitness_DynamicPSO);
			  psoTEXT14 = psoTEXT14 + ctemp;
			  dc.TextOutA(10, y - 20 , psoTEXT14);

			  ctemp.Format("%.3f", gbestFitness_OptimizePATH);
			  psoTEXT10 = psoTEXT10 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 1, psoTEXT10);

			  ctemp.Format("%.3f", bestFitness_list[pso.PSOgenerations - 1].bestFitness);
			  psoTEXT5 = psoTEXT5 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 2, psoTEXT5);

			  ctemp.Format("%.3f", (float)UsedTimeInMs / 1000.0); 
			  ctemp1.Format("%.3f", (float)UsedTimeInMs_DynamicPSO / 1000.0);
			  psoTEXT6 = psoTEXT6 + ctemp + " s &" + psoTEXT13 + ctemp1 + " s ";
			  dc.TextOutA(10, y - 20 - 15 * 3, psoTEXT6);
			  
			  ctemp.Format("%d", bestIndex);
			  psoTEXT9 = psoTEXT9 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 4, psoTEXT9);
			  
			  ctemp.Format("%d", thisPSOnum);
			  psoTEXT7 = psoTEXT7 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 5, psoTEXT7);

			  ctemp.Format("%d", testNum);
			  psoTEXT8 = psoTEXT8 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 6, psoTEXT8);
	}
		break;
	case 1:
	{
			  //д����Ⱥ��Ϣ����Ӧ��ֵ
			  CClientDC dc(this);
			  SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			  dc.SetTextColor(RGB(0, 0, 0));

			  CRect rc;
			  int x, y;
			  GetClientRect(&rc);//��û����ľ��δ�С
			  x = rc.right;
			  y = rc.bottom;

			  CString psoTEXT1 = "Generations:", psoTEXT2 = "Particle_num:", psoTEXT3 = "SetV_numMAX:",
				  psoTEXT4 = "SetInitialV:", psoTEXT5 = "BestFitness_CalculatePSO:", psoTEXT6 = "UsedTime(S):",
				  psoTEXT7 = "ThisPSO_Num:", psoTEXT8 = "Test_Num:", psoTEXT9 = "StaticPSO_BestIndex:", psoTEXT10 = "BestFitness_OptimizePath:", ctemp, ctemp1,
				  psoTEXT11 = "WeightDa:", psoTEXT12 = "WeightV:", psoTEXT13 = "(D):", psoTEXT14 = "BestFitness_DynamicPSO:";

			  //������Ļ
			  dc.TextOutA(x - 70, 10, "Scale:1:4");

			  //����Ļ
			  ctemp.Format("%d", pso.PSOgenerations);
			  psoTEXT1 = psoTEXT1 + ctemp;
			  dc.TextOutA(x - 130, y - 65, psoTEXT1);

			  ctemp.Format("%d", pso.PSOparticle_num);
			  psoTEXT2 = psoTEXT2 + ctemp;
			  dc.TextOutA(x - 130, y - 65 + 15 * 1, psoTEXT2);

			  ctemp.Format("%d", pso.PSOsetV_numMAX);
			  psoTEXT3 = psoTEXT3 + ctemp;
			  dc.TextOutA(x - 130, y - 65 + 15 * 2, psoTEXT3);

			  ctemp.Format("%d", pso.PSOsetInitialV);
			  psoTEXT4 = psoTEXT4 + ctemp;
			  dc.TextOutA(x - 130, y - 65 + 15 * 3, psoTEXT4);

			  dc.TextOutA(x - 110, y - 65 - 15 * 1, "StaticPSO");

			  ctemp.Format("%d", pso_do.WeightDa);
			  psoTEXT11 = psoTEXT11 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 2, psoTEXT11);

			  ctemp.Format("%d", pso_do.WeightV);
			  psoTEXT12 = psoTEXT12 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 3, psoTEXT12);

			  psoTEXT1 = "Generations:", psoTEXT2 = "Particle_num:";

			  ctemp.Format("%d", pso_do.PSOparticle_num);
			  psoTEXT2 = psoTEXT2 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 4, psoTEXT2);

			  ctemp.Format("%d", pso_do.PSOgenerations);
			  psoTEXT1 = psoTEXT1 + ctemp;
			  dc.TextOutA(x - 130, y - 75 - 15 * 5, psoTEXT1);

			  dc.TextOutA(x - 110, y - 75 - 15 * 6, "DynamicPSO");



			  //����Ļ
			  ctemp.Format("%.3f", gbestFitness_DynamicPSO);
			  psoTEXT14 = psoTEXT14 + ctemp;
			  dc.TextOutA(10, y - 20, psoTEXT14);

			  ctemp.Format("%.3f", gbestFitness_OptimizePATH);
			  psoTEXT10 = psoTEXT10 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 1, psoTEXT10);

			  ctemp.Format("%.3f", bestFitness_list[pso.PSOgenerations - 1].bestFitness);
			  psoTEXT5 = psoTEXT5 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 2, psoTEXT5);

			  ctemp.Format("%.3f", (float)UsedTimeInMs / 1000.0);
			  ctemp1.Format("%.3f", (float)UsedTimeInMs_DynamicPSO / 1000.0);
			  psoTEXT6 = psoTEXT6 + ctemp + " s &" + psoTEXT13 + ctemp1 + " s ";
			  dc.TextOutA(10, y - 20 - 15 * 3, psoTEXT6);

			  ctemp.Format("%d", bestIndex);
			  psoTEXT9 = psoTEXT9 + ctemp;
			  dc.TextOutA(10, y - 20 - 15 * 4, psoTEXT9);

	}
		break;
	case 2:
	{
			  //д����Ⱥ��Ϣ����Ӧ��ֵ
			  CClientDC dc(this);
			  SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			  dc.SetTextColor(RGB(0, 0, 0));

			  CRect rc;
			  int x, y;
			  GetClientRect(&rc);//��û����ľ��δ�С
			  x = rc.right;
			  y = rc.bottom;

			  //������Ļ
			  dc.TextOutA(x - 70, 10, "Scale:1:4");
	}
		break;
	case 3:
		break;
	default:
		break;
	}	

//-------------------------------------------------------------------------------------------------------------------------------------------
	//��staticobstaclecircle
	if (state_staticOC)
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;

		for (int i = 0; staticoc[i].r != 0; i++)
		{
			//������Բ
			newpen.CreatePen(PS_DOT, 1, RGB(254, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);
			dc.Ellipse(startgoalp.sx - staticoc[i].pm, startgoalp.sy - staticoc[i].pm, startgoalp.sx + staticoc[i].pm, startgoalp.sy + staticoc[i].pm);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
			//���ϰ���
			newpen.CreatePen(PS_SOLID, 3, RGB(254, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.Ellipse(staticoc[i].x - staticoc[i].r / 2, staticoc[i].y - staticoc[i].r / 2, staticoc[i].x + staticoc[i].r / 2, staticoc[i].y + staticoc[i].r / 2);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
			//���ϰ����չԲ��
			newpen.CreatePen(PS_DASH, 1, RGB(10, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.Ellipse(staticoc[i].x - staticoc[i].r / 2 - safe_expandT, staticoc[i].y - staticoc[i].r / 2 - safe_expandT, staticoc[i].x + staticoc[i].r / 2 + safe_expandT, staticoc[i].y + staticoc[i].r / 2 + safe_expandT);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

			//���ϰ���Բ��
			dc.SetPixel(staticoc[i].x, staticoc[i].y, RGB(238, 206, 25));
		}
	}
	
//-------------------------------------------------------------------------------------------------------------------------------------------
	//��staticobstaclerectangle
	if (state_staticOR)
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;

		for (int i = 0; staticor[i].HalfL != 0; i++)
		{
			//������Բ
			newpen.CreatePen(PS_DOT, 1, RGB(254, 82, 0));
			
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);
			//ά��ԲΪԭʼ��
			//dc.Ellipse(startgoalp.sx - staticor[i].Peak[1].Pm, startgoalp.sy - staticor[i].Peak[1].Pm, startgoalp.sx + staticor[i].Peak[1].Pm, startgoalp.sy + staticor[i].Peak[1].Pm);
			//dc.Ellipse(startgoalp.sx - staticor[i].Peak[3].Pm, startgoalp.sy - staticor[i].Peak[3].Pm, startgoalp.sx + staticor[i].Peak[3].Pm, startgoalp.sy + staticor[i].Peak[3].Pm);
			//ά��ԲΪ��չ��
			dc.Ellipse(startgoalp.sx - staticor[i].Peak[1].PmEX, startgoalp.sy - staticor[i].Peak[1].PmEX, startgoalp.sx + staticor[i].Peak[1].PmEX, startgoalp.sy + staticor[i].Peak[1].PmEX);
			dc.Ellipse(startgoalp.sx - staticor[i].Peak[3].PmEX, startgoalp.sy - staticor[i].Peak[3].PmEX, startgoalp.sx + staticor[i].Peak[3].PmEX, startgoalp.sy + staticor[i].Peak[3].PmEX);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
			//���ϰ���
			newpen.CreatePen(PS_SOLID, 3, RGB(254, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.MoveTo(staticor[i].Peak[0].x, staticor[i].Peak[0].y);
			dc.LineTo(staticor[i].Peak[1].x, staticor[i].Peak[1].y);
			dc.LineTo(staticor[i].Peak[2].x, staticor[i].Peak[2].y);
			dc.LineTo(staticor[i].Peak[3].x, staticor[i].Peak[3].y);
			dc.LineTo(staticor[i].Peak[0].x, staticor[i].Peak[0].y);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

			//���ϰ���,��չ����
			newpen.CreatePen(PS_DASH, 1, RGB(10, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.MoveTo(staticor[i].Peak[0].xEX, staticor[i].Peak[0].yEX);
			dc.LineTo(staticor[i].Peak[1].xEX, staticor[i].Peak[1].yEX);
			dc.LineTo(staticor[i].Peak[2].xEX, staticor[i].Peak[2].yEX);
			dc.LineTo(staticor[i].Peak[3].xEX, staticor[i].Peak[3].yEX);
			dc.LineTo(staticor[i].Peak[0].xEX, staticor[i].Peak[0].yEX);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

			//���ϰ���Բ��
			dc.SetPixel(staticor[i].CenterX, staticor[i].CenterY, RGB(238, 206, 25));
		}
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//��dynamicobstaclecircle
	if (state_dynamicOC)
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;

		for (int i = 0; dynamicoc[i].r != 0; i++)
		{
			//���ϰ���
			newpen.CreatePen(PS_SOLID, 3, RGB(239, 75, 148));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.Ellipse(dynamicoc[i].x - dynamicoc[i].r / 2, dynamicoc[i].y - dynamicoc[i].r / 2, dynamicoc[i].x + dynamicoc[i].r / 2, dynamicoc[i].y + dynamicoc[i].r / 2);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
			//�������ͷ
			COLORREF rgb = RGB(239, 75, 148);
			point_d p1,p2;
			p1.x = dynamicoc[i].x;
			p1.y = dynamicoc[i].y;
			p2.x = dynamicoc[i].x + dynamicoc[i].r*cos(dynamicoc[i].Da*pi/180);
			p2.y = dynamicoc[i].y - dynamicoc[i].r*sin(dynamicoc[i].Da*pi / 180);
			DrawArrow(p1, p2, 40, 15, rgb);
			//���ϰ����չԲ��
			newpen.CreatePen(PS_DASH, 1, RGB(10, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.Ellipse(dynamicoc[i].x - dynamicoc[i].r / 2 - safe_expandT, dynamicoc[i].y - dynamicoc[i].r / 2 - safe_expandT, dynamicoc[i].x + dynamicoc[i].r / 2 + safe_expandT, dynamicoc[i].y + dynamicoc[i].r / 2 + safe_expandT);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
			//���ϰ���Բ��
			dc.SetPixel(dynamicoc[i].x, dynamicoc[i].y, RGB(239, 75, 148));

		}
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//��dynamicobstaclerectangle
	if (state_dynamicOR)
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;
		COLORREF rgb;

		for (int i = 0; dynamicor[i].HalfL != 0; i++)
		{
			//���ϰ���
			newpen.CreatePen(PS_SOLID, 3, RGB(239, 75, 148));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.MoveTo(dynamicor[i].Peak[0].x, dynamicor[i].Peak[0].y);
			dc.LineTo(dynamicor[i].Peak[1].x, dynamicor[i].Peak[1].y);
			dc.LineTo(dynamicor[i].Peak[2].x, dynamicor[i].Peak[2].y);
			dc.LineTo(dynamicor[i].Peak[3].x, dynamicor[i].Peak[3].y);
			dc.LineTo(dynamicor[i].Peak[0].x, dynamicor[i].Peak[0].y);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

			//���ϰ���,��չ����
			newpen.CreatePen(PS_DASH, 1, RGB(10, 82, 0));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.MoveTo(dynamicor[i].Peak[0].xEX, dynamicor[i].Peak[0].yEX);
			dc.LineTo(dynamicor[i].Peak[1].xEX, dynamicor[i].Peak[1].yEX);
			dc.LineTo(dynamicor[i].Peak[2].xEX, dynamicor[i].Peak[2].yEX);
			dc.LineTo(dynamicor[i].Peak[3].xEX, dynamicor[i].Peak[3].yEX);
			dc.LineTo(dynamicor[i].Peak[0].xEX, dynamicor[i].Peak[0].yEX);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

			//�������ͷ
			rgb = RGB(239, 75, 148);
			point_d p1, p2;
			p1.x = dynamicor[i].CenterX;
			p1.y = dynamicor[i].CenterY;
			p2.x = dynamicor[i].CenterX + dynamicor[i].HalfL * 2 * cos(dynamicor[i].Da*pi / 180);
			p2.y = dynamicor[i].CenterY - dynamicor[i].HalfL * 2 * sin(dynamicor[i].Da*pi / 180);
			DrawArrow(p1, p2, 40, 15,rgb);

			//���ϰ���Բ��
			dc.SetPixel(dynamicor[i].CenterX, dynamicor[i].CenterY, RGB(238, 206, 25));
		}
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//��unknownoc
	if (state_unknownOC)
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;
		CBrush brush;

		for (int i = 0; unknownoc[i].r != 0; i++)
		{
			//���ϰ���
			brush.CreateSolidBrush(RGB(0, 173, 207));
			CBrush*   pTempBrush = NULL;
			pTempBrush = (CBrush*)dc.SelectObject(brush);
			dc.Ellipse(unknownoc[i].x - unknownoc[i].r / 2, unknownoc[i].y - unknownoc[i].r / 2, unknownoc[i].x + unknownoc[i].r / 2, unknownoc[i].y + unknownoc[i].r / 2);
			dc.SelectObject(brush);
			brush.DeleteObject();

			//�������ͷ
			COLORREF rgb = RGB(0, 173, 207);
			point_d p1, p2;
			p1.x = unknownoc[i].x;
			p1.y = unknownoc[i].y;
			p2.x = unknownoc[i].x + unknownoc[i].r*cos(unknownoc[i].Da*pi / 180);
			p2.y = unknownoc[i].y - unknownoc[i].r*sin(unknownoc[i].Da*pi / 180);
			DrawArrow(p1, p2, 40, 15, rgb);
			//���ϰ����չԲ��
			newpen.CreatePen(PS_DASH, 1, RGB(0, 173, 207));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.Ellipse(unknownoc[i].xEX - unknownoc[i].rEX / 2, unknownoc[i].yEX - unknownoc[i].rEX / 2, unknownoc[i].xEX + unknownoc[i].rEX / 2, unknownoc[i].yEX + unknownoc[i].rEX / 2 );
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

		}
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//��unknownor
	if (state_unknownOR)
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;
		COLORREF rgb;
		CBrush brush;

		for (int i = 0; unknownor[i].HalfL != 0; i++)
		{
			//���ϰ���
			POINT pt[4];
			pt[0] = CPoint(unknownor[i].Peak[0].x, unknownor[i].Peak[0].y);
			pt[1] = CPoint(unknownor[i].Peak[1].x, unknownor[i].Peak[1].y);
			pt[2] = CPoint(unknownor[i].Peak[2].x, unknownor[i].Peak[2].y);
			pt[3] = CPoint(unknownor[i].Peak[3].x, unknownor[i].Peak[3].y);
			brush.CreateSolidBrush(RGB(0, 173, 207));
			CBrush*   pTempBrush = NULL;
			pTempBrush = (CBrush*)dc.SelectObject(brush);
			dc.SelectObject(&brush);
			dc.Polygon(pt, 4);
			brush.DeleteObject();
			
			//���ϰ���,��չ����
			newpen.CreatePen(PS_DASH, 1, RGB(0, 173, 207));
			oldpen = dc.SelectObject(&newpen);
			dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
			dc.MoveTo(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);
			dc.LineTo(unknownor[i].Peak[1].xEX, unknownor[i].Peak[1].yEX);
			dc.LineTo(unknownor[i].Peak[2].xEX, unknownor[i].Peak[2].yEX);
			dc.LineTo(unknownor[i].Peak[3].xEX, unknownor[i].Peak[3].yEX);
			dc.LineTo(unknownor[i].Peak[0].xEX, unknownor[i].Peak[0].yEX);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();

			//�������ͷ
			rgb = RGB(0, 173, 207);
			point_d p1, p2;
			p1.x = unknownor[i].CenterX;
			p1.y = unknownor[i].CenterY;
			p2.x = unknownor[i].CenterX + unknownor[i].HalfL * 2 * cos(unknownor[i].Da*pi / 180);
			p2.y = unknownor[i].CenterY - unknownor[i].HalfL * 2 * sin(unknownor[i].Da*pi / 180);
			DrawArrow(p1, p2, 40, 15, rgb);

		}
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//����������ʱ��δ֪��̬�ϰ����λ��
	if ((unknownoc[0].r != 0) || (unknownor[0].HalfL != 0))
	{
		for (int i = 0; i < allp_un; i++)
		{
			if (unknownO[i].form == 1)//Բ
			{
				CClientDC dc(this);
				CPen newpen;
				CPen *oldpen;
				CBrush brush;

				newpen.CreatePen(PS_SOLID, 1, RGB(108,115,107));
				oldpen = dc.SelectObject(&newpen);
				dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
				dc.Ellipse(unknownO[i].xEX - unknownO[i].rEX / 2, unknownO[i].yEX - unknownO[i].rEX / 2, unknownO[i].xEX + unknownO[i].rEX / 2, unknownO[i].yEX + unknownO[i].rEX / 2);
				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}
			else if (unknownO[i].form == 2)//��
			{
				CClientDC dc(this);
				CPen newpen;
				CPen *oldpen;
				CBrush brush;

				newpen.CreatePen(PS_SOLID, 1, RGB(108,115,107));
				oldpen = dc.SelectObject(&newpen);
				dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
				dc.MoveTo(unknownO[i].Peak[0].xEX, unknownO[i].Peak[0].yEX);
				dc.LineTo(unknownO[i].Peak[1].xEX, unknownO[i].Peak[1].yEX);
				dc.LineTo(unknownO[i].Peak[2].xEX, unknownO[i].Peak[2].yEX);
				dc.LineTo(unknownO[i].Peak[3].xEX, unknownO[i].Peak[3].yEX);
				dc.LineTo(unknownO[i].Peak[0].xEX, unknownO[i].Peak[0].yEX);
				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}

		}
	}	

//-------------------------------------------------------------------------------------------------------------------------------------------
	//����̬�ཻ�ϰ����ཻʱ�̵�λ��
	if (doview && ( (DObsticle_num[0].form == 1) || (DObsticle_num[0].form == 2)) )
	{
		//��������  
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;

		float t,x,y;
		int m,n;
		REC Peak[4];
		for (int i = 0; i < allp_do; i++)
		{				
			COLORREF rgb;
			int linestyle;
			if (DObsticle_num[i].form == 1)
			{
				n = DObsticle_num[i].pointNum;

				//����������յ����
				for (int z = 0; z < 3; z++)
				{
					if (z==2)//���㶯̬�ϰ�����·���ཻʱ����·���յ㣬���õ�ʱ��
					{
						n = DObsticle_num[i].pointNum;
						float pm0, pa0, pm1, pa1,L;
						
						if (n==-1)
						{
							pm1 = gpathBest[0].AdditionS.pm;
							L = pm1;
							t = t + L / drawscale /(gpathBest[0].AdditionS.v* Kn_ms);
						}
						else
						{
							pm0 = gpathBest[n].GeneralP.pm;
							pa0 = gpathBest[n].GeneralP.pa;
							pm1 = gpathBest[n].AdditionP.pm;
							pa1 = gpathBest[n].AdditionP.pa;

							L = sqrt(pm0*pm0 + pm1*pm1 - 2 * pm0*pm1*cos(abs(pa1 - pa0)));
							t = t + L / drawscale / (gpathBest[n].AdditionP.v* Kn_ms);  
						}
						rgb = RGB(115,33,99);
						linestyle = PS_SOLID;
					}
					else
					{
						t = calculateDOtime(n);//�յ�����
						rgb = RGB(239, 75, 148);
						linestyle = PS_DOT;
					}
					
					//ֻ�����ཻʱ��
					if (z == 2)
					{
						m = DObsticle_num[i].num;
						x = dynamicoc[m].x + cos(dynamicoc[m].Da*pi / 180)*(t*dynamicoc[m].V* Kn_ms*drawscale);
						y = dynamicoc[m].y - sin(dynamicoc[m].Da*pi / 180)*(t*dynamicoc[m].V* Kn_ms*drawscale);

						//���ϰ���
						newpen.CreatePen(linestyle, 1, rgb);
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.Ellipse(x - dynamicoc[m].r / 2, y - dynamicoc[m].r / 2, x + dynamicoc[m].r / 2, y + dynamicoc[m].r / 2);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
						//�������ͷ
						point_d p1, p2;
						p1.x = x;
						p1.y = y;
						p2.x = x + dynamicoc[m].r*cos(dynamicoc[m].Da*pi / 180);
						p2.y = y - dynamicoc[m].r*sin(dynamicoc[m].Da*pi / 180);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
						DrawArrow(p1, p2, 40, 15, rgb);
						//���ϰ����չԲ��
						newpen.CreatePen(PS_DASHDOT, 1, RGB(10, 82, 0));
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.Ellipse(x - dynamicoc[m].r / 2 - safe_expandT, y - dynamicoc[m].r / 2 - safe_expandT, x + dynamicoc[m].r / 2 + safe_expandT, y + dynamicoc[m].r / 2 + safe_expandT);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
						//���ϰ���Բ��
						dc.SetPixel(x, y, RGB(239, 75, 148));

						//��·��
						newpen.CreatePen(PS_DASHDOTDOT, 1, RGB(239, 75, 148));
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.MoveTo(dynamicoc[m].x + dynamicoc[m].r*cos(dynamicoc[m].Da*pi / 180), dynamicoc[m].y - dynamicoc[m].r*sin(dynamicoc[m].Da*pi / 180));
						dc.LineTo(x, y);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
					}

					/*//ͬʱ��������ʱ��
					m = DObsticle_num[i].num;
					x = dynamicoc[m].x + cos(dynamicoc[m].Da*pi / 180)*(t*dynamicoc[m].V* Kn_ms*drawscale);
					y = dynamicoc[m].y - sin(dynamicoc[m].Da*pi / 180)*(t*dynamicoc[m].V* Kn_ms*drawscale);

					//���ϰ���
					newpen.CreatePen(linestyle, 1, rgb);
					oldpen = dc.SelectObject(&newpen);
					dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
					dc.Ellipse(x - dynamicoc[m].r / 2, y - dynamicoc[m].r / 2, x + dynamicoc[m].r / 2, y + dynamicoc[m].r / 2);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();
					//�������ͷ
					point_d p1, p2;
					p1.x = x;
					p1.y = y;
					p2.x = x + dynamicoc[m].r*cos(dynamicoc[m].Da*pi / 180);
					p2.y = y - dynamicoc[m].r*sin(dynamicoc[m].Da*pi / 180);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();
					DrawArrow(p1, p2, 40, 15, rgb);
					//���ϰ����չԲ��
					newpen.CreatePen(PS_DASHDOT, 1, RGB(10, 82, 0));
					oldpen = dc.SelectObject(&newpen);
					dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
					dc.Ellipse(x - dynamicoc[m].r / 2 - safe_expandT, y - dynamicoc[m].r / 2 - safe_expandT, x + dynamicoc[m].r / 2 + safe_expandT, y + dynamicoc[m].r / 2 + safe_expandT);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();
					//���ϰ���Բ��
					dc.SetPixel(x, y, RGB(239, 75, 148));
					if (z != 2)
					{	//��·��
						newpen.CreatePen(PS_DASHDOTDOT, 1, RGB(239, 75, 148));
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.MoveTo(dynamicoc[m].x + dynamicoc[m].r*cos(dynamicoc[m].Da*pi / 180), dynamicoc[m].y - dynamicoc[m].r*sin(dynamicoc[m].Da*pi / 180));
						dc.LineTo(x, y);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
					}*/

					n--;
				}				
			}
			else if (DObsticle_num[i].form == 2)
			{
				n = DObsticle_num[i].pointNum;

				//ֻ�����ཻʱ��
				
				//����������յ����
				for (int z = 0; z < 3; z++)
				{
					if (z == 2)//���㶯̬�ϰ�����·���ཻʱ����·���յ㣬���õ�ʱ��
					{
						n = DObsticle_num[i].pointNum;
						float pm0, pa0, pm1, pa1, L;
						if (n == -1)
						{
							pm1 = gpathBest[0].AdditionS.pm;
							L = pm1;
							t = t + L / drawscale / (gpathBest[0].AdditionS.v* Kn_ms);
						}
						else
						{
							pm0 = gpathBest[n].GeneralP.pm;
							pa0 = gpathBest[n].GeneralP.pa;
							pm1 = gpathBest[n].AdditionP.pm;
							pa1 = gpathBest[n].AdditionP.pa;

							L = sqrt(pm0*pm0 + pm1*pm1 - 2 * pm0*pm1*cos(abs(pa1 - pa0)));
							t = t + L / drawscale / (gpathBest[n].AdditionP.v* Kn_ms);
						}
						rgb = RGB(115,33,99);
						linestyle = PS_SOLID;
					}
					else
					{
						t = calculateDOtime(n);//�յ�����
						rgb = RGB(239, 75, 148);
						linestyle = PS_DOT;
					}

					//ֻ�����ཻʱ��
					if (z == 2)
					{
						m = DObsticle_num[i].num;

						Peak[0].x = dynamicor[m].Peak[0].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[0].y = dynamicor[m].Peak[0].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[1].x = dynamicor[m].Peak[1].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[1].y = dynamicor[m].Peak[1].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[2].x = dynamicor[m].Peak[2].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[2].y = dynamicor[m].Peak[2].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[3].x = dynamicor[m].Peak[3].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[3].y = dynamicor[m].Peak[3].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);

						Peak[0].xEX = dynamicor[m].Peak[0].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[0].yEX = dynamicor[m].Peak[0].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[1].xEX = dynamicor[m].Peak[1].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[1].yEX = dynamicor[m].Peak[1].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[2].xEX = dynamicor[m].Peak[2].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[2].yEX = dynamicor[m].Peak[2].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[3].xEX = dynamicor[m].Peak[3].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						Peak[3].yEX = dynamicor[m].Peak[3].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);

						//���ϰ���
						newpen.CreatePen(linestyle, 1, rgb);
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.MoveTo(Peak[0].x, Peak[0].y);
						dc.LineTo(Peak[1].x, Peak[1].y);
						dc.LineTo(Peak[2].x, Peak[2].y);
						dc.LineTo(Peak[3].x, Peak[3].y);
						dc.LineTo(Peak[0].x, Peak[0].y);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();

						//���ϰ���,��չ����
						newpen.CreatePen(PS_DASHDOT, 1, RGB(10, 82, 0));
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.MoveTo(Peak[0].xEX, Peak[0].yEX);
						dc.LineTo(Peak[1].xEX, Peak[1].yEX);
						dc.LineTo(Peak[2].xEX, Peak[2].yEX);
						dc.LineTo(Peak[3].xEX, Peak[3].yEX);
						dc.LineTo(Peak[0].xEX, Peak[0].yEX);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();

						//�������ͷ
						point_d p1, p2;
						p1.x = dynamicor[m].CenterX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						p1.y = dynamicor[m].CenterY - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
						p2.x = p1.x + dynamicor[m].HalfL * 2 * cos(dynamicor[m].Da*pi / 180);
						p2.y = p1.y - dynamicor[m].HalfL * 2 * sin(dynamicor[m].Da*pi / 180);
						DrawArrow(p1, p2, 40, 15, rgb);

						//���ϰ���Բ��
						dc.SetPixel(dynamicor[i].CenterX, dynamicor[i].CenterY, RGB(238, 206, 25));
						
						//��·��
						newpen.CreatePen(PS_DASHDOTDOT, 1, RGB(239, 75, 148));
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.MoveTo(dynamicor[m].CenterX + dynamicor[m].HalfL * 2 * cos(dynamicor[m].Da*pi / 180), dynamicor[m].CenterY - dynamicor[m].HalfL * 2 * sin(dynamicor[m].Da*pi / 180));
						dc.LineTo(p1.x, p1.y);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
					}

					/*//ͬʱ��������ʱ��
					m = DObsticle_num[i].num;

					Peak[0].x = dynamicor[m].Peak[0].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[0].y = dynamicor[m].Peak[0].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[1].x = dynamicor[m].Peak[1].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[1].y = dynamicor[m].Peak[1].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[2].x = dynamicor[m].Peak[2].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[2].y = dynamicor[m].Peak[2].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[3].x = dynamicor[m].Peak[3].x + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[3].y = dynamicor[m].Peak[3].y - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);

					Peak[0].xEX = dynamicor[m].Peak[0].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[0].yEX = dynamicor[m].Peak[0].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[1].xEX = dynamicor[m].Peak[1].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[1].yEX = dynamicor[m].Peak[1].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[2].xEX = dynamicor[m].Peak[2].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[2].yEX = dynamicor[m].Peak[2].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[3].xEX = dynamicor[m].Peak[3].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					Peak[3].yEX = dynamicor[m].Peak[3].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);

					//���ϰ���
					newpen.CreatePen(linestyle, 1, rgb);
					oldpen = dc.SelectObject(&newpen);
					dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
					dc.MoveTo(Peak[0].x, Peak[0].y);
					dc.LineTo(Peak[1].x, Peak[1].y);
					dc.LineTo(Peak[2].x, Peak[2].y);
					dc.LineTo(Peak[3].x, Peak[3].y);
					dc.LineTo(Peak[0].x, Peak[0].y);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();

					//���ϰ���,��չ����
					newpen.CreatePen(PS_DASHDOT, 1, RGB(10, 82, 0));
					oldpen = dc.SelectObject(&newpen);
					dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
					dc.MoveTo(Peak[0].xEX, Peak[0].yEX);
					dc.LineTo(Peak[1].xEX, Peak[1].yEX);
					dc.LineTo(Peak[2].xEX, Peak[2].yEX);
					dc.LineTo(Peak[3].xEX, Peak[3].yEX);
					dc.LineTo(Peak[0].xEX, Peak[0].yEX);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();

					//�������ͷ
					point_d p1, p2;
					p1.x = dynamicor[m].CenterX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					p1.y = dynamicor[m].CenterY - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
					p2.x = p1.x + dynamicor[m].HalfL * 2 * cos(dynamicor[m].Da*pi / 180);
					p2.y = p1.y - dynamicor[m].HalfL * 2 * sin(dynamicor[m].Da*pi / 180);
					DrawArrow(p1, p2, 40, 15, rgb);

					//���ϰ���Բ��
					dc.SetPixel(dynamicor[i].CenterX, dynamicor[i].CenterY, RGB(238, 206, 25));
					if (z != 2)
					{
						//��·��
						newpen.CreatePen(PS_DASHDOTDOT, 1, RGB(239, 75, 148));
						oldpen = dc.SelectObject(&newpen);
						dc.SelectStockObject(HOLLOW_BRUSH);//���ñ���͸��
						dc.MoveTo(dynamicor[m].CenterX + dynamicor[m].HalfL * 2 * cos(dynamicor[m].Da*pi / 180), dynamicor[m].CenterY - dynamicor[m].HalfL * 2 * sin(dynamicor[m].Da*pi / 180));
						dc.LineTo(p1.x, p1.y);
						dc.SelectObject(oldpen);
						newpen.DeleteObject();
					}*/
					
					n--;
				}			
			}
		}		
	}
//-------------------------------------------------------------------------------------------------------------------------------------------
	//��·��
	if (gpathBest[0].GeneralP.pm != 0)
	{
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;
		dc.MoveTo(startgoalp.sx, startgoalp.sy);

		float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�

		float x, y;
		
		//���;�̬��һ·�����м�
		if (gpathBest[0].AdditionS.pm != 0)//����֪��̬·��,���ٻ�����һ·����
		{
			//��֪��̬·���㴦��ֱ������ϵֵ
			x = startgoalp.sx + gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
			y = startgoalp.sy - gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);

			newpen.CreatePen(PS_SOLID, 5, RGB(114, 123, 180));
			oldpen = dc.SelectObject(&newpen);
			dc.LineTo(x, y);

			dc.SelectObject(oldpen);
			newpen.DeleteObject();
		}
		//����ʼ��͵�һ·����
		x = startgoalp.sx + gpathBest[0].GeneralP.pm*cos(gpathBest[0].GeneralP.pa - pa_SG);
		y = startgoalp.sy - gpathBest[0].GeneralP.pm*sin(gpathBest[0].GeneralP.pa - pa_SG);

		newpen.CreatePen(PS_SOLID, 3, RGB(50, 132, 66));
		oldpen = dc.SelectObject(&newpen);
		dc.LineTo(x, y);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();	

		//�ӵ�һ·����ĸ��Ӷ�̬�㿪ʼ������̬��̬·��
		for (int i = 1; i < allp; i++)
		{
			if (gpathBest[i-1].AdditionP.pm != 0)
			{
				x = startgoalp.sx + gpathBest[i - 1].AdditionP.pm*cos(gpathBest[i - 1].AdditionP.pa - pa_SG);
				y = startgoalp.sy - gpathBest[i - 1].AdditionP.pm*sin(gpathBest[i - 1].AdditionP.pa - pa_SG);

				newpen.CreatePen(PS_SOLID, 5, RGB(114, 123, 180));
				oldpen = dc.SelectObject(&newpen);
				dc.LineTo(x, y);

				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}

			//��̬·���㴦��ֱ������ϵֵ
			x = startgoalp.sx + gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
			y = startgoalp.sy - gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);

			newpen.CreatePen(PS_SOLID, 3, RGB(50, 132, 66));
			oldpen = dc.SelectObject(&newpen);
			dc.LineTo(x, y);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();		
			
		}

		//�����·������յ�֮��ľ���̬·��
		if (gpathBest[allp - 1].AdditionP.pm != 0)
		{
			x = startgoalp.sx + gpathBest[allp - 1].AdditionP.pm*cos(gpathBest[allp - 1].AdditionP.pa - pa_SG);
			y = startgoalp.sy - gpathBest[allp - 1].AdditionP.pm*sin(gpathBest[allp - 1].AdditionP.pa - pa_SG);

			newpen.CreatePen(PS_SOLID, 5, RGB(114, 123, 180));
			oldpen = dc.SelectObject(&newpen);
			dc.LineTo(x, y);

			dc.SelectObject(oldpen);
			newpen.DeleteObject();
		}

		newpen.CreatePen(PS_SOLID, 3, RGB(50, 132, 66));
		oldpen = dc.SelectObject(&newpen);
		dc.LineTo(startgoalp.gx, startgoalp.gy);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();
	
	}
	else if (gpathBest[0].AdditionS.pm != 0)//ֻ��һ�����ӵ�//���;�̬��һ·�����м�
	{
		CClientDC dc(this);
		CPen newpen;
		CPen *oldpen;
		dc.MoveTo(startgoalp.sx, startgoalp.sy);

		float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�

		float x, y;
		//��֪��̬·���㴦��ֱ������ϵֵ
		x = startgoalp.sx + gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
		y = startgoalp.sy - gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);

		newpen.CreatePen(PS_SOLID, 5, RGB(114, 123, 180));
		oldpen = dc.SelectObject(&newpen);
		dc.LineTo(x, y);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();

		newpen.CreatePen(PS_SOLID, 3, RGB(50, 132, 66));
		oldpen = dc.SelectObject(&newpen);
		dc.LineTo(startgoalp.gx, startgoalp.gy);
		dc.SelectObject(oldpen);
		newpen.DeleteObject();		
	}

//-------------------------------------------------------------------------------------------------------------------------------------------
	//����̬δ֪�ϰ������·��
	if ((unknownoc[0].r!=0)||(unknownor[0].HalfL!=0))
	{
		if (gpathBest[0].AdditionSU[0].pm != 0)//�������һ·�����ǰ��·�������޶�̬��֪���·����
		{
			CClientDC dc(this);
			CPen newpen;
			CPen *oldpen;
			float x, y, V, L, T;
			x = startgoalp.sx + gpathBest[0].AdditionSU[0].pm*cos(gpathBest[0].AdditionSU[0].pa);
			y = startgoalp.sy - gpathBest[0].AdditionSU[0].pm*sin(gpathBest[0].AdditionSU[0].pa);

			//������
			drawWD(x, y, gpathBest[0].AdditionSU[0].pa);

			dc.MoveTo(x, y);
			for (int i = 1; gpathBest[0].AdditionSU[i].pm != 0; i++)
			{
				T = unknown.UnknownT;

				//�ж�V��ֵ
				if (gpathBest[0].AdditionS.pm != 0)
				{
					V = gpathBest[0].AdditionS.v;
				}
				else
				{
					V = gpathBest[0].GeneralP.v;
				}
				
				L = V * T *drawscale * Kn_ms;//����

				x = x + L * cos(gpathBest[0].AdditionSU[i].pa);
				y = y - L * sin(gpathBest[0].AdditionSU[i].pa);

				newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
				oldpen = dc.SelectObject(&newpen);
				dc.LineTo(x, y);
				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}
			//�ж�ĩ�˵����ߵ�
			if (gpathBest[0].AdditionS.pm != 0)
			{
				x = startgoalp.sx + gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa);
				y = startgoalp.sy - gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa);
			}
			else if (gpathBest[0].GeneralP.pm == 0)//û��·����
			{
				x = startgoalp.gx;
				y = startgoalp.gy;
			}
			else
			{
				x = startgoalp.sx + gpathBest[0].GeneralP.pm*cos(gpathBest[0].GeneralP.pa);
				y = startgoalp.sy - gpathBest[0].GeneralP.pm*sin(gpathBest[0].GeneralP.pa);
			}

			newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
			oldpen = dc.SelectObject(&newpen);
			dc.LineTo(x, y);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
		}
		if (gpathBest[0].AdditionSUa[0].pm != 0)//�������һ·����ĺ��·��
		{
			CClientDC dc(this);
			CPen newpen;
			CPen *oldpen;
			float x, y, x1, y1, V, L, T, pa;
			ParticleDO tempPDO;
			x = startgoalp.sx + gpathBest[0].AdditionSUa[0].pm*cos(gpathBest[0].AdditionSUa[0].pa);
			y = startgoalp.sy - gpathBest[0].AdditionSUa[0].pm*sin(gpathBest[0].AdditionSUa[0].pa);

			x1 = startgoalp.sx + gpathBest[0].GeneralP.pm * cos(gpathBest[0].GeneralP.pa);
			y1 = startgoalp.sy - gpathBest[0].GeneralP.pm * sin(gpathBest[0].GeneralP.pa);
			pa = tempPDO.calculate_2point_pa(x, y, x1, y1);

			//������
			drawWD(x, y, pa);

			dc.MoveTo(x, y);
			for (int i = 1; gpathBest[0].AdditionSUa[i].pm != 0; i++)
			{
				T = unknown.UnknownT;
				V = gpathBest[0].GeneralP.v;
				L = V * T *drawscale * Kn_ms;//����

				x = x + L * cos(gpathBest[0].AdditionSUa[i].pa);
				y = y - L * sin(gpathBest[0].AdditionSUa[i].pa);

				newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
				oldpen = dc.SelectObject(&newpen);
				dc.LineTo(x, y);
				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}

			x = startgoalp.sx + gpathBest[0].GeneralP.pm*cos(gpathBest[0].GeneralP.pa);
			y = startgoalp.sy - gpathBest[0].GeneralP.pm*sin(gpathBest[0].GeneralP.pa);
			newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
			oldpen = dc.SelectObject(&newpen);
			dc.LineTo(x, y);
			dc.SelectObject(oldpen);
			newpen.DeleteObject();
		}
		for (int j = 0; j < allp; j++)
		{
			if (gpathBest[j].AdditionPU[0].pm != 0)//ÿ��ά�ȵ�ǰ��·�������޶�̬��֪���·����
			{
				CClientDC dc(this);
				CPen newpen;
				CPen *oldpen;
				float x, y, x1, y1, V, L, T, pa;
				ParticleDO tempPDO;
				x = startgoalp.sx + gpathBest[j].AdditionPU[0].pm*cos(gpathBest[j].AdditionPU[0].pa);
				y = startgoalp.sy - gpathBest[j].AdditionPU[0].pm*sin(gpathBest[j].AdditionPU[0].pa);

				if (gpathBest[j].AdditionP.pm!=0)
				{
					x1 = startgoalp.sx + gpathBest[j].AdditionP.pm * cos(gpathBest[j].AdditionP.pa);
					y1 = startgoalp.sy - gpathBest[j].AdditionP.pm * sin(gpathBest[j].AdditionP.pa);
				}
				else
				{
					if (j == (allp - 1))//��һ��Ϊ�յ�
					{
						x1 = startgoalp.gx;
						y1 = startgoalp.gy;
					}
					else
					{
						x1 = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
						y1 = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
					}
				}

				pa = tempPDO.calculate_2point_pa(x, y, x1, y1);

				//������
				drawWD(x, y, pa);

				dc.MoveTo(x, y);
				for (int i = 1; gpathBest[j].AdditionPU[i].pm != 0; i++)
				{
					T = unknown.UnknownT;

					//�ж�V��ֵ
					if (gpathBest[j].AdditionP.pm != 0)
					{
						V = gpathBest[j].AdditionP.v;
					}
					else
					{
						V = gpathBest[j].GeneralP.v;
					}

					L = V * T *drawscale * Kn_ms;//����

					x = x + L * cos(gpathBest[j].AdditionPU[i].pa);
					y = y - L * sin(gpathBest[j].AdditionPU[i].pa);

					newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
					oldpen = dc.SelectObject(&newpen);
					dc.LineTo(x, y);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();
				}
				//�ж�ĩ�˵����ߵ�
				if (gpathBest[j].AdditionP.pm != 0)
				{
					x = startgoalp.sx + gpathBest[j].AdditionP.pm*cos(gpathBest[j].AdditionP.pa);
					y = startgoalp.sy - gpathBest[j].AdditionP.pm*sin(gpathBest[j].AdditionP.pa);
				}
				else
				{
					if (j == (allp - 1))//��һ��Ϊ�յ�
					{
						x = startgoalp.gx;
						y = startgoalp.gy;
					}
					else
					{
						x = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
						y = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
					}
				}

				newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
				oldpen = dc.SelectObject(&newpen);
				dc.LineTo(x, y);
				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}

			if (gpathBest[j].AdditionPUa[0].pm != 0)//���·��
			{
				CClientDC dc(this);
				CPen newpen;
				CPen *oldpen;
				float x, y, x1, y1, V, L, T, pa;
				ParticleDO tempPDO;

				x = startgoalp.sx + gpathBest[j].AdditionPUa[0].pm*cos(gpathBest[j].AdditionPUa[0].pa);
				y = startgoalp.sy - gpathBest[j].AdditionPUa[0].pm*sin(gpathBest[j].AdditionPUa[0].pa);
				
				if (j==(allp-1))//��һ��Ϊ�յ�
				{
					x1 = startgoalp.gx;
					y1 = startgoalp.gy;
				}
				else
				{
					x1 = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
					y1 = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
				}

				pa = tempPDO.calculate_2point_pa(x, y, x1, y1);
				//������
				drawWD(x, y, gpathBest[j].AdditionPUa[0].pa);

				dc.MoveTo(x, y);
				for (int i = 1; gpathBest[j].AdditionPUa[i].pm != 0; i++)
				{
					T = unknown.UnknownT;
					V = gpathBest[j].GeneralP.v;
					L = V * T *drawscale * Kn_ms;//����

					x = x + L * cos(gpathBest[j].AdditionPUa[i].pa);
					y = y - L * sin(gpathBest[j].AdditionPUa[i].pa);

					newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
					oldpen = dc.SelectObject(&newpen);
					dc.LineTo(x, y);
					dc.SelectObject(oldpen);
					newpen.DeleteObject();
				}
				//�ж�ĩ�˵����ߵ�
				if (j == (allp - 1))//��һ��Ϊ�յ�
				{
					x = startgoalp.gx;
					y = startgoalp.gy;
				}
				else
				{
					x = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
					y = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
				}

				newpen.CreatePen(PS_DOT, 1, RGB(173, 41, 26));
				oldpen = dc.SelectObject(&newpen);
				dc.LineTo(x, y);
				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}
		}
	}
		
	//���е�Բ��
	DrawFillet();


	//����ʼĩ����ʾ��ʽ
	switch (COMBOstartgoal)
	{
	case 0:
	{
			  CClientDC dc(this);
			  SetBkMode(dc, TRANSPARENT);
			  dc.SetTextColor(RGB(241, 50, 42));
			  dc.TextOutA(startgoalp.sx, startgoalp.sy, "Start");
			  dc.SetTextColor(RGB(49, 33, 132));
			  dc.TextOutA(startgoalp.gx, startgoalp.gy, "Goal");
	}
		break;
	case 1:
	{
			  CClientDC dc(this);
			  SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			  dc.SetTextColor(RGB(241, 50, 42));
			  CString coordinatesg = "Start", ctemp1, ctemp2;
			  ctemp1.Format("%u", startgoalp.sx);
			  ctemp2.Format("%u", startgoalp.sy);
			  coordinatesg = coordinatesg + "(" + ctemp1 + " , " + ctemp2 + ")";
			  dc.TextOutA(startgoalp.sx, startgoalp.sy, coordinatesg);

			  dc.SetTextColor(RGB(49, 33, 132));
			  coordinatesg = "Goal";
			  ctemp1.Format("%u", startgoalp.gx);
			  ctemp2.Format("%u", startgoalp.gy);
			  coordinatesg = coordinatesg + "(" + ctemp1 + " , " + ctemp2 + ")";
			  dc.TextOutA(startgoalp.gx-80, startgoalp.gy, coordinatesg);
	}	
		break;
	case 2:
		break;
	default:
		break;
	}

	//���þ�̬�ϰ�����ʾ��ʽ
	switch (COMBOsoc)
	{
	case 0:
		for (int i = 0; staticoc[i].r != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(254, 82, 0));
			CString coordinate = "SOC", ctemp;
			ctemp.Format("%d", i + 1);
			coordinate = coordinate + ctemp;
			dc.TextOutA(staticoc[i].x, staticoc[i].y, coordinate);
		}
		for (int i = 0; staticor[i].HalfL != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(254, 82, 0));
			CString coordinate = "SOR", ctemp;
			ctemp.Format("%d", i + 1);
			coordinate = coordinate + ctemp;
			dc.TextOutA(staticor[i].CenterX, staticor[i].CenterY, coordinate);
			coordinate = coordinate + "[Peak1]";
			dc.TextOutA(staticor[i].Peak[1].x, staticor[i].Peak[1].y, coordinate);
			coordinate = "SOR" + ctemp;
			coordinate = coordinate + "[Peak3]";
			dc.TextOutA(staticor[i].Peak[3].x, staticor[i].Peak[3].y, coordinate);
		}
		break;
	case 1:
		for (int i = 0; staticoc[i].r != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(254, 82, 0));
			CString coordinate = "SOC", ctemp, ctemp1, ctemp2;
			ctemp.Format("%d", i + 1);
			ctemp1.Format("%.2f", staticoc[i].pm);
			ctemp2.Format("%.2f", staticoc[i].pa*180/pi);
			coordinate = coordinate + ctemp + "(" + ctemp1 + " , " + ctemp2 + ")";
			dc.TextOutA(staticoc[i].x, staticoc[i].y, coordinate);
		}
		for (int i = 0; staticor[i].HalfL != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(254, 82, 0));
			CString coordinate = "SOR", ctemp, ctemp1, ctemp2;
			ctemp.Format("%d", i + 1);
			ctemp1.Format("%.2f", staticor[i].CenterPm);
			ctemp2.Format("%.2f", staticor[i].CenterPa * 180 / pi);
			coordinate = coordinate + ctemp + "(" + ctemp1 + " , " + ctemp2 + ")";
			dc.TextOutA(staticor[i].CenterX, staticor[i].CenterY, coordinate);

			ctemp1.Format("%.2f", staticor[i].Peak[1].Pm);
			ctemp2.Format("%.2f", staticor[i].Peak[1].Pa * 180 / pi);
			coordinate = "SOR" + ctemp +"[Peak1]"+ "(" + ctemp1 + " , " + ctemp2 + ")";
			dc.TextOutA(staticor[i].Peak[1].x, staticor[i].Peak[1].y, coordinate);

			ctemp1.Format("%.2f", staticor[i].Peak[3].Pm);
			ctemp2.Format("%.2f", staticor[i].Peak[3].Pa * 180 / pi);
			coordinate = "SOR" + ctemp + "[Peak3]" + "(" + ctemp1 + " , " + ctemp2 + ")";
			dc.TextOutA(staticor[i].Peak[3].x, staticor[i].Peak[3].y, coordinate);
		}
		break;
	case 2:
		break;
	default:
		break;
	}

	//���ö�̬��֪�ϰ�����ʾ��ʽ
	switch (COMBOdo)
	{
	case 0:
		for (int i = 0; dynamicoc[i].r != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "DOC", ctemp;
			ctemp.Format("%d", i + 1);
			coordinate = coordinate + ctemp;
			dc.TextOutA(dynamicoc[i].x, dynamicoc[i].y, coordinate);
		}
		for (int i = 0; dynamicor[i].HalfL != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "DOR", ctemp;
			ctemp.Format("%d", i + 1);
			coordinate = coordinate + ctemp;
			dc.TextOutA(dynamicor[i].CenterX, dynamicor[i].CenterY, coordinate);
			coordinate = coordinate + "[Peak1]";
			dc.TextOutA(dynamicor[i].Peak[1].x, dynamicor[i].Peak[1].y, coordinate);
			coordinate = "DOR" + ctemp;
			coordinate = coordinate + "[Peak3]";
			dc.TextOutA(dynamicor[i].Peak[3].x, dynamicor[i].Peak[3].y, coordinate);
		}
		break;
	case 1:
		for (int i = 0; dynamicoc[i].r != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "DOC", ctemp, ctemp1, ctemp2;
			ctemp.Format("%d", i + 1);
			ctemp1.Format("%.2f", dynamicoc[i].Da);
			ctemp2.Format("%.2f", dynamicoc[i].V);
			coordinate = coordinate + ctemp + "(DA" + ctemp1 + " ,V " + ctemp2 + ")";
			dc.TextOutA(dynamicoc[i].x, dynamicoc[i].y, coordinate);
		}
		for (int i = 0; dynamicor[i].HalfL != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "DOR", ctemp, ctemp1, ctemp2;
			ctemp.Format("%d", i + 1);
			ctemp1.Format("%.2f", dynamicor[i].Da);
			ctemp2.Format("%.2f", dynamicor[i].V);
			coordinate = coordinate + ctemp + "(DA" + ctemp1 + " , V" + ctemp2 + ")";
			dc.TextOutA(dynamicor[i].CenterX, dynamicor[i].CenterY, coordinate);

			coordinate = "DOR[Peak1]";
			dc.TextOutA(dynamicor[i].Peak[1].x, dynamicor[i].Peak[1].y, "DOR[Peak1]");
			coordinate = "DOR[Peak3]";
			dc.TextOutA(dynamicor[i].Peak[3].x, dynamicor[i].Peak[3].y, "DOR[Peak3]");

		}
		break;
	case 2:
		break;
	default:
		break;
	}

	//���ö�̬δ֪�ϰ�����ʾ��ʽ
	switch (COMBOdoun)
	{
	case 0:
		for (int i = 0; unknownoc[i].r != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "UOC", ctemp;
			ctemp.Format("%d", i + 1);
			coordinate = coordinate + ctemp;
			dc.TextOutA(unknownoc[i].x, unknownoc[i].y, coordinate);
		}
		for (int i = 0; unknownor[i].HalfL != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "UOR", ctemp;
			ctemp.Format("%d", i + 1);
			coordinate = coordinate + ctemp;
			dc.TextOutA(unknownor[i].CenterX, unknownor[i].CenterY, coordinate);
			coordinate = coordinate + "[Peak1]";
			dc.TextOutA(unknownor[i].Peak[1].x, unknownor[i].Peak[1].y, coordinate);
			coordinate = "DOR" + ctemp;
			coordinate = coordinate + "[Peak3]";
			dc.TextOutA(unknownor[i].Peak[3].x, unknownor[i].Peak[3].y, coordinate);
		}
		break;
	case 1:
		for (int i = 0; unknownoc[i].r != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "DOC", ctemp, ctemp1, ctemp2;
			ctemp.Format("%d", i + 1);
			ctemp1.Format("%.2f", unknownoc[i].Da);
			ctemp2.Format("%.2f", unknownoc[i].V);
			coordinate = coordinate + ctemp + "(DA" + ctemp1 + " ,V " + ctemp2 + ")";
			dc.TextOutA(unknownoc[i].x, unknownoc[i].y, coordinate);
		}
		for (int i = 0; unknownor[i].HalfL != 0; i++)
		{
			CClientDC dc(this);
			SetBkMode(dc, TRANSPARENT);//�������屳��͸��
			dc.SetTextColor(RGB(239, 75, 148));
			CString coordinate = "UOR", ctemp, ctemp1, ctemp2;
			ctemp.Format("%d", i + 1);
			ctemp1.Format("%.2f", unknownor[i].Da);
			ctemp2.Format("%.2f", unknownor[i].V);
			coordinate = coordinate + ctemp + "(DA" + ctemp1 + " , V" + ctemp2 + ")";
			dc.TextOutA(unknownor[i].CenterX, unknownor[i].CenterY, coordinate);

			coordinate = "UOR[Peak1]";
			dc.TextOutA(unknownor[i].Peak[1].x, unknownor[i].Peak[1].y, "UOR[Peak1]");
			coordinate = "UOR[Peak3]";
			dc.TextOutA(unknownor[i].Peak[3].x, unknownor[i].Peak[3].y, "UOR[Peak3]");

		}
		break;
	case 2:
		break;
	default:
		break;
	}
	
	//����·���ڵ���ʾ��ʽ
	if ((gpathBest[0].GeneralP.pm != 0) || (gpathBest[0].AdditionS.pm != 0))
	{
		switch (COMBOPathPoint)
		{
		case 0:
			if (allp!=0)
			{
				for (int i = 0; i<allp; i++)
				{
					CClientDC dc(this);
					SetBkMode(dc, TRANSPARENT);//�������屳��͸��
					dc.SetTextColor(RGB(50, 132, 66));
					CString coordinate = "Path", ctemp;
					ctemp.Format("%d", i + 1);
					coordinate = coordinate + ctemp;

					float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
					float x, y, xo, yo;
					//·���㴦��ֱ������ϵֵ
					xo = gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
					yo = gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);
					x = startgoalp.sx + xo;
					y = startgoalp.sy - yo;

					dc.TextOutA(x, y, coordinate);

					if (i == 0)//�ж����͵�һ·����֮��ĸ��ӵ�
					{
						if (gpathBest[0].AdditionS.pm != 0.0)
						{
							CClientDC dc(this);
							SetBkMode(dc, TRANSPARENT);//�������屳��͸��
							dc.SetTextColor(RGB(114, 123, 180));
							CString coordinate = "P_AD0", ctemp;

							float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
							float x, y, xo, yo;
							//·���㴦��ֱ������ϵֵ
							xo = gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
							yo = gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);
							x = startgoalp.sx + xo;
							y = startgoalp.sy - yo;

							dc.TextOutA(x, y, coordinate);
						}
					}

					if (gpathBest[i].AdditionP.pm != 0.0)
					{
						CClientDC dc(this);
						SetBkMode(dc, TRANSPARENT);//�������屳��͸��
						dc.SetTextColor(RGB(114, 123, 180));
						CString coordinate = "P_AD", ctemp;
						ctemp.Format("%d", i + 1);
						coordinate = coordinate + ctemp;

						float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
						float x, y, xo, yo;
						//·���㴦��ֱ������ϵֵ
						xo = gpathBest[i].AdditionP.pm*cos(gpathBest[i].AdditionP.pa - pa_SG);
						yo = gpathBest[i].AdditionP.pm*sin(gpathBest[i].AdditionP.pa - pa_SG);
						x = startgoalp.sx + xo;
						y = startgoalp.sy - yo;

						dc.TextOutA(x, y, coordinate);
					}

				}
			}
			else//ֻ����㸽�ӵ�
			{
				CClientDC dc(this);
				SetBkMode(dc, TRANSPARENT);//�������屳��͸��
				dc.SetTextColor(RGB(114, 123, 180));
				CString coordinate = "P_AD0", ctemp;

				float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
				float x, y, xo, yo;
				//·���㴦��ֱ������ϵֵ
				xo = gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
				yo = gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);
				x = startgoalp.sx + xo;
				y = startgoalp.sy - yo;

				dc.TextOutA(x, y, coordinate);
			}
			
			break;
		case 1:
			if (allp != 0)
			{
				for (int i = 0; i<allp; i++)
				{
					CClientDC dc(this);
					SetBkMode(dc, TRANSPARENT);//�������屳��͸��
					dc.SetTextColor(RGB(50, 132, 66));
					CString coordinate = "Path", ctemp, ctemp1, ctemp2, ctemp3;
					ctemp.Format("%d", i + 1);
					ctemp1.Format("%.2f", gpathBest[i].GeneralP.pm);
					ctemp2.Format("%.2f", gpathBest[i].GeneralP.pa * 180 / pi);
					coordinate = coordinate + ctemp + "(" + ctemp1 + " , " + ctemp2 + ")";

					float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
					float x, y, xo, yo;
					//·���㴦��ֱ������ϵֵ
					xo = gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
					yo = gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);
					x = startgoalp.sx + xo;
					y = startgoalp.sy - yo;

					dc.TextOutA(x, y, coordinate);

					if (i == 0)//�ж����͵�һ·����֮��ĸ��ӵ�
					{
						if (gpathBest[0].AdditionS.pm != 0.0)
						{
							CClientDC dc(this);
							SetBkMode(dc, TRANSPARENT);//�������屳��͸��
							dc.SetTextColor(RGB(114, 123, 180));
							CString coordinate = "P_AD0", ctemp;
							ctemp1.Format("%.2f", gpathBest[0].AdditionS.pm);
							ctemp2.Format("%.2f", gpathBest[0].AdditionS.pa * 180 / pi);
							ctemp3.Format("%.2f", gpathBest[0].AdditionS.v);
							coordinate = coordinate + "(" + ctemp1 + " , " + ctemp2 + " , V:" + ctemp3 + ")";

							float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
							float x, y, xo, yo;
							//·���㴦��ֱ������ϵֵ
							xo = gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
							yo = gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);
							x = startgoalp.sx + xo;
							y = startgoalp.sy - yo;

							dc.TextOutA(x, y, coordinate);
						}
					}

					if (gpathBest[i].AdditionP.pm != 0.0)
					{
						CClientDC dc(this);
						SetBkMode(dc, TRANSPARENT);//�������屳��͸��
						dc.SetTextColor(RGB(114, 123, 180));
						CString coordinate = "P_AD", ctemp;
						ctemp.Format("%d", i + 1);
						ctemp1.Format("%.2f", gpathBest[i].AdditionP.pm);
						ctemp2.Format("%.2f", gpathBest[i].AdditionP.pa * 180 / pi);
						ctemp3.Format("%.2f", gpathBest[i].AdditionP.v);
						coordinate = coordinate + ctemp + "(" + ctemp1 + " , " + ctemp2 + " , V:" + ctemp3 + ")";

						float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
						float x, y, xo, yo;
						//·���㴦��ֱ������ϵֵ
						xo = gpathBest[i].AdditionP.pm*cos(gpathBest[i].AdditionP.pa - pa_SG);
						yo = gpathBest[i].AdditionP.pm*sin(gpathBest[i].AdditionP.pa - pa_SG);
						x = startgoalp.sx + xo;
						y = startgoalp.sy - yo;

						dc.TextOutA(x, y, coordinate);
					}
				}
			}
			else//ֻ����㸽�ӵ�
			{
				CClientDC dc(this);
				SetBkMode(dc, TRANSPARENT);//�������屳��͸��
				dc.SetTextColor(RGB(114, 123, 180));
				CString coordinate = "P_AD0", ctemp, ctemp1, ctemp2, ctemp3;
				ctemp1.Format("%.2f", gpathBest[0].AdditionS.pm);
				ctemp2.Format("%.2f", gpathBest[0].AdditionS.pa * 180 / pi);
				ctemp3.Format("%.2f", gpathBest[0].AdditionS.v);
				coordinate = coordinate + "(" + ctemp1 + " , " + ctemp2 + " , V:" + ctemp3 + ")";

				float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
				float x, y, xo, yo;
				//·���㴦��ֱ������ϵֵ
				xo = gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
				yo = gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);
				x = startgoalp.sx + xo;
				y = startgoalp.sy - yo;

				dc.TextOutA(x, y, coordinate);
			}
			
			break;
		case 2:
			break;
		default:
			break;
		}
	}
}

void USVView::drawWD(float x, float y, float pa)//����������
{
	CClientDC dc(this);
	CPen newpen;
	CPen *oldpen;
	float max, min, x1, y1, x2, y2;
	ParticleDO tempPDO;

	max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
	min = tempPDO.calculate_Pa_02PI(pa - pi / 2);
	x1 = x + unknown.UnknownR*drawscale*cos(max);
	y1 = y - unknown.UnknownR*drawscale*sin(max);
	dc.MoveTo(x1, y1);
	x2 = x + unknown.UnknownR*drawscale*cos(min);
	y2 = y - unknown.UnknownR*drawscale*sin(min);
	
	newpen.CreatePen(PS_DASHDOTDOT, 1, RGB(173, 41, 26));
	oldpen = dc.SelectObject(&newpen);
	dc.LineTo(x2, y2);
	dc.SelectObject(oldpen);
	newpen.DeleteObject();

	//����Բ
	newpen.CreatePen(PS_DASHDOTDOT, 1, RGB(173, 41, 26));
	oldpen = dc.SelectObject(&newpen);

	dc.MoveTo(x2, y2);
	AngleArc(dc, x, y, unknown.UnknownR*drawscale, min * 180 / pi, 180); //startAngle, sweepAngle

	dc.SelectObject(oldpen);
	newpen.DeleteObject();

}

void USVView::DrawArrow(point_d p1, point_d p2, double theta, int length, COLORREF rgb)//����ͷ
{
	theta = pi*theta / 180;//ת��Ϊ����
	double Px, Py, P1x, P1y, P2x, P2y;
	//��P2Ϊԭ��õ�����P2P1��P��
	Px = p1.x - p2.x;
	Py = p1.y - p2.y;
	//����P��תtheta�ǵõ�����P1
	P1x = Px*cos(theta) - Py*sin(theta);
	P1y = Px*sin(theta) + Py*cos(theta);
	//����P��ת-theta�ǵõ�����P2
	P2x = Px*cos(-theta) - Py*sin(-theta);
	P2y = Px*sin(-theta) + Py*cos(-theta);
	//�����������ƶ�����
	double x1, x2;
	x1 = sqrt(P1x*P1x + P1y*P1y);
	P1x = P1x*length / x1;
	P1y = P1y*length / x1;
	x2 = sqrt(P2x*P2x + P2y*P2y);
	P2x = P2x*length / x2;
	P2y = P2y*length / x2;
	//ƽ�Ʊ�����ֱ�ߵ�ĩ��
	P1x = P1x + p2.x;
	P1y = P1y + p2.y;
	P2x = P2x + p2.x;
	P2y = P2y + p2.y;

	CClientDC dc(this);
	CPen newpen;
	CPen *oldpen;
	newpen.CreatePen(PS_SOLID, 2, rgb);
	oldpen = dc.SelectObject(&newpen);
	
	dc.MoveTo(p1.x, p1.y);
	dc.LineTo(p2.x, p2.y);
	dc.MoveTo(p2.x, p2.y);
	dc.LineTo(P1x, P1y);
	dc.MoveTo(p2.x, p2.y);
	dc.LineTo(P2x, P2y);

	dc.SelectObject(oldpen);
	newpen.DeleteObject();
}

void USVView::DrawFillet()//����Բ��
{
	CClientDC dc(this);
	CPen newpen;
	CPen *oldpen;
	float Fillet_R = 5 * 8 * 3 * drawscale/2;//��ת�뾶10*
	float startAngle, sweepAngle,k1,k2,pa1,pa2,pa12,tempd;
	point_d center, start, end ,point1, point2, point3;
	ParticleDO tempC;

	float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
	
	//�ȼ��㳣���  ��ʾ������
	for (int i = 0; i < allp; i++)
	{
		if (i==0)
		{
			point1.x = startgoalp.sx;
			point1.y = startgoalp.sy;
			point2.x = startgoalp.sx + gpathBest[0].GeneralP.pm*cos(gpathBest[0].GeneralP.pa - pa_SG);
			point2.y = startgoalp.sy - gpathBest[0].GeneralP.pm*sin(gpathBest[0].GeneralP.pa - pa_SG);
			point3.x = startgoalp.sx + gpathBest[1].GeneralP.pm*cos(gpathBest[1].GeneralP.pa - pa_SG);
			point3.y = startgoalp.sy - gpathBest[1].GeneralP.pm*sin(gpathBest[1].GeneralP.pa - pa_SG);
		}
		else if (i==(allp-1))
		{
			point1.x = startgoalp.sx + gpathBest[i-1].GeneralP.pm*cos(gpathBest[i-1].GeneralP.pa - pa_SG);
			point1.y = startgoalp.sy - gpathBest[i-1].GeneralP.pm*sin(gpathBest[i-1].GeneralP.pa - pa_SG);
			point2.x = startgoalp.sx + gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
			point2.y = startgoalp.sy - gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);
			point3.x = startgoalp.gx;
			point3.y = startgoalp.gy;
		}
		else
		{
			point1.x = startgoalp.sx + gpathBest[i - 1].GeneralP.pm*cos(gpathBest[i - 1].GeneralP.pa - pa_SG);
			point1.y = startgoalp.sy - gpathBest[i - 1].GeneralP.pm*sin(gpathBest[i - 1].GeneralP.pa - pa_SG);
			point2.x = startgoalp.sx + gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
			point2.y = startgoalp.sy - gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);
			point3.x = startgoalp.sx + gpathBest[i + 1].GeneralP.pm*cos(gpathBest[i + 1].GeneralP.pa - pa_SG);
			point3.y = startgoalp.sy - gpathBest[i + 1].GeneralP.pm*sin(gpathBest[i + 1].GeneralP.pa - pa_SG);
		}
		if ((point2.x - point1.x)!=0.0)
		{
			k1 = (point2.y - point1.y) / (point2.x - point1.x);
			k2 = (point3.y - point2.y) / (point3.x - point2.x);
		}
		else
		{
		}


		if (abs(k1 - k2)>0.01)
		{
			//���㽻��
			//start = tempC.calculate_point_segment_circle(point2.x, point2.y, point1.x, point1.y, Fillet_R);//���󵽶���̶�����ĵ��ǵ�ʼĩ��
			//end = tempC.calculate_point_segment_circle(point2.x, point2.y, point3.x, point3.y, Fillet_R);
			pa1 = tempC.calculate_2point_pa(point2.x, point2.y, point1.x, point1.y);
			pa2 = tempC.calculate_2point_pa(point2.x, point2.y, point3.x, point3.y);
			pa12 = abs(pa1 - pa2);//����ֱ�ߵļнǣ�Ϊ���
			if (pa12>pi)
			{
				pa12 = 2 * pi - pa12;
			}

			//�������
			tempd = Fillet_R / tan(pa12/2);
			start.x = point2.x + tempd  * cos(pa1);
			start.y = k1 * (start.x - point2.x) + point2.y;

			//�����յ�
			end.x = point2.x + tempd  * cos(pa2);
			end.y = k2 * (end.x - point2.x) + point2.y;
				
			//������ֱ���ཻ��Բ�ĵ�
			center.x = (k2 * start.x - k1 * end.x + k1 * k2 * (start.y - end.y)) / (k2 - k1);
			center.y = (-1.0 / k1) * (center.x -start.x) + start.y;
			
			startAngle = tempC.calculate_2point_pa(center.x, center.y, start.x, start.y)*180/pi;
			sweepAngle = abs(startAngle - tempC.calculate_2point_pa(center.x, center.y, end.x, end.y) * 180 / pi);
			if (sweepAngle>180)
			{
				sweepAngle = sweepAngle - 180;
			}
			if (pa1<pa2)//k1<k2//point3.y>=(k1*(point3.x - point2.x)+point2.y)
			{
				if ((pa2-pa1)<pi)
				{
					sweepAngle = -sweepAngle;
				}				
			}
			else
			{
				if (!((pa1 - pa2)<pi))
				{
					sweepAngle = -sweepAngle;
				}
			}

			newpen.CreatePen(PS_SOLID, 1, RGB(50, 132, 66));
			oldpen = dc.SelectObject(&newpen);

			dc.MoveTo(start.x, start.y);
			AngleArc(dc, center.x, center.y, Fillet_R, startAngle, sweepAngle); //startAngle, sweepAngle

			dc.SelectObject(oldpen);
			newpen.DeleteObject();
		}

	}

	//�ټ��㶯̬���ӵ�  ��ʾ������
	for (int i = 0; i < allp; i++)
	{		
		if (gpathBest[0].AdditionS.pm!=0.0)
		{
			point1.x = startgoalp.sx;
			point1.y = startgoalp.sy;
			point2.x = startgoalp.sx + gpathBest[0].AdditionS.pm*cos(gpathBest[0].AdditionS.pa - pa_SG);
			point2.y = startgoalp.sy - gpathBest[0].AdditionS.pm*sin(gpathBest[0].AdditionS.pa - pa_SG);
			point3.x = startgoalp.sx + gpathBest[0].GeneralP.pm*cos(gpathBest[0].GeneralP.pa - pa_SG);
			point3.y = startgoalp.sy - gpathBest[0].GeneralP.pm*sin(gpathBest[0].GeneralP.pa - pa_SG);

			if ((point2.x - point1.x) != 0.0)
			{
				k1 = (point2.y - point1.y) / (point2.x - point1.x);
				k2 = (point3.y - point2.y) / (point3.x - point2.x);
			}
			else
			{
			}

			if (abs(k1 - k2)>0.01)
			{
				//���㽻��
				//start = tempC.calculate_point_segment_circle(point2.x, point2.y, point1.x, point1.y, Fillet_R);//���󵽶���̶�����ĵ��ǵ�ʼĩ��
				//end = tempC.calculate_point_segment_circle(point2.x, point2.y, point3.x, point3.y, Fillet_R);
				pa1 = tempC.calculate_2point_pa(point2.x, point2.y, point1.x, point1.y);
				pa2 = tempC.calculate_2point_pa(point2.x, point2.y, point3.x, point3.y);
				pa12 = abs(pa1 - pa2);//����ֱ�ߵļнǣ�Ϊ���
				if (pa12>pi)
				{
					pa12 = 2 * pi - pa12;
				}

				//�������
				tempd = Fillet_R / tan(pa12 / 2);
				start.x = point2.x + tempd  * cos(pa1);
				start.y = k1 * (start.x - point2.x) + point2.y;

				//�����յ�
				end.x = point2.x + tempd  * cos(pa2);
				end.y = k2 * (end.x - point2.x) + point2.y;

				//������ֱ���ཻ��Բ�ĵ�
				center.x = (k2 * start.x - k1 * end.x + k1 * k2 * (start.y - end.y)) / (k2 - k1);
				center.y = (-1.0 / k1) * (center.x - start.x) + start.y;

				startAngle = tempC.calculate_2point_pa(center.x, center.y, start.x, start.y) * 180 / pi;
				sweepAngle = abs(startAngle - tempC.calculate_2point_pa(center.x, center.y, end.x, end.y) * 180 / pi);
				if (sweepAngle>180)
				{
					sweepAngle = sweepAngle - 180;
				}
				if (pa1<pa2)//k1<k2//point3.y>=(k1*(point3.x - point2.x)+point2.y)
				{
					if ((pa2 - pa1)<pi)
					{
						sweepAngle = -sweepAngle;
					}
				}
				else
				{
					if (!((pa1 - pa2)<pi))
					{
						sweepAngle = -sweepAngle;
					}
				}

				newpen.CreatePen(PS_SOLID, 1, RGB(50, 132, 66));
				oldpen = dc.SelectObject(&newpen);

				dc.MoveTo(start.x, start.y);
				AngleArc(dc, center.x, center.y, Fillet_R, startAngle, sweepAngle); //startAngle, sweepAngle

				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}
		}

		if (gpathBest[i].AdditionP.pm != 0.0)
		{
			if (i == (allp - 1))
			{
				point1.x = startgoalp.sx + gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
				point1.y = startgoalp.sy - gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);
				point2.x = startgoalp.sx + gpathBest[i].AdditionP.pm*cos(gpathBest[i].AdditionP.pa - pa_SG);
				point2.y = startgoalp.sy - gpathBest[i].AdditionP.pm*sin(gpathBest[i].AdditionP.pa - pa_SG);
				point3.x = startgoalp.gx;
				point3.y = startgoalp.gy;
			}
			else
			{
				point1.x = startgoalp.sx + gpathBest[i].GeneralP.pm*cos(gpathBest[i].GeneralP.pa - pa_SG);
				point1.y = startgoalp.sy - gpathBest[i].GeneralP.pm*sin(gpathBest[i].GeneralP.pa - pa_SG);
				point2.x = startgoalp.sx + gpathBest[i].AdditionP.pm*cos(gpathBest[i].AdditionP.pa - pa_SG);
				point2.y = startgoalp.sy - gpathBest[i].AdditionP.pm*sin(gpathBest[i].AdditionP.pa - pa_SG);
				point3.x = startgoalp.sx + gpathBest[i + 1].GeneralP.pm*cos(gpathBest[i + 1].GeneralP.pa - pa_SG);
				point3.y = startgoalp.sy - gpathBest[i + 1].GeneralP.pm*sin(gpathBest[i + 1].GeneralP.pa - pa_SG);
			}

			if ((point2.x - point1.x) != 0.0)
			{
				k1 = (point2.y - point1.y) / (point2.x - point1.x);
				k2 = (point3.y - point2.y) / (point3.x - point2.x);
			}
			else
			{
			}

			if (abs(k1 - k2)>0.01)
			{
				//���㽻��
				//start = tempC.calculate_point_segment_circle(point2.x, point2.y, point1.x, point1.y, Fillet_R);//���󵽶���̶�����ĵ��ǵ�ʼĩ��
				//end = tempC.calculate_point_segment_circle(point2.x, point2.y, point3.x, point3.y, Fillet_R);
				pa1 = tempC.calculate_2point_pa(point2.x, point2.y, point1.x, point1.y);
				pa2 = tempC.calculate_2point_pa(point2.x, point2.y, point3.x, point3.y);
				pa12 = abs(pa1 - pa2);//����ֱ�ߵļнǣ�Ϊ���
				if (pa12>pi)
				{
					pa12 = 2 * pi - pa12;
				}

				//�������
				tempd = Fillet_R / tan(pa12 / 2);
				start.x = point2.x + tempd  * cos(pa1);
				start.y = k1 * (start.x - point2.x) + point2.y;

				//�����յ�
				end.x = point2.x + tempd  * cos(pa2);
				end.y = k2 * (end.x - point2.x) + point2.y;

				//������ֱ���ཻ��Բ�ĵ�
				center.x = (k2 * start.x - k1 * end.x + k1 * k2 * (start.y - end.y)) / (k2 - k1);
				center.y = (-1.0 / k1) * (center.x - start.x) + start.y;

				startAngle = tempC.calculate_2point_pa(center.x, center.y, start.x, start.y) * 180 / pi;
				sweepAngle = abs(startAngle - tempC.calculate_2point_pa(center.x, center.y, end.x, end.y) * 180 / pi);
				if (sweepAngle>180)
				{
					sweepAngle = sweepAngle - 180;
				}
				if (pa1<pa2)//k1<k2//point3.y>=(k1*(point3.x - point2.x)+point2.y)
				{
					if ((pa2 - pa1)<pi)
					{
						sweepAngle = -sweepAngle;
					}
				}
				else
				{
					if (!((pa1 - pa2)<pi))
					{
						sweepAngle = -sweepAngle;
					}
				}

				newpen.CreatePen(PS_SOLID, 1, RGB(50, 132, 66));
				oldpen = dc.SelectObject(&newpen);

				dc.MoveTo(start.x, start.y);
				AngleArc(dc, center.x, center.y, Fillet_R, startAngle, sweepAngle); //startAngle, sweepAngle

				dc.SelectObject(oldpen);
				newpen.DeleteObject();
			}
		}
		
	}
}

// USVView ��ӡ


void USVView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL USVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void USVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void USVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void USVView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void USVView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// USVView ���

#ifdef _DEBUG
void USVView::AssertValid() const
{
	CView::AssertValid();
}

void USVView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

USVDoc* USVView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(USVDoc)));
	return (USVDoc*)m_pDocument;
}
#endif //_DEBUG


// USVView ��Ϣ�������


void USVView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	//״̬����ʾ����ֵ
	str.Format(_T("���ָ��ĵ�ǰ����(X:%d, Y:%d)"), point.x, point.y);
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMFCRibbonStatusBar* statusBar = (CMFCRibbonStatusBar*)&pFrame->m_wndStatusBar;
	statusBar->SetInformation(str);

	CView::OnMouseMove(nFlags, point);
}

void USVView::OnSet_start_goal_Position()
{
	// TODO:  �ڴ���������������
	static int flag = 0;
	//��ʼ���Ի���
	if (!flag)
	{
		set_start_goal_Position.StartX = 50;
		set_start_goal_Position.StartY = 400;
		set_start_goal_Position.GoalX = 1150;
		set_start_goal_Position.GoalY = 400;
		set_start_goal_Position.V_Kn = 40;
	}
	flag++;
	set_start_goal_Position.DoModal();
	Invalidate();
}

void USVView::OnBtsetpso()
{
	// TODO:  �ڴ���������������
	static int flag = 0;
	//��ʼ���Ի���
	if (!flag)
	{
		setpso.PSOgenerations = 100;
		setpso.PSOparticle_num = 50;
		setpso.PSOsetV_numMAX = 100;
		setpso.PSOsetInitialV = 32;
	}
	flag++;
	setpso.DoModal();
	Invalidate();
}

void USVView::Onsetpsodo()
{
	// TODO:  �ڴ���������������	
	static int flag = 0;
	//��ʼ���Ի���
	if (!flag)
	{
		setdopso.PSOgenerationsDO = 50;
		setdopso.PSOparticle_numDO = 50;
		setdopso.PSOchangeVdo = 1;
		setdopso.PSOchangeDado = 70;
		setdopso.PSOchangeDO = false;
	}
	flag++;
	setdopso.DoModal();
	Invalidate();
}

void USVView::OnSetviewsize()
{
	// TODO:  �ڴ���������������
	static int flag = 0;
	//��ʼ���Ի���
	if (!flag)
	{
	setviewsize.SetViewChange = 0;
	}
	flag++;
	
	CRect rc;
	int x, y;
	GetClientRect(&rc);//��û����ľ��δ�С
	x = rc.right;
	y = rc.bottom;

	setviewsize.setviewL = x-1 ;
	setviewsize.setviewW = y-1 ;
	setviewsize.DoModal();

	Invalidate();
}

void USVView::OnSetunknown()
{
	// TODO:  �ڴ���������������
	static int flag = 0;
	//��ʼ���Ի���
	if (!flag)
	{
		Setunknown.UnknownR = 200;
		Setunknown.UnknownT = 2;
	}
	flag++;
	Setunknown.DoModal();
	Invalidate();
}

void USVView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�ж���ʼĩλ�øı� ���ػ�
	if (previous.gx != startgoalp.gx || previous.gy != startgoalp.gy || previous.sx != startgoalp.sx || previous.sy != startgoalp.sy || previous.v_kn != startgoalp.v_kn )
	{
		if (staticoc[0].r != 0)
		{
			Setstaticobstaclecircle.DoModal();
		}
		if (staticor[0].HalfL != 0)
		{
			Setstaticobstaclerectangle.DoModal();
		}		
		if (dynamicoc[0].r != 0)
		{
			SetdynamicOC.DoModal();
		}
		if (dynamicor[0].HalfL != 0)
		{
			SetdynamicOR.DoModal();
		}
	}
	previous = startgoalp;
	if (state_sgposition || state_staticOC || state_staticOR || state_dynamicOC || state_dynamicOR)
		Invalidate(); 
	CView::OnLButtonUp(nFlags, point);
}


void USVView::OnSetstaticobstaclecircle()
{
	// TODO:  �ڴ���������������
	Setstaticobstaclecircle.DoModal();
	Invalidate();
}

void USVView::OnSetstaticobstaclerectangle()
{
	// TODO:  �ڴ���������������	
	Setstaticobstaclerectangle.DoModal();
	Invalidate();
}

void USVView::OnSetdynamicOC()
{
	// TODO:  �ڴ���������������
	SetdynamicOC.DoModal();
	Invalidate();
}

void USVView::OnSetdynamicOR()
{
	// TODO:  �ڴ���������������
	SetdynamicOR.DoModal();
	Invalidate();
}

void USVView::OnSetunknownoc()
{
	// TODO:  �ڴ���������������
	SetunknownOC.DoModal();
	Invalidate();
}

void USVView::OnSetunknownor()
{
	// TODO:  �ڴ���������������
	SetunknownOR.DoModal();
	Invalidate();
}

void USVView::OnCombostartgoal()
{
	// TODO:  �ڴ���������������
	//�õ���Ͽ������
	CMFCRibbonBar* pRibbon = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbon->FindByID(ID_COMBOstartgoal));
	COMBOstartgoal = pSizeCombo->GetCurSel();
	
	Invalidate();
}

void USVView::OnComboSoc()
{
	// TODO:  �ڴ���������������
	//�õ���Ͽ������
	CMFCRibbonBar* pRibbon = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbon->FindByID(ID_COMBO_SOC));
	COMBOsoc = pSizeCombo->GetCurSel();

	Invalidate();
}

void USVView::OnComboDo()
{
	// TODO:  �ڴ���������������COMBOdo
	//�õ���Ͽ������
	CMFCRibbonBar* pRibbon = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbon->FindByID(ID_COMBO_DO));
	COMBOdo = pSizeCombo->GetCurSel();

	Invalidate();
}

void USVView::OnComboDoun()
{
	// TODO:  �ڴ���������������COMBOdoun
	//�õ���Ͽ������
	CMFCRibbonBar* pRibbon = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbon->FindByID(ID_COMBO_DOun));
	COMBOdoun = pSizeCombo->GetCurSel();

	Invalidate();
}

void USVView::OnComboPathpoint()
{
	// TODO:  �ڴ���������������
	CMFCRibbonBar* pRibbon = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbon->FindByID(ID_COMBO_PathPoint));
	COMBOPathPoint = pSizeCombo->GetCurSel();

	Invalidate();
}

void USVView::OnComboViewinformation()
{
	// TODO:  �ڴ���������������
	CMFCRibbonBar* pRibbon = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbon);
	CMFCRibbonComboBox* pSizeCombo = DYNAMIC_DOWNCAST(CMFCRibbonComboBox, pRibbon->FindByID(ID_COMBO_ViewInformation));
	COMBOview = pSizeCombo->GetCurSel();

	Invalidate();

}

void USVView::OnViewdo()
{
	// TODO:  �ڴ���������������

	if (doview)
	{
		doview = false;
	}
	else
	{
		doview = true;
	}

	Invalidate();
}

void USVView::calculate_SObsticle_num()//���㾲̬�ϰ��Բ�ͷ�����ά����Ϣ����
{
	//ÿ����һ�γ�ʼ��һ��
	for (int i = 0; i < 30; i++)
	{
		SObsticle_num[i].form = 0;
		SObsticle_num[i].rcnum = 0;
		SObsticle_num[i].num = 0;
		SObsticle_num[i].pm = 0.0;
	}
	//���ϰ���Բ����Ϣ�����ϰ�������
	for (int i = 0; staticoc[i].r != 0; i++)
	{
		SObsticle_num[i].form = 1;
		SObsticle_num[i].num = i;
		SObsticle_num[i].pm = staticoc[i].pm;
		allp++;
	}
	//���ϰ��﷽����Ϣ�����ϰ�������
	if (SObsticle_num[0].form == 0)//��û��Բ���ϰ���
	{
		if (staticor[0].HalfL != 0)
		{
			//1peak
			SObsticle_num[0].form = 2;
			SObsticle_num[0].rcnum = 1;
			SObsticle_num[0].num = 0;
			SObsticle_num[0].pm = staticor[0].Peak[1].PmEX;
			allp++;

			//2peak
			if (staticor[0].Peak[3].PmEX < SObsticle_num[0].pm)
			{
				SObsticle_num[1] = SObsticle_num[0];

				SObsticle_num[0].form = 2;
				SObsticle_num[0].rcnum = 3;
				SObsticle_num[0].num = 0;
				SObsticle_num[0].pm = staticor[0].Peak[3].PmEX;
				allp++;
			}
			else
			{
				SObsticle_num[1].form = 2;
				SObsticle_num[1].rcnum = 3;
				SObsticle_num[1].num = 0;
				SObsticle_num[1].pm = staticor[0].Peak[3].PmEX;
				allp++;
			}

			for (int i = 1; staticor[i].HalfL != 0; i++)
			{
				for (int j = 0; j < allp; j++)
				{
					//1peak
					if (staticor[i].Peak[1].PmEX < SObsticle_num[j].pm)
					{
						for (int m = allp; m > j; m--)
						{
							SObsticle_num[m] = SObsticle_num[m - 1];
						}
						SObsticle_num[j].form = 2;
						SObsticle_num[j].rcnum = 1;
						SObsticle_num[j].num = i;
						SObsticle_num[j].pm = staticor[i].Peak[1].PmEX;
						allp++;
						break;
					}
					else if (j == allp - 1)
					{
						SObsticle_num[j + 1].form = 2;
						SObsticle_num[j + 1].rcnum = 1;
						SObsticle_num[j + 1].num = i;
						SObsticle_num[j + 1].pm = staticor[i].Peak[1].PmEX;
						allp++;
						break;
					}
				}

				for (int j = 0; j < allp; j++)
				{
					//2peak
					if (staticor[i].Peak[3].PmEX < SObsticle_num[j].pm)
					{
						for (int m = allp; m > j; m--)
						{
							SObsticle_num[m] = SObsticle_num[m - 1];
						}
						SObsticle_num[j].form = 2;
						SObsticle_num[j].rcnum = 3;
						SObsticle_num[j].num = i;
						SObsticle_num[j].pm = staticor[i].Peak[3].PmEX;
						allp++;
						break;
					}
					else if (j == allp - 1)
					{
						SObsticle_num[j + 1].form = 2;
						SObsticle_num[j + 1].rcnum = 3;
						SObsticle_num[j + 1].num = i;
						SObsticle_num[j + 1].pm = staticor[i].Peak[3].PmEX;
						allp++;
						break;
					}
				}
			}
		}	
		
	}
	else
	{
		for (int i = 0; staticor[i].HalfL != 0; i++)
		{

			for (int j = 0; j < allp; j++)
			{
				//1peak
				if (staticor[i].Peak[1].PmEX < SObsticle_num[j].pm)
				{
					for (int m = allp; m > j; m--)
					{
						SObsticle_num[m] = SObsticle_num[m - 1];
					}
					SObsticle_num[j].form = 2;
					SObsticle_num[j].rcnum = 1;
					SObsticle_num[j].num = i;
					SObsticle_num[j].pm = staticor[i].Peak[1].PmEX;
					allp++;
					break;
				}
				else if (j == allp - 1)
				{
					SObsticle_num[j + 1].form = 2;
					SObsticle_num[j + 1].rcnum = 1;
					SObsticle_num[j + 1].num = i;
					SObsticle_num[j + 1].pm = staticor[i].Peak[1].PmEX;
					allp++;
					break;
				}
			}

			for (int j = 0; j < allp; j++)
			{
				//2peak
				if (staticor[i].Peak[3].PmEX < SObsticle_num[j].pm)
				{
					for (int m = allp; m > j; m--)
					{
						SObsticle_num[m] = SObsticle_num[m - 1];
					}
					SObsticle_num[j].form = 2;
					SObsticle_num[j].rcnum = 3;
					SObsticle_num[j].num = i;
					SObsticle_num[j].pm = staticor[i].Peak[3].PmEX;
					allp++;
					break;
				}
				else if (j == allp - 1)
				{
					SObsticle_num[j + 1].form = 2;
					SObsticle_num[j + 1].rcnum = 3;
					SObsticle_num[j + 1].num = i;
					SObsticle_num[j + 1].pm = staticor[i].Peak[3].PmEX;
					allp++;
					break;
				}
			}
		}
	}
}

void USVView::OnCalculatePSO()//��̬��֪����Ⱥ����
{
	DWORD start = GetTickCount();//��ʱ��ʼ

	calculate_SObsticle_num();//���㾲̬�ϰ��Բ�ͷ�����ά����Ϣ����

	if ((SObsticle_num[0].form != 1) & (SObsticle_num[0].form != 2))//û�о�̬�ϰ���
	{
		allp = 0;
		//·����ʼ��
		for (int i = 0; i < 50; i++)
		{
			gpathBest[i].AdditionP = {};
			gpathBest[i].AdditionS = {};
			gpathBest[i].GeneralP = {};			
			gpathBest[i].GeneralP.v = startgoalp.v_kn;
			for (int j = 0; j < 200; j++)
			{
				gpathBest[i].AdditionPU[j] = {};
				gpathBest[i].AdditionPUa[j] = {};
				gpathBest[i].AdditionSU[j] = {};
				gpathBest[i].AdditionSUa[j] = {};
			}
		}
	}
	else
	{
		// TODO:  �ڴ���������������
		Particle *particle = new Particle[pso.PSOparticle_num];//��̬��������Ⱥ//Particle particle[particle_num];

		float w;//��������  

		allp = 0;//���é�������һ���Լӷ���
		/*for (int i = 0; staticoc[i].r != 0; i++)//�ж��ϰ������
		{
		allp++;
		}*/		
		//·����ʼ��
		for (int i = 0; i < 50; i++)
		{
			gpathBest[i].AdditionP = {};
			gpathBest[i].AdditionS = {};
			gpathBest[i].GeneralP = {};
			gpathBest[i].GeneralP.v = startgoalp.v_kn;
			for (int j = 0; j < 200; j++)
			{
				gpathBest[i].AdditionPU[j] = {};
				gpathBest[i].AdditionPUa[j] = {};
				gpathBest[i].AdditionSU[j] = {};
				gpathBest[i].AdditionSUa[j] = {};
			}
		}
		calculate_SObsticle_num();//���㾲̬�ϰ��Բ�ͷ�����ά����Ϣ����

		particle[0].set_BasicP_num(allp);//��������Ⱥά�����ϰ��
		//int m = particle[1].get_BasicP_num();//�����Ƿ����óɹ�

		calculate_forbidThisDimA();//��ά�ϵ��ϰ������ǣ������һά��Ŀ���Ľ���ǣ��ڴ��󣬿�ʡ�ԣ���������������������

		srand((int)time(NULL));
		//����Ⱥ���ó�ʼֵ
		for (int i = 0; i < pso.PSOparticle_num; i++)
		{
			particle[i].set_pathpoint();
		}

		/*float randPA;
		srand((int)time(NULL));
		Pathpoint *point=new Pathpoint[allp];
		for (int i = 0; i < particle_num; i++)
		{
		for (int j = 0; j < allp; j++)
		{
		randPA = (rand() / (float)RAND_MAX) * 2 * pi;
		*(point + j) = Pathpoint(staticoc[j].pm, randPA);
		}
		particle[i].set_pathpoint(point);
		}
		delete[] point;*///��̬�����ϰ���㣬����������Ⱥ��ʼ��

		//���ˣ������������Ⱥ�ĳ�ʼ��

		//////////////////////////////////////  

		//Pathpoint gpathBest[50];  //ȫ������·���⡣  
		//int bestIndex = 0;//���Ŵ���
		float bestFitness; //��õ���Ӧ�ȡ�  
		bestFitness = particle[0].get_Fitness();

		for (int i = 0; i < allp; i++)
		{
			gpathBest[i] = particle[0].pathpointBest[i];
		}//particle[].pathpointBest[]���鸳ֵ��gpathBest[]

		for (int i = 1; i<pso.PSOparticle_num; ++i)
		{
			if (particle[i].get_Fitness()<bestFitness)
			{
				bestFitness = particle[i].get_Fitness();
				for (int j = 0; j < allp; j++)
				{
					gpathBest[j] = particle[i].pathpointBest[j];
				}//particle[].pathpointBest[]���鸳ֵ��gpathBest[]
				//bestIndex = i;
			}
		}
		////////////////////////////////���ˣ��Ѿ�Ѱ�ҵ���ʼʱ����Ⱥ���š�  

		bestIndex = 0;//���Ŵ���
		gbestFitness = FLT_MAX;//float���ֵ; //��õ���Ӧ��

		for (int k = 0; k<pso.PSOgenerations; ++k)   //kΪ����������  
		{
			w = 0.9f - (0.95f - 0.2f)*k / pso.PSOgenerations;  //��������
			for (int i = 0; i<pso.PSOparticle_num; ++i)
			{
				particle[i].setV(gpathBest, w);
				//particle[i].setV_pathpoint();
				particle[i].set_Fitness();
			}

			bestFitness = particle[0].get_Fitness();
			for (int i = 0; i < allp; i++)
			{
				gpathBest[i] = particle[0].pathpointBest[i];
			}//particle[].pathpointBest[]���鸳ֵ��gpathBest[]

			for (int i = 1; i<pso.PSOparticle_num; ++i)
			{
				if (particle[i].get_Fitness()<bestFitness)
				{
					bestFitness = particle[i].get_Fitness();
					for (int j = 0; j < allp; j++)
					{
						gpathBest[j] = particle[i].pathpointBest[j];
					}//particle[].pathpointBest[]���鸳ֵ��gpathBest[]
					//bestIndex = i;
				}
			}

			if (gbestFitness > bestFitness)
			{
				gbestFitness = bestFitness;
				bestIndex = k + 1;
			}
			bestFitness_list[k].num = k + 1;
			bestFitness_list[k].bestFitness = bestFitness;

		}
		delete[] particle;
		gbestFitness_OptimizePATH = bestFitness;
		//����
		best_eachGenerations[testNum].PSOgenerations = pso.PSOgenerations;
		best_eachGenerations[testNum].PSOparticle_num = pso.PSOparticle_num;
		best_eachGenerations[testNum].PSOsetInitialV = pso.PSOsetInitialV;
		best_eachGenerations[testNum].PSOsetV_numMAX = pso.PSOsetV_numMAX;
		best_eachGenerations[testNum].UsedTime = (float)UsedTimeInMs / 1000.0;
		best_eachGenerations[testNum].bestFitness = bestFitness;
		best_eachGenerations[testNum].bestFitness_num = bestIndex;
	}
	
	DWORD stop = GetTickCount();//��ʱ����
	UsedTimeInMs = stop - start;	
	
	thisPSOnum++;
	best_eachGenerations[testNum].thisPSOnum = thisPSOnum;
	
	testNum++;
	Invalidate();
}

void USVView::OnCalculatedoPso()//��̬��֪����Ⱥ����
{
	// TODO:  �ڴ���������������ForbidA

	DWORD start = GetTickCount();//��ʱ��ʼ	
	
	calculate_DObsticle_num();//���㶯̬�ϰ��Բ�ͷ����Ƿ���USV��ײ����Ϣ����
	
	calculate_DObsticle_forbidA();//���㶯̬�ཻ�ϰ�������

	ParticleDO tempParticleDO;
	
	//DObsticle_num[i].pointNum;
	for (int z = 0; z < docalNUM[0].CalNum; z++)
	{
		ParticleDO *particledo = new ParticleDO[pso_do.PSOparticle_num];//��̬��������Ⱥ//Particle particle[particle_num];

		particledo[0].set_BasicP_num(z);//��������Ⱥά�����ϰ��
		int m = particledo[1].get_BasicP_num();//�����Ƿ����óɹ�
		float w;//��������  
		srand((int)time(NULL));
		//����Ⱥ���ó�ʼֵ
		for (int i = 0; i < (int)pso_do.PSOparticle_num; i++)
		{
			particledo[i].set_pathpoint();
		}

		//���ˣ������������Ⱥ�ĳ�ʼ��

		/////////////////////////////////////////////////////////////////////////////////////////

		float bestFitness; //��õ���Ӧ�� 
		bestFitness = particledo[0].get_Fitness();
		gpathBestDO[z] = particledo[0].pathpointBest;//particle[].pathpointBest[]���鸳ֵ��gpathBest[]

		for (int i = 1; i<(int)pso_do.PSOparticle_num; ++i)
		{
			if (particledo[i].get_Fitness()<bestFitness)
			{
				bestFitness = particledo[i].get_Fitness();
				gpathBestDO[z] = particledo[i].pathpointBest;
			}
		}
		////////////////////////////////���ˣ��Ѿ�Ѱ�ҵ���ʼʱ����Ⱥ����

		bestIndexDO = 0;//���Ŵ���
		gbestFitnessDO = FLT_MAX;//float���ֵ; //��õ���Ӧ��

		for (int k = 0; k<(int)pso_do.PSOgenerations; ++k)   //kΪ����������  
		{
			w = 0.9f - (0.95f - 0.2f)*k / pso_do.PSOgenerations;  //��������
			for (int i = 0; i<(int)pso_do.PSOparticle_num; ++i)
			{
				particledo[i].setV(gpathBestDO, w);
				//particle[i].setV_pathpoint();
				particledo[i].set_Fitness();
			}

			bestFitness = particledo[0].get_Fitness();
			gpathBestDO[z] = particledo[0].pathpointBest;//particle[].pathpointBest[]���鸳ֵ��gpathBest[]

			for (int i = 1; i<(int)pso_do.PSOparticle_num; ++i)
			{
				if (particledo[i].get_Fitness()<bestFitness)
				{
					bestFitness = particledo[i].get_Fitness();
					gpathBestDO[z] = particledo[i].pathpointBest;
				}
			}

			if (gbestFitness > bestFitness)
			{
				gbestFitness = bestFitness;
				bestIndex = k + 1;
			}
			bestFitness_listDO[z][k].num = k + 1;
			bestFitness_listDO[z][k].bestFitness = bestFitness;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//����·�������·��������
		float pa_v;//�ı��·���ķ����
		float Vso; //�ı��ĺϳ��ٶ�
		float Vusv;// Ϊ�ı��USV���ٶ�
		float x0, y0, Ab, temppm;
		int n, pointNum;
		point_d newPoint;
		SetStaticObstacleCircle calculate_PA;
		ParticleDO calculateNewpoint;
		n = DObsticle_num[docalNUM[z].startNUM].num;
		if (DObsticle_num[docalNUM[z].startNUM].form == 1)//Բ�ζ�̬�ϰ���
		{
			pa_v = dynamicoc[n].a_path + gpathBestDO[z].DAchange;
			Vusv = startgoalp.v_kn + gpathBestDO[z].Vchange;
			//�ı��
			Ab = abs(pa_v - dynamicoc[n].Da*pi / 180);//·�����ٶȷ�����ϰ����ٶȷ���н�
			Vso = sqrt(pow((float)Vusv, 2) + pow((float)dynamicoc[n].V, 2) - 2 * Vusv * dynamicoc[n].V * cos(Ab));
		}
		else if (DObsticle_num[docalNUM[z].startNUM].form == 2)//���ζ�̬�ϰ���	
		{
			pa_v = dynamicor[n].a_path + gpathBestDO[z].DAchange;
			Vusv = startgoalp.v_kn + gpathBestDO[z].Vchange;
			//�ı��
			Ab = abs(pa_v - dynamicor[n].Da*pi / 180);//·�����ٶȷ�����ϰ����ٶȷ���н�
			Vso = sqrt(pow((float)Vusv, 2) + pow((float)dynamicor[n].V, 2) - 2 * Vusv * dynamicor[n].V * cos(Ab)) ;
		}

		if (pa_v < 0)
			pa_v = pa_v + 2 * pi;
		else if (pa_v >= 2 * pi)
			pa_v = pa_v - 2 * pi;

		pointNum = DObsticle_num[docalNUM[z].startNUM].pointNum;
		if (pointNum == -1)//1.��ʼ��͵�һ·����
		{
			x0 = startgoalp.sx;
			y0 = startgoalp.sy;
		}
		else  //��ʾ������ϵ��
		{
			x0 = startgoalp.sx + gpathBest[pointNum].GeneralP.pm * cos(gpathBest[pointNum].GeneralP.pa);
			y0 = startgoalp.sy - gpathBest[pointNum].GeneralP.pm * sin(gpathBest[pointNum].GeneralP.pa);
		}

		//����·����
		if (pointNum == -1)//1.��ʼ��͵�һ·����
		{			
			newPoint = calculateNewpoint.calculate_newpoint(x0, y0, docalNUM[z].xChange, docalNUM[z].yChange, Vso, pa_v, Vusv);
			temppm = gpathBest[0].AdditionS.pm = sqrt(pow((float)abs(startgoalp.sx - newPoint.x), 2) + pow((float)abs(startgoalp.sy - newPoint.y), 2));
			if (temppm <= docalNUM[z].pm)
			{
				gpathBest[0].AdditionS.pm = temppm;
				gpathBest[0].AdditionS.pa = calculate_PA.calculate_PolarAngle(newPoint.x, newPoint.y);
			}
			else
			{
				x0 = x0 - startgoalp.sx;
				y0 = startgoalp.sy - y0;
				gpathBest[0].AdditionS.pm = docalNUM[z].pm;
				gpathBest[0].AdditionS.pa = tempParticleDO.calculate_newpointPA(x0, y0, pa_v, docalNUM[z].pm);
			}	
			gpathBest[0].AdditionS.v = gpathBestDO[z].Vchange + startgoalp.v_kn;
		}
		else
		{
			newPoint = calculateNewpoint.calculate_newpoint(x0, y0, docalNUM[z].xChange, docalNUM[z].yChange, Vso, pa_v, Vusv);
			temppm = sqrt(pow((float)abs(startgoalp.sx - newPoint.x), 2) + pow((float)abs(startgoalp.sy - newPoint.y), 2));
			if (temppm <= docalNUM[z].pm)
			{
				gpathBest[pointNum].AdditionP.pm = temppm;
				gpathBest[pointNum].AdditionP.pa = calculate_PA.calculate_PolarAngle(newPoint.x, newPoint.y);
			}
			else
			{
				x0 = x0 - startgoalp.sx;
				y0 = startgoalp.sy - y0;
				gpathBest[pointNum].AdditionP.pm = docalNUM[z].pm;
				gpathBest[pointNum].AdditionP.pa = tempParticleDO.calculate_newpointPA(x0, y0, pa_v, docalNUM[z].pm);
			}
			gpathBest[pointNum].AdditionP.v = gpathBestDO[z].Vchange + startgoalp.v_kn;
		}

		delete[] particledo;
	}

	DWORD stop = GetTickCount();//��ʱ����
	UsedTimeInMs_DynamicPSO = stop - start;

	ParticleDO GbestFitness_OptimizePATH;
	gbestFitness_DynamicPSO = GbestFitness_OptimizePATH.calculate_DynamicL(gpathBest);
	Invalidate();
}

void USVView::OnCalculateunknown()//δ֪��̬�ϰ������
{
	// TODO:  �ڴ���������������
	allp_un = 0;//���é�������һ���Լӷ���
	
	//���ϰ��ﰴ��������
	calculate_unknownO();

	//�Զ�̬δ֪·����ʼ��
	for (int i = 0; i < 50; i++)
	{
		gpathBest[i].GeneralP.v = startgoalp.v_kn;
		for (int j = 0; j < 200; j++)
		{
			gpathBest[i].AdditionSU[j] = { 0.0 };
			gpathBest[i].AdditionSUa[j] = { 0.0 };
			gpathBest[i].AdditionPU[j] = { 0.0 };
			gpathBest[i].AdditionPUa[j] = { 0.0 };
		}
	}

	int CalNum = unknownO[0].CalNum;//Ҫ�����·������
	int startpoint = 0;//ÿ�ο�ʼ��λ��	
	float R = unknown.UnknownR*drawscale;//��Ұ�뾶
	float T = unknown.UnknownT;//���ϼ��
	float V;//�öε��ٶ�
	float L;//����	
	ParticleDO tempPDO;
	float tempX, tempY, tempX1, tempY1;//, x1, y1
	bool collision=0;
	PolarCoordinate General;//��·���յ�ֵ

	for (int num = 0; num < CalNum; num++)
	{
		//unknown = {0};
		int N = 0;//��������
		int pointNum = -1;//ÿ�ο�ʼ��·����

		if (num == 0)
		{
			startpoint = 0;//ÿ�ο�ʼ��λ��
		}
		else
		{
			startpoint = startpoint + unknownO[startpoint].calnumPATH;//ÿ�ο�ʼ��λ��
		}

		pointNum = unknownO[startpoint].pointNum;//ÿ�ο�ʼ��·����
		
		float tempL;//�ö�·������
		float pa;//�ö�·���Ļ���ֵ
		if (pointNum == -1)
		{
			if (unknownO[startpoint].pointNumBOOL == 0)//�޶�̬���ӵ�
			{
				V = startgoalp.v_kn;
				L = V * T *drawscale * Kn_ms;//����
				if (gpathBest[0].GeneralP.pm==0)//�޾�̬�ϰ���
				{
					tempL = sqrt(pow((float)(startgoalp.gx - startgoalp.sx), 2) + pow((float)(startgoalp.gy - startgoalp.sy), 2));
					General.pm = tempL;
					General.pa = 0.0;
				}
				else
				{
					tempL = gpathBest[0].GeneralP.pm;
					General.pm = gpathBest[0].GeneralP.pm;
					General.pa = gpathBest[0].GeneralP.pa;
				}				

				for (int N = 0; N * L <= tempL; N++)
				{
					pa = gpathBest[0].GeneralP.pa;
					unknown.x0 = startgoalp.sx + N * L * cos(pa);
					unknown.y0 = startgoalp.sy - N * L * sin(pa);
					unknown.max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(pa - pi / 2);
				
					//�ж��Ƿ�����
					collision = judge_collision(startpoint, L);
					if (collision)
					{
						//����ײ�ǵ������ֵ����·������
						gpathBest[0].AdditionSU[0].pm = sqrt(pow(((float)startgoalp.sx - unknown.x0), 2) - pow(((float)startgoalp.sy - unknown.y0), 2));
						gpathBest[0].AdditionSU[0].pa = tempPDO.calculate_2point_pa(startgoalp.sx, startgoalp.sy, unknown.x0, unknown.y0);
						break;
					}
				}

				//�������������δ֪·������
				if (collision)
				{
					calculate_collision(startpoint, L, gpathBest[0].AdditionSU, General);
				}

			}
			else if (unknownO[startpoint].pointNumBOOL == -1)//�ж�̬���ӵ�,��ǰ��
			{
				V = gpathBest[0].AdditionS.v;
				L = V * T *drawscale * Kn_ms;//����
				tempL = gpathBest[0].AdditionS.pm;

				for (int N = 0; N * L <= tempL; N++)
				{
					pa = gpathBest[0].AdditionS.pa;
					unknown.x0 = startgoalp.sx + N * L * cos(pa);
					unknown.y0 = startgoalp.sy - N * L * sin(pa);
					unknown.max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(pa - pi / 2);

					//�ж��Ƿ�����
					collision = judge_collision(startpoint, L);
					if (collision)
					{
						//����ײ�ǵ������ֵ����·������
						gpathBest[0].AdditionSU[0].pm = sqrt(pow(((float)startgoalp.sx - unknown.x0), 2) - pow(((float)startgoalp.sy - unknown.y0), 2));
						gpathBest[0].AdditionSU[0].pa = tempPDO.calculate_2point_pa(startgoalp.sx, startgoalp.sy, unknown.x0, unknown.y0);
						break;
					}
				}

				//�������������δ֪·������
				if (collision)
				{
					calculate_collision(startpoint, L, gpathBest[0].AdditionSU, gpathBest[0].AdditionS);
				}
			}
			else if (unknownO[startpoint].pointNumBOOL == 1)//�ж�̬���ӵ�,�ں��
			{
				V = startgoalp.v_kn;
				L = V * T *drawscale * Kn_ms;//����

				tempL = sqrt(pow(gpathBest[0].AdditionS.pm, 2) + pow(gpathBest[0].GeneralP.pm, 2)
					- 2 * gpathBest[0].AdditionS.pm*gpathBest[0].GeneralP.pm*cos(gpathBest[0].AdditionS.pa - gpathBest[0].GeneralP.pa));
				
				tempX = startgoalp.sx + gpathBest[0].AdditionS.pm * cos(gpathBest[0].AdditionS.pa);
				tempY = startgoalp.sy - gpathBest[0].AdditionS.pm * sin(gpathBest[0].AdditionS.pa);
				tempX1 = startgoalp.sx + gpathBest[0].GeneralP.pm * cos(gpathBest[0].GeneralP.pa);
				tempY1 = startgoalp.sy - gpathBest[0].GeneralP.pm * sin(gpathBest[0].GeneralP.pa);
				pa = tempPDO.calculate_2point_pa(tempX, tempY, tempX1, tempY1);
				
				for (int N = 0; N * L <= tempL; N++)
				{					
					unknown.x0 = tempX + N * L * cos(pa);
					unknown.y0 = tempY - N * L * sin(pa);
					unknown.max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(pa - pi / 2);

					//�ж��Ƿ�����
					collision = judge_collision(startpoint, L);
					if (collision)
					{
						//����ײ�ǵ������ֵ����·������
						gpathBest[0].AdditionSUa[0].pm = sqrt(pow(((float)startgoalp.sx - unknown.x0), 2) - pow(((float)startgoalp.sy - unknown.y0), 2));
						gpathBest[0].AdditionSUa[0].pa = tempPDO.calculate_2point_pa(startgoalp.sx, startgoalp.sy, unknown.x0, unknown.y0);
						break;
					}
				}

				//�������������δ֪·������
				if (collision)
				{
					calculate_collision(startpoint, L, gpathBest[0].AdditionSUa, gpathBest[0].GeneralP);
				}
			}			
		}
		else
		{
			if (unknownO[startpoint].pointNumBOOL == 0)//�޶�̬���ӵ�
			{
				V = gpathBest[pointNum].GeneralP.v;
				L = V * T *drawscale * Kn_ms;//����

				tempL = sqrt(pow(gpathBest[pointNum].GeneralP.pm, 2) + pow(gpathBest[pointNum + 1].GeneralP.pm, 2)
					- 2 * gpathBest[pointNum].GeneralP.pm*gpathBest[pointNum + 1].GeneralP.pm*cos(gpathBest[pointNum + 1].GeneralP.pa - gpathBest[pointNum].GeneralP.pa));

				tempX = startgoalp.sx + gpathBest[pointNum].GeneralP.pm * cos(gpathBest[pointNum].GeneralP.pa);
				tempY = startgoalp.sy - gpathBest[pointNum].GeneralP.pm * sin(gpathBest[pointNum].GeneralP.pa);
				if (pointNum!=(allp-1))
				{
					tempX1 = startgoalp.sx + gpathBest[pointNum + 1].GeneralP.pm * cos(gpathBest[pointNum + 1].GeneralP.pa);
					tempY1 = startgoalp.sy - gpathBest[pointNum + 1].GeneralP.pm * sin(gpathBest[pointNum + 1].GeneralP.pa);
				}
				else
				{
					tempX1 = startgoalp.gx;
					tempY1 = startgoalp.gy;
				}

				pa = tempPDO.calculate_2point_pa(tempX, tempY, tempX1, tempY1);

				for (int N = 0; N * L <= tempL; N++)
				{
					unknown.x0 = tempX + N * L * cos(pa);
					unknown.y0 = tempY - N * L * sin(pa);
					unknown.max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(pa - pi / 2);

					//�ж��Ƿ�����
					collision = judge_collision(startpoint, L);
					if (collision)
					{
						//����ײ�ǵ������ֵ����·������
						gpathBest[pointNum].AdditionPU[0].pm = sqrt(pow(((float)startgoalp.sx - unknown.x0), 2) - pow(((float)startgoalp.sy - unknown.y0), 2));
						gpathBest[pointNum].AdditionPU[0].pa = tempPDO.calculate_2point_pa(startgoalp.sx, startgoalp.sy, unknown.x0, unknown.y0);
						break;
					}
				}

				//�������������δ֪·������
				if (collision)
				{
					calculate_collision(startpoint, L, gpathBest[pointNum].AdditionPU, gpathBest[pointNum + 1].GeneralP);
				}
			}
			else if (unknownO[startpoint].pointNumBOOL == -1)//�ж�̬���ӵ�,��ǰ��
			{
				V = gpathBest[pointNum].AdditionP.v;
				L = V * T *drawscale * Kn_ms;//����

				tempL = sqrt(pow(gpathBest[pointNum].GeneralP.pm, 2) + pow(gpathBest[pointNum].AdditionP.pm, 2)
					- 2 * gpathBest[pointNum].GeneralP.pm*gpathBest[pointNum].AdditionP.pm*cos(gpathBest[pointNum].AdditionP.pa - gpathBest[pointNum].GeneralP.pa));

				tempX = startgoalp.sx + gpathBest[pointNum].GeneralP.pm * cos(gpathBest[pointNum].GeneralP.pa);
				tempY = startgoalp.sy - gpathBest[pointNum].GeneralP.pm * sin(gpathBest[pointNum].GeneralP.pa);
				tempX1 = startgoalp.sx + gpathBest[pointNum].AdditionP.pm * cos(gpathBest[pointNum].AdditionP.pa);
				tempY1 = startgoalp.sy - gpathBest[pointNum].AdditionP.pm * sin(gpathBest[pointNum].AdditionP.pa);
				pa = tempPDO.calculate_2point_pa(tempX, tempY, tempX1, tempY1);

				for (int N = 0; N * L <= tempL; N++)
				{
					unknown.x0 = tempX + N * L * cos(pa);
					unknown.y0 = tempY - N * L * sin(pa);
					unknown.max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(pa - pi / 2);

					//�ж��Ƿ�����
					collision = judge_collision(startpoint, L);
					if (collision)
					{
						//����ײ�ǵ������ֵ����·������
						gpathBest[pointNum].AdditionPU[0].pm = sqrt(pow(((float)startgoalp.sx - unknown.x0), 2) - pow(((float)startgoalp.sy - unknown.y0), 2));
						gpathBest[pointNum].AdditionPU[0].pa = tempPDO.calculate_2point_pa(startgoalp.sx, startgoalp.sy, unknown.x0, unknown.y0);
						break;
					}
				}

				//�������������δ֪·������
				if (collision)
				{
					calculate_collision(startpoint, L, gpathBest[pointNum].AdditionPU, gpathBest[pointNum].AdditionP);
				}
			}
			else if (unknownO[startpoint].pointNumBOOL == 1)//�ж�̬���ӵ�,�ں��
			{
				V = gpathBest[pointNum].GeneralP.v;
				L = V * T *drawscale * Kn_ms;//����

				tempL = sqrt(pow(gpathBest[pointNum+1].GeneralP.pm, 2) + pow(gpathBest[pointNum].AdditionP.pm, 2)
					- 2 * gpathBest[pointNum+1].GeneralP.pm*gpathBest[pointNum].AdditionP.pm*cos(gpathBest[pointNum].AdditionP.pa - gpathBest[pointNum+1].GeneralP.pa));

				tempX = startgoalp.sx + gpathBest[pointNum].AdditionP.pm * cos(gpathBest[pointNum].AdditionP.pa);
				tempY = startgoalp.sy - gpathBest[pointNum].AdditionP.pm * sin(gpathBest[pointNum].AdditionP.pa);
				tempX1 = startgoalp.sx + gpathBest[pointNum + 1].GeneralP.pm * cos(gpathBest[pointNum + 1].GeneralP.pa);
				tempY1 = startgoalp.sy - gpathBest[pointNum + 1].GeneralP.pm * sin(gpathBest[pointNum + 1].GeneralP.pa);
				pa = tempPDO.calculate_2point_pa(tempX, tempY, tempX1, tempY1);

				for (int N = 0; N * L <= tempL; N++)
				{
					unknown.x0 = tempX + N * L * cos(pa);
					unknown.y0 = tempY - N * L * sin(pa);
					unknown.max = tempPDO.calculate_Pa_02PI(pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(pa - pi / 2);

					//�ж��Ƿ�����
					collision = judge_collision(startpoint, L);
					if (collision)
					{
						//����ײ�ǵ������ֵ����·������
						gpathBest[pointNum].AdditionPUa[0].pm = sqrt(pow(((float)startgoalp.sx - unknown.x0), 2) - pow(((float)startgoalp.sy - unknown.y0), 2));
						gpathBest[pointNum].AdditionPUa[0].pa = tempPDO.calculate_2point_pa(startgoalp.sx, startgoalp.sy, unknown.x0, unknown.y0);
						break;
					}
				}

				//�������������δ֪·������
				if (collision)
				{
					calculate_collision(startpoint, L, gpathBest[pointNum].AdditionPUa, gpathBest[pointNum + 1].GeneralP);
				}
			}
		}
	}
	Invalidate();
}

void USVView::calculate_collision(int startpoint, float L, PolarCoordinate *Addition, PolarCoordinate General)//������ı���
{
	int calnumPATH = unknownO[startpoint].calnumPATH;//ÿ��·���ΰ�����̬�ϰ���ĸ���
	float x0,y0,x1, y1,x2,y2,pa,d1,d2,xo2,yo2,d0,pa0,paAdd;//x10,y10,
	float x00, y00, x01, y01;//�ж��Ƿ��뾲̬�ϰ����ཻ
	REC peak[4];
	//point_d s1, e1;//�жϵ��ĸ�����
	int unknownPOINT = 0;//δ֪����·����
	ParticleDO tempPDO;
	PointInRC pointInRC,pointInRC1, pointInRC2;
	SetStaticObstacleRectangle temp;
	int pointNum = unknownO[startpoint].pointNum;//���Ǹ�·���ڵ��
	bool flag=0;//��һ���ж�
	bool flag_collisionDONE=0;//�жϸö������ϰ����Ƿ��ѽ�������
	float D;//���յ�֮��ľ���
	float GX, GY;//�˶��յ����ʾ����ֵ

	if (General.pm==0.0)//�յ�Ϊ��ֹ��
	{
		GX = startgoalp.gx ;
		GY = startgoalp.gy ;
	}
	else
	{
		GX = startgoalp.sx + General.pm * cos(General.pa);
		GY = startgoalp.sy - General.pm * sin(General.pa);
	}

	do
	{
		if (flag==0)
		{
			if (pointNum==-1)
			{
				x0 = startgoalp.sx;
				y0 = startgoalp.sy;
			}
			else
			{
				x0 = startgoalp.sx + gpathBest[pointNum].GeneralP.pm * cos(gpathBest[pointNum].GeneralP.pa);
				y0 = startgoalp.sy - gpathBest[pointNum].GeneralP.pm * sin(gpathBest[pointNum].GeneralP.pa);
			}
			
			x1 = startgoalp.sx + Addition[unknownPOINT].pm * cos(Addition[unknownPOINT].pa);
			y1 = startgoalp.sy - Addition[unknownPOINT].pm * sin(Addition[unknownPOINT].pa);
			pa = tempPDO.calculate_2point_pa(x0, y0, x1, y1);
			flag++;
		}
		else
		{
			pa = Addition[unknownPOINT].pa;
		}
						
		//��һ��������USV·����
		x1 = unknown.x0 + L * cos(pa);
		y1 = unknown.y0 - L * sin(pa);
		//������������USV·����
		x2 = unknown.x0 + 2 * L * cos(pa);
		y2 = unknown.y0 - 2 * L * sin(pa);

		int paNUM = 0;//δ֪�ϰ������߽Ƕ� ����

		for (int i = startpoint; i < (startpoint + calnumPATH); i++)
		{
			if (unknownO[i].collisionDONE == 0)//���ϰ���δ�����ײ
			{
				if (unknownO[i].collision == 1)//���ϰ�������
				{
					if (unknownO[i].form == 1)//Բ���ϰ���
					{
						d1 = sqrt(pow((x1 - unknownO[i].xEX), 2) + pow((y1 - unknownO[i].yEX), 2));
						xo2 = unknownO[i].xEX + L * cos(unknownO[i].Da*pi / 180);
						yo2 = unknownO[i].yEX - L * sin(unknownO[i].Da*pi / 180);
						d2 = sqrt(pow((x2 - xo2), 2) + pow((y2 - yo2), 2));

						if (d1 <= (unknownO[i].rEX / 2))//����һ���������� Σ��״̬
						{
							d0 = sqrt(pow((unknown.x0 - unknownO[i].xEX), 2) + pow((unknown.y0 - unknownO[i].yEX), 2));
							pa0 = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, unknownO[i].xEX, unknownO[i].yEX);//�ϰ���Բ�ĺ�·����ļ���ֵ
							if ((unknownO[i].rEX / 2 / d0)>1.0)//��ʱ·�������ϰ�Բ��
							{
								if ((0.0 <= pa) && (pa <= pi))
								{
									if ((0.0 <= pa0) && (pa0 <= pi))
									{
										if (pa>=pa0)
											paAdd = 45 * pi / 180;
										else
											paAdd = -45 * pi / 180;
									}
									else
									{
										paAdd = 45 * pi / 180;
									}
								}
								else
								{
									if ((pi <= pa0) && (pa0 < 2*pi))
									{
										if (pa >= pa0)
											paAdd = 45 * pi / 180;
										else
											paAdd = -45 * pi / 180;
									}
									else
									{
										paAdd = -45 * pi / 180;
									}
								}
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//min
							}
							else
							{
								paAdd = asin(unknownO[i].rEX / 2 / d0);//������
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(pa0 + abs(paAdd));//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(pa0 - abs(paAdd));//min
							}

							paNUM = paNUM + 2;
						}
						else if (d2 <= (unknownO[i].rEX / 2))//�������������������ϰ�����,���� ׼Σ��״̬
						{
							d0 = sqrt(pow((unknown.x0 - xo2), 2) + pow((unknown.y0 - yo2), 2));
							pa0 = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, xo2, yo2);//�ϰ���Բ�ĺ�·����ļ���ֵ
							if ((unknownO[i].rEX / 2 / d0)>1.0)//��ʱ·�������ϰ�Բ��
							{
								if ((0.0 <= pa) && (pa <= pi))
								{
									if ((0.0 <= pa0) && (pa0 <= pi))
									{
										if (pa >= pa0)
											paAdd = 45 * pi / 180;
										else
											paAdd = -45 * pi / 180;
									}
									else
									{
										paAdd = 45 * pi / 180;
									}
								}
								else
								{
									if ((pi <= pa0) && (pa0 < 2 * pi))
									{
										if (pa >= pa0)
											paAdd = 45 * pi / 180;
										else
											paAdd = -45 * pi / 180;
									}
									else
									{
										paAdd = -45 * pi / 180;
									}
								}
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//min
							}
							else
							{
								paAdd = asin(unknownO[i].rEX / 2 / d0);//������
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(pa0 + abs(paAdd));//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(pa0 - abs(paAdd));//min
							}

							paNUM = paNUM + 2;
						}
						else//������һ�����������������������ϰ�����,���� ��ȫ״̬
						{
							unknownPA[paNUM] = pa;//max
							unknownPA[paNUM + 1] = pa;//min

							paNUM = paNUM + 2;
						}
						//�������ϰ�Բ����һ����ֵ
						unknownO[i].xEX = xo2;
						unknownO[i].yEX = yo2;
					}
					else if (unknownO[i].form == 2)//�����ϰ���
					{
						//�����������ڷ����ϰ��ﶥ��
						peak[0].xEX = unknownO[i].Peak[0].xEX + L * cos(unknownO[i].Da*pi / 180);
						peak[0].yEX = unknownO[i].Peak[0].yEX - L * sin(unknownO[i].Da*pi / 180);
						peak[1].xEX = unknownO[i].Peak[1].xEX + L * cos(unknownO[i].Da*pi / 180);
						peak[1].yEX = unknownO[i].Peak[1].yEX - L * sin(unknownO[i].Da*pi / 180);
						peak[2].xEX = unknownO[i].Peak[2].xEX + L * cos(unknownO[i].Da*pi / 180);
						peak[2].yEX = unknownO[i].Peak[2].yEX - L * sin(unknownO[i].Da*pi / 180);
						peak[3].xEX = unknownO[i].Peak[3].xEX + L * cos(unknownO[i].Da*pi / 180);
						peak[3].yEX = unknownO[i].Peak[3].yEX - L * sin(unknownO[i].Da*pi / 180);

						pointInRC1 = temp.calculate_pointInRC(unknownO[i].Peak[0], unknownO[i].Peak[1], unknownO[i].Peak[2], unknownO[i].Peak[3], x1, y1);
						pointInRC2 = temp.calculate_pointInRC(peak[0], peak[1], peak[2], peak[3], x2, y2);

						if (pointInRC1.point == 5)//����һ�������������ϰ�����,���� Σ��״̬
						{
							pointInRC = temp.calculate_pointInRC(unknownO[i].Peak[0], unknownO[i].Peak[1], unknownO[i].Peak[2], unknownO[i].Peak[3], unknown.x0, unknown.y0);
							if (pointInRC.point == 5)//��ʱ·�������ϰ�������
							{
								pa0 = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, unknownor[unknownO[i].num].CenterX, unknownor[unknownO[i].num].CenterY);//�ϰ���Բ�ĺ�·����ļ���ֵ
								if ((0.0 <= pa) && (pa <= pi))
								{
									if ((0.0 <= pa0) && (pa0 <= pi))
									{
										if (pa >= pa0)
											paAdd = 20 * pi / 180;
										else
											paAdd = -20 * pi / 180;
									}
									else
									{
										paAdd = 20 * pi / 180;
									}
								}
								else
								{
									if ((pi <= pa0) && (pa0 < 2 * pi))
									{
										if (pa >= pa0)
											paAdd = 20 * pi / 180;
										else
											paAdd = -20 * pi / 180;
									}
									else
									{
										paAdd = -20 * pi / 180;
									}
								}
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//min
							}
							else
							{
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, unknownO[i].Peak[pointInRC.max].xEX, unknownO[i].Peak[pointInRC.max].yEX));//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, unknownO[i].Peak[pointInRC.min].xEX, unknownO[i].Peak[pointInRC.min].yEX));//min
							}

							paNUM = paNUM + 2;
						}
						else if ( pointInRC2.point == 5)//�������������������ϰ�����,���� ׼Σ��״̬
						{
							pointInRC = temp.calculate_pointInRC(peak[0], peak[1], peak[2], peak[3], unknown.x0, unknown.y0);
							if (pointInRC.point == 5)//��ʱ·�������ϰ�������
							{
								pa0 = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, (unknownor[unknownO[i].num].CenterX + L * cos(unknownO[i].Da*pi / 180)), (unknownor[unknownO[i].num].CenterY - L * sin(unknownO[i].Da*pi / 180)));//�ϰ���Բ�ĺ�·����ļ���ֵ
								if ((0.0 <= pa) && (pa <= pi))
								{
									if ((0.0 <= pa0) && (pa0 <= pi))
									{
										if (pa >= pa0)
											paAdd = 20 * pi / 180;
										else
											paAdd = -20 * pi / 180;
									}
									else
									{
										paAdd = 20 * pi / 180;
									}
								}
								else
								{
									if ((pi <= pa0) && (pa0 < 2 * pi))
									{
										if (pa >= pa0)
											paAdd = 20 * pi / 180;
										else
											paAdd = -20 * pi / 180;
									}
									else
									{
										paAdd = -20 * pi / 180;
									}
								}
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(pa0 + paAdd);//min
							}
							else
							{
								unknownPA[paNUM] = tempPDO.calculate_Pa_02PI(tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, peak[pointInRC.max].xEX, peak[pointInRC.max].yEX));//max
								unknownPA[paNUM + 1] = tempPDO.calculate_Pa_02PI(tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, peak[pointInRC.min].xEX, peak[pointInRC.min].yEX));//min
							}

							paNUM = paNUM + 2;
						}
						else//������һ�����������������������ϰ�����,���� ��ȫ״̬
						{
							unknownPA[paNUM] = pa;//max
							unknownPA[paNUM + 1] = pa;//min

							paNUM = paNUM + 2;
						}
						//�������ϰ�Բ����һ����ֵ
						unknownO[i].Peak[0].xEX = peak[0].xEX;
						unknownO[i].Peak[0].yEX = peak[0].yEX;
						unknownO[i].Peak[1].xEX = peak[1].xEX;
						unknownO[i].Peak[1].yEX = peak[1].yEX;
						unknownO[i].Peak[2].xEX = peak[2].xEX;
						unknownO[i].Peak[2].yEX = peak[2].yEX;
						unknownO[i].Peak[3].xEX = peak[3].xEX;
						unknownO[i].Peak[3].yEX = peak[3].yEX;
					}
				}
			}						
		}//�����ѻ�ñ��ϽǶ�����

		//�Ա��ϽǶ������ж��Ƿ��뾲̬�ϰ����ཻ�����ཻ��ȥ
		float tempUnPA[30]{};//δ֪�ϰ������߽Ƕ�
		int tempNUM = 0;

		for (int i = 0; i < paNUM; i++)
		{
			x00 = unknown.x0;
			y00 = unknown.y0;
			x01 = unknown.x0 + L * cos(unknownPA[i] * pi / 180);
			y01 = unknown.y0 - L * sin(unknownPA[i] * pi / 180);
			if (!judge_so_collision(x00, y00, x01, y01, pointNum))
			{
				tempUnPA[tempNUM] = unknownPA[i];
				tempNUM++;
			}
		}

		//�Կ��б��ϽǶ����鰴�Ƕȸı�������С��������
		for (int j = 0; j < tempNUM - 1; j++)
		{
			float pa1, pa2;
			for (int i = 0; i < tempNUM - 1 - j; i++)
			{
				float temp;
				pa1 = abs(tempUnPA[i] - pa);
				pa2 = abs(tempUnPA[i + 1] - pa);
				if (pa1>pi)
					pa1 = abs(pa1 - 2*pi);
				if (pa2>pi)
					pa2 = abs(pa2 - 2*pi);
				
				if (pa1>pa2)
				{
					temp = tempUnPA[i];
					tempUnPA[i] = tempUnPA[i + 1];
					tempUnPA[i + 1] = temp;
				}
			}
		}

		//�Կ��б��ϽǶ�����ȡ��Сֵ,���жϽǶ��Ƿ������unknownPA[paNUM]��max min �Ƚϣ�
		bool flagTEMP=0;
		for (int j = 0; j < tempNUM; j++)
		{
			for (int i = 0; i < paNUM; i=i+2)
			{
				if (unknownPA[i] >= unknownPA[i+1])
				{
					if (!((unknownPA[i + 1] < tempUnPA[j]) && (tempUnPA[j] < unknownPA[i])))
					{
						Addition[unknownPOINT + 1].pa = tempUnPA[j];
						Addition[unknownPOINT + 1].pm = 1.0;//�����б����ֵ��û��ʵ������

						unknown.x0 = unknown.x0 + L * cos(tempUnPA[j]);
						unknown.y0 = unknown.y0 - L * sin(tempUnPA[j]);
						unknown.max = tempPDO.calculate_Pa_02PI(tempUnPA[j] + pi / 2);
						unknown.min = tempPDO.calculate_Pa_02PI(tempUnPA[j] - pi / 2);

						flagTEMP = 1;
						break;
					}
				}
				else
				{
					if (!(((unknownPA[i + 1] < tempUnPA[j]) && (tempUnPA[j] < 2*pi)) || ((0 <= tempUnPA[j]) && (tempUnPA[j] < unknownPA[i]))))
					{
						Addition[unknownPOINT + 1].pa = tempUnPA[j];
						Addition[unknownPOINT + 1].pm = 1.0;//�����б����ֵ��û��ʵ������

						unknown.x0 = unknown.x0 + L * cos(tempUnPA[j]);
						unknown.y0 = unknown.y0 - L * sin(tempUnPA[j]);
						unknown.max = tempPDO.calculate_Pa_02PI(tempUnPA[j] + pi / 2);
						unknown.min = tempPDO.calculate_Pa_02PI(tempUnPA[j] - pi / 2);

						flagTEMP = 1;
						break;
					}
				}
			}
			if (flagTEMP == 1)
			{
				break;
			}
		}
		if (abs(Addition[unknownPOINT + 1].pa-pa)<(10*pi/180))//���ı�Ƕ�С��10�ȣ���ת��
		{
			Addition[unknownPOINT + 1].pa = pa;
		}
		unknownPOINT++;
		
		D = sqrt(pow((unknown.x0 - GX), 2) + pow((unknown.y0 - GY), 2));//���յ��·��

		if ((!(judge_collision(startpoint, L))) && (D >= L))
		{
			for (int z = startpoint; z < (startpoint + calnumPATH); z++)
			{
				if (unknownO[z].form==1)//Բ
				{
					if (unknownO[z].xEX != unknownoc[unknownO[z].num].xEX)//���ϰ�������
					{
						unknownO[z].collisionDONE = 1;//���ϰ����������ײ
					}
				}
				else if (unknownO[z].form == 2)//����
				{
					if (unknownO[z].Peak[0].xEX != unknownor[unknownO[z].num].Peak[0].xEX)//���ϰ�������
					{
						unknownO[z].collisionDONE = 1;//���ϰ����������ײ
					}
				}				
			}

			//������ǰ�н�һ������
			if (((20 * pi / 180) <= Addition[unknownPOINT].pa) && (Addition[unknownPOINT].pa <= pi))
			{
				paAdd = -20 * pi / 180;
			}
			else if ((pi < Addition[unknownPOINT].pa) && (Addition[unknownPOINT].pa <= (340 * pi / 180)))
			{
				paAdd = 20 * pi / 180;
			}
			Addition[unknownPOINT + 1].pa = Addition[unknownPOINT].pa + paAdd;
			Addition[unknownPOINT + 1].pm = 1.0;//�����б����ֵ��û��ʵ������
			unknownPOINT++;

			for (int N = 0; (D >= (3 * L)) && (!flag_collisionDONE); N++)
			{
				float tempPA;
				if (N==0)//�뱾���յ�ĸ�ֵ
				{
					tempPA = tempPDO.calculate_Pa_02PI(tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, GX, GY));//�뱾���յ�ĸ�ֵ
					unknown.max = tempPDO.calculate_Pa_02PI(tempPA + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(tempPA - pi / 2);

					//�ж��Ƿ�����
					if (judge_collision(startpoint, L))
						break;

					Addition[unknownPOINT + 1].pa = tempPA;
					Addition[unknownPOINT + 1].pm = 1.0;//�����б����ֵ��û��ʵ������
				}
				else
				{
					unknown.x0 = unknown.x0 + L * cos(Addition[unknownPOINT].pa);
					unknown.y0 = unknown.y0 - L * sin(Addition[unknownPOINT].pa);
					unknown.max = tempPDO.calculate_Pa_02PI(Addition[unknownPOINT].pa + pi / 2);
					unknown.min = tempPDO.calculate_Pa_02PI(Addition[unknownPOINT].pa - pi / 2);

					//�ж��Ƿ�����
					if (judge_collision(startpoint, L))
						break;

					Addition[unknownPOINT + 1].pa = Addition[unknownPOINT].pa;
					Addition[unknownPOINT + 1].pm = 1.0;//�����б����ֵ��û��ʵ������
				}

				D = sqrt(pow((unknown.x0 - GX), 2) + pow((unknown.y0 - GY), 2));//���յ��·��
				unknownPOINT++;

				//���ö��ϰ��ﶼ�Ѿ����Ͻ����������ѭ������
				flag_collisionDONE = 1;
				for (int i = startpoint; i < (startpoint + calnumPATH); i++)
				{
					if (unknownO[i].collisionDONE == 0)//���ϰ���δ�����ײ
					{
						flag_collisionDONE = 0;
						break;
					}
				}
			}

		}
		
	} while (D >= (3 * L) && (!flag_collisionDONE));
}

bool USVView::judge_so_collision(float x0, float y0, float x1, float y1, int pointNum)//�ж��Ƿ�;�̬�ϰ�������
{
	//��ʾ������
	ParticleDO temp;
	float tempY, Xobs_t, Yobs_t, k;//, temppm, Ab
	bool flag=0;

	for (int m = 0; m < allp; m++)
	{
		int j = SObsticle_num[m].num;
		if (SObsticle_num[m].form == 1)//Բ�ξ�̬�ϰ���
		{
			//���1��Բ�����߲���·���ཻ�����ϰ�Բ���·��
			if ((x0 - x1) == 0)//����kΪ����󣬼�·����ֱ��x�ᣬ����С
			{
				tempY = abs(x0 - staticoc[j].x);//�ϰ�Բ����·��֮��ľ���

				//·���㴦��ֱ������ϵֵ
				Xobs_t = x0;
				Yobs_t = staticoc[j].y;
			}
			else
			{
				k = (y0 - y1) / (x0 - x1);
				tempY = abs((k* staticoc[j].x - staticoc[j].y + y0 - k*x0) / sqrt(pow(k, 2) + 1.0));//�ϰ�Բ����·��֮��ľ���

				//·���㴦��ֱ������ϵֵ
				Xobs_t = (staticoc[j].x + k * staticoc[j].y + k * (k*x0 - y0)) / (1 + k*k);
				Yobs_t = k*(Xobs_t - x0) + y0;
			}

			if (tempY < (staticoc[j].r / 2 + safe_expandT)) //���ϰ�Բ�ཻ
			{
				//�ϰ���������ֱ�ߵĽ����ֱ������ϵֵ
				flag = temp.calculate_1pointIN2point(x0, y0, x1, y1, Xobs_t, Xobs_t);//�ϰ�Բ���������յ�֮��
				if (flag == 1)
				{
					break;
				}
			}

			//���2��Բ�����߲���·���ཻ�����ϰ�Բ��·��ֻ��һ������
			float tempPM, tempPA;
			tempPM = sqrt(pow((float)abs((float)startgoalp.sx - x1), 2) + pow((float)abs((float)startgoalp.sy - y1), 2));
			tempPA = temp.calculate_2point_pa((float)startgoalp.sx, (float)startgoalp.sy, x1, y1);
		
			if ((pow(staticoc[j].pm, 2) + pow(tempPM, 2) - 2 * staticoc[j].pm*tempPM*cos(abs(staticoc[j].pa - tempPA)))
				<= pow((float)(staticoc[j].r / 2 + safe_expandT), 2))
			{
				flag = 1;
				break;
			}

			/*if (pointNum == -1)
			{
				if ((pow(staticoc[j].pm, 2) + pow(tempPM, 2) - 2 * staticoc[j].pm*tempPM*cos(abs(staticoc[j].pa - tempPA)))
					<= pow((float)(staticoc[j].r / 2 + safe_expandT), 2))
				{
					flag = 1;
					break;
				}
			}
			else
			{
				if ((pow(staticoc[j].pm, 2) + pow(tempPM, 2) - 2 * staticoc[j].pm*tempPM*cos(abs(staticoc[j].pa - tempPA)))
					<= pow((float)(staticoc[j].r / 2 + safe_expandT), 2))
				{
					flag = 1;
					break;
				}
			}*/

		}
		else if (SObsticle_num[m].form == 2)//���ξ�̬�ϰ���
		{
			//·����ת��Ϊ��ʾ����ϵ�¼���
			point_d s1, e1;//�жϵ��ĸ�����

			s1.x = x0;
			s1.y = y0;
			e1.x = x1;
			e1.y = y1;

			if (IsLineIntersectRect(s1, e1, staticor[j].Peak[0], staticor[j].Peak[1], staticor[j].Peak[2], staticor[j].Peak[3]))//�����ϰ���
			{
				flag = 1;
				break;
			}
		}
	}
	return flag;
}

bool USVView::judge_collision(int startpoint,float L)//�ж��Ƿ�����
{
	bool collision=0;
	//int pointNum = unknownO[startpoint].pointNum;//���ĸ�·���ڵ��
	int calnumPATH = unknownO[startpoint].calnumPATH;//ÿ��·���ΰ�����̬�ϰ���ĸ���
	float R = unknown.UnknownR*drawscale;//��Ұ�뾶
	float pa;
	ParticleDO tempPDO;

	float d;//Բ�ľ���

	//��unknownO[i].collision���г�ʼ��
	for (int i = startpoint; i < (startpoint+calnumPATH); i++)
	{
		unknownO[i].collision = 0;
	}

	for (int i = startpoint; i < (startpoint + calnumPATH); i++)
	{
		if (unknownO[i].collisionDONE == 0)//���ϰ���δ�����ײ
		{
			if (unknownO[i].form == 1)//Բ���ϰ���
			{
				d = sqrt(pow((unknown.x0 - unknownO[i].xEX), 2) + pow((unknown.y0 - unknownO[i].yEX), 2));
				if (d <= (unknown.UnknownR*drawscale + unknownO[i].rEX / 2))
				{
					pa = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, unknownO[i].xEX, unknownO[i].yEX);
					if (unknown.max >= unknown.min)
					{
						if ((unknown.min <= pa) && (pa <= unknown.max))
						{
							unknownO[i].collision = 1;//�Ը��ϰ��︳ֵ����
							collision = 1;
						}
					}
					else if (unknown.max<unknown.min)
					{
						if (((unknown.min <= pa) && (pa <= 2 * pi)) || ((0 <= pa) && (pa <= unknown.max)))
						{
							unknownO[i].collision = 1;//�Ը��ϰ��︳ֵ����
							collision = 1;
						}
					}
				}

			}
			else if (unknownO[i].form == 2)//�����ϰ���
			{
				SetStaticObstacleRectangle temp;
				PointInRC pointInRC;
				pointInRC = temp.calculate_pointInRC(unknownO[i].Peak[0], unknownO[i].Peak[1], unknownO[i].Peak[2], unknownO[i].Peak[3], unknown.x0, unknown.y0);
				if (pointInRC.point<5)
				{
					d = sqrt(pow((unknown.x0 - unknownO[i].Peak[pointInRC.point].xEX), 2) + pow((unknown.y0 - unknownO[i].Peak[pointInRC.point].yEX), 2));
					pa = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, unknownO[i].Peak[pointInRC.point].xEX, unknownO[i].Peak[pointInRC.point].yEX);
				}
				else
				{
					float k, x0, y0;
					k = (unknownO[i].Peak[pointInRC.max].yEX - unknownO[i].Peak[pointInRC.min].yEX) / (unknownO[i].Peak[pointInRC.max].xEX - unknownO[i].Peak[pointInRC.min].xEX);
					x0 = (unknown.x0 + k*unknown.y0 + k*(k*unknownO[i].Peak[pointInRC.max].xEX - unknownO[i].Peak[pointInRC.max].yEX)) / (1 + k*k);
					y0 = k*(x0 - unknownO[i].Peak[pointInRC.max].xEX) + unknownO[i].Peak[pointInRC.max].yEX;

					d = sqrt(pow((unknown.x0 - x0), 2) + pow((unknown.y0 - y0), 2));
					pa = tempPDO.calculate_2point_pa(unknown.x0, unknown.y0, x0, y0);
				}

				if (d <= unknown.UnknownR*drawscale)
				{
					if (unknown.max >= unknown.min)
					{
						if ((unknown.min <= pa) && (pa <= unknown.max))
						{
							unknownO[i].collision = 1;//�Ը��ϰ��︳ֵ����
							collision = 1;
						}
					}
					else if (unknown.max < unknown.min)
					{
						if (((unknown.min <= pa) && (pa <= 2 * pi)) || ((0 <= pa) && (pa <= unknown.max)))
						{
							unknownO[i].collision = 1;//�Ը��ϰ��︳ֵ����
							collision = 1;
						}
					}
				}
			}
		}	

	}

	return collision;
}

void USVView::calculate_unknownO()//���ϰ��ﰴ��������
{
	//ÿ����һ�γ�ʼ��һ��
	for (int i = 0; i < 30; i++)
	{
		unknownO[i].Da = 0.0;
		unknownO[i].form = 0;
		unknownO[i].pointNum = -1;
		unknownO[i].pointNumBOOL = 0;
		unknownO[i].rEX = 0.0;
		unknownO[i].t = 0;
		unknownO[i].CalNum = 0;
		unknownO[i].calnumPATH = 0;
		unknownO[i].V = 0.0;
		unknownO[i].pm = 0.0;
		unknownO[i].xEX = 0.0;
		unknownO[i].yEX = 0.0;
		unknownO[i].num = -1;
		unknownO[i].Peak[0] = { 0.0 };
		unknownO[i].Peak[1] = { 0.0 };
		unknownO[i].Peak[2] = { 0.0 };
		unknownO[i].Peak[3] = { 0.0 };
		unknownO[i].collision = 0;
		unknownO[i].collisionDONE = 0;
	}

	//����̬Բ���ϰ������Ϣ����δ֪�ϰ�������
	float sgPM = sqrt(pow((float)abs(int(startgoalp.sx - startgoalp.gx)), 2) + pow((float)abs(int(startgoalp.sy - startgoalp.gy)), 2));//��ʼ�����
	for (int i = 0; unknownoc[i].r != 0; i++)//GDI����ϵ
	{
		allp_un++;

		unknownO[i].form=1;
		unknownO[i].pm = unknownoc[i].pmEX;
		unknownO[i].Da = unknownoc[i].Da;
		unknownO[i].V = unknownoc[i].V;
		unknownO[i].xEX = unknownoc[i].xEX;
		unknownO[i].yEX = unknownoc[i].yEX;
		unknownO[i].rEX = unknownoc[i].rEX;
		unknownO[i].num = i;
		unknownO[i].t = 0;
		
		if ((SObsticle_num[0].form != 1) && (SObsticle_num[0].form != 2))//û�о�̬�ϰ��ȫ��pointNum = -1
		{
			unknownO[i].pointNum = -1;
			if (gpathBest[0].AdditionS.pm!=0)
			{
				if (unknownoc[i].pmEX < gpathBest[0].AdditionS.pm)
				{
					unknownO[i].pointNumBOOL = -1;
				}
				else
				{
					unknownO[i].pointNumBOOL = 1;
				}
			}
		}
		else
		{
			for (int j = 0; SObsticle_num[j].form != 0; j++)
			{
				if (unknownoc[i].pmEX < SObsticle_num[0].pm)
				{
					unknownO[i].pointNum = -1;
					if (gpathBest[0].AdditionS.pm != 0)
					{
						if (unknownoc[i].pmEX < gpathBest[0].AdditionS.pm)
						{
							unknownO[i].pointNumBOOL = -1;
						}
						else
						{
							unknownO[i].pointNumBOOL = 1;
						}
					}
					break;
				}
				else if ((SObsticle_num[j].pm <= unknownoc[i].pmEX) && (unknownoc[i].pmEX < SObsticle_num[j + 1].pm))
				{
					unknownO[i].pointNum = j;
					if (gpathBest[j].AdditionP.pm != 0)
					{
						if (unknownoc[i].pmEX < gpathBest[j].AdditionP.pm)
						{
							unknownO[i].pointNumBOOL = -1;
						}
						else
						{
							unknownO[i].pointNumBOOL = 1;
						}
					}
					break;
				}	
				else if ((SObsticle_num[allp - 1].pm <= unknownoc[i].pmEX) && (unknownoc[i].pmEX < sgPM))
				{
					unknownO[i].pointNum = allp - 1;
					if (gpathBest[allp - 1].AdditionP.pm != 0)
					{
						if (unknownoc[i].pmEX < gpathBest[allp - 1].AdditionP.pm)
						{
							unknownO[i].pointNumBOOL = -1;
						}
						else
						{
							unknownO[i].pointNumBOOL = 1;
						}
					}
					break;
				}
			}
		}
	}

	//����̬�����ϰ������Ϣ����δ֪�ϰ�������
	if (unknownO[0].form == 0)//��û��δ֪Բ���ϰ���
	{
		for (int i = 0; unknownor[i].Peak[0].Pm != 0; i++)//GDI����ϵ
		{
			allp_un++;

			unknownO[i].form = 2;
			unknownO[i].pm = unknownor[i].Peak[0].PmEX;
			unknownO[i].Da = unknownor[i].Da;
			unknownO[i].V = unknownor[i].V;
			unknownO[i].Peak[0] = unknownor[i].Peak[0];
			unknownO[i].Peak[1] = unknownor[i].Peak[1];
			unknownO[i].Peak[2] = unknownor[i].Peak[2];
			unknownO[i].Peak[3] = unknownor[i].Peak[3];
			unknownO[i].num = i;
			unknownO[i].t = 0;

			if ((SObsticle_num[0].form != 1) && (SObsticle_num[0].form != 2))//û�о�̬�ϰ��ȫ��pointNum = -1
			{
				unknownO[i].pointNum = -1;
				if (gpathBest[0].AdditionS.pm != 0)
				{
					if (unknownor[i].Peak[0].PmEX < gpathBest[0].AdditionS.pm)
					{
						unknownO[i].pointNumBOOL = -1;
					}
					else
					{
						unknownO[i].pointNumBOOL = 1;
					}
				}
			}
			else
			{
				for (int j = 0; SObsticle_num[j].form != 0; j++)
				{
					if (unknownor[i].Peak[0].PmEX < SObsticle_num[0].pm)
					{
						unknownO[i].pointNum = -1;
						if (gpathBest[0].AdditionS.pm != 0)
						{
							if (unknownor[i].Peak[0].PmEX < gpathBest[0].AdditionS.pm)
							{
								unknownO[i].pointNumBOOL = -1;
							}
							else
							{
								unknownO[i].pointNumBOOL = 1;
							}
						}
						break;
					}
					else if ((SObsticle_num[j].pm <= unknownor[i].Peak[0].PmEX) && (unknownor[i].Peak[0].PmEX < SObsticle_num[j + 1].pm))
					{
						unknownO[i].pointNum = j;
						if (gpathBest[j].AdditionP.pm != 0)
						{
							if (unknownor[i].Peak[0].PmEX < gpathBest[j].AdditionP.pm)
							{
								unknownO[i].pointNumBOOL = -1;
							}
							else
							{
								unknownO[i].pointNumBOOL = 1;
							}
						}
						break;
					}
					else if ((SObsticle_num[allp - 1].pm <= unknownor[i].Peak[0].PmEX) && (unknownor[i].Peak[0].PmEX < sgPM))
					{
						unknownO[i].pointNum = allp - 1;
						if (gpathBest[allp - 1].AdditionP.pm != 0)
						{
							if (unknownor[i].Peak[0].PmEX < gpathBest[allp - 1].AdditionP.pm)
							{
								unknownO[i].pointNumBOOL = -1;
							}
							else
							{
								unknownO[i].pointNumBOOL = 1;
							}
						}
						break;
					}
				}
			}
		}
	}
	else
	{
		for (int i = 0; unknownor[i].Peak[0].PmEX != 0; i++)//GDI����ϵ
		{
			for (int j = 0; j < allp_un; j++)
			{
				if (unknownor[i].Peak[0].PmEX < unknownO[j].pm)
				{
					for (int m = allp_un; m > j; m--)
					{
						unknownO[m] = unknownO[m - 1];
					}

					unknownO[j].form = 2;
					unknownO[j].pm = unknownor[i].Peak[0].PmEX;
					unknownO[j].Da = unknownor[i].Da;
					unknownO[j].V = unknownor[i].V;
					unknownO[j].Peak[0] = unknownor[i].Peak[0];
					unknownO[j].Peak[1] = unknownor[i].Peak[1];
					unknownO[j].Peak[2] = unknownor[i].Peak[2];
					unknownO[j].Peak[3] = unknownor[i].Peak[3];
					unknownO[j].num = i;
					unknownO[j].t = 0;

					if ((SObsticle_num[0].form != 1) && (SObsticle_num[0].form != 2))//û�о�̬�ϰ��ȫ��pointNum = -1
					{
						unknownO[j].pointNum = -1;
						if (gpathBest[0].AdditionS.pm != 0)
						{
							if (unknownor[i].Peak[0].PmEX < gpathBest[0].AdditionS.pm)
							{
								unknownO[j].pointNumBOOL = -1;
							}
							else
							{
								unknownO[j].pointNumBOOL = 1;
							}
						}
					}
					else
					{
						for (int n = 0; SObsticle_num[n].form != 0; n++)
						{
							if (unknownor[i].Peak[0].PmEX < SObsticle_num[0].pm)
							{
								unknownO[j].pointNum = -1;
								if (gpathBest[0].AdditionS.pm != 0)
								{
									if (unknownor[i].Peak[0].PmEX < gpathBest[0].AdditionS.pm)
									{
										unknownO[j].pointNumBOOL = -1;
									}
									else
									{
										unknownO[j].pointNumBOOL = 1;
									}
								}
								break;
							}
							else if ((SObsticle_num[n].pm <= unknownor[i].Peak[0].PmEX) && (unknownor[i].Peak[0].PmEX < SObsticle_num[n + 1].pm))
							{
								unknownO[j].pointNum = n;
								if (gpathBest[n].AdditionP.pm != 0)
								{
									if (unknownor[i].Peak[0].PmEX < gpathBest[n].AdditionP.pm)
									{
										unknownO[j].pointNumBOOL = -1;
									}
									else
									{
										unknownO[j].pointNumBOOL = 1;
									}
								}
								break;
							}
							else if ((SObsticle_num[allp - 1].pm <= unknownor[i].Peak[0].PmEX) && (unknownor[i].Peak[0].PmEX < sgPM))
							{
								unknownO[j].pointNum = allp - 1;
								if (gpathBest[allp - 1].AdditionP.pm != 0)
								{
									if (unknownor[i].Peak[0].PmEX < gpathBest[allp - 1].AdditionP.pm)
									{
										unknownO[j].pointNumBOOL = -1;
									}
									else
									{
										unknownO[j].pointNumBOOL = 1;
									}
								}
								break;
							}
						}
					}

					allp_un++;
					break;
				}
				else if (j == allp_un - 1)
				{
					unknownO[j+1].form = 2;
					unknownO[j+1].pm = unknownor[i].Peak[0].PmEX;
					unknownO[j+1].Da = unknownor[i].Da;
					unknownO[j+1].V = unknownor[i].V;
					unknownO[j+1].Peak[0] = unknownor[i].Peak[0];
					unknownO[j+1].Peak[1] = unknownor[i].Peak[1];
					unknownO[j+1].Peak[2] = unknownor[i].Peak[2];
					unknownO[j+1].Peak[3] = unknownor[i].Peak[3];
					unknownO[j+1].num = i;
					unknownO[j+1].t = 0;

					if ((SObsticle_num[0].form != 1) && (SObsticle_num[0].form != 2))//û�о�̬�ϰ��ȫ��pointNum = -1
					{
						unknownO[j+1].pointNum = -1;
						if (gpathBest[0].AdditionS.pm != 0)
						{
							if (unknownor[i].Peak[0].PmEX < gpathBest[0].AdditionS.pm)
							{
								unknownO[j+1].pointNumBOOL = -1;
							}
							else
							{
								unknownO[j+1].pointNumBOOL = 1;
							}
						}
					}
					else
					{
						for (int n = 0; SObsticle_num[n].form != 0; n++)
						{
							if (unknownor[i].Peak[0].PmEX < SObsticle_num[0].pm)
							{
								unknownO[j+1].pointNum = -1;
								if (gpathBest[0].AdditionS.pm != 0)
								{
									if (unknownor[i].Peak[0].PmEX < gpathBest[0].AdditionS.pm)
									{
										unknownO[j+1].pointNumBOOL = -1;
									}
									else
									{
										unknownO[j+1].pointNumBOOL = 1;
									}
								}
								break;
							}
							else if ((SObsticle_num[n].pm <= unknownor[i].Peak[0].PmEX) && (unknownor[i].Peak[0].PmEX < SObsticle_num[n + 1].pm))
							{
								unknownO[j+1].pointNum = n;
								if (gpathBest[n].AdditionP.pm != 0)
								{
									if (unknownor[i].Peak[0].PmEX < gpathBest[n].AdditionP.pm)
									{
										unknownO[j+1].pointNumBOOL = -1;
									}
									else
									{
										unknownO[j+1].pointNumBOOL = 1;
									}
								}
								break;
							}
							else if ((SObsticle_num[allp - 1].pm <= unknownor[i].Peak[0].PmEX) && (unknownor[i].Peak[0].PmEX < sgPM))
							{
								unknownO[j+1].pointNum = allp - 1;
								if (gpathBest[allp - 1].AdditionP.pm != 0)
								{
									if (unknownor[i].Peak[0].PmEX < gpathBest[allp - 1].AdditionP.pm)
									{
										unknownO[j+1].pointNumBOOL = -1;
									}
									else
									{
										unknownO[j+1].pointNumBOOL = 1;
									}
								}
								break;
							}
						}
					}

					allp_un++;
					break;
				}
			}
		}
	}

	//��unknownO���鸳ֵCalNum  calnumPATH
	int tempNum = 0, pathNum = 0;
	if (allp_un == 1)
	{
		unknownO[0].CalNum = 1;
		unknownO[0].calnumPATH = 1;
	}
	else
	{
		for (int i = 0; i < allp_un - 1; i++)
		{
			if (unknownO[i].pointNum != unknownO[i + 1].pointNum)
			{
				for (int n = i; n > i - (pathNum + 1); n--)
				{
					unknownO[n].calnumPATH = pathNum + 1;
				}
				tempNum++;
				pathNum = 0;
				if (i == allp_un - 2)
				{
					unknownO[i+1].calnumPATH = 1;
					tempNum++;
				}
			}
			else
			{
				pathNum++;
				if (i == allp_un - 2)
				{
					for (int n = i+1; n > i + 1 - (pathNum + 1); n--)
					{
						unknownO[n].calnumPATH = pathNum + 1;						
					}
					tempNum++;
				}
			}
		}
		for (int i = 0; i < allp_un; i++)
		{
			unknownO[i].CalNum = tempNum;
		}
	}
}

float USVView::calculateDOtime(int pointNum)//���㶯̬�ϰ�����·���ཻʱ����·���յ㣬���õ�ʱ��
{
	float t, sgPM,x0,y0,x00,y00;
	if ((SObsticle_num[0].form != 1) && (SObsticle_num[0].form != 2))//û�о�̬�ϰ��ȫ��pointNum = -1
	{
		if (pointNum <= -2)
		{
			t = 0;
		}
		else
		{
			sgPM = sqrt(pow((float)abs(int(startgoalp.sx - startgoalp.gx)), 2) + pow((float)abs(int(startgoalp.sy - startgoalp.gy)), 2));
			t = sgPM / drawscale / startgoalp.v_ms;
		}
	}
	else
	{
		if (pointNum <= -2)
		{
			t = 0;
		}
		else if (pointNum==-1)//1.��ʼ��͵�һ·����
		{
			//·����
			x0 = startgoalp.sx + gpathBest[0].GeneralP.pm * cos(gpathBest[0].GeneralP.pa);
			y0 = startgoalp.sy - gpathBest[0].GeneralP.pm * sin(gpathBest[0].GeneralP.pa);
			sgPM = sqrt(pow((float)abs((float)startgoalp.sx - x0), 2) + pow((float)abs((float)startgoalp.sy - y0), 2));
			t = sgPM / drawscale / startgoalp.v_ms;
		}
		else//2.·����֮��//3.�յ�����·����
		{			
			//1.��ʼ��͵�һ·����
			x0 = startgoalp.sx + gpathBest[0].GeneralP.pm * cos(gpathBest[0].GeneralP.pa);
			y0 = startgoalp.sy - gpathBest[0].GeneralP.pm * sin(gpathBest[0].GeneralP.pa);
			sgPM = sqrt(pow((float)abs((float)startgoalp.sx - x0), 2) + pow((float)abs((float)startgoalp.sy - y0), 2));
			t = sgPM / drawscale / startgoalp.v_ms;

			for (int j = 0; j < pointNum+1; j++)
			{
				//·����
				x0 = startgoalp.sx + gpathBest[j].GeneralP.pm * cos(gpathBest[j].GeneralP.pa);
				y0 = startgoalp.sy - gpathBest[j].GeneralP.pm * sin(gpathBest[j].GeneralP.pa);
				if (j != allp - 1)
				{
					x00 = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
					y00 = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
				}
				else if (j == allp - 1)
				{
					x00 = startgoalp.gx;
					y00 = startgoalp.gy;
				}

				sgPM = sqrt(pow((float)abs(x00 - x0), 2) + pow((float)abs(y00 - y0), 2));
				t = t + sgPM / drawscale / startgoalp.v_ms;//ʱ���ۼ�
			}
		}
	}
	return t;
}

void USVView::calculate_DObsticle_forbidA()//���㶯̬�ཻ�ϰ�������,�����ཻ��ʼ����ɵ��ٶ������ε�Vso,�ͽ���Vpa���ϳ��ٶȽǶ�
{
	int n,m;
	float t, x, y, x0, y0, tempD, u, a_path_DOC, Ab, pa_max, docDa;
	REC Peak[4];
	ParticleDO temp;

	for (int i = 0; i < allp_do; i++)
	{
		if (DObsticle_num[i].form == 1)//Բ�ζ�̬�ϰ���
		{
			n = DObsticle_num[i].pointNum;			
			t = calculateDOtime(n-1);//���㶯̬�ϰ�����·���ཻʱ����·���յ㣬���õ�ʱ��
			m = DObsticle_num[i].num;

			x = dynamicoc[m].x + cos(dynamicoc[m].Da*pi / 180)*(t*dynamicoc[m].V* Kn_ms*drawscale);
			y = dynamicoc[m].y - sin(dynamicoc[m].Da*pi / 180)*(t*dynamicoc[m].V* Kn_ms*drawscale);
			if (n==-1)
			{
				x0 = startgoalp.sx;
				y0 = startgoalp.sy;
			}
			else
			{
				x0 = startgoalp.sx + gpathBest[n].GeneralP.pm * cos(gpathBest[n].GeneralP.pa);
				y0 = startgoalp.sy - gpathBest[n].GeneralP.pm * sin(gpathBest[n].GeneralP.pa);
			}
			
			tempD = sqrt(pow((float)abs(x0 - x), 2) + pow((float)abs(y0 - y), 2));
			u = abs(asin(((float)dynamicoc[m].r/2 + safe_expandT) / tempD));//��ʱ�̶�̬�ϰ�����·�������ߺ����߽Ƕ�
			//a_path_DOC = 0.0 - atan((y - y0) / (x - x0));//��ʱ�̶�̬�ϰ�����·�������߽Ƕ�
			ParticleDO temp;
			a_path_DOC = temp.calculate_2point_pa(x0, y0, x, y);

			if (a_path_DOC<0)
			{
				a_path_DOC = a_path_DOC + 2 * pi;
			}
			//����̬Բ����ǵ����ֵ����Сֵ��δ�������X��Ľ�����ֿ������ж�(forbidA[i].max>forbidA[i].min)��
			//��Ϊ����Ϊ���X���������ֿ�Ϊ��forbidA[i].max,2*pi����0,forbidA[i].min��
			dynamicoc[m].a_path_DOC = a_path_DOC;
			dynamicoc[m].min = a_path_DOC - u;
			dynamicoc[m].max = a_path_DOC + u;

			if (dynamicoc[m].min < 0)
			{
				dynamicoc[m].min = dynamicoc[m].min + 2 * pi;
			}
			else if (dynamicoc[m].min >= (2 * pi))
			{
				dynamicoc[m].min = dynamicoc[m].min - 2 * pi;
			}

			if (dynamicoc[m].max < 0)
			{
				dynamicoc[m].max = dynamicoc[m].max + 2 * pi;
			}
			else if (dynamicoc[m].max >= (2 * pi))
			{
				dynamicoc[m].max = dynamicoc[m].max - 2 * pi;
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//���ཻ��ʼ����ɵ��ٶ������ε�Vso, �ͽ���pa
			//��ʱ���յ��·��������
			if ((allp == 0) || ((n + 1) >= allp))//û�о�̬�ϰ���򳬹���̬�ϰ���
			{
				x = startgoalp.gx;
				y = startgoalp.gy;
			}
			else
			{
				x = startgoalp.sx + gpathBest[n + 1].GeneralP.pm * cos(gpathBest[n + 1].GeneralP.pa);
				y = startgoalp.sy - gpathBest[n + 1].GeneralP.pm * sin(gpathBest[n + 1].GeneralP.pa);
			}
			
			//a_path_DOC = 0.0 - atan((y - y0) / (x - x0));//��ʱ��·���ε����߽Ƕ�	
			a_path_DOC = temp.calculate_2point_pa(x0, y0, x, y);

			dynamicoc[m].a_path = a_path_DOC;

			Ab = abs(a_path_DOC - dynamicoc[m].Da*pi / 180);//·�����ٶȷ�����ϰ����ٶȷ���н�
			//�ϳ��ٶ�
			dynamicoc[m].Vso = sqrt(pow((float)startgoalp.v_kn, 2) + pow((float)dynamicoc[m].V, 2) - 2 * startgoalp.v_kn * dynamicoc[m].V * cos(Ab) );
			//·���㴦���ϳ��ٶȽǶ���·�����ٶȼн�
			dynamicoc[m].Vpa = acos((pow(startgoalp.v_kn, 2) + pow(dynamicoc[m].Vso, 2) - pow(dynamicoc[m].V, 2)) / (2 * startgoalp.v_kn * dynamicoc[m].Vso));

			//����Ϊ����ϳ��ٶȽǶ�
			/*pa_max = a_path_DOC + pi;
			if ((pa_max>(2 * pi - 0.005)) && (pa_max<(2 * pi + 0.005)))
			{
				pa_max = pa_max - 2 * pi;
			}*/
			pa_max = temp.calculate_Pa_02PI(a_path_DOC + pi);

			docDa = temp.calculate_Pa_02PI((180 + dynamicoc[m].Da) * pi / 180);
			/*docDa = (180 + dynamicoc[m].Da) * pi / 180;
			if ((docDa>(2 * pi - 0.005)) && (docDa<(2 * pi + 0.005)))
			{
				docDa = docDa - 2 * pi;
			}*/

			if (a_path_DOC<pa_max)
			{
				if ( (docDa >= a_path_DOC) && (docDa<pa_max))
				{
					dynamicoc[m].pa_vso = a_path_DOC + dynamicoc[m].Vpa;
				}
				else
				{
					dynamicoc[m].pa_vso = a_path_DOC - dynamicoc[m].Vpa;
				}				
			}
			else
			{
				if (((docDa >= a_path_DOC) && (docDa<=2 * pi)) || ((docDa >= 0) && (docDa<pa_max)))
				{
					dynamicoc[m].pa_vso = a_path_DOC + dynamicoc[m].Vpa;
				}
				else
				{
					dynamicoc[m].pa_vso = a_path_DOC - dynamicoc[m].Vpa;
				}
			}

			if (dynamicoc[m].pa_vso < 0)
			{
				dynamicoc[m].pa_vso = dynamicoc[m].pa_vso + 2 * pi;
			}
			else if (dynamicoc[m].pa_vso>=(2*pi))
			{
				dynamicoc[m].pa_vso = dynamicoc[m].pa_vso - 2 * pi;
			}
				
		}
		else if (DObsticle_num[i].form == 2)//���ζ�̬�ϰ���
		{
			n = DObsticle_num[i].pointNum;
			t = calculateDOtime(n - 1);//���㶯̬�ϰ�����·���ཻʱ����·���յ㣬���õ�ʱ��
			m = DObsticle_num[i].num;

			if (n == -1)
			{
				x0 = startgoalp.sx;
				y0 = startgoalp.sy;
			}
			else
			{
				x0 = startgoalp.sx + gpathBest[n].GeneralP.pm * cos(gpathBest[n].GeneralP.pa);
				y0 = startgoalp.sy - gpathBest[n].GeneralP.pm * sin(gpathBest[n].GeneralP.pa);
			}

			Peak[0].xEX = dynamicor[m].Peak[0].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[0].yEX = dynamicor[m].Peak[0].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[1].xEX = dynamicor[m].Peak[1].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[1].yEX = dynamicor[m].Peak[1].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[2].xEX = dynamicor[m].Peak[2].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[2].yEX = dynamicor[m].Peak[2].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[3].xEX = dynamicor[m].Peak[3].xEX + cos(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);
			Peak[3].yEX = dynamicor[m].Peak[3].yEX - sin(dynamicor[m].Da*pi / 180)*(t*dynamicor[m].V* Kn_ms*drawscale);

			SetStaticObstacleRectangle Rectangle;
			PointInRC pointinrc;
			pointinrc = Rectangle.calculate_pointInRC(Peak[0], Peak[1], Peak[2], Peak[3], x0, y0);

			//dynamicor[m].min = 0.0 - atan((y - Peak[pointinrc.min].yEX) / (x - Peak[pointinrc.min].xEX));//��ʱ�̶�̬�ϰ�����·�������߽Ƕ�
		    //	if (dynamicor[m].min<0)	dynamicor[m].min = dynamicor[m].min + 2 * pi;
			ParticleDO temp;
			dynamicor[m].min = temp.calculate_2point_pa(x0, y0, Peak[pointinrc.min].xEX, Peak[pointinrc.min].yEX);
			
			//dynamicor[m].max = 0.0 - atan((y - Peak[pointinrc.max].yEX) / (x - Peak[pointinrc.max].xEX));//��ʱ�̶�̬�ϰ�����·�������߽Ƕ�
			//if (dynamicor[m].max<0)		dynamicor[m].max = dynamicor[m].max + 2 * pi;
			dynamicor[m].max = temp.calculate_2point_pa(x0, y0, Peak[pointinrc.max].xEX, Peak[pointinrc.max].yEX);
			
			if (dynamicor[m].min < 0)
			{
				dynamicor[m].min = dynamicor[m].min + 2 * pi;
			}
			else if (dynamicor[m].min >= (2 * pi))
			{
				dynamicor[m].min = dynamicor[m].min - 2 * pi;
			}

			if (dynamicor[m].max < 0)
			{
				dynamicor[m].max = dynamicor[m].max + 2 * pi;
			}
			else if (dynamicor[m].max >= (2 * pi))
			{
				dynamicor[m].max = dynamicor[m].max - 2 * pi;
			}
		
			if (dynamicor[m].min>dynamicor[m].max)
			{
				dynamicor[m].a_path_DOC = (dynamicor[m].max + dynamicor[m].min - 2*pi) / 2;
			}
			else
			{
				dynamicor[m].a_path_DOC = (dynamicor[m].max + dynamicor[m].min) / 2;
			}
			
			if (dynamicor[m].a_path_DOC < 0)
			{
				dynamicor[m].a_path_DOC = dynamicor[m].a_path_DOC + 2 * pi;
			}
			else if (dynamicor[m].a_path_DOC >= (2 * pi))
			{
				dynamicor[m].a_path_DOC = dynamicor[m].a_path_DOC - 2 * pi;
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//���ཻ��ʼ����ɵ��ٶ������ε�Vso, �ͽ���pa
			//��ʱ���յ��·��������

			if ((allp == 0) || ((n + 1) >= allp))//û�о�̬�ϰ���򳬹���̬�ϰ���
			{
				x = startgoalp.gx;
				y = startgoalp.gy;
			}
			else
			{
				x = startgoalp.sx + gpathBest[n + 1].GeneralP.pm * cos(gpathBest[n + 1].GeneralP.pa);
				y = startgoalp.sy - gpathBest[n + 1].GeneralP.pm * sin(gpathBest[n + 1].GeneralP.pa);
			}

			//a_path_DOC = 0.0 - atan((y - y0) / (x - x0));//��ʱ��·���ε����߽Ƕ�
			a_path_DOC = temp.calculate_2point_pa(x0, y0, x, y);
			dynamicor[m].a_path = a_path_DOC;

			Ab = abs(a_path_DOC - dynamicor[m].Da*pi / 180);//·�����ٶȷ�����ϰ����ٶȷ���н�
			//�ϳ��ٶ�
			dynamicor[m].Vso = sqrt(pow((float)startgoalp.v_kn, 2) + pow((float)dynamicor[m].V, 2) - 2 * startgoalp.v_kn * dynamicor[m].V * cos(Ab));
			//·���㴦��Dpo��·����ԭ������߼н�
			dynamicor[m].Vpa = acos((pow(startgoalp.v_kn, 2) + pow(dynamicor[m].Vso, 2) - pow(dynamicor[m].V, 2)) / (2 * startgoalp.v_kn * dynamicor[m].Vso));

			//�ϳ��ٶȽǶ�
			/*pa_max = a_path_DOC + pi;
			if ((pa_max>(2 * pi - 0.005)) && (pa_max<(2 * pi + 0.005)))
			{
				pa_max = pa_max - 2 * pi;
			}*/

			pa_max = temp.calculate_Pa_02PI(a_path_DOC + pi);

			docDa = temp.calculate_Pa_02PI((180 + dynamicor[m].Da) * pi / 180);

			/*docDa = (180 + dynamicor[m].Da) * pi / 180;
			if ((docDa>(2 * pi - 0.005)) && (docDa<(2 * pi + 0.005)))
			{
				docDa = docDa - 2 * pi;
			}*/


			if (a_path_DOC<pa_max)
			{
				if ((docDa >= a_path_DOC) && (docDa<pa_max))
				{
					dynamicor[m].pa_vso = a_path_DOC + dynamicor[m].Vpa;
				}
				else
				{
					dynamicor[m].pa_vso = a_path_DOC - dynamicor[m].Vpa;
				}
			}
			else
			{
				if (((docDa >= a_path_DOC) && (docDa<2 * pi)) || ((docDa >= 0 )&& (docDa<pa_max)))
				{
					dynamicor[m].pa_vso = a_path_DOC + dynamicor[m].Vpa;
				}
				else
				{
					dynamicor[m].pa_vso = a_path_DOC - dynamicor[m].Vpa;
				}
			}

			if (dynamicor[m].pa_vso < 0)
			{
				dynamicor[m].pa_vso = dynamicor[m].pa_vso + 2 * pi;
			}
			else if (dynamicor[m].pa_vso >= (2 * pi))
			{
				dynamicor[m].pa_vso = dynamicor[m].pa_vso - 2 * pi;
			}
		}
	}

}

void USVView::calculate_DObsticle_num()//���㶯̬�ϰ��Բ�ͷ����Ƿ���USV��ײ����Ϣ����
{
	//ÿ����һ�γ�ʼ��һ��
	for (int i = 0; i < 20; i++)
	{
		DObsticle_num[i].form = 0;
		DObsticle_num[i].rcnum = 0;
		DObsticle_num[i].num = 0;
		DObsticle_num[i].pointNum = 0;
	}
	allp_do = 0;
	//��ʱ�䣬ÿ��·���Դ˼��㣬�����ĸ�·���ڵ���ཻ��DObsticle_num[j].pointNum ���ⲿֻ�ֿ��жϣ�����DObsticle_num��
	float sgPM,t,t1;//�ö�·���ĳ���&����ʱ��
	point_d s1, e1, s2, e2;//�жϵ��ĸ�����
	if ( (SObsticle_num[0].form != 1) && (SObsticle_num[0].form != 2) )//û�о�̬�ϰ��ȫ��pointNum = -1
	{		
		sgPM = sqrt(pow((float)abs(int(startgoalp.sx - startgoalp.gx)), 2) + pow((float)abs(int(startgoalp.sy - startgoalp.gy)), 2));
		t = sgPM / drawscale / startgoalp.v_ms;

		bool flag;
		float x0;// y0, Xobs_t, Yobs_t;
		REC Peak[4];
		//��̬Բ���ϰ����ж�
		for (int i = 0; dynamicoc[i].r!=0; i++)//GDI����ϵ
		{
			flag = FALSE;

			//���1��Բ�����߲���·���ཻ�����ϰ�Բ���·��

			float tempY = abs(dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(t*dynamicoc[i].V* Kn_ms*drawscale) - startgoalp.sy);//�ϰ�Բ����·��֮��ľ���
			if ( tempY < (dynamicoc[i].r/2 + safe_expandT)) //���ϰ�Բ�ཻ
			{
				//·���㴦��ֱ������ϵֵ
				x0 = dynamicoc[i].x;
				//�ϰ���������ֱ�ߵĽ����ֱ������ϵֵ
				if ( (startgoalp.sx <= x0) && (x0 <= startgoalp.gx))//�ϰ�Բ���������յ�֮��
				{
					flag = true;
				}
			}

			//���2��Բ�����߲���·���ཻ�����ϰ�Բ��·��ֻ��һ������
			
			//���3��Բ��������·���ཻ

			s1.x = startgoalp.sx;
			s1.y = startgoalp.sy;
			e1.x = startgoalp.gx;
			e1.y = startgoalp.gy;

			s2.x = dynamicoc[i].x - cos(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r/2 + safe_expandT);
			s2.y = dynamicoc[i].y + sin(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r/2 + safe_expandT);
			e2.x = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r/2 + safe_expandT + t*dynamicoc[i].V* Kn_ms*drawscale);
			e2.y = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r/2 + safe_expandT + t*dynamicoc[i].V* Kn_ms*drawscale);
			if (IsIntersected(s1, e1, s2, e2) || flag)
			{
				DObsticle_num[allp_do].form = 1;
				DObsticle_num[allp_do].num = i;
				DObsticle_num[allp_do].pointNum = -1;
				dynamicoc[i].pmChange = dynamicoc[i].pm;
				dynamicoc[i].xChange = dynamicoc[i].x;
				dynamicoc[i].yChange = dynamicoc[i].y;
				
				allp_do++;
			}
		}

		//��̬�����ϰ����ж�
		for (int i = 0; dynamicor[i].HalfL != 0; i++)//GDI����ϵ
		{
			s1.x = startgoalp.sx;
			s1.y = startgoalp.sy;
			e1.x = startgoalp.gx;
			e1.y = startgoalp.gy;

			if ((0 <= dynamicor[i].Da) && (dynamicor[i].Da <90))
			{
				Peak[0] = dynamicor[i].Peak[0];
				Peak[1] = dynamicor[i].Peak[1];
				Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*( t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*( t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*( t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*( t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 2;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
				}
			}
			else if ((90 <= dynamicor[i].Da) && (dynamicor[i].Da <180))
			{
				Peak[2] = dynamicor[i].Peak[2];
				Peak[1] = dynamicor[i].Peak[1];
				Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 3;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
				}
			}
			else if ((180 <= dynamicor[i].Da) && (dynamicor[i].Da <270))
			{
				Peak[2] = dynamicor[i].Peak[2];
				Peak[3] = dynamicor[i].Peak[3];
				Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 0;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
				}
			}
			else if ((270 <= dynamicor[i].Da) && (dynamicor[i].Da <360))
			{
				Peak[0] = dynamicor[i].Peak[0];
				Peak[3] = dynamicor[i].Peak[3];
				Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 1;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
				}
			}
		}		
	}
	else
	{
		bool flag;
		float x0, y0, x00, y00, x1, y1, Xobs_t, Yobs_t, k, tempY;
		REC Peak[4];
		//��̬Բ���ϰ����ж�
		for (int i = 0; dynamicoc[i].r != 0; i++)//GDI����ϵ
		{
			flag = FALSE;
			ParticleDO temp;
			//1.��ʼ��͵�һ·����

			//·����
			x0 = startgoalp.sx + gpathBest[0].GeneralP.pm * cos(gpathBest[0].GeneralP.pa);
			y0 = startgoalp.sy - gpathBest[0].GeneralP.pm * sin(gpathBest[0].GeneralP.pa);
			sgPM = sqrt(pow((float)abs((float)startgoalp.sx - x0), 2) + pow((float)abs((float)startgoalp.sy - y0), 2));
			t = sgPM / drawscale / startgoalp.v_ms;

			//���1��Բ�����߲���·���ཻ�����ϰ�Բ���·��
			//����t����ϰ�ԲԲ��GDI����ֵ
			x1 = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(t*dynamicoc[i].V* Kn_ms*drawscale);
			y1 = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(t*dynamicoc[i].V* Kn_ms*drawscale);
			if ((x0 - (float)startgoalp.sx) == 0)//����kΪ����󣬼�·����ֱ��x�ᣬ����С
			{
				tempY = abs(x0 - x1);//�ϰ�Բ����·��֮��ľ���

				//·���㴦��ֱ������ϵֵ
				Xobs_t = x0;
				Yobs_t = y1;
			}
			else
			{
				k = (y0 - (float)startgoalp.sy) / (x0 - (float)startgoalp.sx);
				tempY = abs((k*x1 - y1 + y0 - k*x0) / sqrt(pow(k, 2) + 1.0));//�ϰ�Բ����·��֮��ľ���

				//·���㴦��ֱ������ϵֵ
				Xobs_t = (x1 + k * y1 + k * (k*x0 - y0)) / (1 + k*k);
				Yobs_t = k*(Xobs_t - x0) + y0;
			}

			if (tempY < (dynamicoc[i].r / 2 + safe_expandT)) //���ϰ�Բ�ཻ
			{
				//�ϰ���������ֱ�ߵĽ����ֱ������ϵֵ
				flag = temp.calculate_1pointIN2point(startgoalp.sx, startgoalp.sy, x0, y0, Xobs_t, Xobs_t);//�ϰ�Բ���������յ�֮��
				//if ((startgoalp.sx <= Xobs_t && Xobs_t <= x0) || (startgoalp.sy <= Yobs_t && Yobs_t <= y0))//�ϰ�Բ���������յ�֮��	flag = true;		
			}

			//���2��Բ�����߲���·���ཻ�����ϰ�Բ��·��ֻ��һ������
			float tempPM, tempPA;
			tempPM = sqrt(pow((float)abs((float)startgoalp.sx - x1), 2) + pow((float)abs((float)startgoalp.sy - y1), 2));
			
			tempPA = temp.calculate_2point_pa((float)startgoalp.sx, (float)startgoalp.sy, x1, y1);
			
			if ((pow(gpathBest[0].GeneralP.pm, 2) + pow(tempPM, 2) - 2 * gpathBest[0].GeneralP.pm*tempPM*cos(abs(gpathBest[0].GeneralP.pa - tempPA)))
				<= pow((float)(dynamicoc[i].r / 2 + safe_expandT), 2))
			{
				flag = 1;
			}

			//���3��Բ��������·���ཻ

			s1.x = startgoalp.sx;
			s1.y = startgoalp.sy;
			e1.x = x0;
			e1.y = y0;

			s2.x = dynamicoc[i].x - cos(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r / 2 + safe_expandT);
			s2.y = dynamicoc[i].y + sin(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r / 2 + safe_expandT);
			e2.x = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r / 2 + safe_expandT + t*dynamicoc[i].V* Kn_ms*drawscale);
			e2.y = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r / 2 + safe_expandT + t*dynamicoc[i].V* Kn_ms*drawscale);
			if (IsIntersected(s1, e1, s2, e2) || flag)
			{
				DObsticle_num[allp_do].form = 1;
				DObsticle_num[allp_do].num = i;
				DObsticle_num[allp_do].pointNum = -1;
				dynamicoc[i].pmChange = dynamicoc[i].pm;
				dynamicoc[i].xChange = dynamicoc[i].x ;
				dynamicoc[i].yChange = dynamicoc[i].y ;
				allp_do++;
				continue;
			}

			//2.·����֮��//3.�յ�����·����
			for (int j = 0; j < allp; j++)
			{
				//·����
				t1 = t;//�ѵ���һ��·��������ʱ���¼
				x0 = startgoalp.sx + gpathBest[j].GeneralP.pm * cos(gpathBest[j].GeneralP.pa);
				y0 = startgoalp.sy - gpathBest[j].GeneralP.pm * sin(gpathBest[j].GeneralP.pa);
				if (j != allp - 1)
				{
					x00 = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
					y00 = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
				}
				else if (j == allp - 1)
				{
					x00 = startgoalp.gx;
					y00 = startgoalp.gy;
				}

				sgPM = sqrt(pow((float)abs(x00 - x0), 2) + pow((float)abs(y00 - y0), 2));
				t = t + sgPM / drawscale / startgoalp.v_ms;//ʱ���ۼ�

				//���1��Բ�����߲���·���ཻ�����ϰ�Բ���·��
				//����t����ϰ�ԲԲ��GDI����ֵ
				x1 = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(t*dynamicoc[i].V* Kn_ms*drawscale);
				y1 = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(t*dynamicoc[i].V* Kn_ms*drawscale);
				if ((x0 - x00) == 0)//����kΪ����󣬼�·����ֱ��x�ᣬ����С
				{
					tempY = abs(x0 - x1);//�ϰ�Բ����·��֮��ľ���

					//·���㴦��ֱ������ϵֵ
					Xobs_t = x0;
					Yobs_t = y1;
				}
				else
				{
					k = (y0 - y00) / (x0 - x00);
					tempY = abs((k*x1 - y1 + y0 - k*x0) / sqrt(pow(k, 2) + 1.0));//�ϰ�Բ����·��֮��ľ���

					//·���㴦��ֱ������ϵֵ
					Xobs_t = (x1 + k * y1 + k * (k*x0 - y0)) / (1 + k*k);
					Yobs_t = k*(Xobs_t - x0) + y0;
				}

				if (tempY < (dynamicoc[i].r / 2 + safe_expandT)) //���ϰ�Բ�ཻ
				{
					//�ϰ���������ֱ�ߵĽ����ֱ������ϵֵ
					flag = temp.calculate_1pointIN2point(x0, y0, x00, y00, Xobs_t, Xobs_t);//�ϰ�Բ���������յ�֮��
					//if ((x0 <= Xobs_t && Xobs_t <= x00) || (y0 <= Yobs_t && Yobs_t <= y00))//�ϰ�Բ���������յ�֮��	flag = true;
				}

				//���2��Բ�����߲���·���ཻ�����ϰ�Բ��·��ֻ��һ������
				float tempPM, tempPA;
				tempPM = sqrt(pow((float)abs((float)startgoalp.sx - x1), 2) + pow((float)abs((float)startgoalp.sy - y1), 2));
				ParticleDO temp;
				tempPA = temp.calculate_2point_pa((float)startgoalp.sx, (float)startgoalp.sy, x1, y1);

				if (tempPA<0)
				{
					tempPA = tempPA + 2 * pi;
				}

				if ((pow(gpathBest[j + 1].GeneralP.pm, 2) + pow(tempPM, 2) - 2 * gpathBest[j + 1].GeneralP.pm*tempPM*cos(abs(gpathBest[j + 1].GeneralP.pa - tempPA)))
					<= pow((float)(dynamicoc[i].r / 2 + safe_expandT), 2))
				{
					flag = 1;
				}

				//���3��Բ��������·���ཻ

				s1.x = x0;
				s1.y = y0;
				e1.x = x00;
				e1.y = y00;

				s2.x = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(t1*dynamicoc[i].V* Kn_ms*drawscale - (dynamicoc[i].r / 2 + safe_expandT));
				s2.y = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(t1*dynamicoc[i].V* Kn_ms*drawscale - (dynamicoc[i].r / 2 + safe_expandT));
				e2.x = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r / 2 + safe_expandT + t*dynamicoc[i].V* Kn_ms*drawscale);
				e2.y = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(dynamicoc[i].r / 2 + safe_expandT + t*dynamicoc[i].V* Kn_ms*drawscale);
				if (IsIntersected(s1, e1, s2, e2) || flag)
				{
					DObsticle_num[allp_do].form = 1;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].pointNum = j;
					dynamicoc[i].pmChange = sqrt(pow((float)abs((float)startgoalp.sx - s2.x), 2) + pow((float)abs((float)startgoalp.sy - s2.y), 2));
					dynamicoc[i].xChange = dynamicoc[i].x + cos(dynamicoc[i].Da*pi / 180)*(t1*dynamicoc[i].V* Kn_ms*drawscale);
					dynamicoc[i].yChange = dynamicoc[i].y - sin(dynamicoc[i].Da*pi / 180)*(t1*dynamicoc[i].V* Kn_ms*drawscale);
					allp_do++;
					break;
				}
			}

		}

		//��̬�����ϰ����ж�
		for (int i = 0; dynamicor[i].HalfL != 0; i++)//GDI����ϵ
		{
			//1.��ʼ��͵�һ·����
			//·����
			x0 = startgoalp.sx + gpathBest[0].GeneralP.pm * cos(gpathBest[0].GeneralP.pa);
			y0 = startgoalp.sy - gpathBest[0].GeneralP.pm * sin(gpathBest[0].GeneralP.pa);
			sgPM = sqrt(pow((float)abs((float)startgoalp.sx - x0), 2) + pow((float)abs((float)startgoalp.sy - y0), 2));
			t = sgPM / drawscale / startgoalp.v_ms;

			s1.x = startgoalp.sx;
			s1.y = startgoalp.sy;
			e1.x = x0;
			e1.y = y0;

			if ((0 <= dynamicor[i].Da) && (dynamicor[i].Da <90))
			{
				Peak[0] = dynamicor[i].Peak[0];
				Peak[1] = dynamicor[i].Peak[1];
				Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 2;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX ;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX ;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
					continue;
				}
			}
			else if ((90 <= dynamicor[i].Da) && (dynamicor[i].Da <180))
			{
				Peak[2] = dynamicor[i].Peak[2];
				Peak[1] = dynamicor[i].Peak[1];
				Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 3;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
					continue;
				}
			}
			else if ((180 <= dynamicor[i].Da) && (dynamicor[i].Da <270))
			{
				Peak[2] = dynamicor[i].Peak[2];
				Peak[3] = dynamicor[i].Peak[3];
				Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 0;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
					continue;
				}
			}
			else if ((270 <= dynamicor[i].Da) && (dynamicor[i].Da <360))
			{
				Peak[0] = dynamicor[i].Peak[0];
				Peak[3] = dynamicor[i].Peak[3];
				Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
				Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

				if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
				{
					DObsticle_num[allp_do].form = 2;
					DObsticle_num[allp_do].num = i;
					DObsticle_num[allp_do].rcnum = 1;
					DObsticle_num[allp_do].pointNum = -1;

					if (dynamicor[i].Peak[1].Pm >= dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[1].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[1].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[1].yEX;
					}
					else if (dynamicor[i].Peak[1].Pm < dynamicor[i].Peak[3].Pm)
					{
						dynamicor[i].pmChange = dynamicor[i].Peak[3].Pm;
						dynamicor[i].xChange = dynamicor[i].Peak[3].xEX;
						dynamicor[i].yChange = dynamicor[i].Peak[3].yEX;
					}

					allp_do++;
					continue;
				}
			}

			//2.·����֮��//3.�յ�����·����
			for (int j = 0; j < allp; j++)
			{
				//·����
				t1 = t;//�ѵ���һ��·��������ʱ���¼
				x0 = startgoalp.sx + gpathBest[j].GeneralP.pm * cos(gpathBest[j].GeneralP.pa);
				y0 = startgoalp.sy - gpathBest[j].GeneralP.pm * sin(gpathBest[j].GeneralP.pa);
				if (j != allp - 1)
				{
					x00 = startgoalp.sx + gpathBest[j + 1].GeneralP.pm * cos(gpathBest[j + 1].GeneralP.pa);
					y00 = startgoalp.sy - gpathBest[j + 1].GeneralP.pm * sin(gpathBest[j + 1].GeneralP.pa);
				}
				else if (j == allp - 1)
				{
					x00 = startgoalp.gx;
					y00 = startgoalp.gy;
				}

				sgPM = sqrt(pow((float)abs(x00 - x0), 2) + pow((float)abs(y00 - y0), 2));
				t = t + sgPM / drawscale / startgoalp.v_ms;//ʱ���ۼ�

				s1.x = x0;
				s1.y = y0;
				e1.x = x00;
				e1.y = y00;

				if ((0 <= dynamicor[i].Da) && (dynamicor[i].Da <90))
				{
					Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

					if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
					{
						DObsticle_num[allp_do].form = 2;
						DObsticle_num[allp_do].num = i;
						DObsticle_num[allp_do].rcnum = 2;
						DObsticle_num[allp_do].pointNum = j;

						Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[1].yEX), 2));
						Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[3].yEX), 2));
						if (Peak[1].Pm >= Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[1].Pm;
							dynamicor[i].xChange = Peak[1].xEX;
							dynamicor[i].yChange = Peak[1].yEX;
						}
						else if (Peak[1].Pm < Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[3].Pm;
							dynamicor[i].xChange = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
							dynamicor[i].yChange = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						}

						allp_do++;
						break;
					}
				}
				else if ((90 <= dynamicor[i].Da) && (dynamicor[i].Da <180))
				{
					Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

					if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
					{
						DObsticle_num[allp_do].form = 2;
						DObsticle_num[allp_do].num = i;
						DObsticle_num[allp_do].rcnum = 3;
						DObsticle_num[allp_do].pointNum = j;

						Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[1].yEX), 2));
						Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[3].yEX), 2));
						if (Peak[1].Pm >= Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[1].Pm;
							dynamicor[i].xChange = Peak[1].xEX;
							dynamicor[i].yChange = Peak[1].yEX;
						}
						else if (Peak[1].Pm < Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[3].Pm;
							dynamicor[i].xChange = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
							dynamicor[i].yChange = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						}

						allp_do++;
						break;
					}
				}
				else if ((180 <= dynamicor[i].Da) && (dynamicor[i].Da <270))
				{
					Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

					if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
					{
						DObsticle_num[allp_do].form = 2;
						DObsticle_num[allp_do].num = i;
						DObsticle_num[allp_do].rcnum = 0;
						DObsticle_num[allp_do].pointNum = j;

						Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[1].yEX), 2));
						Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[3].yEX), 2));
						if (Peak[1].Pm >= Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[1].Pm;
							dynamicor[i].xChange = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
							dynamicor[i].yChange = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						}
						else if (Peak[1].Pm < Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[3].Pm;
							dynamicor[i].xChange = Peak[3].xEX;
							dynamicor[i].yChange = Peak[3].yEX;
						}

						allp_do++;
						break;
					}
				}
				else if ((270 <= dynamicor[i].Da) && (dynamicor[i].Da <360))
				{
					Peak[0].xEX = dynamicor[i].Peak[0].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[0].yEX = dynamicor[i].Peak[0].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].xEX = dynamicor[i].Peak[3].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[3].yEX = dynamicor[i].Peak[3].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
					Peak[2].xEX = dynamicor[i].Peak[2].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[2].yEX = dynamicor[i].Peak[2].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);
					Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t*dynamicor[i].V* Kn_ms*drawscale);

					if (IsLineIntersectRect(s1, e1, Peak[0], Peak[1], Peak[2], Peak[3]))//�����ϰ���
					{
						DObsticle_num[allp_do].form = 2;
						DObsticle_num[allp_do].num = i;
						DObsticle_num[allp_do].rcnum = 1;
						DObsticle_num[allp_do].pointNum = j;

						Peak[1].xEX = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[1].yEX = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						Peak[1].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[1].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[1].yEX), 2));
						Peak[3].Pm = sqrt(pow((float)abs((float)startgoalp.sx - Peak[3].xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak[3].yEX), 2));
						if (Peak[1].Pm >= Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[1].Pm;
							dynamicor[i].xChange = dynamicor[i].Peak[1].xEX + cos(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
							dynamicor[i].yChange = dynamicor[i].Peak[1].yEX - sin(dynamicor[i].Da*pi / 180)*(t1*dynamicor[i].V* Kn_ms*drawscale);
						}
						else if (Peak[1].Pm < Peak[3].Pm)
						{
							dynamicor[i].pmChange = Peak[3].Pm;
							dynamicor[i].xChange = Peak[3].xEX;
							dynamicor[i].yChange = Peak[3].yEX;
						}

						allp_do++;
						break;
					}
				}
			}
		}
	}	
	
	//��DObsticle_num���鰴pointNum���д�С��������
	for (int j = 0; j < allp_do - 1; j++)
	{
		for (int i = 0; i < allp_do - 1 - j; i++)
		{
			DOBSTICLE temp;
			if (DObsticle_num[i].pointNum>DObsticle_num[i+1].pointNum)
			{
				temp = DObsticle_num[i];
				DObsticle_num[i] = DObsticle_num[i + 1];
				DObsticle_num[i + 1] = temp;
			}
		}
	}

	//����������������ͨ�з���
	for (int i = 0; i < allp_do; i++)
	{
		ParticleDO colreg;
		DObsticle_num [i].ColREG= colreg.calculate_ColREG(i);//����������������ͨ�з���
	}

	//��DObsticle_num���鸳ֵdocalNUM
	int tempNum = 0,pathNum=0;
	docalNUM[0].startNUM = 0;
	if (allp_do==1)
	{
		docalNUM[0].CalNum = 1;
		docalNUM[0].calnumPATH = 1;
	}
	else
	{
		for (int i = 0; i < allp_do - 1; i++)
		{
			if (DObsticle_num[i].pointNum != DObsticle_num[i + 1].pointNum)
			{
				docalNUM[tempNum + 1].startNUM = i + 1;
				docalNUM[tempNum].calnumPATH = pathNum + 1;
				tempNum++;
				pathNum = 0;
				if (i == allp_do - 2)
				{
					docalNUM[tempNum].calnumPATH = 1;
					tempNum++;
				}
			}
			else
			{
				pathNum++;
				if (i == allp_do - 2)
				{
					docalNUM[tempNum].calnumPATH = pathNum + 1;
					tempNum++;
				}
			}
		}
		for (int i = 0; i < tempNum; i++)
		{
			docalNUM[i].CalNum = tempNum;
		}
	}


	//���鸳ֵCalNum���öζ�̬�ϰ��Ｋ�������ֵ
	for (int i = 0; i < docalNUM[0].CalNum; i++)
	{
		int num = docalNUM[i].calnumPATH;
		int n = docalNUM[i].startNUM;
		int j = DObsticle_num[n].num;
		
		if (DObsticle_num[n].form==1)//Բ���ϰ���
		{
			docalNUM[i].pm = dynamicoc[j].pmChange;
			docalNUM[i].xChange = dynamicoc[j].xChange;
			docalNUM[i].yChange = dynamicoc[j].yChange;
		}
		else if (DObsticle_num[n].form == 2)//�����ϰ���
		{
			docalNUM[i].pm = dynamicor[j].pmChange;
			docalNUM[i].xChange = dynamicor[j].xChange;
			docalNUM[i].yChange = dynamicor[j].yChange;
		}

		for (int m = 1; m < num; m++)
		{
			n++;
			int j = DObsticle_num[n].num;
			if (DObsticle_num[n].form == 1)//Բ���ϰ���
			{
				if (docalNUM[i].pm < dynamicoc[j].pmChange)
				{
					docalNUM[i].pm = dynamicoc[j].pmChange;
					docalNUM[i].xChange = dynamicoc[j].xChange;
					docalNUM[i].yChange = dynamicoc[j].yChange;
				}				
			}
			else if (DObsticle_num[n].form == 2)//�����ϰ���
			{
				if (docalNUM[i].pm < dynamicor[j].pmChange)
				{
					docalNUM[i].pm = dynamicor[j].pmChange;
					docalNUM[i].xChange = dynamicor[j].xChange;
					docalNUM[i].yChange = dynamicor[j].yChange;
				}
			}
		}

	}
}

REC USVView::calculate_drChange(point_d s, point_d e, REC Peak1, REC Peak2, REC Peak3, REC Peak4)//���㶯̬�����ϰ�����·�������Զ��
{
	sqrt(pow((float)abs((float)startgoalp.sx - Peak1.xEX), 2) + pow((float)abs((float)startgoalp.sy - Peak1.yEX), 2));
	return Peak1;
}

void USVView::OnOptimizepath()//�Ż���̬·��
{
	// TODO:  �ڴ���������������

	DWORD start = GetTickCount();//��ʱ��ʼ
	
	bool flag=0;
	//�ж�ʼĩ������
	for (int i = 0; i < allp; i++)//�ж��Ƿ񴩹��ϰ���
	{
		if (SObsticle_num[i].form == 1)//Բ���ϰ���
		{
			int m = SObsticle_num[i].num;

			if (abs(staticoc[m].pm*sin(staticoc[m].pa)) < (staticoc[m].r + safe_expandT))//�����ϰ���
			{
				flag = 1;
				break;
			}			
		}
		else if (SObsticle_num[i].form == 2)//�����ϰ�����ϰ�������
		{
			int m = SObsticle_num[i].num;
			
			point_d ptStart, ptEnd;
			ptStart.x = (float)startgoalp.sx;
			ptStart.y = (float)startgoalp.sy;
			ptEnd.x = (float)startgoalp.gx;
			ptEnd.y = (float)startgoalp.gy;

			if (IsLineIntersectRect(ptStart, ptEnd, staticor[m].Peak[0], staticor[m].Peak[1], staticor[m].Peak[2], staticor[m].Peak[3]))//�����ϰ���
			{
				flag = 1;
				break;
			}
		}
	}
	if (flag==0)//�����У���·�����鸳ֵ
	{
		for (int i = 0; i < allp; i++)
		{
			gpathBest[i].GeneralP.pa = 0;
		}
	}

	//��ʼ����·��������
	for (int j = allp-1; j >=0; j--)
	{
		flag = 0;
		for (int i = 0; i < j+1; i++)//�ж��Ƿ񴩹��ϰ���
		{
			if (SObsticle_num[i].form == 1)//Բ���ϰ���
			{
				int m = SObsticle_num[i].num;

				if (abs(staticoc[m].pm*sin(staticoc[m].pa - gpathBest[j].GeneralP.pa)) < (staticoc[m].r / 2 + safe_expandT))//�����ϰ���
				{
					flag = 1;
					break;
				}
			}
			else if (SObsticle_num[i].form == 2)//�����ϰ�����ϰ�������
			{
				int m = SObsticle_num[i].num;

				point_d ptStart, ptEnd;
				ptStart.x = (float)startgoalp.sx;
				ptStart.y = (float)startgoalp.sy;
				ptEnd.x = gpathBest[j].GeneralP.pm * cos(gpathBest[j].GeneralP.pa) + (float)startgoalp.sx;
				ptEnd.y = (float)startgoalp.sy - gpathBest[j].GeneralP.pm * sin(gpathBest[j].GeneralP.pa);

				if (IsLineIntersectRect(ptStart, ptEnd, staticor[m].Peak[0], staticor[m].Peak[1], staticor[m].Peak[2], staticor[m].Peak[3]))//�����ϰ���
				{
					flag = 1;
					break;
				}
			}
		}

		if (flag == 0)//�����У���·�����鸳ֵ
		{
			for (int i = 0; i < j; i++)
			{
				gpathBest[i].GeneralP.pa = gpathBest[j].GeneralP.pa;
			}
			break;
		}
	}
	
	float pa,pb;
	//·������·��������
	for (int m = 0; m < allp; m++)//·�����0��ʼ
	{
		//���յ�����
		float sgPM = sqrt(pow((float)abs(int(startgoalp.sx - startgoalp.gx)), 2) + pow((float)abs(int(startgoalp.sy - startgoalp.gy)), 2));
		pb = atan((gpathBest[m].GeneralP.pm * cos(gpathBest[m].GeneralP.pa) - sgPM)	/ (gpathBest[m].GeneralP.pm * sin(gpathBest[m].GeneralP.pa)));
		pa = sgPM * cos(pb);

		flag = 0;
		for (int i = m; i < allp; i++)//�ж��Ƿ񴩹��ϰ���
		{
			if (SObsticle_num[i].form == 1)//Բ���ϰ���
			{
				int n = SObsticle_num[i].num;

				if (abs(staticoc[n].pm * cos(staticoc[n].pa + pb) - pa) < (staticoc[n].r / 2 + safe_expandT))//�����ϰ���
				{
					flag = 1;
					break;
				}
			}
			else if (SObsticle_num[i].form == 2)//�����ϰ�����ϰ�������
			{
				int n = SObsticle_num[i].num;

				point_d ptStart, ptEnd;
				ptStart.x = (float)startgoalp.gx;
				ptStart.y = (float)startgoalp.gy;
				ptEnd.x = gpathBest[m].GeneralP.pm * cos(gpathBest[m].GeneralP.pa) + (float)startgoalp.sx;
				ptEnd.y = (float)startgoalp.sy - gpathBest[m].GeneralP.pm * sin(gpathBest[m].GeneralP.pa);

				if (IsLineIntersectRect(ptStart, ptEnd, staticor[n].Peak[0], staticor[n].Peak[1], staticor[n].Peak[2], staticor[n].Peak[3]))//�����ϰ���
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag == 0)//�����У���·�����鸳ֵ
		{
			for (int i = m + 1; i < allp; i++)
			{
				if (pb<=0)
				{
					gpathBest[i].GeneralP.pa = ( - acos(pa / gpathBest[i].GeneralP.pm) - pb);
				}
				else
				{
					gpathBest[i].GeneralP.pa = (acos(pa / gpathBest[i].GeneralP.pm) - pb);
				}
				if (gpathBest[i].GeneralP.pa < 0)
				{
					gpathBest[i].GeneralP.pa = gpathBest[i].GeneralP.pa + 2 * pi;
				}
			}
			break;
		}
		
		for (int j = allp - 1; j > m+1; j--)//��·���㵹������
		{
			pb = atan((gpathBest[m].GeneralP.pm * cos(gpathBest[m].GeneralP.pa) - gpathBest[j].GeneralP.pm * cos(gpathBest[j].GeneralP.pa))
				/ (gpathBest[m].GeneralP.pm * sin(gpathBest[m].GeneralP.pa) - gpathBest[j].GeneralP.pm * sin(gpathBest[j].GeneralP.pa)));
			pa = gpathBest[m].GeneralP.pm * cos(gpathBest[m].GeneralP.pa + pb);
						
			flag = 0;
			for (int i = m; i < j+1; i++)//�ж��Ƿ񴩹��ϰ���
			{
				if (SObsticle_num[i].form == 1)//Բ���ϰ���
				{
					int n = SObsticle_num[i].num;

					if (abs(staticoc[n].pm * cos(staticoc[n].pa + pb) - pa) < (staticoc[n].r / 2 + safe_expandT))//�����ϰ���
					{
						flag = 1;
						break;
					}
				}
				else if (SObsticle_num[i].form == 2)//�����ϰ�����ϰ�������
				{
					int n = SObsticle_num[i].num;

					point_d ptStart, ptEnd;
					ptStart.x = gpathBest[j].GeneralP.pm * cos(gpathBest[j].GeneralP.pa) + (float)startgoalp.sx;
					ptStart.y = (float)startgoalp.sy - gpathBest[j].GeneralP.pm * sin(gpathBest[j].GeneralP.pa);
					ptEnd.x = gpathBest[m].GeneralP.pm * cos(gpathBest[m].GeneralP.pa) + (float)startgoalp.sx;
					ptEnd.y = (float)startgoalp.sy - gpathBest[m].GeneralP.pm * sin(gpathBest[m].GeneralP.pa);

					if (IsLineIntersectRect(ptStart, ptEnd, staticor[n].Peak[0], staticor[n].Peak[1], staticor[n].Peak[2], staticor[n].Peak[3]))//�����ϰ���
					{
						flag = 1;
						break;
					}
				}

			}
			if (flag == 0)//�����У���·�����鸳ֵ
			{
				for (int i = m + 1; i < j; i++)//allp
				{
					if (pb <= 0)//ֱ�߽�������
					{
						gpathBest[i].GeneralP.pa = (-acos(pa / gpathBest[i].GeneralP.pm) - pb);
					}
					else//ֱ�߽�������
					{
						gpathBest[i].GeneralP.pa = (acos(pa / gpathBest[i].GeneralP.pm) - pb);
					}
					if (gpathBest[i].GeneralP.pa < 0)
					{
						gpathBest[i].GeneralP.pa = gpathBest[i].GeneralP.pa + 2 * pi;
					}
				}
				break;
			}
		}
	}
	
	DWORD stop = GetTickCount();//��ʱ����
	UsedTimeInMs_OptimizePATH = stop - start;
	UsedTimeInMs = UsedTimeInMs + UsedTimeInMs_OptimizePATH;
	Particle GbestFitness_OptimizePATH;
	gbestFitness_OptimizePATH = GbestFitness_OptimizePATH.calculate_Fitness(gpathBest);
	best_eachGenerations[testNum].gbestFitness_OptimizePATH = gbestFitness_OptimizePATH;
	Invalidate();
}

void USVView::OnCalculateandoptimize()
{
	// TODO:  �ڴ���������������
	OnCalculatePSO();
	float tempPATH;
	do
	{
		tempPATH = gbestFitness_OptimizePATH;
		OnOptimizepath();
	} while (tempPATH != gbestFitness_OptimizePATH);
}

float USVView::multi(point_d p1, point_d p2, point_d p0)//��ʸ��[p0, p1], [p0, p2]�Ĳ��  
{  
	return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
	//p0�Ƕ���            
	//���������0���������㹲��  
	//���������0����p0p2��p0p1����ʱ�뷽��    
	//�����С��0����p0p2��p0p1��˳ʱ�뷽��    
}

bool USVView::IsIntersected(point_d s1, point_d e1, point_d s2, point_d e2)//�ж��߶��Ƿ��ཻ  
{     
	//1.�����ų������ж��������߶�Ϊ�Խ��ߵ����������Ƿ��ཻ      
	//2.��������	
	if ((max(s1.x, e1.x) > min(s2.x, e2.x)) &&
		(max(s2.x, e2.x) > min(s1.x, e1.x)) &&
		(max(s1.y, e1.y) > min(s2.y, e2.y)) &&
		(max(s2.y, e2.y) > min(s1.y, e1.y)) &&
		(multi(s2, e1, s1) * multi(e1, e2, s1) >= 0) &&
		(multi(s1, e2, s2) * multi(e2, e1, s2) >= 0))
		return true;
	return false;
}

bool USVView::IsLineIntersectRect(point_d ptStart, point_d ptEnd, REC Peak0, REC Peak1, REC Peak2, REC Peak3)// �ж��߶��Ƿ�������ཻ
{
	// Two point both are in rect// One point is in rect, another not.
	SetStaticObstacleRectangle Rectangle;
	if ((Rectangle.calculate_pointInRC(Peak0, Peak1, Peak2, Peak3, ptStart.x, ptStart.y).point == 5) || (Rectangle.calculate_pointInRC(Peak0, Peak1, Peak2, Peak3, ptEnd.x, ptEnd.y).point == 5))
		return TRUE;
	// Two point both aren't in rect
	point_d s2, e2;
	s2.x = Peak0.xEX;
	s2.y = Peak0.yEX;
	e2.x = Peak1.xEX;
	e2.y = Peak1.yEX;
	if (IsIntersected(ptStart, ptEnd, s2, e2))
		return TRUE;

	s2.x = Peak1.xEX;
	s2.y = Peak1.yEX;
	e2.x = Peak2.xEX;
	e2.y = Peak2.yEX;
	if (IsIntersected(ptStart, ptEnd, s2, e2))
		return TRUE;

	s2.x = Peak2.xEX;
	s2.y = Peak2.yEX;
	e2.x = Peak3.xEX;
	e2.y = Peak3.yEX;
	if (IsIntersected(ptStart, ptEnd, s2, e2))
		return TRUE;

	s2.x = Peak0.xEX;
	s2.y = Peak0.yEX;
	e2.x = Peak3.xEX;
	e2.y = Peak3.yEX;
	if (IsIntersected(ptStart, ptEnd, s2, e2))
		return TRUE;

	return FALSE;
}

void USVView::calculate_forbidThisDimA()//��ά�ϵ��ϰ������ǣ������һά��Ŀ���Ľ���ǣ��ڴ��󣬿�ʡ�ԣ���������������������
{	
	for (int j = 0; j < allp; j++)
	{
		if (SObsticle_num[j].form == 1)//Բ���ϰ���ı�ά�ϰ�������
		{
			int i = SObsticle_num[j].num;

			float Atemp, Amin, Amax;

			//float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
			//pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa + pa_SG;

			Atemp = asin((safe_expandT + staticoc[i].r / 2) / staticoc[i].pm);
			Amin = staticoc[i].pa - Atemp;
			Amax = staticoc[i].pa + Atemp;//��ʼ��
			if ((Amin<0) & (Amax>0))//δ�����X��Ľ�����ֿ������ж�(forbidA[i].max>forbidA[i].min)����Ϊ����Ϊ�����X���������ֿ�Ϊ��forbidA[i].min,2*pi����0,forbidA[i].max��
			{
				forbidThisDimA[j].min = staticoc[i].pa - Atemp + 2 * pi;
				forbidThisDimA[j].max = staticoc[i].pa + Atemp;
			}
			else if ((Amax>2 * pi) & (pi<Amin)&(Amin<2 * pi))
			{
				forbidThisDimA[j].min = staticoc[i].pa - Atemp;
				forbidThisDimA[j].max = staticoc[i].pa + Atemp - 2 * pi;
			}
			else
			{
				forbidThisDimA[j].min = staticoc[i].pa - Atemp;
				forbidThisDimA[j].max = staticoc[i].pa + Atemp;
			}

		}
		else if (SObsticle_num[j].form == 2)//�����ϰ���ı�ά�ϰ�������
		{
			int m = SObsticle_num[j].num;
			int n = SObsticle_num[j].rcnum;

			float pa, pb;
			if (staticor[m].Peak[1].PmEX <= staticor[m].Peak[3].PmEX)//P0P3���ϣ�P1P2����
			{
				//POP3��max
				if (n==3)
				{
					forbidThisDimA[j].max = staticor[m].Peak[3].PaEX;
				}
				else
				{
					pb = atan((staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX) - staticor[m].Peak[3].PmEX * cos(staticor[m].Peak[3].PaEX))
						/ (staticor[m].Peak[0].PmEX * sin(staticor[m].Peak[0].PaEX) - staticor[m].Peak[3].PmEX * sin(staticor[m].Peak[3].PaEX)));
					pa = staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX + pb);

					if (pb <= 0)//ֱ�߽�������
					{
						forbidThisDimA[j].max = (-acos(pa / SObsticle_num[j].pm) - pb);
					}
					else//ֱ�߽�������
					{
						forbidThisDimA[j].max = (acos(pa / SObsticle_num[j].pm) - pb);
					}
					if (forbidThisDimA[j].max < 0)
					{
						forbidThisDimA[j].max = forbidThisDimA[j].max + 2 * pi;
					}
				}
				
				//P1P2��min
				if (n == 1)
				{
					forbidThisDimA[j].min = staticor[m].Peak[1].PaEX;
				}
				else
				{
					pb = atan((staticor[m].Peak[1].PmEX * cos(staticor[m].Peak[1].PaEX) - staticor[m].Peak[2].PmEX * cos(staticor[m].Peak[2].PaEX))
						/ (staticor[m].Peak[1].PmEX * sin(staticor[m].Peak[1].PaEX) - staticor[m].Peak[2].PmEX * sin(staticor[m].Peak[2].PaEX)));
					pa = staticor[m].Peak[1].PmEX * cos(staticor[m].Peak[1].PaEX + pb);

					if (pb <= 0)//ֱ�߽�������
					{
						forbidThisDimA[j].min = (-acos(pa / SObsticle_num[j].pm) - pb);
					}
					else//ֱ�߽�������
					{
						forbidThisDimA[j].min = (acos(pa / SObsticle_num[j].pm) - pb);
					}
					if (forbidThisDimA[j].min < 0)
					{
						forbidThisDimA[j].min = forbidThisDimA[j].min + 2 * pi;
					}
				}
			}
			else//P2P3���ϣ�P0P1����
			{
				//P2P3��max
				if (n == 3)
				{
					forbidThisDimA[j].max = staticor[m].Peak[3].PaEX;
				}
				else
				{
					pb = atan((staticor[m].Peak[2].PmEX * cos(staticor[m].Peak[2].PaEX) - staticor[m].Peak[3].PmEX * cos(staticor[m].Peak[3].PaEX))
						/ (staticor[m].Peak[2].PmEX * sin(staticor[m].Peak[2].PaEX) - staticor[m].Peak[3].PmEX * sin(staticor[m].Peak[3].PaEX)));
					pa = staticor[m].Peak[2].PmEX * cos(staticor[m].Peak[2].PaEX + pb);

					if (pb <= 0)//ֱ�߽�������
					{
						forbidThisDimA[j].max = (-acos(pa / SObsticle_num[j].pm) - pb);
					}
					else//ֱ�߽�������
					{
						forbidThisDimA[j].max = (acos(pa / SObsticle_num[j].pm) - pb);
					}
					if (forbidThisDimA[j].max < 0)
					{
						forbidThisDimA[j].max = forbidThisDimA[j].max + 2 * pi;
					}
				}

				//P0P1��min
				if (n == 1)
				{
					forbidThisDimA[j].min = staticor[m].Peak[1].PaEX;
				}
				else
				{
					pb = atan((staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX) - staticor[m].Peak[1].PmEX * cos(staticor[m].Peak[1].PaEX))
						/ (staticor[m].Peak[0].PmEX * sin(staticor[m].Peak[0].PaEX) - staticor[m].Peak[1].PmEX * sin(staticor[m].Peak[1].PaEX)));
					pa = staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX + pb);

					if (pb <= 0)//ֱ�߽�������
					{
						forbidThisDimA[j].min = (-acos(pa / SObsticle_num[j].pm) - pb);
					}
					else//ֱ�߽�������
					{
						forbidThisDimA[j].min = (acos(pa / SObsticle_num[j].pm) - pb);
					}
					if (forbidThisDimA[j].min < 0)
					{
						forbidThisDimA[j].min = forbidThisDimA[j].min + 2 * pi;
					}
				}
			}			
		}				
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (SObsticle_num[allp - 1].form == 1)//Բ���ϰ���Ϊ���һά�����һά��Ŀ���Ľ����
	{
		//Բ���ϰ�������һά��Ŀ���Ľ����
		float SGl, Ab, Aa, Ac, Dpo, x0, y0, Amin, Amax, Xmin, Xmax, Ymin, Ymax, b4ac_min, b4ac_max;
		Ab = staticoc[allp - 1].pa;//����ϰ�����X��ļнǣ�ֻȡcos����X��Գ�
		//�յ���ϰ���Բ��ľ���
		SGl = sqrt(pow((float)(startgoalp.gx - startgoalp.sx), 2) + pow((float)(startgoalp.gy - startgoalp.sy), 2));
		Dpo = sqrt(pow((float)SGl, 2) + pow((float)staticoc[allp - 1].pm, 2) - 2 * staticoc[allp - 1].pm*SGl*cos(Ab));
		//·�������ϰ���Բ���н�
		Ac = asin((safe_expandT + staticoc[allp - 1].r / 2) / Dpo);
		//·���㴦��Dpo��·����ԭ������߼н�
		Aa = acos((pow((float)SGl, 2) + pow((float)Dpo, 2) - pow((float)staticoc[allp - 1].pm, 2)) / (2 * SGl*Dpo));

		//·���㴦��ֱ������ϵֵ
		x0 = SGl;
		y0 = 0.0;

		//�ж�staticoc��ǰ������staticoc�ں���ȷ������Ƕ�
		if ((pi<staticoc[allp - 1].pa) & (2 * pi>staticoc[allp - 1].pa))//staticoc�ں�
		{
			Amin = Aa - Ac;
			Amax = Aa + Ac;
		}
		else//staticoc��ǰ
		{
			Amin = 0.0 - Aa - Ac;
			Amax = 0.0 - Aa + Ac;
		}

		b4ac_min = pow(2 * tan(Amin)*(y0 - tan(Amin)*x0), 2) - 4 * (1 + pow(tan(Amin), 2))*(pow(tan(Amin)*x0 - y0, 2) - pow(staticoc[allp - 1].pm, 2));
		b4ac_max = pow(2 * tan(Amax)*(y0 - tan(Amax)*x0), 2) - 4 * (1 + pow(tan(Amax), 2))*(pow(tan(Amax)*x0 - y0, 2) - pow(staticoc[allp - 1].pm, 2));
		Particle temp_calculatePA;

		if ((b4ac_min >= 0) & (b4ac_max >= 0))
		{
			Xmin = (2 * tan(Amin)*(tan(Amin)*x0 - y0) - sqrt(b4ac_min)) / (2 * (1 + pow(tan(Amin), 2)));
			Ymin = tan(Amin)*(Xmin - x0) + y0;
			forbidThisDimA[allp].min = temp_calculatePA.calculatePA(Xmin, Ymin);//Сֵ�����1

			Xmax = (2 * tan(Amax)*(tan(Amax)*x0 - y0) - sqrt(b4ac_max)) / (2 * (1 + pow(tan(Amax), 2)));
			Ymax = tan(Amax)*(Xmax - x0) + y0;
			forbidThisDimA[allp].max = temp_calculatePA.calculatePA(Xmax, Ymax);//��ֵ�����1

			Xmin = (2 * tan(Amin)*(tan(Amin)*x0 - y0) + sqrt(b4ac_min)) / (2 * (1 + pow(tan(Amin), 2)));
			Ymin = tan(Amin)*(Xmin - x0) + y0;
			forbidThisDimA[allp + 1].max = temp_calculatePA.calculatePA(Xmin, Ymin);//��ֵ�����2

			Xmax = (2 * tan(Amax)*(tan(Amax)*x0 - y0) + sqrt(b4ac_max)) / (2 * (1 + pow(tan(Amax), 2)));
			Ymax = tan(Amax)*(Xmax - x0) + y0;
			forbidThisDimA[allp + 1].min = temp_calculatePA.calculatePA(Xmax, Ymax);//Сֵ�����2
		}
		else if ((b4ac_min < 0) & (b4ac_max >= 0))
		{
			Xmax = (2 * tan(Amax)*(tan(Amax)*x0 - y0) - sqrt(b4ac_max)) / (2 * (1 + pow(tan(Amax), 2)));
			Ymax = tan(Amax)*(Xmax - x0) + y0;
			forbidThisDimA[allp].max = temp_calculatePA.calculatePA(Xmax, Ymax);//��ֵ�����1
			forbidThisDimA[allp].min = staticoc[allp - 1].pa;//Сֵ�����1

			forbidThisDimA[allp + 1].min = staticoc[allp - 1].pa;//Сֵ�����2
			forbidThisDimA[allp + 1].max = staticoc[allp - 1].pa;//��ֵ�����2
		}
		else if ((b4ac_min >= 0) & (b4ac_max < 0))
		{
			Xmin = (2 * tan(Amin)*(tan(Amin)*x0 - y0) - sqrt(b4ac_min)) / (2 * (1 + pow(tan(Amin), 2)));
			Ymin = tan(Amin)*(Xmin - x0) + y0;
			forbidThisDimA[allp].min = temp_calculatePA.calculatePA(Xmin, Ymin);//Сֵ�����1
			forbidThisDimA[allp].max = staticoc[allp - 1].pa;//��ֵ�����1

			forbidThisDimA[allp + 1].min = staticoc[allp - 1].pa;//Сֵ�����2
			forbidThisDimA[allp + 1].max = staticoc[allp - 1].pa;//��ֵ�����2
		}
	}
	else if (SObsticle_num[allp - 1].form == 2)//�����ϰ���Ϊ���һά�����һά��Ŀ���Ľ����
	{
		int m = SObsticle_num[allp - 1].num;
		int n = SObsticle_num[allp - 1].rcnum;
		SetStaticObstacleRectangle Rectangle;
		PointInRC pointInRC;
		pointInRC = Rectangle.calculate_pointInRC(staticor[m].Peak[0], staticor[m].Peak[1], staticor[m].Peak[2], staticor[m].Peak[3], (float)startgoalp.gx, (float)startgoalp.gy);
		
		float pb, pa;

		//min
		pb = atan((staticor[m].Peak[pointInRC.min].PmEX * cos(staticor[m].Peak[pointInRC.min].PaEX) - abs ((float)(startgoalp.gx-startgoalp.sx)) )
			/ (staticor[m].Peak[pointInRC.min].PmEX * sin(staticor[m].Peak[pointInRC.min].PaEX)));
		pa = staticor[m].Peak[pointInRC.min].PmEX * cos(staticor[m].Peak[pointInRC.min].PaEX + pb);
		
		if ((pa / SObsticle_num[allp - 1].pm)<=1)
		{
			if (pb <= 0)//ֱ�߽�������
			{
				forbidThisDimA[allp].max = (-acos(pa / SObsticle_num[allp - 1].pm) - pb);//����Ŀ�����Ľ����
				forbidThisDimA[allp+1].min = (acos(pa / SObsticle_num[allp - 1].pm) - pb);//����Ŀ���Զ�Ľ����
			}
			else//ֱ�߽�������
			{
				forbidThisDimA[allp].max = (acos(pa / SObsticle_num[allp - 1].pm) - pb);
				forbidThisDimA[allp+1].min = (-acos(pa / SObsticle_num[allp - 1].pm) - pb);
			}
			if (forbidThisDimA[allp].max < 0)
			{
				forbidThisDimA[allp].max = forbidThisDimA[allp].max + 2 * pi;
			}
			if (forbidThisDimA[allp+1].min < 0)
			{
				forbidThisDimA[allp + 1].min = forbidThisDimA[allp + 1].min + 2 * pi;
			}
			
			if (staticor[m].Peak[pointInRC.min].PaEX<=pi)
			{
				if (forbidThisDimA[allp].max<=staticor[m].Peak[pointInRC.min].PaEX)//�����յ�ͽڵ�֮�䣬������˽�����
				{
					forbidThisDimA[allp].max = staticor[m].CenterPa;
				}				
			}
			else
			{
				if (forbidThisDimA[allp].max >= staticor[m].Peak[pointInRC.min].PaEX)//�����յ�ͽڵ�֮�䣬������˽�����
				{
					forbidThisDimA[allp].max = staticor[m].CenterPa;
				}
			}

			if (pointInRC.point>4)//������ĸ����⣬���ڶ��㴦����ֹ�������
			{
				forbidThisDimA[allp].max = staticor[m].CenterPa;
				forbidThisDimA[allp].min = staticor[m].CenterPa;
			}
		}
		else
		{
			forbidThisDimA[allp].max = staticor[m].CenterPa;//����Ŀ�����Ľ����
			forbidThisDimA[allp + 1].min = staticor[m].CenterPa;//����Ŀ���Զ�Ľ����
		}
			
		//max
		pb = atan((staticor[m].Peak[pointInRC.max].PmEX * cos(staticor[m].Peak[pointInRC.max].PaEX) - abs((float)(startgoalp.gx - startgoalp.sx)))
			/ (staticor[m].Peak[pointInRC.max].PmEX * sin(staticor[m].Peak[pointInRC.max].PaEX)));
		pa = staticor[m].Peak[pointInRC.max].PmEX * cos(staticor[m].Peak[pointInRC.max].PaEX + pb);

		if ((pa / SObsticle_num[allp - 1].pm) <= 1)
		{
			if (pb <= 0)//ֱ�߽�������
			{
				forbidThisDimA[allp].min = (-acos(pa / SObsticle_num[allp - 1].pm) - pb);//����Ŀ�����Ľ����
				forbidThisDimA[allp + 1].max = (acos(pa / SObsticle_num[allp - 1].pm) - pb);//����Ŀ���Զ�Ľ����
			}
			else//ֱ�߽�������
			{
				forbidThisDimA[allp].min = (acos(pa / SObsticle_num[allp - 1].pm) - pb);
				forbidThisDimA[allp + 1].max = (-acos(pa / SObsticle_num[allp - 1].pm) - pb);
			}
			if (forbidThisDimA[allp].min < 0)
			{
				forbidThisDimA[allp].min = forbidThisDimA[allp].min + 2 * pi;
			}
			if (forbidThisDimA[allp + 1].max < 0)
			{
				forbidThisDimA[allp + 1].max = forbidThisDimA[allp + 1].max + 2 * pi;
			}

			if (staticor[m].Peak[pointInRC.max].PaEX <= pi)
			{
				if (forbidThisDimA[allp].min <= staticor[m].Peak[pointInRC.max].PaEX)//�����յ�ͽڵ�֮�䣬������˽�����
				{
					forbidThisDimA[allp].min = staticor[m].CenterPa;
				}
			}
			else
			{
				if (forbidThisDimA[allp].min >= staticor[m].Peak[pointInRC.max].PaEX)//�����յ�ͽڵ�֮�䣬������˽�����
				{
					forbidThisDimA[allp].min = staticor[m].CenterPa;
				}
			}

			if (pointInRC.point>4)//������ĸ����⣬���ڶ��㴦����ֹ�������
			{
				forbidThisDimA[allp].max = staticor[m].CenterPa;
				forbidThisDimA[allp].min = staticor[m].CenterPa;
			}
		}
		else
		{
			forbidThisDimA[allp].min = staticor[m].CenterPa;//����Ŀ�����Ľ����
			forbidThisDimA[allp + 1].max = staticor[m].CenterPa;//����Ŀ���Զ�Ľ����
		}		
	}
}

void USVView::OnDataoutput()
{
	// TODO:  �ڴ���������������
	//�����Ϊ�Ի��� ����Ҫ���� #include <Afxdlgs.h>
	CFileDialog dlg(FALSE,
		"xls",
		"FileList",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Excel �ļ�(*.xls)|*.xls||");
	dlg.m_ofn.lpstrTitle = "USV�����������Ϊ";

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
			//������1-ʼĩ��
			sSql = " CREATE TABLE ʼĩ�� ( ���X TEXT , ���Y TEXT , �յ�X TEXT , �յ�Y TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			CString stemp[4];
			stemp[0].Format("%d", startgoalp.sx);
			stemp[1].Format("%d", startgoalp.sy);
			stemp[2].Format("%d", startgoalp.gx);
			stemp[3].Format("%d", startgoalp.gy);
			strInsert = " INSERT INTO ʼĩ�� (���X , ���Y , �յ�X , �յ�Y )  VALUES ( ";
			strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "') ";
			database.ExecuteSQL(strInsert);
					
			//������2-��̬�ϰ��Բ������
			sSql = " CREATE TABLE ��̬�ϰ��Բ������ ( ��� TEXT , X���� TEXT , Y���� TEXT , ����� TEXT , ���� TEXT , ���� TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			int i = 0;
			while (staticoc[i].r != 0)
			{
				CString stemp[6];
				stemp[0].Format("%d", i + 1);
				stemp[1].Format("%d", staticoc[i].x);
				stemp[2].Format("%d", staticoc[i].y);
				stemp[3].Format("%d", staticoc[i].r);
				stemp[4].Format("%f", staticoc[i].pm);
				stemp[5].Format("%f", staticoc[i].pa);
				strInsert = " INSERT INTO ��̬�ϰ��Բ������ ( ��� , X���� , Y���� , ����� , ���� , ���� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "' , " + "'" + stemp[4] + "' , " + "'" + stemp[5] + "') ";
				database.ExecuteSQL(strInsert);
				i++;
			}

			//������2-��̬�ϰ����������
			sSql = " CREATE TABLE ��̬�ϰ���������� ( ��� TEXT , ���ĵ�X TEXT , ���ĵ�Y TEXT , �볤 TEXT , ��� TEXT , ����� TEXT ) ";			
			database.ExecuteSQL(sSql);//����Excel����ļ�
			i = 0;
			while (staticor[i].HalfL != 0)
			{
				CString stemp[6];
				stemp[0].Format("%d", i+1);
				stemp[1].Format("%d", staticor[i].CenterX);
				stemp[2].Format("%d", staticor[i].CenterY);
				stemp[3].Format("%d", staticor[i].HalfL);
				stemp[4].Format("%d", staticor[i].HalfW);
				stemp[5].Format("%f", staticor[i].Da);
				strInsert = " INSERT INTO ��̬�ϰ���������� ( ��� , ���ĵ�X , ���ĵ�Y , �볤 , ��� , ����� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "' , " + "'" + stemp[4] + "' , " + "'" + stemp[5] + "') ";
				database.ExecuteSQL(strInsert);
				i++;
			}


			//������3-����Ⱥ����
			sSql = " CREATE TABLE ����Ⱥ���� ( �������� TEXT , ������ TEXT , �����ٶ������� TEXT , ��ʼ���ٶȲ��� TEXT, �����ʱ TEXT, �����Ӧ�� TEXT, �Ż�·�� TEXT, ��Ѵ��� TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			{
				CString stemp1[8];
				stemp1[0].Format("%d", pso.PSOgenerations);
				stemp1[1].Format("%d", pso.PSOparticle_num);
				stemp1[2].Format("%d", pso.PSOsetV_numMAX);
				stemp1[3].Format("%d", pso.PSOsetInitialV);
				stemp1[4].Format("%.3f", (float)UsedTimeInMs / 1000.0);
				stemp1[5].Format("%.3f", gbestFitness);
				stemp1[6].Format("%.3f", gbestFitness_OptimizePATH);
				stemp1[7].Format("%d", bestIndex+1);
				
				strInsert = " INSERT INTO ����Ⱥ���� ( �������� , ������ , �����ٶ������� , ��ʼ���ٶȲ��� , �����ʱ , �����Ӧ�� , �Ż�·��, ��Ѵ��� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp1[0] + "' , " + "'" + stemp1[1] + "' , " + "'" + stemp1[2] + "' , " + "'" + stemp1[3] + "' , " + "'" + stemp1[4] + "' , "
					+ "'" + stemp1[5] + "' , " + "'" + stemp1[6] + "' , " + "'" + stemp1[7] + "') ";
				database.ExecuteSQL(strInsert);
			}
			
			//������4-·���ڵ�
			sSql = " CREATE TABLE ·���ڵ� ( ·���� TEXT , ���� TEXT , ���� TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			for (int i = 0; i < allp; i++)
			{
				CString stemp[3];
				stemp[0].Format("%d", i + 1);
				stemp[1].Format("%.3f", gpathBest[i].GeneralP.pm);
				stemp[2].Format("%.3f", gpathBest[i].GeneralP.pa);

				strInsert = " INSERT INTO ·���ڵ� ( ·���� , ���� , ���� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "') ";
				database.ExecuteSQL(strInsert);
			}
			
			//������5-��������
			sSql = " CREATE TABLE �������� ( ��� TEXT , �������� TEXT , ������ TEXT , �����ٶ������� TEXT , ��ʼ���ٶȲ��� TEXT, �����ʱ TEXT, �����Ӧ�� TEXT, �Ż�·�� TEXT, ��Ѵ��� TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			for (int k = 0; k < testNum; k++)
			{
				CString stemp1[9];
				stemp1[0].Format("%d", best_eachGenerations[k].thisPSOnum);
				stemp1[1].Format("%d", best_eachGenerations[k].PSOgenerations);
				stemp1[2].Format("%d", best_eachGenerations[k].PSOparticle_num);
				stemp1[3].Format("%d", best_eachGenerations[k].PSOsetV_numMAX);
				stemp1[4].Format("%d", best_eachGenerations[k].PSOsetInitialV);
				stemp1[5].Format("%.3f", best_eachGenerations[k].UsedTime);
				stemp1[6].Format("%.3f", best_eachGenerations[k].bestFitness);
				stemp1[7].Format("%.3f", best_eachGenerations[k].gbestFitness_OptimizePATH);
				stemp1[8].Format("%d", best_eachGenerations[k].bestFitness_num);

				strInsert = " INSERT INTO �������� ( ��� , �������� , ������ , �����ٶ������� , ��ʼ���ٶȲ��� , �����ʱ , �����Ӧ�� , �Ż�·�� , ��Ѵ��� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp1[0] + "' , " + "'" + stemp1[1] + "' , " + "'" + stemp1[2] + "' , " + "'" + stemp1[3] + "' , " + "'" + stemp1[4] + "' , "
					+ "'" + stemp1[5] + "' , " + "'" + stemp1[6] + "' , " + "'" + stemp1[7] + "' , " + "'" + stemp1[8] + "') ";
				database.ExecuteSQL(strInsert);
			}

			//������6-ÿ�������Ӧ������
			sSql = " CREATE TABLE ÿ�������Ӧ������ ( ���� TEXT , ��Ӧ��ֵ TEXT ) ";			
			database.ExecuteSQL(sSql);//����Excel����ļ�
			for (int k = 0; k < pso.PSOgenerations; k++)
			{
				CString stemp[2];
				stemp[0].Format("%d", (int)bestFitness_list[k].num);
				stemp[1].Format("%f", bestFitness_list[k].bestFitness);

				strInsert = " INSERT INTO ÿ�������Ӧ������ ( ���� , ��Ӧ��ֵ )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "') ";
				database.ExecuteSQL(strInsert);
			}

			//������7-��̬��֪�ϰ��Բ������
			sSql = " CREATE TABLE ��̬�ϰ��Բ������ ( ��� TEXT , X���� TEXT , Y���� TEXT , ����� TEXT , ����� TEXT ,�ٶ� TEXT , ���� TEXT , ���� TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			i = 0;
			while (dynamicoc[i].r != 0)
			{
				CString stemp[8];
				stemp[0].Format("%d", i + 1);
				stemp[1].Format("%d", dynamicoc[i].x);
				stemp[2].Format("%d", dynamicoc[i].y);
				stemp[3].Format("%d", dynamicoc[i].r);
				stemp[4].Format("%f", dynamicoc[i].Da);
				stemp[5].Format("%f", dynamicoc[i].V);
				stemp[6].Format("%f", dynamicoc[i].pm);
				stemp[7].Format("%f", dynamicoc[i].pa);
				strInsert = " INSERT INTO ��̬�ϰ��Բ������ ( ��� , X���� , Y���� , ����� , �����, �ٶ� , ���� , ���� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "' , " + "'" + stemp[4] + "' , " + "'" + stemp[5] + "' , " + "'" + stemp[6] + "' , " + "'" + stemp[7] + "') ";
				database.ExecuteSQL(strInsert);
				i++;
			}


			//������8-��̬��֪�ϰ����������
			sSql = " CREATE TABLE ��̬�ϰ���������� ( ��� TEXT , ���ĵ�X TEXT , ���ĵ�Y TEXT , �볤 TEXT , ��� TEXT , ����� TEXT , �ٶ� TEXT) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			i = 0;
			while (dynamicor[i].HalfL != 0)
			{
				CString stemp[7];
				stemp[0].Format("%d", i + 1);
				stemp[1].Format("%d", dynamicor[i].CenterX);
				stemp[2].Format("%d", dynamicor[i].CenterY);
				stemp[3].Format("%d", dynamicor[i].HalfL);
				stemp[4].Format("%d", dynamicor[i].HalfW);
				stemp[5].Format("%f", dynamicor[i].Da);
				stemp[6].Format("%f", dynamicor[i].V);
				strInsert = " INSERT INTO ��̬�ϰ���������� ( ��� , ���ĵ�X , ���ĵ�Y , �볤 , ��� , ����� , �ٶ� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "' , " + "'" + stemp[4] + "' , " + "'" + stemp[5] + "' , " + "'" + stemp[6] + "') ";
				database.ExecuteSQL(strInsert);
				i++;
			}

			//������8-��̬δ֪�ϰ��Բ������
			sSql = " CREATE TABLE δ֪�ϰ��Բ������ ( ��� TEXT , X���� TEXT , Y���� TEXT , ����� TEXT , ����� TEXT ,�ٶ� TEXT , ���� TEXT , ���� TEXT ) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			i = 0;
			while (unknownoc[i].r != 0)
			{
				CString stemp[8];
				stemp[0].Format("%d", i + 1);
				stemp[1].Format("%d", unknownoc[i].x);
				stemp[2].Format("%d", unknownoc[i].y);
				stemp[3].Format("%d", unknownoc[i].r);
				stemp[4].Format("%f", unknownoc[i].Da);
				stemp[5].Format("%f", unknownoc[i].V);
				stemp[6].Format("%f", unknownoc[i].pm);
				stemp[7].Format("%f", unknownoc[i].pa);
				strInsert = " INSERT INTO δ֪�ϰ��Բ������ ( ��� , X���� , Y���� , ����� , �����, �ٶ� , ���� , ���� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "' , " + "'" + stemp[4] + "' , " + "'" + stemp[5] + "' , " + "'" + stemp[6] + "' , " + "'" + stemp[7] + "') ";
				database.ExecuteSQL(strInsert);
				i++;
			}


			//������9-��̬δ֪�ϰ����������
			sSql = " CREATE TABLE δ֪�ϰ���������� ( ��� TEXT , ���ĵ�X TEXT , ���ĵ�Y TEXT , �볤 TEXT , ��� TEXT , ����� TEXT , �ٶ� TEXT) ";
			database.ExecuteSQL(sSql);//����Excel����ļ�
			i = 0;
			while (unknownor[i].HalfL != 0)
			{
				CString stemp[7];
				stemp[0].Format("%d", i + 1);
				stemp[1].Format("%d", unknownor[i].CenterX);
				stemp[2].Format("%d", unknownor[i].CenterY);
				stemp[3].Format("%d", unknownor[i].HalfL);
				stemp[4].Format("%d", unknownor[i].HalfW);
				stemp[5].Format("%f", unknownor[i].Da);
				stemp[6].Format("%f", unknownor[i].V);
				strInsert = " INSERT INTO δ֪�ϰ���������� ( ��� , ���ĵ�X , ���ĵ�Y , �볤 , ��� , ����� , �ٶ� )  VALUES ( ";
				strInsert = strInsert + "'" + stemp[0] + "' , " + "'" + stemp[1] + "' , " + "'" + stemp[2] + "' , " + "'" + stemp[3] + "' , " + "'" + stemp[4] + "' , " + "'" + stemp[5] + "' , " + "'" + stemp[6] + "') ";
				database.ExecuteSQL(strInsert);
				i++;
			}
					
		}

		// �ر�Excel����ļ�
		database.Close();

		AfxMessageBox("����USV������ΪExcel�ļ��ɹ���");
	}
	CATCH_ALL(e)
	{
		//�������ͺܶ࣬������Ҫ���б���
		AfxMessageBox("Excel�ļ�����ʧ�ܡ�");
	}
	END_CATCH_ALL;
}