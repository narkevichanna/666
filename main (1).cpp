#include <iostream>
#include"TXLib.h"
#include <string>
#include <sstream>
#include <cmath>
using namespace std;
class Menu {
public:
    HDC image = txLoadImage("меню.bmp");
    void draw() {
    txBitBlt(txDC(), 0, 0, 1000, 900, image, 0, 0);
    txSetColor(TX_BLACK,7);
    txSetFillColor(RGB(105, 105, 105));
    txRectangle(390, 470, 650, 540);
    txSetColor(TX_BLACK);
    txTextOut(460, 470, "Start");
    txSelectFont("Comic Sans MS", 60);
    }
};
class Menu2 {
public:
    HDC image = txLoadImage("заново.bmp");
    void draw() {
    txBitBlt(txDC(), 0, 0, 1000, 900, image, 0, 0);
    }
};
class BackGround{
public:

    int x, y;
    HDC image1 = txLoadImage("дорога2.bmp");
    HDC image2 = txLoadImage("лева€часть.bmp");
    HDC image3 = txLoadImage("права€часть.bmp");
    BackGround(int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
    txBitBlt(txDC(),200,y,0,0, image1 ,0,0);
    txBitBlt(txDC(),200,y-799,0,0, image1 ,0,0);

    txTransparentBlt(txDC(),0,y,0,0, image2 ,0,0,TX_WHITE);
    txTransparentBlt(txDC(),0,y-799,0,0, image2 ,0,0,TX_WHITE);

    txTransparentBlt(txDC(),800,y,0,0, image3 ,0,0,TX_WHITE);
    txTransparentBlt(txDC(),800,y-799,0,0, image3 ,0,0,TX_WHITE);
    txTextOut(10, 50, "Timer:");
    txSelectFont("Tines", 50);
    txTextOut(10, 100, "Coins:");
    txSelectFont("Tines", 50);
    }

    void moved(){
        y += 7;
        if (y >= 799){
            y = 0;
        }
    }
};
class Car{
public:
    int x, y;
    HDC image = txLoadImage("основнмаш.bmp");
    Car (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image ,0,0, TX_WHITE);
    }

    void moved(){
        if(GetAsyncKeyState('A')){
            x -= 3;
        }
        if (x < 200) {
                x = 200;
            }
        if(GetAsyncKeyState('D')){
            x += 3;
        }
        if (x > 675) {
                x = 675;
            }
        if(GetAsyncKeyState('S')){
            y += 3;
        }
        if (y < 0) {
                y = 0;
            }
        if(GetAsyncKeyState('W')){
            y -= 3;
        }
        if (y > 690) {
                y = 690;
            }

    }
};

class Enemy{
public:
    int x, y;
    int image_flag;
    int speed;
    HDC image1 = txLoadImage("пр1.bmp");
    HDC image2 = txLoadImage("пр2.bmp");
    HDC image3 = txLoadImage("пр3.bmp");
    Enemy (int x,int y, int image_flag, int speed){
    this ->x=x;
    this ->y =y;
    this->image_flag = image_flag;
    this->speed = speed;
    }
    void draw(){
        if (image_flag == 1){
            txTransparentBlt(txDC(),x,y,0,0, image2 ,0,0, TX_WHITE);
        }
        if (image_flag == 2){
            txTransparentBlt(txDC(),x,y,0,0, image1 ,0,0, TX_WHITE);
        }
        if (image_flag == 3){
            txTransparentBlt(txDC(),x,y,0,0, image3 ,0,0, TX_WHITE);
        }
    }

    void moved(){
        y -= speed;

    }
};
class Monetka{
public:
    int x,y;
    HDC image = txLoadImage("монетка.bmp");
    Monetka(int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image ,0,0, TX_WHITE);
    }
};
class Game{
public:
    int scene = 0;
    BackGround bg = BackGround(-300,0);
    Car car= Car(460,650);
    double double_timer = 0;
    int int_timer;
    int int_cointimer = 0;
    int coins = 0;
    int int_lifetimer = 3;
    Enemy *pro[2];
    bool catch_coin[2];
    int coin_timer[2];

    Monetka *coin[2];
    Menu menu;
    Menu2 menu2;
    double double_deathtimer = 3;
    int int_deathtimer;
    void check(){
    if (txMouseX() >= 390 && txMouseX() <= 650 && txMouseY() >= 470 && txMouseY() <= 540 && txMouseButtons()==1 ){
        scene = 1;
    }
}
    void run(){
    txCreateWindow(1000,900);
    for(int i = 0; i < 2; i++){
        pro[i] = new Enemy (rand() % 400 + 200  + ((rand() % 150 + 100) *i), (rand() % 1300 + 1000) + i*20, rand() % 3 + 1, rand() % 6 + 3);
    }
    if (abs(pro[1]->x - pro[0]->x) < 100){
            pro[1]->x += 100;
        }
     for (int i =0; i < 2; i++){
        coin[i] = new Monetka (rand() % 300 + 200 + ((rand() % 150 + 100)*i), rand() % 600 + 50);
        catch_coin[i] = false;
        coin_timer[i] = 300;
    }
    while(true){
        if(scene == 0){
        txBegin();
        txClear();
        check();
        menu.draw();
        txEnd();
        }
        if (scene == 1){
        txBegin();
        txClear();
        bg.draw();
        double_timer += 0.01;
        //
        int_timer = double_timer;
        ostringstream str1;
        str1 << int_timer;
        string str_timer = str1.str();
        const char* char_timer = str_timer.c_str();
        txTextOut(130, 55, char_timer);
        //
        ostringstream str2;
        str2 << int_cointimer;
        string str_cointimer = str2.str();
        const char* char_cointimer = str_cointimer.c_str();
        txTextOut(130, 100, char_cointimer);
        //
        for(int i = 0; i < 2; i ++){
            if (catch_coin[i]){
                coin_timer[i] -= 1;
            }
            if (coin_timer[i] <= 0){
                    coin_timer[i] = 0;
                }
        }
        bg.moved();
        car.draw();
        car.moved();
        for (int i = 0; i < 2; i++){
            coin[i]->draw();
            if ((coin[i]->x - (car.x+50))*(coin[i]->x - (car.x+50))+(coin[i]->y - (car.y+100))*(coin[i]->y - (car.y+100)) <= 12000){
                    coin[i]->y = rand() % 10000 + 1200;
                    coin[i]->x = rand() % 400 + 200 + ((rand() % 150 + 100)*i);
                    catch_coin[i] = true;
                    int_cointimer += 1;
                    coins += 1;
            }
            if (catch_coin[i]){
                if (coin_timer[i] == 0){
                    coin[i]->y = rand() % 600 + 50 ;
                    coin[i]->x = rand() % 350 + 200 + ((rand() % 150 + 100)*i);
                    catch_coin[i] = false;
                    coin_timer[i] = 200;
                }
            }
        }
        if (coins - 5 == 0){
            if (int_lifetimer < 3){
                int_lifetimer += 1;
            }
            coins = 0;
        }
        for(int i = 0; i < 2; i++){
            pro[i]->draw();
            pro[i]->moved();

            if(pro[i]->y <= -50){
                if (i == 0){
                    pro[0]->y = (rand() % 1300 + 1000) + i*20;
                    pro[0]->x = rand() % 300 + 200  + ((rand() % 150 + 100) *i);
                    pro[0]->image_flag = rand() % 3 + 1;
                    pro[0]->speed = rand() % 6 + 3;
                }
                if (i == 1){
                    pro[1]->y = (rand() % 1300 + 1000) + i*20;
                    pro[1]->x = pro[0]->x  + ((rand() % 150 + 100) *i);
                    pro[1]->image_flag = rand() % 3 + 1;
                    pro[1]->speed = rand() % 6 + 3;
                }
            }
            if(car.x >= pro[i]->x - 100 && car.x <= pro[i]->x + 100 && car.y <= pro[i]->y + 240 && car.y >= pro[i]->y - 240){
                if (i == 0){
                    pro[0]->y = (rand() % 1300 + 1000) + i*20;
                    pro[0]->x = rand() % 300 + 200  + ((rand() % 150 + 100) *i);
                    pro[0]->image_flag = rand() % 3 + 1;
                    pro[0]->speed = rand() % 6 + 3;
                }
                if (i == 1){
                    pro[1]->y = (rand() % 1300 + 1000) + i*20;
                    pro[1]->x = pro[0]->x  + 150;
                    pro[1]->image_flag = rand() % 3 + 1;
                    pro[1]->speed = rand() % 6 + 3;
                }
                int_lifetimer -= 1;
            }
        }
        if(int_lifetimer == 0){
            scene = 2;
            double_timer = 0;
            int_cointimer = 0;
            int_lifetimer = 3;
        }
                txSetFillColor(TX_RED);
                txRectangle(750, 25, 950, 65);
                txSetFillColor(TX_GREEN);
                txRectangle(750,25,int_lifetimer*66.66+750, 65);
                ostringstream str3;
        str3 << int_lifetimer;
        string str_lifetimer = str3.str();
        const char* char_lifetimer = str_lifetimer.c_str();
        txTextOut(840, 23, char_lifetimer);
        txEnd();
        }
        if (scene == 2){
            txClear();
            menu2.draw();
            int_deathtimer = double_deathtimer;
            ostringstream str4;
            str4 << int_deathtimer;
            string str_deathtimer = str4.str();
            const char* char_deathtimer = str_deathtimer.c_str();
            txTextOut(130, 90, "¬озвращение в меню через: ");
            txTextOut(650, 90, char_deathtimer);
            double_deathtimer -= 0.01;
            if(double_deathtimer <= 0){
                scene = 0;
                double_deathtimer = 3;
            }
            txSleep(1);
        }
        }
    }
};
int main()
{
    Game game;
    game.run();
}
