#ifndef MENU_H
#define MENU_H


#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include "game.h"
#include "class.h"

using namespace std;

class Menu {
    
    private :
    
    Song** songTab; //tableau de liens sur song
    unsigned int currI; //indice dans songTab de currPtr
    unsigned int nbSongs; //taille du tab
    bool active; //false si menu inactif = une game est active
    //Game* currGame; //La partie en cours
    unsigned int difficulty;// 1, 2 ou 3
    bool mode;
    
    
    
    public :
    /**@brief Constructeur par défaut
     */
    Menu();
    
    /**@brief Constructeur
     
     Constructeur de la classe Menu
     
     Ouvre le fichier 'filename' et remplit songTab des Song correspondants
     
     @param[in,out] filename
     */
    Menu(const string& filename);
    
    /**@brief Destructeur
     Destructeur de la classe Menu
     Libère l'espace alloué dans le tableau songTab
     */
    ~Menu();
    
    /**@brief Modifie le currPtr de manière à remonter dans le menu
     */
    void moveUp();
    
    /**@brief Modifie le currPtr de manière à descendre dans le menu
     */
    void moveDown();
    
    /**@brief Crée la partie associée à la chanson pointée par currPtr
     Rend le menu inactif
     */
    Song& getCurrSong();
    
    /** @brief Accesseur de la chanson en cours
     @return Reference de la chanson en cours
     */
    const Song& getConstCurrSong();
    
    /** @brief Accesseur pointeur sur la chanson
     @return position du pointeur
     */
    unsigned int getCurrI() const;
    
    /** @brief Accesseur nombre de chansons disponibles
     @return nombre de chansons
     */
    unsigned int getNbSongs() const;
    
    /** @brief Accesseur DIfficulté
     @return difficulté
     */
    unsigned int getDifficulty() const;
    
    /** @brief Accesseur Game
     @return reference de Game
     */
    Game& getGame();
    
    /** @brief Accesseur booleen d'activité du menu (txt)
     @return Booleen d'activité
     */
    bool isActive() const;
    
    /** @brief Mutateur Difficulté
     */
    void increaseDiff();
    
    /** @brief Mutateur Difficultés
     */
    void decreaseDiff();
    
    /** @brief Accesseur Mode de jeux
     @return Mode de jeux
     */
    bool getMode() const;
    
    /** @brief Renvoie le tab des noms de chansons
     @return Liste des chansons
     */
    string getList();
    
    /** @brief Renvoie le bom de la chanson a l'indice i
     @param indice
     */
    string getTitleSong(unsigned int i);
    
};

#endif

