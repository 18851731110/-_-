#pragma once
#include "USVDoc.h"
#include "USVView.h"

class Pathpoint
{
public:
	Pathpoint();
	Pathpoint(float pm, float pa);
	~Pathpoint();
	PolarCoordinate GeneralP;//�����
	PolarCoordinate AdditionP;//·���ڵ��ĸ��ӵ�AdditionP[3]
	PolarCoordinate AdditionS;//��ʼ�㵽һά·���ڵ�֮��ĸ��ӵ�AdditionS[3]
	
	//��һ��Ϊ·����ļ�����ϵ�µ�pa��pm������ֻ��pa��Ϊ�ӵ�ǰ�㵽��һ�����ļ����꣨�Ե�ǰ��Ϊ���㣩		
	PolarCoordinate AdditionPU[200];//��̬δ֪�ϰ���·���㣨���޶�̬��֪���ӵ㣬���д�ֵ�����ж�̬��֪���ӵ㣬���ֵΪ�ϰ�Σ�
	PolarCoordinate AdditionSU[200];//��ʼ�㵽һά·���ڵ�֮��Ķ�̬δ֪�ϰ���·���㣨���޶�̬��֪���ӵ㣬���д�ֵ�����ж�̬��֪���ӵ㣬���ֵΪ�ϰ�Σ�
	PolarCoordinate AdditionPUa[200];//��̬δ֪�ϰ���·���㣨�ж�̬��֪���ӵ㣬��ֵΪ�°�Σ�
	PolarCoordinate AdditionSUa[200];//��ʼ�㵽һά·���ڵ�֮��Ķ�̬δ֪�ϰ���·���㣨�ж�̬��֪���ӵ㣬��ֵΪ�°�Σ�
};