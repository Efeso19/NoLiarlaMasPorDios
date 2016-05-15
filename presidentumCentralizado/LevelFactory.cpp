/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LevelFactory.cpp
 * Author: chiri
 * 
 * Created on 26 de abril de 2016, 17:17
 */

#include "LevelFactory.h"


LevelFactory* LevelFactory::pinstance = 0;
LevelFactory* LevelFactory::Instance(){
    
    if(pinstance == 0) pinstance = new LevelFactory();

    return pinstance;
}

LevelFactory::LevelFactory() {
}

Mundo* LevelFactory::crearMundo(int nivel){
    
    /*
     * AQUI, CON EL SWITCH SE COMPROBARÁ QUE NIVEL HAY QUE CARGAR, Y SEGUN EL NÚMERO
     * SE LANZARÁ UN if(!->loadFromFile("resources/....nivel1CIUDADANOS.tmx"))
     * U OTRO SEGÚN SEA EL INT QUE SE LE PASA. 
     * DESPUÉS, CON ESE FILE, SE RECORRERÁ EL XML PARA CARGAR EL MUNDO.
     */  
    
    //switch(nivel)
       
        //case 1: 
        
       //default: statement
    
    
    //FINALMENTE SE CREARÁ UNA INSTANCIA DE Mundo Y SE DEVOLVERÁ CON return
    
    return 0;
    
}


LevelFactory::~LevelFactory() {
}

