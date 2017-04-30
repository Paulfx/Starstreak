#include "sdlGame.h"
#include "sdlClass.h"



SdlGame::SdlGame() {

}

SdlGame::SdlGame(SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty,bool mode) : window(window), renderer(renderer){
    assert(renderer);

    game = new Game(song,difficulty,mode);
    
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
}

SdlGame::~SdlGame() {
    //Libération images
    //et de la musique en cours
    delete game;
    Mix_HaltMusic();
}


//Affichage du jeu
void SdlGame::sdlShow(){
    
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    
    Cadre& cadre = game->getCadre();

   // im_ligneValidation.draw(renderer,0,cadre.getBeginValid());

    drawValidation();
    int taille = width/20;

    for(unsigned int i=0;i<cadre.getNbNote();++i) {
        Note& note = cadre.getNote(i);
        int color = note.getColor();
        switch(color) {
            case 0 : im_note0.draw(renderer,cadre.getTabPos(0)+color*taille,note.getPosY(),taille);break; //TODO ENLEVER TABPOS DE CADRE !
            case 1 : im_note1.draw(renderer,cadre.getTabPos(0)+color*taille,note.getPosY(),taille);break;
            case 2 : im_note2.draw(renderer,cadre.getTabPos(0)+color*taille,note.getPosY(),taille);break;
            case 3 : im_note3.draw(renderer,cadre.getTabPos(0)+color*taille,note.getPosY(),taille);break;
            case 4 : im_note4.draw(renderer,cadre.getTabPos(0)+color*taille,note.getPosY(),taille);break;
            default:break;
        }
    }

}

void SdlGame::drawValidation(){
    Cadre& cadre = game->getCadre();
    int taille = width/20;  

    for(unsigned int i=0;i<5;++i) {
        if(!tabPush[i]) {
            tabImV[i].draw(renderer,cadre.getTabPos(0)+i*taille,cadre.getBeginValid(),taille,taille);
        }
        else {
            tabImVPush[i].draw(renderer,cadre.getTabPos(0)+i*taille,cadre.getBeginValid(),taille,taille);
        }
    }
}


//Seconde Loop
// Correspond au jeu
void SdlGame::sdlLoop(){
    SDL_Event events;
    bool quitGame = false;
    

    /*SDL_MIXER (lancement de la chanson)*/
    string aMusic="../data/mp3/";
    aMusic+=game->getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();
    cout<<"lancement de :"<<accesMusic<<endl;
    music=Mix_LoadMUS(accesMusic);
    if (!music){
        cout<<"Mix_LoadMus "<<accesMusic<<"error"<<endl;
    }
    if (Mix_PlayMusic(music,1)==-1) {
        cout<<"Mix_PlayMusic error"<<endl;
    }

    Keyboard& keyboard = game->getKeyboard();

    float time_seconds = SDL_GetTicks() / 1000.f;
    while(!quitGame){
        //keyboard.setLongPressAllSimplePress(); //Tous les simplePress deviennent longPress
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quitGame = true;
            }
            else if (events.type == SDL_KEYDOWN){ //Appui
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_A:
                        quitGame=true;
                        Mix_HaltMusic();
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

        float new_time = SDL_GetTicks() / 1000.f;
        float delta = new_time - time_seconds;
        time_seconds = new_time;

        sdlShow();
        game->update(delta);
        SDL_RenderPresent(renderer);
    }

}
