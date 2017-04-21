
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

    
    fontMenu=TTF_OpenFont("../data/theme/police/default.ttf", 50);
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
    

    
    //Initialisation du menu
    menu= new Menu("../data/index");
     
    //Ouverture de la fenetre
    window = SDL_CreateWindow("StarStreak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_RESIZABLE); //SDL_WINDOW_FULLSCREEN_DESKTOP
 
    //parametres gestion de position/taille/resolution etc
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);//renderer synchro avec le rafraichissement de la fenetre
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.
    SDL_RenderSetLogicalSize(renderer, 640, 480); //taille fenetre
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //rend en noir
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888, //
                                SDL_TEXTUREACCESS_STREAMING,
                                //fluidité sur l'affichage des images
                                640, 480); //taille de l'ecran (on pourrait utiliser des parametres du main ?)
    
    
    im_background.loadFromFile("../data/Batman.jpg",renderer);
    
    
    
    
    
    
    
    
}


//Affichage du menu
void sdlGame::sdlShowMenu(){
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    


    im_background.draw(renderer,0,0,640,480);
 

    //Decla des 3 composants de la liste
    SDL_Surface * SurfaceList;
    SDL_Texture * tex;
    SDL_Rect rec;
    
    
    
    SDL_Color couleurNoire = {0, 0, 0};
    string tamp;
    
    cout<<menu->getNbSongs();

    for(unsigned int i=0;i<menu->getNbSongs();i++){
       
        tamp=menu->getTitleSong(i);
        cout <<tamp <<endl;
        SurfaceList = TTF_RenderText_Blended(fontMenu,tamp.c_str(), couleurNoire);
        if(SurfaceList==NULL){
        	cout<<"Erreur lors de la creation de la surface : "<<SDL_GetError()<<endl;
        	
        }
        tex= SDL_CreateTextureFromSurface(renderer,SurfaceList);
         if(tex==NULL){
        	cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
        	
        }
        SurfaceList=NULL;
        rec.x=150;
        rec.y=100+25*i;
        rec.w=10*tamp.size();
        rec.h=20;

        if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
            cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
        }
    }
    
    
}


//Affichage du jeu
void sdlGame::sdlShowGame(){
    
}



//Essai de loop+affichage
void sdlGame::sdlTest(){

        sdlShowMenu();
        SDL_RenderPresent(renderer);
        SDL_Delay(5000);
}


//Seconde Loop
// Correspond au jeu
void sdlGame::sdlGameLoop(){
    SDL_Event events;
    bool quitGame = false;
    
                /*mise en place de la partie*/
    
    /*SDL_MIXER (lancement de la chanson)*/
   
    
    Mix_Music *music;
    
    string aMusic="../data/mp3/";
    aMusic+=menu->getGame()->getSong().fileMusic;
    const char *accesMusic = aMusic.c_str();
    cout<<"lancement de :"<<accesMusic<<endl;
    
    music=Mix_LoadMUS(accesMusic);
    
    if (!music){
        cout<<"Mix_LoadMus "<<accesMusic<<"error"<<endl;
    }
    
    if (Mix_PlayMusic(music,1)==-1) {
        cout<<"Mix_PlayMusic error"<<endl;
    }
    
    
    while(!quitGame){
        
        
        
        
        
        //float timeBegin = SDL_GetTicks();
        
        
        

        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quitGame = true;
            }else if(1) {
            //boucle avec rafraichissement (=> actions automatiques)
                    //defiler cadre
                    //score
            }
        }
    }
}



//Premiere Loop
// Correspond au menu, la loop du jeu sera appelé dedans (aprés choose)
void sdlGame::sdlMenuLoop(){
    SDL_Event events;
    bool quit = false;
    
    
        /*SDL_Mixer*/
    Mix_AllocateChannels(5);
    
        /* bruitages de naviguation + musique de fond*/
    Mix_Chunk *soudMove;
    soudMove=Mix_LoadWAV("../data/theme/sounds/move.ogg");
    if(!soudMove){
        cout<<"erreur ouverture effet de séléction"<<Mix_GetError()<<endl;
    }
    Mix_Chunk *soudAccept;
    soudAccept=Mix_LoadWAV("../data/theme/sounds/action.ogg");
    if(!soudAccept){
        cout<<"erreur ouverture effet de validation"<<Mix_GetError()<<endl;
    }
        /*musique de fond dans le menu*/
    Mix_Chunk *soudMenu;
    soudMenu=Mix_LoadWAV("../data/theme/sounds/menu.ogg");
    if(!soudMenu){
        cout<<"erreur ouverture musique menu"<<Mix_GetError()<<endl;
    }
    
    
    while (!quit){
        
            /*afficheMenuSDL*/
        
        if (Mix_PlayChannel(1,soudMenu,2)==-1) {
                cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
            }
        
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quit = true;
            }
            
            else if (events.type == SDL_KEYDOWN) {// Si une touche est enfoncee
                switch (events.key.keysym.scancode) { //On test en fonction de la touche enfoncée (id par scancode)
                    case SDL_SCANCODE_UP: //flèche du haut
                        if (Mix_PlayChannel(2,soudMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->moveUp();
                        break;
                    case SDL_SCANCODE_DOWN://flèche du bas
                        if (Mix_PlayChannel(3,soudMove,1)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->moveDown();
                        break;
                    case SDL_SCANCODE_RETURN://touche entré
                        if (Mix_PlayChannel(4,soudAccept,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->choose();
                        sdlGameLoop();
                    case SDL_SCANCODE_ESCAPE://touche echap
                        quit=true;
                        Mix_HaltChannel(1);//arrete le musique du menu 
                        Mix_FreeChunk(soudAccept);
                        Mix_FreeChunk(soudMove);
                        Mix_FreeChunk(soudMenu);
                    default :
                        break;
                }
            }
        }
    }
}





sdlGame::~sdlGame(){
    
    
    
    //Fermeture TTF
    //TTF_CloseFont(fontMenu);  -> erreur d'allocation
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
}


