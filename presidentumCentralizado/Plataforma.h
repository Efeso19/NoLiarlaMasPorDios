/* 
 * File:   Plataforma.h
 * Author: Aitor
 *
 * Created on 19 de abril de 2016, 17:52
 */

#ifndef PLATAFORMA_H
#define	PLATAFORMA_H
#include <SFML/Graphics.hpp>

class Plataforma {
public:
    Plataforma(int x, int y, int numMapa, int tipo);
    Plataforma(const Plataforma& orig);
    virtual ~Plataforma();
    
    sf::Sprite spritePlat;
    sf::Texture texPlat;
    void move();
    void romperPlataforma();
    void regeneracionPlataforma();
    
    int direccion;
    int tipo; //0 horizontal, 1 vertical, 2 rompible
    bool rota;
    int romper;
    float tiempoRotura;
private:
    int posx;
    int posy;
    float recorrido;
    
    
    
    sf::Clock tiempoRecorrido;
    float tiempo;
    
    sf::Color colorInicial;

};

#endif	/* PLATAFORMA_H */

