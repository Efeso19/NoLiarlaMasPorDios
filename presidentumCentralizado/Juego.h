/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.h
 * Author: chiri
 *
 * Created on 5 de abril de 2016, 17:56
 */

#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include "Escena.h"

class Juego {
    
public:
    static Juego* Instance();
    Juego();
    void Init();
    
    Escena* currentState();
    
    void setState (Escena* state);
    
    void Update();
    
    virtual ~Juego();
    
    sf::RenderWindow* window;
    
    sf::Event event;
    
    int windowWidth = 1066; //Width de la window
    
    int windowHeight = 600; //Height de la window
    
private:
	Escena* _state;
        static Juego* pinstance;
};

#endif /* JUEGO_H */
