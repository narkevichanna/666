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
    txBitBlt(txDC(),x+500,y,0,0, image1 ,0,0);
    txBitBlt(txDC(),x+500,y-799,0,0, image1 ,0,0);

    txTransparentBlt(txDC(),x+280,y,0,0, image2 ,0,0,TX_WHITE);
    txTransparentBlt(txDC(),x+280,y-799,0,0, image2 ,0,0,TX_WHITE);

    txTransparentBlt(txDC(),x+1050,y,0,0, image3 ,0,0,TX_WHITE);
    txTransparentBlt(txDC(),x+1050,y-799,0,0, image3 ,0,0,TX_WHITE);
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
    HDC image = txLoadImage("основнмашина.bmp");
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
        if (x < 240) {
                x = 240;
            }
        if(GetAsyncKeyState('D')){
            x += 3;
        }
        if (x > 668) {
                x = 668;
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
/*class Enemy1{
public:
    int x, y;
    int image_flag;
    HDC image1 = txLoadImage("маш1.bmp");
    HDC image2 = txLoadImage("кр.bmp");
    HDC image3 = txLoadImage("кр.bmp");
    HDC image4 = txLoadImage("кр.bmp");
    Enemy1 (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        if (image_flag == 1){
            txTransparentBlt(txDC(),x,y,0,0, image1 ,0,0, TX_WHITE);
        }
        if (image_flag == 2){
            txTransparentBlt(txDC(),x,y,0,0, image2 ,0,0, TX_WHITE);
        }
        if (image_flag == 3){
            txTransparentBlt(txDC(),x,y,0,0, image3 ,0,0, TX_WHITE);
        }
        if (image_flag == 4){
            txTransparentBlt(txDC(),x,y,0,0, image4 ,0,0, TX_WHITE);
        }
    }

    void moved(){
        y += 3;

    }
};*/
class Enemy2{
public:
    int x, y;
    int image_flag;
    HDC image1 = txLoadImage("кр.bmp");
    HDC image2 = txLoadImage("кр.bmp");
    HDC image3 = txLoadImage("кр.bmp");
    HDC image4 = txLoadImage("кр.bmp");
    Enemy2 (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        if (image_flag == 1){
            txTransparentBlt(txDC(),x,y,0,0, image1 ,0,0, TX_WHITE);
        }
        if (image_flag == 2){
            txTransparentBlt(txDC(),x,y,0,0, image2 ,0,0, TX_WHITE);
        }
        if (image_flag == 3){
            txTransparentBlt(txDC(),x,y,0,0, image3 ,0,0, TX_WHITE);
        }
        if (image_flag == 4){
            txTransparentBlt(txDC(),x,y,0,0, image4 ,0,0, TX_WHITE);
        }
    }

    void moved(){
        y -= 3;

    }
};
class Game{
public:
    int scene = 0;
    BackGround bg = BackGround(-300,0);
    Car car= Car(460,650);
    double double_timer = 0;
    int int_timer;
    //Enemy1 *pro[2];
    Enemy2 *pro2[2];
    Menu menu;
    void check(){
    if (txMouseX() >= 390 && txMouseX() <= 650 && txMouseY() >= 470 && txMouseY() <= 540 && txMouseButtons()==1 ){
        scene = 1;
    }
}
    void run(){
    txCreateWindow(1000,900);
    /*for(int i = 0; i < 2; i++){
        pro[i] = new Enemy1(rand() % (650 - 500 +1) + 500, -(rand() % (500 - 200 + 1)+200)) ;
    }*/
    for(int i = 0; i < 2; i++){
        pro2[i] = new Enemy2 (rand() % (400- 200 + 1)+200, rand() % (1300 - 1000 + 1)+ 1000);
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
        double_timer += 0.01;
        int_timer = double_timer;
        bg.draw();
        ostringstream str1;
        str1 << int_timer;
        string str_timer = str1.str();
        const char* char_timer = str_timer.c_str();
        txTextOut(460, 60, char_timer);
        bg.moved();
        car.draw();
        car.moved();
        for(int i = 0; i < 2; i++){
            if((car.x - pro2[i]->x)*(car.x - pro2[i]->x) <= 12110 and (car.y - pro2[i]->y)*(car.y - pro2[i]->y) <= 55225){
                while ((pro2[0]->x - pro2[1]->x)*(pro2[0]->x - pro2[1]->x) <= 10000){
                    pro2[i]->x = rand() % (400- 200 + 1)+200;
                    cout << (pro2[0]->x - pro2[1]->x)*(pro2[0]->x - pro2[1]->x) << " ";
                }
                pro2[i]->y = rand() % (1300 - 1000 + 1)+ 1000;
                double_timer = 0;
            }
        }
        /*for(int i = 0; i < 2; i++){
            pro[i]->draw();
            pro[i]->moved();
            if(pro[i]->y >= 900){
                pro[i]->y = -(rand() % (500 - 200));
                pro[i]->x = rand() % (650 - 500 +1) + 500;
                pro[i]->image_flag = rand() % 5 - 1;
            }
        }*/
        for(int i = 0; i < 2; i++){
            pro2[i]->draw();
            pro2[i]->moved();
            if(pro2[i]->y <= -50){
                pro2[i]->y = (rand() % (1300 - 1000 +1)+ 1000);
                pro2[i]->x = rand() % (400- 200 + 1)+200;
                while ((pro2[0]->x - pro2[1]->x)*(pro2[0]->x - pro2[1]->x) <= 10000){
                    pro2[i]->x = rand() % (400- 200 + 1)+200;
                }
                pro2[i]->image_flag = rand() % 5 - 1;
            }
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
