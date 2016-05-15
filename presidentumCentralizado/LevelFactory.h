/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LevelFactory.h
 * Author: chiri
 *
 * Created on 26 de abril de 2016, 17:17
 */

#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include "Mundo.h"

class LevelFactory {
public:
    
    static LevelFactory* Instance();
    LevelFactory();
    Mundo* crearMundo(int nivel);
   
    ~LevelFactory();
private:
    
    static LevelFactory* pinstance;

};

#endif /* LEVELFACTORY_H */

