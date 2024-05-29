#include "bibliotecas.h"

// Estrutura para representar uma facção
typedef struct _faccao{
    char nome[15];
    int pts_recurso, pts_poder;
    int x, y; // posicao da faccao
    struct _faccao *prox;
    CAlianca *proxalianca;
    CEdificio *proxedificio;
    CUnidade *proxunidade;
} TFaccao;

typedef struct _cfaccao{
    TFaccao *ini, *fim;
    int tam;
} CFaccao;

TFaccao *Tfaccao_aloca(const char *nome, const int x, const int y)
{
    TFaccao *novo = (TFaccao*)malloc(sizeof(TFaccao));
    if(!novo){
        msg_erro("Falha ao criar a faccao.", "Tfaccao_aloca");
        return NULL;
    }
    strcpy(novo->nome, nome);
    novo->x = x;
    novo->y = y;
    novo->pts_recurso = 0;
    novo->pts_poder = 0;
    novo->proxunidade = NULL;
    novo->proxedificio = NULL;
    novo->proxalianca = NULL;   
    return novo;
}

CFaccao *Cfaccao_cria(void)
{
    CFaccao *novo = (CFaccao*) malloc(sizeof(CFaccao)); 

    if(!novo){
        msg_erro("Falha ao criar a faccao.", "faccao_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

int Cfaccao_vazia(const CFaccao *cabeca)
{
    return(cabeca == NULL || cabeca->tam == 0);
}

void faccao_inserir(CFaccao *cabeca, const char *nome, const int x, const int y)
{
    TFaccao *novo = Tfaccao_aloca(nome, x, y);
    if(!novo)
    {
        msg_erro("Falha ao inserir faccao.", "faccao_inserir");
        return;
    }
    if (Cfaccao_vazia(cabeca)){
        cabeca->ini = cabeca->fim = novo;

    } else {
        novo->prox = cabeca->ini;
        cabeca->ini = novo;
    }
    cabeca->tam++;
}

int faccao_existe(const CFaccao *cabeca, const char *nome)
{
    if(Cfaccao_vazia(cabeca)) return 0;
    TFaccao *aux = cabeca->ini;
    while(aux){
        if(strcmp(aux->nome, nome) == 0){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void cfaccao_desaloca(CFaccao **cabeca)
{
    if (!*cabeca) return;
    
    TFaccao *aux = (*cabeca)->ini, *temp;
    CUnidade *aux_unidade = (*cabeca)->ini->proxunidade;
    CEdificio *aux_edificio = (*cabeca)->ini->proxedificio;
    CAlianca *aux_alianca = (*cabeca)->ini->proxalianca;

    while(aux){
        temp = aux;
        aux = temp->prox;

        cunidade_desaloca(&aux_unidade);
        cedificio_desaloca(&aux_edificio);  
        calianca_desaloca(&aux_alianca);

        free(temp);
    }

    free(*cabeca);
    *cabeca = NULL;
    return;
}

void tfaccao_desaloca(CFaccao *cabeca, char *nome_faccao)
{
    if (Cfaccao_vazia(cabeca))
    {
        msg_erro("Faccao nao existe.", "tfaccao_desaloca");
        return;
    }

    TFaccao *aux = cabeca->ini, *temp;

    if(strcmp(aux->nome, nome_faccao) == 0){ // Primeiro caso: a primeira faccao ja eh a que queremos
        cabeca->ini = aux->prox;
        free(aux);

    } else {
        temp = aux;
        aux = aux->prox;
        while(aux)
        {
            if(strcmp(aux->nome, nome_faccao) == 0){
                temp->prox = aux->prox;
                free(aux);
                return;
            }
            temp = aux;
            aux = aux->prox;            
        }
        msg_erro("Faccao nao encontrada!", "tfaccao_desaloca");
    }
}

void faccoes_converte_txt_lista(CFaccao *cabeca, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo){
        msg_erro("Erro ao abrir arquivo.", "faccoes_converte_txt_lista");
        return;
    }

    TFaccao aux;

    while(!feof(arquivo))
    {
        fscanf(arquivo, "%s %d %d", aux.nome, &(aux.x), &(aux.y));
        faccao_inserir(cabeca, aux.nome, aux.x, aux.y);
    }
    fclose(arquivo);
    
}

void faccoes_display(const CFaccao *cabeca)
{
    if (Cfaccao_vazia(cabeca))
    {
        msg_erro("Faccao vazia.", "faccoes_display");
        return;
    }
    TFaccao *aux = cabeca->ini;
    while(aux){
        printf("Faccao '%s', posicao '%d,%d', pts_poder '%d', pts_recurso '%d\n", aux->nome, aux->x, aux->y, aux->pts_poder, aux->pts_recurso);
        aux = aux->prox;
    }
}

void faccoes_posicionar_mapa(const CFaccao *cabeca, char **mapa)
{
    if (Cfaccao_vazia(cabeca))
    {
        msg_erro("Faccao vazia.", "faccoes_inicializar_mapa");
        return;
    }
    TFaccao *aux = cabeca->ini;
    int i, j;
    char c = 'A';
    while(aux){
        i = aux->x, j = aux->y;
        mapa[i][j] = c++;
        aux = aux->prox;
    }
}

TFaccao *faccao_buscar(CFaccao *cabeca, char *nome)
{
    TFaccao *aux = cabeca->ini;
    while(aux)
    {
        if (strcmp(aux->nome, nome) == 0)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void faccao_coleta(CFaccao *cabeca, const char chave, const int tipo, const int qtd)
{
    char aux[3]; aux[0] = 'F'; aux[1] = toupper(chave); aux[2] = '\0';
    
    TFaccao *faccao = faccao_buscar(cabeca, aux);
    if (faccao)
        faccao->pts_recurso += qtd;
    else
        msg_erro("Erro ao encontrar faccao", "faccao_buscar");    
}

void faccao_combate(CFaccao *cabeca, char *f1, char *f2)
{
    TFaccao *faccao_atacante = faccao_buscar(cabeca, f1);
    TFaccao *faccao_defensora = faccao_buscar(cabeca, f2);

    if (!faccao_atacante || !faccao_defensora){
        msg_erro("Alguma faccao nao encontrada.", "faccao_combate");
        return;
    }

    // Faccao vencedora perde 20% dos pontos de poder e ganha 20% de pontos de recurso
    if (faccao_atacante->pts_poder > faccao_defensora->pts_poder){
        printf("Faccao atacante venceu! Faccao defensora destruida.\n");
        faccao_atacante->pts_poder *= 0.8; 
        faccao_atacante->pts_recurso *= 1.2;
        tfaccao_desaloca(cabeca, f2);

    } else if (faccao_atacante->pts_poder < faccao_defensora->pts_poder){
        printf("Faccao defensora venceu! Faccao atacante destruida.\n");
        faccao_defensora->pts_poder *= 0.8;
        faccao_defensora->pts_recurso *= 1.2;
        tfaccao_desaloca(cabeca, f1);

    } else {
        printf("Empate! Ambas perdem recursos e poder.\n");
        faccao_atacante->pts_poder *= 0.5;
        faccao_atacante->pts_recurso *= 0.5;
        faccao_defensora->pts_poder *= 0.5;
        faccao_defensora->pts_recurso *= 0.5;
    }
}

void faccao_teste(CFaccao *cabeca)
{
    TFaccao *aux = cabeca->ini;
    aux->pts_poder += 10; // FC
    aux->prox->pts_poder += 5; // FB
    aux->prox->prox->pts_poder += 10; // FA
    
}




