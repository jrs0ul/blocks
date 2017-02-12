#ifndef _SHAPE_H
#define _SHAPE_H
#include "GameBoard.h"
#include "TextureLoader.h"


class Shape{

    unsigned char data[16];
    int timer;
    int deathTimer;
public:
    unsigned int x;
    unsigned int y;
    int lag;

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

    Shape(const Shape& s){
        //printf("copying shape\n");
        memcpy(data, s.data, 16);
        width = s.width;
        height = s.height;
        x = 5;
        y = 0;
        dead = false;
        timer = 0;
        lag = 10;
        deathTimer = 0;
    }
//-------------
    Shape(int type){


        switch(type){
            case 0:{
                data[0] =  1;  
                data[4] =  1;  
                data[8] =  1; 
                data[12] = 1;

                width = 1;
                height = 4;
            }break;
            case 1:{
                data[0] =  1;  data[1] = 1;
                data[4] =  1;  data[5] = 1;

                width = 2;
                height = 2;
            }break;
            case 2:{
                data[0] =  0;  data[1] = 1; data[2] =  0;
                data[4] =  1;  data[5] = 1; data[6] =  1;

                width = 3;
                height = 2;
            }break;

            case 3:{
                data[0] =  1;  data[1] = 1; data[2] =  1;
                data[4] =  0;  data[5] = 0; data[6] =  1;

                width = 3;
                height = 2;
            }break;
            case 4:{
                data[0] =  1;  data[1] = 1; data[2] =  0;
                data[4] =  0;  data[5] = 1; data[6] =  1;

                width = 3;
                height = 2;
            }break;





        }
        lag = 10;
        x = 5;
        y = 0;
        dead = false;
        timer = 0;
        deathTimer = 0;

    }

};



#endif //_SHAPE_H
