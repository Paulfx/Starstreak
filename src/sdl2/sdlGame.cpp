#include "sdlGame.h"
#include "sdlClass.h"




SdlGame::SdlGame() {

}

SdlGame::SdlGame(SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty) : window(window), renderer(renderer){
    assert(renderer);

    game = new Game(song,difficulty);
    
    SDL_GetWindowSize(window, &width, &height);

    im_note0.loadFromFile("../data/theme/notes/vert.png",renderer);
    im_note1.loadFromFile("../data/theme/notes/rouge.png",renderer);
    im_note2.loadFromFile("../data/theme/notes/jaune.png",renderer);
    im_note3.loadFromFile("../data/theme/notes/bleu.png",renderer);
    im_note4.loadFromFile("../data/theme/notes/orange.png",renderer);

    im_ligneValidation.loadFromFile("../data/theme/notes/ligneValidation.png",renderer);
    
    
    
    im_noteV0.loadFromFile("../data/theme/notes/validGreen.png",renderer);
    tabImV[0]=im_noteV0;
    im_noteV1.loadFromFile("../data/theme/notes/validRed.png",renderer);
    tabImV[1]=im_noteV1;
    im_noteV2.loadFromFile("../data/theme/notes/validYel.png",renderer);
    tabImV[2]=im_noteV2;
    im_noteV3.loadFromFile("../data/theme/notes/validBl.png",renderer);
    tabImV[3]=im_noteV3;
    im_noteV4.loadFromFile("../data/theme/notes/validOr.png",renderer);
    tabImV[4]=im_noteV4;
    backgroundImageLoad();
    
    im_noteVPush0.loadFromFile("../data/theme/notes/validGreenON.png",renderer);
    tabImVPush[0]=im_noteVPush0;
    im_noteVPush1.loadFromFile("../data/theme/notes/validRedON.png",renderer);
    tabImVPush[1]=im_noteVPush1;
    im_noteVPush2.loadFromFile("../data/theme/notes/validYelON.png",renderer);
    tabImVPush[2]=im_noteVPush2;
    im_noteVPush3.loadFromFile("../data/theme/notes/validBlON.png",renderer);
    tabImVPush[3]=im_noteVPush3;
    im_noteVPush4.loadFromFile("../data/theme/notes/validOrON.png",renderer);
    tabImVPush[4]=im_noteVPush4;

    tabPush[0]=false;
    tabPush[1]=false;
    tabPush[2]=false;
    tabPush[3]=false;
    tabPush[4]=false;
    

    string aMusic="../data/wav/";
    aMusic+=game->getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();
    cout<<"lancement de :"<<accesMusic<<endl;
    music=Mix_LoadMUS(accesMusic);
    if (!music){
        cout<<"Mix_LoadMus "<<accesMusic<<"error"<<endl;
    }
    
    //TTF
    //Besoin de re- initialisé?
    fontMenu=TTF_OpenFont("../data/theme/police/fast99.ttf", 0.0625*width);
    if(fontMenu==NULL) {
        cout<<"TTF_OpenFont: "<<endl<<TTF_GetError()<<endl;
    }
  
}


void SdlGame::backgroundImageLoad(){
    
    
    string aImage="../data/Backgroundsgame/";
    aImage+=game->getSong().fileImage;
    const char *accesImage= aImage.c_str();
    cout <<"Ouverture du background :"<< aImage;
    
    Background.loadFromFile(accesImage,renderer);
}


SdlGame::~SdlGame() {
    //Libération images
    //et de la musique en cours
    delete game;
    Mix_FreeMusic(music);
}


SDL_Texture* SdlGame::surfaceToTexture( SDL_Surface* surf ) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}


void SdlGame::sdlScore(){
    SDL_Color white = {255, 255, 255};
    SDL_Color black = {0,0,0};
    SDL_Surface* surf;
    int score=game->getScore().getTotalScore();
    string sc=to_string(score);
    surf=TTF_RenderText_Blended(fontMenu,sc.c_str(),black);
    texScore=surfaceToTexture(surf);
    SDL_Rect rec;
    rec.x=100;
    rec.y=200;
    rec.w=200;
    rec.h=100;
    if(SDL_RenderCopy(renderer,texScore, NULL, &rec)!=0){
        cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
    }
}


//Affichage du jeu
void SdlGame::sdlShow(){
    
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    
    Cadre& cadre = game->getCadre();

   // im_ligneValidation.draw(renderer,0,cadre.getBeginValid());

    drawValidation();
    int widthNote = width/10;
    int heightNote = height/6;

    for(unsigned int i=0;i<cadre.getNbNote();++i) {
        Note& note = cadre.getNote(i);
        int color = note.getColor();
        int Distx=width/4;
        switch(color) {
            case 0 : im_note0.draw(renderer,Distx+color*widthNote,note.getPosY());break; //TODO ENLEVER TABPOS DE CADRE !
            case 1 : im_note1.draw(renderer,Distx+color*widthNote,note.getPosY());break;
            case 2 : im_note2.draw(renderer,Distx+color*widthNote,note.getPosY());break;
            case 3 : im_note3.draw(renderer,Distx+color*widthNote,note.getPosY());break;
            case 4 : im_note4.draw(renderer,Distx+color*widthNote,note.getPosY());break;
            default:break;
        }
    }

}

void SdlGame::drawValidation(){
    Cadre& cadre = game->getCadre();
    int widthV = width/10;
    int Distx=width/4; // 1/4 + 1/2 + 1/4
    int Disty=height*5/6;
    int heightV =height/6;

    int taille=width/20;
    for(unsigned int i=0;i<5;++i) {
        if(!tabPush[i]) {
            tabImV[i].draw(renderer,Distx+i*widthV,cadre.getBeginValid(),widthV);
        }
        else {
            tabImVPush[i].draw(renderer,Distx+i*widthV,cadre.getBeginValid(),widthV);
        }
    }
}


//Seconde Loop
// Correspond au jeu
void SdlGame::sdlLoop(){
    SDL_Event events;
    bool quitGame = false;
    
    if (Mix_PlayMusic(music,1)==-1) {
        cout<<"Mix_PlayMusic error"<<endl;
    }

    

    Keyboard& keyboard = game->getKeyboard();

    float time_seconds = SDL_GetTicks() / 1000.f;
    while(!quitGame){
        float new_time = SDL_GetTicks() / 1000.f;
        float delta = new_time - time_seconds;
        time_seconds = new_time;
        game->update(delta);

        //keyboard.setLongPressAllSimplePress(); //Tous les simplePress deviennent longPress
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quitGame = true;
            }
            else if (events.type == SDL_KEYDOWN){ //Appui
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_A:
                        quitGame=true;
                        //Mix_HaltMusic();
                        break;
                    case SDL_SCANCODE_Q:keyboard.setPress(0);tabPush[0]=true;break;
                    case SDL_SCANCODE_W:keyboard.setPress(1);tabPush[1]=true;break;
                    case SDL_SCANCODE_E:keyboard.setPress(2);tabPush[2]=true;break;
                    case SDL_SCANCODE_R:keyboard.setPress(3);tabPush[3]=true;break;
                    case SDL_SCANCODE_T:keyboard.setPress(4);tabPush[4]=true;break;

                    default:break;
                }
            }
            else if (events.type == SDL_KEYUP){ //Relachement
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_Q:keyboard.setNoPress(0);tabPush[0]=false;break;
                    case SDL_SCANCODE_W:keyboard.setNoPress(1);tabPush[1]=false;break;
                    case SDL_SCANCODE_E:keyboard.setNoPress(2);tabPush[2]=false;break;
                    case SDL_SCANCODE_R:keyboard.setNoPress(3);tabPush[3]=false;break;
                    case SDL_SCANCODE_T:keyboard.setNoPress(4);tabPush[4]=false;break;
                    default:break;
                }
            }
        }
        //keyboard.afficher();
        sdlShow();
        sdlScore();
        SDL_RenderPresent(renderer);
    }

}
