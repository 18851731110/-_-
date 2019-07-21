#pragma once
#include "Pathpoint.h"

class Particle
{
public:
	Particle();
	~Particle();
	void set_BasicP_num(int m);
	int get_BasicP_num()const;

	void set_pathpoint();
	float NormalRandom(float miu, float sigma, float min, float max);//��̬�ֲ�������ʼ��
	float AverageRandom(float min, float max);
	float Normal(float x, float miu, float sigma);

	void calculate_forbidA(int i);
	bool judge_PATH_effectivity(int i);
	float calculate_Fitness(Pathpoint *pathpoint);
	void set_Fitness();
	float get_Fitness()const;

	void setV(Pathpoint *gpathBest, float w);
	void setV_pathpoint();

	float calculatePA(float X, float Y);

	Pathpoint pathpointBest[50];

private:
	Pathpoint pathpoint[50]; //= new Pathpoint[BasicP_num];

	float Fitness;  //��Ӧ��  
	static int BasicP_num;//��׼ά��
	//int Dim_num;//��ά����ת���
	float V[50];

	int setV_num;//�����ٶȴ���

	static float PMmax, PMmin;
	static float Vmax, Vmin; //������������������ٶȽ������Ƶģ�������ֻ����һ���ķ�Χ�ڡ�  
	static float c1, c2; //c1,c2��ѧϰ���ӡ�  
};

