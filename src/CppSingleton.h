#ifndef _CPP_SINGLETON
#define _CPP_SINGLETON

#include <ctime>
#include "audio/SoundSystem.h"
#include "audio/OggStream.h"
#include "TextureLoader.h"
#include "Vectors.h"
#include "TouchData.h"
#include "fCommon.h"
#include "gui/Button.h"
#include "gui/Text.h"
#include "gui/YesNoDialog.h"
#include "gui/Scrollbar.h"
#include "SysConfig.h"
#include "Collisions.h"
#include "Utils.h"
#include "Threads.h"
#include "externals.h"
#include "GameBoard.h"
#include "Shape.h"
//-------------------------------------
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 480

enum GameStates{MENU, GAME, CREDITS, HELP, OPTIONS};



#ifndef __IPHONEOS__
//   #define _DEBUG_ 1
#endif


//============================================
class Singleton{
    
    void LoadFiles();
    void draw_intro();
    //void CreateFishTypes();
    void checkconfig(const char *name);
    void loadlang();
    void DrawAdventureMode(unsigned index, bool debug=false);
    void showstatus(int x, int y, unsigned type = 0);
    void mainMenuLogic();
    void xbox(PicsContainer& pics, int x, int y, int x1, int y1, COLOR c);
    void FishAI();
    void fish_atc(unsigned index);
    bool fishSmellsBait(unsigned fishindex, unsigned fishlikeswhat);
    void CheckPower(int max);
    void CheckPullout();
    void CheckLRButtons();
    void PullOut();
    void Throw();
   
    void punktas();
    void DrawRestaurant();
    void showfish(int x, int y, int c, int ind);
    
    void ShopLogic();
    void DrawShop();
    
    void DrawCredits();
    void Credits();
    void DrawHelp();
    void Help();
    void optionsLogic();
    void drawOptions();

    void DrawGame();
    void GameLogic();


public:
  
    GameStates GameState;

    int ScreenWidth;
    int ScreenHeight;
    bool windowed;

    char DocumentPath[255];

    unsigned char Keys[20];
    unsigned char OldKeys[20];
    Vector3D gamepad;
    
    SoundSystem ss;
    OggStream music;
    
    PicsContainer pics;
    
    
    
    int Ftim;
    
    
    bool ExitDialog_Active;
    
    
    float Alpha1;
    float Alpha2;
    
    TFont Font;

    
    
    
    
    int MouseXOld, MouseYOld, MouseX, MouseY, MouseButton, MouseButtonOld,
    fishx,fishy;
    
    
    Vector3D oldMoveTouch;
    
    char Key, OldKey;
    
    
    unsigned globalKEY;
    
    
    
    Button jrs0ul_button;
    Button Play_Button;
    Button Credits_Button;
    Button Help_Button;
    Button Options_Button;
    Button QuitButton;
    Button optionsOK_button;
    YesNoDialog yesno;
    Button more_button;
    Button prevHelpPage_button;
    Button nextHelpPage_button;
    Button helpBack_button;
    Button NoMusic_Button;
    
    
    
    
    unsigned maxHelpPage;
    unsigned activeHelpPage;
    
    ScrollBar musicVolumeBar;
    
    bool useAccel;
    Vector3D _acceleration;
    Vector3D firstTouch;
    Vector3D pos;
    
    SystemConfig sys;
    
    int clickCount;
    
    bool launchjrs0ul;
    bool launchmystore;

    TouchData touches;
    
    
    int loadingAnim;

    unsigned ticketIndex;

    bool Works;


    GameBoard gameBoard;
    Shape * shape;
    Shape * newShape;
    int lines;

    //---



    
    
    Singleton():
                jrs0ul_button(SCREEN_WIDTH/2 - 82, 148, 164, 32),
                
                Play_Button(SCREEN_WIDTH/2 - 64,
                            180, 128, 30),
                Credits_Button(SCREEN_WIDTH/2 - 64,
                               300, 128, 30),
                Help_Button(SCREEN_WIDTH/2 - 64,
                            260, 128, 30),
    
                Options_Button(SCREEN_WIDTH/2 - 64,
                               220, 128, 30),

                QuitButton(SCREEN_WIDTH/2 - 64,
                           340, 128, 30),
    
                
                more_button(10, SCREEN_HEIGHT-64, 100, 64),
                prevHelpPage_button(10, SCREEN_HEIGHT - 60, 48, 48),
                nextHelpPage_button(SCREEN_WIDTH-10-48, SCREEN_HEIGHT - 60, 48, 48),
                helpBack_button(25, 15, 60, 30, COLOR(0.7f, 0.7f, 1.0f)),
                NoMusic_Button(SCREEN_WIDTH/2 - 50, 2, 48, 50, COLOR(1,1,1,0.6f))
                
                      
    {




#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
                ScreenWidth = 320;
                ScreenHeight = 480;
#else
                ScreenWidth = 320;
                ScreenHeight = 480;
                windowed = false;
#endif

                clickCount = 0; GameState = MENU; 
                Ftim = 0;

                maxHelpPage = 2;
                    
                    
        
                //---
                    
                launchjrs0ul = false;
                launchmystore = false;
                
                    
                oldMoveTouch = Vector3D(-1,-1,0);
                loadingAnim = 0;

                Works = true;
                shape = 0;
                newShape = 0;
                lines = 0;
               }
    
    void init();
    void loadConfig();
    void logic();
    void render();
    void destroy();
    
};


#endif //_CPP_SINGLETON

