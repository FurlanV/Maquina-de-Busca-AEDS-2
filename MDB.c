#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include "MDB.h"
#include "TADPatricia.h"
#include "TADLista.h"

void calculaPesoTermos(TArvore p,int nDocumentos)
{
    TCelula *celula;    
    int nTermosDocumento;
    if(p==NULL)
        return;
    
    if(!EExterno(p))
        calculaPesoTermos(p->NO.NInterno.Esq,nDocumentos);
    
    if(p != NULL && p->NoLista.tamanho > 0){
        celula = p->NoLista.lista.primeiro;
        nTermosDocumento = p->NoLista.tamanho;
        while(celula != NULL){
            celula->item.pesoTermo =((float)celula->item.qtdOcorrencias*((log2(nDocumentos))/nTermosDocumento));
            celula = celula->prox;
        }
    }
    
    if(!EExterno(p))
        calculaPesoTermos(p->NO.NInterno.Dir,nDocumentos);
    
}

TArvore montaIndiceInvertido(TArvore raiz,string *matrizArquivos)
{
    FILE *file;
    DIR *dir;
    struct dirent *lsdir;
    char diretorio[30],caminhoArquivo[50];
    string *palavra;
    int idDoc=1,nDocumentos,*contaPalavras,i;
    
    printf("Digite o caminho para a pasta onde estao os arquivos a serem lidos..\n");
    scanf("%s",&diretorio);
    strcpy(caminhoArquivo,diretorio);
    
    nDocumentos = contaArquivos(dir,lsdir,diretorio);
    nDoc = nDocumentos;
    
    contaPalavras = malloc(sizeof(int)*nDocumentos);
    
    for(i=0;i<nDocumentos;i++){
        
        if(i==0)
            contaPalavras[0] = 1;
        else
            contaPalavras[i] = 0;
    }
    
    dir = opendir(diretorio);
    strcat(diretorio,"/");
    if(dir){ 
        while((lsdir = readdir(dir))){
            
            if(strcmp(lsdir->d_name,".directory") && strcmp(lsdir->d_name,".") && strcmp(lsdir->d_name,"..")){
                strcat(diretorio,lsdir->d_name);
                matrizArquivos[idDoc-1] = lsdir->d_name;
                file = fopen(diretorio,"r");

                 while(!feof(file)){   
                     palavra = (string)malloc(sizeof(char)*30);
                    
                     fscanf(file,"%s ",palavra);
                     
                     if(raiz != NULL && pesquisaOcorrencia(palavra,raiz,idDoc) == FALSE)
                         contaPalavras[idDoc-1]++;
                     
                     raiz = Insere(palavra,&raiz,idDoc);                       
                     }
                    
                    idDoc++;
                    fclose(file);
                    strcpy(diretorio,caminhoArquivo);
                    strcat(diretorio,"/");
            }
        } 
        
        nPalavrasDistintas = contaPalavras;
    }
    else
        printf("ERRO ! Caminho nao encontrado!\n");    
    
    calculaPesoTermos(raiz,nDocumentos);  
    
    printf("\n");
    
        
    closedir(dir);
    return raiz;
}

int contaArquivos(DIR *dir,struct dirent *dirent,string diretorio)
{
    int nArquivos = 0;
    
    dir = opendir(diretorio);
    
    if(dir){
        while((dirent = readdir(dir))){
           if(strcmp(dirent->d_name,".directory") && strcmp(dirent->d_name,".") && strcmp(dirent->d_name,".."))
            nArquivos++;
        }
    }       
    
    closedir(dir);
    return nArquivos;
}

char **alocaMatrizString(char **matriz,int nStrings)
{
    int i;
  
    matriz = (char**)malloc(sizeof(char*)*nStrings);
    
    for(i=0; i<nStrings; i++)
         matriz[i]=(char*)malloc(sizeof(char)*nStrings);
    
    return matriz;
}

void menu()
{
    TArvore raiz = NULL;
    int opc = 1,nTermos,i,j;
    float *vetorPesos,*vetorRelevancia;
    string *strings;
    int maiorRelevancia;
    
    nomeArquivos = alocaMatrizString(nomeArquivos,nDoc);
    
    while(opc != 0){
        printf("1- Montar indice invertido | 2- Pesquisar termo | 3- Imprimir indice invertido | 0- sair\n");
        scanf("%d",&opc);
        
        switch(opc){
            case 1:
                raiz = montaIndiceInvertido(raiz,nomeArquivos);
                break;
            case 2:
                printf("Digite o numero de termos da Pesquisa\n");
                scanf("%d",&nTermos);
                
                vetorPesos = malloc(sizeof(float)*nDoc);
                vetorRelevancia = malloc(sizeof(float)*nDoc);
                strings = alocaMatrizString(strings,nTermos);
                
                for(i=0;i<nDoc;i++){
                    vetorPesos[i] = 0;
                    vetorRelevancia[i] = 0;
                }
                
                printf("digite o(s) termo(s) que voce deseja pesquisar separados por um 'ENTER'\n");
                
                for(i=0;i<nTermos;i++){
                    scanf("%s",strings[i]);
                }
                
                for(j=0;j<nDoc;j++){
                    for(i=0;i<nTermos;i++){
                        vetorPesos[j] += retornaPesoTermo(strings[i],raiz,j+1); //Faço a soma dos pesos de cada termo por documento e guardo no vetor na posicao nDoc-1
                    }
                }
                
                for(i=0;i<nDoc;i++){
                    vetorRelevancia[i] = (((float)1/nPalavrasDistintas[i])*vetorPesos[i]);//Cada soma de peso dos termos esta guardado na posicao nDoc-1
                }                                                                         //Logo faço os calculos necessarios para determinar a relevancia dos arquivos
                        
                for(i=0;i<nDoc;i++){
                    if(i==0)
                        maiorRelevancia = 0;
                    else{
                        if(vetorRelevancia[maiorRelevancia] < vetorRelevancia[i])
                            maiorRelevancia = i;
                    }
                    printf("Relevancia arquivo %d: %.2f\n",i+1,vetorRelevancia[i]);
                }
                
                printf("\n");
                printf("(%s)\n",nomeArquivos[maiorRelevancia]);
                
                if(maiorRelevancia == 0){
                        if(vetorRelevancia[1] > vetorRelevancia[2]){
                            printf("(%s)\n",nomeArquivos[1]);
                            printf("(%s)\n",nomeArquivos[2]);
                        }
                        else{
                            printf("(%s)\n",nomeArquivos[2]);
                            printf("(%s)\n",nomeArquivos[1]);
                        }
                }
                else if(maiorRelevancia == 1){
                    if(vetorRelevancia[0] > vetorRelevancia[2]){
                        printf("(%s)\n",nomeArquivos[0]);
                        printf("(%s)\n",nomeArquivos[2]);
                    }
                    else{
                        printf("(%s)\n",nomeArquivos[2]);
                        printf("(%s)\n",nomeArquivos[0]);
                    }
                }
                else{
                    if(vetorRelevancia[0] > vetorRelevancia[1]){
                        printf("(%s)\n",nomeArquivos[0]);
                        printf("(%s)\n",nomeArquivos[1]);
                    }
                    else{
                        printf("(%s)\n",nomeArquivos[1]);
                        printf("(%s)\n",nomeArquivos[0]);
                    }
                }
                
                printf("\n");
                
                break;
            case 3:
                imprimirOrdem(raiz);
                printf("\n");
                break;
            default:
                break;
        }
    }
}
