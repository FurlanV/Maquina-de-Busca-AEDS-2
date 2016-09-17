#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADPatricia.h"

char Caractere(short i, String k)
{
    /* Retorna o i-esimo Caractere da chave k a partir da esquerda */
    return i > strlen(k)? NULL: k[i];
}
boolean MenorIgual(char a, char b)
{
    if(a == NULL)
       return NULL;
    if( b == NULL)
       return NULL;
    return a <= b ? TRUE:FALSE;
}
boolean EExterno(TArvore p)
{
    /* Verifica se p^ e nodo externo */
    return (p->nt == Externo)?TRUE:FALSE;
}

TArvore CriaNoInt(short i, TArvore *Esq,  TArvore *Dir, char Caractere)
{
    TArvore p;
    p = (TArvore)malloc(sizeof(TipoPatNo));
    p->nt = Interno;
    p->NO.NInterno.Esq = *Esq;
    p->NO.NInterno.Dir = *Dir;
    p->NO.NInterno.Index = i;
    p->NO.NInterno.Caractere = Caractere;
    return p;
}

TArvore CriaNoExt(String k,int idDoc)
{
    TArvore p;
    TItem x;
    
    x.idDoc = idDoc;
    x.qtdOcorrencias = 1;
    x.relevancia = 0;
    
    p = (TArvore)malloc(sizeof(TipoPatNo));
    p->nt = Externo;
    p->NO.Chave = k;  
    
    inicializaLista(&(p->NoLista.lista));
    inserirLista(&(p->NoLista.lista),&x);
    p->NoLista.tamanho = 1;
    return p;
}

boolean pesquisaOcorrencia(String k, TArvore t,int idDoc)
{
    TCelula *celula;
    
    if (EExterno(t))
    {
        celula = t->NoLista.lista.primeiro->prox;
        if (strncmp(k,t->NO.Chave,strlen(k)) == 0){
            while(celula){
                if(celula->item.idDoc == idDoc)
                    return TRUE;
                else
                    celula = celula->prox;
            }
            
            if(celula == NULL)
                return FALSE;
        }
       else{
          return FALSE;
       }
    }
    if (MenorIgual(Caractere(t->NO.NInterno.Index, k),t->NO.NInterno.Caractere))
        return pesquisaOcorrencia(k, t->NO.NInterno.Esq,idDoc);
    else 
        return pesquisaOcorrencia(k, t->NO.NInterno.Dir,idDoc);

}

float retornaPesoTermo(String k, TArvore t,int idDoc)
{
    TCelula *celula;
    
    if (EExterno(t))
    {
        celula = t->NoLista.lista.primeiro->prox;
        if (strncmp(k,t->NO.Chave,strlen(k)) == 0){
            while(celula){
                if(celula->item.idDoc == idDoc)
                    return celula->item.pesoTermo;
                else
                    celula = celula->prox;
            }
            
            if(celula == NULL)
                return 0;
        }
       else{
          return 0;
       }
    }
    if (MenorIgual(Caractere(t->NO.NInterno.Index, k),t->NO.NInterno.Caractere))
        return retornaPesoTermo(k, t->NO.NInterno.Esq,idDoc);
    else 
        return retornaPesoTermo(k, t->NO.NInterno.Dir,idDoc);
    
}

void imprimirNo(TArvore no)
{
    if(no == NULL)
        printf("No Nulo\n");
    else if(no->nt == Externo)
    {
        printf("Palavra: %s -> ",no->NO.Chave);
        imprimirLista(&(no->NoLista.lista));
    }
    //else
        //printf(" Interno :%c,%d\n",no->NO.NInterno.Caractere,no->NO.NInterno.Index);
}

// Percurso da árvore
void imprimirOrdem(TArvore ap)
{

    if(ap == NULL)
        return;
    if(!EExterno(ap))
        imprimirOrdem(ap->NO.NInterno.Esq);
    
    imprimirNo(ap);
    
    if(!EExterno(ap))
        imprimirOrdem(ap->NO.NInterno.Dir);
}

TArvore InsereEntre(String k, TArvore *t, short i,int idDoc)
{
    TArvore p;
    char caractere;
    if (EExterno(*t) || i < (*t)->NO.NInterno.Index){
        /* cria um novo no externo */
        if(EExterno(*t)){
           caractere = Caractere(i,(*t)->NO.Chave);
        }
        else{
          caractere = (*t)->NO.NInterno.Caractere;
        }
        p = CriaNoExt(k,idDoc);
        if (MenorIgual(Caractere(i,k),caractere))
            return (CriaNoInt(i,&p,t,Caractere(i, k)));
        else 
            return (CriaNoInt(i,t,&p,caractere));
    }
    else{
        if (MenorIgual(Caractere((*t)->NO.NInterno.Index, k),(*t)->NO.NInterno.Caractere))
            (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i,idDoc);
        else
            (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i,idDoc);
        
        return (*t);
    }
}

TArvore Insere(String k, TArvore *t,int idDoc)
{
    TArvore p;
    int i;
    TCelula *celula;
    TItem item;
    
    if (*t == NULL){
        return (CriaNoExt(k,idDoc));
    }
    else{
        
        p = *t;
        
        while (!EExterno(p)){
            if (MenorIgual(Caractere(p->NO.NInterno.Index,k),p->NO.NInterno.Caractere))
                p = p->NO.NInterno.Esq;
            else 
                p = p->NO.NInterno.Dir;
        }
        
        /* acha o primeiro Caractere diferente */
        i = 0;
        if(strlen(k)>=strlen(p->NO.Chave)){
              while ((i <= strlen(k)) && (Caractere(i,k) == Caractere(i,p->NO.Chave)))
                i++;
        
              if (i >= strlen(k)){
                    celula = p->NoLista.lista.primeiro;
                  
                    if(celula->item.idDoc == idDoc){
                      celula->item.qtdOcorrencias++;
                    }
                  else{
                      while(celula->prox != NULL && celula->item.idDoc != idDoc)
                          celula = celula->prox;
                      
                      if(celula->item.idDoc == idDoc)
                          celula->item.qtdOcorrencias++;
                      else{
                          if(celula->item.idDoc != idDoc && celula->prox == NULL){
                            item.idDoc = idDoc;
                            item.qtdOcorrencias = 1;
                            item.relevancia = 0;
                            inserirLista(&(p->NoLista.lista),&item);
                            p->NoLista.tamanho++;
                          }
                        }
                    }
                return (*t);
            }
            else 
                return (InsereEntre(k, t, i,idDoc));      
            }               
            else{
              while ((i <= strlen(p->NO.Chave)) && (Caractere(i, k) == Caractere(i, p->NO.Chave)))
                i++;
        
              if (i >= strlen(p->NO.Chave)){
                    celula = p->NoLista.lista.primeiro;
                  
                    if(celula->item.idDoc == idDoc){
                      celula->item.qtdOcorrencias++;
                    }
                    else{
                      while(celula->prox != NULL && celula->item.idDoc != idDoc)
                          celula = celula->prox;
                      
                      if(celula->item.idDoc == idDoc)
                          celula->item.qtdOcorrencias++;
                      else{
                          if(celula->item.idDoc != idDoc && celula->prox == NULL){
                            item.idDoc = idDoc;
                            item.qtdOcorrencias = 1;
                            item.relevancia = 0;
                            inserirLista(&(p->NoLista.lista),&item);
                            p->NoLista.tamanho++;
                          }
                      }
                  }
                    return (*t);
            }
            else 
                return (InsereEntre(k, t, i,idDoc));
        }
    }
}
