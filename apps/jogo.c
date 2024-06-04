#include "bibliotecas.h"

int main(int argc, char const *argv[])
{
    int opt;
    Dimensao *dimensao = NULL;
    char **mapa_oficial = NULL;
    char **mapa_faccao = NULL;
    char **mapa_edificio = NULL;
    char **mapa_unidade = NULL;

    CFaccao *cfaccao = Cfaccao_cria();

    while(1)
    {
        puts("------STRATEGY GAME------");
        puts("Escolha uma opcao:");
        puts("1-Inicializar jogo padrao");
        puts("2-Inicializar jogo manualmente");
        puts("3-Encerrar jogo");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:            
            dimensao = mapa_le_dimensao("./input/config.txt");
            if(mapa_vazio(mapa_oficial, dimensao)){
                mapa_oficial = mapa_aloca(dimensao);
                mapa_gera(mapa_oficial, dimensao);

                faccoes_converte_txt_lista(cfaccao, "./input/faccoes.txt");
                mapa_faccao = mapa_aloca(dimensao);
                mapa_replica(mapa_oficial, mapa_faccao, dimensao);
                mapa_faccao_atualiza(cfaccao, mapa_faccao, dimensao);

            } else {
                puts("Mapa ja criado!");
            }                

            break;

        case 2:
            int n, m;
            puts("Informe a dimensao do mapa");
            scanf("%d%d", &n, &m);
            if (n <= 0 || m <= 0)
            {
                msg_erro("Dimensao invalida", "Inicializacao manual");
                break;
            }
            dimensao = seta_dimensao(n, m);
            if(mapa_vazio(mapa_oficial, dimensao))
            {
                mapa_oficial = mapa_aloca(dimensao);
                mapa_gera(mapa_oficial, dimensao);

                int n_facccoes, i;
                puts("Informe o numero de faccoes");
                scanf("%d", &n_facccoes);
                for (i = 0; i < n_facccoes; i++)
                {
                    char nome[3];
                    printf("Informe o nome da faccao %d\n (ex: 'FA')", i+1);
                    scanf("%s", nome);
                    nome[0] = toupper(nome[0]);
                    nome[1] = toupper(nome[1]);

                    int pos_x, pos_y;
                    puts("Informe a posicao inicial dela");
                    scanf("%d%d", &pos_x, &pos_y);

                    if (pos_x < 0 || pos_x >= n || pos_y < 0 || pos_y >= m)
                    {
                        msg_erro("Dimensao invalida", "Inicializao manual");
                        continue;
                    }

                    faccao_inserir(cfaccao, nome, pos_x, pos_y);
                }
                mapa_faccao = mapa_aloca(dimensao);
                mapa_replica(mapa_oficial, mapa_faccao, dimensao);
                mapa_faccao_atualiza(cfaccao, mapa_faccao, dimensao);
                
            } else {
                puts("Mapa ja criado!");
            }
            break;

        case 3:
            desaloca_mapa(&mapa_oficial, dimensao);
            desaloca_dimensao(&dimensao);
            return 0;    
            break;

        case 4:
            mapa_display(mapa_oficial, dimensao);
            printf("\n");
            mapa_display(mapa_faccao, dimensao);
            break;

        default:
            break;
        }
      
    }
     

    return 0;
}
