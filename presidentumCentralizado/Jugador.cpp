/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.cpp
 * Author: alfon
 * 
 * Created on 5 de abril de 2016, 19:31
 */
#include <vector>
#include <string> 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Jugador.h"
#include "Camara.h"
#include "Mapa.h"
#include "Proyectil.h"
#include <SFML/Audio.hpp>
#include "Mapa.h"
#include "Proyectil.h"
#include "Juego.h"
#include "Mundo.h"
#include "EInGame.h"
#include "EMenu.h"


using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")

Jugador* Jugador::pinstance = 0;
Jugador* Jugador::Instance(){
    
    if(pinstance == 0) pinstance = new Jugador();

    return pinstance;
}

Jugador::Jugador() {
}

Jugador::Jugador(const Jugador& orig) {
}

Jugador::~Jugador() {
}

void Jugador::iniciarJugador(float x, float y, int politic, int politic2, int politic3, bool activado){
    //prueba=0;
    //prueba2=0;
    vidas=10;
    vidasPrincipales=3;
    seleccionJugador=1;
    vidasMiniaturas1=10;
    vidasMiniaturas2=10;
    ultimo=1;
    
    matriz=new int*[99];
    for(int i=0; i<99;i++){
        matriz[i]=new int[4];
    }
    
    if (!bufferHurt.loadFromFile("resources/FX/HURT.flac"))
        std::cout<<"Problema al cargar bufferHurt";
    soundHurt.setBuffer(bufferHurt);
    
    politico=politic;
    leerXML();
    switch(politico){
        case 1:
            if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pablospritesheet.png";
            }
            break;
        case 2:
            if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura de albertspritesheet.png";
            }
            break;
        case 3:
            if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura de marianospritesheet.png";
            }
            

            break;
        case 4:
            if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
            }
            break;
            
    }
    
    prueba=politic2;
    leerXML();
    switch(prueba){
        case 1:
            if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pablospritesheet.png";
            }
            break;
        case 2:
            if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura de albertspritesheet.png";
            }
            break;
        case 3:
            if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura de marianospritesheet.png";
            }
            

            break;
        case 4:
            if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
            }
            break;
            
    }
    
    prueba2=politic3;
    leerXML();
    switch(prueba2){
        case 1:
            if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pablospritesheet.png";
            }
            break;
        case 2:
            if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                std::cerr<<"Error al cargar la textura de albertspritesheet.png";
            }
            break;
        case 3:
            if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                std::cerr<<"Error al cargar la textura de marianospritesheet.png";
            }
            

            break;
        case 4:
            if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
            }
            break;
            
    }
    
    
    sprite.setTexture(texturaJugador);
    //Le pongo el centroide donde corresponde
    // w=78 h=148 en todos los sprites menos en los de ataque
    sprite.setOrigin(39, 74);
   
    sprite.setOrigin((matriz[0][2])/2,(matriz[0][3])/2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(matriz[0][0], matriz[0][1], matriz[0][2], matriz[0][3]));
    
    sprite.setPosition(x, y);
//    std::cout<<sprite.getPosition().x<<" estamos en estas dos coordenadas "<<sprite.getPosition().y<<std::endl;
    tieneLLave = false;
    activo = activado;
    alturaSuelo=sprite.getPosition().y+10;
    
    posicionJugador.x=x;
    posicionJugador.y=y;
    salto=false;
    velocidadMovimiento=3;
    velocidadSalto=12;
    velocidadJugador.x=0;
    velocidadJugador.y=0;
    muerto=false;
    direccionPro=1;//para saber la direccion del proyectil. Derecha: 1. Izquierda 2.
    
    proyectiles = new vector<Proyectil*>();
    golpeado=false;
    col=0;
    paso=0;
    golpeoXseg=0;
    eliminadoA=-1;
    eliminadoC=-1;
    estadoDelPacto = 0; 
    bossTocado = false;
    dialogo = false;
    carcelAbierta = false;
    sf::Texture* dialogo1= new sf::Texture();
    if(!dialogo1->loadFromFile("resources/carcelCerradaDialog.png")){
        std::cerr<<"Error al cargar la textura de carcelCerradaDialog.png";
    }
    sf::Texture* dialogo2= new sf::Texture();
    if(!dialogo2->loadFromFile("resources/carcelAbiertaDialog.png")){
        std::cerr<<"Error al cargar la textura de carcelAbiertaDialog.png";
    }
    dialogoCerrado = new sf::Sprite(*dialogo1);
    dialogoAbierto = new sf::Sprite(*dialogo2);     
    ///////////////////////////BUFFER DE SONIDO////////
    
   
    if (!bufferSalto.loadFromFile("resources/FX/Salto.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    
   
    soundSalto.setBuffer(bufferSalto);
    
    if (!bufferAtaque.loadFromFile("resources/FX/ATAQUE.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    
   
    soundAtaque.setBuffer(bufferAtaque);

    
    
    ///////////////////////////SETEO DEL CONTROLADOR////////
    
    
    for(int i=0; i<8;i++){  //Busca un mando conectado
        
        if(sf::Joystick::isConnected(i)){
            
            controllerIndex = i;
            std::cout<<"Mando encontrado en puerto: "<<controllerIndex<<std::endl; 
            break;
        }
        
    }
    
   
    
}

void Jugador::leerXML(){
    int posX=0;
    int linea=1;
    /****LECTURA DEL XML PARA EL SPRITE!!****/
    ifstream fin;
    switch(politico){
        case 1:
            fin.open("resources/pablospritesheet.xml");
                
            break;
        case 2:
            fin.open("resources/albertspritesheet.xml");
            break;
        case 3:
            fin.open("resources/marianospritesheet.xml");
            break;
        case 4:
            fin.open("resources/pedrospritesheet.xml");
                
            
            break;
            
    } // abrir el xml que se va a leer
    
    
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
        if(linea==15){break;}
    }
    //Esto es para imprimir la matriz obtenida en consola
    /*
    if(linea>2){
        for(int i=0; i<=11;i++){
            for (int j=0;j<4;j++){
                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
            }
            cout << endl;
        }
    }
    cout<<"presidentumClases"<<endl;
    */
}

void Jugador::draw(){
    if(muerto==false){
         Juego::Instance()->window->draw(sprite);
         dibujarProyectiles();
        //std::cout<<sprite.getPosition().x<<" "<<sprite.getPosition().y<<std::endl;
    }
    //std::cout<<sprite.getPosition().y<<std::endl;
    
    
    //    //PRUEBAS DEL MANDO
//    if(sf::Joystick::isButtonPressed(controllerIndex,0)){
//        std::cout<<"Mando: A "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,1)){
//         std::cout<<"Mando: B "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,2)){
//         std::cout<<"Mando: X "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,3)){
//         std::cout<<"Mando: Y "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,4)){
//         std::cout<<"Mando: L "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,5)){
//         std::cout<<"Mando: R "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,6)){
//         std::cout<<"Mando: Select "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,7)){
//         std::cout<<"Mando: Start "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,8)){
//         std::cout<<"Mando: JoyClickL "<<std::endl;
//
//    }
//    if(sf::Joystick::isButtonPressed(controllerIndex,9)){
//         std::cout<<"Mando: JoyClickR "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovY) ==  100){
//        std::cout<<"Mando: UP "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovY) ==  -100){
//        std::cout<<"Mando: DOWN "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  -100){
//        std::cout<<"Mando: LEFT "<<std::endl;
//
//    }
//    if(sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  100){
//        std::cout<<"Mando: RIGHT "<<std::endl;
//
//    }
}

sf::Sprite Jugador::getSprite(){
    return sprite;
}

//estoy pasando por parametro los vectores de sprites por el handle (que es una guarrada) porque no puedo hacerlo en el main
//una vez con la maquina de estado podremos accedera ellos sin pasarlo por parametro
void Jugador::handle(){
    /*sf::Clock golpeoTime;
    float golpeo=0;
    
    golpeo= golpeoTime.getElapsedTime().asSeconds();
    if(golpeo>0.5 && direccionPro==1){
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
        sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
        golpeoTime.restart();
    }

    if(golpeo>0.5 && direccionPro==0){
        sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //IMPORTANTE recolocar el centroide
        sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
        golpeoTime.restart();
    }
*/

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !EMenu::Instance(Juego::Instance())->enPausa && EMenu::Instance(Juego::Instance())->pauseLimiter.getElapsedTime().asSeconds()>0.2){

           EMenu::Instance(Juego::Instance())->salida = false;
           EMenu::Instance(Juego::Instance())->enPausa = true;
           EMenu::Instance(Juego::Instance())->Handle();
       
    }
    
    const float gravedad =0.5;

    if(estadoDelPacto==1){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            std::cout<<"Ha dicho que SI"<<std::endl;
            estadoDelPacto = 2;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
            std::cout<<"Ha dicho que NO"<<std::endl;
            estadoDelPacto = 3;
        }
    }
    if(estadoDelPacto==0 && !muerto && Mundo::Instance()->camara->countdown!=0){
        /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
    //        if(politico==2 || politico ==3){
    //            disparar();
    //        }else{
                std::cout<<matriz[1][2]<<" "<<matriz[1][3]<<std::endl;
                sprite.setOrigin(matriz[2][2]/2,matriz[1][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
                sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
    //        }
        }*/
        bool enelsuelo=false;
        int i=0;

         for(i=0; i<Mundo::Instance()->mapa->arraySuelo.size(); i++){
             if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arraySuelo[i]->getGlobalBounds())){   
                 if(this->getSprite().getPosition().y<Mundo::Instance()->mapa->arraySuelo[i]->getPosition().y){
                     /*Solo se subira a la plataforma si el personaje se encuentra por encima de esta, es decir: 
                      SI posicion Y del personaje < posicion Y plataforma */
                    velocidadJugador.y = 0;//EInGame::Instance()->mundo->mapa->
                    alturaSuelo=Mundo::Instance()->mapa->arraySuelo[i]->getPosition().y-90;
                    enelsuelo=true;
                 }else{
                     velocidadJugador.y=1;
                 }
             }
         }

        int choque=-1; //0 der, 1 izq, -1 nada
        int j=0;
        for(j=0; j<Mundo::Instance()->mapa->arrayParedes.size(); j++){
            if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arrayParedes[j]->getGlobalBounds())){
                if(this->getSprite().getPosition().x<Mundo::Instance()->mapa->arrayParedes[j]->getPosition().x){
                    choque=0;
                }else if(this->getSprite().getPosition().x>Mundo::Instance()->mapa->arrayParedes[j]->getPosition().x){
                    choque=1;
                }
            }
        }


        for(j=0; j<Mundo::Instance()->mapa->arrayMuerte.size(); j++){
            if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arrayMuerte[j]->getGlobalBounds())){
    //            if(this->getSprite().getPosition().x<mapa->arrayMuerte[j]->getPosition().x){
    //                choque=0;
    //            }else if(this->getSprite().getPosition().x>mapa->arrayMuerte[j]->getPosition().x){
    //                choque=1;
    //            }
                if(seleccionJugador==1){
                    vidas=0;
                    if(vidas==0 && vidasPrincipales>0){
                        vidasPrincipales--;
                        vidas=10;
                        if(vidasPrincipales==0){
                            vidas=0;
                        }
                        Mundo::Instance()->camara->resetearCamara();
                        posicionJugador.x=60;
                    }
                    std::cout<<"ME he muerto!!"<<std::endl;
                }
                if(seleccionJugador==2){
                    Mundo::Instance()->camara->resetearCamara();
                    posicionJugador.x=60;
                    vidasMiniaturas1=0;
                }
                if(seleccionJugador==3){
                    Mundo::Instance()->camara->resetearCamara();
                    posicionJugador.x=60;
                    vidasMiniaturas2=0;
                }
            }
        }


        int choquePlat;
        int k=0;

        for(k=0; k<Mundo::Instance()->mapa->arrayPlataformas.size(); k++){
            if(this->getSprite().getGlobalBounds().intersects(Mundo::Instance()->mapa->arrayPlataformas[k]->spritePlat.getGlobalBounds())){  
                if(this->getSprite().getPosition().y<Mundo::Instance()->mapa->arrayPlataformas[k]->spritePlat.getPosition().y
                        && Mundo::Instance()->mapa->arrayPlataformas[k]->rota==false){
                    alturaSuelo=Mundo::Instance()->mapa->arrayPlataformas[k]->spritePlat.getPosition().y-90;
                    enelsuelo=true;
                    if(Mundo::Instance()->mapa->arrayPlataformas[k]->tipo==0){
                        if(Mundo::Instance()->mapa->arrayPlataformas[k]->direccion==1){
                            posicionJugador.x+=0.9;
                        }else{
                            posicionJugador.x-=0.9;
                        }
                    }

                    if(Mundo::Instance()->mapa->arrayPlataformas[k]->tipo==2){
                        //Jugador sobre una plataforma rompible
                        Mundo::Instance()->mapa->arrayPlataformas[k]->romperPlataforma();
                    }

                    choquePlat=0;
                }
            }
        }

        if(enelsuelo==true){
            posicionJugador.y=alturaSuelo+36.5;
        }else{
            //cout<<"ESTOY EN EL AIRE!!!"<<endl;
            alturaSuelo=580;
        }


        if((vidasPrincipales>0) && vidasMiniaturas1>=0 && vidasMiniaturas2>=0){

            //velocidadMovimiento=3;
            if(vidasMiniaturas1==0 && vidasMiniaturas2==0){
                //posicionJugador.x=200;
                //velocidadMovimiento=0;
                ultimo=1;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || seleccionJugador==1){
                politico=politico;
                seleccionJugador=1;
                vidas=vidas;
                vidasPrincipales=vidasPrincipales;

                switch(politico){
                case 1:
                    if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                        std::cerr<<"Error al cargar la textura de pablospritesheet.png";
                    }
                    break;
                case 2:
                    if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                        std::cerr<<"Error al cargar la textura de albertspritesheet.png";
                    }
                    break;
                case 3:
                    if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                        std::cerr<<"Error al cargar la textura de marianospritesheet.png";
                    }
                    break;
                case 4:
                    if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                        std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
                    }
                    break;

                }
            }

        }

        else if(vidasPrincipales==0 && vidasMiniaturas1==0 && vidasMiniaturas2==0){
            muerto=true;
            cout<<"HA MUEEEEERTO!!!"<<endl;
        }

        if((vidasPrincipales>=0 || vidasPrincipales!=0) && vidasMiniaturas1>0 && vidasMiniaturas2>=0){

            if(vidasMiniaturas2==0 && vidasPrincipales<=0){
                //posicionJugador.x=200;
                //velocidadMovimiento=0;
                ultimo=2;
            }
            //velocidadMovimiento=3;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || seleccionJugador==2){

                //prueba=politico;
                //politico=4;
                //prueba=4;
                seleccionJugador=2;
                //vidasMiniaturas1=vidasMiniaturas1;

                switch(prueba){
                    case 1:
                        if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                            std::cerr<<"Error al cargar la textura de pablospritesheet.png";
                        }
                        break;
                    case 2:
                        if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                            std::cerr<<"Error al cargar la textura de albertspritesheet.png";
                        }
                        break;
                    case 3:
                        if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                            std::cerr<<"Error al cargar la textura de marianospritesheet.png";
                        }
                        break;
                    case 4:
                        if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                            std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
                        }
                        break;

                }
            }
        }

        else if(vidasPrincipales==0 && vidasMiniaturas1==0 && vidasMiniaturas2==0){
            muerto=true;
            cout<<"HA MUEEEEERTO!!!"<<endl;
        }



        if((vidasPrincipales>=0 || vidasPrincipales!=0) && vidasMiniaturas1>=0 && vidasMiniaturas2>0){
            if(vidasMiniaturas1==0 && vidasPrincipales<=0){
                //posicionJugador.x=200;
                //velocidadMovimiento=0;
                ultimo=3;
            }

            //velocidadMovimiento=3;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)  || seleccionJugador==3){

                //prueba2=politico;
                //politico=4;
                //prueba2=3;
                //politico=3;
                seleccionJugador=3;
                //vidasMiniaturas2=vidasMiniaturas2;

                switch(prueba2){
                    case 1:
                        if(!texturaJugador.loadFromFile("resources/pablospritesheet.png")){
                            std::cerr<<"Error al cargar la textura de pablospritesheet.png";
                        }
                        break;
                    case 2:
                        if(!texturaJugador.loadFromFile("resources/albertspritesheet.png")){
                            std::cerr<<"Error al cargar la textura de albertspritesheet.png";
                        }
                        break;
                    case 3:
                        if(!texturaJugador.loadFromFile("resources/marianospritesheet.png")){
                            std::cerr<<"Error al cargar la textura de marianospritesheet.png";
                        }
                        break;
                    case 4:
                        if(!texturaJugador.loadFromFile("resources/pedrospritesheet.png")){
                            std::cerr<<"Error al cargar la textura de pedrospritesheet.png";
                        }
                        break;

                }
            }
        }

        else if(vidasPrincipales==0 && vidasMiniaturas1==0 && vidasMiniaturas2==0){
            muerto=true;
            cout<<"HA MUEEEEERTO!!!"<<endl;
        }

        if(vidasPrincipales==0 && vidasMiniaturas1==0 && vidasMiniaturas2==0){
                muerto=true;
        }



        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) /*|| sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  100*/){

            direccion=1;

            direccionPro=1;
            //camara->moveRight(this);

            velocidadJugador.x = velocidadMovimiento;
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)

            paso= pasoTime.getElapsedTime().asSeconds();
            if(paso>=0 && paso<=0.2){
                sprite.setTextureRect(sf::IntRect(matriz[4][0], matriz[4][1], matriz[4][2], matriz[4][3]));
            }
             if(paso>0.2){
                 if(paso>0.4){
                     pasoTime.restart();
                 }
                sprite.setTextureRect(sf::IntRect(matriz[5][0], matriz[5][1], matriz[5][2], matriz[5][3]));

            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) /*|| sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  -100*/){

            direccion=0;

            direccionPro=0;

            //camara->moveLeft(this);

                velocidadJugador.x = -velocidadMovimiento;


                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)

                 paso= pasoTime.getElapsedTime().asSeconds();
                if(paso>=0 && paso<=0.2){
                    sprite.setTextureRect(sf::IntRect(matriz[7][0], matriz[7][1], matriz[7][2], matriz[7][3]));
                   // std::cout<<"ID= holaaaaaaaaaaaaaaaaaa"<<std::endl;
                }
                 if(paso>0.2){
                     if(paso>0.4){
                         pasoTime.restart();
                     }
                    sprite.setTextureRect(sf::IntRect(matriz[8][0], matriz[8][1], matriz[8][2], matriz[8][3]));

                }



            //}  



        }

        /*else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            golpeoXseg=golpeosSegundo.getElapsedTime().asSeconds();


            if(golpeoXseg>0.5){

                    sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
                    sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                    velocidadJugador.x = 0;
                    golpeosSegundo.restart();
                }

            if(direccion==1){
                if(golpeoXseg>0.5){

                    sprite.setOrigin(matriz[0][2]/4,matriz[0][3]/2);
                    sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                    velocidadJugador.x = 0;
                    golpeosSegundo.restart();
                }


            }

            else if(direccion==0){
                if(golpeoXseg>0.5){
                    sprite.setOrigin(-20,matriz[0][3]/2);
                    sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                    velocidadJugador.x = 0;
                    golpeosSegundo.restart();
                }
                sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2);
            }
        }*/

        else{
            velocidadJugador.x = 0;
            if(direccionPro==1){
                sprite.setTextureRect(sf::IntRect(matriz[3][0], matriz[3][1], matriz[3][2], matriz[3][3]));
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    sprite.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));
                }
            }
            else{ 
                sprite.setOrigin(matriz[6][2]/2,matriz[6][3]/2);
                sprite.setTextureRect(sf::IntRect(matriz[6][0], matriz[6][1], matriz[6][2], matriz[6][3]));
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
                }
            }
        }




        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)  ){
            golpeoXseg=golpeosSegundo.getElapsedTime().asMilliseconds();
            float disparoAparicion=0;
            disparoAparicion=aparicionProyectil.getElapsedTime().asSeconds();
            soundAtaque.play();

            if(direccion){
                sf::Vector2f origin(matriz[0][2]/4,matriz[0][3]/2);
                sf::IntRect textRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]);
           }
            else{
                sf::Vector2f origin(60,matriz[2][3]/2);
                sf::IntRect textRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]);
            }


            velocidadJugador.x = 0;

            switch(politico){
                case 1:
                case 4:
                    if(golpeoXseg>9.1){
                        if(direccion == 1){
                            sprite.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
                            sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
                        }else{
                            sprite.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
                            sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
                        }
                        golpeando();
                        golpeosSegundo.restart();
                    }
                    break;
                default:
                    if(disparoAparicion>0.35){
                        disparar();
                        aparicionProyectil.restart();
                    }
            }




        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right) /*|| (sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  100 && sf::Joystick::isButtonPressed(controllerIndex,0))*/){

            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
            sprite.setTextureRect(sf::IntRect(matriz[9][0], matriz[9][1], matriz[9][2], matriz[9][3]));



        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) /*|| (sf::Joystick::getAxisPosition(controllerIndex, sf::Joystick::PovX) ==  -100 && sf::Joystick::isButtonPressed(controllerIndex,0))*/){
            sprite.setOrigin(matriz[0][2]/2,matriz[0][3]/2); //Si el jugador cambia de direccion MIENTRAS golpea/dispara, recoloca el centroide (se evita un bug visual)
            sprite.setTextureRect(sf::IntRect(matriz[10][0], matriz[10][1], matriz[10][2], matriz[10][3]));
        }
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) /*|| sf::Joystick::isButtonPressed(controllerIndex,0)*/ && salto){


                    velocidadJugador.y = -velocidadSalto;
                    salto = false;
                    soundSalto.play(); 
        }

        if(!salto){
            velocidadJugador.y += gravedad;
           // cout<<"pos Y "<<posicionJugador.y<<endl;
            //cout<<"altura suelo "<<alturaSuelo<<endl;

        }        
        else
            velocidadJugador.y = 0;

        if(choque==0){
            velocidadJugador.x=-1;
        }
        if(choque==1){
            velocidadJugador.x=1;
        }
        posicionJugador += velocidadJugador;

        salto = posicionJugador.y+10  >= alturaSuelo;
    //    std::cout<<"pos Y "<<posicionJugador.y<<std::endl;
    //    cout<<"altura suelo"<<alturaSuelo<<endl;
    //    cout<<salto<<endl;
        if(salto){
            sprite.setPosition(0, alturaSuelo-10);
    //        //posicionJugador.y = alturaSuelo - 10;
    //        
        }
    //    cout<<"posicion X "<<posicionJugador.x<<endl;
        //cout<<"posicion Y "<<posicionJugador.y<<endl;
        if(enelsuelo==true){
                    //posicionJugador.y=alturaSuelo+36.5;
        }



        sprite.setPosition(posicionJugador);
    
    } 
}

void Jugador::disparar(){
    float disparoAparicion=0;
    disparoAparicion=aparicionProyectil.getElapsedTime().asSeconds();
    if(direccionPro==1){//derecha
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            sprite.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
            sprite.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
//            std::cout<<"Estoy golpeando y cambiadno el sprite"<<std::endl;
            if(politico==2 || politico == 3 ){
                //Al disparar, se genera un proyectil y se inserta en el vector
                Proyectil *pro = new Proyectil(direccionPro, sprite.getPosition(), matriz, politico);
                //pro->crearPro();
               
                //std::cout << "posicion X proyectil reciente:" << pro->posx << std::endl;
                proyectiles->push_back(pro);
                
                //Al disparar, se genera un proyectil y se inserta en el vector
//                Proyectil *pro2 = new Proyectil(direccionPro, sprite.getPosition(), matriz, politico);
//                //pro->crearPro();
//                pro2->aparece=false;
//                //std::cout << "posicion X proyectil reciente:" << pro->posx << std::endl;
//                proyectiles->push_back(pro2);
                /****/
               std::cout << "Hay: "<< proyectiles->size() << " proyectiles!!!!!" << std::endl;
                
                /****/
            }
        }
    }else{//izquierda
        if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            sprite.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
            sprite.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
            if(politico==2 || politico == 3 ){
                //Al disparar, se genera un proyectil y se inserta en el vector
                Proyectil *pro = new Proyectil(direccionPro, sprite.getPosition(), matriz, politico);
                proyectiles->push_back(pro);
                /****/
//                std::cout << "Hay: "<< proyectiles->size() << " proyectiles" << std::endl;
                /****/
            }
        }
    }
}

void Jugador::dibujarProyectiles(){
    
    
    int i=0;
        //compruebo que los proyectiles del jugador se destruyen ya sea por que recorren una distancia determinadad
        //o porque golpean a los NPC. 
        //IMP si el proyectil del jugador colisiona con otro del NPC que ocurre? el mundo se destruiria y nada podria volver a ser como antes...
        for(i=0; i<proyectiles->size();i++){
            proyectiles->at(i)->dibuja();
            //std::cout<<"proyectil jugador disparado"<<std::endl;
            if(proyectiles->at(i)->destruir()){
                if(!proyectiles->empty()){
                    //Hay que comprobar que el vector no este vacio cuando quiera eliminar un objeto
                    delete proyectiles->at(i);
                    proyectiles->erase(proyectiles->begin()+i);
                }
                
            }else{
                for(int j=0; j<Mundo::Instance()->enemigosAdistancia->size(); j++){
                    if(proyectiles->at(i)->getSprite().getGlobalBounds().intersects(Mundo::Instance()->enemigosAdistancia->at(j)->getSprite()->getGlobalBounds()) && Jugador::Instance()->proyectiles->at(i)->aparece){
                        delete Mundo::Instance()->enemigosAdistancia->at(j);
                        Mundo::Instance()->enemigosAdistancia->erase(Mundo::Instance()->enemigosAdistancia->begin()+j);
                        enemigosEliminados++;
                        Mundo::Instance()->enemigosTotalesEliminados++;
                        if(!proyectiles->empty()){
                              Jugador::Instance()->proyectiles->at(i)->aparece=false;

//                            delete proyectiles->at(i);
//                           proyectiles->erase(proyectiles->begin()+i);
                        }
                    }
                }
                for(int j=0; j<Mundo::Instance()->enemigosCuerpo->size(); j++){
                    if(proyectiles->at(i)->getSprite().getGlobalBounds().intersects(Mundo::Instance()->enemigosCuerpo->at(j)->getSprite()->getGlobalBounds()) && Jugador::Instance()->proyectiles->at(i)->aparece){
                        if(Mundo::Instance()->enemigosCuerpo->at(j)->tieneLlave){
                            std::cout<<"he dropeado la puta llave cuando me han matado con proyectiles"<<std::endl;
                            Mundo::Instance()->mostrarKey = true;
                            Mundo::Instance()->llave->setPosition(Mundo::Instance()->enemigosCuerpo->at(j)->getSprite()->getPosition().x, Mundo::Instance()->enemigosCuerpo->at(j)->getSprite()->getPosition().y+20);
                        }

                        
                        delete Mundo::Instance()->enemigosCuerpo->at(j);
                        Mundo::Instance()->enemigosCuerpo->erase(Mundo::Instance()->enemigosCuerpo->begin()+j);
                        enemigosEliminados++;
                        Mundo::Instance()->enemigosTotalesEliminados++;
                        if(!proyectiles->empty()){
                             Jugador::Instance()->proyectiles->at(i)->aparece=false;

//                            delete proyectiles->at(i);
//                            proyectiles->erase(proyectiles->begin()+i);
                        }
                    }
                }
                if(proyectiles->at(i)->getSprite().getGlobalBounds().intersects(Mundo::Instance()->jefefinal->getSprite()->getGlobalBounds()) && Jugador::Instance()->proyectiles->at(i)->aparece){
                    Mundo::Instance()->jefefinal->hp-=1;
                    std::cout<<"El boss tiene: "<<Mundo::Instance()->jefefinal->hp<<std::endl;
                    Jugador::Instance()->proyectiles->at(i)->aparece=false;
                }
                
            }
        }
    
    
}

bool Jugador::isMoving(){
    
    if((posicionJugador.x-posicionAnterior.x < -3.95 || posicionJugador.x-posicionAnterior.x > 1.95))
        return true;
    else if(posicionJugador.x+posicionAnterior.x == -2 || posicionJugador.x+posicionAnterior.x == 0)
        return false;
    
}

void Jugador::golpeando() {
    
//    std::cout<<"le estoy pasando los enemigos correctamente"<<Mundo::Instance()->enemigosCuerpo->size()<<" "<<Mundo::Instance()->enemigosAdistancia->size()<<std::endl;
    for(int i=0; i<Mundo::Instance()->enemigosCuerpo->size(); i++){
        if(sprite.getGlobalBounds().intersects( Mundo::Instance()->enemigosCuerpo->at(i)->getSprite()->getGlobalBounds())){
            if(Mundo::Instance()->enemigosCuerpo->at(i)->tieneLlave){
                std::cout<<"he dropeado la puta llave"<<std::endl;
                Mundo::Instance()->mostrarKey = true;
                Mundo::Instance()->llave->setPosition(Mundo::Instance()->enemigosCuerpo->at(i)->getSprite()->getPosition().x, Mundo::Instance()->enemigosCuerpo->at(i)->getSprite()->getPosition().y+20);
            }
            delete Mundo::Instance()->enemigosCuerpo->at(i);
            Mundo::Instance()->enemigosCuerpo->erase(Mundo::Instance()->enemigosCuerpo->begin()+i);
            eliminadoC=i;
            enemigosEliminados++;
            Mundo::Instance()->enemigosTotalesEliminados++;
            //std::cout<<"Quedan "<<Mundo::Instance()->enemigosCuerpo->size()<<" cuerpo a cuerpo"<<std::endl;
        }
    }
    for(int i=0; i<Mundo::Instance()->enemigosAdistancia->size(); i++){
        if(sprite.getGlobalBounds().intersects(Mundo::Instance()->enemigosAdistancia->at(i)->getSprite()->getGlobalBounds())){
            delete Mundo::Instance()->enemigosAdistancia->at(i);
            Mundo::Instance()->enemigosAdistancia->erase(Mundo::Instance()->enemigosAdistancia->begin()+i);
            eliminadoA=i;
            enemigosEliminados++;
            Mundo::Instance()->enemigosTotalesEliminados++;
            std::cout<<"Quedan "<<Mundo::Instance()->enemigosAdistancia->size()<<" a distancia"<<std::endl;

        }
    }
    
    if(sprite.getGlobalBounds().intersects(Mundo::Instance()->jefefinal->getSprite()->getGlobalBounds())){
        Mundo::Instance()->jefefinal->hp-=2;
        std::cout<<"El jefe final tiene: "<<Mundo::Instance()->jefefinal->hp<<" de vida"<<std::endl;
    }
    
}

void Jugador::comprobarCelda(){
    
    if(carcelAbierta){
        //carcelAbierta significa que el usuario debe ser recompensado
        //dialogoAbierto->setPosition(mapa->spriteCarcelCerrada->getPosition().x, mapa->spriteCarcelCerrada->getPosition().y-100);
        Mundo::Instance()->mapa->dibujaCarcelAbierta();
        //mapa->dibujaCarcelAbierta(window);
        //window.draw(*dialogoAbierto);
        Mundo::Instance()->mapa->dibujaDialogoAbierto();
        //mapa->dibujaDialogoAbierto(window);
        tieneLLave = false; //para eliminar la llave
    }else{
        if(sprite.getGlobalBounds().intersects(Mundo::Instance()->mapa->spriteCarcelCerrada->getGlobalBounds())){
            if(tieneLLave){
                std::cout<<"estoy tocando la puta carcel con la llave"<<std::endl;
                //window.draw(*dialogoAbierto);
                Mundo::Instance()->mapa->dibujaDialogoAbierto();
                //mapa->dibujaDialogoAbierto(window);

                
                carcelAbierta = true;
                dialogo= false;
            }else{
                //dialogoCerrado->setPosition(mapa->spriteCarcelCerrada->getPosition().x+10, mapa->spriteCarcelCerrada->getPosition().y-100);
                Mundo::Instance()->mapa->dibujaCarcelCerrada();
                //mapa->dibujaCarcelCerrada(window);
                //window.draw(*dialogoCerrado);
                //mapa->dibujaDialogoCerrado(window);
                Mundo::Instance()->mapa->dibujaDialogoCerrado();
                dialogo = true; 
            }
        }else{
            Mundo::Instance()->mapa->dibujaCarcelCerrada();
            //mapa->dibujaCarcelCerrada(window);
            dialogo = false;
        }
        
    }
    
    
    
}

void Jugador::resetearJugador(){
    tieneLLave = false;
    golpeado = false;
    estadoDelPacto = 0;
    dialogo = false;
    carcelAbierta = false;
    
    vidasMiniaturas1=10;
   vidasMiniaturas2=10;


vidas=10;
   vidasPrincipales=3;
    
    std::cout<<"Jugador reseteado, vidas: "<<vidas<<" , "<<vidasPrincipales<<std::endl;
    
    
}