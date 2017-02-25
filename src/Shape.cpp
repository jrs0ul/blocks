#include "Shape.h"

bool Shape::overlaps(GameBoard& b, int shiftX, int shiftY){
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int a = 0; a < width; a++){
            if (data[i * 4 + a]){

                if (x + shiftX + a >= 10)
                    return true;

                if (y + shiftY + i >= 22)
                    return true;

                if (b.board[y + shiftY + i][x + shiftX + a])
                    return true;
            }
        }
    }

    return false;

}


//------------------------
void Shape::moveDown(GameBoard& b){
    timer++;
    if (timer >= lag){
        timer = 0;
    
        if ((y + height < 22)&&(!overlaps(b, 0, 1))){
            y++;
        }
        else{
            deathTimer++;
            if (deathTimer >= 2){
                stay(b);
                dead = true;
            }
        }
    }
}
//-----------------------
void Shape::moveLeft(GameBoard& b){
    
    if ((x > 0)&&(!overlaps(b, -1, 0)))
        x--;
}
//---------------------------
void Shape::moveRight(GameBoard& b){

    if ((x + width < 10)&&(!overlaps(b, 1, 0)))
        x++;
}


//-----------------
void Shape::stay(GameBoard& b){
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int a = 0; a < width; a++){
            if (data[i * 4 + a])
                b.board[y + i][x + a] = 1;
            }
        }

}
//-----------------
void Shape::draw(unsigned int px, unsigned int py, PicsContainer& pics){

    if (!dead){
        for (unsigned int i = 0; i < height; i++){
            for (unsigned int a = 0; a < width; a++){
                if ((data[i * 4 + a]) && (y + i > 1))
                    pics.draw(1, px + (x + a) * 16, py + (y + i - 2)*16, 1, false, 1.0f, 1.0f, 0.0f,
                              c, c);
            }
        }
    }
}
//-------------------------
void Shape::rotate(GameBoard& b){
    unsigned char tmpdata[16];
    unsigned int tmpHeight = height;
    unsigned int tmpWidth = width;

    memcpy(tmpdata, data, 16);
   // if (state == 0){

        for (unsigned int i = 0; i < width; i++){
            for (unsigned int a = 0; a < height; a++){
                data[i * 4 + a] = tmpdata[a * 4 + (width - 1 - i)];
                //printf("%u ", a*4+(width - 1 - i));
            }
        }
        //printf("\n----\n");

        height = tmpWidth;
        width = tmpHeight;
    //}
   /* else{
        if ((type == 1)||(type == 5)||(type == 4)){
            for (unsigned int i = 0; i < width; i++){
                for (unsigned int a = 0; a < height; a++){
                    data[i * 4 + a] = tmpdata[a * 4 + (width - 1 - i)];
                }
            }

            height = tmpWidth;
            width = tmpHeight;

        }
        else{
            //TODO: copy back the original shape;
        }
    }*/

    if (overlaps(b, 0, 0)){
        height = tmpHeight;
        width = tmpWidth;
        memcpy(data, tmpdata, 16);

    }
    else{
        state++;
    }



}
