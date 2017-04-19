
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
    assert(ok == 0);
}


// ============= GAME =============== //




sdlGame::sdlGame(){
    // INITIALISATION
    //SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    
    
    //TTF
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    //chemin + taille de police
    //Police du menu
    fontMenu=TTF_OpenFont("../data/theme/police/fast99.ttf", 65);
    
    
    //IMAGE
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }
    
    
    
    //Initialisation du menu
    Menu menu("../data/index");
    
    
    //Initialisation de la liste de songs du menu
    //Une surface pour chaque nom de chanson stocké dans un tab
    //On affichera le tab avec un certain decalage -> utile pour le movedown
    SDL_Color couleurNoire = {0, 0, 0};
    vector<string> ListSong=menu.getList();
    int nbSongs=menu.getNbSongs();
    SDL_Surface tabList[nbSongs];
    for(unsigned int i=0;i<nbSongs();i++){
        tabList[i] = TTF_RenderText_Blended(fontMenu, ListSong[i], couleurNoire);
    }
    
    /* 
     TODO: affichage des surface avec espacement et affichage du curseur avec le meme increment (position pas acces)
            
     */
    
    
    
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
    
    
    im_background.loadFromFile("/../data/Batman.jpg",renderer);
    
    
    
    
    
    
    
    
}


sdlGame::~sdlGame(){
    
    
    
    //Fermeture TTF
    TTF_CloseFont(fontMenu);
    TTF_Quit();
    
    IMG_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
}

void sdlGame::sdlShowMenu(){
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    
    int x,y;
    for(x=0;x<640;x++){
        for(y=0;y<480;y++){
            im_background.draw(renderer,x*640,y*480,640,480);
        }
    }
    
    
}

void sdlGame::sdlShowGame(){
    
}




void sdlGame::sdlTest(){
        sdlShowMenu();
        SDL_RenderPresent(renderer);
}



void sdlGame::sdlGameLoop(){
    SDL_Event events;
    bool quitGame = false;
    while(!quitGame){
        /*mise en place de la partie*/
        
        //SDL_MIXER (lancement de la chanson)
        timeBegin = SDL_GetTicks();
        
        
        
        
        
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                quitGame = true;
            }
            else if {
                //boucle avec rafraichissement (=> actions automatiques)
                    //defiler cadre
                    //score
            }
    }
}

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



