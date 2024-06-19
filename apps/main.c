#include "libraries.h"

int main(int argc, char const *argv[])
{
    char letra;
    char linha_arquivo[25], linha_peca[3], linha_acao[9], linha_peca2[3];
    int linha_x, linha_y, linha_tipo, linha_qtde, dim_x, dim_y, numero_fac, id;

    Dimension *dimensao = NULL;
    char **mapa_oficial, **mapa_faccao, **mapa_edificio, **mapa_unidade;
    mapa_oficial = mapa_faccao = mapa_edificio = mapa_unidade = NULL;

    //  Criando a cabeça da lista de facçôes
    CFaccao *cfaccao = cfaccao_cria();
    //  Abrindo arquivo de entrada
    FILE *arq = abrir_arquivo("./input/entrada3.txt", "r");
    //  Lendo o tamanho do tabuleiro e setando a dimensão
    fscanf(arq, "%d %d", &dim_x, &dim_y); 
    dimensao = sets_dimension(dim_x, dim_y);
    //  Construindo os mapas
    map_makes(&mapa_oficial, &mapa_faccao, &mapa_edificio, &mapa_unidade, dimensao);
    //  Pegando a quantidade de facções do arquivo 
    fscanf(arq,"%d", &numero_fac); 
   
   // Lendo o arquivo de entrada
    while(fgets(linha_arquivo, sizeof(linha_arquivo), arq) != NULL)
    {   
        sscanf(linha_arquivo, "%s %s", linha_peca, linha_acao);

        if(strcmp(linha_acao, "pos") == 0){
            letra = linha_peca[0];            
            
            if(letra == 'F'){ // Posicionamento de facção
                sscanf(linha_arquivo, "%*s %*s %d %d", &linha_x, &linha_y); 
                //  Insere a facção na lista e atualiza 'mapa_faccao'
                faccao_inserir(cfaccao, linha_peca, linha_x, linha_y); 
                faccao_mapa_atualiza(cfaccao, mapa_faccao, dimensao);

                gera_log(linha_acao, linha_peca, "", 0, 0, 0, linha_x, linha_y);

            } else { // Posicionamento de unidade
                id = ((int) linha_peca[1])-48;
                //  Pega o nome da facção e faz a busca dela na lista
                char aux[3];
                strcpy(aux, linha_peca);
                unidade_para_faccao(aux);
                TFaccao *faccao_aux = faccao_buscar(cfaccao, aux); 

                //  Lê o tipo, x e y da linha
                sscanf(linha_arquivo, "%*s %*s %d %d %d", &linha_tipo, &linha_x, &linha_y);

                //  Insere a unidade e atualiza 'mapa_unidade'
                faccao_unidade_inserir(faccao_aux, tolower(aux[1]), id, linha_tipo, linha_x, linha_y);   
                faccao_mapa_unidade_atualiza(cfaccao, mapa_oficial, mapa_unidade, dimensao); 

                gera_log(linha_acao, linha_peca, "", linha_tipo, 0, 0, linha_x, linha_y);
            }
        }

        if (strcmp(linha_acao,"move") == 0) // Movimentação de unidades
        {
            sscanf(linha_arquivo, "%*s %*s %d %d %d", &linha_tipo, &linha_x, &linha_y);
            
            faccao_unidade_move(cfaccao, mapa_unidade, dimensao, linha_peca, linha_tipo, linha_x, linha_y);
            faccao_mapa_unidade_atualiza(cfaccao, mapa_oficial, mapa_unidade, dimensao); 

            gera_log(linha_acao, linha_peca, "", linha_tipo, 0, 0, linha_x, linha_y);
        }

        if (strcmp(linha_acao, "coleta") == 0) // Coleta de pontos de recurso
        {
            sscanf(linha_arquivo, "%*s %*s %d %d", &linha_tipo, &linha_qtde);

            faccao_coleta(cfaccao, linha_peca[0], linha_qtde);

            gera_log(linha_acao, linha_peca, "", linha_tipo, 0, linha_qtde, 0, 0);
        }
        
        if (strcmp(linha_acao, "constroi") == 0) // Construção de edifícios
        {
            sscanf(linha_arquivo, "%*s %*s %d %d %d %d", &linha_qtde, &linha_tipo, &linha_x, &linha_y);

            faccao_edificio_constroi(cfaccao, mapa_edificio, linha_peca, linha_qtde, linha_tipo, linha_x,linha_y);

            gera_log(linha_acao, linha_peca, "", linha_tipo, 0, linha_qtde, linha_x, linha_y);
        }

        if(strcmp(linha_acao, "combate") == 0) // Combate entre unidades
        {
            int linha_tipo2;
            sscanf(linha_arquivo, "%*s %*s %d %s %d", &linha_tipo, linha_peca2, &linha_tipo2);

            faccao_unidade_combate(cfaccao, linha_peca2);

            gera_log(linha_acao, linha_peca, linha_peca2, linha_tipo, linha_tipo2, 0, 0, 0);
        }

        if(strcmp(linha_acao, "alianca") == 0) // Aliança entre facções
        {
            sscanf(linha_arquivo, "%*s %*s %s", linha_peca2);
            
            faccao_alianca(cfaccao, linha_peca, linha_peca2);

            gera_log(linha_acao, linha_peca, linha_peca2, 0, 0, 0, -1, -1);
        } 
        
        if(strcmp(linha_acao, "ataca") == 0) // Ataque de facção
        {
            sscanf(linha_arquivo, "%*s %*s %s %d %d", linha_peca2, &linha_x, &linha_y);
            
            faccao_ataca(cfaccao, linha_peca, linha_peca2, linha_x, linha_y);     
        }

        if(strcmp(linha_acao, "ganha") == 0) // Coleta de pontos de poder de facções
        {
            sscanf(linha_arquivo, "%*s %*s %d", &linha_qtde);
            
            faccao_ganha_pontos_poder(cfaccao, linha_peca, linha_qtde);

            gera_log(linha_acao, linha_peca, "", 0, 0, linha_qtde, 0, 0);
        }  
    }
    
    //Fechando o arquivo
    fclose(arq);

    /*  Visualizaçãp final dos mapas */
    puts("\nMAPA FACCAO");
    map_display(mapa_faccao, dimensao);
    puts("\nMAPA UNIDADE");
    map_display(mapa_unidade, dimensao);
    puts("\nMAPA EDIFICIO");
    map_display(mapa_edificio, dimensao);

    /*  Verifica a facção vencedora */
    faccao_verifica_vencedor(cfaccao);
    
    /*  Área de desalocação de memória */
    map_deallocates(&mapa_oficial, dimensao);
    map_deallocates(&mapa_faccao, dimensao);
    map_deallocates(&mapa_edificio, dimensao);
    map_dimension_deallocates(&dimensao);   
    cfaccao_desaloca(&cfaccao);

    return 0;
}