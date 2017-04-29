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


SdlMenu::SdlMenu(){
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
    /*
    int flags=MIX_INIT_OGG;
    int initted=Mix_Init(flags);
    if(initted&flags != flags) {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        // handle error
    }
     */
    
    //Debuggage sdl_mixer cross OS -> .ogg pas supporté pas mac naturelement
    Mix_AllocateChannels(5);
    
    {
        int i,n=Mix_GetNumChunkDecoders();
        printf("There are %d available chunk(sample) decoders:\n",n);
        for(i=0; i<n; ++i)
            printf("	%s\n", Mix_GetChunkDecoder(i));
        n = Mix_GetNumMusicDecoders();
        printf("There are %d available music decoders:\n",n);
        for(i=0; i<n; ++i)
            printf("	%s\n", Mix_GetMusicDecoder(i));
    }

    
/*SDL_Mixer init*/
   

    
    /* bruitages de naviguation + musique de fond*/

    soundMove=Mix_LoadWAV("../data/theme/sounds/336.wav"); //Mix_LoadWAV("../data/theme/sounds/move.ogg")
    if(!soundMove){
        cout<<"erreur ouverture effet de séléction:"<<Mix_GetError()<<endl;
    }

    soundAccept=Mix_LoadWAV("../data/theme/sounds/action.ogg");
    if(!soundAccept){
        cout<<"erreur ouverture effet de validation:"<<Mix_GetError()<<endl;
    }
    /*musique de fond dans le menu*/
    /**@todo Ouvrir plusieurs son de menu qui se lance aléatoirement**/

    soundMenu=Mix_LoadWAV("../data/theme/sounds/menu.ogg");
    if(!soundMenu){
        cout<<"erreur ouverture musique menu:"<<Mix_GetError()<<endl;
    }
    if (Mix_FadeInChannel(1,soundMenu,2,4000)==-1) {
        cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
        }
    Mix_Pause(1);


    


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
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888, //
                                SDL_TEXTUREACCESS_STREAMING,
                                //fluidité sur l'affichage des images
                                0,0); //taille de l'ecran (on pourrait utiliser des parametres du main ?)
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


//Affichage du menu SELECT state=1
void SdlMenu::sdlShow(){
    SDL_Color WhiteC = {255, 255, 255};
    SDL_Color RedC={255,0,0};
    switch(stateMenu){
        case 0: {
            SDL_SetRenderDrawColor(renderer, 230, 240, 255, 255);
            SDL_RenderClear(renderer);

            im_backgroundMenu0.draw(renderer,0,0,width,height);
            switch(posPtr){
                case 0:
                    im_ptrMenuBlack.draw(renderer,(0.66*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
                    im_ptrMenuWhite.draw(renderer,(0.25*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
                    break;
                case 1:
                    im_ptrMenuBlack.draw(renderer,(0.66*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
                    im_ptrMenuWhite.draw(renderer,(0.25*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
                    break;
                case 2:
                    im_ptrMenuBlack.draw(renderer,(0.66*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
                    im_ptrMenuWhite.draw(renderer,(0.25*width),posPtr*(0.1375*height)+(0.35*height),0.05*width,0.07*height);
                    break;
            }
            break;
        }
        case 1: {
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

            //Decla des 3 composants de la liste
            SDL_Surface * SurfaceList;
            SDL_Texture * tex;
            SDL_Rect rec;
            
            //SDL_Color couleurNoire = {0, 0, 0};
            string tempTitle;

            cout<<menu->getNbSongs();
            int i=beginShowTitle;
            int posTitle=0;
            while(i<endShowTitle){
                tempTitle=menu->getTitleSong(i);
                cout <<tempTitle <<endl;
                SurfaceList = TTF_RenderText_Blended(fontMenu,tempTitle.c_str(),WhiteC);
                if(SurfaceList==NULL){
                    cout<<"Erreur lors de la creation de la surface : "<<SDL_GetError()<<endl;

                }
                tex= SDL_CreateTextureFromSurface(renderer,SurfaceList);
                if(tex==NULL){
                    cout<<"Erreur lors de la creation de la texture : "<<SDL_GetError()<<endl;

                }
                SurfaceList=NULL;
                rec.x=(0.025)*width;
                rec.y=(0.03125)*height+posTitle*(0.0625)*height;
                rec.w=(0.0167)*width*tempTitle.size();
                rec.h=(0.0625)*height;
                if(SDL_RenderCopy(renderer, tex, NULL, &rec)!=0){
                    cout<<"Erreur lors de l'update du renderer : "<<SDL_GetError()<<endl; //printf plus en C
                }
                i++;
                posTitle++;
            }
            break;
        }
        case 2: {
            
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
                        tempTxt="0: Pour les NOOBS";
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
                                    //(0.33)*width,(0.0375*height)+posPtr*(0.0625*height),(0.15*height),(0.05*height)
            im_ptrMenu.draw(renderer,(0.40)*width,0.25*height+(0.105*height)*posPtr,0.1*width,0.05*height);
            
            
            
            break;
        }
    }

        SDL_RenderPresent(renderer);//ligne a rajouter dans showMenu ? (fin) non comme ds pacman
}


//Essai de loop+affichage
void SdlMenu::sdlTest(){
    sdlLoop();
}

//Premiere Loop
// Correspond au menu, la loop du jeu sera appelé dedans (aprés choose)
void SdlMenu::sdlLoop(){
    SDL_Event events;
    bool quit = false;
    Mix_Resume(1);
                        /*Debut de la boucle Menu*/
    while (!quit){
        sdlShow();

        switch(stateMenu){
            case 0: {// menu0 loop

                while(SDL_PollEvent(&events)){
                    if (events.type == SDL_QUIT){
                        quit = true;
                    }else if(events.type == SDL_KEYDOWN){
                        switch(events.key.keysym.scancode){
                            case SDL_SCANCODE_UP:
                                if (Mix_PlayChannel(2,soundMove,0)==-1) {
                                    cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                                }
                                movePtr("up",0,0);
                                break;
                            case SDL_SCANCODE_DOWN:
                                if (Mix_PlayChannel(3,soundMove,0)==-1) {
                                    cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                                }
                                movePtr("down",0,0);
                                break;
                            case SDL_SCANCODE_RETURN:
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
                                        quit=true;
                                        Mix_HaltChannel(1);
                                        cout <<endl <<"Pas encore implementé, une mise à jour arrive prochainement, stay tuned"<< endl;
                                        break;
                                    }
                                    case 2: {//QUIT
                                        quit=true;
                                        soundQuit();
                                        break;
                                    }
                                }
                                break;
                            case SDL_SCANCODE_ESCAPE:
                                quit=true;
                                soundQuit();
                                break;
                            default:
                                break;
                        }
                    }

                }
                break;
            }
            case 1: {//SELECT lloop
                while (SDL_PollEvent(&events)) {
                if (events.type == SDL_QUIT){
                    quit = true;
                    soundQuit();
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
                                quit=true;
                                break;
                            }
                            default :
                                break;
                        }
                    }
                }
                break;
            }
            case 2: {//Difficulty loop
                while (SDL_PollEvent(&events)) {
                    if (events.type == SDL_QUIT){
                        quit = true;
                        soundQuit();
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
                                
                                
                                
                                SdlGame game(texture,window,renderer,menu->getCurrSong(),posPtr+1,menu->getMode());
                                //DETRUIRE LE JEUUUUUU
                                Mix_HaltChannel(1);// Theo faudra que tu supprimes cette ligne lorsque le choix de la difficultée sera ok
                                game.sdlLoop();
                                if (Mix_FadeInChannel(1,soundMenu,2,4000)==-1) {// RElance la musique du menu
                                    cout<<"Mix_PlayChannel error"<<Mix_GetError()<<endl;
                                }
                                stateMenu = 0;
                                //ON PEUT FAIRE UN BIEN JOUERF AFFICHAGE DU SCORE OU UNNE CONNERIE DE CE GENRE ICI (une fonction show avec un delay ou un ok)
                                break;
                            }
                         
                            case SDL_SCANCODE_ESCAPE://touche echap
                            {
                                
                                //On pourrait imaginer un retour au menu de selection donc destruction de game ?
                                quit=true;
                                soundQuit();
                                break;
                            }
                            default :
                                break;
                        }
                    }
                }
                break;
            }
        }

    }
}


void SdlMenu::soundQuit() {// ne peut etre appelé que lorsqu' on quite le programme sinon on aura plus aucun son lorsque l'on retourne dans le menu
    Mix_HaltChannel(1);//arrete le musique du menu MAIS CA DANS FONCTION !
    Mix_FreeChunk(soundAccept);
    Mix_FreeChunk(soundMove);
    Mix_FreeChunk(soundMenu);
}




SdlMenu::~SdlMenu(){



    //Fermeture TTF
    //TTF_CloseFont(fontMenu);  -> erreur d'allocation
    TTF_Quit();
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire).

}


