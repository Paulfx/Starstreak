
#include "sdlGame.h"



sdlGame::sdlGame(){
    
    window=NULL;
    renderer=NULL;
    font=NULL;
    texture=NULL;
    menu=NULL;
    
}


sdlGame::~sdlGame(){
    
}




void sdlGame::init_Window(){
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

}

void sdlGame::open_Window(){
    window = SDL_CreateWindow("StarStreak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,SDL_WINDOW_FULLSCREEN_DESKTOP);
    //parametres gestion de position/taille/resolution etc
    renderer = SDL_CreateRenderer(sdlWindow, -1, 0);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.
    SDL_RenderSetLogicalSize(sdlRenderer, 640, 480); //taille fenetre
    SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255); //rend en noir
    SDL_RenderClear(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
    texture = SDL_CreateTexture(sdlRenderer,
                                   SDL_PIXELFORMAT_ARGB8888, //
                                   SDL_TEXTUREACCESS_STREAMING,
                                   //fluidité sur l'affichage des images
                                   640, 480); //taille de l'ecran (on pourrait utiliser des parametres du main ?)
}




/* void sdlGame (){
*/

void sdlLoop ();{
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
                    default :
                        break;
                }
        
            }
        }
        
        

}
