#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "stdio.h"

#define CEP_STATUS_INTRO 0
#define CEP_STATUS_GAME 1
#define CEP_GAME_OVER 2

#define CEP_TXT_CENTER 1
#define CEP_TXT_LEFT 2

#define CEP_WND_WIDTH 320
#define CEP_WND_HEIGHT 200

#define CEP_DIR_RIGHT 0
#define CEP_DIR_LEFT 1

#define CEP_JMP_DIR 0
#define CEP_JMP_UP 1
#define CEP_JMP_LONG 1

/* Initialization des composants */
SDL_Window* pWindow = NULL;
TTF_Font *pFont =NULL;
SDL_Renderer* pRenderer = NULL;

typedef struct key_tag {
    int status;
    Uint32 last_up;
    Uint32 last_down;
} KeyStatus;

KeyStatus a_ks[4];

#define KS_RIGHT  0
#define KS_LEFT  1
#define KS_UP 2
#define KS_SPACE 3

#define KS_KEYDOWN 1
#define KS_KEYUP 2



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
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,0,0,0,0,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    { 2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4}
};
  

int status = CEP_STATUS_GAME;
int difficulty =0;
int q=0;
int sfc_loaded=0;
int x_saut =0;

Uint32 last_time;
/* Initialization des éléments graphiques */

SDL_Surface* level_sfc = NULL;
SDL_Texture* pScene = NULL;

SDL_Texture* pPlayer = NULL;
SDL_Texture* pEnemy = NULL;

/* Définition des mosaiques */
SDL_Rect space = {32,0,8,8};
SDL_Rect sky = {24,0, 8,8};
SDL_Rect gnd3 = {16,0,8,8};
SDL_Rect gnd2 = {8,0,8,8};
SDL_Rect gnd1 = {0,0,8,8};

/* Définition des sprites */
SDL_Rect spr_player_right[3] = { {0,0, 12, 16}, {32, 0, 15, 16}, {48,0, 15,16} };
SDL_Rect spr_player_left[3] = { {2,16, 15, 16}, {17, 16, 15, 16}, {52,16, 12,16}};

SDL_Rect spr_player_jmpr = {16,0,15, 16};
SDL_Rect spr_player_jmpl = {32,16,15, 16};

// Paramètres
int score = 0;
int high_score =0;
int vie = 3;

// Enemy
SDL_Rect spr_enemy[3]= { {0,0,16,16 }, {16,0,16,16}, {32,0,16,16} };
SDL_Rect spr_enemy_dest = {0, 0, 16,16};
int enemy_x = 16;
int enemy_y = 84;
int enemy_sens_x=0;


SDL_Rect spr_player_dest = {0,0,16,16};
int play_x = 16;
int play_y = 136;

void deplace_enemy() {
    int pos_en_y = (enemy_y +16) / 8;
    int pos_en_x = enemy_x / 8;
   // printf("j=%d, i=%d, contenu=%d\n", pos_en_y, pos_en_x, ga_scene[pos_en_y][pos_en_x]);
    if (ga_scene[pos_en_y][pos_en_x]==0) {
     enemy_y++;
     enemy_sens_x=0;
    }
    else {
        if (enemy_sens_x ==0 ) {
         if ( ((random()*10) % 10)>=1) enemy_sens_x=1;
            else enemy_sens_x = -1;
        }
        if (enemy_sens_x ==-1) {
            if ( (enemy_x--)<=0)
             enemy_sens_x =1;
            } else if (enemy_sens_x ==1) {
                if ((enemy_x++)>=304) enemy_sens_x =-1;
            }
    }
    spr_enemy_dest.x = enemy_x;
    spr_enemy_dest.y = enemy_y;

    SDL_RenderCopy(pRenderer, pEnemy, &spr_enemy[enemy_x %3], &spr_enemy_dest);

}

unsigned int direction = CEP_DIR_RIGHT; // bit 15=1 => jmp , 
unsigned int jmp_direction = CEP_JMP_DIR;
unsigned int jmp_type = 0;
Uint32 lastup_down=0;

int x_saut_index = 0;

int costume =0;
/* Définition des fonctions */
int Trajectoire_Saut( int x_saut) {
    int y;
    float delta = 5.33f;
    printf("t_s:jmp_type=%d\n", jmp_type);
    if (jmp_type==CEP_JMP_LONG)
        delta = 2.5f *delta;
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

int Destroy() {
    SDL_DestroyTexture(pEnemy);
    SDL_DestroyTexture(pPlayer);
    SDL_DestroyTexture(pScene);
    SDL_FreeSurface(level_sfc);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
}
void Display_Text(const char* pszTitle, int attrb, SDL_Color *pColor, int x, int y) {
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
    SDL_RenderCopy(pRenderer, pTexture, NULL, &dstrect );
    SDL_DestroyTexture(pTexture);
}
void Update_Intro() {
        SDL_Color color = {255,0,0};
        SDL_SetRenderDrawColor(pRenderer, 0,0,0, 255);
        SDL_RenderClear(pRenderer);
        Display_Text("Menu du jeu", CEP_TXT_CENTER, &color, 0,0);
        Display_Text("1 Niveau facile", CEP_TXT_LEFT, &color, 0,32);
        Display_Text("2 Niveau moyen", CEP_TXT_LEFT, &color, 0,48);
        Display_Text("3 Niveau difficile", CEP_TXT_LEFT, &color, 0,64);

        SDL_RenderPresent(pRenderer);
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
            }

        break;
    }
}

void Init_Scene() {
    SDL_Surface* scene_sfc = SDL_CreateRGBSurface(0,320,200,32,0,0,0,0);
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
int jmp_right_criteria() {
    int ga_r = (play_y+16) / 8;
    int ga_c = (play_x+16) / 8 ;
    return (ga_scene[ga_r][ga_c] ==0);
}
int jmp_left_criteria() {
    int ga_r = (play_y+16) / 8;
    int ga_c = (play_x) / 8 ;
    return (ga_scene[ga_r][ga_c] ==0);

}
void Update_Game() {
 
    Uint32 cur_time = SDL_GetTicks() - last_time;
    if (cur_time<=30) {
        SDL_Delay(30 - cur_time);
    } else {
        // Affichage des paramètres:
     


        last_time = SDL_GetTicks();
        if (sfc_loaded==0) {
            Init_Scene();
            sfc_loaded=1;
        }

        // Create Screen
        SDL_Rect rct_scene = {0,0,320,200};
        SDL_RenderCopy(pRenderer, pScene, &rct_scene, &rct_scene );


        // Collision

        // Process Display
 
        if ((direction & 32768)==0) {
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
                else x_saut=0;
                direction |= 32768;
                if ((a_ks[KS_RIGHT].status == KS_KEYUP) && (a_ks[KS_LEFT].status == KS_KEYUP))
                    jmp_direction = CEP_JMP_UP;
                else {
                    jmp_direction = CEP_JMP_DIR;
                }
                if (lastup_down == 0)
                    lastup_down = SDL_GetTicks();
            } 

            spr_player_dest.x = play_x;
            spr_player_dest.y = play_y;
            if (direction == CEP_DIR_RIGHT) 
                SDL_RenderCopy(pRenderer, pPlayer, &spr_player_right[costume], &spr_player_dest);
            else if (direction == CEP_DIR_LEFT)
                SDL_RenderCopy(pRenderer, pPlayer, &spr_player_left[costume], &spr_player_dest);
        } else {
            // Process JMP
          //  int pos_pl_y = (play_y +16) / 8;
           // int pos_pl_x = play_x / 8;
  //          int pos_pl_x_r = (play_x + 16) / 8;
   //         int pos_pl_y_up =(play_y) /8;
            // 1. Detect long jmp
            if (a_ks[KS_UP].status == KS_KEYUP) {
                if (lastup_down>0) {
                   int diff = (SDL_GetTicks() - lastup_down);
                    if ( diff >= 100) {
                        if (direction >=32767)  jmp_type = CEP_JMP_LONG; else jmp_type =0;
                    }
                    printf("diff = %d\nstatus  =%d\n lastupd=%d\n jmptype=%d\n", diff, a_ks[KS_UP].status, lastup_down, jmp_type) ;

                    lastup_down = 0;
                }
            }
            if (jmp_direction == CEP_JMP_UP)
                x_saut_index = 0; else x_saut_index=2;
            if ((direction & 32767) == CEP_DIR_LEFT) {
                if ((play_x-=x_saut_index)<=0)
                    play_x = 0;
                x_saut -=2;
                play_y = play_y - Trajectoire_Saut(x_saut);
                if ((x_saut<24) && !jmp_left_criteria()) {
                    play_y -= play_y %8;
                    direction &=32767;
                    jmp_type=0;
                }
            } else if ((direction & 32767) == CEP_DIR_RIGHT ) {
                if ((play_x+=x_saut_index)>=304)
                    play_x= 304;
                x_saut +=2;
                play_y = play_y + Trajectoire_Saut(x_saut);
 
                // DEBUG
               if (jmp_type ==1)
                    printf("1)play y =%d, x_saut=%d\n", play_y, x_saut);

//                if (ga_scene[pos_pl_y][pos_pl_x_r]!=0)
                if ((x_saut>24) && !jmp_right_criteria()  ) {
                    play_y -= play_y %8;
                    direction &=32767;
                    jmp_type=0;
                }
                                                   // DEBUG:
                if (jmp_type ==1)
                    printf("2)play y =%d", play_y);

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
    Display_Text(s_params, CEP_TXT_LEFT , &color, 0,164);
    sprintf(s_params, "Vie(s)=%d", vie);
    Display_Text(s_params, CEP_TXT_LEFT , &color, 0,180);

    SDL_RenderPresent(pRenderer);
}

void update_status() {
            switch(status) {
                case CEP_STATUS_INTRO:
                    Update_Intro();
                break;
                case CEP_STATUS_GAME:
                    Update_Game();
                break;
            }

}
void main() {
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
}