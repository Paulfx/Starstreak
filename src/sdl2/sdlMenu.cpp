#include "sdlMenu.h"

//TODO :
    //Menu deroulant pour le select
    //Menu difficulté (2)
    //Menu 0


// ============= MENU =============== //

//Procédure de mouvement pour le pointeur du menu 0 et 2`
//nbDiff=0 pour le menu 0


// Pas très utile vu qu'on a fixer le nb de difficulté
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
        printf("	%s\n", Mix_GetChunkDecoder(i));
        n = Mix_GetNumMusicDecoders();
        printf("There are %d available music decoders:\n",n);
    }
    for(i=0; i<n; ++i){
        printf("	%s\n", Mix_GetMusicDecoder(i));
    }
            

    
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


    SDL_GetWindowSize(window, &width, &height);    //parametres gestion de position/taille/resolution etc
    
    
    //POLICE DU MENU
    fontMenu= NULL;
    fontMenu=TTF_OpenFont("../data/theme/police/fast99.ttf", 0.0625*width); //TAILLE GENERE DYNAMIQUEMENT EN FONCTION DE LA TAILLE DE L'ECRAN
    if(fontMenu==NULL) {
        cout<<"TTF_OpenFont: "<<endl<<TTF_GetError()<<endl;
        // handle error
    }
    
    
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);//renderer synchro avec le rafraichissement de la fenetre
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // permet d'obtenir les redimensionnements plus doux.


    SDL_RenderSetLogicalSize(renderer,width, height); //taille fenetre
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //rend en noir
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
   /* texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888, //
                                SDL_TEXTUREACCESS_STREAMING,
                                //fluidité sur l'affichage des images
                                0,0); //taille de l'ecran (on pourrait utiliser des parametres du main ?)*/
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
    
    SDL_Color WhiteC = {255, 255, 255};
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
    }
    else{
        posPtr=menu->getCurrI()%10;//%menu->getNbSongs();
        im_ptrMenu.draw(renderer,(0.33)*width,(0.0375*height)+posPtr*(0.0625*height),(0.15*height),(0.05*height));
    }
    
    //Declaration des 3 composants de la liste
    SDL_Surface * SurfaceList;
    SDL_Texture * tex;
    SDL_Rect rec;
    
    //SDL_Color couleurNoire = {0, 0, 0};
    string tempTitle;
    
    //cout<<menu->getNbSongs();
    int i=beginShowTitle;
    int posTitle=0;
    while(i<endShowTitle)
    {
        tempTitle=menu->getTitleSong(i);
        //cout <<tempTitle <<endl;
        SurfaceList = TTF_RenderText_Blended(fontMenu,tempTitle.c_str(),WhiteC);
        if(SurfaceList==NULL)
        {
            cout<<"Erreur lors de la creation de la surface : "<<SDL_GetError()<<endl;
        }
        tex= SDL_CreateTextureFromSurface(renderer,SurfaceList);
        if(tex==NULL)
        {
            cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
        }
        SurfaceList=NULL;
        rec.x=(0.025)*width;
        rec.y=(0.03125)*height+posTitle*(0.0625)*height;
        rec.w=(0.0167)*width*tempTitle.size();
        rec.h=(0.0625)*height;
        if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0)
        {
            cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
        }
        i++;
        posTitle++;

    }
}

//### Affiche le menu difficulté ##########
void SdlMenu::sdlShowDiff(){
    SDL_Color RedC={255,0,0};
    SDL_Color WhiteC = {255, 255, 255};
    SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
    SDL_RenderClear(renderer);
    im_backgroundMenu2.draw(renderer,0,0,width,height);
    
    //###### Affichage Chanson Selectionnée ##########
    SDL_Surface * Surface;
    SDL_Texture * tex;
    SDL_Rect rec;
    
    Surface=TTF_RenderText_Blended(fontMenu,choosenSongTitle.c_str(),RedC);
    if(Surface==NULL){
        cout<<"Erreur lors de la creation de la surface : "<<SDL_GetError()<<endl;
        
    }
    tex=SDL_CreateTextureFromSurface(renderer,Surface);
    if(tex==NULL){
        cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
        
    }
    rec.x=0.09*width;
    rec.y=0.07*height;
    rec.w=0.0167*width*choosenSongTitle.size();
    rec.h=0.0625*height;
    if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
        cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
    }
    
    //##### Affichage Difficulté ##########
    string tempTxt;
    for(unsigned int i=0;i<3;i++){
        switch(i){
            case 0:{
                tempTxt="0: Pour les ROUILLES";
                break;
            }
            case 1:{
                tempTxt="1: Pour les CASUALS";
                break;
            }
                
            case 2:{
                tempTxt="2: Pour les ROCKERS";
                break;
            }
        }
        Surface=TTF_RenderText_Blended(fontMenu,tempTxt.c_str(),WhiteC);
        tex=SDL_CreateTextureFromSurface(renderer,Surface);
        if(tex==NULL){
            cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;
            
        }
        rec.x=0.066*width;
        rec.y=0.20*height+(0.105*height)*i;
        rec.w=0.016*width*tempTxt.size();
        rec.h=0.12*height;
        if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
            cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
        }
    }
    
    //######### Affichage du pointeur ########
    im_ptrMenu.draw(renderer,(0.40)*width,0.25*height+(0.105*height)*posPtr,0.1*width,0.05*height);
}

//Essai de loop+affichage
void SdlMenu::sdlTest(){
    sdlLoop();
}



//###### LOOP menu #####
void SdlMenu::sdlLoopMenu(bool quit){
    SDL_Event events;
    while(SDL_PollEvent(&events)){
        if (events.type == SDL_QUIT){
            quit = true;
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
                        case 0: {//SET MODE GAME + state
                            stateMenu=1;
                            posPtr=0;
                            break;
                        }
                        case 1:{//SET MODE CREATE + state -> set mode dans la partie 2
                            creationMode=true;
                            stateMenu=1;
                            break;
                        }
                        case 2: {//QUIT
                            quit=true;
                            soundQuit();
                            break;
                        }
                    }
                    break;
                }
                case SDL_SCANCODE_ESCAPE:
                {
                    quit=true;
                    soundQuit();
                    break;
                }
                default:break;
            }
        }
        
    }
}

//###### LOOP Select song ############
void SdlMenu::sdlLoopSelect(){
    SDL_Event events;
    while (SDL_PollEvent(&events)) {
        if (events.type == SDL_QUIT){
            stateMenu=0;
        }else if (events.type == SDL_KEYDOWN) {// Si une touche est enfoncee
            switch (events.key.keysym.scancode) { //On test en fonction de la touche enfoncée (id par scancode)
                case SDL_SCANCODE_UP: //flèche du haut
                {
                    if (Mix_PlayChannel(2,soundMove,0)==-1) {
                        cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                    }
                    menu->moveUp();
                    break;
                }
                case SDL_SCANCODE_DOWN://flèche du bas
                {
                    if (Mix_PlayChannel(3,soundMove,0)==-1) {
                        cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                    }
                    menu->moveDown();
                    break;
                }
                case SDL_SCANCODE_RETURN://touche entré
                {
                    if (Mix_PlayChannel(4,soundAccept,0)==-1) {
                        cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                    }
                    choosenSongTitle=(menu->getCurrSong()).title;
                    //im_chargment.show()
                    
                    stateMenu = 2; //Direction Difficulté !
                    posPtr=0;
                    break;
                }
                    
                case SDL_SCANCODE_ESCAPE://touche echap
                {
                    stateMenu=0; //retour arrière
                    creationMode=false;
                    break;
                }
                default:break;
            }
        }
    }

}

// ###### LOOP difficulté ##########
void SdlMenu::sdlLoopDiff(){
    SDL_Event events;
    while (SDL_PollEvent(&events)) {
        if (events.type == SDL_QUIT){
            stateMenu=0; //retour a menu, pas a select ?
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
                        SdlPartitionMaker partMaker(window,renderer,menu->getCurrSong());
                        partMaker.sdlLoop();
                        soundInit();
                        stateMenu=0;
                        creationMode=false;
                        
                    }
                    else {
                        
                        soundQuit();
                        SdlGame game(window,renderer,menu->getCurrSong(),posPtr+1,menu->getMode());
                        game.sdlLoop();
                        soundInit();//pour relancer les sons (on ne repasse jamais dans l'appel en haut de menu)
                        stateMenu = 0;
                        //ON PEUT FAIRE UN BIEN JOUERF AFFICHAGE DU SCORE OU UNNE CONNERIE DE CE GENRE ICI (une fonction show avec un delay ou un ok)
                        //Pourquoi un object de la classe "loadingImage" ou "fadeImage" :)?
                        
                    }
                    break;
                }
                case SDL_SCANCODE_ESCAPE://touche echap
                {
                    stateMenu=1;//retour arrière
                    break;
                }
                default:
                    break;
            }
        }
    }

}


//########## LOOP PRINCIPALE #########
void SdlMenu::sdlLoop(){
    
    bool quit = false;
    soundInit();
    //sdlShow();
    while (!quit){
        switch(stateMenu){
            case 0: {// menu0 loop
                sdlShowMenu();
                SDL_RenderPresent(renderer);
                sdlLoopMenu(quit);
                break;
            }
            case 1: {//SELECT lloop
                sdlShowSelect();
                SDL_RenderPresent(renderer);
                sdlLoopSelect();
                break;
            }
            case 2: {//Difficulty loop
                sdlShowDiff();
                SDL_RenderPresent(renderer);
                sdlLoopDiff();
                break;
            }
            default:break;
        }

    }
}

void SdlMenu::soundInit() {
    
    soundMove=NULL;
    soundAccept=NULL;
    soundMenu=NULL;
    
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
    
void SdlMenu::soundQuit() {// ne peut etre appelé que lorsqu' on quite le programme sinon on aura plus aucun son lorsque l'on retourne dans le menu
    Mix_HaltChannel(1);
    Mix_FreeChunk(soundAccept);
    Mix_FreeChunk(soundMove);
    Mix_FreeChunk(soundMenu);
}



SdlMenu::~SdlMenu(){

    delete menu;

    //Fermeture TTF
    //TTF_CloseFont(fontMenu);  -> erreur d'allocation
    TTF_Quit();
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

}


