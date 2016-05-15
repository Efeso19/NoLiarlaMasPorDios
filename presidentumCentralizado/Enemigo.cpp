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
 * VARIABLES DE ENEMIGO HEREDADAS;
    int x; //posicion del personaje en x
    int y; //posicion del personaje en y
    int ataque; // daño que el NPC inflinje al jugador
    int hp; // vida que tiene el NPC
    //Mundo* mundo;
    //IA* ia;
    sf::Texture* spriteSheet; // spritesheet que usará el sprite
 * Perruquita no la lies mas XD
*/

#include "Enemigo.h"
#include "Juego.h"
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

Enemigo::Enemigo() : patrullaje(true) {
    
//    std::cout<<"hola, soy un enemigo vacio"<<std::endl;
    
    
}

Enemigo::Enemigo(bool valorPatrullaje, float posx, float posy, int type, int partido){
    
    //std::cout<<"Enemigo creado"<<std::endl;
    
    patrullaje=valorPatrullaje;
    x=posx;
    y=posy+40;
 
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    leerXML();

    // 1 PP. 2 PSOE. 3 CS. 4 PODEMOS
    switch(partido){
        case 1: case 5: case 9:
            if(!texturaEnemigo.loadFromFile("resources/PP/enemigosPP.png")){
                std::cerr<<"Error al cargar la textura de enemigosPP.png";
            }
            break;
        case 2: case 6: case 10:
            if(!texturaEnemigo.loadFromFile("resources/PSOE/enemigosPSOE.png")){
                std::cerr<<"Error al cargar la textura de enemigosPSOE.png";
            }
            break;
        case 3: case 7: case 11:
            if(!texturaEnemigo.loadFromFile("resources/CIUDADANOS/enemigosCIUDADANOS.png")){
                std::cerr<<"Error al cargar la textura de enemigosCIUDADANOS.png";
            }
            
            break;
        case 4: case 8: case 12:
            if(!texturaEnemigo.loadFromFile("resources/PODEMOS/enemigosPODEMOS.png")){
                std::cerr<<"Error al cargar la textura de EnemigosPODEMOS.png";
            }
            break;
    }
    
    
    tipo=type;
//    std::cout<<posx<<" "<<posy<<" "<<tipo<<std::endl;
    spriteSheet = new sf::Sprite;
    spriteSheet->setTexture(texturaEnemigo);
    if(tipo == 1){
//        std::cout<<matriz[10][0]<<" "<<matriz[10][1]<<" "<<matriz[10][2]<<" "<<matriz[10][3]<<std::endl;
        spriteSheet->setOrigin(matriz[10][2]/2, matriz[10][3]/2);
        spriteSheet->setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
    }else{
        spriteSheet->setOrigin(matriz[1][2]/2, matriz[1][3]/2);
        spriteSheet->setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
    }
    
    spriteSheet->setPosition(x, y);
    
    direccion=1;
    
    proyectiles = new vector<Proyectil*>();
    paso=0;
    golpeosSegundo;
    golpeoXseg=0;
    golpeado=false;
    tieneLlave = false;
  
    if (!bufferHurt.loadFromFile("resources/FX/HURT.flac"))
        std::cout<<"Problema al cargar bufferHurt";
    soundHurt.setBuffer(bufferHurt);
    
    
}


bool Enemigo::getPatrullaje(){
    
    return patrullaje;
    
}

void Enemigo::setPatrullaje(bool valorPatrullaje){
    
    patrullaje = valorPatrullaje;
    
}

Enemigo::~Enemigo() {
}

void Enemigo::leerXML(){
    int posX=0;
    int linea=1;
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    fin.open("resources/PP/enemigosPP.xml"); // abrir el xml que se va a leer
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

void Enemigo::draw(){
    Juego::Instance()->window->draw(*spriteSheet);
}

void Enemigo::handle(){
    
        if(Jugador::Instance()->getSprite().getPosition().x > x-(1066*0.7)){
       
        int posInicioX=Jugador::Instance()->getSprite().getPosition().x;
        float dif=posInicioX-spriteSheet->getPosition().x;
        if(tipo==0){
            if(direccion == 1){
                if(x-150<spriteSheet->getPosition().x){
                    //std::cout<<"a la izq"<<std::endl;
                    spriteSheet->move(-7.5, 0);
                }else{
                    direccion = 0;
                }
            }else{
                if(x+150>spriteSheet->getPosition().x){
                    //std::cout<<"a la der"<<std::endl;
                    spriteSheet->move(7.5, 0);
                }else{
                    direccion = 1;
                }
            }
        }else{
            if(dif>0){
                direccion = 0;
                
            }else{
                direccion = 1;
            }
        }
        if(direccion==1){
            paso= pasoTime.getElapsedTime().asSeconds();
            if(tipo==0){
                if(paso>=0 && paso<=0.2){
                    spriteSheet->setOrigin(matriz[3][2]/2, matriz[3][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                    //std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
                }
                 if(paso>0.2){
                     //if(paso>0.4){
                        //std::cout<<"ID= adiooooooooooooooooooooooooooooooooooooooos"<<std::endl;
                        pasoTime.restart();
                     //}
                    spriteSheet->setOrigin(matriz[6][2]/2, matriz[6][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));

                }
            }
        }else if(direccion==0){
            paso= pasoTime.getElapsedTime().asSeconds();
            if(tipo==0){
                if(paso>=0 && paso<=0.2){
                    spriteSheet->setOrigin(matriz[2][2]/2, matriz[2][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                    //std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
                }
                 if(paso>0.2){
                     //if(paso>0.4){
                        //std::cout<<"ID= adiooooooooooooooooooooooooooooooooooooooos"<<std::endl;
                        pasoTime.restart();
                     //}

                    spriteSheet->setOrigin(matriz[7][2]/2, matriz[7][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));

                }
            }
        }
        //
        //std::cout<<"La diferencia entre el sprite y el NPC es de: "<<dif<<std::endl;
            golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();
            if(abs(dif)<60 && direccion==1 && tipo==0 && !golpeado && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+20) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-20)){
                //golpeo a la izquierda cuerpo a cuerpo

                if(golpeoXseg>1){
                    //std::cout<<"te miro y te golpeo izq"<<std::endl;
                    spriteSheet->setOrigin(40, matriz[9][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
                    if(spriteSheet->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
//                        std::cout<<"te miro y te golpeo izq"<<spriteSheet->getPosition().y<<" "<<Jugador::Instance()->getSprite().getPosition().y<<std::endl;
                        Jugador::Instance()->soundHurt.play();
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
//                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;

                    }
                    golpeosSegundo.restart();
                }
                golpeado = false;
            }else if(abs(dif)<60 && direccion==0 && tipo == 0 && !golpeado && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+20) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-20)){
                //golpero a la derecha cuerpo a cuerpo
                if(golpeoXseg>1){
                    //std::cout<<"te miro y te golpeo dere"<<std::endl;
                    Jugador::Instance()->soundHurt.play();
                    spriteSheet->setOrigin(40, matriz[8][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));
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
//                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;

                    }
                    golpeosSegundo.restart();
                }
                golpeado = false;
            }         
            else if(abs(dif)<300 && direccion==0 && tipo ==1 && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+52) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-58)){
                //golpeo a la derecha a distancia
                if(golpeoXseg>1){
                    //std::cout<<"te miro y te golpeo dere a distancia"<<spriteSheet.getPosition().y<<" "<<jugador->getSprite().getPosition().y<<std::endl;
                    spriteSheet->setOrigin(30, matriz[17][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[17][0], matriz[17][1], matriz[17][2], matriz[17][3]));
                    disparar();

                    golpeosSegundo.restart();
                }else{
                    spriteSheet->setOrigin(matriz[10][2]/2, matriz[10][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                }
            }else if(abs(dif)<300 && direccion==1 && tipo ==1 && Jugador::Instance()->getSprite().getPosition().y < (spriteSheet->getPosition().y+52) && Jugador::Instance()->getSprite().getPosition().y > (spriteSheet->getPosition().y-58)){
                //golpeo a la izquierda a distancia
                //jugador->getSprite().getPosition().y < (spriteSheet.getPosition().y+52) && jugador->getSprite().getPosition().y > (spriteSheet.getPosition().y-58)
                //con comprobacion para que los el npc dispare si esta en esa zona Y, para que no tire chorizos sin sentido
                if(golpeoXseg>1){
                    //std::cout<<"te miro y te golpeo izq a distancia "<<spriteSheet.getPosition().y<<" "<<jugador->getSprite().getPosition().y<<std::endl;
                    spriteSheet->setOrigin(50, matriz[18][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[18][0], matriz[18][1], matriz[18][2], matriz[18][3]));

                    disparar();

                    golpeosSegundo.restart();
                }else{
                    spriteSheet->setOrigin(matriz[10][2]/2, matriz[10][3]/2);
                    spriteSheet->setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                }
            }


        
     
    }
    

    
}

void Enemigo::disparar(){
    
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

sf::Sprite* Enemigo::getSprite(){

    return spriteSheet;

}
