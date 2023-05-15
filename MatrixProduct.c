#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **aloca_matriz(int linhas, int colunas) {
    int **matriz;
    int i;

    matriz = (int **) malloc(linhas * sizeof(int *));
    for (i = 0; i < linhas; i++)
        matriz[i] = (int *) malloc(colunas * sizeof(int));

    return matriz;
}

void inicializa_matriz(int **matriz, int linhas, int colunas) {
    int i, j;

    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            matriz[i][j] = rand() % 10;
}

void inicializa_vetor(int *vetor, int tamanho) {
    int i;

    for (i = 0; i < tamanho; i++)
        vetor[i] = rand() % 10;
}

void libera_matriz(int **matriz, int linhas) {
    int i;

    for (i = 0; i < linhas; i++)
        free(matriz[i]);
    free(matriz);
}

void multiplica_matriz_vetor(int **matriz, int *vetor, int *resultado, int linhas, int colunas) {
    int i, j;

    for (i = 0; i < linhas; i++) {
        resultado[i] = 0;
        for (j = 0; j < colunas; j++)
            resultado[i] += matriz[i][j] * vetor[j];
    }
}

void multiplica_matriz_vetor_rev(int **matriz, int *vetor, int *resultado, int linhas, int colunas) {
    int i, j;

    for (j = 0; j < colunas; j++) {
        resultado[j] = 0;
        for (i = 0; i < linhas; i++)
            resultado[j] += matriz[i][j] * vetor[j];
    }
}

int main(int argc, char **argv) {
    srand(time(NULL));

    if (argc < 2) {
        printf("Uso: Informe a dimensão da matriz como argumento\n");
        return 1;
    }

    int dimensao = atoi(argv[1]);
    int **A;
    int *x;
    int *resultado;
    clock_t tempo_inicio, tempo_fim, tempo_inicio_rev, tempo_fim_rev;
    double tempo_total, tempo_total_rev;
  
    A = aloca_matriz(dimensao, dimensao);
    x = (int *) malloc(dimensao * sizeof(int));
    resultado = (int *) malloc(dimensao * sizeof(int));

    inicializa_matriz(A, dimensao, dimensao);
    inicializa_vetor(x, dimensao);

    tempo_inicio = clock();
    multiplica_matriz_vetor(A, x, resultado, dimensao, dimensao);
    tempo_fim = clock();

    tempo_total = ((double) (tempo_fim - tempo_inicio)) / CLOCKS_PER_SEC;
    printf("Tempo para a dimensao %d aninhamento padrão: %.8lf segundos\n", dimensao, tempo_total);

    tempo_inicio_rev = clock();
    multiplica_matriz_vetor_rev(A, x, resultado, dimensao, dimensao);
    tempo_fim_rev = clock();

    tempo_total_rev = ((double) (tempo_fim_rev - tempo_inicio_rev)) / CLOCKS_PER_SEC;
    printf("Tempo para a dimensao %d aninhamento invertido: %.8lf segundos\n", dimensao, tempo_total_rev);

    libera_matriz(A, dimensao);
    free(x);
    free(resultado);

    return 0;
}