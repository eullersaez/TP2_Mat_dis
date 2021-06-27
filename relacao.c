#include <stdio.h>
#include <stdlib.h>
#include <locale.h>                        //utilizacao da biblioteca locale.h para poder imprimir com acentos.


int busca_posicao(int a, int* vetor_nos){  //funcao recebe um inteiro e um vetor e retorna em qual posicao do vetor esse inteiro se encontra.
    int posicao = 0;
    int achou = 0;
    while(!achou){
        if(vetor_nos[posicao]==a){
            achou = 1;
        }else{
            posicao++;
        }
    }
    return posicao;
}

char testa_reflexiva(int num_nos, int matriz_de_adjacencia[][num_nos]){ //funcao testa se a relacao eh reflexiva checando se todos os elementos da diag. principal
    char resultado = 'V';                                               //da matriz de adjacencia sao == 1.
    for(int i=0; i<num_nos; i++){
        if(matriz_de_adjacencia[i][i]==0){
            resultado = 'F';
        }
    }
    return resultado;
}

char testa_irreflexiva(int num_nos, int matriz_de_adjacencia[][num_nos]){ //funcao testa se a relacao eh irreflexiva checando se todos os elementos da diag. principal
    char resultado = 'V';                                                 //da matriz de adjacencia sao == 0.
    for(int i=0; i<num_nos; i++){
        if(matriz_de_adjacencia[i][i]==1){
            resultado = 'F';
        }
    }
    return resultado;

}

char testa_simetrica(int num_nos, int matriz_de_adjacencia[][num_nos]){ //funcao testa se a relacao eh simetrica ao comparar a matriz de adjacencia com o equivalente a
    char resultado = 'V';                                               //sua transposta. caso seja igual para todos os elementos, entao sera simetrica.
    for(int i=0; i<num_nos; i++){
        for(int j=0; j<num_nos; j++){
            if(matriz_de_adjacencia[i][j] != matriz_de_adjacencia[j][i]){
                resultado = 'F';
            }
        }
    }
    return resultado;
}

char testa_anti_simetrica(int num_nos, int matriz_de_adjacencia[][num_nos]){ //funcao testa se a relacao eh anti-simetrica ao comparar se onde existe uma ligacao de x para y na matriz
    char resultado;                                                          //de adjacencia, existe tambem uma ligacao de y para x. caso exista e x!=y, entao retornara falso.
    resultado = 'V';
    for(int i=0; i<num_nos;i++){
        for(int j=0; j<num_nos; j++){
            if(matriz_de_adjacencia[i][j]==1){
                if(matriz_de_adjacencia[j][i]==1 && i!=j){
                    resultado = 'F';
                }
            }
        }
    }
    return resultado;
}

char testa_assimetrica(int num_nos, int matriz_de_adjacencia[][num_nos]){  //funcao testa se a relacao eh assimetrica ao percorrer toda a matriz de adjacemcia e verificar se quando existe
    char resultado;                                                        //uma ligacao de x para y nao existe nenhuma ligacao de y para x. caso isso seja valido, eh retornado verdadeiro.
    resultado = 'V';
    for(int i=0; i<num_nos;i++){
        for(int j=0; j<num_nos; j++){
            if(matriz_de_adjacencia[i][j]==1){
                if(matriz_de_adjacencia[j][i]==1){
                    resultado = 'F';
                }
            }
        }
    }
    return resultado;
}

char testa_transitiva(int num_nos, int matriz_de_adjacencia[][num_nos]){    //funcao testa se a relacao eh transitiva ao percorrer toda a matriz de adjacencia checando se em todos os casos
    char resultado;                                                         //quando ha a ligacao de um x para um y e um y para um z, nao ha a ligacao de x para z. caso seja valido, eh retormadp
    resultado = 'V';                                                        //falso.
    for(int i=0; i<num_nos;i++){
        for(int j=0; j<num_nos; j++){
            for(int z=0; z<num_nos; z++){
                if(matriz_de_adjacencia[i][j]==1){
                    if(matriz_de_adjacencia[j][z]==1){
                        if(matriz_de_adjacencia[i][z]==0){
                            resultado = 'F';
                        }
                    }
                }
            }
        }
    }
    return resultado;
}

int main(){

    setlocale(LC_ALL, "Portuguese");                       //habilita a acentuacao para portugues
    FILE * entrada;                                        //ponteiro para o arquivo de entrada "en.txt".
    entrada = fopen("entrada.txt", "r");

    int vetor_concatenado[1000];                           //vetor contendo todos os elementos do arquivo de modo concatenado.
    int i = 0;                                             //setando todos os  valores do vetor para -1 pois esta sera a condicao de parada para navegar ate o fim do vetor
    for(i; i<1000;i++){
        vetor_concatenado[i] = -1;
    }
    i=0;
    while(!feof(entrada)){                                  //leitura de todos os dados do arquivo sendo armazenado concatenando-os em um vetor.
        fscanf(entrada, "%i", &vetor_concatenado[i]);
        i++;
    }

    int num_nos = 0;
    num_nos = vetor_concatenado[0];                         //variavel que guarda o numero de nos entrados
    int vetor_nos[num_nos];

    for(i=0; i<=num_nos; i++){                              //armazenamento de nos em um vetor exclusivo para tal.
        vetor_nos[i] = vetor_concatenado[i+1];
    }

    int num_relacoes = 0;
    for(i=num_nos+1; vetor_concatenado[i]!=-1 ; i++){       //descobrindo o dobro do numero de ligacoes distintas para aloca-las em um vetor
        num_relacoes++;
    }

    int vetor_relacoes[num_relacoes];
    for(i=0; i<=num_relacoes; i++){                              //armazenamento de relacoes em um vetor exclusivo para tal.
        vetor_relacoes[i] = vetor_concatenado[i+num_nos+1];
    }

    int matriz_de_adjacencia[num_nos][num_nos];                 //setando todos os elementos da matriz de relacao para 0.
    int j=0;
    for(i=0; i<num_nos;i++){
        for(j=0; j<num_nos; j++){
            matriz_de_adjacencia[i][j] = 0;
        }
    }

    for(int aux=0; aux<num_relacoes; aux = aux+2){               //for percorre de 2 em 2 o vetor contendo as relacoes (ligacoes) ate o final. em cada etapa do for,
        i = busca_posicao(vetor_relacoes[aux], vetor_nos);       //atribui-se a i e j as posicoes que cada elemento do vetor que contem as ligacoes assume no vetor de nos
        j = busca_posicao(vetor_relacoes[aux+1], vetor_nos);     //e entao atribui-se 1 nessas posicoes da matriz de adjacencia para representar a ligacao de um x para um y.
        matriz_de_adjacencia[i][j] = 1;
    }


    printf("Reflexiva: %c\n", testa_reflexiva(num_nos, matriz_de_adjacencia));  //impressao do resultado para a relacao ser reflexiva.
    if(testa_reflexiva(num_nos, matriz_de_adjacencia) == 'F'){                  //imprime-se todos os pares x e x que deveriam estar ligados caso nao seja reflexiva.
        for(int i=0; i<num_nos; i++){
            if(matriz_de_adjacencia[i][i]==0){
                printf("(%i,%i); ", vetor_nos[i],vetor_nos[i]);
            }
        }
        printf("\n");
    }

    printf("Irreflexiva: %c\n", testa_irreflexiva(num_nos, matriz_de_adjacencia)); //impressao do resultado para a relacao ser irreflexiva.
    if(testa_irreflexiva(num_nos, matriz_de_adjacencia) == 'F'){                   //imprime-se todos os pares x e x que não deveriam estar ligados caso nao seja irreflexiva.
        for(int i=0; i<num_nos; i++){
            if(matriz_de_adjacencia[i][i]==1){
                printf("(%i,%i); ", vetor_nos[i],vetor_nos[i]);
            }
        }
        printf("\n");
    }

    printf("Simétrica: %c\n", testa_simetrica(num_nos, matriz_de_adjacencia));       //impressao do resultado para a relacao ser simetrica.
    if(testa_simetrica(num_nos, matriz_de_adjacencia) == 'F'){                       //imprime-se todos os pares y e x que deveriam ter uma relacao de x para y mas nao o tem, caso nao seja
        for(j=0; j<num_nos;j++){                                                     //simetrica.
            for(i=0;i<num_nos;i++){
                if(matriz_de_adjacencia[j][i]!=matriz_de_adjacencia[i][j] && matriz_de_adjacencia[j][i]==0){
                    printf("(%i,%i); ",vetor_nos[j],vetor_nos[i]);
                }
            }
        }
        printf("\n");
    }

    printf("Anti-simétrica: %c\n", testa_anti_simetrica(num_nos, matriz_de_adjacencia)); //impressao do resultado para a relacao ser anti-simetrica.
    if(testa_anti_simetrica(num_nos, matriz_de_adjacencia) == 'F'){                      //imprime-se todos os pares x e y que tem ligacao y e x quando x!=y, caso seja nao seja anti-simetrica
        for(i=0; i<num_nos;i++){
            for(j=0; j<num_nos; j++){
                if(matriz_de_adjacencia[i][j]==1){
                    if(matriz_de_adjacencia[j][i]==1 && i!=j){
                        printf("(%i,%i); ",vetor_nos[i],vetor_nos[j]);
                    }
                }
            }
        }
        printf("\n");
    }

    printf("Assimétrica: %c\n", testa_assimetrica(num_nos, matriz_de_adjacencia));   //impressao do resultado para a relacao ser assimetrica.

    printf("Transitiva: %c\n", testa_transitiva(num_nos, matriz_de_adjacencia));     //impressao do resultado para a relacao ser transitiva.
    if(testa_transitiva(num_nos, matriz_de_adjacencia) == 'F'){                      //cria-se uma matriz auxiliar de adjacencia para colocar todos os pares x e z que deveriam estar presentes
        int matriz_auxiliar_de_adjacencia[num_nos][num_nos];                         //para tornar a relacao transitiva, pois no caso ha uma ligacao de x para y e uma de y para z.
        for(i=0; i<num_nos;i++){                                                     //logo apos, imprime-se os pares x e z contidos na matriz auxiliar de adjacencia.
            for(j=0; j<num_nos; j++){
                matriz_auxiliar_de_adjacencia[i][j] = 0;
            }
        }
        for(int i=0; i<num_nos;i++){
            for(int j=0; j<num_nos; j++){
                for(int z=0; z<num_nos; z++){
                    if(matriz_de_adjacencia[i][j]==1){
                        if(matriz_de_adjacencia[j][z]==1){
                            if(matriz_de_adjacencia[i][z]==0){
                                matriz_auxiliar_de_adjacencia[i][z] = 1;

                            }
                        }
                    }
                }
            }
        }
        for(i=0;i<num_nos;i++){
            for(j=0;j<num_nos;j++){
                if(matriz_auxiliar_de_adjacencia[i][j] == 1){
                    printf("(%i,%i); ",vetor_nos[i],vetor_nos[j]);
                }
            }
        }
        printf("\n");
    }

    if(testa_reflexiva(num_nos, matriz_de_adjacencia)=='V' && testa_simetrica(num_nos, matriz_de_adjacencia)=='V' && testa_transitiva(num_nos, matriz_de_adjacencia)=='V'){ //teste para equivalencia
        printf("Relação de equivalência: V\n");
    }else{
        printf("Relação de equivalência: F\n");
    }

    if(testa_reflexiva(num_nos, matriz_de_adjacencia)=='V' && testa_anti_simetrica(num_nos, matriz_de_adjacencia)=='V' && testa_transitiva(num_nos, matriz_de_adjacencia)=='V'){ //teste para ordem parcial
        printf("Relação de ordem parcial: V\n");
    }else{
        printf("Relação de ordem parcial: F\n");
    }

    int matriz_auxiliar_de_adjacencia[num_nos][num_nos];            //processo semelhante ao de imprimir os pares x e z acima, no entanto apenas armazenando as ligacoes de x para z que deveriam estar
        for(i=0; i<num_nos;i++){                                    //presentes para tornar verdadeiro o fato da relacao ser transitiva, na matriz auxiliar de adjacencia.
            for(j=0; j<num_nos; j++){
                matriz_auxiliar_de_adjacencia[i][j] = 0;
            }
        }
        for(int i=0; i<num_nos;i++){
            for(int j=0; j<num_nos; j++){
                for(int z=0; z<num_nos; z++){
                    if(matriz_de_adjacencia[i][j]==1){
                        if(matriz_de_adjacencia[j][z]==1){
                            if(matriz_de_adjacencia[i][z]==0){
                                matriz_auxiliar_de_adjacencia[i][z] = 1;

                            }
                        }
                    }
                }
            }
        }

    for(i=0; i<num_nos;i++){                                            //soma da matriz auxiliar de adjacencia com a matriz de adjacencia adiciona as ligacoes necessarias de x para z
        for(j=0; j<num_nos; j++){                                       //de modo a tornar a relacao transitiva.
            matriz_de_adjacencia[i][j] = matriz_de_adjacencia[i][j] + matriz_auxiliar_de_adjacencia[i][j];
        }
    }
    printf("Fecho transitivo da relação: ");

    for(i=0;i<num_nos;i++){                                             //impressao do fecho transitivo da relacao que agora eh dado pela propria matriz de adjacencia, conforme explicado no
            for(j=0;j<num_nos;j++){                                     //passo anterior.
                if(matriz_de_adjacencia[i][j] == 1){
                    printf("(%i,%i); ",vetor_nos[i],vetor_nos[j]);
                }
            }
        }

    printf("\n");
    fclose(entrada);

    return 0;
}
