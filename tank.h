#include <iostream>
#include <time.h> 
#include <windows.h>
#include"date.h"
void HideCursor() {  //隐藏光标            
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void GoToxy(int x, int y) {  //光标移动，X、Y表示横、纵坐标
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//坦克
class Tank {
public:
    int x, y; //中心坐标
    int Direction; //方向
    int Model;  //模型
    int Revival; //复活次数
    int Num; //敌方坦克编号  
    bool Type;   //我方坦克此参数为1
    bool Exist;  //存活为1，不存活为0
}AI_tank[6], my_tank;
//子弹
class Bullet {
public:
    int x, y;    //坐标
    int Direction;  //方向
    bool Exist;  //1为存在，0不存在
    bool Type;   //0为敌方子弹，1为我方子弹
}bullet[50];
//基本函数
void GoToxy(int x, int y);    //光标移动
void HideCursor();           //隐藏光标

void Key();  //键盘输入
void Init(); //初始化
void Pause(); //暂停
void Show(); //打印框架
void Print_Map();  //打印地图
void Cheak_Game(); //检测游戏胜负
void GameOver();  //游戏结束

//坦克
void Creat_AI_T(Tank* AI_tank); //建立坦克  
void Creat_My_T(Tank* my_tank);

void Move_AI_T(Tank* AI_tank);//坦克移动
void Move_My_T(int turn);

void Clear_T(int x, int y);  //清除坦克
void Print_T(Tank tank);  //打印坦克
bool Cheak_T(Tank tank, int direction); //检测障碍,1阻碍

//子弹
void Creat_AI_B(Tank* tank);  //敌方坦克发射子弹
void Creat_My_B(Tank tank);//我方坦克发射子弹
void Move_B(Bullet bullet[50]); //子弹移动
void Break_B(Bullet* bullet); //子弹碰撞
void Print_B(int x, int y);//打印子弹
void Clear_B(int x, int y); //清除子弹
int  Cheak_B(int x, int y);  //子弹前方情况

void Show() {       //打印框架   
    std::cout << "  ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁";
    std::cout << "▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁\n";
    for (int i = 0; i < 48; i++) {
        std::cout << "▕                                                                             ▏\n";
    }
    std::cout << "  ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔";
    std::cout << "▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n";
}
void Print_Map() {     // 打印地图   
    int Map[50][40] = {
        //map里的值: 0为可通过陆地，1为砖，6为墙，100~105为敌方坦克，200为我的坦克，
               { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,4 },
               { 4,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,4 },
               { 4,6,6,6,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,6,6,6,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 },
               { 4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4 }
    };
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 40; j++)
            map[i][j] = Map[i][j];
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 40; j++)
            if (map[i][j] == 1) {
                GoToxy(2 * j, i);
                std::cout << "▓";
            }
            else if (map[i][j] == 6) {
                GoToxy(2 * j, i);
                std::cout << "■";
            }
    GoToxy(38, 46);
    std::cout << " ◣◢";
    GoToxy(38, 47);
    std::cout << "◣█ ◢";
    GoToxy(38, 48);
    std::cout << "◢█ ◣";
}
void Cheak_Game() {
    //敌人坦克全部不存活
    if (Enemy <= 0 && !AI_tank[0].Exist && !AI_tank[1].Exist && !AI_tank[2].Exist
        && !AI_tank[3].Exist && !AI_tank[4].Exist && !AI_tank[5].Exist)
        GameOver();
    if (my_tank.Revival >= L)//我复活次数用完
        GameOver();//游戏结束
}
void GameOver() {
    bool home = 1;
    while (home) {
        GoToxy(37, 21);
        std::cout << "游戏结束!";
        if (GetAsyncKeyState(0xD) & 0x8000) {  //回车键
            system("cls");   //清屏
            Show();
            Init(); //初始化
            break;
        }
        else if (GetAsyncKeyState(0x1B) & 0x8000)  //Esc键退出   
            exit(0);
    }
}
void Creat_My_T(Tank* my_tank) {//建立我的坦克
    my_tank->x = 15;
    my_tank->y = 47;
    my_tank->Direction = 1;
    // my_tank->Model = 0;
    my_tank->Exist = 1;
    my_tank->Type = 1;
    Print_T(*my_tank);   //打印我的坦克
}
void Move_My_T(int turn) {//turn为Key()函数传入的方向值
    Clear_T(my_tank.x, my_tank.y);
    my_tank.Direction = turn;
    if (Cheak_T(my_tank, my_tank.Direction))  //我方坦克当前方向上无障碍
        switch (turn) {
        case W: my_tank.y--; break;  //上
        case S: my_tank.y++; break;  //下
        case A: my_tank.x--; break;  //左
        case D: my_tank.x++; break;  //右
        }
    Print_T(my_tank);
}
void Print_T(Tank tank) {//打印
    for (int i = 0; i < 3; i++) {
        GoToxy((tank.x - 1) * 2, tank.y - 1 + i);//在坦克中心坐标的左边，上中下三行打印
        std::cout << Tank_Model[i][tank.Direction - 1]; //打印的是地址，地址既字符串
        for (int j = 0; j < 3; j++)
            if (tank.Type)//若为我的坦克
                map[tank.y + j - 1][tank.x + i - 1] = 200;
        //在map上敌方值为100~105,我方为200
            else
                map[tank.y + j - 1][tank.x + i - 1] = 100 + tank.Num;
        //这样可以通过map值读取坦克编号
    }
}
void Creat_AI_T(Tank* AI_tank) {
    AI_tank->x = 19 + 17 * (Pos); //pos为坦克生成位置,-1为左位置,0为中间,1为右,2为我的坦克位置
    AI_tank->y = 2;
    AI_tank->Direction = 2;  //方向朝下
    AI_tank->Revival++; //复活次数+1
    AI_tank->Exist = 1;//存在
    Pos++;
    Enemy--;
    if (Pos == 2)  //循环重置(pos只能为-1，0，1)
        Pos = -1;
    Print_T(*AI_tank);
    return;
}
void Move_AI_T(Tank* AI_tank) {
    if (AI_tank->Exist) {  //存在 
        Clear_T(AI_tank->x, AI_tank->y);
        if (Cheak_T(*AI_tank, AI_tank->Direction))//前方无障碍
            switch (AI_tank->Direction) {
            case W: AI_tank->y--; break;  //上
            case S: AI_tank->y++; break;  //下
            case A: AI_tank->x--; break;  //左
            case D: AI_tank->x++; break;  //右
            }
        else {//前方有障碍 
            for (int i = rand() % 4 + 1; i <= 4; i++)
                if (Cheak_T(*AI_tank, i)) {  //循环判断,返1可通过
                    AI_tank->Direction = i;
                    break;
                }
        }
        Print_T(*AI_tank);     //打印敌方坦克
    }
}
bool Cheak_T(Tank tank, int direction) {  //检测坦克前方障碍,返1为可通过
    switch (direction) {
    case W:
        if (map[tank.y - 2][tank.x] == 0 && map[tank.y - 2][tank.x - 1] == 0 && map[tank.y - 2][tank.x + 1] == 0)
            return 1;
        else return 0;
    case S:
        if (map[tank.y + 2][tank.x] == 0 && map[tank.y + 2][tank.x - 1] == 0 && map[tank.y + 2][tank.x + 1] == 0)
            return 1;
        else return 0;
    case A:
        if (map[tank.y][tank.x - 2] == 0 && map[tank.y - 1][tank.x - 2] == 0 && map[tank.y + 1][tank.x - 2] == 0)
            return 1;
        else return 0;
    case D:
        if (map[tank.y][tank.x + 2] == 0 && map[tank.y - 1][tank.x + 2] == 0 && map[tank.y + 1][tank.x + 2] == 0)
            return 1;
        else return 0;
    default: return 0;
    }
}
void Clear_T(int x, int y) {   //清除坦克
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++) {//将坦克占用的地图清零
            map[y + j - 1][x + i - 1] = 0;
            GoToxy(2 * x + 2 * j - 2, y + i - 1);
            std::cout << "  ";
        }
}

//键盘输入
void Key() {
    //上下左右键
    if (GetAsyncKeyState('W') & 0x8000)
        Move_My_T(W);
    else if (GetAsyncKeyState('S') & 0x8000)
        Move_My_T(S);
    else if (GetAsyncKeyState('A') & 0x8000)
        Move_My_T(A);
    else if (GetAsyncKeyState('D') & 0x8000)
        Move_My_T(D);
    //子弹发射
    else if (GetAsyncKeyState('P') & 0x8000) {
        Creat_My_B(my_tank);
    }
    else if (GetAsyncKeyState(0x1B) & 0x8000)// Esc键退出
        exit(0);
    else if (GetAsyncKeyState(0x20) & 0x8000)//空格暂停
        Pause();
}
void Pause() {    //暂停
    while (1) {
        if (GetAsyncKeyState(0xD) & 0x8000) {      //回车键继续  
            break;
        }
        else if (GetAsyncKeyState(0x1B) & 0x8000) //Esc键退出   
            exit(0);
    }
}
void Creat_AI_B(Tank* tank) { //敌方发射子弹
    if (!(rand() % 10)) { //在随后的每个游戏周期中有10分之一的可能发射子弹       
        Creat_My_B(*tank);
    }
}
void Creat_My_B(Tank tank) {
    switch (tank.Direction)
    {
    case W:
        bullet[B_num].x = tank.x;
        bullet[B_num].y = tank.y - 2;
        bullet[B_num].Direction = 1;//1表示向上
        break;
    case S:
        bullet[B_num].x = tank.x;
        bullet[B_num].y = tank.y + 2;
        bullet[B_num].Direction = 2;//2表示向下
        break;
    case A:
        bullet[B_num].x = tank.x - 2;
        bullet[B_num].y = tank.y;
        bullet[B_num].Direction = 3;//3表示向左
        break;
    case D:
        bullet[B_num].x = tank.x + 2;
        bullet[B_num].y = tank.y;
        bullet[B_num].Direction = 4;//4表示向右
        break;
    }
    bullet[B_num].Exist = 1; //子弹存在
    bullet[B_num].Type = tank.Type; //我方坦克发射的子弹bullet.Type=1
    B_num++;
    if (B_num == 50) //如果子弹编号增长到50号，那么重头开始编号
        B_num = 0;   //考虑到地图上不可能同时存在50颗子弹，所以数组元素设置50个
}
void Move_B(Bullet bullet[50]) {  //子弹移动                            
    for (int i = 0; i < 50; i++) {
        if (bullet[i].Exist) {//如果子弹存在        
            if (map[bullet[i].y][bullet[i].x] == 0) {
                Clear_B(bullet[i].x, bullet[i].y);//子弹当前位置无障碍，抹除子弹图形
                switch (bullet[i].Direction) {//子弹变到下一个坐标
                case W:(bullet[i].y)--; break;
                case S:(bullet[i].y)++; break;
                case A:(bullet[i].x)--; break;
                case D:(bullet[i].x)++; break;
                }
            }
            //判断子弹当前位置情况
            if (map[bullet[i].y][bullet[i].x] == 0) //子弹坐标无障碍
                Print_B(bullet[i].x, bullet[i].y);//打印
            else Break_B(&bullet[i]);     //子弹碰撞       
            for (int j = 0; j < 50; j++)
                //子弹间的碰撞判断,若是我方子弹和敌方子弹碰撞则都删除,若为两敌方子弹则无视
                if (bullet[j].Exist && j != i && (bullet[i].Type || bullet[j].Type)
                    && bullet[i].x == bullet[j].x && bullet[i].y == bullet[j].y)
                {                              //同样的两颗我方子弹不可能产生碰撞
                    bullet[j].Exist = 0;
                    bullet[i].Exist = 0;
                    Clear_B(bullet[j].x, bullet[j].y);

                    break;
                }
        }
    }
}
void Break_B(Bullet* bullet) {
    int x = bullet->x;
    int y = bullet->y;  //子弹坐标
    int i;
    if (map[y][x] == 1) {  //子弹碰到砖块   
        if (bullet->Direction == A || bullet->Direction == D)
            //若子弹是横向的
            for (i = -1; i <= 1; i++)
                if (map[y + i][x] == 1) {
                    map[y + i][x] = 0;
                    GoToxy(2 * x, y + i);
                    std::cout << "  ";
                }
        if (bullet->Direction == W || bullet->Direction == S)   //子弹是向上或是向下移动的
            for (i = -1; i <= 1; i++)
                if (map[y][x + i] == 1) {  //如果子弹打中砖块两旁为砖块,则删除砖,若不是则忽略    
                    map[y][x + i] = 0;    //砖块碎
                    GoToxy(2 * (x + i), y);
                    std::cout << "  ";
                }
        bullet->Exist = 0; //子弹不存在
    }
    else if (map[y][x] == 4 || map[y][x] == 6)  //子弹碰到边框或者不可摧毁方块
        bullet->Exist = 0;
    else if (bullet->Type == 1 && map[y][x] >= 100 && map[y][x] <= 105) { //我方子弹碰到了敌方坦克    
        AI_tank[(int)map[y][x] % 100].Exist = 0;
        bullet->Exist = 0;
        Clear_T(AI_tank[(int)map[y][x] % 100].x, AI_tank[(int)map[y][x] % 100].y);  //清除坦克

    }
    else if (bullet->Type == 0 && map[y][x] == 200) {   //若敌方子弹击中我的坦克    
        my_tank.Exist = 0;
        bullet->Exist = 0;
        Clear_T(my_tank.x, my_tank.y);
        my_tank.Revival++; //我方坦克复活次数加1
    }
    else if (map[y][x] == 9) { //子弹碰到巢    
        bullet->Exist = 0;
        GoToxy(38, 46);      std::cout << "      ";
        GoToxy(38, 47);      std::cout << "      ";
        GoToxy(38, 48);      std::cout << "◢◣  ";
        GameOver();
    }
}
int Cheak_B(int x, int y) {//子弹当前位置情况
    if (map[y][x] == 0)
        return 1;
    else
        return 0;
}
void Print_B(int x, int y) {
    GoToxy(2 * x, y);
    std::cout << "o";
}
void Clear_B(int x, int y) {
    GoToxy(2 * x, y);
    if (Cheak_B(x, y) == 1) {//子弹当前坐标在空地上 
        std::cout << "  ";
    }
}

void Init() {      //初始化
    Enemy = 24;
    my_tank.Revival = 0;  //我的坦克复活次数为0
    Pos = 0;
    B_num = 0;
    Print_Map();
    Creat_My_T(&my_tank);
    for (int i = 0; i < 50; i++) {//子弹
        bullet[i].Exist = 0;
    }
    for (int i = 0; i <= 5; i++) {//敌方坦克
        AI_tank[i].Revival = 0;
        AI_tank[i].Exist = 0;  //初始化坦克全是不存活的，用Creat_AI_T()建立不存活的坦克
        AI_tank[i].Num = i;
        AI_tank[i].Type = 0;
    }
}