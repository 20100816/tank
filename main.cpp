// 坦克大战.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include"tank.h"
int main() {
    int i;
    int gap[16] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };  //间隔数组，用于控制速度
    HideCursor();     //隐藏光标
    Show();      //打印框架
    Init();     //初始化
    while (1) {
        if (gap[0]++ % Speed == 0) {
            //速度调整,     
            Cheak_Game();  //游戏胜负检测
            for (i = 0; i <= 5; i++) {//敌方坦克移动循环
                if (gap[i + 7]++ % 3 == 0)
                    Move_AI_T(&AI_tank[i]);
            }
            for (i = 0; i <= 5; i++)//建立敌方坦克
                if (AI_tank[i].Exist == 0 && AI_tank[i].Revival < 4 && gap[i + 1]++ % 50 == 0) {  //一个敌方坦克每局只有4条命
                    //坦克死掉后间隔一段时间建立
                    Creat_AI_T(&AI_tank[i]);
                    break;
                }
            for (i = 0; i <= 5; i++)
                if (AI_tank[i].Exist)
                    Creat_AI_B(&AI_tank[i]);
            if (my_tank.Exist && gap[14]++ % 2 == 0)
                Key();
            if (my_tank.Exist == 0 && my_tank.Revival < L && gap[15]++ % 15 == 0)//我方坦克复活
                Creat_My_T(&my_tank);
            Move_B(bullet);
        }
        Sleep(5);
    }
    return 0;
}

