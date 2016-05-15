/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECinematica.h
 * Author: chiri
 *
 * Created on 7 de abril de 2016, 17:29
 */

#ifndef ECINEMATICA_H
#define ECINEMATICA_H

#include "Juego.h"

class ECinematica: public Escena {
public:
    
    void Handle();
    void Init();
    void Update();
    void Render();
    Juego* getContext();
    static ECinematica* Instance(Juego* context);
    ~ECinematica();
    
    sf::RectangleShape rectangulo;
  
    
protected:
    ECinematica(Juego* context);
    ECinematica(const ECinematica &);
    ECinematica &operator = (const ECinematica &);

private:
    
    bool  initState;
    static ECinematica* pinstance;
    Juego* _context;
    
};

#endif /* ECINEMATICA_H */

