
#include "sdlGame.h"


const int TAILLE_SPRITE=32;


// ============= IMAGE =============== //

Image::Image () {
    surface = NULL;
    texture = NULL;
    has_changed = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    surface = IMG_Load(filename);
    if (surface == NULL) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        surface = IMG_Load(nfn.c_str());
        if (surface == NULL) {
            nfn = string("../") + nfn;
            surface = IMG_Load(nfn.c_str());
        }
    }
    if (surface == NULL) {
        cout<<"Error: cannot load "<< filename <<endl;
        exit(1);
    }
    
    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if (texture == NULL) {
        
        cout << "Error: problem to create the texture of "<< filename<< endl;
        cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?surface->w:w;
    r.h = (h<0)?surface->h:h;
    
    if (has_changed) {
        ok = SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch);
        assert(ok == 0);
        has_changed = false;
    }
    
    ok = SDL_RenderCopy(renderer,texture,NULL,&r);
    //assert(ok == 0);
}


// ============= GAME =============== //




sdlGame::sdlGame(){
    // INITIALISATION
    
    
    

 
    
    
    //SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    
    
    //TTF
    if (TTF_Init() == -1) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    //chemin + taille de police
    //Police du menu
    fontMenu= NULL;
    fontMenu=TTF_OpenFont("../data/theme/police/fast99.ttf", 50);
    if(fontMenu==NULL) {
        cout<<"TTF_OpenFont: "<<endl<<TTF_GetError()<<endl;
        // handle error
    }
    
    //IMAGE
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }
    
    //MIXER
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,1024)==-1){
        cout<<Mix_GetError()<<endl;
    }
    
    //Recuperation taille desktop pour le fullscreen

    



    //Initialisation du menu
    menu= new Menu("../data/index");
     
    //Ouverture de la fenetre
    window = SDL_CreateWindow("StarStreak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,0,0,SDL_WINDOW_FULLSCREEN_DESKTOP);
    
    
    SDL_GetWindowSize(window, &width, &height);
    //parametres gestion de position/taille/resolution etc
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);//renderer synchro avec le rafraichissement de la fenetre
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.
    SDL_RenderSetLogicalSize(renderer,width, height); //taille fenetre
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //rend en noir
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888, //
                                SDL_TEXTUREACCESS_STREAMING,
                                //fluidité sur l'affichage des images
                                0,0); //taille de l'ecran (on pourrait utiliser des parametres du main ?)
    cout << width << "######"<< endl << height ;
    if(renderer){
        im_backgroundMenu.loadFromFile("../data/theme/BackgroundMenu.jpg",renderer);

        im_ptrMenu.loadFromFile("../data/theme/Select.png",renderer);
        
        
        
        im_note0.loadFromFile("../data/theme/notes/vert.png",renderer);
        im_note1.loadFromFile("../data/theme/notes/rouge.png",renderer);
        im_note2.loadFromFile("../data/theme/notes/jaune.png",renderer);
        im_note3.loadFromFile("../data/theme/notes/bleu.png",renderer);
        im_note4.loadFromFile("../data/theme/notes/orange.png",renderer);
        
        im_ligneValidation.loadFromFile("../data/theme/notes/ligneValidation.png",renderer);

    }else {
        cout << "Erreur dans l'initialisation du renderer" << endl;
    }
}


//Affichage du menu
void sdlGame::sdlShowMenu(){
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    
    int posPtr=menu->getCurrI()%10;
    
    im_backgroundMenu.draw(renderer,0,0,width,height);
    
    im_ptrMenu.draw(renderer,400,30+posPtr*50,120,40);

    //Decla des 3 composants de la liste
    SDL_Surface * SurfaceList;
    SDL_Texture * tex;
    SDL_Rect rec;
    
    
    
    SDL_Color couleurNoire = {0, 0, 0};
    SDL_Color couleurBlanche = {255, 255, 255};
    string tempTitle;
    
    cout<<menu->getNbSongs();
    

    for(unsigned int i=0;i<menu->getNbSongs();i++){
       
        tempTitle=menu->getTitleSong(i);
        cout <<tempTitle <<endl;
        SurfaceList = TTF_RenderText_Blended(fontMenu,tempTitle.c_str(), couleurBlanche);
        if(SurfaceList==NULL){
        	cout<<"Erreur lors de la creation de la surface : "<<SDL_GetError()<<endl;
        	
        }
        tex= SDL_CreateTextureFromSurface(renderer,SurfaceList);
         if(tex==NULL){
        	cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
        	
        }
        SurfaceList=NULL;
        rec.x=30;
        rec.y=25+i*50;//(1/3)*(height)+50*i+5;
        rec.w=20*tempTitle.size();
        rec.h=50;
        if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
            cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
        }
    }
    
    
    
    
        SDL_RenderPresent(renderer);//ligne a rajouter dans showMenu ? (fin)
}


//Essai de loop+affichage
void sdlGame::sdlTest(){

    sdlMenuLoop();
    
    
       /* sdlShowMenu();
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
        */
}


//Affichage du jeu
void sdlGame::sdlShowGame(){
    
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);

    Cadre& cadre = menu->getGame().getCadre();

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
void sdlGame::sdlGameLoop(){
    SDL_Event events;
    bool quitGame = false;
    
    Game& game = menu->getGame();
    
    /*SDL_MIXER (lancement de la chanson)*/
    Mix_Music *music;
    string aMusic="../data/mp3/";
    aMusic+=game.getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();//Mix_load n'accepte de cont char donc convertion
    cout<<"lancement de :"<<accesMusic<<endl;
    music=Mix_LoadMUS(accesMusic);
    if (!music){
        cout<<"Mix_LoadMus "<<accesMusic<<"error"<<endl;
    }
    if (Mix_PlayMusic(music,1)==-1) {
        cout<<"Mix_PlayMusic error"<<endl;
    }

    float time_seconds = SDL_GetTicks() / 1000.f;
    while(!quitGame){
        float new_time = SDL_GetTicks() / 1000.f;
        float delta = new_time - time_seconds;
        time_seconds = new_time;

        game.update(delta);

        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quitGame = true;
            }
            
            else if (events.type == SDL_KEYDOWN){
                switch(events.key.keysym.scancode) {
                    case SDL_SCANCODE_Q:
                        quitGame=true;
                        break;
                    default:break;
                }
            }
        }
        sdlShowGame();
        SDL_RenderPresent(renderer);
    }

}



//Premiere Loop
// Correspond au menu, la loop du jeu sera appelé dedans (aprés choose)
void sdlGame::sdlMenuLoop(){
    SDL_Event events;
    bool quit = false;
    
                        /*SDL_Mixer init*/
    Mix_AllocateChannels(5);
    
    

    /* bruitages de naviguation + musique de fond*/
    Mix_Chunk *soundMove;
    soundMove=Mix_LoadWAV("../data/theme/sounds/move.ogg");
    if(!soundMove){
        cout<<"erreur ouverture effet de séléction:"<<Mix_GetError()<<endl;
    }
    Mix_Chunk *soundAccept;
    soundAccept=Mix_LoadWAV("../data/theme/sounds/action.ogg");
    if(!soundAccept){
        cout<<"erreur ouverture effet de validation:"<<Mix_GetError()<<endl;
    }
    /*musique de fond dans le menu*/
    Mix_Chunk *soundMenu;
    soundMenu=Mix_LoadWAV("../data/theme/sounds/menu.ogg");
    if(!soundMenu){
        cout<<"erreur ouverture musique menu:"<<Mix_GetError()<<endl;
    }
    if (Mix_PlayChannel(1,soundMenu,2)==-1) {
        cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
    }
    Mix_Pause(1);
    
                        /*Debut de la boucle Menu*/
    
    while (!quit){
        
        
        
        sdlShowMenu();
        
        
        
        
        
        Mix_Resume(1);
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quit = true;
            }
            
            else if (events.type == SDL_KEYDOWN) {// Si une touche est enfoncee
                switch (events.key.keysym.scancode) { //On test en fonction de la touche enfoncée (id par scancode)
                    case SDL_SCANCODE_UP: //flèche du haut
                        if (Mix_PlayChannel(2,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->moveUp();
                        break;
                    case SDL_SCANCODE_DOWN://flèche du bas
                        if (Mix_PlayChannel(3,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->moveDown();
                        break;
                    case SDL_SCANCODE_RETURN://touche entré
                        if (Mix_PlayChannel(4,soundAccept,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->choose();
                        sdlGameLoop();
                    case SDL_SCANCODE_ESCAPE://touche echap
                        quit=true;
                        Mix_HaltChannel(1);//arrete le musique du menu 
                        Mix_FreeChunk(soundAccept);
                        Mix_FreeChunk(soundMove);
                        Mix_FreeChunk(soundMenu);
                    default :
                        break;
                }
            }
        }
    }

  //  SDL_menu_quit();

}





sdlGame::~sdlGame(){
    
    
    
    //Fermeture TTF
    //TTF_CloseFont(fontMenu);  -> erreur d'allocation
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
}


