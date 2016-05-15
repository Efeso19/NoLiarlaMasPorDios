/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mundo.cpp
 * Author: chiri
 * 
 * Created on 14 de abril de 2016, 18:00
 */
#include <iostream>
#include <SFML/System.hpp>
#include "Mundo.h"
#include "Juego.h"
#include "jugador.h"
#include "Camara.h"
#include "LevelFactory.h"
#include "EInGame.h"

#define UPDATE_TICK_TIME 1000/15

Mundo* Mundo::pinstance = 0;
Mundo* Mundo::Instance(){
    
    if(pinstance == 0) pinstance = new Mundo();

    return pinstance;
}

Mundo::Mundo() : camaraVel(10) {
    
    
}

bool Mundo::crearMundo(int l){
    /*
     * nivel| niv1-niv2-niv3
     * ------------------------
     * nivel| 1-5-9 -> PP
     * nivel| 2-6-10 -> PSOE
     * nivel| 3-7-11 -> CIUDADANOS
     * nivel| 4-8-12 -> PODEMOS
     * 
     * ESTA ES LA VARIABLE QUE RECIBE EL METODO LEERMAPA PARA CARGARLA
     */
    
    nivel = l; //NIVEL SELECCIONADO
    
    //JUGADOR/////////////////
    Jugador::Instance();
    Jugador::Instance()->iniciarJugador(60, 340, l, secundario1, secundario2, true);
    Jugador::Instance()->vidasPrincipales= corazonesPrincipal;
    Jugador::Instance()->vidas = barrasPrincipal;
    Jugador::Instance()->vidasMiniaturas1 = barrasSecundario1;
    Jugador::Instance()->vidasMiniaturas2 = barrasSecundario2;
    Jugador::Instance()->enemigosEliminados = 0;

   if(faseActual==0 || faseActual>3) //MIRAR Mundo.h
        faseActual=1;
   
    /*
    lugaresVisitados[1] = -1;
    lugaresVisitados[2] = -1;
    lugaresVisitados[3] = -1;
    */
        
    
    std::cout<<"Has seleccionado al jugador de: ";
    if(nivel==1)std::cout<<"PODEMOS"<<std::endl;
    else if(nivel==2)std::cout<<"CIUDADANOS"<<std::endl;
    else if(nivel==3)std::cout<<"PP"<<std::endl;
    else if(nivel==4)std::cout<<"PSOE"<<std::endl;
    
    if(faseActual == 1){
        switch(l){ //TRANSFORMADOR DE NUMERO DE JUGADOR A NUMERO DE NIVEL

            case 1: lugaresVisitados[0] = 4;break; // La primera posicion del array será la sede del propio partido break;
            case 2: lugaresVisitados[0] = 3;break; // La primera posicion del array será la sede del propio partido
            case 3: lugaresVisitados[0] = 1;break; // La primera posicion del array será la sede del propio partido
            case 4: lugaresVisitados[0] = 2;break; // La primera posicion del array será la sede del propio partido
        }
    }

    
    //lugaresVisitados[0] = l;
    std::cout<<"lugaresVisitados[0]: "<< lugaresVisitados[0]<<std::endl;
    
    for(int i=0; i< 4; i++){
        std::cout<<"valor "<<lugaresVisitados[i]<<std::endl;
    }

    int random;
    //int min = 1;
    //int max = 4;
   
    do {
            /* initialize random seed: */
        //random = ( rand() / ((double)RAND_MAX+1)) * (max-min+1) + min;

        srand(time(NULL));
        random=(rand()%4)+1;
        //std::cout<<"Random: "<<random<<std::endl;

    } while(random==lugaresVisitados[0] || random==lugaresVisitados[1] || random==lugaresVisitados[2] || random==lugaresVisitados[3]);

    
//    switch(random){ //TRANSFORMADOR DE NUMERO DE JUGADOR A NUMERO DE NIVEL
//        
//        case 1: nivel = 4; break;
//        case 2: nivel = 3; break;
//        case 3: nivel = 1; break;
//        case 4: nivel = 2; break;
//        
//
//    }
    nivel = random;
    std::cout<<"Te ha tocado jugar en: ";
    if(nivel==1)std::cout<<"Sede del PP"<<std::endl;
    else if(nivel==2)std::cout<<"Sede del PSOE"<<std::endl;
    else if(nivel==3)std::cout<<"Sede de CIUDADANOS"<<std::endl;
    else if(nivel==4)std::cout<<"Sede de PODEMOS"<<std::endl;
    
    switch(faseActual){
        
        case 1: lugaresVisitados[1] =  nivel;
        std::cout<<"Fase 1: "<<lugaresVisitados[1]<<std::endl;
        
        case 2: lugaresVisitados[2] =  nivel;
        std::cout<<"Fase 2: "<<lugaresVisitados[2]<<std::endl;
        
        case 3: lugaresVisitados[3] =  nivel;
        std::cout<<"Fase 3: "<<lugaresVisitados[3]<<std::endl;
        
        
    }
    
    if(faseActual==2){
       nivel=nivel+4;
    }

    if(faseActual==3){
        nivel=nivel+8;
    }
    std::cout<<"Se va a cargar el nivel: "<<nivel<<std::endl;
    std::cout<<"Fase actual: "<<faseActual<<std::endl;
    //nivel=(random*(faseActual-1))+4; //faseActual-1 es la fase de la que venimos
    //MAPA////////////////////
    std::cout<<"HOASLASL!! NUMOERPAMP "<<nivel<<std::endl;
    mapa = new Mapa();
    mapa->leerMapa(nivel);
    
    
    //CAMARA//////////////////
    camRes = new sf::Vector2i;
    camaraVel = 3;
    
    camara = new Camara();
    
    
    //INICIALIZANDO Y LLENANDO LOS VECTORES DE ENEMIGOS
        
    enemigosCuerpo = new std::vector<Enemigo*>();
    enemigosAdistancia = new std::vector<Enemigo*>();
    std::cout<<"Numero de enemigos"<<mapa->numEnemigosC<<" "<<mapa->numEnemigosA<<std::endl;
    for(int i=0; i<mapa->numEnemigosC; i++){

        enemigosCuerpo->push_back(new Enemigo(true, mapa->matrizEnemigosC[i][0], mapa->matrizEnemigosC[i][1], 0, nivel));

    }
    for(int i=0; i<mapa->numEnemigosA; i++){

        enemigosAdistancia->push_back(new Enemigo(true, mapa->matrizEnemigosA[i][0],mapa->matrizEnemigosA[i][1], 1, nivel));

    }
    
    jefefinal = new BossFinal(true, mapa->posxBoss, mapa->posyBoss, nivel);

      
    /***Llave***/
    srand (time(NULL));
    int iSecret = rand() % mapa->numEnemigosC;
    enemigosCuerpo->at(iSecret)->tieneLlave = true;
    std::cout<<"La llave la tiene el NPC: "<<iSecret<<std::endl;
    sf::Texture *texturaKey = new sf::Texture();
    mostrarKey = false;
    switch(l){
        case 1:
        case 5:
        case 9:
            if(!texturaKey->loadFromFile("resources/key/keyPODEMOS.png")){
                std::cerr<<"Error al cargar la textura de keyPODEMOS.png";
            }
            break;
        case 2:
        case 6:
        case 10:
            if(!texturaKey->loadFromFile("resources/key/keyCS.png")){
                std::cerr<<"Error al cargar la textura de keyCS.png";
            }
            break;
        case 3:
        case 7:
        case 11:
            if(!texturaKey->loadFromFile("resources/key/keyPP.png")){
                std::cerr<<"Error al cargar la textura de keyPP.png";
            }
            break;
        case 4: 
        case 8:
        case 12:
            if(!texturaKey->loadFromFile("resources/key/keyPSOE.png")){
                std::cerr<<"Error al cargar la textura de keyPSOE.png";
            }
            break;
    }
    llave = new sf::Sprite(*texturaKey);    

    
//        
//    ///////////////////////////BUFFER DE SONIDO////////
    
    buffer = new sf::SoundBuffer;
    musica = new sf::Sound;
    bufferSobre = new sf::SoundBuffer;
    bufferHurt = new sf::SoundBuffer;
    soundSobre = new sf::Sound;
    soundHurt = new sf::Sound;
    
    if (!bufferSobre->loadFromFile("resources/FX/SOBRE.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    soundSobre->setBuffer(*bufferSobre);
    
    if (!bufferHurt->loadFromFile("resources/FX/HURT.flac"))
        std::cout<<"Problema al cargar bufferSalto";
    soundHurt->setBuffer(*bufferHurt);
//    
//    //////////////////////////////
    
    if(nivel==1 || nivel==5 || nivel==9){
        if (!buffer->loadFromFile("resources/PP/PP.flac"))
            std::cout<<"Error cargando PP.flac"<<std::endl;  
    } 
    if(nivel==2 || nivel==6 || nivel==10){
         if (!buffer->loadFromFile("resources/PSOE/PSOE.flac"))
            std::cout<<"Error cargando PSOE.flac"<<std::endl;   
    } 
    if(nivel==3 || nivel==7 || nivel==11){
        if (!buffer->loadFromFile("resources/CIUDADANOS/CIUDADANOS.flac"))
            std::cout<<"Error cargando CIUDADANOS.flac"<<std::endl;  
    } 
    if(nivel==4 || nivel==8 || nivel==12){
        if (!buffer->loadFromFile("resources/PODEMOS/PODEMOS.flac"))
            std::cout<<"Error cargando PODEMOS.flac"<<std::endl;  
    } 
     
    
    
    musica->setBuffer(*buffer);
    musica->setLoop(true);
    //musica->play(); 
    aux= true;//no tocar
    
    mundoCreado = true;
    
    //EInGame::Instance(Juego::Instance())->eliminandoMundo = false;
    return true;

}

void Mundo::Update(){
    
  
    
    
    
    if(!Jugador::Instance()->muerto)     //CONTORLA QUE EL HANDLE SE BLOQUEE
            Jugador::Instance()->handle();
             
        else
            camara->cartelGameOver();
        
    //IA DE LOS ENEMIGOS    
    
    if(updateClock.getElapsedTime().asMilliseconds() > UPDATE_TICK_TIME){
        timeElapsed = updateClock.restart();
        //manejadores de los enemigos
        for(int i=0; i<enemigosCuerpo->size(); i++){
           enemigosCuerpo->at(i)->handle();    
        }
        for(int j=0; j<enemigosAdistancia->size(); j++){
           enemigosAdistancia->at(j)->handle();
        }
        jefefinal->handle();
    }
    
     
    //COLISIONES DE LOS PROYECTILES
    
    //compruebo que los proyectiles del jugador se destruyen ya sea por que recorren una distancia determinadad
    //o porque golpean a los NPC. 
    //IMP si el proyectil del jugador colisiona con otro del NPC que ocurre? el mundo se destruiria y nada podria volver a ser como antes...
//    for(int i=0; i<Jugador::Instance()->proyectiles->size();i++){
//        Jugador::Instance()->proyectiles->at(i)->dibuja();
//        if(Jugador::Instance()->proyectiles->at(i)->destruir()){
 //            if(!Jugador::Instance()->proyectiles->empty()){
//                //Hay que comprobar que el vector no este vacio cuando quiera eliminar un objeto
//                delete Jugador::Instance()->proyectiles->at(i);
//                Jugador::Instance()->proyectiles->erase(Jugador::Instance()->proyectiles->begin()+i);
//            }
//
//        }else{
//            int j=0;
//            for(j=0; j<enemigosAdistancia->size(); j++){
//                if(Jugador::Instance()->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(enemigosAdistancia->at(j)->getSprite()->getGlobalBounds()) && Jugador::Instance()->proyectiles->at(j)->aparece){
//                    std::cout<<"Acabo de colisionar con un NPC a distancia"<<Jugador::Instance()->proyectiles->at(j)->aparece<<std::endl;
//                    delete enemigosAdistancia->at(j);
//                    enemigosAdistancia->erase(enemigosAdistancia->begin()+j);
//                    Jugador::Instance()->enemigosEliminados++;
//                    Jugador::Instance()->proyectiles->at(i)->aparece=false;
//                    std::cout<<"Acabo de settear el proyectil"<<Jugador::Instance()->proyectiles->at(j)->aparece<<std::endl;
//                }
//            }
//            j=0;
//            for(j=0; j<enemigosCuerpo->size(); j++){
//                if(Jugador::Instance()->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(enemigosCuerpo->at(j)->getSprite()->getGlobalBounds()) && Jugador::Instance()->proyectiles->at(j)->aparece){
//                    if(enemigosCuerpo->at(j)->tieneLlave){
//                        std::cout<<"he dropeado la puta llave cuando me han matado con proyectiles"<<std::endl;
//                        mostrarKey = true;
//                        llave->setPosition(enemigosCuerpo->at(j)->getSprite()->getPosition().x, enemigosCuerpo->at(j)->getSprite()->getPosition().y+20);
//                    }
//                    std::cout<<"Acabo de colisionar con un NPC cuerpo a cuerpo"<<Jugador::Instance()->proyectiles->at(j)->aparece<<std::endl;
//                    Jugador::Instance()->proyectiles->at(i)->aparece=false;
//                    std::cout<<"Acabo de settear el proyectil"<<Jugador::Instance()->proyectiles->at(j)->aparece<<std::endl;
//                    delete enemigosCuerpo->at(j);
//                    enemigosCuerpo->erase(enemigosCuerpo->begin()+j);
//                    Jugador::Instance()->enemigosEliminados++;
//                    
//                }
//            }
//            if(Jugador::Instance()->proyectiles->at(i)->getSprite().getGlobalBounds().intersects(jefefinal->getSprite()->getGlobalBounds()) && Jugador::Instance()->proyectiles->at(i)->aparece){
//                jefefinal->hp-=1;
//                
//                std::cout<<"el boss tiene"<<jefefinal->hp<<std::endl;
//               
//                Jugador::Instance()->proyectiles->at(i)->aparece=false;
//                
//            }
//        }
//    }
    
    //ACTUALIZAR VIDA DEL PERSONAJE
    //camara->actualizarVidasPrincipales(Jugador::Instance()->vidasPrincipales);
    
    //RECOGIDA DE VOTOS
    
    for(int i=0; i<mapa->arrayVotos->size(); i++)
        if(mapa->arrayVotos->at(i)->getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
            std::cout<<"El personaje ha tocado un voto"<<std::endl;
            delete mapa->arrayVotos->at(i);
            mapa->arrayVotos->erase(mapa->arrayVotos->begin()+i);
            //Aitor, aqui tienes que hacer una variable que incremente, asi te mostrara los votos que llevas
            votosTotales++;
            std::cout<<"Vtos tottales"<<votosTotales<<std::endl;
            camara->sumaVotos(1);
            soundSobre->play();
        }
      
}

void Mundo::Render(){
    bool aux2 = false;
    
        mapa->dibuja();
      
      //Jugador::Instance()->proyectiles->
      
        mapa->dibujaPlataformas();
        mapa->reconstruirPlataformas();
        
        mapa->dibujaVotos();
        
        if(faseActual == 1){
            mapa->dibujaAyuda1();
            mapa->dibujaAyuda2();
            mapa->dibujaAyuda3();
            mapa->dibujaAyuda4();
        }
        
        if(faseActual == 2){
            mapa->dibujaAyuda5();
        }
        //dibujo los dos vectores de los enemigos
        for(int i=0; i<enemigosCuerpo->size(); i++){
            enemigosCuerpo->at(i)->draw();
        }
        for(int j=0; j<enemigosAdistancia->size(); j++){
           enemigosAdistancia->at(j)->draw();
        }
        jefefinal->draw();
      
      
        //AQUI IMPRIMO LOS PROYECTILES DE LOS ENEMIGOS
        int y=0, j=0;
        for(y=0; y<enemigosAdistancia->size(); y++){
            //imprimimos los proyectiles
            for(j=0; j<enemigosAdistancia->at(y)->proyectiles->size();j++){
                enemigosAdistancia->at(y)->proyectiles->at(j)->dibuja();
                if(enemigosAdistancia->at(y)->proyectiles->at(j)->destruir()){
                    if(!enemigosAdistancia->at(y)->proyectiles->empty()){
                        delete enemigosAdistancia->at(y)->proyectiles->at(j);
                        enemigosAdistancia->at(y)->proyectiles->erase(enemigosAdistancia->at(y)->proyectiles->begin()+j);
                        soundHurt->play();
                    }
                    
                }else{
                    if(enemigosAdistancia->at(y)->proyectiles->at(j)->getSprite().getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds())){
                        std::cout<<"El proyectil ha danyado al juagdor"<<std::endl;
                        if(!enemigosAdistancia->at(y)->proyectiles->empty()){
                            delete enemigosAdistancia->at(y)->proyectiles->at(j);
                            enemigosAdistancia->at(y)->proyectiles->erase(enemigosAdistancia->at(y)->proyectiles->begin()+j);
                            soundHurt->play();
                        }
                        tiempo= relojGolpe.getElapsedTime().asSeconds();
                        Jugador::Instance()->golpeado=true;
                        
                        
                        if(Jugador::Instance()->seleccionJugador==1){
                            Jugador::Instance()->vidas=Jugador::Instance()->vidas-1;
                        }
                        
                        if(Jugador::Instance()->seleccionJugador==2){
                            Jugador::Instance()->vidasMiniaturas1=Jugador::Instance()->vidasMiniaturas1-1;
                            if(Jugador::Instance()->vidasMiniaturas1<0){
                                Jugador::Instance()->vidasMiniaturas1=0;
                            }
                            
                        }
                        
                        if(Jugador::Instance()->seleccionJugador==3){
                            Jugador::Instance()->vidasMiniaturas2=Jugador::Instance()->vidasMiniaturas2-1;
                            if(Jugador::Instance()->vidasMiniaturas2<0){
                                Jugador::Instance()->vidasMiniaturas2=0;
                            }
                            
                        }
                        
                        if(Jugador::Instance()->vidas<0)Jugador::Instance()->vidas=0;
                        if(Jugador::Instance()->vidasPrincipales<0)Jugador::Instance()->vidasPrincipales=0;
                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;
                        
                        
                        
                        
                        
                        /*Jugador::Instance()->vidas=Jugador::Instance()->vidas-1;
                        if(Jugador::Instance()->vidas<0)Jugador::Instance()->vidas=0;
                        std::cout<<"El jugador ahora tiene: "<<Jugador::Instance()->vidas<<"vidas"<<std::endl;*/
                    }
                }
            } 
        }
        j=0;
        for(j=0; j<jefefinal->proyectiles->size();j++){
            jefefinal->proyectiles->at(j)->dibuja();
            if(jefefinal->proyectiles->at(j)->destruir()){
                if(!jefefinal->proyectiles->empty()){
                    delete jefefinal->proyectiles->at(j);
                    jefefinal->proyectiles->erase(jefefinal->proyectiles->begin()+j);
                    soundHurt->play();
                }

            }else{
                if(jefefinal->proyectiles->at(j)->getSprite().getGlobalBounds().intersects(Jugador::Instance()->getSprite().getGlobalBounds()) && !jefefinal->muerto){
                    std::cout<<"El proyectil ha danyado al juagdor"<<std::endl;
                    if(!jefefinal->proyectiles->empty()){
                        delete jefefinal->proyectiles->at(j);
                        jefefinal->proyectiles->erase(jefefinal->proyectiles->begin()+j);
                        soundHurt->play();
                    }
                    tiempo= relojGolpe.getElapsedTime().asSeconds();
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
            }
        }
        if(mostrarKey){
            if(Jugador::Instance()->getSprite().getGlobalBounds().intersects(llave->getGlobalBounds())){
                mostrarKey = false;
                Jugador::Instance()->tieneLLave= true;
                std::cout<<"Tengo la llave de tu corasson"<<std::endl;
            }else{
                Juego::Instance()->window->draw(*llave);
            }
        }

        
        mapa->dibujaSimpatizante(Jugador::Instance()->politico, faseActual);
        Jugador::Instance()->comprobarCelda();
        //Jugador::Instance()->draw();
        camara->mostrarLlave();
        Juego::Instance()->window->draw(camara->getHudVotos());
        Juego::Instance()->window->draw(camara->getHudVotosValue());
        Juego::Instance()->window->draw(camara->getContador());
        Juego::Instance()->window->draw(camara->getContadorValue());
        
        if(Jugador::Instance()->seleccionJugador==2){
            if(Jugador::Instance()->prueba==1 || Jugador::Instance()->prueba==2 || Jugador::Instance()->prueba==3 || Jugador::Instance()->prueba==4){
                Jugador::Instance()->draw();
                Juego::Instance()->window->draw(camara->getMiniatura1());
                Juego::Instance()->window->draw(camara->getMiniatura1vida());
                camara->actualizarVidasMiniaturas(Jugador::Instance()->vidasMiniaturas1, Jugador::Instance()->prueba, Jugador::Instance()->seleccionJugador);
                int timer1 = clock.getElapsedTime().asSeconds();


                   if (timer1 > 1){
                       if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                    Mundo::Instance()->camara->countdown=camara->countdown-5;
                    clock.restart();
                       }
                   }

                if(Jugador::Instance()->vidasMiniaturas1>0 || Jugador::Instance()->ultimo==2){
                    Jugador::Instance()->draw();
                    //delete *player->seleccionJugador=2;
                }
                /*if(player->vidasMiniaturas1==0){
                    if(player->vidasMiniaturas2>0){
                        player->seleccionJugador=3;
                    }
                    if(player->vidasPrincipales!=0){
                        player->seleccionJugador=1;
                    }
                }*/
                if(Jugador::Instance()->vidasMiniaturas1==0){
                    //player->getSprite().getPosition().x;
                    //player->velocidadMovimiento=0;
                    //player->getSprite().setScale(100,100);
                    Jugador::Instance()->posicionJugador.x=60;
                    camara->resetearCamara();
                    if(Jugador::Instance()->vidasMiniaturas2>0){
                        Jugador::Instance()->seleccionJugador=3;
                    }

                    if(Jugador::Instance()->vidasPrincipales>0){
                        Jugador::Instance()->seleccionJugador=1;
                    }

                }
            }
            
        }
        
        if(Jugador::Instance()->seleccionJugador==3){
            if(Jugador::Instance()->prueba2==1 || Jugador::Instance()->prueba2==2 || Jugador::Instance()->prueba2==3 || Jugador::Instance()->prueba2==4){
                Jugador::Instance()->draw();
                Juego::Instance()->window->draw(camara->getMiniatura2());
                Juego::Instance()->window->draw(camara->getMiniatura2vida());
                camara->actualizarVidasMiniaturas(Jugador::Instance()->vidasMiniaturas2, Jugador::Instance()->prueba2, Jugador::Instance()->seleccionJugador);
                int timer2 = clock.getElapsedTime().asSeconds();

                if (timer2 > 1){
                       if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                    Mundo::Instance()->camara->countdown=camara->countdown-5;
                    clock.restart();
                       }
                   }
                if(Jugador::Instance()->vidasMiniaturas2>0 || Jugador::Instance()->ultimo==3){
                    Jugador::Instance()->draw();
                    //delete *player->seleccionJugador=3; 
                }

                if(Jugador::Instance()->vidasMiniaturas2==0){
                    //player->getSprite().getPosition().x;
                    //player->velocidadMovimiento=0;
                    //player->getSprite().setScale(100,100);
                    Jugador::Instance()->posicionJugador.x=60;
                    camara->resetearCamara();
                    if(Jugador::Instance()->vidasMiniaturas1>0){
                        Jugador::Instance()->seleccionJugador=2;
                    }

                    if(Jugador::Instance()->vidasPrincipales>0){
                        Jugador::Instance()->seleccionJugador=1;
                    } 
                }
            }
            
        }
        
        Juego::Instance()->window->draw(camara->getBarraVida());
        Juego::Instance()->window->draw(camara->getVidas());
        Juego::Instance()->window->draw(camara->getVidasPrincipales());
        
        if(Jugador::Instance()->seleccionJugador==1){
            Juego::Instance()->window->draw(camara->getBarraVida());
            Juego::Instance()->window->draw(camara->getVidas());
            Juego::Instance()->window->draw(camara->getVidasPrincipales());
            camara->actualizarVidas(Jugador::Instance()->vidas, Jugador::Instance()->politico, Jugador::Instance()->seleccionJugador);
            camara->actualizarVidasPrincipales(Jugador::Instance()->vidasPrincipales, Jugador::Instance()->seleccionJugador);
            int timer = clock.getElapsedTime().asSeconds();
               
            if (timer > 1){
                   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                Mundo::Instance()->camara->countdown=camara->countdown-5;
                clock.restart();
                   }
               }
            
            if(Jugador::Instance()->vidasPrincipales>0 && Jugador::Instance()->ultimo==1){
                //std::cout<<"MUERTOOOOOOOOO EL 11111111::::"<<player->vidasPrincipales<<std::endl;
                Jugador::Instance()->draw();
                //delete *player->seleccionJugador=1;
            }
            
            if(Jugador::Instance()->vidasPrincipales==0){
                //player->getSprite().getPosition().x;
                //player->velocidadMovimiento=0;
                //player->getSprite().setScale(100,100);
                Jugador::Instance()->posicionJugador.x=60;
                camara->resetearCamara();
                if(Jugador::Instance()->vidasMiniaturas1>0){
                    Jugador::Instance()->seleccionJugador=2;
                }
                
                if(Jugador::Instance()->vidasMiniaturas2>0){
                    Jugador::Instance()->seleccionJugador=3;
                } 
            }
        }
        
           
        camara->actualizarTiempo();
        //camara->actualizarVidas(player->vidas, player->politico, player->seleccionJugador);
        
        /*if(player->vidasPrincipales==0){
            player->vidasMiniaturas1=player->vidasMiniaturas1;
            if(player->vidasMiniaturas1==0){
                std::cout<<"MUERTOS TODOSSSSSSSSSS"<<std::endl;
                player->vidasMiniaturas2=player->vidasMiniaturas2;
                if(player->vidasMiniaturas2==0){
                    player->muerto=true;
                    std::cout<<"MUERTOS TODOSSSSSSSSSS"<<std::endl;
                }
            }
            //player->muerto=true;
            std::cout<<"MUERTOS TODOSSSSSSSSSS"<<std::endl;
        }*/
        
        //if(player->seleccionJugador==1){
            if(Jugador::Instance()->vidas==0){
                /*if(player->vidasPrincipales==0){
                    player->muerto=true;
                }*/
                
                /*if(player->vidasMiniaturas1==0){
                    player->muerto=true;
                }
                
                if(player->vidasMiniaturas2==0){
                    player->muerto=true;
                }
                 */
                //player->muerto=true;
                Jugador::Instance()->vidasPrincipales=Jugador::Instance()->vidasPrincipales-1;

                if(Jugador::Instance()->vidasPrincipales>0){//resucita con una vida menos
                    //player->muerto=false;
                    Jugador::Instance()->vidas=10;
                    Jugador::Instance()->posicionJugador.x=60;
                    camara->resetearCamara();
                }
            }
        
        
        if(jefefinal->hp<1){
            //std::cout<<"El Boss ha muerto"<<std::endl;
            jefefinal->muerto= true;
            if(Jugador::Instance()->estadoDelPacto == 2 || Jugador::Instance()->estadoDelPacto == 3){
                camara->cartelFinal();
                
                //this->~Mundo();
               
            }else{
               mapa->dibujaDialogoPacto();
               Jugador::Instance()->estadoDelPacto = 1;
               camara->setLastTime(camara->countdown);
            }
        }
        camara->draw();
        
        if(Jugador::Instance()->muerto || Mundo::Instance()->camara->countdown==0 || (Jugador::Instance()->vidasPrincipales<=0 && Jugador::Instance()->vidasMiniaturas1==0  &&  Jugador::Instance()->vidasMiniaturas2==0)){     //CONTORLA QUE APAREZCA EL CARTEL DE GAME OVER
            Jugador::Instance()->muerto= true;
            Jugador::Instance()->estadoDelPacto = 4; //para que se pare el tiempo del reloj
            camara->cartelGameOver();
            //Mundo::Instance()->musica.stop();
            std::cout<<"HA MUEEEEERTO!!!"<<std::endl;
        }
        
        if(Jugador::Instance()->prueba==0 && Jugador::Instance()->prueba2==0 && Jugador::Instance()->vidasPrincipales<=0){
                Jugador::Instance()->muerto= true;
                camara->cartelGameOver();
        }
        
        if(Jugador::Instance()->prueba==0 && Jugador::Instance()->vidasMiniaturas2==0 && Jugador::Instance()->vidasPrincipales<=0){
                Jugador::Instance()->muerto= true;
                camara->cartelGameOver();
        }
        
        if(Jugador::Instance()->prueba2==0 && Jugador::Instance()->vidasMiniaturas1==0 && Jugador::Instance()->vidasPrincipales<=0){
                Jugador::Instance()->muerto= true;
                camara->cartelGameOver();
        }
        
        
        //Bucle de obtención de eventos
        //while (Juego::Instance()->window->pollEvent(Juego::Instance()->event)){
            
            //switch(Juego::Instance()->event.type){     
                //Si se recibe el evento de cerrar la ventana la cierro
        if(Jugador::Instance()->estadoDelPacto == 2 || Jugador::Instance()->estadoDelPacto == 3){
            
        
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                if(faseActual == 3){
                    if(aux){
                        sumarValoresTotales();
                        aux=false;
                        aux2 = true; 
                    }
                    
                }else{
                    EInGame::Instance(Juego::Instance())->eliminarMundo();
                    musica->stop();
                }

            }
        }
        ///}
        
        if(aux2){
            camara->cartelPresidente();
        }
        
}

void Mundo::eliminarMundo(){
    sumarValoresTotales();
    mostrarKey = false;
    pausa = false;
    
    
    
    //delete camara;
    delete mapa;
    delete camRes;
    delete jefefinal;
    delete enemigosAdistancia;
    delete enemigosCuerpo;
    delete llave;
    delete camara;
    
    delete buffer;
    delete musica;
    delete bufferSobre;
    delete bufferHurt;
    delete soundSobre;
    delete soundHurt;
    
        
    mapa = 0;
    camRes = 0;
    jefefinal = 0;
    enemigosAdistancia = 0;
    enemigosCuerpo = 0;
    llave = 0;
    camara = 0;
    
//  buffer = 0;
//  musica = 0;
    bufferSobre = 0;
    bufferHurt = 0;
    soundSobre = 0;
    soundHurt = 0;
    
    //pinstance = 0;
    std::cout << "Mundo ha sido eliminado"   << std::endl;
    
    
}

Mundo::~Mundo() {
   
    
    //eliminarMundo();
    //std::cout<<"Mapa: "<<&mapa<<std::endl;
    //std::cout<<"Camara: "<<&camara<<std::endl;
}

void Mundo::sumarValoresTotales(){
    
    std::cout<<"estoy en la fase: "<<faseActual<<std::endl;
        tiempoEmpleado += (camara->tiempoInicio-camara->lastTime);
    std::cout<<"tiempo total:"<<tiempoEmpleado<<std::endl;
    incrementoTiempo = camara->votosConseguidos + (Jugador::Instance()->enemigosEliminados*2) + camara->lastTime;
            
    
        
    if(Jugador::Instance()->carcelAbierta){
        numSimpatizantesLiberados++;
        incrementoTiempo +=15;
    }
    
    std::cout<<"El incremento del timepo es: "<<camara->votosConseguidos<<"+("<<Jugador::Instance()->enemigosEliminados*2<<")+"<<camara->lastTime<<"+15="<<incrementoTiempo<<std::endl;
    
    if(Jugador::Instance()->estadoDelPacto == 2){
        numPactosRealizados ++;
        if(secundario2 == 0 && secundario1 != 0){
            switch(nivel){
                case 1: case 5: case 9:
                    secundario2 = 3;
                    break;
                case 2: case 6: case 10:
                    secundario2 = 4;
                    break;
                case 3: case 7: case 11:
                    secundario2 = 2;
                    break;
                case 4: case 8: case 12:
                    secundario2 = 1;
                    break;                    
            }
        }
        if(secundario1 == 0){
            
            switch(nivel){
                case 1: case 5: case 9:
                    secundario1 = 3;
                    break;
                case 2: case 6: case 10:
                    secundario1 = 4;
                    break;
                case 3: case 7: case 11:
                    secundario1 = 2;
                    break;
                case 4: case 8: case 12:
                    secundario1 = 1;
                    break;                    
            }        
        }
                
        
    }
    actualizarVidas();
    
    std::cout<<votosTotales<<"Simpa: "<<numSimpatizantesLiberados<<", pactos: "<<numPactosRealizados<<",enemigos "<<enemigosTotalesEliminados<<std::endl;
    
    
}

void Mundo::actualizarVidas(){
    
    
    corazonesPrincipal = Jugador::Instance()->vidasPrincipales;

    barrasPrincipal = Jugador::Instance()->vidas;
    barrasSecundario1 = Jugador::Instance()->vidasMiniaturas1;
    barrasSecundario2 = Jugador::Instance()->vidasMiniaturas2;
 
    std::cout<<"Corazones "<<corazonesPrincipal<<" barrasP "<<barrasPrincipal<<" barrasS1 "<<barrasSecundario1<<" barrasS2 "<<barrasSecundario2<<std::endl;
    
}

