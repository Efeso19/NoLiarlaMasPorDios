/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECargando.h
 * Author: chiri
 *
 * Created on 5 de mayo de 2016, 17:48
 */

#ifndef ECARGANDO_H
#define ECARGANDO_H

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Juego.h"


class ECargando: public Escena {
public:
    
    static ECargando* Instance(Juego* context);    
    ECargando(Juego* context);
    void Handle();
    void Init();
    void Update();
    void Render();
  
    ~ECargando();
    
private:

    sf::Font* font; 
    sf::RectangleShape* bgCartel;
    sf::RectangleShape* cartel;
//    sf::RectangleShape* marcoCarga;
//    sf::RectangleShape* progresoCarga;
    sf::Text* tituloText;
    sf::Text* cuerpoText;
     
    bool entryPoint;
    
    static ECargando* pinstance;
    Juego* _context;
    
};

#endif /* ECARGANDO_H */

