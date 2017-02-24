
#include "CppSingleton.h"
#include "Collisions.h"




//---------------------------------------------
void Singleton::draw_intro(){
    pics.draw(14, SCREEN_WIDTH/2 - 256/2,
              0, 0, false, 1.0f, 1.0f, 0,
              COLOR(1.0f, 1.0f, 1.0f, 1.0f),
              COLOR(1.0f, 1.0f, 1.0f, 0.8f));
    
    
//#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
    more_button.draw(pics, 25, 0);
//#endif
    Play_Button.draw(pics, 18, 0);
    Help_Button.draw(pics, 18, 2);
    Credits_Button.draw(pics, 18, 1);
    Options_Button.draw(pics, 18, 3);
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    QuitButton.draw(pics, 18, 4);
#endif
}
//------------------------------------
void Singleton::drawOptions(){
    draw_intro();
    int x = SCREEN_WIDTH/2 - 100;
    int y = 25;
    int width = 280;
    int height = 460;
    COLOR c1 = COLOR(0.5f,0.0f,0.8f, 0.9f);
    COLOR c2 = COLOR(0.2f,0.0f,0.3f, 0.7f);
    pics.draw(-1, x, y, 0, false, width, height, 0, 
              c1, c2);
    
    pics.draw(8, x - 32, y, 0, false,
              32/64.0f, height/128.0f, 0, c1, c2);
    pics.draw(8, x + width, y, 1, false,
              32/64.0f, height/128.0f, 0, c1, c2);
    
    pics.draw(18, SCREEN_WIDTH/2, 32, 3, true);
    optionsOK_button.drawTextnPicture(pics, 7, 2, 0, "OK");
    WriteShadedText(130, 110, pics, 0, "Music volume:");
    
    musicVolumeBar.draw(pics, 2, 8, 9);
    if (yesno.active())
        yesno.draw(pics, 0, 8, 2, 7, 128.0f);
}

//-----------------------------------
void Singleton::optionsLogic(){
    
    if (touches.move.count()){
        musicVolumeBar.processInput(touches.move[0].v[0], touches.move[0].v[1]);
        sys.musicVolume = musicVolumeBar.state()/100.0f; 
        music.setVolume(sys.musicVolume);
    }
    if (touches.down.count()){
        musicVolumeBar.processInput(touches.down[0].v[0], touches.down[0].v[1]);
        sys.musicVolume = musicVolumeBar.state()/100.0f; 
        music.setVolume(sys.musicVolume);
    }
    
    if (touches.up.count()){
        int mx = touches.up[0].v[0];
        int my = touches.up[0].v[1];
        
        
        if (musicVolumeBar.isPointerOnNextpage(mx, my)){
            musicVolumeBar.pageDown();
            sys.musicVolume = musicVolumeBar.state()/100.0f; 
            music.setVolume(sys.musicVolume);
            //ss.playsound(8);
        }
        if (musicVolumeBar.isPointerOnPrevpage(mx, my)){
            musicVolumeBar.pageUp();
            sys.musicVolume = musicVolumeBar.state()/100.0f; 
            music.setVolume(sys.musicVolume);
            //ss.playsound(8);
        }
        
               
        if (optionsOK_button.isPointerOnTop(mx, my)){
            GameState = MENU;
            char buf[255];
            sprintf(buf, "%s/settings.cfg", DocumentPath);
            sys.write(buf);
        }
    }
}



//__________________________________________
void Singleton::LoadFiles(){
    
    puts("Loading - please wait ");
    
    char dir[128];

    strcpy(dir, "data/pics/");

    
    Font.load(pics, 0, "charai.tga", dir); 
    pics.loadFile("blocks.tga", 1, 16, 16, dir, 1);
    pics.loadFile("buttons.tga", 2, 48, 48, dir, 1);
    pics.loadFile("panel.tga",5, 512, 64, dir, 1);
    pics.loadFile("guistuff.tga",8, 64, 128, dir, 1);
    pics.loadFile("title.tga", 14, 256, 128, dir, 1);
    pics.loadFile("menu.tga", 18, 128, 64, dir, 1);
    pics.loadFile("rodykle.tga", 19, 32, 32, dir, 1);
    pics.loadFile("guistuff2.tga", 21, 128, 64, dir, 1);
    pics.loadFile("moregames.tga",25, 100, 64, dir, 1);
  
    puts("images +/- loaded ;)");
}

//--------------------------------------
void Singleton::loadConfig(){

    char buf[255];
    sprintf(buf, "%s/settings.cfg", DocumentPath);
    sys.load(buf);
    ScreenWidth = sys.ScreenWidth;
    ScreenHeight = sys.ScreenHeight;
    windowed = sys.useWindowed;

    sys.write(buf);

}
//----------------------------------------
void Singleton::init(){
        
    LoadFiles();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    
    musicVolumeBar.set(50, 130, 2, 100, sys.musicVolume*10, 2);
    
    ss.init(0);
    ss.loadFiles("data/sfx/", "audio.txt");
    music.open("data/music.ogg");
    music.setVolume(sys.musicVolume);
    music.playback();
   
    useAccel = false;
}

//--------------------
void Singleton::mainMenuLogic(){
   
    if ((OldKeys[6])&&(!Keys[6])){
        Works = false;
    }
        

    if (touches.up.count()){
        
        if (Play_Button.pressed){
            GameState = GAME;
            Play_Button.reset();
        }
        if (Credits_Button.pressed){
            GameState = CREDITS;
            Credits_Button.reset();
        }
        if (Help_Button.pressed){
            GameState = HELP;
            activeHelpPage = 0;
            Help_Button.reset();
        }
        
        if (Options_Button.pressed){
            GameState = OPTIONS;
            Options_Button.reset();
        }

        if (QuitButton.pressed){
            Works = false;
        }
        
//#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        if (more_button.pressed){
            more_button.c = COLOR(1,1,1);
            launchmystore = true;
            more_button.reset();
        }
//#endif
    }
    
    if (touches.down.count()){
        int mx = touches.down[0].v[0];
        int my = touches.down[0].v[1];
        
        //printf("click x:%d y:%d\n", mx , my);
        if (Play_Button.isPointerOnTop(mx, my)){
            Play_Button.scalex = 1.5f;
            Play_Button.pressed = true;
        }
        if (Credits_Button.isPointerOnTop(mx, my)){
            Credits_Button.scalex = 1.5f;
            Credits_Button.pressed =true;
        }
        if (Help_Button.isPointerOnTop(mx, my)){
            Help_Button.scalex = 1.5f;
            Help_Button.pressed = true;
        }
        if (Options_Button.isPointerOnTop(mx, my)){
            Options_Button.scalex = 1.5f;
            Options_Button.pressed = true;
        }

        if (QuitButton.isPointerOnTop(mx, my)){
            QuitButton.scalex = 1.5f;
            QuitButton.pressed = true;
        }
        
        if (more_button.isPointerOnTop(mx, my)){
            more_button.c = COLOR(0.5f, 0.5f, 0.5f);
            more_button.pressed = true;
        }
    }
}



//----------------------------------
void Singleton::DrawCredits(){
    draw_intro();
    int x = SCREEN_WIDTH/2 - 180;
    int y = 25;
    int width = 360;
    int height = 280;
    COLOR c1 = COLOR(0.5f,0.0f,0.8f, 0.9f);
    COLOR c2 = COLOR(0.2f,0.0f,0.3f, 0.7f);
    pics.draw(-1, x, y, 0, false, width, height, 0, 
              c1, c2);
    
    pics.draw(8, x - 32, y, 0, false,
              32/64.0f, height/128.0f, 0, c1, c2);
    pics.draw(8, x + width, y, 1, false,
              32/64.0f, height/128.0f, 0, c1, c2);
    
    pics.draw(18, SCREEN_WIDTH/2, 32, 1, true);
    
    Font.setcolor(0,0,0);
    Font.display(SCREEN_WIDTH/2 - 73, 61, "Code & Graphics:");
    Font.display(SCREEN_WIDTH/2 - 28, 81, "jrs0ul");
    //WriteShadedText(SCREEN_WIDTH/2 - 82, 101, pics, 0, "http://jrs0ul.com/");
    Font.display(SCREEN_WIDTH/2 - 77, 171, "Awesome music by:");
    Font.display(SCREEN_WIDTH/2 - 122, 201, "Fonogeri from album 'Fable'");
    Font.display(SCREEN_WIDTH/2 - 172, 221, "http://www.jamendo.com/en/album/53232");
    Font.setcolor(1,1,1);
    
    Font.display(SCREEN_WIDTH/2 - 72, 60, "Code & Graphics:");
    Font.display(SCREEN_WIDTH/2 - 27, 80, "jrs0ul");
    Font.display(SCREEN_WIDTH/2 - 76, 170, "Awesome music by:");
    Font.display(SCREEN_WIDTH/2 - 121, 200, "Fonogeri from album 'Fable'");
    Font.display(SCREEN_WIDTH/2 - 171, 220, "http://www.jamendo.com/en/album/53232");
}
//------------------------------
void Singleton::Credits(){
    
    
    if (((touches.oldDown.count())&&(!touches.down.count()))){
        
        if (jrs0ul_button.isPointerOnTop(MouseX,MouseY))
            launchjrs0ul = true;
        else
            GameState = MENU;
    }
}
//-----------------------------
void Singleton::DrawHelp(){
    draw_intro();
    int x = SCREEN_WIDTH/2 - 120;
    int y = 5;
    int width = 240;
    int height = 460;
    COLOR c1 = COLOR(0.5f,0.0f,0.8f, 0.9f);
    COLOR c2 = COLOR(0.2f,0.0f,0.3f, 0.7f);
    pics.draw(-1, x, y, 0, false, width, height, 0, 
              c1, c2);
    
    pics.draw(8, x - 32, y, 0, false,
              32/64.0f, height/128.0f, 0, c1, c2);
    pics.draw(8, x + width, y, 1, false,
              32/64.0f, height/128.0f, 0, c1, c2);
    pics.draw(18, SCREEN_WIDTH/2, 32, 2, true);
    
    char pages[4][11][255] = {{" ",
                              " "
                              },
                            {" ",
                             " "},
                            {},
                            {" ",
                             " ",
                            }};
    
    switch (activeHelpPage){
        case 0:{
            for (unsigned i = 0; i < 11; i++)
                WriteShadedText(x, 50+i*20, pics, 0, pages[0][i], 0.95f);
            
        } break;
        case 1:{
            for (unsigned i = 0; i < 11; i++)
                WriteShadedText(x, 50+i*20, pics, 0, pages[1][i], 0.95f);
        }break;
        
        case 2:{
              
        }break;
            
    }
    char buf[255];
    sprintf(buf, "%u/%u", activeHelpPage+1, maxHelpPage+1);
    WriteShadedText(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT - 50, pics, 0, buf);
    
    if (activeHelpPage == maxHelpPage)
        nextHelpPage_button.c = COLOR(0.5f, 0.5f, 0.5f);
    else
        nextHelpPage_button.c = COLOR(1.0f, 1.0f, 1.0f);
    nextHelpPage_button.draw(pics, 2, 9);
    
    if (activeHelpPage == 0)
        prevHelpPage_button.c = COLOR(0.5f, 0.5f, 0.5f);
    else
        prevHelpPage_button.c = COLOR(1.0f, 1.0f, 1.0f);
    prevHelpPage_button.draw(pics, 2, 8);
    
    helpBack_button.drawTextnPicture(pics, 7, 2, 0, "back");
    
    
}
//--------------------------
void Singleton::Help(){
    
    if (touches.up.count()){
        
        float mx = touches.up[0].v[0];
        float my = touches.up[0].v[1];
        
        if (helpBack_button.isPointerOnTop(mx, my)){
            GameState = MENU;
        }
        
        if (prevHelpPage_button.isPointerOnTop(mx, my)){
            if (activeHelpPage > 0)
                activeHelpPage--;
        }
        if (nextHelpPage_button.isPointerOnTop(mx, my)){
            if (activeHelpPage < maxHelpPage)
                activeHelpPage++;
        }
        
    }
}
//-------------------
void Singleton::DrawGame(){
    
    for (unsigned i = 0; i < 20; i++){
        for (unsigned a = 0; a < 10; a++){
            pics.draw(1, 16 + a * 16, 16 + i*16, 0, false);
        }
    }
    gameBoard.draw(pics);
    if (shape)
        shape->draw(16, 16, pics);


    Font.setcolor(1,0,0);
    char buf[255];
    sprintf(buf,"Lines:%d",lines);
    Font.display(200, 15, buf);
    Font.display(200, 50, "Next:");

    if (newShape){
        newShape->x=0;
        newShape->y=2;
        newShape->draw(200, 70, pics);
    }
}
//-------------------
void Singleton::render(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        glRotatef(-90, 0, 0, 1);
        glOrthof(0.0, (GLfloat) SCREEN_WIDTH, (GLfloat) SCREEN_HEIGHT, 0.0, 400, -400);
    #else
        glOrtho(0.0, (GLfloat) SCREEN_WIDTH, (GLfloat) SCREEN_HEIGHT, 0.0, 400, -400);
    #endif
    
    switch(GameState){
        case MENU:draw_intro(); break;
        case GAME: DrawGame(); break;
        case CREDITS: DrawCredits(); break;
        case HELP: DrawHelp(); break;
        case OPTIONS: drawOptions(); break;
    }

    
#if !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
    if (!windowed)
        pics.draw(19, MouseX, MouseY, 2, false);
#endif

    glEnable(GL_TEXTURE_2D);
    pics.drawBatch(666);   
}
//---------------------
void Singleton::GameLogic(){

    if (gameBoard.isTopRowDirty()){
        delete shape;
        delete newShape;
        newShape = 0;
        shape = 0;
        lines = 0;
        gameBoard.clean();
        GameState = MENU;
        printf("game over\n");
    }


    if (shape){
        //printf("Shape control...\n");

        if ((Keys[0])&&(!OldKeys[0]))
            shape->rotate(gameBoard);
        if (Keys[2])
            shape->moveLeft(gameBoard);
        if (Keys[3])
            shape->moveRight(gameBoard);
        if (Keys[1]){
            shape->speedUp();
        }
        shape->moveDown(gameBoard);
        if (shape->dead){
            delete shape;
            shape = 0;
            int ln = gameBoard.findLines();
            lines += ln;
            for (int i = 0; i < ln; i++)
                ss.playsound(0); 
        }
    }
    else {
        if (newShape){
            shape = new Shape(*newShape);
            delete newShape;
            newShape = 0;
            //printf("making shape...\n");
        }
        newShape = new Shape(rand()%5);
        //printf("making newShape...\n");

    }
}

//---------------------
void Singleton::logic(){
    
    if (music.playing())
        music.update();
    
    if (touches.down.count()){
        MouseX = touches.down[0].v[0];
        MouseY = touches.down[0].v[1];
    }
    
    if (touches.move.count()){
        MouseX = touches.move[0].v[0];
        MouseY = touches.move[0].v[1];
    }
   
    switch(GameState){
        case MENU: mainMenuLogic(); break;
        case GAME: GameLogic(); break;
        case CREDITS: Credits(); break;
        case HELP: Help(); break;
        case OPTIONS: optionsLogic(); break;
    }   
    touches.oldDown.destroy();
    for (unsigned long i = 0; i < touches.down.count(); i++ ){
        Vector3D v = touches.down[i];
        touches.oldDown.add(v);
    }
    touches.up.destroy();
    touches.down.destroy();
    touches.move.destroy();
}
//-------------------------
void Singleton::destroy(){
    puts("Bye");
    if (shape)
        delete shape;
    if (newShape)
        delete newShape;
    music.release();
    ss.freeData();
    ss.exit();
    pics.destroy();
}


