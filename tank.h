#include <iostream>
#include <time.h> 
#include <windows.h>
#include"date.h"
void HideCursor() {  //���ع��            
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void GoToxy(int x, int y) {  //����ƶ���X��Y��ʾ�ᡢ������
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//̹��
class Tank {
public:
    int x, y; //��������
    int Direction; //����
    int Model;  //ģ��
    int Revival; //�������
    int Num; //�з�̹�˱��  
    bool Type;   //�ҷ�̹�˴˲���Ϊ1
    bool Exist;  //���Ϊ1�������Ϊ0
}AI_tank[6], my_tank;
//�ӵ�
class Bullet {
public:
    int x, y;    //����
    int Direction;  //����
    bool Exist;  //1Ϊ���ڣ�0������
    bool Type;   //0Ϊ�з��ӵ���1Ϊ�ҷ��ӵ�
}bullet[50];
//��������
void GoToxy(int x, int y);    //����ƶ�
void HideCursor();           //���ع��

void Key();  //��������
void Init(); //��ʼ��
void Pause(); //��ͣ
void Show(); //��ӡ���
void Print_Map();  //��ӡ��ͼ
void Cheak_Game(); //�����Ϸʤ��
void GameOver();  //��Ϸ����

//̹��
void Creat_AI_T(Tank* AI_tank); //����̹��  
void Creat_My_T(Tank* my_tank);

void Move_AI_T(Tank* AI_tank);//̹���ƶ�
void Move_My_T(int turn);

void Clear_T(int x, int y);  //���̹��
void Print_T(Tank tank);  //��ӡ̹��
bool Cheak_T(Tank tank, int direction); //����ϰ�,1�谭

//�ӵ�
void Creat_AI_B(Tank* tank);  //�з�̹�˷����ӵ�
void Creat_My_B(Tank tank);//�ҷ�̹�˷����ӵ�
void Move_B(Bullet bullet[50]); //�ӵ��ƶ�
void Break_B(Bullet* bullet); //�ӵ���ײ
void Print_B(int x, int y);//��ӡ�ӵ�
void Clear_B(int x, int y); //����ӵ�
int  Cheak_B(int x, int y);  //�ӵ�ǰ�����

void Show() {       //��ӡ���   
    std::cout << "  �x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x";
    std::cout << "�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x�x\n";
    for (int i = 0; i < 48; i++) {
        std::cout << "��                                                                             ��\n";
    }
    std::cout << "  ��������������������������������������������������������������������������";
    std::cout << "��������������������������������������������������������������������������\n";
}
void Print_Map() {     // ��ӡ��ͼ   
    int Map[50][40] = {
        //map���ֵ: 0Ϊ��ͨ��½�أ�1Ϊש��6Ϊǽ��100~105Ϊ�з�̹�ˣ�200Ϊ�ҵ�̹�ˣ�
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
                std::cout << "��";
            }
            else if (map[i][j] == 6) {
                GoToxy(2 * j, i);
                std::cout << "��";
            }
    GoToxy(38, 46);
    std::cout << " ����";
    GoToxy(38, 47);
    std::cout << "���� ��";
    GoToxy(38, 48);
    std::cout << "���� ��";
}
void Cheak_Game() {
    //����̹��ȫ�������
    if (Enemy <= 0 && !AI_tank[0].Exist && !AI_tank[1].Exist && !AI_tank[2].Exist
        && !AI_tank[3].Exist && !AI_tank[4].Exist && !AI_tank[5].Exist)
        GameOver();
    if (my_tank.Revival >= L)//�Ҹ����������
        GameOver();//��Ϸ����
}
void GameOver() {
    bool home = 1;
    while (home) {
        GoToxy(37, 21);
        std::cout << "��Ϸ����!";
        if (GetAsyncKeyState(0xD) & 0x8000) {  //�س���
            system("cls");   //����
            Show();
            Init(); //��ʼ��
            break;
        }
        else if (GetAsyncKeyState(0x1B) & 0x8000)  //Esc���˳�   
            exit(0);
    }
}
void Creat_My_T(Tank* my_tank) {//�����ҵ�̹��
    my_tank->x = 15;
    my_tank->y = 47;
    my_tank->Direction = 1;
    // my_tank->Model = 0;
    my_tank->Exist = 1;
    my_tank->Type = 1;
    Print_T(*my_tank);   //��ӡ�ҵ�̹��
}
void Move_My_T(int turn) {//turnΪKey()��������ķ���ֵ
    Clear_T(my_tank.x, my_tank.y);
    my_tank.Direction = turn;
    if (Cheak_T(my_tank, my_tank.Direction))  //�ҷ�̹�˵�ǰ���������ϰ�
        switch (turn) {
        case W: my_tank.y--; break;  //��
        case S: my_tank.y++; break;  //��
        case A: my_tank.x--; break;  //��
        case D: my_tank.x++; break;  //��
        }
    Print_T(my_tank);
}
void Print_T(Tank tank) {//��ӡ
    for (int i = 0; i < 3; i++) {
        GoToxy((tank.x - 1) * 2, tank.y - 1 + i);//��̹�������������ߣ����������д�ӡ
        std::cout << Tank_Model[i][tank.Direction - 1]; //��ӡ���ǵ�ַ����ַ���ַ���
        for (int j = 0; j < 3; j++)
            if (tank.Type)//��Ϊ�ҵ�̹��
                map[tank.y + j - 1][tank.x + i - 1] = 200;
        //��map�ϵз�ֵΪ100~105,�ҷ�Ϊ200
            else
                map[tank.y + j - 1][tank.x + i - 1] = 100 + tank.Num;
        //��������ͨ��mapֵ��ȡ̹�˱��
    }
}
void Creat_AI_T(Tank* AI_tank) {
    AI_tank->x = 19 + 17 * (Pos); //posΪ̹������λ��,-1Ϊ��λ��,0Ϊ�м�,1Ϊ��,2Ϊ�ҵ�̹��λ��
    AI_tank->y = 2;
    AI_tank->Direction = 2;  //������
    AI_tank->Revival++; //�������+1
    AI_tank->Exist = 1;//����
    Pos++;
    Enemy--;
    if (Pos == 2)  //ѭ������(posֻ��Ϊ-1��0��1)
        Pos = -1;
    Print_T(*AI_tank);
    return;
}
void Move_AI_T(Tank* AI_tank) {
    if (AI_tank->Exist) {  //���� 
        Clear_T(AI_tank->x, AI_tank->y);
        if (Cheak_T(*AI_tank, AI_tank->Direction))//ǰ�����ϰ�
            switch (AI_tank->Direction) {
            case W: AI_tank->y--; break;  //��
            case S: AI_tank->y++; break;  //��
            case A: AI_tank->x--; break;  //��
            case D: AI_tank->x++; break;  //��
            }
        else {//ǰ�����ϰ� 
            for (int i = rand() % 4 + 1; i <= 4; i++)
                if (Cheak_T(*AI_tank, i)) {  //ѭ���ж�,��1��ͨ��
                    AI_tank->Direction = i;
                    break;
                }
        }
        Print_T(*AI_tank);     //��ӡ�з�̹��
    }
}
bool Cheak_T(Tank tank, int direction) {  //���̹��ǰ���ϰ�,��1Ϊ��ͨ��
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
void Clear_T(int x, int y) {   //���̹��
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++) {//��̹��ռ�õĵ�ͼ����
            map[y + j - 1][x + i - 1] = 0;
            GoToxy(2 * x + 2 * j - 2, y + i - 1);
            std::cout << "  ";
        }
}

//��������
void Key() {
    //�������Ҽ�
    if (GetAsyncKeyState('W') & 0x8000)
        Move_My_T(W);
    else if (GetAsyncKeyState('S') & 0x8000)
        Move_My_T(S);
    else if (GetAsyncKeyState('A') & 0x8000)
        Move_My_T(A);
    else if (GetAsyncKeyState('D') & 0x8000)
        Move_My_T(D);
    //�ӵ�����
    else if (GetAsyncKeyState('P') & 0x8000) {
        Creat_My_B(my_tank);
    }
    else if (GetAsyncKeyState(0x1B) & 0x8000)// Esc���˳�
        exit(0);
    else if (GetAsyncKeyState(0x20) & 0x8000)//�ո���ͣ
        Pause();
}
void Pause() {    //��ͣ
    while (1) {
        if (GetAsyncKeyState(0xD) & 0x8000) {      //�س�������  
            break;
        }
        else if (GetAsyncKeyState(0x1B) & 0x8000) //Esc���˳�   
            exit(0);
    }
}
void Creat_AI_B(Tank* tank) { //�з������ӵ�
    if (!(rand() % 10)) { //������ÿ����Ϸ��������10��֮һ�Ŀ��ܷ����ӵ�       
        Creat_My_B(*tank);
    }
}
void Creat_My_B(Tank tank) {
    switch (tank.Direction)
    {
    case W:
        bullet[B_num].x = tank.x;
        bullet[B_num].y = tank.y - 2;
        bullet[B_num].Direction = 1;//1��ʾ����
        break;
    case S:
        bullet[B_num].x = tank.x;
        bullet[B_num].y = tank.y + 2;
        bullet[B_num].Direction = 2;//2��ʾ����
        break;
    case A:
        bullet[B_num].x = tank.x - 2;
        bullet[B_num].y = tank.y;
        bullet[B_num].Direction = 3;//3��ʾ����
        break;
    case D:
        bullet[B_num].x = tank.x + 2;
        bullet[B_num].y = tank.y;
        bullet[B_num].Direction = 4;//4��ʾ����
        break;
    }
    bullet[B_num].Exist = 1; //�ӵ�����
    bullet[B_num].Type = tank.Type; //�ҷ�̹�˷�����ӵ�bullet.Type=1
    B_num++;
    if (B_num == 50) //����ӵ����������50�ţ���ô��ͷ��ʼ���
        B_num = 0;   //���ǵ���ͼ�ϲ�����ͬʱ����50���ӵ�����������Ԫ������50��
}
void Move_B(Bullet bullet[50]) {  //�ӵ��ƶ�                            
    for (int i = 0; i < 50; i++) {
        if (bullet[i].Exist) {//����ӵ�����        
            if (map[bullet[i].y][bullet[i].x] == 0) {
                Clear_B(bullet[i].x, bullet[i].y);//�ӵ���ǰλ�����ϰ���Ĩ���ӵ�ͼ��
                switch (bullet[i].Direction) {//�ӵ��䵽��һ������
                case W:(bullet[i].y)--; break;
                case S:(bullet[i].y)++; break;
                case A:(bullet[i].x)--; break;
                case D:(bullet[i].x)++; break;
                }
            }
            //�ж��ӵ���ǰλ�����
            if (map[bullet[i].y][bullet[i].x] == 0) //�ӵ��������ϰ�
                Print_B(bullet[i].x, bullet[i].y);//��ӡ
            else Break_B(&bullet[i]);     //�ӵ���ײ       
            for (int j = 0; j < 50; j++)
                //�ӵ������ײ�ж�,�����ҷ��ӵ��͵з��ӵ���ײ��ɾ��,��Ϊ���з��ӵ�������
                if (bullet[j].Exist && j != i && (bullet[i].Type || bullet[j].Type)
                    && bullet[i].x == bullet[j].x && bullet[i].y == bullet[j].y)
                {                              //ͬ���������ҷ��ӵ������ܲ�����ײ
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
    int y = bullet->y;  //�ӵ�����
    int i;
    if (map[y][x] == 1) {  //�ӵ�����ש��   
        if (bullet->Direction == A || bullet->Direction == D)
            //���ӵ��Ǻ����
            for (i = -1; i <= 1; i++)
                if (map[y + i][x] == 1) {
                    map[y + i][x] = 0;
                    GoToxy(2 * x, y + i);
                    std::cout << "  ";
                }
        if (bullet->Direction == W || bullet->Direction == S)   //�ӵ������ϻ��������ƶ���
            for (i = -1; i <= 1; i++)
                if (map[y][x + i] == 1) {  //����ӵ�����ש������Ϊש��,��ɾ��ש,�����������    
                    map[y][x + i] = 0;    //ש����
                    GoToxy(2 * (x + i), y);
                    std::cout << "  ";
                }
        bullet->Exist = 0; //�ӵ�������
    }
    else if (map[y][x] == 4 || map[y][x] == 6)  //�ӵ������߿���߲��ɴݻٷ���
        bullet->Exist = 0;
    else if (bullet->Type == 1 && map[y][x] >= 100 && map[y][x] <= 105) { //�ҷ��ӵ������˵з�̹��    
        AI_tank[(int)map[y][x] % 100].Exist = 0;
        bullet->Exist = 0;
        Clear_T(AI_tank[(int)map[y][x] % 100].x, AI_tank[(int)map[y][x] % 100].y);  //���̹��

    }
    else if (bullet->Type == 0 && map[y][x] == 200) {   //���з��ӵ������ҵ�̹��    
        my_tank.Exist = 0;
        bullet->Exist = 0;
        Clear_T(my_tank.x, my_tank.y);
        my_tank.Revival++; //�ҷ�̹�˸��������1
    }
    else if (map[y][x] == 9) { //�ӵ�������    
        bullet->Exist = 0;
        GoToxy(38, 46);      std::cout << "      ";
        GoToxy(38, 47);      std::cout << "      ";
        GoToxy(38, 48);      std::cout << "����  ";
        GameOver();
    }
}
int Cheak_B(int x, int y) {//�ӵ���ǰλ�����
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
    if (Cheak_B(x, y) == 1) {//�ӵ���ǰ�����ڿյ��� 
        std::cout << "  ";
    }
}

void Init() {      //��ʼ��
    Enemy = 24;
    my_tank.Revival = 0;  //�ҵ�̹�˸������Ϊ0
    Pos = 0;
    B_num = 0;
    Print_Map();
    Creat_My_T(&my_tank);
    for (int i = 0; i < 50; i++) {//�ӵ�
        bullet[i].Exist = 0;
    }
    for (int i = 0; i <= 5; i++) {//�з�̹��
        AI_tank[i].Revival = 0;
        AI_tank[i].Exist = 0;  //��ʼ��̹��ȫ�ǲ����ģ���Creat_AI_T()����������̹��
        AI_tank[i].Num = i;
        AI_tank[i].Type = 0;
    }
}