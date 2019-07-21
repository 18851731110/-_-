#pragma once
#include "Pathpoint.h"
#include "USVDoc.h"
#include "USVView.h"

class ParticleDO
{
public:
	ParticleDO();
	~ParticleDO();
	void set_BasicP_num(int m);
	int get_BasicP_num()const;

	void set_pathpoint();
	bool calculate_ColREG(int num);//����������������ͨ�з��� trueΪ���ͨ�У�FALSEΪ�Ҳ�ͨ��
	bool judge_PATH_effectivity();
	float calculate_2point_pa(float x1, float y1, float x2, float y2);//��������ĽǶȣ���������  1Ϊ��ʼ�� �� 2�յ�  ���ػ���ֵ
	bool calculate_1pointIN2point(float x1, float y1, float x2, float y2, float x, float y);//����һ���Ƿ���һ���߶��м䣨��Լ����ϰ���Բ���㣩
	bool calculate_1pointIN2pointLINE(float x1, float y1, float x2, float y2, float x, float y);//����һ���Ƿ���һ���߶���
	float calculate_DynamicL(Pathpoint *pathpoint);
	float calculate_Pa_02PI(float pa);//����ֵ����0-2pi�ļ���ֵ

	float multi(point_d p1, point_d p2, point_d p0);//��ʸ��[p0, p1], [p0, p2]�Ĳ��  
	bool IsIntersected(point_d s1, point_d e1, point_d s2, point_d e2);//�ж��߶��Ƿ��ཻ 
	bool IsLineIntersectRect(point_d ptStart, point_d ptEnd, REC Peak0, REC Peak1, REC Peak2, REC Peak3);// �ж��߶��Ƿ�������ཻ
	float calculate_newpointPA(float x0, float y0, float pa_v, float pm);//��������·����ļ���(ֱ�ߺ�Բ�Ľ���)
	point_d calculate_newpoint(float x0, float y0, float xChange, float yChange, float Vso, float pa_v, float Vusv);//��������·����//��ת��Ϊ��������
	point_d calculate_point_segment_circle(float x0, float y0, float x1, float y1, float r);//���㵹��ʱ(ֱ�ߺ�Բ�Ľ���)��x0��y0ͬʱΪԲ��//��ת��Ϊ��ʾ������
	float calculate_Fitness(PathpointDO pathpoint);

	void set_Fitness();
	float get_Fitness()const;
	void setV(PathpointDO *gpathBestDO, float w);

	PathpointDO pathpointBest;

private:
	PathpointDO pathpoint; //= new Pathpoint[BasicP_num];

	bool ColREG_do;//1Ϊ���к��¹�����ϣ�0Ϊ�����к��¹������

	float Fitness;  //��Ӧ��  
	static int BasicP_num;//��ά������docalNUM[z]�е�λ��
	float V[2];
	int setV_num;//�����ٶȴ���

	int pointNum;//���ĸ�·���ڵ��	
	int calnumPATH;//�ö�·���ΰ�����̬�ϰ���ĸ���
	int startNUM;//��ʼ��λ��

	static float PMmax, PMmin;
	static float Vmax, Vmin; //������������������ٶȽ������Ƶģ�������ֻ����һ���ķ�Χ�ڡ�  
	static float c1, c2; //c1,c2��ѧϰ���ӡ�  
};

