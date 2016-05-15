/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundo.h
 * Author: chiri
 *
 * Created on 14 de abril de 2016, 18:00
 */

#ifndef MUNDO_H
#define MUNDO_H
#include "Mapa.h"
#include "Simpatizante.h"
#include "BossFinal.h"
#include "Enemigo.h"
#include "Proyectil.h"

class Mundo {
public:
    
    static Mundo* Instance();
    
    Mundo();
    
    bool crearMundo(int l);

    void Update();
    
    void Render();
    
    void eliminarMundo();
    
    void sumarValoresTotales();
    void actualizarVidas();
    
    ~Mundo();
    
    int nivel;
    
    bool mundoCreado = false;
    
    //RELOJES//////////////////////
    
 
    sf::Clock relojGolpe;
    sf::Clock clock;
    sf::Clock updateClock;
    sf::Time timeElapsed;

    float tiempo;
    
    //MUSICA//////////////////////
    
    sf::SoundBuffer* buffer;
    sf::Sound* musica;
    sf::SoundBuffer* bufferSobre;
    sf::SoundBuffer* bufferHurt;
    sf::Sound* soundSobre;
    sf::Sound* soundHurt;
    
  
    //ENEMGOS////////////////////
    
    BossFinal* jefefinal;
    
    std::vector<Enemigo*>* enemigosAdistancia;  //array de enemigos a distancia
    
    std::vector<Enemigo*>* enemigosCuerpo;  //array de enemigos cuerpo a cuerpo
    
    
    //Simpatizante** simpatizantes; //array de simpatizantes
    
    //Proyectil** proyectiles5; //array de proyectiles
    
    Mapa* mapa;
    
    //CAMARA
    
    Camara* camara; //Apuntador al objeto camara
    int camaraVel;  //desplzamiento de la camara
    sf::Vector2i* camRes; //Resolucion de la camara
    
    //VARIABLES DE PROGRESION DE JUEGO
    
    int lugaresVisitados[4]; //niveles a descartar

    
    int faseActual=0;
    
    bool mostrarKey;
    sf::Sprite *llave;
    bool pausa;
    
    /*****Varaibles para guardar informacion*****/
    int votosTotales =0;
    int enemigosTotalesEliminados=0;
    int numPactosRealizados=0;
    int numSimpatizantesLiberados=0;
    int tiempoEmpleado=0;
    
    int corazonesPrincipal = 3;
    int barrasPrincipal = 10;
    int barrasSecundario1 = 10;
    int barrasSecundario2 = 10;
   
    int secundario1 = 0;
    int secundario2 = 0;
    
    
private:


       static Mundo* pinstance;
    
};

#endif /* MUNDO_H */

