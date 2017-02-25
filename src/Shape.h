#ifndef _SHAPE_H
#define _SHAPE_H
#include "GameBoard.h"
#include "TextureLoader.h"


#define MAXTICKS 20
#define MAXSHAPES 7


class Shape{

    unsigned char data[16];
    int timer;
    int deathTimer;
    COLOR c;
    unsigned state;
public:
    unsigned int x;
    unsigned int y;
    int lag;

    unsigned type;

    unsigned int width;
    unsigned int height;
    bool dead;


    bool overlaps(GameBoard& b, int shiftX, int shiftY);
    void moveLeft(GameBoard& b);
    void moveRight(GameBoard& b);
    void moveDown(GameBoard& b);
    void stay(GameBoard& b);
    void draw(unsigned int px, unsigned int py, PicsContainer& pics);
    void rotate(GameBoard& b);
    void speedUp(){timer = lag;}

    Shape(const Shape& s){
        //printf("copying shape\n");
        memcpy(data, s.data, 16);
        width = s.width;
        height = s.height;
        x = 5;
        y = 0;
        dead = false;
        timer = 0;
        lag = MAXTICKS;
        deathTimer = 0;
        c = s.c;
        type = s.type;
        state = 0;
    }
//-------------
    Shape(int t){

        switch(t){
            case 0:{
                data[0] =  1;  data[1] = 1;
                data[4] =  1;  data[5] = 1;

                width = 2;
                height = 2;
                c = COLOR(0, 0, 1);
            }break;
            case 1:{
                data[0] =  0;  data[1] = 1; data[2] =  0;
                data[4] =  1;  data[5] = 1; data[6] =  1;

                width = 3;
                height = 2;
                c = COLOR(1, 1, 0);
            }break;

             case 2:{
                data[0] =  0;  data[1] = 1; data[2] =  1;
                data[4] =  1;  data[5] = 1; data[6] =  0;

                width = 3;
                height = 2;
                c = COLOR(1, 0, 0.5f);

            }break;
            case 3:{
                data[0] =  1;  data[1] = 1; data[2] =  0;
                data[4] =  0;  data[5] = 1; data[6] =  1;

                width = 3;
                height = 2;
                c = COLOR(0, 1, 0);

            }break;

            case 4:{
                data[0] =  1;  data[1] = 1; data[2] =  1;
                data[4] =  0;  data[5] = 0; data[6] =  1;

                width = 3;
                height = 2;
                c = COLOR(0, 1, 1);
            }break;

            case 5:{
                data[0] =  1;  data[1] = 1; data[2] =  1;
                data[4] =  1;  data[5] = 0; data[6] =  0;

                width = 3;
                height = 2;
                c = COLOR(1, 0.5f, 0);
            }break;

            case 6:{
                data[0] =  1;  data[1] = 1; data[2] =  1; data[3] = 1;

                width = 4;
                height = 1;
                c = COLOR(1, 0, 0);
            }break;


                      




        }
        lag = MAXTICKS;
        x = 5;
        y = 0;
        dead = false;
        timer = 0;
        deathTimer = 0;
        type = t;
        state = 0;

    }

};



#endif //_SHAPE_H
