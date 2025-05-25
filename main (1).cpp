#include <iostream>
#include"TXLib.h"
#include <string>
#include <sstream>
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
    txSetColor(TX_BLACK,7);
    txSetFillColor(RGB(105, 105, 105));
    txRectangle(390, 470, 650, 540);
    txSetColor(TX_BLACK);
    txTextOut(460, 470, "Start");
    txSelectFont("Comic Sans MS", 60);
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
    txTextOut(800, 90, "Coins:");
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
    HDC image1 = txLoadImage("пр1.bmp");
    Enemy (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image1 ,0,0, TX_WHITE);
    }

    void moved(){
        y -= 3;

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
    int int_lifetimer = 3;
    Enemy *pro[2];
    bool catch_coin[2];
    int coin_timer[2];

    Monetka *coin[2];
    Menu menu;
    Menu2 menu2;
    void check(){
    if (txMouseX() >= 390 && txMouseX() <= 650 && txMouseY() >= 470 && txMouseY() <= 540 && txMouseButtons()==1 ){
        scene = 1;
    }
}
    void run(){
    txCreateWindow(1000,900);
    for(int i = 0; i < 2; i++){
        pro[i] = new Enemy ((rand() % (600- 200 + 1)+ 200) + ((rand() % (150 - 100 + 1) + 150)*i), (rand() % (1200 - 1100 + 1)+ 1100));
    }
     for (int i =0; i < 2; i++){
        coin[i] = new Monetka ((rand() % (600- 200 + 1)+ 200) + ((rand() % (150 - 100 + 1) + 150)*i), (rand() % (600 - 50 + 1)+ 50));
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
        ostringstream str3;
        str3 << int_lifetimer;
        string str_lifetimer = str3.str();
        const char* char_lifetimer = str_lifetimer.c_str();
        txTextOut(850, 55, char_lifetimer);
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
                    coin[i]->y = (rand() % (10000 - 1200 +1)+ 1200);
                    coin[i]->x = (rand() % (400- 200 + 1)+ 200) + ((rand() % (150 - 100 + 1) + 150)*i);
                    catch_coin[i] = true;
                    int_cointimer += 1;
            }
            if (catch_coin[i]){
                if (coin_timer[i] == 0){
                    coin[i]->y = (rand() % (600 - 50 +1)+ 50);
                    coin[i]->x = (rand() % (400- 200 + 1)+ 200) + ((rand() % (150 - 100 + 1) + 150)*i);
                    catch_coin[i] = false;
                    coin_timer[i] = 200;
                }
            }
        }
        for(int i = 0; i < 2; i++){
            pro[i]->draw();
            pro[i]->moved();

            if(pro[i]->y <= -50){
                pro[i]->y = (rand() % (1300 - 1000 +1)+ 1000);
                pro[i]->x = (rand() % (500- 200 + 1)+ 200) + ((rand() % (150 - 100 + 1) + 150)*i);
            }
            if(car.x >= pro[i]->x - 100 && car.x <= pro[i]->x + 100 && car.y <= pro[i]->y + 240 && car.y >= pro[i]->y - 240){
                pro[i]->y = (rand() % (1300 - 1000 +1)+ 1000);
                pro[i]->x = (rand() % (500- 200 + 1)+ 200) + ((rand() % (150 - 100 + 1) + 150)*i);
                int_lifetimer -= 1;
            }
        }
        if(int_lifetimer == 0){
            scene = 2;
            double_timer = 0;
            int_cointimer = 0;
            int_lifetimer = 3;
        }
        if (scene ==2){
            menu2.draw();
        }
        txEnd();
        }
        }
    }
};
int main()
{
    Game game;
    game.run();
}
