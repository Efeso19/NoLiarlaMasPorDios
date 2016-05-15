/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camara.h
 * Author: alfon
 *
 * Created on 17 de marzo de 2016, 22:14
 */

#ifndef CAMARA_H
#define CAMARA_H
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include "Jugador.h"
 #include <string> 

class Camara {
public:
    Camara();
    Camara(const Camara& orig);
    virtual ~Camara();
    
    void draw();
    void moveRight();
    void moveLeft();
    void sumaVotos(int votos);
     void actualizarVidas(int v, int pol, int seleccionJugador);
    void actualizarVidasPrincipales(int vp, int seleccionJugador);
    void actualizarVidasMiniaturas(int vm, int pol, int seleccionJugador);
    void actualizarVidasMiniaturas2(int vm, int pol, int seleccionJugador);
    void cartelFinal();
    void cartelGameOver();
    void setLastTime(int c);
    void mostrarLlave();
    void cartelPresidente();
    //void setHudVotosValue(int votoObtenido);
    int getPosx();
    sf::Sprite getHudVotos();
    sf::Text getHudVotosValue();
    sf::Sprite getContador();
    sf::Text getContadorValue();
    sf::Sprite getVidasPrincipales();
    sf::Sprite getSpriteVidaAlbert2();
    sf::Sprite getVidas();
    sf::Sprite getBarraVida();
    sf::Sprite getMiniatura1();
    sf::Sprite getMiniatura1vida();
    sf::Sprite getMiniatura2();
    sf::Sprite getMiniatura2vida();
  
//    sf::Clock getClock();
    void actualizarTiempo();
    void resetearCamara();
    int desplazamientoCamara;
    int posicionOrigenCamara;
    int lastTime;
    int countdown; 
    sf::Text hudVotosValue; //Numero de votos
    int tiempoInicio;
    int votosConseguidos;
private:
    
    int ancho;
    int alto;
    
   
    int kVel;
    //sf::Time time; //PRUEBA INTERPOLACION
    
    sf::View *camara;
    
    sf::Font font;  
    sf::Font fontpixelated;
    sf::Sprite hudVotos; //Fuente VOTOS:
    
    sf::Sprite background;
    
    sf::Clock clock; //Tiempo HUD
    //int countdown; //Cuenta atras HUD
    sf::Sprite contador; //Reloj
    sf::Text contadorValue; //Valor cuenta atras
    std::string convertTime;  //Para convertir de int a String el tiempo
    
    std::string convertVotos;
    
    int **matriz; //Para el spritesheet del HUD
    int posX;
    int linea;
    
    float aceleracion = 0.0; //Aceleracion del movimiento de la camara
    float increment = 0.2; //Incrementos de camara
    bool isMoving;  //Controla si se está moviendo el jugador (de momento no se usa)
    
    sf::Sprite vidas;
    sf::Sprite barraVida;
    sf::Sprite vidasPrincipales;
    sf::Sprite miniatura1;
    sf::Sprite miniatura1vida;
    sf::Sprite miniatura2;
    sf::Sprite miniatura2vida;

    sf::Texture texturaHUD;
  
};

#endif /* CAMARA_H */

