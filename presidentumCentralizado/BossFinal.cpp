/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   Enemigo.cpp
 * Author: chiri
 * 
 * Created on 12 de abril de 2016, 20:25
 *
 * 
*/

#include "BossFinal.h"
#include "Juego.h"
#include "Mundo.h"
#include <iostream>
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstring>

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")

BossFinal::BossFinal() : patrullaje(true) {
    
    std::cout<<"hola, soy un enemigo vacio"<<std::endl;
    
    
}

BossFinal::BossFinal(bool valorPatrullaje, float posx, float posy, int type){
    //type es para determinar el partido politico del jefe
    std::cout<<"JEFE creado"<<std::endl;
    
    patrullaje=valorPatrullaje;
    x=posx;
    y=posy+40;
 
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    tipo=type;
    leerXML();
    
    
    texturaEnemigo = new sf::Texture();
    switch(tipo){
        case 1:
        case 5:
        case 9:
            if(!texturaEnemigo->loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Mariano";
            }
             
            break;
        case 2:
        case 6:
        case 10:
            
            if(!texturaEnemigo->loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Pedro";
            }
            
            break;
        case 3:
        case 7:
        case 11:
            
            if(!texturaEnemigo->loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Albert";
            } 
            break;
        case 4:
        case 8:
        case 12:
            if(!texturaEnemigo->loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura del boss final Pablo";
            }
            break;
            
    }
    std::cout<<posx<<"      "<<posy<<" "<<tipo<<std::endl;
    spriteSheet = new sf::Sprite(*texturaEnemigo);
    //spriteSheet->setTexture(*texturaEnemigo);
    std::cout<<posx<<" "<<posy<<" "<<tipo<<std::endl;
    spriteSheet->setOrigin(matriz[0][2]/2, matriz[0][3]/2);
    
    spriteSheet->setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
    spriteSheet->setPosition(x, y);

    
    direccion=1;
    
    proyectiles = new vector<Proyectil*>();
    paso=0;
    golpeosSegundo;
    golpeoXseg=0;
    golpeado=false;
    activado = false; //si nos acercamos lo suficiente al bss final despertará y empezara a moverse
    hp= 10;
    muerto = false; 
    
}


bool BossFinal::getPatrullaje(){
    
    return patrullaje;
    
}

void BossFinal::setPatrullaje(bool valorPatrullaje){
    
    patrullaje = valorPatrullaje;
    
}

BossFinal::~BossFinal() {
}

void BossFinal::leerXML(){
    int posX=0;
    int linea=1;
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    if(tipo==4 || tipo == 8 || tipo == 12){
        fin.open("resources/pablospritesheet.xml");
        std::cout<<"Estoy cargando el XML de Pablo, siendo Bosss"<<std::endl;
    }else{
        fin.open("resources/marianospritesheet.xml"); // abrir el xml que se va a leer
        std::cout<<"Estoy cargando el XML de los demas, siendo Bosss"<<tipo<<std::endl;
    }
    // comenzamos a leer cada una de las lineas
    while (!fin.eof()){
        // esto es para controlar el tamanyo maximo de cada linea
        char buf[MAX_CHARS_PER_LINE];
        fin.getline(buf, MAX_CHARS_PER_LINE);
        int n = 0;

        // cada linea va almacenada en un vector
        const char* token[MAX_TOKENS_PER_LINE] = {};

        // parseamos las lineas, separando cada elemento de la linea por comillas (")
        token[0] = strtok(buf, DELIMITER);

        if (token[0]){
            for (n = 1; n < MAX_TOKENS_PER_LINE; n++){
                token[n] = strtok(0, DELIMITER);

                if (linea<=2) break; // si no hay mas, se termina el bucle
                //SOLO nos interesa a partir de la linea 2 del XML
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
                        break;
                    }
                }        
            }
        }
        linea++;
        if(linea==22){break;}
    }
    //Esto es para imprimir la matriz obtenida en consola
    /*
    if(linea>2){
        for(int i=0; i<=18;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
           }
            cout << endl;
        }
    }
    */
}

void BossFinal::draw(){
    Juego::Instance()->window->draw(*spriteSheet);
}

void BossFinal::handle(){
    
    if(Jugador::Instance()->getSprite().getPosition().x > ((Mundo::Instance()->mapa->_tileWidth*Mundo::Instance()->mapa->_width)-15*Mundo::Instance()->mapa->_tileWidth) && !activado){
        activado = true; 
    }
    if(activado && !Jugador::Instance()->muerto && !muerto){
        int posInicioX=Jugador::Instance()->getSprite().getPosition().x;
        float dif=posInicioX-spriteSheet->getPosition().x;
        //Para que el personaje se mueva
        if(direccion == 1){
            if(x-400<spriteSheet->getPosition().x){
                //std::cout<<"a la izq"<<std::endl;
                spriteSheet->move(-8, 0);
            }else{
                direccion = 0;
            }
        }else{
            if(x+50>spriteSheet->getPosition().x){
                //std::cout<<"a la der"<<std::endl;
                spriteSheet->move(8, 0);
            }else{
                direccion = 1;
            }
        }
        
        if(direccion==1){
            paso= pasoTime.getElapsedTime().asSeconds();
            if(paso>=0 && paso<=0.2){
                spriteSheet->setOrigin(matriz[8][2]/2, matriz[8][3]/2);
                spriteSheet->setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
            }
             if(paso>0.2){
                pasoTime.restart();
                spriteSheet->setOrigin(matriz[7][2]/2, matriz[7][3]/2);
                spriteSheet->setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
            }
        }else if(direccion==0){
            paso= pasoTime.getElapsedTime().asSeconds();
            if(paso>=0 && paso<=0.2){
                spriteSheet->setOrigin(matriz[4][2]/2, matriz[4][3]/2);
                spriteSheet->setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
            }
             if(paso>0.2){
                pasoTime.restart();
                spriteSheet->setOrigin(matriz[5][2]/2, matriz[5][3]/2);
                spriteSheet->setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));
           
             }
        }
        
        golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();
//        if(abs(dif)<60 && direccion==1 && (tipo == 2 || tipo == 4) && !golpeado && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+20) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-20)){
//            //golpeo a la izquierda cuerpo a cuerpo
//
//            if(golpeoXseg>1){
//                //std::cout<<"te miro y te golpeo izq"<<std::endl;
//                spriteSheet->setOrigin(40, matriz[2][3]/2);
//                spriteSheet->setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
//                if(spriteSheet->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
//                    std::cout<<"te miro y te golpeo izq"<<spriteSheet->getPosition().y<<" "<<Jugador::Instance()->getSprite().getPosition().y<<std::endl;
//                    golpeado = true;
//                    Jugador::Instance()->golpeado=true;
//                    Jugador::Instance()->vidas=Jugador::Instance()->vidas-2;
//                    if(Jugador::Instance()->vidas<0)
//                        Jugador::Instance()->vidas=0;
//                    std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;
//
//                }
//                golpeosSegundo.restart();
//            }
//            golpeado = false;
//        }else if(abs(dif)<60 && direccion==0 && (tipo == 2 || tipo == 4) && !golpeado && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+20) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-20)){
//            //golpero a la derecha cuerpo a cuerpo
//            if(golpeoXseg>1){
//                //std::cout<<"te miro y te golpeo dere"<<std::endl;
//                spriteSheet->setOrigin(40, matriz[1][3]/2);
//                spriteSheet->setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
//                if(spriteSheet->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
//                    golpeado = true;
//                    Jugador::Instance()->golpeado=true;
//                    //std::cout<<"Le he golpeado al payaso ejeje"<<std::endl;
//                    Jugador::Instance()->vidas=Jugador::Instance()->vidas-2;
//                    if(Jugador::Instance()->vidas<0)
//                        Jugador::Instance()->vidas=0;
//                    std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;
//
//                }
//                golpeosSegundo.restart();
//            }
//            golpeado = false;
//        }  
        if( (tipo == 2 || tipo == 4 || tipo == 6 || tipo == 8 || tipo == 10 || tipo == 12) && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+52) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-58)){
            if(dif < 0 && dif>-60){
                if(golpeoXseg>1){
                    //std::cout<<"te miro y te golpeo izq"<<std::endl;
                    spriteSheet->setOrigin(40, matriz[2][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                    if(spriteSheet->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
                        //std::cout<<"te miro y te golpeo izq"<<spriteSheet.getPosition().y<<" "<<jugador->getSprite().getPosition().y<<std::endl;
                        golpeado = true;
                        Jugador::Instance()->golpeado=true;
                        
                        //player->vidas=player->vidas-1;
                        
                        if(Jugador::Instance()->seleccionJugador==1){
                            Jugador::Instance()->vidas=Jugador::Instance()->vidas-2;
                        }
                        
                        if(Jugador::Instance()->seleccionJugador==2){
                            Jugador::Instance()->vidasMiniaturas1=Jugador::Instance()->vidasMiniaturas1-2;
                            if(Jugador::Instance()->vidasMiniaturas1<0){
                                Jugador::Instance()->vidasMiniaturas1=0;
                            }
                            
                        }
                        
                        if(Jugador::Instance()->seleccionJugador==3){
                            Jugador::Instance()->vidasMiniaturas2=Jugador::Instance()->vidasMiniaturas2-2;
                            if(Jugador::Instance()->vidasMiniaturas2<0){
                                Jugador::Instance()->vidasMiniaturas2=0;
                            }
                            
                        }
                        
                        if(Jugador::Instance()->vidas<0)Jugador::Instance()->vidas=0;
                        if(Jugador::Instance()->vidasPrincipales<0)Jugador::Instance()->vidasPrincipales=0;
                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;

                    }
                    golpeosSegundo.restart();
                }
                golpeado = false;
            }else if(dif > 0 && dif<60){
                if(golpeoXseg>1){
                    //std::cout<<"te miro y te golpeo dere"<<std::endl;
                    spriteSheet->setOrigin(40, matriz[1][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                    if(spriteSheet->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
                        golpeado = true;
                        Jugador::Instance()->golpeado=true;
                        
                        //player->vidas=player->vidas-1;
                        
                        if(Jugador::Instance()->seleccionJugador==1){
                            Jugador::Instance()->vidas=Jugador::Instance()->vidas-2;
                        }
                        
                        if(Jugador::Instance()->seleccionJugador==2){
                            Jugador::Instance()->vidasMiniaturas1=Jugador::Instance()->vidasMiniaturas1-2;
                            if(Jugador::Instance()->vidasMiniaturas1<0){
                                Jugador::Instance()->vidasMiniaturas1=0;
                            }
                            
                        }
                        
                        if(Jugador::Instance()->seleccionJugador==3){
                            Jugador::Instance()->vidasMiniaturas2=Jugador::Instance()->vidasMiniaturas2-2;
                            if(Jugador::Instance()->vidasMiniaturas2<0){
                                Jugador::Instance()->vidasMiniaturas2=0;
                            }
                            
                        }
                        
                        if(Jugador::Instance()->vidas<0)Jugador::Instance()->vidas=0;
                        if(Jugador::Instance()->vidasPrincipales<0)Jugador::Instance()->vidasPrincipales=0;
                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;
 
                    }
                    golpeosSegundo.restart();
                }
            golpeado = false;
            }
        }

        if( (tipo == 1 || tipo == 3 || tipo == 5 || tipo == 7 || tipo == 9 || tipo == 11 ) && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+52) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-58)){
            if(dif < 0 && dif>-300){
                if(golpeoXseg>1){
                    spriteSheet->setOrigin(50, matriz[2][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));

                    
                        //IMPORTANTE cambiar el centroide a la hora de atacar!


                        //Al disparar, se genera un proyectil y se inserta en el vector
                        Proyectil *pro = new Proyectil(0, spriteSheet->getPosition(), matriz, 5);
                        proyectiles->push_back(pro);
                        /****/
                        //std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                        /****/

                    

                    golpeosSegundo.restart();
                }else{
                    spriteSheet->setOrigin(matriz[0][2]/2, matriz[0][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
                }
                
                
                
            }else if(dif > 0 && dif<300){
                if(golpeoXseg>1){
                    spriteSheet->setOrigin(30, matriz[1][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                    //Al disparar, se genera un proyectil y se inserta en el vector
                    Proyectil *pro = new Proyectil(1, spriteSheet->getPosition(), matriz, 5);
                    pro->crearPro();
                    std::cout << "posicion X proyectil reciente:" << pro->getSprite().getPosition().y << std::endl;
                    proyectiles->push_back(pro);
                    /****/
                    //std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                    /****/

                    golpeosSegundo.restart();
                }else{
                    spriteSheet->setOrigin(matriz[0][2]/2, matriz[0][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
                } 
                
                
                
            }
        
        }
    }

     
    
      
    
}

void BossFinal::disparar(){
    
    float disparoAparicion=0;
    disparoAparicion=aparicionProyectil.getElapsedTime().asSeconds();
    if(direccion==0){//derecha
        if(disparoAparicion>0.35){
       

            //Al disparar, se genera un proyectil y se inserta en el vector
            Proyectil *pro = new Proyectil(1, spriteSheet->getPosition(), matriz, 5);
            pro->crearPro();
            std::cout << "posicion X proyectil reciente:" << pro->getSprite().getPosition().y << std::endl;
            proyectiles->push_back(pro);
            /****/
            //std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
            /****/
            
        }
    }else{//izquierda
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            
            
            //Al disparar, se genera un proyectil y se inserta en el vector
            Proyectil *pro = new Proyectil(0, spriteSheet->getPosition(), matriz, 5);
            proyectiles->push_back(pro);
            /****/
            //std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
            /****/
            
        }
    }
    
}

sf::Sprite* BossFinal::getSprite(){

    return spriteSheet;

}
