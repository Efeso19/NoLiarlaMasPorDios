/* 
 * File:   Plataforma.cpp
 * Author: Aitor
 * 
 * Created on 19 de abril de 2016, 17:52
 */

#include "Plataforma.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

Plataforma::Plataforma(int x, int y, int numMapa, int t) {
    tipo=t; // 0 horizontal, 1 vertical, 2 rompible
    posx=x;
    posy=y;
    tiempo=0;
    recorrido=0;
    direccion=1; //1 derecha, 0 izquierda
    if(t==2){
        colorInicial= spritePlat.getColor();
        rota=false;
        romper=0;
    }
    
    if(numMapa==1 || numMapa==5 || numMapa==9){ //PP
        if(tipo==0){//horizontal
            std::cout<<"tipo------ "<<tipo<<std::endl;
            if (!texPlat.loadFromFile("resources/PP/PlataformaHorizontal.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaHorizontal.png";
              exit(0);
          }  
        }
        
        if(tipo==1){//vertical
            if (!texPlat.loadFromFile("resources/PP/PlataformaVerticalPP.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaVerticalPP.png";
              exit(0);
          }  
        }
        
        if(tipo==2){//rompible
            if (!texPlat.loadFromFile("resources/PP/PlataformaRompiblePP.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaRompiblePP.png";
              exit(0);
          }  
        }
    }
    
    if(numMapa==2 || numMapa==6 || numMapa==10){//PSOE
       if(tipo==0){//horizontal
            std::cout<<"tipo------ "<<tipo<<std::endl;
            if (!texPlat.loadFromFile("resources/PSOE/PlataformaHorizontalPSOE.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaHorizontal.png";
              exit(0);
          }  
        }
        
        if(tipo==1){//vertical
            if (!texPlat.loadFromFile("resources/PSOE/PlataformaVerticalPSOE.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaVerticalPP.png";
              exit(0);
          }  
        }
        
        if(tipo==2){//rompible
            if (!texPlat.loadFromFile("resources/PSOE/PlataformaRompiblePSOE.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaRompiblePP.png";
              exit(0);
          }  
        }
    }
    
    if(numMapa==3 || numMapa==7 || numMapa==11){//C'S
        if(tipo==0){//horizontal
            std::cout<<"tipo------ "<<tipo<<std::endl;
            if (!texPlat.loadFromFile("resources/CIUDADANOS/PlataformaHorizontalC'S.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaHorizontal.png";
              exit(0);
          }  
        }
        
        if(tipo==1){//vertical
            if (!texPlat.loadFromFile("resources/CIUDADANOS/PlataformaVerticalC'S.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaVerticalPP.png";
              exit(0);
          }  
        }
        
        if(tipo==2){//rompible
            if (!texPlat.loadFromFile("resources/CIUDADANOS/PlataformaRompibleC'S.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaRompiblePP.png";
              exit(0);
          }  
        }
    }
    
    if(numMapa==4 || numMapa==8 || numMapa==12){//PODEMOS
       if(tipo==0){//horizontal
            std::cout<<"tipo------ "<<tipo<<std::endl;
            if (!texPlat.loadFromFile("resources/PODEMOS/PlataformaHorizontalPodemos.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaHorizontal.png";
              exit(0);
          }  
        }
        
        if(tipo==1){//vertical
            if (!texPlat.loadFromFile("resources/PODEMOS/PlataformaVerticalPodemos.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaVerticalPP.png";
              exit(0);
          }  
        }
        
        if(tipo==2){//rompible
            if (!texPlat.loadFromFile("resources/PODEMOS/PlataformaRompiblePODEMOS.png"))
          {
              std::cerr << "Error cargando la imagen PlataformaRompiblePP.png";
              exit(0);
          }  
        }
    }
    
    
    
    spritePlat.setTexture(texPlat);
    spritePlat.setPosition(x, y);
    tiempo= tiempoRecorrido.getElapsedTime().asSeconds();
}

Plataforma::Plataforma(const Plataforma& orig) {
}

Plataforma::~Plataforma() {
}

void Plataforma::move(){
    if(tipo==0){ //horizontal
        tiempo= tiempoRecorrido.getElapsedTime().asSeconds();
        if(direccion==1){
            if(tiempo>0.035){
                spritePlat.move(2.5,0);
                recorrido+=2.5;
               // cout<<spritePlat.getPosition().x<<endl;
                // cout<<"Espacio recorrido: "<<recorrido<<endl;
                tiempoRecorrido.restart();
            }
        }

        if(direccion==0){
            if(tiempo>0.035){
                spritePlat.move(-2.5,0);
                recorrido+=2.5;
                //cout<<spritePlat.getPosition().x<<endl;
                // cout<<"Espacio recorrido: "<<recorrido<<endl;
                tiempoRecorrido.restart();
            }
        }

        if(recorrido>256){
            if(direccion==1){
                direccion=0;
                recorrido=0;
                //cout<<"Cambio a izquierda"<<endl;
            }else{
                direccion=1;
                recorrido=0;
                //cout<<"Cambio a derecha"<<endl;
            } 
        }
    }
    
    if(tipo==1){//vertical
        tiempo= tiempoRecorrido.getElapsedTime().asSeconds();
        if(direccion==1){
            if(tiempo>0.035){
                spritePlat.move(0,2.5);
                recorrido+=2.5;
               // cout<<spritePlat.getPosition().x<<endl;
                // cout<<"Espacio recorrido: "<<recorrido<<endl;
                tiempoRecorrido.restart();
            }
        }

        if(direccion==0){
            if(tiempo>0.035){
                spritePlat.move(0,-2.5);
                recorrido+=2.5;
                //cout<<spritePlat.getPosition().x<<endl;
                // cout<<"Espacio recorrido: "<<recorrido<<endl;
                tiempoRecorrido.restart();
            }
        }

        if(recorrido>256){
            if(direccion==1){
                direccion=0;
                recorrido=0;
            }else{
                direccion=1;
                recorrido=0;
            } 
        }
    }
}


void Plataforma::romperPlataforma(){
    tiempoRotura= tiempoRecorrido.getElapsedTime().asSeconds();
    if(rota==false){
        
        if(tiempoRotura>=0 && tiempoRotura<0.5){
            if(romper==1) spritePlat.setColor(sf::Color(255, 170, 170, 255));
            if(romper==2) spritePlat.setColor(sf::Color(255, 50, 50, 255));
            if(romper==3) spritePlat.setColor(sf::Color(255, 0, 0, 255));
        }
        
        if(tiempoRotura>=0.5){
             tiempoRecorrido.restart();            
             romper++;
        }
        
        if(romper>3){
            rota=true;
        }   
    }
}

void Plataforma::regeneracionPlataforma(){
    if(rota==true){
        tiempoRotura=tiempoRecorrido.getElapsedTime().asSeconds();
        if(tiempoRotura>3){
            rota=false;
            romper=0;
            spritePlat.setColor(colorInicial);
        }
    }
}