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

// USVView.h : USVView ��Ľӿ�
//

#pragma once
#define pi 3.1416
#define generations 200//����Ⱥ��������
#define particle_num 100//������
#define setV_numMAX 300//�����ٶȴ������ֵ
#define drawscale 0.25//������1:4
#define safe_expand 24//��̬�ϰ��ﰲȫ���Ͳ���������������δ����
#define safe_expandT 6//��̬�ϰ��ﰲȫ���Ͳ����������������ѻ���
#define Kn_ms 0.514444//��ת��Ϊm/s

typedef struct ViewSizeDEF
{
	UINT H, W;
	bool change;
}ViewSize;

typedef struct StartGoalPOINTDEF
{
	UINT sx, sy, gx, gy;
	float v_kn, v_ms;
}StartGoalPOINT;

typedef struct StaticOCDEF
{
	unsigned int x, y, r;
	float pm;//����
	float pa;//����
}StaticOC;

typedef struct DynamicOCDEF
{
	unsigned int x, y, r;
	float pm;//����
	float pmChange;//��ײ�ǵ�ļ���
	//float paChange;//��ײ�ǵ�ļ���
	float xChange;//��ײ·�����ı��Ͻ���ת���x
	float yChange;//��ײ·�����ı��Ͻ���ת���y
	float pa;//����
	float Da;//�����
	float V;//�ٶ�
	float min;
	float max;
	float Vso;//�ϰ��usv�ϳ��ٶ�
	float Vpa;//�ϳɽǣ�usv�ٶȽ���
	float pa_vso;//�ϳ��ٶȵĽǶ�
	float a_path_DOC;//��ʱ�̶�̬�ϰ�����·�������߽Ƕ�
	float a_path;//��ʱ��·���ε����߽Ƕ�
}DynamicOC;

typedef struct defREC
{
	float x, y;//��ʾ���е�����
	float xEX, yEX;//��ʾ���еļ�����չֵ������
	float Pm;//��ʼ������ϵ�� ����
	float Pa;//��ʼ������ϵ�� ����
	float PmEX;//��ʼ������ϵ�� ������չֵ�� ����
	float PaEX;//��ʼ������ϵ�� ������չֵ�� ����
}REC;

typedef struct StaticORDEF
{
	UINT CenterX, CenterY, HalfL, HalfW;
	float CenterPm;//����
	float CenterPa;//����
	REC Peak[4];
	float Da;//�����
}StaticOR;

typedef struct DynamicORDEF
{
	UINT CenterX, CenterY, HalfL, HalfW;
	float CenterPm;//����
	float CenterPa;//����
	float pmChange;//��ײ�ǵ�ļ���
	//float paChange;//��ײ�ǵ�ļ���
	float xChange;//��ײ·�����ı��Ͻ���ת���x
	float yChange;//��ײ·�����ı��Ͻ���ת���y
	REC Peak[4];
	float Da;//�����
	float V;//�ٶ�
	float min;
	float max;
	float Vso;//�ϰ��usv�ϳ��ٶ�
	float Vpa;//�ϳɽǣ�usv�ٶȽ���
	float pa_vso;//�ϳ��ٶȵĽǶ�
	float a_path_DOC;//��ʱ�̶�̬�ϰ�����·�������߽Ƕ�
	float a_path;//��ʱ��·���ε����߽Ƕ�
}DynamicOR;

typedef struct ForbidADEF
{
	float min;
	float max;
}ForbidA;

typedef struct PSODEF
{
	int PSOgenerations;//��������
	int PSOparticle_num;//������
	int PSOsetV_numMAX;//�����ٶ�������
	int PSOsetInitialV;//��ʼ���ٶȲ���
}PSO;

typedef struct PSO_DODEF
{
	UINT PSOgenerations;//��������
	UINT PSOparticle_num;//������
	UINT WeightV;//�����ٶȱ仯Ȩ��
	UINT WeightDa;//���ýǶȱ仯Ȩ��
	bool changeWeight;//�Ƿ�ɵ�Ȩ��ֵ
}PSO_DO;

typedef struct bestFitnessLISTDEF
{
	int num;
	float bestFitness;
}bestFitnessLIST;

typedef struct bestEachGenerationsDEF
{
	int PSOgenerations;//��������
	int PSOparticle_num;//������
	int PSOsetV_numMAX;//�����ٶ�������
	int PSOsetInitialV;//��ʼ���ٶȲ���
	float UsedTime;
	int bestFitness_num;
	float bestFitness;
	float gbestFitness_OptimizePATH;
	int thisPSOnum;
}bestEachGenerations;

typedef struct SOBSTICLEDEF
{
	int form;//�ϰ�����ʽ��1ΪԲ��2Ϊ����
	int rcnum;//���ε�peak�㣨peak1��peak3��
	int num;//�ڸ��ϰ�������Ĵ���0��ʼ��
	float pm;//����ֵ
}SOBSTICLE;

typedef struct DOBSTICLEDEF
{
	int form;//�ϰ�����ʽ��1ΪԲ��2Ϊ����
	int rcnum;//���ε�peak�㣨peak1��peak3��
	int num;//�ڸ��ϰ�������Ĵ���0��ʼ��
	//float pm;//����ֵ
	int pointNum;//���ĸ�·���ڵ��	
	bool ColREG;//����������������ͨ�з���,trueΪ��࣬FALSEΪ�Ҳ�
}DOBSTICLE;

typedef struct DoCalNumDEF//��Ҫ���㶯̬�ϰ��Ĵ���
{
	int CalNum;//��Ҫ���㶯̬�ϰ��Ĵ��������ֲ��ڼ���·������
	int calnumPATH;//ÿ��·���ΰ�����̬�ϰ���ĸ���
	int startNUM;//��ʼ��λ��
	float pm;//�öμ��������ֵ
	float xChange;//��ײ·�����ı��Ͻ���ת���x
	float yChange;//��ײ·�����ı��Ͻ���ת���y
}DoCalNum;

typedef struct UnknownOCDEF
{
	unsigned int x, y, r;
	float xEX, yEX, rEX,pmEX;
	float pm;//����
	float pa;//����
	float Da;//�����
	float V;//�ٶ�
	int t;//����ʱ��
}UnknownOC;

typedef struct UnknownORDEF
{
	UINT CenterX, CenterY, HalfL, HalfW;
	float CenterPm;//����
	float CenterPa;//����
	REC Peak[4];
	float Da;//�����
	float V;//�ٶ�
	int t;//����ʱ��
}UnknownOR;

typedef struct UnknownODEF
{
	int form;//�ϰ�����ʽ��1ΪԲ��2Ϊ����
	float pm;//����	
	int pointNum;//���ĸ�·���ڵ��	
	int pointNumBOOL;//���и��ӵ㣬0�޸��ӵ㣬-1�ڵ�ǰ·����͸��ӵ�֮�䣬1Ϊ�ڸ��ӵ��·��ĩ��֮��
	int t;//����ʱ��
	float Da;//�����
	float V;//�ٶ�
	int num;//�ڸ��ϰ�������Ĵ���0��ʼ��
	int CalNum;//��Ҫ���㶯̬�ϰ��Ĵ��������ֲ��ڼ���·������
	int calnumPATH;//ÿ��·���ΰ�����̬�ϰ���ĸ���
	bool collision;//�Ƿ�������0δ����1����
	bool collisionDONE;//�Ƿ��������ײ

	float xEX, yEX, rEX;//Բ���ϰ���
	REC Peak[4];//�����ϰ���
}UnknownO;

typedef struct UnknownDEF//USV·����Ĳ���
{
	float UnknownR;//��Ұ�뾶
	float UnknownT;//���ϼ��
	float min;//��Ұ�Ƕ�Сֵ���Ե�ǰ·����ΪԲ�ģ�
	float max;//��Ұ�Ƕȴ�ֵ���Ե�ǰ·����ΪԲ�ģ�
	float x0;//��ǰx����
	float y0;//��ǰy����
	int t;//��ǰʱ��
	//int pointNum;//��ǰ·����
}Unknown;

typedef struct point_dDef
{
	float x, y;
}point_d;

typedef struct PathpointDOdef
{
	float Vchange;//�ٶȱ仯��
	float DAchange;//�Ƕȱ仯��
}PathpointDO;

typedef struct PolarCoordinatedef
{
	float pm;//����
	float pa;//����
	float v;//�ٶ�
}PolarCoordinate;

class USVView : public CView
{
protected: // �������л�����
	USVView();
	DECLARE_DYNCREATE(USVView)

// ����
public:

	USVDoc* GetDocument() const;
	//float bestFitnessLIST[generations][2];//ÿ����Ӧ��ֵ

	void DrawArrow(point_d p1, point_d p2, double theta, int length,COLORREF rgb);//����ͷ
	void DrawFillet();//����Բ��

	float calculateDOtime(int pointNum);//���㶯̬�ϰ�����·���ཻʱ����·���յ㣬���õ�ʱ��

	void calculate_forbidThisDimA();//��ά�ϵ��ϰ������ǣ������һά��Ŀ���Ľ���ǣ��ڴ��󣬿�ʡ�ԣ���������������������
	void calculate_SObsticle_num();//���㾲̬�ϰ��Բ�ͷ�����ά����Ϣ����
	void calculate_DObsticle_num();//���㶯̬�ϰ��Բ�ͷ����Ƿ���USV��ײ����Ϣ����
	void calculate_DObsticle_forbidA();//���㶯̬�ཻ�ϰ�������
	REC calculate_drChange(point_d s, point_d e, REC Peak1, REC Peak2, REC Peak3, REC Peak4);//���㶯̬�����ϰ�����·�������Զ��

	float multi(point_d p1, point_d p2, point_d p0);//��ʸ��[p0, p1], [p0, p2]�Ĳ��  
	bool IsIntersected(point_d s1, point_d e1, point_d s2, point_d e2);//�ж��߶��Ƿ��ཻ 
	bool IsLineIntersectRect(point_d ptStart, point_d ptEnd, REC Peak0, REC Peak1, REC Peak2, REC Peak3);// �ж��߶��Ƿ�������ཻ

	void calculate_unknownO();//���ϰ��ﰴ��������
	bool judge_collision(int startpoint,float L);//�ж��Ƿ�����
	void calculate_collision(int startpoint, float L, PolarCoordinate *Addition, PolarCoordinate General);//������ı���
	bool judge_so_collision(float x0, float y0, float x1, float y1, int pointNum);//�ж��Ƿ�;�̬�ϰ�������
	void drawWD(float x, float y, float pa);//����������

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~USVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCalculatePSO();
	afx_msg void OnSet_start_goal_Position();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetstaticobstaclecircle();
	afx_msg void OnCombostartgoal();
	afx_msg void OnComboSoc();
	afx_msg void OnDataoutput();
	afx_msg void OnComboPathpoint();
	afx_msg void OnBtsetpso();
//	afx_msg void OnOptimizepath();
	afx_msg void OnOptimizepath();
	afx_msg void OnCalculateandoptimize();
//	afx_msg void OnSetstaticobstaclerectangle();
	afx_msg void OnSetstaticobstaclerectangle();
	afx_msg void OnSetviewsize();
	afx_msg void OnSetdynamicOC();
	afx_msg void OnSetdynamicOR();
	afx_msg void OnComboViewinformation();
	afx_msg void OnComboDo();
	afx_msg void OnComboDoun();
	afx_msg void OnCalculatedoPso();
	afx_msg void Onsetpsodo();

	afx_msg void OnViewdo();
	afx_msg void OnSetunknownoc();
	afx_msg void OnSetunknownor();

	afx_msg void OnSetunknown();
	afx_msg void OnCalculateunknown();
};

#ifndef _DEBUG  // USVView.cpp �еĵ��԰汾
inline USVDoc* USVView::GetDocument() const
   { return reinterpret_cast<USVDoc*>(m_pDocument); }
#endif

