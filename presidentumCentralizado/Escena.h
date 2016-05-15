/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Escena.h
 * Author: chiri
 *
 * Created on 5 de abril de 2016, 20:16
 */

#ifndef ESCENA_H
#define ESCENA_H


class Escena {
public:
    Escena();
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Handle() = 0;
    virtual ~Escena();
    bool initState;
    
};

#endif /* ESCENA_H */