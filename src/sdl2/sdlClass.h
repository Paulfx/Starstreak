#ifndef SDL_CLASS_H
#define SDL_CLASS_H
//+ classe son, etc...

class Image {
    
private:
    
    int width,height;
    SDL_Texture * texture;

public:
    Image ();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
};


class LoadingImage {

};

#endif