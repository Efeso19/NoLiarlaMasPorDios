/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EIntro.cpp
 * Author: chiri
 * 
 * Created on 5 de abril de 2016, 19:47
 */

#include <stdio.h>
#include <iostream>

#include "EIntro.h"
#include "EMenu.h"


using namespace std;

EIntro* EIntro::pinstance = 0;
EIntro* EIntro::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new EIntro(context);

    return pinstance;
}

EIntro::EIntro(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.
  
}

void EIntro::Handle(){
    
    std::cout << "EIntro: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

void EIntro::Init(){
    
   
    
}

void EIntro::Update(){
    
    if(!initState){
        Init();
        initState = true;
    }
    
    //ACCIONES DE UPDATE
    
    Render();

}

void EIntro::Render(){
    

}

Juego* EIntro::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

EIntro::~EIntro(){
                            //Destruccion de la instancia 
    std::cout << "EIntro ha sido eliminada. "  << std::endl;
    _context = 0;
    pinstance = 0;
    
}