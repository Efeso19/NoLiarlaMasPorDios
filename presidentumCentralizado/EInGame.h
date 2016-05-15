/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EInGame.h
 * Author: chiri
 *
 * Created on 7 de abril de 2016, 17:57
 */

#ifndef EINGAME_H
#define EINGAME_H

#include "Juego.h"
#include "Mundo.h"

class EInGame: public Escena {
public:

    static EInGame* Instance(Juego* context);
    void Handle();
    void Init();
    void Update();
    void Render();
    int** getRecorte();
    int** generarRecorte();
    Juego* getContext();
    void eliminarMundo();
    ~EInGame();
    
    bool eliminandoMundo; //PARA NO EJEGUTAR EL UPDATE/RENDER DE MUNDO MIENTRAS SE ELIMINA
    
protected:
    EInGame(Juego* context);
    EInGame(const EInGame &);
    EInGame &operator = (const EInGame &);

private:
    
    int** matrizRecorte;
    static EInGame* pinstance;
    Juego* _context;
    
};

#endif /* EINGAME_H */

