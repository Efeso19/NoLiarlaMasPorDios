/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: chiri
 * 
 * Created on 5 de abril de 2016, 17:56
 */
#include <iostream>
#include <vector>
#include <string>
#include <functional> 
#include "Juego.h"

#include "EIntro.h"
#include "EMenu.h"
#include "EMenuInGame.h"
#include "ECinematica.h"
#include "EInGame.h"
#include "ECargando.h"

using namespace std;

Juego* Juego::pinstance = 0;
Juego* Juego::Instance(){
    
    if(pinstance == 0) pinstance = new Juego();

    return pinstance;
}

Juego::Juego(){
    
    _state = 0;
    
}

void Juego::Init(){
    //VideoMode mode, const String& title, Uint32 style = Style::Default, const ContextSettings& settings = ContextSettings(
    window = new sf::RenderWindow(sf::VideoMode(this->windowWidth, this->windowHeight), "Ventana de juego");
    window->setFramerateLimit(60);
    sf::Clock reloj;
    
    std::cout << "Instancia de Juego: " << this  << std::endl;
//    std::cout << "Pulsa la tecla 1 para cambiar al estado ECinematica."  << std::endl;
//    std::cout << "Pulsa la tecla 2 para cambiar al estado EInGame."  << std::endl;
//    std::cout << "Pulsa la tecla 3 para cambiar al estado EMenu."  << std::endl;
//    std::cout << "Pulsa la tecla 4 para cambiar al estado EIntro."  << std::endl;
//    std::cout << "Pulsa la tecla 5 para cambiar al estado EMenuInGame."  << std::endl;
//    std::cout << "Pulsa la tecla 6 para cambiar al estado ECargando."  << std::endl;
//    std::cout << "Pulsa la tecla 7 para consultar el estado actual."  << std::endl;
//    std::cout << "Pulsa la tecla 8 para Destruir ECinematica"  << std::endl;
//    std::cout << "Pulsa la tecla 9 para Destruir EMenuInGame"  << std::endl;
    
    //ECinematica::Instance(this)->Handle();
    
    EMenu::Instance(this)->Handle();
    while(window->isOpen()){
       
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && reloj.getElapsedTime().asSeconds()>0.2){ECinematica::Instance(this)->Handle(); reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && reloj.getElapsedTime().asSeconds()>0.2){ EInGame::Instance(this)->Handle(); reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && reloj.getElapsedTime().asSeconds()>0.2){ EMenu::Instance(this)->Handle(); reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && reloj.getElapsedTime().asSeconds()>0.2){ EIntro::Instance(this)->Handle(); reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && reloj.getElapsedTime().asSeconds()>0.2){ EMenuInGame::Instance(this)->Handle();  reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && reloj.getElapsedTime().asSeconds()>0.2){ ECargando::Instance(this)->Handle();  reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && reloj.getElapsedTime().asSeconds()>0.2){ std::cout << "ESTADO ACTUAL: "  << this->currentState() << std::endl; reloj.restart(); }
//        
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && reloj.getElapsedTime().asSeconds()>0.2){delete ECinematica::Instance(this);reloj.restart(); }
//        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && reloj.getElapsedTime().asSeconds()>0.2){delete EInGame::Instance(this);reloj.restart(); }


        
        //Bucle de obtención de eventos
        while (window->pollEvent(event)){
            
            switch(event.type){     
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window->close();
                    break;
                    

            }
        }
        
        if(_state!=0){ //Con el valor 0, el juego dejará de pintar
           
            Update();
        }
        
    }
    
}

void Juego::Update(){

    _state->Update();
    
}

Escena* Juego::currentState(){
    
    return _state;
   
}

void Juego::setState(Escena* state){
    
    _state = state;
        
}

Juego::~Juego() {
    
   delete EInGame::Instance(this);
   std::cout << "Juego ha sido eliminado."   << std::endl;
    
    
}
