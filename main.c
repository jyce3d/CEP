#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "stdio.h"
#include <time.h>
#define CEP_STATUS_INTRO 0
#define CEP_STATUS_GAME 1
#define CEP_STATUS_DEATH 2

#define CEP_GAME_OVER 3
#define CEP_STATUS_NEXT 4

#define CEP_TXT_CENTER 1
#define CEP_TXT_LEFT 2

#define CEP_WND_WIDTH 320
#define CEP_WND_HEIGHT 240

#define CEP_DIR_RIGHT 1
#define CEP_DIR_LEFT 2

#define CEP_JMP_DIR 0
#define CEP_JMP_UP 1
#define CEP_JMP_LONG 1

#define CEP_ENEMY_SPAWNED 1
#define CEP_ENEMY_WAIT 0

#define TRUE 1
#define FALSE 0

/* Initialization des composants */
SDL_Window* pWindow = NULL;
TTF_Font *pFont =NULL;
SDL_Renderer* pRenderer = NULL;

typedef struct key_tag {
    int status;
    Uint32 last_up;
    Uint32 last_down;
} KeyStatus;

int status_score=0;
KeyStatus a_ks[4];

#define KS_RIGHT  0
#define KS_LEFT  1
#define KS_UP 2
#define KS_SPACE 3

#define KS_KEYDOWN 1
#define KS_KEYUP 2

#define CEP_MAX_ENEMY 3

#define CEP_TEXT_FILLED 1

#define CEP_MAX_EXERC 20



/*Initialisation des variables */
// île de la felicité
char ga_scene_1[20][40]= {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,0,2,3,3,3,3,3,3,3,4},
    { 0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4}
};
// Le gnouf
char ga_scene_2[20][40]= {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 4,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0,2,3,3,3,3,4,0,0,0,2},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,4,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,2,3,3,3,3,4},
    { 0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4}
};

char ga_scene_3[20][40]= {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,0,2,3,3,3,4,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1,-2,-3,-4,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-5,-6,-7,-8,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-9,-10,-11,-12,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-13,-14,-15,-16,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-17,-18,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4}
};
// Le gnouf
char ga_scene_4[20][40]= {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { 5,-20,-21,-23,-24,-20,-21,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,-20,-21,-23,5,6,6,6,6,7,-20,-21,-23,5},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { 5,6,6,6,7,-20,-21,-23,-24,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,-20,-21,-23,-24,5,6,6,6,6,7},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { 5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7}
};
// Le gnouf bas
char ga_scene_5[20][40]= {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-36,-37,-38,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { 5,6,6,7,-20,-21,-23,-24,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,-20,-21,-23, 5},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-36,-37,-38,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { 5,-20,-21,-23,-24,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 7},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-36,-37,-38,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-33,-24,-20,-21,-23,-30,-32,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { 5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7}
};
// sortie
char ga_scene_6[20][40]= {
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7},
   { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { 5,6,6,7,-20,-21,-23,-24,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 7},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24,-20,-21,-23,-24},
    { 5,6,6,6,6,6,-20,-21,-23,-24,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6, 7},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-36,-37,-38,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-36,-37,-38,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-32,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { -20,-21,-23,-24,-20,-21,-23,-24,-30,-31,-33,-24,-20,-21,-23,-30,-32,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-30,-31,-32,-23,-24,-20,-21,-23,-24},
    { 5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7}
};

char ga_title_1[255] = "HELENILE";
char ga_title_2[255] = "SELENILE";
char ga_title_3[255] = "FELICILE";
char ga_title_4[255] = "LE GNOUF BAS";
char ga_title_5[255] = "LE GNOUF HAUT";
char ga_title_6[255] = "LE GNOUF SORTIE";

int g_cur_level = 0;

char (*ga_scene)[40];

char ga_exerc_1[20][255] = { {"45 : 9 = ?"}, {"27+32 = 5?"}, {"653-77=5?6"}, {"245+89=33?"}, {"570+158 = 7?8"}, {"547 + 238 = 7?5"}, {"857 - 424=43?"}, {"942 - 321 = 62?"},
{"4+7-3-6-5 = -?"}, {"11+(-7)=?"}, {"-2 - ? = -10" }, {"3 + ? =11"}, {"5 - ?  = -4"}, { "8,3 + 8, 7 = 1?"}, {"5,4 + 12, ? = 17,5"}, {"10,2 - 1,3 = 8,?"}, {"? + 8 = 14"},
{"? + 3,1 = 6,1"}, {"1 - (-11) = 1?"}, {"65 + 10:2 = 7?"} };
char ga_exerc_sol_1[20] = {5, 9, 7, 4, 2, 8, 3, 1, 3, 4, 8, 8, 9,7 , 1, 9, 6, 3, 2, 0};


char ga_exerc_2[20][255] = { {"4 X (3+9)  = 4?"}, {"(27+30)/3= ?9"}, {"7+3 X (2+8) =3?"},  {"(3 X 2-6+10) X 5=5? "}, 
{"(6+9)X(8-5)X2 = ?0"}, {"(4 X 3+8-10)X7=?0"}, {"(5+6-3)X2+7)=?3"}, {"4+10X(9-8+2)=?4"}, {"16 X 5:2 X 5 X 8:4= ? 00"}, {"23+15 X 2 = 5?"}, {"45-22+58 X 2 = ?39"},
{"(12+20) X 2 -14 + 56 = 10?"}, {"2 X 5 + (12 + 6):6=1?"}, {"45 X 6 - 96 +14 = 1?8"}, {"56+25 X 8 = ?56"}, {"45-12 + 58 X 9 = 55?"}, {"45 + 5 x 8= 8?"},
{"9+ (2 + 8):2=8?"}, {"8 X 9 + 8 = 8?"}, {"125 X 8 - 1 = 9?9"} };
char ga_exerc_sol_2[20] = {8, 1, 7, 0,9,
7,2,3, 4, 3, 1,6, 3, 8, 2, 5, 5, 6, 0, 9};

char ga_exerc_3[20][255] = { {"6+8.(x+7) = -98 => x=-?0"}, {"3x + 15 = -2x => x=?"}, {"7 + 5x = 7x - 13 => x=1?"}, 
{"x-8 = 10 => x=?8"},{"3x = 6 => x=?"},{"x+3=-8 => x=-1?"},{"3x-6(3-4x)=9x-2 => x=1?/30"},{"3(2-3x)-(4+5x)=0 => x=1/?"}, {"3x-5 = 0 => 5 / ?"}, {"x-3 = -3 => x=?"},
{"x-2 = 2x -4 => x=?"}, {"3x=4 => x=4/?"}, {"2(x-2)= 8 => x=?"}, {"1-x = -7+3 => x=?"}, {"2x=3 => x=3 / ?"}, {"3x+4 = 6x+9 => -? / 3"}, {"x+6 = 9 => x=?"}, {"x/6 = 2 => x=?2"},
{"2x - 7.8 = 56 => x=11?"}, {"6x+7x-13 => x=?"} };
char ga_exerc_sol_3[20] = {2, 5, 0, 
1, 2, 1, 6, 7, 3, 0, 2, 3, 6, 5, 2, 5,3, 1, 2, 1};

char *ga_title;
char ga_exerc[255];
char ga_exerc_sol;

int sel_exerc =0;
int status = CEP_STATUS_INTRO;
int difficulty =0;
int q=0;
int sfc_loaded=0;
int x_saut =0;
int max_enemy = 1;

Uint32 last_time;
/* Initialization des éléments graphiques */

SDL_Surface* level_sfc = NULL;
SDL_Texture* pScene = NULL;
SDL_Texture* pFlipTexture = NULL;

SDL_Texture* pPlayer = NULL;
SDL_Texture* pEnemy = NULL;

SDL_Texture* pCoins = NULL;

/* Définition des mosaiques */
SDL_Rect space = {32,0,8,8};
SDL_Rect sky = {24,0, 8,8};
SDL_Rect gnd3 = {16,0,8,8};
SDL_Rect gnd2 = {8,0,8,8};
SDL_Rect gnd1 = {0,0,8,8};
SDL_Rect tree1 = {0,8,8,8};
SDL_Rect tree2 = {8,8,8,8};
SDL_Rect tree3 = {16,8,8,8};
SDL_Rect tree4 = {24,8,8,8};
SDL_Rect tree5 = {0,16,8,8};
SDL_Rect tree6 = {8,16,8,8};
SDL_Rect tree7 = {16,16,8,8};
SDL_Rect tree8 = {24,16,8,8};
SDL_Rect tree9 = {0,24,8,8};
SDL_Rect tree10 = {8,24,8,8};
SDL_Rect tree11 = {16,24,8,8};
SDL_Rect tree12 = {24,24,8,8};
SDL_Rect tree13 = {0,32,8,8};
SDL_Rect tree14 = {8,32,8,8};
SDL_Rect tree15 = {16,32,8,8};
SDL_Rect tree16 = {24,32,8,8};
SDL_Rect tree17 = {16,40,8,8};
SDL_Rect tree18 = {24,40,8,8};

SDL_Rect brik1 = {40,0,8,8};
SDL_Rect brik2 = {48,0,8,8};

SDL_Rect brik_dk1 = {56,0,8,8};
SDL_Rect brik_dk2 = {64,0,8,8};

SDL_Rect gnd_dk1 = {72,0,8,8};
SDL_Rect gnd_dk2 = {80,0,8,8};
SDL_Rect gnd_dk3 = {88,0,8,8};

SDL_Rect jail_1 = {97,0,8,8};
SDL_Rect jail_2 = {105,0,8,8};
SDL_Rect jail_3 = {113,0,8,8};
SDL_Rect jail_4 = {97,16,8,8};
SDL_Rect jail_5 = {105,16,8,8};
SDL_Rect jail_6 = {113,16,8,8};
SDL_Rect jail_7 = {97,8,8,8};
SDL_Rect jail_8 = {105,8,8,8};
SDL_Rect jail_9 = {113,8,8,8};

/* Définition des sprites */
SDL_Rect spr_player_right[3] = { {0,0, 12, 16}, {32, 0, 15, 16}, {48,0, 15,16} };
SDL_Rect spr_player_left[3] = { {2,16, 15, 16}, {17, 16, 15, 16}, {52,16, 12,16}};

SDL_Rect spr_player_dead[1] = { {0,32, 15,15}};

SDL_Rect spr_player_jmpr = {16,0,15, 16};
SDL_Rect spr_player_jmpl = {32,16,15, 16};

// Paramètres
int score = 0;
int high_score =0;
int vie = 3;

// Enemy
SDL_Rect spr_enemy[3]= { {0,0,16,16 }, {16,0,16,16}, {32,0,16,16} };
SDL_Rect spr_enemy_dest = {0, 0, 16,16};
SDL_Rect spr_coin_dest = {0,0, 15,15};
SDL_Rect spr_fruct_dest = {0,0,15,15};
int enemy_x[CEP_MAX_ENEMY] = {16, 128, 64};
int enemy_y[CEP_MAX_ENEMY] = {84, 16, 16};
int enemy_sens_x[CEP_MAX_ENEMY]={0, 0,0};
int enemy_status[CEP_MAX_ENEMY] = {1, 1, 1};
int enemy_waiting[CEP_MAX_ENEMY] = {0,0, 0};

// Coins
SDL_Rect spr_coins[10] = { {0,0,15,15} , {15,0,15,15}, {31,0,15,15}, {47,0,15,15}, {63,0,15,15},
{79,0,15,15}, {95,0,15,15}, {111,0,15,15}, {127,0,15,15}, {143,0,15,15}};
int coins_x[10] = {32, 128, 304, 64, 96, 286, 80, 176, 224, 288 };
int coins_y[10] = {16, 16, 16, 64, 64, 64,112,112,112,112 };
SDL_Rect spr_fructs[1] = { {160,0,15,15} };
int fructs_x[1] = {200};
int fructs_y[1] = {112};
int sel_fruct_idx = -1;
int status_fruct = 0;
int fruct_deltay= -4;
int fruct_cp = 0;

SDL_Rect spr_player_dest = {0,0,16,16};
int play_x = 16;
int play_y = 136;
unsigned int direction = CEP_DIR_RIGHT; // bit 15=1 => jmp , 
unsigned int jmp_direction = CEP_JMP_DIR;

void Initialize_Fructs() {
    fructs_x[0] = 200;
    fructs_y[0] = 112;

    sel_fruct_idx = -1;
    status_fruct = 0;
    fruct_deltay= -4;
    fruct_cp = 0;

}
void Initialize_ks() {
    
    a_ks[KS_RIGHT].status = KS_KEYUP;
    a_ks[KS_RIGHT].last_up =0;
    a_ks[KS_LEFT].status = KS_KEYUP;
    a_ks[KS_LEFT].last_up =0;
    a_ks[KS_UP].status = KS_KEYUP;
    a_ks[KS_UP].last_up =0;
}
void Remove_Fruct(int idx) {
                        fructs_x[idx] =fructs_y[idx] = -1;
                        fruct_cp = 0;
                        status_fruct = 0;
                        fruct_deltay = -4;
                        sel_fruct_idx = -1;

}
int set_scene_selection() {
    sfc_loaded = 0;
    switch (g_cur_level % 6) {
        case 0:
           ga_scene = ga_scene_1;
           ga_title = ga_title_1;
        break;
        case 1:
           ga_scene = ga_scene_2;
           ga_title = ga_title_2;
        break;
        case 2:
           ga_scene = ga_scene_3;
           ga_title = ga_title_3;
        break;
        case 3:
           ga_scene = ga_scene_4;
           ga_title = ga_title_4;
        break;
        case 4:
           ga_scene = ga_scene_5;
           ga_title = ga_title_5;
        break;
        
        case 5: 
           ga_scene = ga_scene_6;
           ga_title = ga_title_6;
        break;

    }
    return 0;
}


void spawn_enemy(int idx) {
     enemy_x[idx] = (((rand()) % 30)+5)*8;   
     enemy_y[idx] = 16;
}
void initialize_level() {
    play_x = 16;
    play_y = 136;
    for (int i=0;i<max_enemy;i++) {
        enemy_waiting[i] = 0;
        spawn_enemy(i);
    }
    direction &= 32767; // annule le saut au cas ou
    Initialize_ks();
    Initialize_Fructs();

}

void display_enemy(int idx) {

        if (enemy_status[idx]==CEP_ENEMY_SPAWNED) {
            spr_enemy_dest.x = enemy_x[idx];
            spr_enemy_dest.y = enemy_y[idx];

            SDL_RenderCopy(pRenderer, pEnemy, &spr_enemy[enemy_x[idx] %3], &spr_enemy_dest);
        } else {
            enemy_waiting[idx]+=1;
            if (enemy_waiting[idx]>=50) {
                enemy_status[idx] = CEP_ENEMY_SPAWNED;
                spawn_enemy(idx);
                enemy_waiting[idx]=0;
            }
            
        }
}

void deplace_enemy() {
    int pos_en_y = 0;
  
    for (int i=0;i<max_enemy;i++) {
        pos_en_y = (enemy_y[i] +16) /8;

        if ((ga_scene[pos_en_y][(enemy_x[i]+16)/8]<=0) && (ga_scene[pos_en_y][(enemy_x[i])/8]<=0)  ) {
            enemy_y[i]++;
            enemy_sens_x[i]=0;
        } else {
            if (enemy_sens_x[i] ==0 ) {
                if ( ((rand()) % 10)>=5) enemy_sens_x[i]=1;
                    else enemy_sens_x[i] = -1;
            }
            if (enemy_sens_x[i] ==-1) {
                if ( (enemy_x[i]--)<=0) {
                    if (enemy_y[i]>=136) {
                        enemy_status[i]=CEP_ENEMY_WAIT;
                    } else
                        enemy_sens_x[i] =1;
                }
                } else if (enemy_sens_x[i] ==1) {
                    if ((enemy_x[i]++)>=304) enemy_sens_x[i] =-1;
                }
        }   
        display_enemy(i);
    }
}
int jmp_type = -1;
Uint32 lastup_down=0;

int x_saut_index = 0;

int costume =0;
/* Définition des fonctions */
int Trajectoire_Saut( int x_saut) {
    int y;
    float delta = 5.33f;
    if (jmp_type==CEP_JMP_LONG)
        delta = 2.0f *delta;
    if (x_saut>24)
        y=delta /2;
    else    
        y=-delta /2 ;
    return y;
}

int Create() {
    if (SDL_Init(SDL_INIT_VIDEO) !=0) {
        printf("Erreur d'initialisation de la SDL : %s\n", SDL_GetError() );
        return -1;
    }

    pWindow = SDL_CreateWindow("CEP - Certificat D'étude Primate", 
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                CEP_WND_WIDTH, CEP_WND_HEIGHT,SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI );
    SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
                            
    if (pWindow) {
            if (!TTF_Init()) {
                if ( !(pFont = TTF_OpenFont("freefont/FreeMono.ttf", 16)) ) {
                    printf("Erreur lors du chargement de la font %s \n", SDL_GetError());
                    return -1;
                } else {
                    if ((pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) )==NULL) {
                        printf("Erreur lors de la création du Renderer %s \n", SDL_GetError());
                        return -1;
                    } else {
                        level_sfc = IMG_Load("level.bmp");
                        SDL_Surface* player_sfc = IMG_Load("player.bmp");
                        SDL_SetColorKey(player_sfc, SDL_TRUE, SDL_MapRGB(player_sfc->format, 0xFF, 0xFF, 0xFF));
                        pPlayer = SDL_CreateTextureFromSurface(pRenderer, player_sfc);
                        SDL_FreeSurface(player_sfc);
                        SDL_Surface* enemy_sfc = IMG_Load("enemy.bmp");
                        SDL_SetColorKey(enemy_sfc, SDL_TRUE, SDL_MapRGB(enemy_sfc->format, 0xFF, 0xFF, 0xFF));
                        pEnemy = SDL_CreateTextureFromSurface(pRenderer, enemy_sfc);
                        SDL_FreeSurface(enemy_sfc);
                        SDL_Surface* coins_sfc = IMG_Load("coins.bmp");
                        SDL_SetColorKey(coins_sfc, SDL_TRUE, SDL_MapRGB(coins_sfc->format, 0xFF, 0xFF, 0xFF));
                        pCoins = SDL_CreateTextureFromSurface(pRenderer, coins_sfc);
                        SDL_FreeSurface(coins_sfc);
                                              //SDL_Surface* flip_sfc = SDL_CreateRGBSurface()
                        //pFlipTexture = SDL_CreateTextureFromSurface(flip_sfc);
                        SDL_ShowCursor(SDL_DISABLE );

                        return 1;
                    }
                }
            } else {
                printf("Erreur lors de la création de TTF_Init %s \n", SDL_GetError());
                return -1;

            }
    } else {
        printf("Erreur lors de la création de la fenêtre %s \n", SDL_GetError());
        return -1;
    }
}

void Destroy() {
    SDL_DestroyTexture(pEnemy);
    SDL_DestroyTexture(pPlayer);
    SDL_DestroyTexture(pScene);
    SDL_DestroyTexture(pCoins);
    SDL_DestroyTexture(pFlipTexture);
    SDL_FreeSurface(level_sfc);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}

void Display_Text(const char* pszTitle, int attrb, SDL_Color *pColor, int x, int y, int filled) {
    SDL_Surface* pSurface = TTF_RenderText_Solid(pFont, pszTitle, *pColor );
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
    SDL_FreeSurface(pSurface);
    int texW, texH;
    SDL_QueryTexture(pTexture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = {0,0, texW, texH};
    switch(attrb) {
        case CEP_TXT_CENTER:
            dstrect.x = (CEP_WND_WIDTH - texW) /2;
            dstrect.y = y;
        break;
        case CEP_TXT_LEFT:
            dstrect.x = x;
            dstrect.y = y;
        break;
        default:
        break;
    }
    if (filled == 1) {
        SDL_SetRenderDrawColor( pRenderer, 0, 0, 0, 0 );
        SDL_RenderFillRect( pRenderer, &dstrect );
    }
    SDL_RenderCopy(pRenderer, pTexture, NULL, &dstrect );
    SDL_DestroyTexture(pTexture);
}
void Update_Intro() {
        SDL_Color color = {255,0,0};
        SDL_SetRenderDrawColor(pRenderer, 0,0,0, 255);
        SDL_RenderClear(pRenderer);
        Display_Text("Menu du jeu", CEP_TXT_CENTER, &color, 0,0, 0);
        Display_Text("1 Niveau facile", CEP_TXT_LEFT, &color, 0,32, 0);
        Display_Text("2 Niveau moyen (PEMDAS)", CEP_TXT_LEFT, &color, 0,48, 0);
        Display_Text("3 Niveau difficile (Equations)", CEP_TXT_LEFT, &color, 0,64, 0);

      //  SDL_RenderPresent(pRenderer);
}

void Update_GameOver() {
        SDL_Color color = {255,0,0};
        SDL_SetRenderDrawColor(pRenderer, 0,0,0, 255);
        SDL_RenderClear(pRenderer);
        Display_Text("Fin du Jeu", CEP_TXT_CENTER, &color, 0,96,0);
        char s_params[255];
        sprintf(s_params,"Score :%d", score);
        Display_Text(s_params, CEP_TXT_CENTER, &color, 0,104,0);
        if (score>high_score) {
            high_score = score;
            Display_Text("Nouveau High Score", CEP_TXT_CENTER, &color, 0,112,0);
        }
        vie =3;
        score =0;
        SDL_RenderPresent(pRenderer);
        SDL_Delay(2500);
        status = CEP_STATUS_INTRO;
        sfc_loaded = 0;
        g_cur_level=0;
        direction = CEP_DIR_RIGHT;

}
void choose_level() {
    sel_exerc = rand() % CEP_MAX_EXERC;
    switch (difficulty) {
        case 1: 
            sprintf(ga_exerc, "%s", ga_exerc_1[sel_exerc]);
            ga_exerc_sol = ga_exerc_sol_1[sel_exerc];
        break;
        case 2: 
            sprintf(ga_exerc, "%s",ga_exerc_2[sel_exerc]);
            ga_exerc_sol = ga_exerc_sol_2[sel_exerc];
        break;
        case 3: 
            sprintf(ga_exerc, "%s", ga_exerc_3[sel_exerc]);
            ga_exerc_sol = ga_exerc_sol_3[sel_exerc];
        break;

    }
}
void Update_NextLevel() {
        SDL_Delay(2500);
        g_cur_level ++;
        set_scene_selection();
        initialize_level();
        choose_level();
        score = score +1000;

        if ( g_cur_level % 6 == 0)
            if (max_enemy<3) max_enemy++;

        status = CEP_STATUS_GAME;
        direction = CEP_DIR_RIGHT;
  
}

void Process_Intro(SDL_Event* pEvent) {
    SDL_KeyboardEvent *key=NULL;
    switch(pEvent->type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP:

            key = &(pEvent->key);
            if (key->keysym.sym==SDLK_1) {
                difficulty = 1;
                status = CEP_STATUS_GAME;
                choose_level();

            } else if (key->keysym.sym==SDLK_2) {
                difficulty = 2;
                status = CEP_STATUS_GAME;
                choose_level();

            } else if (key->keysym.sym==SDLK_3) {
                difficulty = 3;
                status = CEP_STATUS_GAME;
                choose_level();
            }

        break;
    }
}

void Init_Scene() {
    SDL_Surface* scene_sfc = SDL_CreateRGBSurface(0,CEP_WND_WIDTH,CEP_WND_HEIGHT,32,0,0,0,0);
    SDL_Rect dest_rect;
    sel_fruct_idx = -1;
    dest_rect.w=8;
    dest_rect.h=8;
    for (int i=0; i<40;i++) { // parcours des colonnes de la matrice
        for (int j=0;j<20;j++) {
            dest_rect.x=i*8;
            dest_rect.y=j*8;
            switch (ga_scene[j][i]) {
                case -1:
                    SDL_BlitSurface(level_sfc, &tree1, scene_sfc, &dest_rect);
                break;
                case -2:
                    SDL_BlitSurface(level_sfc, &tree2, scene_sfc, &dest_rect);
                break;
                case -3:
                    SDL_BlitSurface(level_sfc, &tree3, scene_sfc, &dest_rect);
                break;
                case -4:
                    SDL_BlitSurface(level_sfc, &tree4, scene_sfc, &dest_rect);
                break;
                case -5:
                    SDL_BlitSurface(level_sfc, &tree5, scene_sfc, &dest_rect);
                break;

                case -6:
                    SDL_BlitSurface(level_sfc, &tree6, scene_sfc, &dest_rect);
                break;
                case -7:
                    SDL_BlitSurface(level_sfc, &tree7, scene_sfc, &dest_rect);
                break;
                case -8:
                    SDL_BlitSurface(level_sfc, &tree8, scene_sfc, &dest_rect);
                break;
                case -9:
                    SDL_BlitSurface(level_sfc, &tree9, scene_sfc, &dest_rect);
                break;
                case -10:
                    SDL_BlitSurface(level_sfc, &tree10, scene_sfc, &dest_rect);
                break;
                case -11:
                    SDL_BlitSurface(level_sfc, &tree11, scene_sfc, &dest_rect);
                break;
                case -12:
                    SDL_BlitSurface(level_sfc, &tree12, scene_sfc, &dest_rect);
                break;
                case -13:
                    SDL_BlitSurface(level_sfc, &tree13, scene_sfc, &dest_rect);
                break;
                case -14:
                    SDL_BlitSurface(level_sfc, &tree14, scene_sfc, &dest_rect);
                break;
                case -15:
                    SDL_BlitSurface(level_sfc, &tree15, scene_sfc, &dest_rect);
                break;
                case -16:
                    SDL_BlitSurface(level_sfc, &tree16, scene_sfc, &dest_rect);
                break;
                case -17:
                    SDL_BlitSurface(level_sfc, &tree17, scene_sfc, &dest_rect);
                break;
                case -18:
                    SDL_BlitSurface(level_sfc, &tree18, scene_sfc, &dest_rect);
                break;

                case 0:
                    SDL_BlitSurface(level_sfc, &sky, scene_sfc, &dest_rect);
                break;
                case 1:
                    SDL_BlitSurface(level_sfc, &space, scene_sfc, &dest_rect);
                break;
                case 2:
                    SDL_BlitSurface(level_sfc, &gnd1, scene_sfc, &dest_rect);
                break;
                case 3:
                    SDL_BlitSurface(level_sfc, &gnd2, scene_sfc, &dest_rect);
                break;
                case 4:
                    SDL_BlitSurface(level_sfc, &gnd3, scene_sfc, &dest_rect);
                break;
                case -20:
                    SDL_BlitSurface(level_sfc, &brik1, scene_sfc, &dest_rect);
                break;
                case -21:
                    SDL_BlitSurface(level_sfc, &brik2, scene_sfc, &dest_rect);
                break;
                case -23:
                    SDL_BlitSurface(level_sfc, &brik_dk1, scene_sfc, &dest_rect);
                break;
               case -24:
                    SDL_BlitSurface(level_sfc, &brik_dk2, scene_sfc, &dest_rect);
                break;
               case -30:
                    SDL_BlitSurface(level_sfc, &jail_1, scene_sfc, &dest_rect);
                break;
               case -31:
                    SDL_BlitSurface(level_sfc, &jail_2, scene_sfc, &dest_rect);
                break;
               case -32:
                    SDL_BlitSurface(level_sfc, &jail_3, scene_sfc, &dest_rect);
                break;
               case -33:
                    SDL_BlitSurface(level_sfc, &jail_4, scene_sfc, &dest_rect);
                break;
               case -34:
                    SDL_BlitSurface(level_sfc, &jail_5, scene_sfc, &dest_rect);
                break;
               case -35:
                    SDL_BlitSurface(level_sfc, &jail_6, scene_sfc, &dest_rect);
                break;
               case -36:
                    SDL_BlitSurface(level_sfc, &jail_7, scene_sfc, &dest_rect);
                break;
               case -37:
                    SDL_BlitSurface(level_sfc, &jail_8, scene_sfc, &dest_rect);
                break;
               case -38:
                    SDL_BlitSurface(level_sfc, &jail_9, scene_sfc, &dest_rect);
                break;


               case 5:
                    SDL_BlitSurface(level_sfc, &gnd_dk1, scene_sfc, &dest_rect);
                break;
               case 6:
                    SDL_BlitSurface(level_sfc, &gnd_dk2, scene_sfc, &dest_rect);
                break;
               case 7:
                    SDL_BlitSurface(level_sfc, &gnd_dk3, scene_sfc, &dest_rect);
                break;

                 
            }
        }
    }
    if (pScene !=NULL) SDL_DestroyTexture(pScene);
    pScene = SDL_CreateTextureFromSurface(pRenderer, scene_sfc);
    SDL_FreeSurface(scene_sfc);


}
// Return true if still jumping
int jmp_criteria(int idx_x, int idx_y, int verbose ) {
    char s_params[2];
    int ga_r = (play_y+idx_y) / 8;
    int ga_c = (play_x+idx_x) / 8 ;
    SDL_Color color = {255,255,255};
    // affiche le curseur
    if (verbose==1) {
        sprintf(s_params, "I");
        printf("y = %d et idx_y=%d et ga_scene=%d, ga_r=%d, ga_c=%d\n", play_y, idx_y, ga_scene[ga_r][ga_c], ga_r, ga_c);
        Display_Text(s_params, CEP_TXT_LEFT , &color, ga_c*8,ga_r*8, 0);
    }
    return (ga_scene[ga_r][ga_c] <=0);
}


void Move_Monkey() {
                if (a_ks[KS_RIGHT].status == KS_KEYDOWN) {
                    if ( (play_x+=2)>=304 )
                        play_x = 304;
                  direction = CEP_DIR_RIGHT;
                  costume ++;
                  costume = costume % 3;
                }
                if (a_ks[KS_LEFT].status == KS_KEYDOWN) {
                    if ( (play_x-=2)<=0)
                        play_x = 0;
                    direction = CEP_DIR_LEFT;
                    costume ++;
                    costume = costume % 3;
                }
                if (a_ks[KS_UP].status == KS_KEYDOWN) {
                    if (direction == CEP_DIR_LEFT)
                        x_saut = 48;
                    else {
                        x_saut=0;
                    }
                    // si right, left relachés alors saut haut sinon saut dans la direction
                    if ((a_ks[KS_RIGHT].status == KS_KEYUP) && (a_ks[KS_LEFT].status == KS_KEYUP)) {
                        jmp_direction = CEP_JMP_UP;
                        jmp_type = 0;
                    }
                    else {
                        jmp_direction = CEP_JMP_DIR;
                    }                
                    if (lastup_down == 0)
                    lastup_down = SDL_GetTicks();
                } 

}

int is_collided() {
    int x1 = play_x +8;
    int y1 = play_y +8;
    int x2 = 0;
    int y2 = 0;
    int x3 = 0;
    int y3= 0;
    if (sel_fruct_idx !=-1) {
        x3= fructs_x[sel_fruct_idx];
        y3= fructs_y[sel_fruct_idx];
    }

    for (int i=0; i<max_enemy;i++ ) {
 
        x2 = enemy_x[i]+8 ;
        y2 = enemy_y[i] + 8;
        if (  abs(x1-x2) <=8 && abs(y1-y2) <=8 )
            return 1;
        if (  abs(x1-x2) <=8 && abs(y1-y2) <= 16  ) 
            status_score = 1;
        if ( sel_fruct_idx != -1) {

            if (abs(x2-x3) <=8 && abs(y3-y2) <=16 ) {
  
                status_score =1;
                Remove_Fruct(sel_fruct_idx);
                
                enemy_status[i]=CEP_ENEMY_WAIT;
                enemy_x[i]=0;
                enemy_y[i]=0;
            }
        }
    }
    // Collision with coins
    if ((direction & 32768) ==0)
        return 0;

    for (int i=0; i<10; i++) {
        x2 = coins_x[i]+8 ;
        y2 = coins_y[i] + 8;
        if (  abs(x1-x2) <=8 && abs(y1-y2) <=8 ) {
            if (i == ga_exerc_sol) 
                status= CEP_STATUS_NEXT;
            else
                return 1;
        }
        
    }
    // collision with fructs
    for (int i=0;i<1; i++) {
        x2= fructs_x[i]+8;
        y2 = fructs_y[i]+8;
       if (  abs(x1-x2) <=8 && abs(y1-y2) <=8 ) {
        if (sel_fruct_idx == -1 ) {
            sel_fruct_idx = i;
            status_fruct = 0;
        }
       }
    }

    return 0;
}

void Update_Game() {
 
   
        // Affichage des paramètres:

        SDL_Delay(30);
        last_time = SDL_GetTicks();
        if (sfc_loaded==0) {
            Init_Scene(); // si on change de niveau et que la scene doit être recréé via une nouvelle surface.
            initialize_level(); // sprites coordinates;
            sfc_loaded=1;
        }

        // Create Screen

        SDL_Rect rct_scene = {0,0,CEP_WND_WIDTH,CEP_WND_HEIGHT};
        SDL_RenderCopy(pRenderer, pScene, &rct_scene, &rct_scene );
 // Display coins
        for (int i=0;i<10;i++) {
            spr_coin_dest.x = coins_x[i];
            spr_coin_dest.y = coins_y[i];
            SDL_RenderCopy(pRenderer, pCoins, &spr_coins[i], &spr_coin_dest);
        }
        // display fructs
  
        for (int i=0; i<1;i++) {
   
            if ((sel_fruct_idx ==i) )
            {
                if (status_fruct == 0) {
                    fructs_x[i] = play_x;
                    fructs_y[i] = play_y - 8;
                } else {
                    // tester la direction
                        if (status_fruct == CEP_DIR_RIGHT) {
                            fructs_x[i] += 4;
                        } else if (status_fruct == CEP_DIR_LEFT) {
                            fructs_x[i] -=4;
                        }

                    // tester les limites hauteur
                        fructs_y[i] += fruct_deltay;

                        fruct_cp ++;
                        if ((fruct_cp % 3)==0 ) {
                            fruct_deltay = - fruct_deltay;
                            fruct_cp = 0;
                        } 
                        
        
                    // tester limite longueur
                    if (fructs_x[i] ==0 || fructs_x[i] >=320) 
                        Remove_Fruct(i);
                    
                }
            } // end if
            spr_fruct_dest.x = fructs_x[i];
            spr_fruct_dest.y = fructs_y[i];
            if (fructs_x[i] >0 && fructs_y[i] >0 )
                SDL_RenderCopy(pRenderer, pCoins, &spr_fructs[i], &spr_fruct_dest);
        } // end for

        // Collision
        if (is_collided()) {
            status=CEP_STATUS_DEATH;
        } else {
        // Process Display
 
            if ((direction & 32768)==0) {
            // controle chute hors saut
                jmp_type = -1;
                if (direction == CEP_DIR_RIGHT) {
                    // on check devant et derrière => si roche derriere on ne tombe pas quelque soit la direction dans laquelle on va
                    if (jmp_criteria(16,16,0) && jmp_criteria(0,16,0) ) {
                        jmp_type = 0;
                        play_y += Trajectoire_Saut(32);

                    }
                    else {
                        play_y -= play_y %8;
                        Move_Monkey(); // déplacement du singe et mise en place des costumes (voir)
                    }

                } else if (direction == CEP_DIR_LEFT) {
                    if (jmp_criteria(0,16,0) && jmp_criteria(16,16,0)) {
                        play_y += Trajectoire_Saut(32);
                        jmp_type = 0;
                    }
                    else {
                        play_y -= play_y %8;
                        Move_Monkey();
                    }

                }
                // Check une touche up appuyée pour initier le saut.
                if (a_ks[KS_UP].status == KS_KEYUP) {
                    if (lastup_down>0) {
                        int diff = (SDL_GetTicks() - lastup_down);
                        if ( diff >= 250) 
                          jmp_type = CEP_JMP_LONG; else jmp_type =0;
                        direction |= 32768;
                        lastup_down = 0;
                    }
                }

                spr_player_dest.x = play_x;
                spr_player_dest.y = play_y;
                if (direction == CEP_DIR_RIGHT) 
                    SDL_RenderCopy(pRenderer, pPlayer, &spr_player_right[costume], &spr_player_dest);
                else if (direction == CEP_DIR_LEFT)
                    SDL_RenderCopy(pRenderer, pPlayer, &spr_player_left[costume], &spr_player_dest);
            } else { // Jumping
            // Process JMP
            // Si en saut et que l'on tombe sur un mur au moment où il s'arrête.
            // 1. Detect long jmp
            // x_saut_index défini saut droit ou saut dans une direction (inc ou dec x de 2)
                if (jmp_direction == CEP_JMP_UP)
                    x_saut_index = 0; else x_saut_index=2;
                if ((direction & 32767) == CEP_DIR_LEFT) {
                    if ((play_x-=x_saut_index)<=0)
                        play_x = 0;
                    x_saut -=2;
                    play_y = play_y - Trajectoire_Saut(x_saut);
                    if ((x_saut<24) && !jmp_criteria(0,16,0)) {
                        play_y -= play_y %8;
                        direction &=32767; // annule l'état saut
                    } else if (x_saut >=24 && !jmp_criteria(0,0,0)) {
                    // on force la descente et on force un saut court pour éviter qu'il s'enfonce la tête dans le mur.
                        jmp_type =0;
                        x_saut = 22;
                    }
                } else if ((direction & 32767) == CEP_DIR_RIGHT ) {
                    if ((play_x+=x_saut_index)>=304)
                        play_x= 303;
                 x_saut +=2;
                 play_y = play_y + Trajectoire_Saut(x_saut);
                //descente
                 if ((x_saut>24) && !jmp_criteria(16,16,0)  ) {
                        play_y -= play_y %8;
                        direction &=32767;  // annule l'état saut
                        if (status_score ==1) score=score +200;
                        status_score =0;
                   } else if (x_saut<=24 && !jmp_criteria(16,0,0)) { 
                    // Si le saut était long et que l'on tombe sur une plateforme, on racourcit le saut
                      jmp_type = 0;
                      x_saut = 26; // on force la descente et on force un saut court pour éviter qu'il s'enfonce la tête dans le mur.
                    }

                }
                spr_player_dest.x = play_x;
                spr_player_dest.y = play_y;
                if ((direction & 32767)==CEP_DIR_RIGHT) 
                    SDL_RenderCopy(pRenderer, pPlayer, &spr_player_jmpr, &spr_player_dest);
                else if ((direction & 32767)==CEP_DIR_LEFT)
                    SDL_RenderCopy(pRenderer, pPlayer, &spr_player_jmpl, &spr_player_dest);

            }
        // Process Enemy

            deplace_enemy();
        }
    
    SDL_SetRenderDrawColor(pRenderer, 0,0,0, 255);
    SDL_Color color = {255,255,255};
    char s_params[255];
    sprintf(s_params, "Score=%d        HIGH Score= %d", score, high_score);
    Display_Text(s_params, CEP_TXT_LEFT , &color, 0,164,0);
    sprintf(s_params, "Vie(s)=%d", vie);
    Display_Text(s_params, CEP_TXT_LEFT , &color, 0,180, 0);
    sprintf(s_params, "%s", ga_exerc);
    Display_Text(s_params, CEP_TXT_CENTER , &color,0, 0, CEP_TEXT_FILLED);
    sprintf(s_params, "%s", ga_title);
    Display_Text(s_params, CEP_TXT_CENTER, &color, 0,196, 0);
    

    //SDL_RenderPresent(pRenderer);
}
void renderer_present() {
    //SDL_SetRendererTarget()
    SDL_RenderPresent(pRenderer);
}
void update_death() {
        // Create Screen
    SDL_Rect rct_scene = {0,0,CEP_WND_WIDTH,CEP_WND_HEIGHT};
    SDL_RenderCopy(pRenderer, pScene, &rct_scene, &rct_scene );

    for (int i=0;i<max_enemy;i++)
       display_enemy(i);

    SDL_RenderCopy(pRenderer, pPlayer, &spr_player_dead[0], &spr_player_dest);
    SDL_RenderPresent(pRenderer);

    SDL_Delay(2500);
    direction = CEP_DIR_RIGHT;
    vie --;
    if (vie>0) {
        initialize_level();

        status = CEP_STATUS_GAME;
    } else 
        status = CEP_GAME_OVER;

}
void update_status() {
            SDL_SetRenderDrawColor(pRenderer, 0,0,0, 255);
        SDL_RenderClear(pRenderer);

            switch(status) {
                case CEP_STATUS_INTRO:
                    Update_Intro();
                break;
                case CEP_STATUS_GAME:
                    Update_Game();
                break;
                case CEP_STATUS_DEATH:
                    update_death();
                break;
                case CEP_GAME_OVER:
                    Update_GameOver();
                break;
                case CEP_STATUS_NEXT:
                    Update_NextLevel();
                break;
            }
            renderer_present();
}

int main(int argc, char *argv[]) {
    // Intialize le générateur congruentiel par rapport à l'horloge 
    time_t t;
    t = time(NULL);
    srand(t);
    // Initialisation de la première scene du jeu
    // ------------------------------------------
    set_scene_selection();
    // ------------------------------------------

    SDL_Event event;
  
    Initialize_ks();
    if (Create()==1) {
        last_time = SDL_GetTicks();
        while (q==0) {
            
         
            update_status();
              //  Process_Game();
            while (SDL_PollEvent(&event) != 0) {
                switch (event.type) {
                    case SDL_QUIT:
                        q=1;
                    break;
                    case SDL_KEYUP:
                        if (event.key.keysym.sym==SDLK_ESCAPE) q=1;                    
                        if (event.key.keysym.sym==SDLK_RIGHT) {
                            a_ks[KS_RIGHT].status = KS_KEYUP;
                            a_ks[KS_RIGHT].last_up = SDL_GetTicks();
                        } else if (event.key.keysym.sym==SDLK_LEFT) {
                            a_ks[KS_LEFT].status = KS_KEYUP;
                            a_ks[KS_LEFT].last_up = SDL_GetTicks();
                        } else if (event.key.keysym.sym==SDLK_UP) {
                            a_ks[KS_UP].status = KS_KEYUP;
                            a_ks[KS_UP].last_up = SDL_GetTicks();
                        }
                        if (status == CEP_STATUS_INTRO) 
                            Process_Intro(&event);
                        

                    break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym==SDLK_RIGHT) {
                            a_ks[KS_RIGHT].status = KS_KEYDOWN;
                            a_ks[KS_RIGHT].last_down = SDL_GetTicks();
                        } else if (event.key.keysym.sym==SDLK_LEFT) {
                            a_ks[KS_LEFT].status = KS_KEYDOWN;
                            a_ks[KS_LEFT].last_down = SDL_GetTicks();
                        } else if (event.key.keysym.sym==SDLK_UP) {
                            a_ks[KS_UP].status = KS_KEYDOWN;
                            a_ks[KS_UP].last_down = SDL_GetTicks();
                        } else if (event.key.keysym.sym==SDLK_SPACE){
                             if (sel_fruct_idx != -1 ) {
                                status_fruct = direction;
                                fructs_y[sel_fruct_idx]+=8;
                             }

                        }
                        
                    break;
                    default:
                    break;
                }
            }
        }

    }

    Destroy();
    exit(0);
    return 0;
}


                          /*verbose
                            char str[255];
                            sprintf(str, "abs(x2-x3) = %d et abs(y2-y3)=%d \n", abs(x2-x3), abs(y2-y3));
                            SDL_Color color2 = {255,0,0};
                            Display_Text(str, CEP_TXT_CENTER, &color2,0 ,220,0);
                        */