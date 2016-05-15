/* 
 * File:   Proyectil.cpp
 * Author: Aitor
 * 
 * Created on 5 de abril de 2016, 10:38
 */

#include "Proyectil.h"
#include "Juego.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = "\""; //IMPORTANTE, cada elemento de las lineas del XML van separados por comillas (")

Proyectil::Proyectil(){
    
}

Proyectil::Proyectil(int direccion, sf::Vector2f pospersonaje, int **mat, int politic) {
    dir=direccion;
    disRecorrida=0;
    if(direccion==1){
        posx=pospersonaje.x+40;
        posy=pospersonaje.y;
    }else{
        posx=pospersonaje.x-70;
        posy=pospersonaje.y;
    }
    matriz=mat;
    politico=politic;
    /*
    //para imprimir la matriz
    for(int i=0; i<=11;i++){
        for (int j=0;j<4;j++){
            cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
        }
        cout << endl;
    }
    */
    //CARGAR LA IMAGEN
    texPro = new sf::Texture();
    if(politic==2){
        if (!texPro->loadFromFile("resources/albertspritesheet.png")){
            std::cerr << "Error cargando la imagen";
            exit(0);
        }
        spritePro.setTexture(*texPro);
        spritePro.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
    }else if(politic==3){
        if (!texPro->loadFromFile("resources/marianospritesheet.png")){
            std::cerr << "Error cargando la imagen";
            exit(0);
        } 
        spritePro.setTexture(*texPro);
        spritePro.setTextureRect(sf::IntRect(matriz[11][0], matriz[11][1], matriz[11][2], matriz[11][3]));
    }else{
        if (!texPro->loadFromFile("resources/NPC-PROYECTIL.png")){
            std::cerr << "Error cargando la imagen de los rpoyectiles";
            exit(0);
        } 
        spritePro.setTexture(*texPro);
    }

    
    spritePro.setPosition(posx, posy);
    
    //std::cout << "proyectil creado!" << std::endl;
    //std::cout << "posicion X proyectil:" << posx << " posicion Y proyectil:" << posy << std::endl;

    disparoAparicion=0;
    disparoTime=0;
    aparece = true;
    std::cout<<"He creado un proyectil y aparece"<<aparece<<std::endl;


}

Proyectil::Proyectil(const Proyectil& orig) {
}

Proyectil::~Proyectil() {
}

void Proyectil::leerSprite(){
        /*LECTURA DEL XML!*/
    
    /*MATRIZ BIDIMENSIONAL para almacenar los 4 parametros de cada sprite*/
    
    matriz= new int*[99];
    for(int i = 0; i < 99; i++){
        matriz[i] = new int[4];
    }

    int posX=0;
    int linea=1;
    
    
   /****LECTURA DEL XML PARA EL SPRITE!!****/
    
    
  ifstream fin;
  if(politico!=5){
  fin.open("resources/albertspritesheet.xml"); // abrir el xml que se va a leer
  }else{
      fin.open("resources/CIUDADANOS/enemigosCIUDADANOS.xml");
  }
          if (!fin.good()) 
            std::cout << "No se ha podido abrir el spritesheet" << std::endl;
  
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
  //Para imprimir la matriz del sprite sheet XML!
//      if(linea>2){
//        for(int i=0; i<=11;i++){
//            for (int j=0;j<4;j++){
//                cout << "Matriz["<< i <<"]["<< j << "] =" << matriz[i][j] << endl;
//            }
//            cout << endl;
//        }
//    }
  /*FIN DE LECTURA DE XML!*/
}


void Proyectil::dibuja(){
    if(aparece){
        Juego::Instance()->window->draw(spritePro);
        //std::cout<<"proyectil dibujado"<<std::endl;
    }
    disparoTime= proyectilClock.getElapsedTime().asSeconds(); //Tiempo que determina la velocidad del proyectil
    if(disparoTime>0.015){ //Cuanto mayor sea, mas lento ira el proyectil
        if(dir==1){//derecha
            spritePro.move(3.5,0);
            disRecorrida+=3.5;
        }
        if(dir==0){
            spritePro.move(-3.5,0);
            disRecorrida+=3.5;
        }
        proyectilClock.restart(); 
    }
    
}

bool Proyectil::destruir(){
    if(disRecorrida>300){
        //cout << "Proyectil destruido" << endl;
        return true;
    }else{
        return false;
    }
}

sf::Sprite Proyectil::getSprite(){
    return spritePro;
}

Proyectil Proyectil::crearPro(){
    
    disparoAparicion=0;
    disparoAparicion=proyectilClock.getElapsedTime().asSeconds();
    //Dependiendo de la direccion hacia donde este mirando, se aplica un sprite u otro
     if(dir==1){ //Derecha
         if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            spritePro.setOrigin(matriz[1][2]/4,matriz[1][3]/2);
            spritePro.setTextureRect(sf::IntRect(matriz[1][0], matriz[1][1], matriz[1][2], matriz[1][3]));
            //Al disparar, se genera un proyectil y se inserta en el vector
            //Proyectil *pro = new Proyectil(direccion, position);
            //std::cout << "posicion X proyectil reciente:" << pro->posx << std::endl;
            //proyectiles.push_back(pro);
           /****/
            //std::cout << "Hay: "<< proyectiles.size() << " proyectiles" << std::endl;
           /****/
            return *this;
         }    
     }

     if(dir==0){ //Izquierda
         if(disparoAparicion>0.35){
            //IMPORTANTE cambiar el centroide a la hora de atacar!
            spritePro.setOrigin(matriz[1][2]/1.325,matriz[1][3]/2);
            spritePro.setTextureRect(sf::IntRect(matriz[2][0], matriz[2][1], matriz[2][2], matriz[2][3]));
            //Al disparar, se genera un proyectil y se inserta en el vector
   //         Proyectil *pro = new Proyectil(direccion, position);
            //proyectiles.push_back(pro);
           /****/
            //std::cout << "Hay: "<< proyectiles.size() << " proyectiles" << std::endl;
           /****/
            return *this;
        }
    }


    
    
    
    
    
}
