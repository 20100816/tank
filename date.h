#pragma once
#include<iostream>
using namespace std;
int map[50][40];//��ͼ��ά����
int B_num;      //�ӵ����
int Pos;     //�з�̹������λ��,-1Ϊ���,0Ϊ�м�,1Ϊ�ұ�,2Ϊ�ҵ�̹��λ��
int Speed = 7;  //��Ϸ�ٶ�
int Enemy; //��δ���ֵĵ���
const char* Tank_Model[3][4] = {
    {"���� ��", "���j ��", "���j��", "���j��"},
    {"�d ���g", "�d ���g", "�����g", "�d����"},
    {"���m ��", "���� ��", "���m��", "���m��"}
};
#define W 1       //��
#define S 2         //��
#define A 3         //��
#define D 4          //��
#define L 4       // ̹����4����