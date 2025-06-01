#include <stdio.h>

// Desafio Batalha Naval
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#define TAMANHO 10
#define TAMANHO_HABILIDADE 5

// Estrutura para armazenar uma habilidade
typedef struct {
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    const char* nome;
} Habilidade;

void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for(int i = 0; i < TAMANHO; i++) {
        for(int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void posicionarNavios(int tabuleiro[TAMANHO][TAMANHO]) {
    // Navio 1: horizontal na linha 3 (índice 2)
    for(int i = 0; i < 3; i++) {
        tabuleiro[2][3 + i] = 3;  // Posições D3, E3, F3
    }
    
    // Navio 2: vertical na coluna H (índice 7)
    for(int i = 0; i < 3; i++) {
        tabuleiro[5 + i][7] = 3;  // Posições H6, H7, H8
    }
    
    // Navio 3: diagonal descendente
    for(int i = 0; i < 3; i++) {
        tabuleiro[1 + i][1 + i] = 3;  // Posições B2, C3, D4
    }
    
    // Navio 4: diagonal ascendente
    for(int i = 0; i < 3; i++) {
        tabuleiro[8 - i][1 + i] = 3;  // Posições B9, C8, D7
    }
}

void exibirCoordenadas(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nPosições dos navios:\n");
    
    printf("\nNavio 1 (Horizontal):\n");
    for(int j = 0; j < TAMANHO; j++) {
        if(tabuleiro[2][j] == 3) {
            printf("(%d, %c) ", 3, 'A' + j);
        }
    }
    
    printf("\n\nNavio 2 (Vertical):\n");
    for(int i = 0; i < TAMANHO; i++) {
        if(tabuleiro[i][7] == 3) {
            printf("(%d, %c) ", i + 1, 'H');
        }
    }
    
    printf("\n\nNavio 3 (Diagonal Descendente):\n");
    for(int i = 0; i < 3; i++) {
        printf("(%d, %c) ", 2 + i, 'B' + i);
    }
    
    printf("\n\nNavio 4 (Diagonal Ascendente):\n");
    for(int i = 0; i < 3; i++) {
        printf("(%d, %c) ", 9 - i, 'B' + i);
    }
    printf("\n");
}

void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nTABULEIRO BATALHA NAVAL\n");
    printf("   A B C D E F G H I J\n");
    for(int i = 0; i < TAMANHO; i++) {
        if(i == 9) {
            printf("%d", i + 1);
        } else {
            printf("%d ", i + 1);
        }
        for(int j = 0; j < TAMANHO; j++) {
            printf(" %d", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Funções para criar as habilidades especiais
Habilidade criarHabilidadeCone() {
    Habilidade cone = {{
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }, "Cone"};
    return cone;
}

Habilidade criarHabilidadeOctaedro() {
    Habilidade octaedro = {{
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }, "Octaedro"};
    return octaedro;
}

Habilidade criarHabilidadeCruz() {
    Habilidade cruz = {{
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    }, "Cruz"};
    return cruz;
}

// Função para exibir uma habilidade
void exibirHabilidade(Habilidade hab) {
    printf("\nHabilidade %s:\n", hab.nome);
    for(int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for(int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", hab.matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para aplicar uma habilidade em uma posição específica do tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO][TAMANHO], Habilidade hab, int linha, int coluna) {
    // Exibe uma mensagem indicando qual habilidade está sendo aplicada e em qual posição
    printf("\nAplicando habilidade %s na posição (%d, %c):\n", hab.nome, linha, 'A' + coluna);
    
    // Cria uma matriz temporária 10x10 inicializada com zeros
    // Usamos uma matriz temporária para não afetar o tabuleiro original
    int tabuleiroTemp[TAMANHO][TAMANHO] = {0};
    
    // Converte a linha de base 1 para base 0
    // Ex: Se o usuário informou linha 3, internamente usamos 2
    linha = linha - 1;
    
    // Loop duplo para percorrer a matriz 5x5 da habilidade
    for(int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for(int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcula a posição atual no tabuleiro
            int linha_atual = linha + i;      // A linha começa da posição informada
            int coluna_atual = coluna + j - 2;// Centraliza horizontalmente (subtrai 2)
            
            // Verifica se a posição calculada está dentro dos limites do tabuleiro
            if(linha_atual >= 0 && linha_atual < TAMANHO && 
               coluna_atual >= 0 && coluna_atual < TAMANHO) {
                // Copia o valor da matriz da habilidade para o tabuleiro temporário
                tabuleiroTemp[linha_atual][coluna_atual] = hab.matriz[i][j];
            }
        }
    }
    
    // Exibe o cabeçalho do tabuleiro (letras das colunas)
    printf("   A B C D E F G H I J\n");
    
    // Loop para exibir o tabuleiro temporário
    for(int i = 0; i < TAMANHO; i++) {
        // Formatação especial para o número 10 (última linha)
        if(i == 9) {
            printf("%d", i + 1);
        } else {
            printf("%d ", i + 1);
        }
        
        // Exibe cada posição do tabuleiro
        for(int j = 0; j < TAMANHO; j++) {
            printf(" %d", tabuleiroTemp[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    
    // Inicializa o tabuleiro com zeros
    inicializarTabuleiro(tabuleiro);
    
    // Posiciona os navios no tabuleiro
    posicionarNavios(tabuleiro);
    
    // Exibe as coordenadas dos navios
    exibirCoordenadas(tabuleiro);
    
    // Exibe o tabuleiro completo
    exibirTabuleiro(tabuleiro);
    
    // Criar e exibir as habilidades especiais
    printf("\n=== HABILIDADES ESPECIAIS ===\n");
    
    Habilidade cone = criarHabilidadeCone();
    Habilidade octaedro = criarHabilidadeOctaedro();
    Habilidade cruz = criarHabilidadeCruz();
    
    exibirHabilidade(cone);
    exibirHabilidade(octaedro);
    exibirHabilidade(cruz);
    
    // Demonstrar o uso das habilidades em diferentes posições do tabuleiro
    printf("\n=== DEMONSTRAÇÃO DAS HABILIDADES ===\n");
    aplicarHabilidade(tabuleiro, cone, 3, 4);     // Aplicar cone na posição (3, D)
    aplicarHabilidade(tabuleiro, octaedro, 5, 6); // Aplicar octaedro na posição (5, F)
    aplicarHabilidade(tabuleiro, cruz, 7, 8);     // Aplicar cruz na posição (7, H)
    
    return 0;
}
