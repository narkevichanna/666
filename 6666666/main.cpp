#include <iostream>
#include"TXLib.h"

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
    txBitBlt(txDC(),200,y,0,0, image1 ,0,0);
    txBitBlt(txDC(),200,y-799,0,0, image1 ,0,0);

    txTransparentBlt(txDC(),0,y,0,0, image2 ,0,0,TX_WHITE);
    txTransparentBlt(txDC(),0,y-799,0,0, image2 ,0,0,TX_WHITE);

    txTransparentBlt(txDC(),800,y,0,0, image3 ,0,0,TX_WHITE);
    txTransparentBlt(txDC(),800,y-799,0,0, image3 ,0,0,TX_WHITE);
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
    Enemy2 *pro2[2];
    Menu menu;
    void check(){
    if (txMouseX() >= 390 && txMouseX() <= 650 && txMouseY() >= 470 && txMouseY() <= 540 && txMouseButtons()==1 ){
        scene = 1;
    }
}
    void run(){
    txCreateWindow(1000,900);
    for(int i = 0; i < 2; i++){
        pro2[i] = new Enemy2 (rand() % (1000- 200 + 1)+200, rand() % (1300 - 1000 + 1)+ 1000);
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
        bg.moved();
        car.draw();
        car.moved();
        for(int i = 0; i < 2; i++){
            pro2[i]->draw();
            pro2[i]->moved();
            if(pro2[i]->y <= -50){
                pro2[i]->y = (rand() % (1300 - 1000 +1)+ 1000);
                pro2[i]->x = rand() % (370 - 250 +1) + 250;
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
