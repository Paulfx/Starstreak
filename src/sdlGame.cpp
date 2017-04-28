#include "sdlGame.h"
#include "sdlClass.h"



SdlGame::SdlGame() {

}

SdlGame::SdlGame(SDL_Texture * texture, SDL_Window * window, SDL_Renderer * renderer, const Song& song,unsigned int difficulty,bool mode) : texture(texture), window(window), renderer(renderer){
    assert(renderer);

    game = new Game(song,difficulty,mode);


    im_note0.loadFromFile("../data/theme/notes/vert.png",renderer);
    im_note1.loadFromFile("../data/theme/notes/rouge.png",renderer);
    im_note2.loadFromFile("../data/theme/notes/jaune.png",renderer);
    im_note3.loadFromFile("../data/theme/notes/bleu.png",renderer);
    im_note4.loadFromFile("../data/theme/notes/orange.png",renderer);
    
    im_ligneValidation.loadFromFile("../data/theme/notes/ligneValidation.png",renderer);
}

SdlGame::~SdlGame() {
    //Libération images
    delete game;
}


//Affichage du jeu
void SdlGame::sdlShow(){
    
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    Cadre& cadre = game->getCadre();

    im_ligneValidation.draw(renderer,0,cadre.getBeginValid());

    for(unsigned int i=0;i<cadre.getNbNote();++i) {
        Note& note = cadre.getNote(i);
        int color = note.getColor();
        switch(color) {
            case 0 : im_note0.draw(renderer,note.getPosX(),note.getPosY());break;
            case 1 : im_note1.draw(renderer,note.getPosX(),note.getPosY());break;
            case 2 : im_note2.draw(renderer,note.getPosX(),note.getPosY());break;
            case 3 : im_note3.draw(renderer,note.getPosX(),note.getPosY());break;
            case 4 : im_note4.draw(renderer,note.getPosX(),note.getPosY());break;
            default:break;
        }
    }

}


//Seconde Loop
// Correspond au jeu
void SdlGame::sdlLoop(){
    SDL_Event events;
    bool quitGame = false;
    

    /*SDL_MIXER (lancement de la chanson)*/
    Mix_Music *music;
    string aMusic="../data/mp3/";
    aMusic+=game->getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();//Mix_load n'accepte de cont char donc convertion
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
        keyboard.setLongPressAllSimplePress(); //Tous les simplePress deviennent longPress
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quitGame = true;
            }
            else if (events.type == SDL_KEYDOWN){ //Appui
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_A:
                        quitGame=true;
                        break;
                    case SDL_SCANCODE_Q:keyboard.setPress(0);break;
                    case SDL_SCANCODE_W:keyboard.setPress(1);break;
                    case SDL_SCANCODE_E:keyboard.setPress(2);break;
                    case SDL_SCANCODE_R:keyboard.setPress(3);break;
                    case SDL_SCANCODE_T:keyboard.setPress(4);break;

                    default:break;
                }
            }
            else if (events.type == SDL_KEYUP){ //Relachement
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_Q:keyboard.setNoPress(0);break;
                    case SDL_SCANCODE_W:keyboard.setNoPress(1);break;
                    case SDL_SCANCODE_E:keyboard.setNoPress(2);break;
                    case SDL_SCANCODE_R:keyboard.setNoPress(3);break;
                    case SDL_SCANCODE_T:keyboard.setNoPress(4);break;
                    default:break;
                }
            }
        }
        keyboard.afficher();

        float new_time = SDL_GetTicks() / 1000.f;
        float delta = new_time - time_seconds;
        time_seconds = new_time;

        game->update(delta);

        
        sdlShow();
        SDL_RenderPresent(renderer);
    }

}