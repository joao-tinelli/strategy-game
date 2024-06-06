#include "bibliotecas.h"

FILE *abrir_arquivo(char *path_arquivo, char *operacao);
void construir_mapas(char ***mapa_oficial, char ***mapa_faccao, char ***mapa_edificio, char ***mapa_unidade, Dimensao *dimensao);

int main(int argc, char const *argv[])
{
    char letra;
    char linha_arquivo[25], linha_peca[3], linha_acao[9];
    int linha_x, linha_y, linha_tipo, linha_qtde, dim_x, dim_y, numero_fac, id;

    Dimensao *dimensao = NULL;
    char **mapa_oficial, **mapa_faccao, **mapa_edificio, **mapa_unidade;
    mapa_oficial = mapa_faccao = mapa_edificio = mapa_unidade = NULL;

    //  Criando a cabeça da  lista de facçôes
    CFaccao *cfaccao = Cfaccao_cria();
    //  Abrir arquivo de entrada
    FILE *arq = abrir_arquivo("./input/entrada.txt", "r");
    //  Lendo o tamanho do tabuleiro e setando a dimensão
    fscanf(arq, "%d %d", &dim_x, &dim_y); 
    dimensao = seta_dimensao(dim_x, dim_y);
    //  Construindo os mapas
    construir_mapas(&mapa_oficial, &mapa_faccao, &mapa_edificio, &mapa_unidade, dimensao);
    //  Pegando a quantidade de faccoes do arquivo 
    fscanf(arq,"%d", &numero_fac); 
   
    while(fgets(linha_arquivo, sizeof(linha_arquivo), arq) != NULL)
    {   
        sscanf(linha_arquivo, "%s %s", linha_peca, linha_acao);
        if(strcmp(linha_acao, "pos") == 0){
            letra = linha_peca[0];            
            
            if(letra == 'F'){ // posicionamento de faccao
                sscanf(linha_arquivo, "%*s %*s %d %d", &linha_x, &linha_y); 
                //  Insere a facção na lista e atualiza 'mapa_faccao'
                faccao_inserir(cfaccao, linha_peca, linha_x, linha_y); 
                mapa_faccao_atualiza(cfaccao, mapa_faccao, dimensao);
            } else { // posicionamento de unidade
                ///printf("%s\n", linha_peca);
                id = ((int) linha_peca[1])-48;
                //  Monta o nome da facção e faz a busca ela na lista
                linha_peca[1] = linha_peca[0];
                linha_peca[0] = 'F';
                TFaccao *faccao_aux = faccao_buscar(cfaccao, linha_peca); 
                //  Lê o TIPO, X e Y da linha
                sscanf(linha_arquivo, "%*s %*s %d %d %d", &linha_tipo, &linha_x, &linha_y);
                //  Insere a unidade e atualiza 'mapa_unidade'
                faccao_unidade_inserir(faccao_aux, tolower(linha_peca[1]), id, linha_tipo, linha_x, linha_y);   
                mapa_faccao_unidade_atualiza(cfaccao, mapa_unidade, dimensao); 
            }
        }
        if(strcmp(linha_acao,"move") == 0)
        {
            sscanf(linha_arquivo, "%*s %*s %d %d %d", &linha_tipo, &linha_x, &linha_y);
            printf("\n%d %d %d", linha_tipo, linha_x, linha_y);
            
            linha_peca[1] = linha_peca[0];    
            linha_peca[0] = 'F';

            faccao_unidade_move(cfaccao, linha_peca, linha_tipo, linha_x, linha_y);
            mapa_faccao_unidade_atualiza(cfaccao, mapa_unidade, dimensao); 

            puts("\nMAPA UNIDADE");
            mapa_display(mapa_unidade, dimensao);
        }
        /*
         if(strcmp(linha_acao,"coleta")==0)
        {
           fscanf(arq,"%d %d", &linha_x, &linha_y);
           printf("\n%d %d",linha_x,linha_y);
        }
         if(strcmp(linha_acao,"constroi")==0)
        {
           fscanf(arq,"%d %d %d %d", &linha_x, &linha_y, &linha_tipo,&linha_qtde);
           printf("\n%d %d %d %d",linha_x,linha_y,linha_tipo,linha_qtde);
        }
         if(strcmp(linha_acao,"combate")==0)
        {
           char s3[3];
           fscanf(arq,"%d %s", &linha_x,s3);
           printf("\n%d %s",linha_x,s3);
        }
        //ataca - vence - ganha - defende - perde
        */    
    }
    //Fechando o arquivo
    fclose(arq);

    //puts("\nMAPA FACCAO");
    //mapa_display(mapa_faccao, dimensao);
    
    
    /*  Area de desalocação */
    desaloca_mapa(&mapa_oficial, dimensao);
    desaloca_mapa(&mapa_faccao, dimensao);
    desaloca_mapa(&mapa_edificio, dimensao);
    desaloca_dimensao(&dimensao);   
    cfaccao_desaloca(&cfaccao);

    return 0;
}


FILE *abrir_arquivo(char *path_arquivo, char *operacao) 
{
    FILE *arq = fopen(path_arquivo, operacao);
    if (arq == NULL)
    {
        msg_erro("Erro ao abrir arquivo.", "abrir_arquivo");
        return NULL;
    }  

    return arq;
}

void construir_mapas(char ***mapa_oficial, char ***mapa_faccao, char ***mapa_edificio, char ***mapa_unidade, Dimensao *dimensao)
{
    *mapa_oficial = mapa_aloca(dimensao);    
    mapa_gera(*mapa_oficial, dimensao);

    *mapa_faccao = mapa_aloca(dimensao);
    mapa_replica(*mapa_oficial, *mapa_faccao, dimensao);

    *mapa_edificio = mapa_aloca(dimensao);
    mapa_replica(*mapa_oficial, *mapa_edificio, dimensao);

    *mapa_unidade = mapa_aloca(dimensao);
    mapa_replica(*mapa_oficial, *mapa_unidade, dimensao);
}