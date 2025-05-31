#include <iostream>
#include"TXLib.h"
#include <string>
#include <sstream>
using namespace std;
class Background{
public:
    HDC image = txLoadImage("img/bg.bmp");
    void draw(){
        txBitBlt(txDC(), 0, 0, 0, 0, image, 0, 0);
    }
};
class Menu{
public:
    HDC image1 = txLoadImage("img/menu_bg.bmp");
    HDC image2 = txLoadImage("img/start_btn1.bmp");
    HDC image3 = txLoadImage("img/exit_btn1.bmp");
    void draw(){
        txBitBlt(txDC(), 0, 0, 0, 0, image1, 0, 0);
        txSetFillColor(TX_GREY);
        //txRectangle(470, 650, 730, 710);
        txTransparentBlt(txDC(), 470, 625, 0, 0, image2, 0, 0, TX_WHITE);
        txTransparentBlt(txDC(), 470, 745, 0, 0, image3, 0, 0, TX_WHITE);
        txSetColor(TX_WHITE);
        txTextOut(400, 300, "SPACE BATTLE");
        txSelectFont("Comic Sans MS", 78);
    }
    bool check(){
        if (txMouseX() >= 470 && txMouseX() <= 770 && txMouseY() >= 625 && txMouseY() <= 725 ){
            if(txMouseButtons()==1 ){
                return true;
            }
        }
        if (txMouseX() >= 470 && txMouseX() <= 770 && txMouseY() >= 745 && txMouseY() <= 845 ){
            if(txMouseButtons()==1 ){
                exit(1);
            }
        }
    }
};
class Menu1{
public:
    HDC image1 = txLoadImage("img/menu_bg.bmp");
    HDC image3 = txLoadImage("img/exit_btn1.bmp");
    void draw(){
        txBitBlt(txDC(), 0, 0, 0, 0, image1, 0, 0);
        txTransparentBlt(txDC(), 470, 625, 0, 0, image3, 0, 0, TX_WHITE);
        txSetColor(TX_WHITE);
        txTextOut(450, 300, "YOU WIN");
        txSelectFont("Comic Sans MS", 78);
    }
};
class Menu2{
public:
    HDC image1 = txLoadImage("img/menu_bg.bmp");
    HDC image3 = txLoadImage("img/exit_btn1.bmp");
    void draw(){
        txBitBlt(txDC(), 0, 0, 0, 0, image1, 0, 0);
        txTransparentBlt(txDC(), 470, 625, 0, 0, image3, 0, 0, TX_WHITE);
        txSetColor(TX_WHITE);
        txTextOut(450, 300, "YOU LOSE");
        txSelectFont("Comic Sans MS", 78);
    }
};
class Enemy{
public:
    int x, y;
    int img_flag;
    HDC image1 = txLoadImage("img/enemy.bmp");
    HDC image2 = txLoadImage("img/enemy2.bmp");
    Enemy (int x,int y, int img_flag){
    this ->x=x;
    this ->y =y;
    this-> img_flag = img_flag;
    }
    void draw(){
        if(img_flag == 1){
            txTransparentBlt(txDC(),x,y,0,0, image1 ,0,0, TX_WHITE);
        }
        if(img_flag == 2){
            txTransparentBlt(txDC(),x,y,0,0, image2 ,0,0, TX_WHITE);
        }
    }
    void moved(){
        y += 3;
    }
};
class Bullet{
public:
    int x, y;
    HDC image = txLoadImage("img/bullet.bmp");
    Bullet (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image ,0,0, TX_WHITE);
    }
    void moved(){
        y -= 10;
    }
};
class Bullet2{
public:
    int x, y;
    int state = 0;
    HDC image1 = txLoadImage("img/bullet2.bmp");
    HDC image2 = txLoadImage("img/explode.bmp");
    Bullet2 (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        if(state == 0){
            txTransparentBlt(txDC(),x,y,0,0, image1 ,0,0, TX_WHITE);
        }
        if(state == 1){
            txTransparentBlt(txDC(),x,y,0,0, image2 ,0,0, TX_WHITE);
        }
    }
    void moved(){
        if(state == 0){
            y -= 10;
        }
    }
};
class EBullet{
public:
    int x, y;
    HDC image = txLoadImage("img/ebullet.bmp");
    EBullet (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image ,0,0, TX_WHITE);
    }
    void moved(){
        y += 10;
    }
};
class Pers{
public:
    int x, y;
    int hp = 10;
    HDC image = txLoadImage("img/pers.bmp");
    Pers (int x,int y){
    this ->x=x;
    this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image ,0,0, TX_WHITE);
    }
    void moved(){
        if(GetAsyncKeyState('A')){
            x -= 6;
        }
        if (x < 0) {
                x = 0;
            }
        if(GetAsyncKeyState('D')){
            x += 6;
        }
        if (x > 1100) {
                x = 1100;
            }
        if (hp > 100){
            hp = 100;
        }
    }
};
class Heal{
public:
    int x, y;
    HDC image = txLoadImage("img/heal.bmp");
    Heal (int x,int y){
        this ->x=x;
        this ->y =y;
    }
    void draw(){
        txTransparentBlt(txDC(),x,y,0,0, image ,0,0, TX_WHITE);
    }
    void moved(){
        y += 5;
    }
};
class Game {
public:
    Background bg;
    Menu menu;
    Menu1 menu1;
    Menu2 menu2;
    int scene = 0;
    int exp = 0;
    Pers pers = Pers(600, 800);
    Heal *heal[2];
    Enemy *enemy[5];
    Bullet *bull[20];
    Bullet2 bull2 = Bullet2(0, 0);
    EBullet *ebull[20];
    int shoot_number[20];
    bool is_fire[20];
    bool is_fire2 = false;
    bool is_efire[20];
    bool is_heal[2];
    bool is_explode = false;

    int fire_timer = 15;
    double fire_timer2 = 0;
    int heal_timer = 0;
    int efire_timer = 50;
    int menu_timer = 50;
    int menu1_timer = 50;
    int menu2_timer = 50;
    int explode_timer = 0;
    void run(){
        txCreateWindow(1200, 1000);
        for(int i = 0; i < 5; i++){
            enemy[i] = new Enemy(rand() % 1100, -500 - (rand() % 200), rand() % 2 + 1);
        }
        for(int i = 0; i < 20; i++){
            bull[i] = new Bullet(0, 0);
            is_fire[i] = false;
        }
        for(int i = 0; i < 20; i++){
            ebull[i] = new EBullet(0, 0);
        }
        for(int i = 0; i < 2; i++){
            heal[i] = new Heal(0, 0);
            is_heal[i] = false;
        }
        while(true){
            if (scene == 0){
                txBegin();
                menu.draw();
                menu.check();
                if(menu.check() == true){
                    if(menu_timer <= 0){
                        scene = 1;
                        menu_timer = 100;
                    }
                }
                menu_timer --;
                txEnd();
            }
            if (scene == 1){
                txBegin();
                txClear();
                bg.draw();
                pers.draw();
                pers.moved();
                for(int i = 0; i < 2; i++){
                    if (heal_timer >= 200){
                        if(is_heal[i] == false){
                            is_heal[i] = true;
                            heal_timer = 0;
                            heal[i]->x = 100 + rand() % 900;
                            heal[i]->y = -100 - rand() % 1400;
                        }
                    }
                    if(is_heal[i]){
                        heal[i]->draw();
                        heal[i]->moved();
                        if(heal[i]->y >= 1000){
                            is_heal[i] == false;
                            heal[i]->x = 100 + rand() % 900;
                            heal[i]->y = -100 - rand() % 1400;
                        }
                        if(heal[i]->x + 10 >= pers.x && heal[i]->x < pers.x + 62 && heal[i]->y + 10 >= pers.y && heal[i]->y <= pers.y + 85){
                            is_heal[i] == false;
                            heal[i]->x = 100 + rand() % 900;
                            heal[i]->y = -100 - rand() % 1400;
                            pers.hp += 20;
                        }
                    }
                }
                for(int i = 0; i < 5; i++){
                    enemy[i]->draw();
                    enemy[i]->moved();
                    if (enemy[i]->y >= 1000){
                        enemy[i]->y = -500 - (rand() % 200);
                        enemy[i]->x = rand() % 1100;
                        enemy[i]->img_flag = rand() % 2 + 1;
                    }
                    if (pers.x >= enemy[i]->x - 70 && pers.x <= enemy[i]->x + 70 && pers.y <= enemy[i]->y + 90 && pers.y >= enemy[i]->y - 90){
                        enemy[i]->y = -500 - (rand() % 200);
                        enemy[i]->x = rand() % 1100;
                        enemy[i]->img_flag = rand() % 2 + 1;
                        pers.hp -= 10;
                        exp+=5;
                    }
                    if (is_fire2){
                        if(bull2.x >= enemy[i]->x - 40 && bull2.x <= enemy[i]->x + 60 && bull2.y <= enemy[i]->y + 85){
                            enemy[i]->y = -500 - (rand() % 200);
                            enemy[i]->x = rand() % 1100;
                            enemy[i]->img_flag = rand() % 2 + 1;

                            bull2.state = 1;
                            bull2.x -= 150;
                            bull2.y -= 150;
                            is_explode = true;
                            exp+=5;
                        }
                    }
                    if(is_explode){
                        explode_timer++;
                        if(enemy[i]->x >= bull2.x - 150 && enemy[i]->x <= bull2.x + 300 && enemy[i]->y >= bull2.y - 150 && enemy[i]->y <= bull2.y + 300){
                                enemy[i]->y = -500 - (rand() % 200);
                                enemy[i]->x = rand() % 1100;
                                enemy[i]->img_flag = rand() % 2 + 1;
                                exp+=5;
                            }
                        if (explode_timer == 10){
                            bull2.state = 0;
                            is_fire2 = false;
                            explode_timer = 0;
                            is_explode = false;
                        }
                    }
                }
                for(int i = 0; i < 20; i++){
                    shoot_number[i] = rand() % 5;
                    if(enemy[shoot_number[i]]->y > 0){
                        if (efire_timer >= 50){
                            if (is_efire[i] != true){
                                is_efire[i] = true;
                                ebull[i]->x = enemy[shoot_number[i]]->x + 60;
                                ebull[i]->y = enemy[shoot_number[i]]->y + 95;
                                efire_timer = 0;
                            }
                        }
                    }
                }
                for(int i = 0; i < 20; i++){
                    //cout << is_fire[i] << " ";
                    if (is_efire[i]){
                        ebull[i]->draw();
                        ebull[i]->moved();
                        if(ebull[i]->y >= pers.y - 30 && ebull[i]->y <= pers.y && ebull[i]->x >= pers.x && ebull[i]->x <= pers.x + 60){
                            pers.hp -= 10;
                            is_efire[i] = false;
                        }
                    }
                    if (ebull[i]->y >= 1000){
                        is_efire[i] = false;
                    }

                }
                for(int i = 0; i < 20; i++){
                    if(txMouseButtons() == 1){
                        if (fire_timer >= 15){
                            if (is_fire[i] != true){
                                is_fire[i] = true;
                                bull[i]->x = pers.x + 30;
                                bull[i]->y = pers.y;
                                fire_timer = 0;
                            }
                        }
                    }
                    if (is_fire[i] != true){
                        bull[i]->x = pers.x + 30;
                        bull[i]->y = pers.y;
                    }
                }
                if (GetAsyncKeyState('1')){
                    if(fire_timer2 <= 0){
                        if(is_fire2 == false){
                            //cout << "1";
                            is_fire2 = true;
                            bull2.x = pers.x-10;
                            bull2.y = pers.y;
                            fire_timer2 = 10;
                        }
                    }
                }
                if (is_fire2 == false){
                    bull2.x = pers.x-10;
                    bull2.y = pers.y;
                }
                if (is_fire2){
                    bull2.draw();
                    bull2.moved();
                    if(bull2.y < -100){
                        is_fire2 = false;
                    }
                }
                for(int i = 0; i < 20; i++){
                    //cout << is_fire[i] << " ";
                    if (is_fire[i]){
                        bull[i]->draw();
                        bull[i]->moved();
                        for(int j = 0; j < 5; j++){
                            if(bull[i]->y <= enemy[j]->y + 78 && bull[i]->x >= enemy[j]->x && bull[i]->x <= enemy[j]->x + 97){
                                is_fire[i] = false;
                                enemy[j]->y = -500 - (rand() % 200);
                                enemy[j]->x = rand() % 1100;
                                exp+=5;
                            }
                        }
                    }
                    if (pers.y - bull[i]->y >= 600){
                        is_fire[i] = false;
                    }

                }
                if (pers.hp <= 0){
                    scene = 3;
                    exp = 0;
                    for(int j = 0; j < 5; j++){
                        enemy[j]->y = -500 - (rand() % 200);
                        enemy[j]->x = rand() % 1100;
                    }
                    for(int i = 0; i < 2; i++){
                        is_heal[i] == false;
                        heal[i]->x = 100 + rand() % 900;
                        heal[i]->y = -100 - rand() % 1400;
                    }
                    for(int i = 0; i < 20; i++){
                        shoot_number[i] = rand() % 5;
                        ebull[i]->x = enemy[shoot_number[i]]->x + 60;
                        ebull[i]->y = enemy[shoot_number[i]]->y + 95;
                    }
                    is_fire2 = false;
                    pers.hp = 100;
                    fire_timer2 = 0;
                }
                txSetFillColor(TX_RED);
                txRectangle(50, 25, 250, 65);
                txSetFillColor(TX_GREEN);
                txRectangle(50,25,pers.hp*2+50, 65);

                txSetFillColor(TX_BLACK);
                txRectangle(500, 25, 700, 65);
                txSetFillColor(TX_YELLOW);
                txRectangle(500,25,exp*2+500, 65);

                if(exp >= 100){
                    scene = 2;
                    pers.hp = 100;
                    for(int j = 0; j < 5; j++){
                        enemy[j]->y = -500 - (rand() % 200);
                        enemy[j]->x = rand() % 1100;
                    }
                    for(int i = 0; i < 2; i++){
                        is_heal[i] == false;
                        heal[i]->x = 100 + rand() % 900;
                        heal[i]->y = -100 - rand() % 1400;
                    }
                    for(int i = 0; i < 20; i++){
                        shoot_number[i] = rand() % 5;
                        ebull[i]->x = enemy[shoot_number[i]]->x + 60;
                        ebull[i]->y = enemy[shoot_number[i]]->y + 95;
                    }
                    is_fire2 = false;
                    exp = 0;
                    fire_timer2 = 0;
                }
                if (is_fire2 == false){
                    int int_fire_timer2 = fire_timer2;
                    ostringstream str1;
                    str1 << int_fire_timer2;
                    string str_fire_timer2 = str1.str();
                    const char* char_fire_timer2 = str_fire_timer2.c_str();
                    txTextOut(1150, 25, char_fire_timer2);
                    if(fire_timer2 >= 0){
                        fire_timer2 -= 0.01;
                    }
                }
                heal_timer++;
                fire_timer++;
                efire_timer++;
                txSleep(1);
                txEnd();
            }
            if(scene == 2){
                txBegin();
                menu1.draw();
                if (txMouseX() >= 470 && txMouseX() <= 770 && txMouseY() >= 625 && txMouseY() <= 725 ){
                    if(txMouseButtons()==1 ){
                        if(menu1_timer <= 0){
                            scene = 0;
                        }
                    }
                }
                menu1_timer -= 1;
                txEnd();
            }
            if(scene == 3){
                txBegin();
                menu2.draw();
                if (txMouseX() >= 470 && txMouseX() <= 770 && txMouseY() >= 625 && txMouseY() <= 725 ){
                    if(txMouseButtons()==1 ){
                        if(menu2_timer <= 0){
                            scene = 0;
                        }
                    }
                }
                menu2_timer -= 1;
                txEnd();
            }
            //cout << scene << " ";
        }
    }
} ;
int main(){
    Game game;
    game.run();
}
