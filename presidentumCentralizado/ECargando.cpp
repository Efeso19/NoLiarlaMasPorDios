/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ECargando.cpp
 * Author: chiri
 * 
 * Created on 5 de mayo de 2016, 17:48
 */
#include <stdio.h>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Juego.h"
#include "ECargando.h"
#include "EInGame.h"
#include "EMenu.h"

using namespace std;

ECargando* ECargando::pinstance = 0;
ECargando* ECargando::Instance(Juego* context){
    
    if(pinstance == 0) pinstance = new ECargando(context);
    
    return pinstance;
}

ECargando::ECargando(Juego* context){ //CONSTRUCTOR REAL
    
    _context = context; //En el momento en el que se crea el estado, se asigna su contexto.

}

void ECargando::Handle(){
    
    std::cout << "ECargando: "  << this << std::endl;
    _context->setState(this);   //Al hacer Handle, se activa este estado en el contexto.
    
    
}

void ECargando::Init(){
  
    

    // Texto
    font = new sf::Font;
    font->loadFromFile("fonts/alterebro-pixel-font.ttf");
    sf::String stringPoliticos(L"políticos");
    sf::String stringPodras(L"podrás");
    
    std::string lines = std::string("Preparando las cortes...");
    lines+="\nPreparando diputados... ";
    lines+="\nPreparando simpatizantes... ";
    lines+="\nPreparando votos... ";
    lines+="\nPreparando jefes... ";
    lines+="\nSi pactas con otros ";
    lines+=stringPoliticos;
    lines+="\n";
    lines+=stringPodras;
    lines+=" usarlos mientras juegas";
    
    
    bgCartel = new sf::RectangleShape;
    cartel = new sf::RectangleShape;
//    marcoCarga = new sf::RectangleShape;
//    progresoCarga = new sf::RectangleShape;
    tituloText = new sf::Text("CARGANDO...", *font, 30);
    cuerpoText = new sf::Text(lines, *font, 30);
    
    bgCartel->setFillColor(sf::Color(180,50,50,200));
    bgCartel->setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x, (float)Juego::Instance()->window->getSize().y));

    bgCartel->setOrigin((float)bgCartel->getSize().x/2, (float)bgCartel->getSize().y/2);
    bgCartel->setPosition((float)bgCartel->getSize().x/2, (float)bgCartel->getSize().y/2);
    
 
    cartel->setFillColor(sf::Color(255,255,255,200));
    cartel->setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x/1.4, (float)Juego::Instance()->window->getSize().y/1.4));
    cartel->setOrigin((float)cartel->getSize().x/2, (float)cartel->getSize().y/2);
    cartel->setPosition((float)bgCartel->getSize().x/2, (float)bgCartel->getSize().y/2);
    cartel->setOutlineColor(sf::Color::Black);
    cartel->setOutlineThickness(2);
    
    
 
    tituloText->setPosition(cartel->getOrigin().x+40,cartel->getOrigin().y-140);
    tituloText->setPosition((float)bgCartel->getSize().x/2-130,(float)bgCartel->getSize().y/2-230);
    tituloText->setCharacterSize(70);
    tituloText->setColor(sf::Color::Black);

    
    //cuerpoText.setPosition(cartel.getOrigin().x-100,cartel.getOrigin().y-70);
    cuerpoText->setPosition((float)bgCartel->getSize().x/2-160,(float)bgCartel->getSize().y/2-110);
   
    cuerpoText->setCharacterSize(50);
    cuerpoText->setColor(sf::Color::Black);
    
//    marcoCarga->setFillColor(sf::Color(255,255,255,255));
//    marcoCarga->setOutlineColor(sf::Color::Black);
//    marcoCarga->setOutlineThickness(3/);
//    marcoCarga->setSize(sf::Vector2f(400, 80));
//
//    marcoCarga->setOrigin(marcoCarga->getSize().x/2,marcoCarga->getSize().y/2);
//    marcoCarga->setPosition(_context->window->getSize().x/2, _context->window->getSize().y/2+100);
//    
//    
//    
//    
//    progresoCarga->setFillColor(sf::Color(60,250,60,200));
//
//    progresoCarga->setSize(sf::Vector2f(100, 80));
//
//    progresoCarga->setOrigin(progresoCarga->getSize().x/2,progresoCarga->getSize().y/2);
//    progresoCarga->setPosition(_context->window->getSize().x/2-150, _context->window->getSize().y/2+100);
//    
    entryPoint = true;
}

void ECargando::Update(){
    
     if(!initState){
        Init();
        initState = true;
    }
    
    Render();
    
    
    Mundo::Instance()->crearMundo(EMenu::Instance(_context)->partidoSeleccionado);
        
    if(Mundo::Instance()->mundoCreado)
        EInGame::Instance(_context)->eliminandoMundo = false;
        Mundo::Instance()->musica->play();
        EInGame::Instance(_context)->Handle();
     
//    if(progresoCarga->getPosition().x < _context->window->getSize().x/2+150 && entryPoint)
//        progresoCarga->move(5,0);
//    else if(progresoCarga->getPosition().x == _context->window->getSize().x/2-150)
//        entryPoint = true;
//    else{
//        progresoCarga->move(-5,0);
//        entryPoint = false;
//    }
    
    
    
}


void ECargando::Render(){
    
    //LO QUE QUIERO HACER AQUI ES QUE CUANDO ENTRE EN ESTE ESTADO, PINTE
    //EN LA PANTALLA UN CARTEL DE CARGANDO Y ETONCES CAMBIAR AL ESTADO EInGame
    _context->window->clear(sf::Color::Black);
    
    _context->window->draw(*bgCartel);
    _context->window->draw(*cartel);
    _context->window->draw(*tituloText);
    _context->window->draw(*cuerpoText);
    
//    _context->window->draw(*marcoCarga);
//    _context->window->draw(*progresoCarga);
    
    
    _context->window->display();
    
    
}


ECargando::~ECargando() {
    
    
    
}

