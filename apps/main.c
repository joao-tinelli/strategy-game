#include "bibliotecas.h"


int main(int argc, char const *argv[])
{
    char letra;
    char linha_arquivo[25], linha_peca[3], linha_acao[9], linha_peca2[3];
    int linha_x, linha_y, linha_tipo, linha_qtde, dim_x, dim_y, numero_fac, id;

    Dimensao *dimensao = NULL;
    char **mapa_oficial, **mapa_faccao, **mapa_edificio, **mapa_unidade;
    mapa_oficial = mapa_faccao = mapa_edificio = mapa_unidade = NULL;

    //  Criando a cabeça da  lista de facçôes
    CFaccao *cfaccao = Cfaccao_cria();
    //  Abrir arquivo de entrada
    FILE *arq = abrir_arquivo("./input/entrada3.txt", "r");
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

                gera_log(linha_acao, linha_peca, "", 0, 0, 0, linha_x, linha_y);
            } else { // posicionamento de unidade
                id = ((int) linha_peca[1])-48;
                //  Monta o nome da facção e faz a busca ela na lista
                char aux[3];
                strcpy(aux, linha_peca);
                unidade_para_faccao(aux);
                TFaccao *faccao_aux = faccao_buscar(cfaccao, aux); 
                //  Lê o TIPO, X e Y da linha
                sscanf(linha_arquivo, "%*s %*s %d %d %d", &linha_tipo, &linha_x, &linha_y);
                //  Insere a unidade e atualiza 'mapa_unidade'
                faccao_unidade_inserir(faccao_aux, tolower(aux[1]), id, linha_tipo, linha_x, linha_y);   
                faccao_mapa_unidade_atualiza(cfaccao, mapa_oficial, mapa_unidade, dimensao); 

                gera_log(linha_acao, linha_peca, "", linha_tipo, 0, 0, linha_x, linha_y);
            }
        }
        if (strcmp(linha_acao,"move") == 0)
        {
            sscanf(linha_arquivo, "%*s %*s %d %d %d", &linha_tipo, &linha_x, &linha_y);
            
            faccao_unidade_move(cfaccao, mapa_unidade, dimensao, linha_peca, linha_tipo, linha_x, linha_y);
            faccao_mapa_unidade_atualiza(cfaccao, mapa_oficial, mapa_unidade, dimensao); 

            gera_log(linha_acao, linha_peca, "", linha_tipo, 0, 0, linha_x, linha_y);
        }

        if (strcmp(linha_acao, "coleta") == 0) // !!!!!!!!!!
        {
            sscanf(linha_arquivo, "%*s %*s %d %d", &linha_tipo, &linha_qtde);

            faccao_coleta(cfaccao, linha_peca[0], linha_qtde);

            gera_log(linha_acao, linha_peca, "", linha_tipo, 0, linha_qtde, 0, 0);
        }
        
        if (strcmp(linha_acao, "constroi") == 0)
        {
            sscanf(linha_arquivo, "%*s %*s %d %d %d %d", &linha_qtde, &linha_tipo, &linha_x, &linha_y);

            faccao_edificio_constroi(cfaccao, mapa_edificio, linha_peca, linha_qtde, linha_tipo, linha_x,linha_y);

            gera_log(linha_acao, linha_peca, "", linha_tipo, 0, linha_qtde, linha_x, linha_y);
        }

        if(strcmp(linha_acao, "combate") == 0)
        {
            int linha_tipo2;
            sscanf(linha_arquivo, "%*s %*s %d %s %d", &linha_tipo, linha_peca2, &linha_tipo2);

            faccao_unidade_combate(cfaccao, linha_peca2);

            gera_log(linha_acao, linha_peca, linha_peca2, linha_tipo, linha_tipo2, 0, 0, 0);
        }
        
        if(strcmp(linha_acao, "ataca") == 0)
        {
            sscanf(linha_arquivo, "%*s %*s %s %d %d", linha_peca2, &linha_x, &linha_y);
            
            faccao_ataca(cfaccao, linha_peca, linha_peca2, linha_x, linha_y);     
        }

        if(strcmp(linha_acao, "ganha") == 0)
        {
            sscanf(linha_arquivo, "%*s %*s %d", &linha_qtde);
            
            faccao_ganha_postos_poder(cfaccao, linha_peca, linha_qtde);

            gera_log(linha_acao, linha_peca, "", 0, 0, linha_qtde, 0, 0);
        }  
    }
    //Fechando o arquivo
    fclose(arq);

    /*  Visualizaçãp final dos mapas */
    puts("\nMAPA FACCAO");
    mapa_display(mapa_faccao, dimensao);
    puts("\nMAPA UNIDADE");
    mapa_display(mapa_unidade, dimensao);
    puts("\nMAPA EDIFICIO");
    mapa_display(mapa_edificio, dimensao);

    /*  verifica a faccao ganhadora */
    faccao_verifica_vencedor(cfaccao);
    
    /*  Area de desalocação */
    desaloca_mapa(&mapa_oficial, dimensao);
    desaloca_mapa(&mapa_faccao, dimensao);
    desaloca_mapa(&mapa_edificio, dimensao);
    desaloca_dimensao(&dimensao);   
    cfaccao_desaloca(&cfaccao);

    return 0;
}