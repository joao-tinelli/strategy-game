#include "bibliotecas.h"

int main(int argc, char const *argv[])
{
    FILE *arq = NULL;
    char s1[3], s2[9], letra;
    int v1, v2, v3, v4, linhas, colunas, fac;
    arq = fopen("./input/entrada.txt", "r");

    if (arq == NULL)
    {
        msg_erro("Erro ao abrir arquivo", "main");
        return 1;
    }    

    Dimensao *dimensao = NULL;
    char **mapa_oficial = NULL;
    char **mapa_faccao = NULL;
    char **mapa_edificio = NULL;
    char **mapa_unidade = NULL;

    fscanf(arq, "%d %d", &linhas, &colunas); // lendo o tamanho do tabuleiro

    dimensao = seta_dimensao(linhas, colunas);
    mapa_oficial = mapa_aloca(dimensao);    
    mapa_gera(mapa_oficial, dimensao); // gerando mapa oficial

    mapa_faccao = mapa_aloca(dimensao);
    mapa_replica(mapa_oficial, mapa_faccao, dimensao);

    mapa_edificio = mapa_aloca(dimensao);
    mapa_replica(mapa_oficial, mapa_edificio, dimensao);

    mapa_unidade = mapa_aloca(dimensao);
    mapa_replica(mapa_oficial, mapa_unidade, dimensao);


    CFaccao *cfaccao = Cfaccao_cria();
    fscanf(arq,"%d", &fac); //quantidade de faccoes ok
   
    while(!feof(arq))
    {
        fscanf(arq,"%s %s", s1, s2);        
        
        if(strcmp(s2,"pos") == 0){
            letra = s1[0];            
            
            if(letra == 'F'){ // posicionamento de faccao
                fscanf(arq,"%d %d", &v1, &v2); // x y
                faccao_inserir(cfaccao, s1, v1, v2); 
                mapa_faccao_atualiza(cfaccao, mapa_faccao, dimensao);

            } else { // posicionamento de unidade
            
                fscanf(arq,"%d %d %d", &v1, &v2, &v3); // tipo, x, y
    
                printf("%d %d %d\n", v1, v2, v3);
                int id = (int) s1[1];
                s1[1] = s1[0];
                s1[0] = 'F';

    

                printf("%c, %c", s1[0], s2[0]);

                TFaccao *faccao_aux = faccao_buscar(cfaccao, s1);            
                
                s1[1] = tolower(s1[1]);
                
        
                faccao_unidade_inserir(faccao_aux, s1[1], id, v1, v2, v3);    
                mapa_unidade[v2][v3] = s1[1];    
                //mapa_faccao_unidade_atualiza(cfaccao, mapa_unidade, dimensao); 
                           
            }
        }

        /*
        if(strcmp(s2,"move")==0)
        {
           fscanf(arq,"%d %d %d", &v1, &v2, &v3);
           printf("\n%d %d %d",v1,v2,v3);
        }
         if(strcmp(s2,"coleta")==0)
        {
           fscanf(arq,"%d %d", &v1, &v2);
           printf("\n%d %d",v1,v2);
        }
         if(strcmp(s2,"constroi")==0)
        {
           fscanf(arq,"%d %d %d %d", &v1, &v2, &v3,&v4);
           printf("\n%d %d %d %d",v1,v2,v3,v4);
        }
         if(strcmp(s2,"combate")==0)
        {
           char s3[3];
           fscanf(arq,"%d %s", &v1,s3);
           printf("\n%d %s",v1,s3);
        }
        //ataca - vence - ganha - defende - perde
        */        
    }

    fclose(arq);
    mapa_display(mapa_faccao, dimensao);
    puts("");
    mapa_display(mapa_unidade, dimensao);
    
    // ok
    desaloca_mapa(&mapa_oficial, dimensao);
    desaloca_mapa(&mapa_faccao, dimensao);
    desaloca_mapa(&mapa_edificio, dimensao);
    desaloca_dimensao(&dimensao);   
    cfaccao_desaloca(&cfaccao);

    return 0;
}
