
#include "sdlGame.h"





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
    
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    
    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
    
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }
    Menu menu("../data/index");
    
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
    
    
    
    
    
}


sdlGame::~sdlGame(){
    
    IMG_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).
    
}


// a chaque debut de loop on appel SDL affiche


/*
SDL_Texture* sdlGame::surfaceNote(SDL_Renderer * renderer,int i){
    
    //Initialisation pour lecture de format JPG,PNG par sdl_image (1.2 ?)
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
    
    SDL_Texture* tex;
    //switch sur le i -> affichage de note differente (couleur principalement)
    SDL_RWops *rwop; //SDL_RW sur sdl_image permet la lecture du .png
    rwop=SDL_RWFromFile("/../data/Batman.jpg", "rb");
    SDL_Surface * image;
    image=IMG_LoadJPG_RW(rwop);
    tex= SDL_CreateTextureFromSurface(renderer,image);
    
    Uint32 format;
    int access = 0;
    int largeur = 0;
    int hauteur = 0;
    SDL_QueryTexture(tex,&format, &access, &largeur, &hauteur);
    
    SDL_Rect dest = { 640/2 - largeur/2,480/2 - hauteur/2, largeur, hauteur};
    SDL_RenderCopy(renderer,pTexture,NULL,&dest);

}
*/



/* void sdlGame (){
*/

void sdlGame::sdlLoop(){
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
                    case SDL_SCANCODE_ESCAPE:
                        quit=true;
                    default :
                        break;
                }
            }
        }
    }
}




