/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <SFML/Graphics.hpp>
#include "tinyxml.h"
#include "Camara.h"
#include <iostream>
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include "Mapa.h"
#include <math.h> 
#include "Jugador.h"

#define kVel 10

#include "Jugador.h"
#include "Juego.h"
#include <fstream>
#include <cstring>

static int alfonso(){
    
    sf::RenderWindow window(sf::VideoMode(1066, 600), "Presidentum!"); 
   
    sf::Texture texture;
    if(!texture.loadFromFile("resources/background.jpg")){
        std::cerr<<"error al cargar el background";
        exit(0);
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    std::cout<<"sprite cargado"<<std::endl;
    window.setVerticalSyncEnabled(true); //Para evitar cortes en los refrescos
    window.setFramerateLimit(60);	//Establecemos maximo real de procesamiento (aunque trabajamos con 60)
    Jugador* player = new Jugador(200, 380, 2, true);//le pasamos la posicion X e Y donde se colocará el sprite. 
                                                    //El tercer parametro es que personaje es, solo puede ser hasta el 4. 1.Pablo 2.Albert 3.Rajoy 4.Pedro
                                                    //El cuarto parametro es para saber si está activado el personaje en el array de personajes ya que solo un personaje se puede mostrar.
    //player->leerXML();//PREGUNTA    ¿es mejor que la matriz deonde se guardan los datos del psrite sheet sea global de la clase Juego o que cada jugador tenga su propia matriz aunque sea la misma?

    Mapa *mapa = new Mapa();
    mapa->leerMapa(1);
    std::cout<<"holaaaaaa"<<std::endl;
    Camara *camara=new Camara(window.getSize().x, window.getSize().y, kVel, *mapa);
    //le pasamos el alto y el ancho de la ventana
    //el siguiente parametro es la distancia que se mueve la ventana cada vez que se mueve el personaje
    //le pasamos el fondo para poder consultarlo
    //el mapa->fondo nos ayuda a saber hasta donde debemos mover la camara ya que es el ancho del mapa
    //el mapa->_tileWidth nos indica el ancho del tile
   
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            //player->handle(event, window);
        }
         //Juego::Instance()->window->clear(sf::Color::White);
        window.clear(sf::Color::White);
        mapa->dibujaA(window);
        //window.draw(sprite);
        player->draw(window);
        player->handle(event, window, mapa, camara);
        
        //std::cout<< player->getSprite().getPosition().x <<std::endl;
        //window.draw(player->getSprite());     
        //setteo la camara
        /*
         
             proyectiles[i]->dibuja(window);
            if(proyectiles[i]->destruir()){ //Si recorre mas de 450 de distancia...
                delete proyectiles[i]; //...se destruye el proyectil
                proyectiles.erase(proyectiles.begin()+i); //y se elimina la posicion del vector donde estaba
            }*/
        int i=0;
        std::cout<<player->proyectiles->size()<<std::endl;
        for(i=0; i<player->proyectiles->size();i++){
            player->proyectiles->at(i)->dibuja(window);
            std::cout<<"estoy dibujando"<<std::endl;
            if(player->proyectiles->at(i)->destruir()){
                delete player->proyectiles->at(i);
                player->proyectiles->erase(player->proyectiles->begin()+i);
            }
        }
        camara->draw(window);
        window.display();
        //Juego::Instance()->window->display();
        
    }
    
    return 0;
    
}
