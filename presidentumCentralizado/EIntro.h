/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EIntro.h
 * Author: chiri
 *
 * Created on 5 de abril de 2016, 19:47
 */

#ifndef EINTRO_H
#define EINTRO_H

#include "Juego.h"

class EIntro: public Escena {
public:
    
    void Handle();
    void Init();
    void Update();
    void Render();
    Juego* getContext();
    static EIntro* Instance(Juego* context);
    ~EIntro();
    
    
protected:
    EIntro(Juego* context);
    EIntro(const EIntro &);
    EIntro &operator = (const EIntro &);

private:
    
    static EIntro* pinstance;
    Juego* _context;
    
};

#endif /* EINTRO_H */

