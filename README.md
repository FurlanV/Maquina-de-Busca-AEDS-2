# Maquina-de-Busca-com-Patricia
 
Máquinas de busca, tais como Google, Bing, Yahoo, trabalham com a busca de
palavras-chave em textos armazenados na Web. Para que os documentos contendo os
termos sejam recuperados, os mesmos precisam ser devidamente indexados à priori.
Nesse contexto, são utilizadas estruturas de dados que facilitem a recuperação das
informações, como é o caso do uso de arquivos invertidos. Dada uma coleção de
documentos, um índice invertido é uma estrutura contendo uma entrada para cada
palavra (termo de busca) que aparece em, pelo menos, um dos documentos. Essa entrada
associa a cada palavra do texto um ou mais pares do tipo <qtde, idDoc>, onde qtde
corresponde ao número de vezes em que a palavra em questão apareceu em um
determinado documento identificado por idDoc. Tais estruturas de índices são
comumente implementadas com base em árvores e tabelas hash, pois as mesmas não
precisam ser reconstruídas a cada atualização
