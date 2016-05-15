/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMenuInGame.h
 * Author: chiri
 *
 * Created on 7 de abril de 2016, 19:46
 */

#ifndef EMENUINGAME_H
#define EMENUINGAME_H

#include "Juego.h"

class EMenuInGame: public Escena {
public:
    
    void Handle();
    void Init();
    void Update();
    void Render();
    Juego* getContext();
    static EMenuInGame* Instance(Juego* context);
    ~EMenuInGame();
    
    
protected:
    EMenuInGame(Juego* context);
    EMenuInGame(const EMenuInGame &);
    EMenuInGame &operator = (const EMenuInGame &);

private:
    
    static EMenuInGame* pinstance;
    Juego* _context;
    
};

#endif /* EMENUINGAME_H */

