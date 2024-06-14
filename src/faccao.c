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
    novo->pts_recurso = 20;
    novo->pts_poder = 20;
    novo->proxunidade = cunidade_cria();
    novo->proxedificio = cedificio_cria();
    novo->proxalianca = calianca_cria();   
    return novo;
}

CFaccao *Cfaccao_cria(void)
{
    CFaccao *novo = (CFaccao*) malloc(sizeof(CFaccao)); 

    if(!novo)
    {
        msg_erro("Falha ao criar a faccao.", "faccao_cria");
        return NULL;
    }

    novo->ini = novo->fim = NULL;
    novo->tam = 0;

    return novo;
}

void cfaccao_desaloca(CFaccao **cabeca)
{
    if ((*cabeca)->ini == NULL)
    {
        free(*cabeca);
        *cabeca = NULL;
        return;
    } 
    
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

int Cfaccao_vazia(const CFaccao *cabeca)
{
    return(cabeca == NULL || cabeca->tam == 0);
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

int faccao_verifica_posicao(CFaccao *cabeca, const int x, const int y) 
{
    if (Cfaccao_vazia(cabeca)) return 0;

    TFaccao *aux = cabeca->ini;
    while (aux)
    {
        if ((aux->x = x) && (aux->y == y))
            return 1;
        aux = aux->prox;
    }
    return 0;
}

void faccao_inserir(CFaccao *cabeca, const char *nome, const int x, const int y)
{
    TFaccao *novo = Tfaccao_aloca(nome, x, y);
    if(!novo)
    {
        msg_erro("\nFalha ao inserir faccao.", "faccao_inserir");
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
        if (!faccao_verifica_posicao(cabeca, aux.x, aux.y))
            faccao_inserir(cabeca, aux.nome, aux.x, aux.y);
    }
    fclose(arquivo);    
}

void faccao_display(const CFaccao *cabeca)
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

void faccao_coleta(CFaccao *cabeca, const char chave, const int qtd)
{
    char aux[3]; aux[0] = 'F'; aux[1] = chave; aux[2] = '\0';

    TFaccao *faccao = faccao_buscar(cabeca, aux);

    if (faccao)        
        faccao->pts_recurso += qtd;
    else 
        msg_erro("Erro ao encontrar faccao", "faccao_buscar");    
     
}

void faccao_ataca(CFaccao *cabeca, char *f1, char *f2, const int x, const int y) // Combate de faccoes
{
    TFaccao *faccao_atacante = faccao_buscar(cabeca, f1);
    TFaccao *faccao_defensora = faccao_buscar(cabeca, f2);

    if (!faccao_atacante || !faccao_defensora){
        msg_erro("Alguma faccao nao encontrada.", "faccao_combate");
        return;
    }

    gera_log("ataca", f1, f2, 0, 0, 0, x, y);       
    gera_log("defende", f2, f1, 0, 0, 0, x, y); 

    // Faccao vencedora perde 20% dos pontos de poder e ganha 70% de pontos de recurso da fac. defensora
    // Faccao perdedora metade dos postos de poder e perde 70% de pontos de recurso
    if (faccao_atacante->pts_poder > faccao_defensora->pts_poder){
        faccao_defensora->pts_poder /= 2;
        faccao_defensora->pts_recurso *= 0.3;

        faccao_atacante->pts_poder *= 0.8; 
        faccao_atacante->pts_recurso += (faccao_defensora->pts_recurso * 0.7);

        gera_log("perde", f2, f1, 0, 0, 0, x, y); 
    } else if (faccao_atacante->pts_poder < faccao_defensora->pts_poder){
        printf("Faccao defensora venceu! Faccao atacante destruida.\n");
        faccao_defensora->pts_poder *= 0.8;
        faccao_defensora->pts_recurso *= 1.2;

        faccao_atacante->pts_poder = (faccao_defensora->pts_poder) - (faccao_atacante->pts_poder);
        faccao_atacante->pts_recurso *= 0*2;
        gera_log("perde", f1, f2, 0, 0, 0, x, y); 
    } else {
        printf("Empate! Ambas perdem recursos e poder.\n");
        faccao_atacante->pts_poder *= 0.5;
        faccao_atacante->pts_recurso *= 0.5;
        faccao_defensora->pts_poder *= 0.5;
        faccao_defensora->pts_recurso *= 0.5;
    } 
}

void faccao_unidade_combate(CFaccao *cabeca, char *unidade_defensora)
{
    int id = (int) (unidade_defensora[1]-48);
    char f_defensora[3];
    TFaccao *aux_faccao = NULL;

    strcpy(f_defensora, unidade_defensora);
    unidade_para_faccao(f_defensora);

    aux_faccao = faccao_buscar(cabeca, f_defensora);

    // Unidade atacante sempre vence
    tunidade_desaloca(aux_faccao->proxunidade, id);
}

void faccao_ganha_postos_poder(CFaccao *cabeca, char *nome_faccao, const int qtd_pts_poder)
{
    TFaccao *faccao = faccao_buscar(cabeca, nome_faccao);

    faccao->pts_poder += qtd_pts_poder;
}

void faccao_alianca(CFaccao *cabeca, char *f1, char *f2)
{
    if(Cfaccao_vazia(cabeca))
    {
        msg_erro("Nao ha nehuma faccao.", "faccao_alianca");
        return;
    }
    TFaccao *faccao_1 = faccao_buscar(cabeca, f1);
    TFaccao *faccao_2 = faccao_buscar(cabeca, f2);

    if (!faccao_1 || !faccao_2)
    {
        msg_erro("Alguma faccao nao existe", "faccao_alianca");
        return;
    }

    if (faccao_1->pts_poder >= faccao_2->pts_poder) // f1 recebe tudo de f2 e se tornam uma faccao so
    { 
        faccao_1->pts_poder += faccao_2->pts_poder;
        faccao_1->pts_recurso += faccao_2->pts_recurso;
        calianca_insere(faccao_1->proxalianca, f2);
        edificio_merge(faccao_1->proxedificio, faccao_2->proxedificio);
        unidade_merge(faccao_1->proxunidade, faccao_2->proxunidade);

        tfaccao_desaloca(cabeca, faccao_2->nome);

    } else { // f2 recebe tudo de f1 e se tornam uma faccao so
        faccao_2->pts_poder += faccao_1->pts_poder;
        faccao_2->pts_recurso += faccao_1->pts_recurso;
        calianca_insere(faccao_2->proxalianca, f1);
        edificio_merge(faccao_2->proxedificio, faccao_1->proxedificio);
        unidade_merge(faccao_2->proxunidade, faccao_1->proxunidade);

        tfaccao_desaloca(cabeca, faccao_1->nome);
    }
}

void mapa_faccao_atualiza(CFaccao *cabeca, char **mapa_faccao, Dimensao *dimensao)
{
    if(Cfaccao_vazia(cabeca) || mapa_vazio(mapa_faccao, dimensao))
    {
        msg_erro("Cfaccao vazia ou mapa vazio.", "mapa_faccao_atualiza");
        return;
    }
    TFaccao *aux = cabeca->ini;
    while(aux)
    {
        int x = aux->x, y = aux->y;
        mapa_faccao[x][y] = aux->nome[1];
        aux = aux->prox;
    }
}

void faccao_unidade_inserir(TFaccao *faccao, const char chave, const char id, const int tipo, const int x, const int y)
{    
    unidade_inserir(faccao->proxunidade, chave, id, tipo, x, y);
    if (tipo == 2) faccao->pts_poder += 10; // a cada soldado criado a faccao ganha 10 pts de poder    
}

void faccao_mapa_unidade_atualiza(CFaccao *cabeca, char **mapa_oficial, char **mapa_unidade, Dimensao *dimensao)
{
    if(Cfaccao_vazia(cabeca) || mapa_vazio(mapa_unidade, dimensao))
    {
        msg_erro("Nao ha faccoes ou o mapa unidade nao foi criado.", "mapa_unidade_atualiza");
        return;
    }

    mapa_replica(mapa_oficial, mapa_unidade, dimensao);
    
    TFaccao *aux = cabeca->ini;
    while(aux){
        CUnidade *cunidade_aux = aux->proxunidade;        
        mapa_unidade_atualiza(cunidade_aux, mapa_unidade);
        aux = aux->prox;
    }
}

void faccao_unidade_move(CFaccao *cabeca, char **mapa_unidade, Dimensao *dimensao, char *nome, const int tipo, const int x, const int y) 
{
    char nome_unidade[3];
    strcpy(nome_unidade, nome);

    nome[1] = nome[0];    
    nome[0] = 'F';

    TFaccao *fac_aux = faccao_buscar(cabeca, nome);   

    char tipo_terreno = mapa_tipo_terreno(mapa_unidade, dimensao, x, y);

    // Coleta de recursos ao explorar novo territorio
    if (tipo_terreno == 'P')
        fac_aux->pts_recurso += 10;
    else if (tipo_terreno == 'F')
        fac_aux->pts_recurso += 20;    

    if (fac_aux) unidade_move(fac_aux->proxunidade, nome_unidade, tipo, x, y);
    else return;
}

void faccao_edificio_constroi(CFaccao *cabeca, char **mapa_edificio, char *identificador, int qtd, int tipo, int x, int y)
{
    TFaccao *fac_aux = faccao_buscar(cabeca, identificador);   

    if (tipo == 1) { // Edificio recurso: -3 pts
        fac_aux->pts_recurso -= (qtd * 3);
    } else if (tipo == 2) { //Edificio campo: -4 pts
        fac_aux->pts_recurso -= (qtd * 4);
    } else { // Edificio lab: -5 pts
        fac_aux->pts_recurso -= (qtd * 5);
    }

    // Adiciona no mapa
    mapa_edificio[x][y] = tolower(identificador[1]);

    edificio_constroi(fac_aux->proxedificio, identificador, qtd, tipo, x, y);
}

CAlianca *faccao_retorna_calianca(CFaccao *cabeca, char *identificador)
{
    TFaccao *aux = faccao_buscar(cabeca, identificador);
    return aux->proxalianca;
}

void faccao_verifica_vencedor(CFaccao *cabeca)
{
    TFaccao *faccoes = cabeca->ini, *aux = cabeca->ini;

    while (faccoes->prox)
    {
        faccoes = faccoes->prox;

        if (aux->pts_poder < faccoes->pts_poder) {
            aux = faccoes;
        }
        if (aux->pts_poder == faccoes->pts_poder) {
            if (aux->pts_recurso < faccoes->pts_recurso)
                aux = faccoes;
        }
    }
    printf("Faccao vencedora: %s\n", aux->nome);
    
    CAlianca *aux1 = faccao_retorna_calianca(cabeca, aux->nome);
    alianca_aliados(aux1);

    gera_log("vence", aux->nome, "", -1, -1, -1, -1, -1);
}