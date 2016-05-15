/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Camara.cpp
 * Author: alfon
 * 
 * Created on 17 de marzo de 2016, 22:14
 */

#include "Camara.h"
#include "Mapa.h"
#include <iostream>
#include "Jugador.h"
#include "Mundo.h"
#include "Juego.h"
#include <SFML/System.hpp>

 #include <sstream>
 #include <vector>
 #include <string> 
 #include <fstream>
 #include <cstring>
using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
 const int MAX_TOKENS_PER_LINE = 20;
 const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")
 
 template <typename T>
std::string to_string(T countdown)
{
	std::ostringstream convert ;
	convert << countdown ;
	return convert.str() ;
}

Camara::Camara(){
    
    
    Mundo::Instance()->camRes->x = (int)Juego::Instance()->window->getSize().x;
    Mundo::Instance()->camRes->y = (int)Juego::Instance()->window->getSize().y;
    
    ancho=Mundo::Instance()->camRes->x;
    alto=Mundo::Instance()->camRes->y;
    camara = new sf::View(sf::FloatRect(0,0, ancho, alto));
    desplazamientoCamara=0;
    posicionOrigenCamara=camara->getCenter().x;
    kVel=Mundo::Instance()->camaraVel;
    //mapa= new Mapa();
    
    ///Mundo::Instance()->mapa->_tileWidth=map._tileWidth;
    //Mundo::Instance()->mapa->_width=map._width;
    //Mundo::Instance()->mapa->fondo=map.fondo;
    background=Mundo::Instance()->mapa->fondo;
    
    /********MOVIMIENTO*********/  
    bool isMoving = false;
    float aceleracion = 0.0;
    
    /********HUD*********/  
     
      /*MATRIZ BIDIMENSIONAL para almacenar los 4 parametros de cada sprite*/
     
     matriz= new int*[99];
     for(int i = 0; i < 99; i++){
         matriz[i] = new int[4];
     }
 
     posX=0;
     linea=1;
     lastTime = 0;
     
    /****LECTURA DEL XML PARA EL SPRITE!!****/
     
 
   ifstream fin;
   fin.open("resources/HUDspritesheet.xml"); // abrir el xml que se va a leer
   
   
   // comenzamos a leer cada una de las lineas
   while (!fin.eof())
   {
     // esto es para controlar el tamanyo maximo de cada linea
     char buf[MAX_CHARS_PER_LINE];
     fin.getline(buf, MAX_CHARS_PER_LINE);
     int n = 0;
     
     // cada linea va almacenada en un vector
     const char* token[MAX_TOKENS_PER_LINE] = {};
     
     // parseamos las lineas, separando cada elemento de la linea por comillas (")
     token[0] = strtok(buf, DELIMITER);
     
     if (token[0])
     {
       for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
       {
         token[n] = strtok(0, DELIMITER);
         
         //SOLO nos interesa a partir de la linea 22 del XML
         if(linea>2){
             //Vamos almacenando en la matriz segun el parametro que nos interesa en el orden correcto
            if(n==3){ //El tercer elemento corresponde a x
                matriz[posX][0]=atoi(token[n]);
             }
            
            if(n==5){ //El quinto elemento corresponde a y
                matriz[posX][1]=atoi(token[n]);
            }
            
            if(n==7){ //El septimo elemento corresponde a w
                matriz[posX][2]=atoi(token[n]);
            }
            
            if(n==9){ //El noveno elemento corresponde a h
                matriz[posX][3]=atoi(token[n]);
                posX++;
            }
         }
 
         if (!token[n]) break; // si no hay mas, se termina el bucle
       }
     }
 
     // imprime los 4 parametros(x,y,w,h) obtenidos de cada linea en la consola
 //    for (int i = 0; i < n; i++){// n = #of tokens
 //        if(linea>22){
 //            if(i==3 || i==5 || i==7 || i==9){
 //                cout << "Token[" << i << "] = " << token[i] << endl;
 //                
 //            }  
 //        }    
 //    } 
    
     linea++;
   }
   
   //Esto es para imprimir la matriz obtenida en consola
     if(linea>22){
         for(int i=0; i<11;i++){
             for (int j=0;j<4;j++){
//                 cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
             }
//             cout << endl;
         }
     }
    
    

    
    font.loadFromFile("fonts/MyriadPro Regular.ttf");

    fontpixelated.loadFromFile("fonts/MyriadPro Regular.ttf");

    votosConseguidos=0;
    convertVotos=to_string(votosConseguidos);
    hudVotosValue.setString(convertVotos);
    hudVotosValue.setFont(fontpixelated);
    hudVotosValue.setCharacterSize(30);
    hudVotosValue.setColor(sf::Color::White);



    //temporizador
    countdown = 70;
    if(Mundo::Instance()->faseActual > 1){
        countdown += Mundo::Instance()->incrementoTiempo;
    }
    
    tiempoInicio = countdown;
    convertTime= to_string(countdown);
    

    contadorValue.setFont(font);
    contadorValue.setString(convertTime);
    contadorValue.setPosition(533,30);
    contadorValue.setCharacterSize(20);
    contadorValue.setColor(sf::Color::Black);
     
     
    //Cargo la imagen donde reside la textura del sprite del HUD
    if (!texturaHUD.loadFromFile("resources/HUDspritesheet.png"))
    {
        std::cerr << "Error cargando la imagen caras.png";
        exit(0);
    }
     
    vidas.setTexture(texturaHUD);
    contador.setTexture(texturaHUD);
    hudVotos.setTexture(texturaHUD);
    vidasPrincipales.setTexture(texturaHUD);
    barraVida.setTexture(texturaHUD);
    miniatura1.setTexture(texturaHUD);
    miniatura1vida.setTexture(texturaHUD);
    miniatura2.setTexture(texturaHUD);
    miniatura2vida.setTexture(texturaHUD);

    

    //Cojo el sprite que me interesa por defecto del sheet
    hudVotos.setTextureRect(sf::IntRect(matriz[16][0], matriz[16][1], matriz[16][2], matriz[16][3]));
    contador.setTextureRect(sf::IntRect(matriz[15][0], matriz[15][1], matriz[15][2], matriz[15][3]));
    vidasPrincipales.setTextureRect(sf::IntRect(matriz[14][0], matriz[14][1], matriz[14][2], matriz[14][3]));
    miniatura1.setTextureRect(sf::IntRect(matriz[33][0], matriz[33][1], matriz[33][2], matriz[33][3]));
    miniatura1.setScale(0.5,0.5);
    miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
    miniatura1vida.setScale(0.5,0.5);
    miniatura2.setTextureRect(sf::IntRect(matriz[32][0], matriz[32][1], matriz[32][2], matriz[32][3]));
    miniatura2.setScale(0.5,0.5);
    miniatura2vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
    miniatura2vida.setScale(0.5,0.5);
    //Los posiciono
    hudVotosValue.setPosition(130,30);
    hudVotos.setPosition(65,15);
    
    contador.setPosition(490,15);
    contadorValue.setPosition(505,30);
    
    vidas.setPosition(700, -20);
    barraVida.setPosition(787,74);
    vidasPrincipales.setPosition(785, 25);
    miniatura1.setPosition(180,20);
    miniatura1vida.setPosition(204,25);
    miniatura2.setPosition(270,20);
    miniatura2vida.setPosition(294,25);
    /********HUD*********/

}

Camara::Camara(const Camara& orig) {
}

Camara::~Camara() {
}

void Camara::draw(){
    
    //window.draw(hudVotosValue); //VALOR NUMERICO DE LOS VOTOS
    //window.draw(hudVotos);      //CARTEL DE VOTOS
    
    moveRight();
    moveLeft();
    
    //TODO LO QUE ESTÁ COMENTADO, LO DEJO PARA SEGUIR MAS ADELANTE CON LA CAMARA ACELERADA
    
//    if(aceleracion > 0.01){
//      
//           aceleracion-=increment/kVel;
//
//    }
//    
//     if(aceleracion < -0.01){
//      
//           aceleracion+=increment/kVel;
//  
//    }
      
    camara->move(aceleracion,0);

   
    Juego::Instance()->window->setView(*camara);
    
    
    //std::cout<<"desplazamientoCamara: "<<desplazamientoCamara<<" kVel: "<< kVel<<" Aceleracion: "<<aceleracion<<" Jugador activo: "<<player->isMoving()<<std::endl;
    
}

void Camara::moveRight(){
    
    if(desplazamientoCamara==0){
        //comprobamos que la posicion del personaje sea mayor que la camara y que el centro de la camara sea menor del fondo
        if(Jugador::Instance()->getSprite().getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(mapa->_tileWidth*mapa->_width*0.79)){
//            std::cout<<(Mundo::Instance()->mapa->_tileWidth*Mundo::Instance()->mapa->_width*0.79)<<std::endl;
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            //camara->move(kVel,0);
  

//           std::cout<<"posicionhud "<<hudVotos.getPosition().x;
            /*PRUEBA INTERPOLACIÓN*/
            //camara->move(1*kVel*time.asSeconds(),0);
            /*PRUEBA INTERPOLACIÓN*/
            desplazamientoCamara+=kVel;
        }
        /*if(personaje.getPosition().x >= camara->getSize().x*0.6 && camara->getCenter().x <=(background.getLocalBounds().width*0.79)){
            //con background.getLocalBounds().width*0.79 calculo la parte derecha del mapa para fijar la camara
            camara->move(kVel,0);
            desplazamientoCamara=desplazamientoCamara+kVel; 
        }*/

    }else{
        //con esto averiguamos el margen derecho para saber cuando parar la camara al llegar al final del mapa
        int margen= background.getLocalBounds().width-(background.getLocalBounds().width*0.83);
        if(Jugador::Instance()->getSprite().getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(Jugador::Instance()->getSprite().getPosition().x+margen) &&
            (Jugador::Instance()->getSprite().getPosition().x+margen)<(Mundo::Instance()->mapa->_tileWidth*Mundo::Instance()->mapa->_width)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(background.getLocalBounds().width*0.79)){
        //if(personaje.getPosition().x>= camara->getSize().x*0.6 + desplazamientoCamara && camara->getCenter().x<=(mapa->_tileWidth*mapa->_width*0.79)){
            //if(personaje->getSprite().getPosition().x<=((mapa->_tileWidth*mapa->_width)-2164)){
                camara->move(kVel,0);
                
                hudVotos.move(kVel,0);
                hudVotosValue.move(kVel,0);
                contador.move(kVel, 0);
                contadorValue.move(kVel, 0);
                vidas.move(kVel, 0);
                vidasPrincipales.move(kVel, 0);
                barraVida.move(kVel, 0);
                miniatura1.move(kVel,0);
                miniatura1vida.move(kVel,0);
                miniatura2.move(kVel,0);
                miniatura2vida.move(kVel,0);

//            if(aceleracion<kVel)
//                if(aceleracion>kVel)
//                    aceleracion = kVel;
//                else
//                    aceleracion+=increment;
                
                
                desplazamientoCamara+=kVel;
            //}
            
            

           
            /*PRUEBA INTERPOLACIÓN*/
           // camara->move(1*kVel*time.asSeconds(),0);
            /*PRUEBA INTERPOLACIÓN*/
            //desplazamientoCamara=desplazamientoCamara+kVel;  

        }
    } 
}

void Camara::moveLeft(){
    
    if(desplazamientoCamara!=0){
        if(Jugador::Instance()->getSprite().getPosition().x<= camara->getSize().x*0.4 + desplazamientoCamara && camara->getCenter().x!=posicionOrigenCamara){
            camara->move(-kVel,0);
            
            hudVotos.move(-kVel,0);
            hudVotosValue.move(-kVel,0);
            contador.move(-kVel, 0);
            contadorValue.move(-kVel, 0);
            vidas.move(-kVel, 0);
            vidasPrincipales.move(-kVel, 0);
            barraVida.move(-kVel, 0);
            miniatura1.move(-kVel,0);
            miniatura1vida.move(-kVel,0);
            miniatura2.move(-kVel,0);
            miniatura2vida.move(-kVel,0);

//            if(aceleracion > -kVel)
//                if(aceleracion < -kVel)
//                    aceleracion = -kVel;
//                else
//                    aceleracion-=increment;
            
           
            /*PRUEBA INTERPOLACIÓN*/
            //camara->move(-1*kVel*time.asSeconds(),0);
            /*PRUEBA INTERPOLACIÓN*/
            desplazamientoCamara-=kVel;
        }
    }
    
}


int Camara::getPosx(){
    return camara->getCenter().x;
}

sf::Sprite Camara::getHudVotos(){
    return hudVotos;
}

sf::Text Camara::getHudVotosValue(){
    return hudVotosValue;
}

//void Camara::setHudVotosValue(int sumaVotos){
//     votosConseguidos=votosConseguidos+sumaVotos;
//     convertVotos=to_string(votosConseguidos);
//     hudVotosValue.setString(convertVotos);
//}

sf::Sprite Camara::getContador(){
    return contador;
}

sf::Text Camara::getContadorValue(){
    return contadorValue;
}

void Camara::actualizarTiempo(){
    int timer = clock.getElapsedTime().asSeconds();
    if(Jugador::Instance()->estadoDelPacto == 0){           
        if (timer > 0 && countdown !=0){
    //        std::cout<<"tiempo!!! "<<countdown<<std::endl;
            countdown--;
            contadorValue.setString(to_string(countdown));
            clock.restart();
        }
    }
}

void Camara::sumaVotos(int votos){
     votosConseguidos=votosConseguidos+votos;
     convertVotos=to_string(votosConseguidos);
     hudVotosValue.setString(convertVotos);
}

sf::Sprite Camara::getVidasPrincipales(){
    return vidasPrincipales;
}


sf::Sprite Camara::getVidas(){
    return vidas;
}

sf::Sprite Camara::getBarraVida(){
    return barraVida;
}

sf::Sprite Camara::getMiniatura1(){
    return miniatura1;
}

sf::Sprite Camara::getMiniatura1vida(){
    return miniatura1vida;
}

sf::Sprite Camara::getMiniatura2(){
    return miniatura2;
}

sf::Sprite Camara::getMiniatura2vida(){
    return miniatura2vida;
}

void Camara::actualizarVidas(int v, int pol, int seleccionJugador){
    if(seleccionJugador==1){
    
        if(pol==1){ //vida de pablo
            vidas.setTextureRect(sf::IntRect(matriz[19][0], matriz[19][1], matriz[19][2], matriz[19][3]));
            if(v==10) barraVida.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        if(v==9) barraVida.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        if(v==8) barraVida.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
        if(v==7) barraVida.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
        if(v==6) barraVida.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
        if(v==5) barraVida.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
        if(v==4) barraVida.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        if(v==3) barraVida.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
        if(v==2) barraVida.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
        if(v==1) barraVida.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        if(v==0) barraVida.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
        }
        if(pol==2){ //vida de albert
           vidas.setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
           if(v==10) barraVida.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        if(v==9) barraVida.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        if(v==8) barraVida.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
        if(v==7) barraVida.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
        if(v==6) barraVida.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
        if(v==5) barraVida.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
        if(v==4) barraVida.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        if(v==3) barraVida.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
        if(v==2) barraVida.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
        if(v==1) barraVida.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        if(v==0) barraVida.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
        }
        if(pol==3){ //vida de mariano
          vidas.setTextureRect(sf::IntRect(matriz[18][0], matriz[18][1], matriz[18][2], matriz[18][3]));
          if(v==10) barraVida.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        if(v==9) barraVida.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        if(v==8) barraVida.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
        if(v==7) barraVida.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
        if(v==6) barraVida.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
        if(v==5) barraVida.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
        if(v==4) barraVida.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        if(v==3) barraVida.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
        if(v==2) barraVida.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
        if(v==1) barraVida.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        if(v==0) barraVida.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
        }
        if(pol==4){ //vida de pedro
            vidas.setTextureRect(sf::IntRect(matriz[20][0], matriz[20][1], matriz[20][2], matriz[20][3]));
            if(v==10) barraVida.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        if(v==9) barraVida.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        if(v==8) barraVida.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
        if(v==7) barraVida.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
        if(v==6) barraVida.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
        if(v==5) barraVida.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
        if(v==4) barraVida.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        if(v==3) barraVida.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
        if(v==2) barraVida.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
        if(v==1) barraVida.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        if(v==0) barraVida.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
        }

        /*if(v==10) barraVida.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        if(v==9) barraVida.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        if(v==8) barraVida.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
        if(v==7) barraVida.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
        if(v==6) barraVida.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
        if(v==5) barraVida.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
        if(v==4) barraVida.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        if(v==3) barraVida.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
        if(v==2) barraVida.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
        if(v==1) barraVida.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
        if(v==0) barraVida.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
*/
    
        
    }
}

void Camara::actualizarVidasPrincipales(int vp, int seleccionJugador){
    Jugador *ju;
    //if(ju->seleccionJugador==1){
    if(seleccionJugador==1){    
    
        if(vp==3){
            vidasPrincipales.setTextureRect(sf::IntRect(matriz[14][0], matriz[14][1], matriz[14][2], matriz[14][3]));
        }
        if(vp==2){
            vidasPrincipales.setTextureRect(sf::IntRect(matriz[13][0], matriz[13][1], matriz[13][2], matriz[13][3]));
        }
        if(vp==1){
            vidasPrincipales.setTextureRect(sf::IntRect(matriz[12][0], matriz[12][1], matriz[12][2], matriz[12][3]));
        }
        if(vp==0){
            vidasPrincipales.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
        }
    }
    //}
    
}

void Camara::actualizarVidasMiniaturas(int vm, int pol, int seleccionJugador){
    if(seleccionJugador==2){
        if(pol==1){
            miniatura1.setTextureRect(sf::IntRect(matriz[35][0], matriz[35][1], matriz[35][2], matriz[35][3]));
            if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));
        }

        if(pol==2){
            miniatura2.setTextureRect(sf::IntRect(matriz[32][0], matriz[32][1], matriz[32][2], matriz[32][3]));
            if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));
        }

        if(pol==3){
            miniatura2.setTextureRect(sf::IntRect(matriz[34][0], matriz[34][1], matriz[34][2], matriz[34][3]));
            if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));
        }

        if(pol==4){
            miniatura2.setTextureRect(sf::IntRect(matriz[33][0], matriz[33][1], matriz[33][2], matriz[33][3]));
            if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));
        }
    }
    
    
    else if(seleccionJugador==3){
        
        if(vm==10){ 
            
                miniatura2vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura2vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) {
                miniatura2vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3])); 
            }
            if(vm==7) miniatura2vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura2vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura2vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura2vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura2vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura2vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura2vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura2vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));
        
        
        if(pol==1){
            miniatura2.setTextureRect(sf::IntRect(matriz[35][0], matriz[35][1], matriz[35][2], matriz[35][3]));
            
        }

        if(pol==2){
            miniatura2.setTextureRect(sf::IntRect(matriz[32][0], matriz[32][1], matriz[32][2], matriz[32][3]));
           
        }

        if(pol==3){
            miniatura2.setTextureRect(sf::IntRect(matriz[34][0], matriz[34][1], matriz[34][2], matriz[34][3]));
           
        }

        if(pol==4){
            miniatura2.setTextureRect(sf::IntRect(matriz[33][0], matriz[33][1], matriz[33][2], matriz[33][3]));
            
        }
    }
    
    
}

void Camara::actualizarVidasMiniaturas2(int vm, int pol, int seleccionJugador){
    if(seleccionJugador==3){
        
        if(vm==10){ 
            
                miniatura2vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura2vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) {
                miniatura2vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3])); 
            }
            if(vm==7) miniatura2vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura2vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura2vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura2vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura2vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura2vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura2vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura2vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));
        
        
        if(pol==1){
            miniatura2.setTextureRect(sf::IntRect(matriz[35][0], matriz[35][1], matriz[35][2], matriz[35][3]));
            /*if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));*/
        }

        if(pol==2){
            miniatura2.setTextureRect(sf::IntRect(matriz[32][0], matriz[32][1], matriz[32][2], matriz[32][3]));
            /*if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));*/
        }

        if(pol==3){
            miniatura2.setTextureRect(sf::IntRect(matriz[34][0], matriz[34][1], matriz[34][2], matriz[34][3]));
            /*if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));*/
        }

        if(pol==4){
            miniatura2.setTextureRect(sf::IntRect(matriz[33][0], matriz[33][1], matriz[33][2], matriz[33][3]));
            /*if(vm==10){ 
                miniatura1vida.setTextureRect(sf::IntRect(matriz[28][0], matriz[28][1], matriz[28][2], matriz[28][3]));
            }
            if(vm==9) miniatura1vida.setTextureRect(sf::IntRect(matriz[21][0], matriz[21][1], matriz[21][2], matriz[21][3]));
            if(vm==8) miniatura1vida.setTextureRect(sf::IntRect(matriz[31][0], matriz[31][1], matriz[31][2], matriz[31][3]));
            if(vm==7) miniatura1vida.setTextureRect(sf::IntRect(matriz[29][0], matriz[29][1], matriz[29][2], matriz[29][3]));
            if(vm==6) miniatura1vida.setTextureRect(sf::IntRect(matriz[23][0], matriz[23][1], matriz[23][2], matriz[23][3]));
            if(vm==5) miniatura1vida.setTextureRect(sf::IntRect(matriz[22][0], matriz[22][1], matriz[22][2], matriz[22][3]));
            if(vm==4) miniatura1vida.setTextureRect(sf::IntRect(matriz[24][0], matriz[24][1], matriz[24][2], matriz[24][3]));
            if(vm==3) miniatura1vida.setTextureRect(sf::IntRect(matriz[27][0], matriz[27][1], matriz[27][2], matriz[27][3]));
            if(vm==2) miniatura1vida.setTextureRect(sf::IntRect(matriz[25][0], matriz[25][1], matriz[25][2], matriz[25][3]));
            if(vm==1) miniatura1vida.setTextureRect(sf::IntRect(matriz[26][0], matriz[26][1], matriz[26][2], matriz[26][3]));
            if(vm==0) miniatura1vida.setTextureRect(sf::IntRect(matriz[30][0], matriz[30][1], matriz[30][2], matriz[30][3]));*/
        }
    }
    
}

void Camara::resetearCamara(){
    desplazamientoCamara=0;
    camara->setCenter(533, 300);
    contador.setPosition(490,15);
    contadorValue.setPosition(505,30);

    vidas.setPosition(700, -20);
    barraVida.setPosition(787,74);
    vidasPrincipales.setPosition(785, 25);
    miniatura1.setPosition(180,20);
    miniatura1vida.setPosition(204,25);
    miniatura2.setPosition(270,20);
    miniatura2vida.setPosition(294,25);
    hudVotosValue.setPosition(130,30);
    hudVotos.setPosition(65,15);
}

void Camara::cartelFinal(){
    if(lastTime==0)
        setLastTime(countdown);
    // Texto
    sf::Font font;  
    font.loadFromFile("fonts/alterebro-pixel-font.ttf");
  
    sf::RectangleShape bgCartel;
    bgCartel.setFillColor(sf::Color(180,255,180,200));
    bgCartel.setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x, (float)Juego::Instance()->window->getSize().y));
    bgCartel.setOrigin((float)bgCartel.getSize().x/2, (float)bgCartel.getSize().y/2);
    bgCartel.setPosition(camara->getCenter().x,camara->getCenter().y);
    
    sf::RectangleShape cartel;
    cartel.setFillColor(sf::Color(255,255,255,255));
    cartel.setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x/1.4, (float)Juego::Instance()->window->getSize().y/1.4));
    cartel.setOrigin((float)cartel.getSize().x/2, (float)cartel.getSize().y/2);
    cartel.setPosition(camara->getCenter().x,camara->getCenter().y);
    cartel.setOutlineColor(sf::Color::Black);
    cartel.setOutlineThickness(2);
    
    sf::Text tituloText("-ENHORABUENA-", font, 30);

    //tituloText.setPosition(cartel.getOrigin().x+40,cartel.getOrigin().y-140);
    tituloText.setPosition(camara->getCenter().x-130,camara->getCenter().y-230);
    tituloText.setCharacterSize(70);
    tituloText.setColor(sf::Color::Black);
   
    std::string lines = std::string("Has superado el nivel");
    lines+="\n\nVOTOS CONSEGUIDOS: ";
    lines+=to_string(votosConseguidos);
    lines+="\nPACTO REALIZADO: ";
    if(Jugador::Instance()->estadoDelPacto == 2){
        lines+=to_string("SI");
    }
    if(Jugador::Instance()->estadoDelPacto == 3){
        lines+=to_string("NO");
    }
    lines+="\nENEMIGOS DERROTADOS: ";
    lines+=to_string(Jugador::Instance()->enemigosEliminados);
    lines+="\nSIMPATIZANTE LIBERADO: ";
    if(Jugador::Instance()->carcelAbierta){
        lines+=to_string("SI");
    }else{
        lines+=to_string("NO");
    }
    lines+="\nTIEMPO: ";
    
    lines+=to_string(lastTime);
    lines+="\nPresiona la 'X' para continuar";

    sf::Text cuerpoText(lines, font, 30);
    //cuerpoText.setPosition(cartel.getOrigin().x-100,cartel.getOrigin().y-70);
    cuerpoText.setPosition(camara->getCenter().x-160,camara->getCenter().y-160);
   
    cuerpoText.setCharacterSize(50);
    cuerpoText.setColor(sf::Color::Black);
    
    Juego::Instance()->window->draw(bgCartel);
    Juego::Instance()->window->draw(cartel);
    Juego::Instance()->window->draw(tituloText);
    Juego::Instance()->window->draw(cuerpoText);
    
    if(Mundo::Instance()->faseActual == 3){
        cartelPresidente();
    }
    
}

void Camara::cartelGameOver(){
    if(lastTime == 0)
        setLastTime(countdown);
    // Texto
    sf::Font font;  
    font.loadFromFile("fonts/alterebro-pixel-font.ttf");
  
    sf::RectangleShape bgCartel;
    bgCartel.setFillColor(sf::Color(255,180,180,200));
    bgCartel.setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x, (float)Juego::Instance()->window->getSize().y));
    bgCartel.setOrigin((float)bgCartel.getSize().x/2, (float)bgCartel.getSize().y/2);
    bgCartel.setPosition(camara->getCenter().x,camara->getCenter().y);
    
    sf::RectangleShape cartel;
    cartel.setFillColor(sf::Color(255,255,255,255));
    cartel.setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x/1.4, (float)Juego::Instance()->window->getSize().y/1.4));
    cartel.setOrigin((float)cartel.getSize().x/2, (float)cartel.getSize().y/2);
    cartel.setPosition(camara->getCenter().x,camara->getCenter().y);
    cartel.setOutlineColor(sf::Color::Black);
    cartel.setOutlineThickness(2);
    
    sf::Text tituloText("-GAME OVER-", font, 30);
    //tituloText.setPosition(cartel.getOrigin().x+40,cartel.getOrigin().y-140);
    tituloText.setPosition(camara->getCenter().x-80,camara->getCenter().y-230);
    tituloText.setCharacterSize(70);
    tituloText.setColor(sf::Color::Black);
   
    std::string lines = std::string("No has conseguido llegar a ser presidente");
    lines+="\n\nVOTOS CONSEGUIDOS: ";
    lines+=to_string(votosConseguidos);
    lines+="\nPACTO REALIZADO: ";
    lines+=to_string("NO");
    lines+="\nENEMIGOS DERROTADOS: ";
    lines+=to_string(Jugador::Instance()->enemigosEliminados);
    lines+="\nSIMPATIZANTE LIBERADO: ";
    if(Jugador::Instance()->carcelAbierta){
        lines+=to_string("SI");
    }else{
        lines+=to_string("NO");
    }
    lines+="\n\nTIEMPO: ";
    lines+=to_string(lastTime);

    sf::Text cuerpoText(lines, font, 30);
    //cuerpoText.setPosition(cartel.getOrigin().x-100,cartel.getOrigin().y-70);
    cuerpoText.setPosition(camara->getCenter().x-240,camara->getCenter().y-160);
   
    cuerpoText.setCharacterSize(50);
    cuerpoText.setColor(sf::Color::Black);
    
    Juego::Instance()->window->draw(bgCartel);
    Juego::Instance()->window->draw(cartel);
    Juego::Instance()->window->draw(tituloText);
    Juego::Instance()->window->draw(cuerpoText);
    
}

void Camara::setLastTime(int c){
    
    if(lastTime==0)
        lastTime = c;
    
}

void Camara::mostrarLlave(){
    
    if(Jugador::Instance()->tieneLLave){
        Mundo::Instance()->llave->setPosition(this->camara->getCenter().x+75,this->camara->getCenter().y-275);
        Juego::Instance()->window->draw(*Mundo::Instance()->llave);
        
    }
    
}



void Camara::cartelPresidente(){
    if(lastTime==0)
        setLastTime(countdown);
    // Texto
    sf::Font font;  
    font.loadFromFile("fonts/alterebro-pixel-font.ttf");
  
    sf::RectangleShape bgCartel;
    bgCartel.setFillColor(sf::Color(180,255,180,200));
    bgCartel.setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x, (float)Juego::Instance()->window->getSize().y));
    bgCartel.setOrigin((float)bgCartel.getSize().x/2, (float)bgCartel.getSize().y/2);
    bgCartel.setPosition(camara->getCenter().x,camara->getCenter().y);
    
    sf::RectangleShape cartel;
    cartel.setFillColor(sf::Color(255,255,255,255));
    cartel.setSize(sf::Vector2f((float)Juego::Instance()->window->getSize().x/1.4, (float)Juego::Instance()->window->getSize().y/1.4));
    cartel.setOrigin((float)cartel.getSize().x/2, (float)cartel.getSize().y/2);
    cartel.setPosition(camara->getCenter().x,camara->getCenter().y);
    cartel.setOutlineColor(sf::Color::Black);
    cartel.setOutlineThickness(2);
    
    sf::Text tituloText("-ERES EL PRESIDENTE-", font, 30);

    //tituloText.setPosition(cartel.getOrigin().x+40,cartel.getOrigin().y-140);
    tituloText.setPosition(camara->getCenter().x-130,camara->getCenter().y-230);
    tituloText.setCharacterSize(70);
    tituloText.setColor(sf::Color::Black);
   
    std::string lines = std::string("Tus stats finales son:");
    lines+="\n\nVOTOS CONSEGUIDOS: ";
    lines+=to_string(Mundo::Instance()->votosTotales);
    lines+="\nPACTOS REALIZADOS: ";
    lines+=to_string(Mundo::Instance()->numPactosRealizados);
    

    lines+="\nENEMIGOS DERROTADOS: ";
    lines+=to_string(Mundo::Instance()->enemigosTotalesEliminados);
    lines+="\nSIMPATIZANTES LIBERADOS: ";
    lines+=to_string(Mundo::Instance()->numSimpatizantesLiberados);
    
    lines+="\nTIEMPO REQUERIDO: ";
    
    lines+=to_string(Mundo::Instance()->tiempoEmpleado);
    lines+="\nPresiona la 'X' para volver al menu";

    sf::Text cuerpoText(lines, font, 30);
    //cuerpoText.setPosition(cartel.getOrigin().x-100,cartel.getOrigin().y-70);
    cuerpoText.setPosition(camara->getCenter().x-160,camara->getCenter().y-160);
   
    cuerpoText.setCharacterSize(50);
    cuerpoText.setColor(sf::Color::Black);
    
    Juego::Instance()->window->draw(bgCartel);
    Juego::Instance()->window->draw(cartel);
    Juego::Instance()->window->draw(tituloText);
    Juego::Instance()->window->draw(cuerpoText);
    
}