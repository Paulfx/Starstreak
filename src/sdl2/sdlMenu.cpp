#include "sdlMenu.h"

//TODO :
    //Menu deroulant pour le select
    //Menu difficulté (2)
    //Menu 0


// ============= MENU =============== //

//Procédure de mouvement pour le pointeur du menu 0 et 2`
//nbDiff=0 pour le menu 0


const string txtDiff0 = "1. Pour les ROUILLES";
const string txtDiff1 = "2. Pour les CASUALS";
const string txtDiff2 = "3. Pour les ROCKEURS";



void SdlMenu::movePtr(const string move,const int IDmenu,const int nbDiff){
    if(IDmenu==0){
        if(move=="up"){
            if(posPtr==0){
                posPtr=2;
            }else{
                posPtr=posPtr-1;
            }
        }else{
            if(posPtr==2){
                posPtr=0;
            }else{
                posPtr=posPtr+1;
            }
        }
    }else{
        if(move=="up"){
            if(posPtr==0){
                posPtr=nbDiff-1;
            }else{
                posPtr=posPtr-1;
            }
        }else{//move down
            if(posPtr==nbDiff-1){
                posPtr=0;
            }else{
                posPtr=posPtr+1;
            }
        }
        
    }
}

SdlMenu::SdlMenu() : creationMode(false){
    // INITIALISATION DE SDL
    sdlInit();

            /*SDL_Mixer init*/
    soundMove=NULL;
    soundAccept=NULL;
    soundMenu=NULL;
    
    posPtr=0;
    stateMenu=0;

    //Initialisation du menu
    menu= new Menu("../data/index");

    //Ouverture de la fenetre
    window = SDL_CreateWindow("StarStreak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,0,0,SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);//renderer synchro avec le rafraichissement de la fenetre
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.
    SDL_GetWindowSize(window, &width, &height);    //parametres gestion de position/taille/resolution etc
    
    //TTF
    //POLICE DU MENU
    fontMenu=TTF_OpenFont("../data/theme/police/fast99.ttf", 0.0625*width); //TAILLE GENERE DYNAMIQUEMENT EN FONCTION DE LA TAILLE DE L'ECRAN
    if(fontMenu==NULL) {
        cout<<"TTF_OpenFont: "<<endl<<TTF_GetError()<<endl;
        // handle error
    }
    
    createTextTextures();
    SDL_RenderSetLogicalSize(renderer,width, height); //taille fenetre
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //rend en noir
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    


    if(renderer){

        im_backgroundMenu0.loadFromFile("../data/theme/BackgroundMenu0.jpg",renderer);
        im_backgroundMenu1.loadFromFile("../data/theme/BackgroundMenu1.jpg",renderer);
        im_backgroundMenu2.loadFromFile("../data/theme/BackgroundMenu2.jpg",renderer);

        im_ptrMenu.loadFromFile("../data/theme/Select.png",renderer);
        im_ptrMenuWhite.loadFromFile("../data/theme/selecteurBlanc.png",renderer);
        im_ptrMenuBlack.loadFromFile("../data/theme/selecteurNoir.png",renderer);
    }else {
        cout << "Erreur dans l'initialisation du renderer" << endl;
    }
}

void SdlMenu::sdlInit() {
    //SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }
        //TTF
    if (TTF_Init() == -1) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << SDL_GetError() << endl;SDL_Quit();exit(1);
    }

    //IMAGE
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;SDL_Quit();exit(1);
    }
    //MIXER
    
     if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096)==-1){
         cout<<Mix_GetError()<<endl;
     }
   
    int i,n=Mix_GetNumChunkDecoders();
    printf("There are %d available chunk(sample) decoders:\n",n);
    for(i=0; i<n; ++i){
        printf("    %s\n", Mix_GetChunkDecoder(i));
        n = Mix_GetNumMusicDecoders();
        printf("There are %d available music decoders:\n",n);
    }
    for(i=0; i<n; ++i){
        printf("    %s\n", Mix_GetMusicDecoder(i));
    }
}

void SdlMenu::soundInit() {
    
    soundMove=NULL;
    soundAccept=NULL;
    soundMenu=NULL;
    soundBack=NULL;
    
    if (soundMenu==NULL){
        Mix_AllocateChannels(5);
        
        soundMove=Mix_LoadWAV("../data/theme/sounds/move.wav");
        if(!soundMove){
            cout<<"erreur ouverture effet de séléction:"<<Mix_GetError()<<endl;
        }
        
        soundAccept=Mix_LoadWAV("../data/theme/sounds/action.wav");
        if(!soundAccept){
            cout<<"erreur ouverture effet de validation:"<<Mix_GetError()<<endl;
        }
        
        soundBack=Mix_LoadWAV("../data/theme/sounds/back.wav");
        if(!soundBack){
            cout<<"erreur ouverture effet de retour:"<<Mix_GetError()<<endl;
        }
        /*musique de fond dans le menu*/
        /**@todo Ouvrir plusieurs son de menu qui se lance aléatoirement**/
        
        soundMenu=Mix_LoadWAV("../data/theme/sounds/menuKiller.wav");
        if(!soundMenu){
            cout<<"erreur ouverture musique menu:"<<Mix_GetError()<<endl;
        }
        if (Mix_PlayChannel(1,soundMenu,2)==-1) {
            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
        }
    }
}
    
void SdlMenu::soundQuit() {
    Mix_HaltChannel(1);
    Mix_FreeChunk(soundAccept);
    Mix_FreeChunk(soundMove);
    Mix_FreeChunk(soundMenu);
    Mix_FreeChunk(soundBack);
}



SdlMenu::~SdlMenu(){

    delete menu;

    //Fermeture TTF
    TTF_CloseFont(fontMenu);
    soundQuit();
    TTF_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

}


void SdlMenu::createTextTextures() {
    SDL_Color white = {255, 255, 255};
    SDL_Texture* texture;
    for(unsigned int i=0;i<menu->getNbSongs();++i) {
        SDL_Surface* surf;
        surf = TTF_RenderText_Blended(fontMenu,menu->getTitleSong(i).c_str(),white);
        texture=surfaceToTexture(surf);
        texTab.push_back(texture);
    }
    SDL_Surface* surfDiff0;
    surfDiff0 = TTF_RenderText_Blended(fontMenu,txtDiff0.c_str(),white);
    textureDiff0=surfaceToTexture(surfDiff0);

    SDL_Surface* surfDiff1;
    surfDiff1 = TTF_RenderText_Blended(fontMenu,txtDiff1.c_str(),white);
    textureDiff1=surfaceToTexture(surfDiff1);

    SDL_Surface* surfDiff2;
    surfDiff2 = TTF_RenderText_Blended(fontMenu,txtDiff2.c_str(),white);
    textureDiff2=surfaceToTexture(surfDiff2);

}

SDL_Texture* SdlMenu::surfaceToTexture( SDL_Surface* surf ) {
    SDL_Texture* texture;
    texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    return texture;
}

// ##### Affiche le menu 0 ##########
void SdlMenu::sdlShowMenu(){
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    im_backgroundMenu0.draw(renderer,0,0,width,height);
    im_ptrMenuBlack.draw(renderer,(0.66*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
    im_ptrMenuWhite.draw(renderer,(0.25*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
}

//###### Affiche le menu Select song #########
void SdlMenu::sdlShowSelect(){
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    im_backgroundMenu1.draw(renderer,0,0,width,height);
    int beginShowTitle=0;
    int endShowTitle=10;

    //Menu Deroulant
    if((menu->getCurrI())>9){
        posPtr=9;//pointe sur la derniere
        im_ptrMenu.draw(renderer,(0.33)*width,(0.0375*height)+posPtr*(0.0625*height),(0.15*height),(0.05*height));
        
        beginShowTitle=menu->getCurrI()%10; //affiche les 10 chanson aprés la menu->getCurrI()%10
        endShowTitle=menu->getCurrI();
        if(menu->getCurrI()==10){
            beginShowTitle=1;
            endShowTitle=menu->getCurrI()+1;
        }
    }
    else{
        posPtr=menu->getCurrI()%10;//%menu->getNbSongs();
        im_ptrMenu.draw(renderer,(0.33)*width,(0.0375*height)+posPtr*(0.0625*height),(0.15*height),(0.05*height));
    }
    
    SDL_Rect rec;
    int i=beginShowTitle;
    int posTitle=0;
    while(i<endShowTitle)
    {
        rec.x=(0.025)*width;
        rec.y=(0.03125)*height+posTitle*(0.0625)*height;
        rec.w=(0.0167)*width*menu->getTitleSong(i).size();
        rec.h=(0.0625)*height;
        if(SDL_RenderCopy(renderer, texTab[i], NULL, &rec)!=0){
            cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
        }
        i++;
        posTitle++;

    }
}

//### Affiche le menu difficulté ##########
void SdlMenu::sdlShowDiff(){
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    im_backgroundMenu2.draw(renderer,0,0,width,height);
    
    //###### Affichage Chanson Selectionnée ##########
    SDL_Rect rec;
    rec.x=0.09*width;
    rec.y=0.07*height;
    rec.w=0.0167*width*menu->getCurrSong().title.size();
    rec.h=0.0625*height;
    if(SDL_RenderCopy(renderer, texTab[menu->getCurrI()], NULL, &rec)!=0){ //CURR I 
        cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
    }
    //##### Affichage Difficulté ##########
    int size;
    SDL_Texture* tex;
    for(unsigned int i=0;i<3;i++){
        switch(i){
            case 0:tex=textureDiff0;size=txtDiff0.size();break;
            case 1:tex=textureDiff1;size=txtDiff1.size();break;
            case 2:tex=textureDiff2;size=txtDiff2.size();break;
        }
        rec.x=0.066*width;
        rec.y=0.20*height+(0.105*height)*i;
        rec.w=0.016*width*size;
        rec.h=0.12*height;
        if(SDL_RenderCopy(renderer, tex ,NULL, &rec)!=0){
            cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
        }
    }
    //######### Affichage du pointeur ########
    im_ptrMenu.draw(renderer,(0.40)*width,0.25*height+(0.105*height)*posPtr,0.1*width,0.05*height);
}


//########## LOOP PRINCIPALE #########
void SdlMenu::sdlLoop(){
    soundInit();
    while (stateMenu!=-1){
        switch(stateMenu){
            case 0: {// menu0 loop
                stateMenu=sdlLoopMenu();
                break;
            }
            case 1: {//SELECT lloop
                stateMenu=sdlLoopSelect();
                break;
            }
            case 2: {//Difficulty loop
                stateMenu=sdlLoopDiff();
                break;
            }
            default:break;
        }
    }
}



//###### LOOP menu #####
int SdlMenu::sdlLoopMenu(){
    assert(stateMenu==0);
    SDL_Event events;
    while(1) {
        while(SDL_PollEvent(&events)){
            if (events.type == SDL_QUIT){
                return -1;
            }else if(events.type == SDL_KEYDOWN){
                switch(events.key.keysym.scancode){
                    case SDL_SCANCODE_UP:
                    {
                        if (Mix_PlayChannel(2,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        movePtr("up",0,0);
                        break;
                    }
                    case SDL_SCANCODE_DOWN:
                    {
                        if (Mix_PlayChannel(3,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        movePtr("down",0,0);
                        break;
                    }
                    case SDL_SCANCODE_RETURN:
                    {
                        if (Mix_PlayChannel(4,soundAccept,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        switch(posPtr){
                            case 0: {//Select menu
                                posPtr=0;
                                return 1;
                            }
                            case 1:{//Create menu
                                creationMode=true;
                                return 1;
                            }
                            case 2: {//QUIT
                                return -1;
                            }
                        }
                        break;
                    }
                    case SDL_SCANCODE_ESCAPE:
                    {
                        return -1;
                    }
                    default:break;
                }
            }
            
        }
        sdlShowMenu();
        SDL_RenderPresent(renderer);
    }
}

//###### LOOP Select song ############
int SdlMenu::sdlLoopSelect(){
    assert(stateMenu==1);
    SDL_Event events;
    while(1) {
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                stateMenu=0;
                posPtr=0;
            }else if (events.type == SDL_KEYDOWN) {// Si une touche est enfoncee
                switch (events.key.keysym.scancode) { //On test en fonction de la touche enfoncée (id par scancode)
                    case SDL_SCANCODE_UP:
                    {
                        if (Mix_PlayChannel(2,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->moveUp();
                        break;
                    }
                    case SDL_SCANCODE_DOWN:
                    {
                        if (Mix_PlayChannel(3,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        menu->moveDown();
                        break;
                    }
                    case SDL_SCANCODE_RETURN://Menu difficulté
                    {
                        if (Mix_PlayChannel(4,soundAccept,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        posPtr=0;
                        return 2;
                    }
                        
                    case SDL_SCANCODE_ESCAPE://Retour arrière
                    {
                        if (Mix_PlayChannel(4,soundBack,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        creationMode=false;
                        posPtr=0;
                        return 0;
                    }
                    default:break;
                }
            }
        }
        sdlShowSelect();
        SDL_RenderPresent(renderer);
    }
}

// ###### LOOP difficulté ##########
int SdlMenu::sdlLoopDiff(){
    assert(stateMenu==2);
    SDL_Event events;
    while(1) {
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT){
                return -1; //retour a menu, pas a select ?
            }else if (events.type == SDL_KEYDOWN) {// Si une touche est enfoncee
                switch (events.key.keysym.scancode) { //On test en fonction de la touche enfoncée (id par scancode)
                    case SDL_SCANCODE_UP: //flèche du haut
                    {
                        if (Mix_PlayChannel(2,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        movePtr("up",2,3);
                        break;
                    }
                    case SDL_SCANCODE_DOWN:
                    {//flèche du bas
                        if (Mix_PlayChannel(3,soundMove,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        movePtr("down",2,3);
                        break;
                    }
                    case SDL_SCANCODE_RETURN://touche entré
                    {
                        if (Mix_PlayChannel(4,soundAccept,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        
                        if(creationMode) {
                            soundQuit();
                            SdlPartitionMaker partMaker(window,renderer,menu->getCurrSong(),posPtr+1);
                            partMaker.sdlLoop();
                            soundInit();
                            creationMode=false;
                            posPtr=0;
                            return 0;//Menu initial
                        }
                        else {
                            soundQuit();
                            SdlGame game(window,renderer,menu->getCurrSong(),posPtr+1);
                            game.sdlLoop();
                            soundInit();//pour relancer les sons (on ne repasse jamais dans l'appel en haut de menu)
                            //ON PEUT FAIRE UN BIEN JOUERF AFFICHAGE DU SCORE OU UNNE CONNERIE DE CE GENRE ICI (une fonction show avec un delay ou un ok)
                            //Pourquoi un object de la classe "loadingImage" ou "fadeImage" :)?
                            posPtr=0;
                            return 0;
                        }
                        break;
                    }
                    case SDL_SCANCODE_ESCAPE://touche echap
                    {
                        if (Mix_PlayChannel(4,soundBack,0)==-1) {
                            cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                        }
                        return 1;//retour arrière
                    }
                    default:
                        break;
                }
            }
        }

        sdlShowDiff();
        SDL_RenderPresent(renderer);
    }
}
