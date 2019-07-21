#include "stdafx.h"
#include "Particle.h"
#include "USVDoc.h"
#include "USVView.h"
#include "math.h"
#include "float.h"
#include "SetStaticObstacleRectangle.h"

float Particle::PMmax = 1443.0f;   //1200*800�Խ����1442.22  
float Particle::PMmin = 0.0f;
float Particle::Vmax = PMmax - PMmin;  //ͨ������Vmax=Xmax-Xmin;    
float Particle::Vmin = 0 - Vmax;

float Particle::c1 = 2.0f;
float Particle::c2 = 2.0f;

int Particle::BasicP_num = 0;

extern StartGoalPOINT startgoalp;

extern StaticOC staticoc[20];

ForbidA forbidA[20]{};//�����
extern ForbidA forbidThisDimA[20];//��ά�����
//extern ForbidA forbidThisRcDimA[20];//���α�ά�����

extern PSO pso;//����Ⱥ����

extern StaticOR staticor[20];

extern SOBSTICLE SObsticle_num[30];//�ϰ������飬һάΪ��ά�ȼ������򣬶�άΪ��Բ�жϣ�1ΪԲ��2Ϊ�������ڸ��ϰ�������Ĵ���0��ʼ��

Particle::Particle()
{
	for (int i = 0; i < 50; i++)
	{
		pathpoint[i].AdditionP = {};
		pathpoint[i].AdditionS = {};
		pathpointBest[i].AdditionP = {};
		pathpointBest[i].AdditionS = {};
		for (int j = 0; j < 200; j++)
		{
			pathpoint[i].AdditionPU[j] = {};
			pathpoint[i].AdditionPUa[j] = {};
			pathpoint[i].AdditionSU[j] = {};
			pathpoint[i].AdditionSUa[j] = {};

			pathpointBest[i].AdditionPU[j] = {};
			pathpointBest[i].AdditionPUa[j] = {};
			pathpointBest[i].AdditionSU[j] = {};
			pathpointBest[i].AdditionSUa[j] = {};
		}
	}
}


Particle::~Particle()
{
}

void Particle::set_BasicP_num(int m)
{
	BasicP_num = m;
}

int Particle::get_BasicP_num()const
{
	return BasicP_num;
}

void Particle::set_pathpoint()
{	
	for (int i = 0; i < BasicP_num; i++)//��ʼ��������·����ļ��������ϰ���һ�����ѹ̶��������ǣ����ֵ�����Ͻ�����
	{
		pathpoint[i].GeneralP.pm = SObsticle_num[i].pm;//��ʼ������

		calculate_forbidA(i);//��̬���������

		int flag = 0;
		int set_num = 0;
		do
		{
			//pathpoint[i].GeneralP.pa = (rand() / (float)RAND_MAX) * 2 * pi;
			pathpoint[i].GeneralP.pa = NormalRandom(0, (pi / 2), (-pi), pi);//��̬�ֲ�������ʼ��
			if (pathpoint[i].GeneralP.pa < 0)
			{
				pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa + 2 * pi;
			}

			//float pa_SG = atan(float(((float)startgoalp.gy - (float)startgoalp.sy) / ((float)startgoalp.gx - (float)startgoalp.sx)));//ʼĩ�����߽Ƕ�
			//pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa + pa_SG;

			flag = judge_PATH_effectivity(i);//�ж�·�����Ƿ����Ҫ�󣬲�����Ҫ��Ϊ1

			set_num++;
			if (set_num >= pso.PSOsetV_numMAX)
			{
				flag = 2;
			}
		} while (flag == 1);
		
		if (flag == 2)//����ʼ�����������pso.PSOsetV_numMAX���򷵻���һ·��ֵ����
		{
			i = i - 2;
			continue;
		}

		pathpointBest[i] = pathpoint[i];
		V[i] = 2 * pi / (float)pso.PSOsetInitialV;  // �޸�2*pi/8?(PMmax - PMmin) / 8.0f
	}

	Fitness = calculate_Fitness(pathpoint);
}

float Particle::NormalRandom(float miu, float sigma, float min, float max)//��̬�ֲ�������ʼ��1
{
	//float miu=0, sigma=pi/2, min=-pi, max=pi;//ԭΪsigma=pi/3���ĺ��֧�������ϰ�����һ��
	float x, dScope, y;
	do
	{
		x = AverageRandom(min, max);
		y = Normal(x, miu, sigma);
		dScope = AverageRandom(0, Normal(miu, miu, sigma));
	} while (dScope > y);
	return x;
}

float Particle::AverageRandom(float min, float max)//��̬�ֲ�������ʼ��2
{
	int nbRand = rand() % 10001;
	return (min + nbRand*(max - min) / 10000);
}

float Particle::Normal(float x, float miu, float sigma)//��̬�ֲ�������ʼ��3
{
	return 1.0 / sqrt(2 * 3.1416) / sigma * exp(-1 * (x - miu)*(x - miu) / (2 * sigma*sigma));
}

float Particle::calculate_Fitness(Pathpoint *pathpoint)
{
	float sg = sqrt(pow((float)abs(int(startgoalp.sx - startgoalp.gx)), 2) + pow((float)abs(int(startgoalp.sy - startgoalp.gy)), 2));
	float cg = sqrt(pow((float)pathpoint[BasicP_num-1].GeneralP.pm, 2) + pow((float)sg, 2) - 2 * sg*pathpoint[BasicP_num-1].GeneralP.pm*cos(pathpoint[BasicP_num-1].GeneralP.pa));
	float Fitness_temp;
	Fitness_temp = pathpoint[0].GeneralP.pm + cg;//�׶κ�β�ξ���

	float pa,length;
	for (int i = 0; i < BasicP_num-1; i++)
	{
		if (abs(pathpoint[i].GeneralP.pa - pathpoint[i+1].GeneralP.pa)<pi)
		{
			pa = abs(pathpoint[i].GeneralP.pa - pathpoint[i + 1].GeneralP.pa);
		}
		else
		{
			pa = 2*pi-abs(pathpoint[i].GeneralP.pa - pathpoint[i + 1].GeneralP.pa);
		}
		
		length = sqrt(pow((float)pathpoint[i].GeneralP.pm, 2) + pow((float)pathpoint[i + 1].GeneralP.pm, 2) - 2 * pathpoint[i].GeneralP.pm*pathpoint[i + 1].GeneralP.pm*cos(pa));

		Fitness_temp = Fitness_temp + length;
	}
	return Fitness_temp;
}

void Particle::set_Fitness()
{
	if (setV_num<pso.PSOsetV_numMAX)
	{
		float temp = calculate_Fitness(pathpoint);
		if (temp<Fitness)
		{
			Fitness = temp;
			for (int i = 0; i < BasicP_num; i++)
			{
				pathpointBest[i] = pathpoint[i];
			}//particle[].pathpoint[]���鸳ֵ��pathpointBest[]
		}
	}
	/*else
	{
		Fitness = FLT_MAX;//float���ֵ
	}*/
	
}

float Particle::get_Fitness()const
{
	return Fitness;
}

void Particle::setV(Pathpoint *gpathBest, float w)
{
	float r1, r2;
	//srand((int)time(NULL));
	for (int i = 0; i < BasicP_num; i++)
	{
		calculate_forbidA(i);
		//���ˣ���ά���ϰ��������������δ�������X��Ľ�����ֿ������ж�(forbidA[i].max>forbidA[i].min)��
		//��Ϊ����Ϊ���X���������ֿ�Ϊ��forbidA[i].max,2*pi����0,forbidA[i].min��
				
		bool flag = 0;
		setV_num = 0;
		
		do
		{			
			r1 = rand() / (float)RAND_MAX;
			r2 = rand() / (float)RAND_MAX;
			V[i] = w*V[i] + c1*r1*(pathpointBest[i].GeneralP.pa - pathpoint[i].GeneralP.pa) + c2*r2*(gpathBest[i].GeneralP.pa - pathpoint[i].GeneralP.pa);
			pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa + V[i];
			//paȡ��0-2*pi�м�
			if (pathpoint[i].GeneralP.pa >= 2 * pi)
				pathpoint[i].GeneralP.pa = fmod(pathpoint[i].GeneralP.pa, (float)(2 * pi));
			else if (pathpoint[i].GeneralP.pa < 0)
			{
				pathpoint[i].GeneralP.pa = fmod(pathpoint[i].GeneralP.pa, (float)(2 * pi));
				pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa + 2 * pi;
			}

			flag = judge_PATH_effectivity(i);//�ж�·�����Ƿ����Ҫ�󣬲�����Ҫ��Ϊ1

			setV_num++;
			if (setV_num >= pso.PSOsetV_numMAX)
			{
				flag = 0;
			}
		} while (flag == 1);
		
		/*if (SObsticle_num[i].form == 2)//�����ϰ���
		{
			pathpoint[i].GeneralP.pa = pathpointBest[i].GeneralP.pa;
			//pathpoint[i].GeneralP.pa = gpathBest[i].GeneralP.pa;
		}*/
		
		/*if (flag == 2)//����ʼ�����������pso.PSOsetV_numMAX���򷵻���һ·��ֵ����
		{
			i = i - 2;
			continue;
		}*/
	}	
}

void Particle::calculate_forbidA(int i)
{	
	float Ab, Aa, Ac, Dpo, x0, y0, Amin, Amax, Xmin1, Xmax1, Xmin2, Xmax2, Ymin1, Ymax1, Ymin2, Ymax2, Xmin, Xmax, Ymin, Ymax, b4ac_min, b4ac_max, Xobs_t, Yobs_t;
	for (int j = 0; j < i + 1; j++)
	{
		if (i == 0)
		{
			forbidA[i].min = forbidThisDimA[i].min;
			forbidA[i].max = forbidThisDimA[i].max;	//��USVView�����������ά�ϵ��ϰ�������
			break;
		}

		if (SObsticle_num[j].form == 1)//Բ���ϰ�����ϰ�������
		{
			int m = SObsticle_num[j].num;

			Ab = abs(staticoc[m].pa - pathpoint[i - 1].GeneralP.pa);//��һά·����ͱ����ϰ���н�
			//·������ϰ���Բ��ľ���
			Dpo = sqrt(pow((float)pathpoint[i - 1].GeneralP.pm, 2) + pow((float)staticoc[m].pm, 2) - 2 * staticoc[m].pm*pathpoint[i - 1].GeneralP.pm*cos(Ab));
			//·�������ϰ���Բ���н�
			Ac = asin((safe_expandT + staticoc[m].r / 2) / Dpo);
			//·���㴦��Dpo��·����ԭ������߼н�
			Aa = acos((pow((float)pathpoint[i - 1].GeneralP.pm, 2) + pow((float)Dpo, 2) - pow((float)staticoc[m].pm, 2)) / (2 * pathpoint[i - 1].GeneralP.pm*Dpo));
			//Aa = (pow((float)pathpoint[i - 1].GeneralP.pm, 2) + pow((float)Dpo, 2) - pow((float)staticoc[m].pm, 2)) / (2 * pathpoint[i - 1].GeneralP.pm*Dpo);

			//·���㴦��ֱ������ϵֵ
			x0 = pathpoint[i - 1].GeneralP.pm*cos(pathpoint[i - 1].GeneralP.pa);
			y0 = pathpoint[i - 1].GeneralP.pm*sin(pathpoint[i - 1].GeneralP.pa);

			if (abs(staticoc[m].pa - pathpoint[i - 1].GeneralP.pa)<pi)//�ж�path��ǰ������staticoc��ǰ����ȷ������Ƕ�
			{
				if ((pathpoint[i - 1].GeneralP.pa - staticoc[m].pa) >= 0)//path��ǰ
				{
					Amin = pathpoint[i - 1].GeneralP.pa + Aa - Ac;
					Amax = pathpoint[i - 1].GeneralP.pa + Aa + Ac;
				}
				else//path�ں�
				{
					Amin = pathpoint[i - 1].GeneralP.pa - Aa - Ac;
					Amax = pathpoint[i - 1].GeneralP.pa - Aa + Ac;
				}
			}
			else
			{
				if ((pathpoint[i - 1].GeneralP.pa - staticoc[m].pa) <= 0)//path��ǰ
				{
					Amin = pathpoint[i - 1].GeneralP.pa + Aa - Ac;
					Amax = pathpoint[i - 1].GeneralP.pa + Aa + Ac;
				}
				else//path�ں�
				{
					Amin = pathpoint[i - 1].GeneralP.pa - Aa - Ac;
					Amax = pathpoint[i - 1].GeneralP.pa - Aa + Ac;
				}
			}

			//�ϰ���������ֱ�ߵĽ����ֱ������ϵֵ  min
			Xobs_t = (staticoc[m].pm * cos(staticoc[m].pa) + tan(Amin) * staticoc[m].pm * sin(staticoc[m].pa) + tan(Amin)*(tan(Amin)*x0 - y0)) / (1 + tan(Amin)*tan(Amin));
			Yobs_t = tan(Amin)*(Xobs_t - x0) + y0;

			b4ac_min = pow(2 * tan(Amin)*(y0 - tan(Amin)*x0), 2) - 4 * (1 + pow(tan(Amin), 2))*(pow(tan(Amin)*x0 - y0, 2) - pow(pathpoint[i].GeneralP.pm, 2));
			Xmin1 = (2 * tan(Amin)*(tan(Amin)*x0 - y0) + sqrt(b4ac_min)) / (2 * (1 + pow(tan(Amin), 2)));
			Ymin1 = tan(Amin)*(Xmin1 - x0) + y0;
			Xmin2 = (2 * tan(Amin)*(tan(Amin)*x0 - y0) - sqrt(b4ac_min)) / (2 * (1 + pow(tan(Amin), 2)));
			Ymin2 = tan(Amin)*(Xmin2 - x0) + y0;
			if (((Xmin1 - Xobs_t) * (Xobs_t - x0) <0 || (Ymin1 - Yobs_t) * (Yobs_t - y0) <0) & ((Xmin2 - Xobs_t) * (Xobs_t - x0) >0 || (Ymin2 - Yobs_t) * (Yobs_t - y0)>0))
			{
				Xmin = Xmin2;
				Ymin = Ymin2;
				forbidA[j].min = calculatePA(Xmin, Ymin);//Сֵ�����
			}
			else if (((Xmin1 - Xobs_t) * (Xobs_t - x0) >0 || (Ymin1 - Yobs_t) * (Yobs_t - y0) >0) & ((Xmin2 - Xobs_t) * (Xobs_t - x0) <0 || (Ymin2 - Yobs_t) * (Yobs_t - y0)<0))
			{
				Xmin = Xmin1;
				Ymin = Ymin1;
				forbidA[j].min = calculatePA(Xmin, Ymin);//Сֵ�����
			}
			else
			{
				if (j = i)
				{
					forbidA[j].min = forbidThisDimA[i].min;//Сֵ�����
				}
				else//��Ը��ǵĽϴ��ϰ�������㷨
				{
					/*if (((x0 <= Xmin1) & (Xmin1 <= Xobs_t)) || ((Xobs_t <= Xmin1) & (Xmin1 <= x0)))
					{
						forbidA[j].min = calculatePA(Xmin1, Ymin1);//Сֵ�����
					}
					else
					{
						forbidA[j].min = calculatePA(Xmin2, Ymin2);//Сֵ�����
					}*/

					forbidA[j].min = -acos((pow(SObsticle_num[j].pm, 2) + pow((float)(staticoc[m].pm), 2) - pow((float)(staticoc[m].r + safe_expandT), 2)) / (2 * SObsticle_num[j].pm*staticoc[m].pm)) + staticoc[m].pa;
				}
			}

			//�ϰ���������ֱ�ߵĽ����ֱ������ϵֵ  max
			Xobs_t = (staticoc[m].pm * cos(staticoc[m].pa) + tan(Amax) * staticoc[m].pm * sin(staticoc[m].pa) + tan(Amax)*(tan(Amax)*x0 - y0)) / (1 + tan(Amax)*tan(Amax));
			Yobs_t = tan(Amax)*(Xobs_t - x0) + y0;

			b4ac_max = pow(2 * tan(Amax)*(y0 - tan(Amax)*x0), 2) - 4 * (1 + pow(tan(Amax), 2))*(pow(tan(Amax)*x0 - y0, 2) - pow(pathpoint[i].GeneralP.pm, 2));
			Xmax1 = (2 * tan(Amax)*(tan(Amax)*x0 - y0) + sqrt(b4ac_max)) / (2 * (1 + pow(tan(Amax), 2)));
			Ymax1 = tan(Amax)*(Xmax1 - x0) + y0;
			Xmax2 = (2 * tan(Amax)*(tan(Amax)*x0 - y0) - sqrt(b4ac_max)) / (2 * (1 + pow(tan(Amax), 2)));
			Ymax2 = tan(Amax)*(Xmax2 - x0) + y0;
			if (((Xmax1 - Xobs_t) * (Xobs_t - x0) <0 || (Ymax1 - Yobs_t) * (Yobs_t - y0) <0) & ((Xmax2 - Xobs_t) * (Xobs_t - x0) >0 || (Ymax2 - Yobs_t) * (Yobs_t - y0) >0))
			{
				Xmax = Xmax2;
				Ymax = Ymax2;
				forbidA[j].max = calculatePA(Xmax, Ymax);//��ֵ�����
			}
			else if (((Xmax1 - Xobs_t) * (Xobs_t - x0) >0 || (Ymax1 - Yobs_t) * (Yobs_t - y0) >0) & ((Xmax2 - Xobs_t) * (Xobs_t - x0) <0 || (Ymax2 - Yobs_t) * (Yobs_t - y0) <0))
			{
				Xmax = Xmax1;
				Ymax = Ymax1;
				forbidA[j].max = calculatePA(Xmax, Ymax);//��ֵ�����
			}
			else
			{
				if (j = i)
				{
					forbidA[j].max = forbidThisDimA[i].max;//��ֵ�����
				}
				else//��Ը��ǵĽϴ��ϰ�������㷨
				{
					/*if (((x0 <= Xmax1) & (Xmax1 <= Xobs_t)) || ((Xobs_t <= Xmax1) & (Xmax1 <= x0)))
					{
						forbidA[j].max = calculatePA(Xmax1, Ymax1);//��ֵ�����
					}
					else
					{
						forbidA[j].max = calculatePA(Xmax2, Ymax2);//��ֵ�����
					}*/
					forbidA[j].max = acos((pow(SObsticle_num[j].pm, 2) + pow((float)(staticoc[m].pm), 2) - pow((float)(staticoc[m].r + safe_expandT), 2)) / (2 * SObsticle_num[j].pm*staticoc[m].pm)) + staticoc[m].pa;
				}
			}			
		}
		else if (SObsticle_num[j].form == 2)//�����ϰ�����ϰ�������
		{
			int m = SObsticle_num[j].num;
			int n = SObsticle_num[j].rcnum;
			
			//·����ת��Ϊ��ʾ����ϵ�¼���
			float px, py;
			px = pathpoint[i - 1].GeneralP.pm *cos(pathpoint[i - 1].GeneralP.pa) + (float)startgoalp.sx;
			py = (float)startgoalp.sy - pathpoint[i - 1].GeneralP.pm *sin(pathpoint[i - 1].GeneralP.pa);

			SetStaticObstacleRectangle Rectangle;
			PointInRC pointInRC;
			pointInRC = Rectangle.calculate_pointInRC(staticor[m].Peak[0], staticor[m].Peak[1], staticor[m].Peak[2], staticor[m].Peak[3], px, py);

			if (pointInRC.point==5)//��ֹȥmax��minʱ  �ڴ����8.27 00��04
			{
				pointInRC.max = 0;
				pointInRC.min = 0;
			}

			float pb, pa, pa1, pa2;

			//min
			pb = atan((staticor[m].Peak[pointInRC.min].PmEX * cos(staticor[m].Peak[pointInRC.min].PaEX) - (pathpoint[i - 1].GeneralP.pm * cos(pathpoint[i - 1].GeneralP.pa)))
				/ ((staticor[m].Peak[pointInRC.min].PmEX * sin(staticor[m].Peak[pointInRC.min].PaEX)) - (pathpoint[i - 1].GeneralP.pm * sin(pathpoint[i - 1].GeneralP.pa))));
			pa = staticor[m].Peak[pointInRC.min].PmEX * cos(staticor[m].Peak[pointInRC.min].PaEX + pb);

			/*if ((pa / SObsticle_num[j].pm) <= 1)
			{
			}
			else
			{
				forbidA[j].min = staticor[m].CenterPa;//����Ŀ�����Ľ����
			}*/

			pa1 = -acos(pa / SObsticle_num[i].pm) - pb;
			pa2 = acos(pa / SObsticle_num[i].pm) - pb;
			if (pa1 < 0)
			{
				pa1 = pa1 + 2 * pi;
			}
			if (pa2 < 0)
			{
				pa2 = pa2 + 2 * pi;
			}

			//ת����������ϵ�½���
			Xmin1 = SObsticle_num[j].pm * cos(pa1);
			Ymin1 = SObsticle_num[j].pm * sin(pa1);
			Xmin2 = SObsticle_num[j].pm * cos(pa2);
			Ymin2 = SObsticle_num[j].pm * sin(pa2);
			Xobs_t = staticor[m].Peak[pointInRC.min].xEX - startgoalp.sx;
			Yobs_t = startgoalp.sy - staticor[m].Peak[pointInRC.min].yEX;
			x0 = pathpoint[i - 1].GeneralP.pm * cos(pathpoint[i - 1].GeneralP.pa);
			y0 = pathpoint[i - 1].GeneralP.pm * sin(pathpoint[i - 1].GeneralP.pa);

			if (((Xmin1 - Xobs_t) * (Xobs_t - x0) <0 || (Ymin1 - Yobs_t) * (Yobs_t - y0) <0) & ((Xmin2 - Xobs_t) * (Xobs_t - x0) >0 || (Ymin2 - Yobs_t) * (Yobs_t - y0) >0))
			{
				forbidA[j].min = pa2;//Сֵ�����
			}
			else if (((Xmin1 - Xobs_t) * (Xobs_t - x0) >0 || (Ymin1 - Yobs_t) * (Yobs_t - y0) >0) & ((Xmin2 - Xobs_t) * (Xobs_t - x0) <0 || (Ymin2 - Yobs_t) * (Yobs_t - y0) <0))
			{
				forbidA[j].min = pa1;//Сֵ�����
			}
			else
			{
				if (j = i)//�ھ��α�ά��
				{
					forbidA[j].min = forbidThisDimA[i].min;//Сֵ�����
				}
				else//���ھ��α�ά�ϣ������м��ά����
				{
					if (staticor[m].Peak[1].PmEX <= staticor[m].Peak[3].PmEX)//P0P3���ϣ�P1P2����
					{
						//P1P2��min
						pb = atan((staticor[m].Peak[1].PmEX * cos(staticor[m].Peak[1].PaEX) - staticor[m].Peak[2].PmEX * cos(staticor[m].Peak[2].PaEX))
							/ (staticor[m].Peak[1].PmEX * sin(staticor[m].Peak[1].PaEX) - staticor[m].Peak[2].PmEX * sin(staticor[m].Peak[2].PaEX)));
						pa = staticor[m].Peak[1].PmEX * cos(staticor[m].Peak[1].PaEX + pb);

						if (pb <= 0)//ֱ�߽�������
						{
							forbidA[j].min = (-acos(pa / SObsticle_num[j].pm) - pb);
						}
						else//ֱ�߽�������
						{
							forbidA[j].min = (acos(pa / SObsticle_num[j].pm) - pb);
						}
						if (forbidA[j].min < 0)
						{
							forbidA[j].min = forbidA[j].min + 2 * pi;
						}
					}
					else//P2P3���ϣ�P0P1����
					{
						//P0P1��min
						pb = atan((staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX) - staticor[m].Peak[1].PmEX * cos(staticor[m].Peak[1].PaEX))
							/ (staticor[m].Peak[0].PmEX * sin(staticor[m].Peak[0].PaEX) - staticor[m].Peak[1].PmEX * sin(staticor[m].Peak[1].PaEX)));
						pa = staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX + pb);

						if (pb <= 0)//ֱ�߽�������
						{
							forbidA[j].min = (-acos(pa / SObsticle_num[j].pm) - pb);
						}
						else//ֱ�߽�������
						{
							forbidA[j].min = (acos(pa / SObsticle_num[j].pm) - pb);
						}
						if (forbidA[j].min< 0)
						{
							forbidA[j].min = forbidA[j].min + 2 * pi;
						}						
					}
				}
			}

			//max
			pb = atan((staticor[m].Peak[pointInRC.max].PmEX * cos(staticor[m].Peak[pointInRC.max].PaEX) - (pathpoint[i - 1].GeneralP.pm * cos(pathpoint[i - 1].GeneralP.pa)))
				/ ((staticor[m].Peak[pointInRC.max].PmEX * sin(staticor[m].Peak[pointInRC.max].PaEX)) - (pathpoint[i - 1].GeneralP.pm * sin(pathpoint[i - 1].GeneralP.pa))));
			pa = staticor[m].Peak[pointInRC.max].PmEX * cos(staticor[m].Peak[pointInRC.max].PaEX + pb);

			pa1 = -acos(pa / SObsticle_num[i].pm) - pb;
			pa2 = acos(pa / SObsticle_num[i].pm) - pb;
			if (pa1 < 0)
			{
				pa1 = pa1 + 2 * pi;
			}
			if (pa2 < 0)
			{
				pa2 = pa2 + 2 * pi;
			}

			//ת����������ϵ�½���
			Xmax1 = SObsticle_num[j].pm * cos(pa1);
			Ymax1 = SObsticle_num[j].pm * sin(pa1);
			Xmax2 = SObsticle_num[j].pm * cos(pa2);
			Ymax2 = SObsticle_num[j].pm * sin(pa2);
			Xobs_t = staticor[m].Peak[pointInRC.max].xEX - startgoalp.sx;
			Yobs_t = startgoalp.sy - staticor[m].Peak[pointInRC.max].yEX;
			x0 = pathpoint[i - 1].GeneralP.pm * cos(pathpoint[i - 1].GeneralP.pa);
			y0 = pathpoint[i - 1].GeneralP.pm * sin(pathpoint[i - 1].GeneralP.pa);

			if (((Xmax1 - Xobs_t) * (Xobs_t - x0) <0 || (Ymax1 - Yobs_t) * (Yobs_t - y0) <0) & ((Xmax2 - Xobs_t) * (Xobs_t - x0) >0 || (Ymax2 - Yobs_t) * (Yobs_t - y0) >0))
			{
				forbidA[j].max = pa2;//��ֵ�����
			}
			else if (((Xmax1 - Xobs_t) * (Xobs_t - x0) >0 || (Ymax1 - Yobs_t) * (Yobs_t - y0) >0) & ((Xmax2 - Xobs_t) * (Xobs_t - x0) <0 || (Ymax2 - Yobs_t) * (Yobs_t - y0) <0))
			{
				forbidA[j].max = pa1;//��ֵ�����
			}
			else
			{
				if (j = i)//�ھ��α�ά��
				{
					forbidA[j].max = forbidThisDimA[i].max;//��ֵ�����
				}
				else//���ھ��α�ά�ϣ������м��ά����
				{
					if (staticor[m].Peak[1].PmEX <= staticor[m].Peak[3].PmEX)//P0P3���ϣ�P1P2����
					{
						//POP3��max
						pb = atan((staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX) - staticor[m].Peak[3].PmEX * cos(staticor[m].Peak[3].PaEX))
							/ (staticor[m].Peak[0].PmEX * sin(staticor[m].Peak[0].PaEX) - staticor[m].Peak[3].PmEX * sin(staticor[m].Peak[3].PaEX)));
						pa = staticor[m].Peak[0].PmEX * cos(staticor[m].Peak[0].PaEX + pb);

						if (pb <= 0)//ֱ�߽�������
						{
							forbidA[j].max = (-acos(pa / SObsticle_num[j].pm) - pb);
						}
						else//ֱ�߽�������
						{
							forbidA[j].max = (acos(pa / SObsticle_num[j].pm) - pb);
						}
						if (forbidA[j].max < 0)
						{
							forbidA[j].max = forbidA[j].max + 2 * pi;
						}
					}
					else//P2P3���ϣ�P0P1����
					{
						//P2P3��max
						pb = atan((staticor[m].Peak[2].PmEX * cos(staticor[m].Peak[2].PaEX) - staticor[m].Peak[3].PmEX * cos(staticor[m].Peak[3].PaEX))
							/ (staticor[m].Peak[2].PmEX * sin(staticor[m].Peak[2].PaEX) - staticor[m].Peak[3].PmEX * sin(staticor[m].Peak[3].PaEX)));
						pa = staticor[m].Peak[2].PmEX * cos(staticor[m].Peak[2].PaEX + pb);

						if (pb <= 0)//ֱ�߽�������
						{
							forbidA[j].max = (-acos(pa / SObsticle_num[j].pm) - pb);
						}
						else//ֱ�߽�������
						{
							forbidA[j].max = (acos(pa / SObsticle_num[j].pm) - pb);
						}
						if (forbidA[j].max< 0)
						{
							forbidA[j].max = forbidA[j].max + 2 * pi;
						}
					}
				}
			}
			
		}

		if (i == BasicP_num - 1)
		{
			forbidA[BasicP_num].min = forbidThisDimA[BasicP_num].min;
			forbidA[BasicP_num].max = forbidThisDimA[BasicP_num].max;
			forbidA[BasicP_num + 1].min = forbidThisDimA[BasicP_num + 1].min;
			forbidA[BasicP_num + 1].max = forbidThisDimA[BasicP_num + 1].max;//��USVView������������һά���յ���ϰ�������
		}
		
	}
	//���ˣ���ά���ϰ��������������δ�������X��Ľ�����ֿ������ж�(forbidA[i].max>forbidA[i].min)��
	//��Ϊ����Ϊ���X���������ֿ�Ϊ��forbidA[i].max,2*pi����0,forbidA[i].min��	
}

bool Particle::judge_PATH_effectivity(int i)
{
	bool flag = 0;

	for (int n = 0; n < i + 1; n++)
	{
		if (forbidA[n].max>=forbidA[n].min)
		{
			if ((forbidA[n].min < pathpoint[i].GeneralP.pa) & (pathpoint[i].GeneralP.pa < forbidA[n].max))
			{
				flag = 1;
				break;
			}
		}
		else
		{
			if ((forbidA[n].min < pathpoint[i].GeneralP.pa)&(pathpoint[i].GeneralP.pa < 2 * pi)
				|| ((0 <= pathpoint[i].GeneralP.pa)&(pathpoint[i].GeneralP.pa < forbidA[n].max)))
			{
				flag = 1;
				break;
			}
		}

		if (i == BasicP_num - 1)//�ж����һ�����յ�֮��Ľ����
		{
			if (forbidA[BasicP_num].max>=forbidA[BasicP_num].min)
			{
				if ((forbidA[BasicP_num].min < pathpoint[i].GeneralP.pa) & (pathpoint[i].GeneralP.pa < forbidA[BasicP_num].max))
				{
					flag = 1;
					break;
				}
			}
			else
			{
				if ((forbidA[BasicP_num].min < pathpoint[i].GeneralP.pa)&(pathpoint[i].GeneralP.pa < 2 * pi)
					|| ((0 <= pathpoint[i].GeneralP.pa)&(pathpoint[i].GeneralP.pa < forbidA[BasicP_num].max)))
				{
					flag = 1;
					break;
				}
			}

			if (forbidA[BasicP_num + 1].max>=forbidA[BasicP_num + 1].min)
			{
				if ((forbidA[BasicP_num + 1].min < pathpoint[i].GeneralP.pa) & (pathpoint[i].GeneralP.pa < forbidA[BasicP_num + 1].max))
				{
					flag = 1;
					break;
				}
			}
			else
			{
				if ((forbidA[BasicP_num + 1].min < pathpoint[i].GeneralP.pa)&(pathpoint[i].GeneralP.pa < 2 * pi)
					|| ((0 <= pathpoint[i].GeneralP.pa)&(pathpoint[i].GeneralP.pa < forbidA[BasicP_num + 1].max)))
				{
					flag = 1;
					break;
				}
			}
		}
		/*
		//·���㲻�����ϰ�����չ��Բ��
		if ( (pow(pathpoint[i].GeneralP.pm, 2) + pow(staticoc[n].pm, 2) - 2 * pathpoint[i].GeneralP.pm*staticoc[n].pm*cos(abs(pathpoint[i].GeneralP.pa - staticoc[n].pa)) )
			<= pow((float)(staticoc[n].r/2 + safe_expandT), 2))
		{
			flag = 1;
			break;
		}*/
	}

	//·���㲻�����ϰ�����չ��Բ����,��Ժ�����ϰ����Բ�򷽸����˱�ά��ά��Բ
	if (flag==0)
	{
		for (int m = 0; m < BasicP_num; m++)
		{
			if (SObsticle_num[m].form == 1)//Բ���ϰ�����ϰ�������
			{
				int j = SObsticle_num[m].num;
				if ((pow(pathpoint[i].GeneralP.pm, 2) + pow(staticoc[j].pm, 2) - 2 * pathpoint[i].GeneralP.pm*staticoc[j].pm*cos(abs(pathpoint[i].GeneralP.pa - staticoc[j].pa)))
					<= pow((float)(staticoc[j].r / 2 + safe_expandT), 2))
				{
					flag = 1;
					break;
				}
			}
			else if (SObsticle_num[m].form == 2)//�����ϰ�����ϰ�������
			{
				int j = SObsticle_num[m].num;

				//·����ת��Ϊ��ʾ����ϵ�¼���
				float px, py;
				px = pathpoint[i].GeneralP.pm *cos(pathpoint[i].GeneralP.pa) + (float)startgoalp.sx;
				py = (float)startgoalp.sy - pathpoint[i].GeneralP.pm *sin(pathpoint[i].GeneralP.pa);

				SetStaticObstacleRectangle Rectangle;
				PointInRC pointInRC;
				pointInRC = Rectangle.calculate_pointInRC(staticor[j].Peak[0], staticor[j].Peak[1], staticor[j].Peak[2], staticor[j].Peak[3], px, py);
				if (pointInRC.point == 5)
				{
					flag = 1;
					break;
				}
			}
		}
	}
		
	return flag;
}

void Particle::setV_pathpoint()//���øı��ٶȺ�ļ���
{
	/*for (int i = 0; i < BasicP_num; i++)
	{
		pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa + V[i];
		if (pathpoint[i].GeneralP.pa >= 2 * pi)
			pathpoint[i].GeneralP.pa = fmod(pathpoint[i].GeneralP.pa, (float)(2 * pi));
		else if (pathpoint[i].GeneralP.pa < 0)
			pathpoint[i].GeneralP.pa = pathpoint[i].GeneralP.pa+2 * pi;
	}*/
}

float Particle::calculatePA(float X, float Y)
{
	float forbidA;
	if (X>0)
	{
		forbidA = atan(Y/X);
		if (forbidA<0)
		{
			forbidA = forbidA + 2 * pi;
		}
	}
	else if (X<0)
	{
		forbidA = pi+atan(Y / X);
	}
	else
	{
		if (Y>0)
		{
			forbidA = pi / 2;
		}
		else if (Y<0)
		{
			forbidA = 3 * pi / 2;
		}
		else
		{
			forbidA = 0;
		}
	}
	return forbidA;
}