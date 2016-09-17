#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TADLista.h"

TLista inicializaLista(TLista *lista)
{
    lista->primeiro = alocaCelula();
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}

TCelula *alocaCelula()
{
    return (TCelula*)malloc(sizeof(TCelula));
}

void inserirLista(TLista *lista,TItem *item)
{
    TCelula *novaCelula;
    
    novaCelula = alocaCelula();
    novaCelula->item = *item;
    novaCelula->prox = NULL;
    
    lista->ultimo->prox  = novaCelula;
    lista->ultimo = novaCelula;
}

void imprimirLista(TLista *lista)
{
    TCelula *celulaAux;
    celulaAux = lista->primeiro->prox;
    
    while (celulaAux != NULL)
    {
        if(celulaAux->prox == NULL)
            printf("[%d,%d]\n",celulaAux->item.qtdOcorrencias,celulaAux->item.idDoc);
            //printf("[%d,%d][%.1f]\n",celulaAux->item.qtdOcorrencias,celulaAux->item.idDoc,celulaAux->item.pesoTermo);
            //printf("[%d,%d][%.2f][%.2f]\n",celulaAux->item.qtdOcorrencias,celulaAux->item.idDoc,celulaAux->item.pesoTermo);
        else
            printf("[%d,%d] -> ",celulaAux->item.qtdOcorrencias,celulaAux->item.idDoc);
            //printf("[%d,%d][%.1f] -> ",celulaAux->item.qtdOcorrencias,celulaAux->item.idDoc,celulaAux->item.pesoTermo);
            //printf("[%d,%d][%.2f][%.2f] ->",celulaAux->item.qtdOcorrencias,celulaAux->item.idDoc,celulaAux->item.pesoTermo);
        
        celulaAux = celulaAux->prox;
    }
}

float somaPesos(TLista *lista)
{
    float somaPesos;
    TCelula *celula;
    
    if(lista){
        celula = lista->primeiro->prox;
        while(celula != NULL){
            somaPesos += (float)celula->item.pesoTermo;
            celula = celula->prox;
        }
    }
    
    return(somaPesos);
}
