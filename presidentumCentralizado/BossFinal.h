/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.h
 * Author: chiri
 *
 * Created on 12 de abril de 2016, 20:25
 */


//#include "NPC.h"
#ifndef BOSSFINAL_H
#define BOSSFINAL_H
#include "NPC.h"
#include "Jugador.h"
#include "Proyectil.h"

class BossFinal: public NPC {
public:
    BossFinal();
    BossFinal(bool valorPatrullaje, float posx, float posy, int type);
    bool getPatrullaje();
    void setPatrullaje(bool valorPatrullaje);
    void leerXML();
    ~BossFinal();
    void draw();
    void handle();
    void disparar();
    sf::Sprite* getSprite();
    
    int hp;
    std::vector<Proyectil*>* proyectiles;
    float paso;
    sf::Clock pasoTime;
    sf::Clock golpeosSegundo;
    float golpeoXseg;
    bool muerto;
    
private:
    sf::Clock aparicionProyectil;
    int direccion;//0 derecha. 1 izquierda
    int tipo;//partido politico
    bool patrullaje;
    int **matriz;
    sf::Texture *texturaEnemigo;
    bool golpeado;
    bool activado;

};

#endif /* ENEMIGO_H */

