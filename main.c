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
#define CEP_JMP_RIGHT 2
#define CEP_JMP_LEFT 4


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
#define KS_KEYUP 0;



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


SDL_Rect spr_player_dest = {0,0,16,16};
int play_x = 16;
int play_y = 136;

unsigned int direction = CEP_DIR_RIGHT;
int costume =0;
/* Définition des fonctions */
int Trajectoire_Saut( int x) {
    int y;
    if (x<24)
        y=-5.33f /4;
    else    
        y=5.33f /4 ;
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
    SDL_SetWindowFullscreen(pWindow, SDL_WINDOW_FULLSCREEN);
                            
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
void Update_Game() {
    Uint32 cur_time = SDL_GetTicks() - last_time;
    if (cur_time<=30) {
        SDL_Delay(30 - cur_time);
    } else {
        last_time = SDL_GetTicks();
        if (sfc_loaded==0) {
            Init_Scene();
            sfc_loaded=1;
        }

        // Create Screen
        SDL_Rect rct_scene = {0,0,320,200};
        SDL_RenderCopy(pRenderer, pScene, &rct_scene, &rct_scene );



        // Process Enemy

        // Collision

        // Process Display
       // printf("%d\n", direction);
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
            }
            spr_player_dest.x = play_x;
            spr_player_dest.y = play_y;
            if (direction == CEP_DIR_RIGHT) 
                SDL_RenderCopy(pRenderer, pPlayer, &spr_player_right[costume], &spr_player_dest);
            else if (direction == CEP_DIR_LEFT)
                SDL_RenderCopy(pRenderer, pPlayer, &spr_player_left[costume], &spr_player_dest);
        } else {
            // Process JMP
            if ((direction & 32767) == CEP_DIR_LEFT) {
                if ((play_x-=2)<=0)
                    play_x = 0;
                x_saut -=2;
        //        printf("%d %d\n", x_saut, play_x);
                play_y = play_y - Trajectoire_Saut(x_saut);
                if (x_saut<=0) {
                    direction &=32767;
                }
            } else if ((direction & 32767) == CEP_DIR_RIGHT ) {
                if ((play_x+=2)>=304)
                    play_x= 304;
                x_saut +=2;
                play_y = play_y + Trajectoire_Saut(x_saut);
                if (x_saut >=44) {
                    direction &=32767;
                }
            }
            spr_player_dest.x = play_x;
            spr_player_dest.y = play_y;
            if ((direction & 32767)==CEP_DIR_RIGHT)
                SDL_RenderCopy(pRenderer, pPlayer, &spr_player_jmpr, &spr_player_dest);
            else if ((direction & 32767)==CEP_DIR_LEFT)
                SDL_RenderCopy(pRenderer, pPlayer, &spr_player_jmpl, &spr_player_dest);

        }
    }
    SDL_RenderPresent(pRenderer);
}

/*void Process_Game(SDL_Event *pEvent) {
    SDL_KeyboardEvent *pKey;
    
    
    switch (pEvent->type) {
        case SDL_KEYUP:
            if ((direction & 32768) ==0) 
                costume =0;
        break;
            case SDL_KEYDOWN:
                pKey = &(pEvent->key);
                if (pKey->keysym.sym==SDLK_RIGHT) {
                    if ((direction & 32768) ==0) {
                       if ( (play_x+=4)>=304 )
                            play_x = 304;
                        direction = CEP_DIR_RIGHT;
                        costume ++;
                        costume = costume % 3;
                    }
                } else if (pKey->keysym.sym == SDLK_LEFT) {
                    if ((direction & 32768) ==0)
                    {
                       if ( (play_x-=4)<=0)
                            play_x = 0;
                        direction = CEP_DIR_LEFT;
                        costume ++;
                        costume = costume % 3;
                    }
                } else if (pKey->keysym.sym == SDLK_SPACE) {
                    if ((direction & 32768) ==0) {
                        if (direction == CEP_DIR_LEFT)
                            x_saut = 48;
                        else x_saut=0;
                        direction |= 32768;
                    }
                    
                }
            break;

        }
  
}*/

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
            //if (status == CEP_STATUS_GAME)
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
   /*                     switch(status) {
                            case CEP_STATUS_INTRO:
                                Process_Intro(&event);
                            break;
                            case CEP_STATUS_GAME:
                                Process_Game(&event);
                            break;
                        }*/
                    break;
                }
               // update_status();
            }
        }

    }

    Destroy();
    exit(0);
}