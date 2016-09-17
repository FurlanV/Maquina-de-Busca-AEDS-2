/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MDB.h
 * Author: vinicius
 *
 * Created on 3 de Maio de 2016, 21:16
 */

#ifndef MDB_H
#define MDB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <dirent.h>   
#include "TADPatricia.h"


void menu();
int contaArquivos(DIR *dir,struct dirent *dirent,string diretorio);
TArvore montaIndiceInvertido(TArvore raiz,string *matrizArquivos);
void calculaPesoTermos(TArvore p,int nDocumentos);
void calculaRelevanciaDocumento(TArvore p,int nTermosDistintos[],int i);
char **alocaMatrizString(char **matriz,int nStrings);

#ifdef __cplusplus
}
#endif

#endif /* MDB_H */


