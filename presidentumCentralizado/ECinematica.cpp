/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECinematica.cpp
 * Author: chiri
 * 
 * Created on 7 de abril de 2016, 19:41
 */

#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Juego.h"
#include "EIntro.h"
#include "EMenu.h"
#include "EMenuInGame.h"
#include "ECinematica.h"
#include "EInGame.h"


using namespace std;

ECinematica* ECinematica::pinstance = 0;
ECinematica* ECinematica::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new ECinematica(context);
    
    return pinstance;
}

ECinematica::ECinematica(Juego* context){ //CONSTRUCTOR REAL
    
    initState = false;
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.

}

void ECinematica::Handle(){
    
    std::cout << "ECinematica: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
}

void ECinematica::Init(){
    
   
    rectangulo.setSize(sf::Vector2f(300, 200));
    rectangulo.setOutlineColor(sf::Color::Red);
    rectangulo.setFillColor(sf::Color::Red);
    rectangulo.setOutlineThickness(2);
    rectangulo.setOrigin(rectangulo.getSize().x/2,rectangulo.getSize().y/2);
    rectangulo.setPosition(_context->window->getSize().x/2, _context->window->getSize().y/2);
    
}

void ECinematica::Update(){
    
    if(!initState){
        Init();
        initState = true;
    }
    
    rectangulo.rotate(0.1);
    
    Render();
    
}


void ECinematica::Render(){
   
    _context->window->clear(sf::Color::White); //COLOR DE FONDO BLANCO    
    _context->window->draw(rectangulo);
    _context->window->display();
    
}

Juego* ECinematica::getContext(){
    
    return _context;    //Para recuperar el contexto
    
}

ECinematica::~ECinematica(){
                            //Destruccion de la instancia 
    std::cout << "ECinematica ha sido eliminada. "  << std::endl;
    _context = 0;
    pinstance = 0;
    
    
    
}