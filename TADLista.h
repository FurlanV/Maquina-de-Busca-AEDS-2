/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TADLista.h
 * Author: vinicius
 *
 * Created on 3 de Maio de 2016, 10:57
 */

#ifndef TADLISTA_H
#define TADLISTA_H

#ifdef __cplusplus
extern "C" {
#endif
    
typedef  char *String;
typedef  short boolean;

typedef struct{
    int idDoc;
    int qtdOcorrencias;
    float relevancia;
    float pesoTermo;
}TItem;

typedef struct{
    TItem item;
    struct TCelula *prox;
}TCelula;

typedef struct{
    TCelula *primeiro;
    TCelula *ultimo;
}TLista;

TCelula *alocaCelula();
TLista inicializaLista(TLista *lista);
void inserirLista(TLista *lista,TItem *item);
void imprimirLista(TLista *lista);
float somaPesos(TLista *lista);

#ifdef __cplusplus
}
#endif

#endif /* TADLISTA_H */


