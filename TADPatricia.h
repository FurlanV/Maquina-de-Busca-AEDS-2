#include "TADLista.h"

#ifndef TADPATRICIA_H
#define TADPATRICIA_H

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE !TRUE
#define D 8

typedef  char *string;
typedef  short boolean;

typedef enum
{
  Interno, Externo
} TipoNo;

typedef struct TipoPatNo *TArvore;
typedef struct TipoPatNo
{
    TipoNo nt;
    union
    {
      String Chave; 
      struct{
            short Index;
            char Caractere;
            TArvore Esq, Dir;
        } NInterno;
    } NO;
    
    struct{
        TLista lista;
        int tamanho;
    }NoLista;
    
} TipoPatNo;

char Caractere(short i, String k);
boolean MenorIgual(char a, char b);
boolean EExterno(TArvore p);
TArvore CriaNoInt(short i, TArvore *Esq,  TArvore *Dir, char Caractere);
TArvore CriaNoExt(String k,int idDoc);
boolean pesquisaOcorrencia(String k, TArvore t,int idDoc);
float retornaPesoTermo(String k, TArvore t,int idDoc);
void imprimirNo(TArvore no);
void imprimirOrdem(TArvore ap);
TArvore InsereEntre(String k, TArvore *t, short i,int idDoc);
TArvore Insere(String k, TArvore *t,int idDoc);

string *nomeArquivos;
int *nPalavrasDistintas;
int nDoc;

#ifdef __cplusplus
}
#endif

#endif /* TADPATRICIA_H */


