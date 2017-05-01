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
    aMusic+=partMaker->getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();
    cout<<"lancement de :"<<accesMusic<<endl;

    music=Mix_LoadMUS(accesMusic);
    //music=Mix_LoadMUS("../data/wav/sth.wav");

    if (!music){
        cout<<"Mix_LoadMus "<<accesMusic<<Mix_GetError()<<endl;
    }
    
    backgroundImageLoad();
    
    tabSquareColor[0].loadFromFile("../data/theme/square/squareGreen.png",renderer);
    tabSquareColor[1].loadFromFile("../data/theme/square/squareRed.png",renderer);
    tabSquareColor[2].loadFromFile("../data/theme/square/squareYellow.png",renderer);
    tabSquareColor[3].loadFromFile("../data/theme/square/squareBlue.png",renderer);
    tabSquareColor[4].loadFromFile("../data/theme/square/squareOrange.png",renderer);
}

SdlPartitionMaker::~SdlPartitionMaker() {
    Mix_FreeMusic(music);
	delete partMaker;
}





void SdlPartitionMaker::backgroundImageLoad(){
    string aImage="../data/Backgroundsgame/";
    aImage+=partMaker->getSong().fileImage;
    const char *accesImage= aImage.c_str();
    cout <<"Ouverture du background :"<< aImage;
    
    Background.loadFromFile(accesImage,renderer);
}



void SdlPartitionMaker::sdlShowDiff() {
    SDL_Surface * surface;
    SDL_Texture * tex;
    SDL_Rect rec;
    SDL_Color WhiteC = {0,0,0};
    unsigned int difficulty = partMaker->getDifficulty();
    string message="DIFFICULTE : "+to_string(difficulty);
    
    surface=TTF_RenderText_Blended(font,message.c_str(),WhiteC);
    tex=SDL_CreateTextureFromSurface(renderer,surface);
    if(tex==NULL){
        cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
    }
    rec.x=width/10;
    rec.y=height/10;
    rec.w=width/10;
    rec.h=height/10;
    if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
        cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl;
    }

}




//A REPRENDRE -> affiche une image si il y a un un.
void SdlPartitionMaker::sdlShow(string line) {
    
	SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    Background.draw(renderer,0,0,width,height);
    int c;
    for(unsigned int i=0;i<5;i++){
        c=line[i]-48;
        if(c==true){
           SdlShowSquare(i);
        }
    }
}


void SdlPartitionMaker::SdlShowSquare(unsigned int i){
    switch(i){
        case 0:{
            tabSquareColor[i].draw(renderer,width/6+i*width/10,height/2,width/10,width/10);
            break;
        }
        case 1:{
            tabSquareColor[i].draw(renderer,width/6+i*width/10,height/2,width/10,width/10);
            break;
        }
        case 2:{
            tabSquareColor[i].draw(renderer,width/6+i*width/10,height/2,width/10,width/10);
            break;
        }
        case 3:{
            tabSquareColor[i].draw(renderer,width/6+i*width/10,height/2,width/10,width/10);
            break;
        }
        case 4:{
            tabSquareColor[i].draw(renderer,width/6+i*width/10,height/2,width/10,width/10);
            break;
        }
    }
}



void SdlPartitionMaker::sdlShowTime(int time){
    SDL_Surface * surface;
    SDL_Texture * tex;
    SDL_Rect rec;
    SDL_Color WhiteC = {0,0,0};
    string message="Time : "+to_string(time);
    
    surface=TTF_RenderText_Blended(font,message.c_str(),WhiteC);
    tex=SDL_CreateTextureFromSurface(renderer,surface);
    if(tex==NULL){
        cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
    }
    rec.x=width*8/10;
    rec.y=height/10;
    rec.w=width/10;
    rec.h=height/10;
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
        sdlShow(line);
        sdlShowTime(timeSeconds);
        sdlShowDiff();
        SDL_RenderPresent(renderer);
    }
    partMaker->save();
}

	
