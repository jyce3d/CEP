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
#define CEP_WND_HEIGHT 200

#define CEP_DIR_RIGHT 0
#define CEP_DIR_LEFT 1

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

#define CEP_MAX_EXERC 8



/*Initialisation des variables */

char ga_scene[20][40]= {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,0,2,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,0,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4}
};
  
char ga_exerc_1[8][255] = { {"45 : 9 = ?"}, {"27+32 = 5?"}, {"653-77=5?6"}, {"245+89=33?"}, {"570+158 = 7?8"}, {"547 + 238 = 7?5"}, {"857 - 424=43?"}, {"942 - 321 = 62?"} };
char ga_exerc_sol_1[8] = {5, 9, 7, 4, 2, 8, 3, 1};


char ga_exerc_2[8][255] = { {"4 X (3+9)  = 4?"}, {"(27+30)/3= ?9"}, {"7+3 X (2+8) =3?"},  {"(3 X 2-6+10) X 5=5? "}, 
{"(6+9)X(8-5)X2 = ?0"}, {"(4 X 3+8-10)X7=?0"}, {"(5+6-3)X2+7)=?3"}, {"4+10X(9-8+2)=?4"} };
char ga_exerc_sol_2[8] = {8, 1, 7, 0,9,
7,2,3};

char ga_exerc_3[8][255] = { {"6+8.(x+7) = -98 => x=-?0"}, {"3x + 15 = -2x => x=?"}, {"7 + 5x = 7x - 13 => x=1?"}, 
{"x-8 = 10 => x=?8"},{"3x = 6 => x=?"},{"x+3=-8 => x=-1?"},{"3x-6(3-4x)=9x-2 => x=1?/30"},{"3(2-3x)-(4+5x)=0 => x=1/?"} };
char ga_exerc_sol_3[8] = {2, 5, 0, 
1, 2, 1, 6, 7};

char ga_exerc[255];
char ga_exerc_sol;

int sel_exerc =0;
int status = CEP_STATUS_INTRO;
int difficulty =0;
int q=0;
int sfc_loaded=0;
int x_saut =0;
int max_enemy = 3;

Uint32 last_time;
/* Initialization des éléments graphiques */

SDL_Surface* level_sfc = NULL;
SDL_Texture* pScene = NULL;

SDL_Texture* pPlayer = NULL;
SDL_Texture* pEnemy = NULL;

SDL_Texture* pCoins = NULL;

/* Définition des mosaiques */
SDL_Rect space = {32,0,8,8};
SDL_Rect sky = {24,0, 8,8};
SDL_Rect gnd3 = {16,0,8,8};
SDL_Rect gnd2 = {8,0,8,8};
SDL_Rect gnd1 = {0,0,8,8};

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

SDL_Rect spr_player_dest = {0,0,16,16};
int play_x = 16;
int play_y = 136;
unsigned int direction = CEP_DIR_RIGHT; // bit 15=1 => jmp , 
unsigned int jmp_direction = CEP_JMP_DIR;

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

        if ((ga_scene[pos_en_y][(enemy_x[i]+16)/8]==0) && (ga_scene[pos_en_y][(enemy_x[i])/8]==0)  ) {
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
                                CEP_WND_WIDTH, CEP_WND_HEIGHT,SDL_WINDOW_SHOWN );
   // SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
                            
    if (pWindow) {
            if (!TTF_Init()) {
                if ( !(pFont = TTF_OpenFont("freefont/FreeMono.ttf", 16)) ) {
                    printf("Erreur lors du chargement de la font %s \n", SDL_GetError());
                    return -1;
                } else {
                    if ((pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED) )==NULL) {
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

        SDL_RenderPresent(pRenderer);
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
        initialize_level();
        choose_level();
        score = score +1000;

        status = CEP_STATUS_GAME;
  
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
    dest_rect.w=8;
    dest_rect.h=8;
    for (int i=0; i<40;i++) { // parcours des colonnes de la matrice
        for (int j=0;j<20;j++) {
            dest_rect.x=i*8;
            dest_rect.y=j*8;
            switch (ga_scene[j][i]) {
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
            }
        }
    }
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
    return (ga_scene[ga_r][ga_c] ==0);
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

    for (int i=0; i<max_enemy;i++ ) {
 
        x2 = enemy_x[i]+8 ;
        y2 = enemy_y[i] + 8;
        if (  abs(x1-x2) <=8 && abs(y1-y2) <=8 )
            return 1;
        if (  abs(x1-x2) <=8 && abs(y1-y2) <= 16  ) 
        status_score = 1;
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
    return 0;
}
void Update_Game() {
 
    Uint32 cur_time = SDL_GetTicks() - last_time;
    if (cur_time<=40) {
        SDL_Delay(40 - cur_time);
    } else {
   
        // Affichage des paramètres:


        last_time = SDL_GetTicks();
        if (sfc_loaded==0) {
            Init_Scene();
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
    vie --;
    if (vie>0) {
        initialize_level();

        status = CEP_STATUS_GAME;
    } else 
        status = CEP_GAME_OVER;

}
void update_status() {
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
}


int main(int argc, char *argv[]) {
    // Intialize le générateur congruentiel par rapport à l'horloge 
    time_t t;
    t = time(NULL);
    srand(t);

    SDL_Event event;
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
