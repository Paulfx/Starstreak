#include "sdlPartitionMaker.h"


SdlPartitionMaker::SdlPartitionMaker(SDL_Window * window, SDL_Renderer * renderer, const Song& song, unsigned int difficulty) : window(window), renderer(renderer) {
	assert(renderer);

    partMaker=new PartitionMaker(song,difficulty);

    cout<<"Partition Maker créé"<<endl;
    
    SDL_GetWindowSize(window, &width, &height);

    font=TTF_OpenFont("../data/theme/police/fast99.ttf", 0.0625*width); //TAILLE GENERE DYNAMIQUEMENT EN FONCTION DE LA TAILLE DE L'ECRAN
    if(font==NULL) {
        cout<<"TTF_OpenFont: "<<endl<<TTF_GetError()<<endl;
    }
    
    string aMusic="../data/wav/";
    //aMusic+=game->getSong().fileMusic;
    //aMusic+=song.fileMusic;
    aMusic+=partMaker->getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();
    cout<<"lancement de :"<<accesMusic<<endl;
    music=Mix_LoadMUS(accesMusic);
    if (!music){
        cout<<"Mix_LoadMus "<<accesMusic<<"error"<<endl;
    }
}

SdlPartitionMaker::~SdlPartitionMaker() {
    Mix_FreeMusic(music);
	delete partMaker;
}



void SdlPartitionMaker::sdlShow() {
	SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

	unsigned int difficulty = partMaker->getDifficulty();
	string message="DIFFICULTE : "+difficulty;

	SDL_Surface * surface;
    SDL_Texture * tex;
    SDL_Rect rec;
	SDL_Color WhiteC = {0,0,0};


    surface=TTF_RenderText_Blended(font,message.c_str(),WhiteC);
    tex=SDL_CreateTextureFromSurface(renderer,surface);
    if(tex==NULL){
        cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
    }
    rec.x=width/2;
    rec.y=height/2;
    rec.w=surface->w;
    rec.h=surface->h;
    if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
        cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl;
    }

}


void SdlPartitionMaker::sdlLoop() {
	SDL_Event events;
    bool quit = false;
    
    if (Mix_PlayMusic(music,1)==-1) {
        cout<<"Mix_PlayMusic error"<<endl;
    }
    
    float duration = partMaker->getSong().duration;
    Keyboard& keyboard = partMaker->getKeyboard();

    
    int time;
    float timeSeconds=0;
    int timeBefore=SDL_GetTicks();
    
	while(timeSeconds<=duration && !quit) {
		time=SDL_GetTicks()-timeBefore;
		timeSeconds=time/1000.f;
		cout<<timeSeconds<<"   "<<duration<<endl;
        //keyboard.setLongPressAllSimplePress(); //Tous les simplePress deviennent longPress
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quit = true;
            }
            else if (events.type == SDL_KEYDOWN){ //Appui
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_A:
                        quit=true;
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
        string line=keyboard.getCurrentStateStr();
        for(unsigned int i=0;i<5;i++) {keyboard.setNoPress(i);}
        cout<<"LINE : "<<line<<endl;
        time = SDL_GetTicks() - timeBefore;
        timeSeconds=time/1000.f;
        
        partMaker->update(time,line);

        sdlShow();
        SDL_RenderPresent(renderer);
    }
    partMaker->save();
}

	