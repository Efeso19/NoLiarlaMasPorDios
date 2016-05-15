/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EMenuInGame.cpp
 * Author: chiri
 * 
 * Created on 7 de abril de 2016, 19:46
 */

#include <stdio.h>
#include <iostream>

#include "EMenuInGame.h"
#include "Juego.h"
#include "Escena.h"

using namespace std;

EMenuInGame* EMenuInGame::pinstance = 0;
EMenuInGame* EMenuInGame::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new EMenuInGame(context);

    return pinstance;
}

EMenuInGame::EMenuInGame(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EMenuInGame::Handle(){
    
    std::cout << "EMenuInGame: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

void EMenuInGame::Init(){
    
   
    
}

void EMenuInGame::Update(){
    
    if(!initState){
        Init();
        initState = true;
    }
    
    //ACCIONES DE UPDATE
    
    Render();

}

void EMenuInGame::Render(){
    

}

Juego* EMenuInGame::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

EMenuInGame::~EMenuInGame(){
                            //Destruccion de la instancia 
    std::cout << "EMenuInGame ha sido eliminada. "  << std::endl;
    _context = 0;
    pinstance = 0;
    
}