
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
        printf("TTF_OpenFont: %s\n", TTF_GetError());
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
    Menu menu("../data/index");
    nbSongs=menu.getNbSongs();
     
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
 
    //Initialisation de la liste de songs du menu
    //Une surface pour chaque nom de chanson stocké dans un tab
    //On affichera le tab avec un certain decalage -> utile pour le movedown

    //int nbSongs=menu.getNbSongs();
    
    //cout << endl << nbSongs << endl; 
    //Decla des 3 composants de la liste
    SDL_Surface * SurfaceList;
    SDL_Texture * tabTextureList[nbSongs];
    SDL_Rect tabRectList[nbSongs];
    
    
    
    SDL_Color couleurNoire = {0, 0, 0};
    
    //Recuperation de la liste des songs
    vector<string> * ListSong;
    //ListSong.resize(nbSongs);
    ListSong=menu.getList();
   
   
  
   
    
    //Tampon car bug sur le vectorString -> prend des caractères
    string tamp;
  
    for(int i=0;i<nbSongs;i++){
        cout <<"NTM" <<endl;
        SurfaceList = TTF_RenderText_Blended(fontMenu,"tamp", couleurNoire);
        if(SurfaceList==NULL){
        	printf("Erreur lors de la creation de la surface : %s",SDL_GetError());
        	
        }
        tabTextureList[i]= SDL_CreateTextureFromSurface(renderer,SurfaceList);
         if(tabTextureList[i]==NULL){
        	printf("Erreur lors de la creation de la texture : %s",SDL_GetError());
        	
        }
        SurfaceList=NULL;
        tabRectList[i].x=25*i;
        tabRectList[i].y=100;
        tabRectList[i].w=300;
        tabRectList[i].h=20;
    }

    //Affiche la liste
    for(int j=0;j<nbSongs;j++){
        if(SDL_RenderCopy(renderer, tabTextureList[j], NULL, &tabRectList[j])!=0){
        	printf("Erreur lors de l'update du renderer : %s",SDL_GetError());
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
    while(!quitGame){
        /*mise en place de la partie*/
        
        //SDL_MIXER (lancement de la chanson)
        //timeBegin = SDL_GetTicks();
        
        //SDL_MIXER (lancement de la chanson)
        
        Mix_Music *music;
        string aMusic=menu.getGame()->getSong().fileMusic;
        const char *accesMusic = aMusic.c_str();
        music=Mix_LoadMUS(accesMusic);
        if (!music){
            cout<<"Mix_LoadMus "<<accesMusic<<"error"<<endl;
        }
        
        if (Mix_PlayMusic(music,1)==-1) {
            cout<<"Mix_PlayMusic error"<<endl;
        }
        
        
        
        
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
    while (!quit){
        
            /*afficheMenuSDL*/
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quit = true;
            }
            else if (events.type == SDL_KEYDOWN) {// Si une touche est enfoncee
                switch (events.key.keysym.scancode) { //On test en fonction de la touche enfoncée (id par scancode)
                    case SDL_SCANCODE_UP: //flèche du haut
                        menu.moveUp();
                        break;
                    case SDL_SCANCODE_DOWN://flèche du bas
                        menu.moveDown();
                        break;
                    case SDL_SCANCODE_RETURN://touche entré
                        menu.choose();
                        //sdlGameLoop();
                    case SDL_SCANCODE_ESCAPE://touche echap
                        quit=true;
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


