#pragma once
#include<iostream>
using namespace std;
int map[50][40];//地图二维数组
int B_num;      //子弹编号
int Pos;     //敌方坦克生成位置,-1为左边,0为中间,1为右边,2为我的坦克位置
int Speed = 7;  //游戏速度
int Enemy; //还未出现的敌人
const char* Tank_Model[3][4] = {
    {"◢┃ ◣", "◢╦ ◣", "◢╦◣", "◢╦◣"},
    {"╠ █╣", "╠ █╣", "━█╣", "╠█━"},
    {"◥╩ ◤", "◥┃ ◤", "◥╩◤", "◥╩◤"}
};
#define W 1       //上
#define S 2         //下
#define A 3         //左
#define D 4          //右
#define L 4       // 坦克有4条命