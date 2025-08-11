#include <stdio.h>

/*
 Desafio Batalha Naval
 Implementação em C com três níveis:
  - Nível Novato: 2 navios (1 horizontal, 1 vertical) e impressão das coordenadas
  - Nível Aventureiro: matriz 10x10, 4 navios (incluindo 2 diagonais), imprime 0/3
  - Nível Mestre: padrões cone, cruz, octaedro (0/1) com laços aninhados
*/

void print_mat_int(const int *m, int R, int C, int linha_em_branco) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("%d ", *((m + i*C) + j));
        }
        printf("\n");
        if (linha_em_branco) printf("\n");
    }
}

/* ====================== NÍVEL NOVATO ====================== */
void nivel_novato(void) {
    const int N = 6;
    int tabuleiro[6][6] = {0};

    /* Variáveis de posicionamento */
    int h_row = 1, h_col = 1, h_len = 4; /* navio horizontal */
    int v_row = 2, v_col = 4, v_len = 3; /* navio vertical   */

    /* Posiciona horizontal e imprime coordenadas */
    for (int j = 0; j < h_len; j++) {
        tabuleiro[h_row][h_col + j] = 1;
        printf("Horizontal: (%d,%d)\n", h_row, h_col + j);
    }

    /* Posiciona vertical e imprime coordenadas */
    for (int i = 0; i < v_len; i++) {
        tabuleiro[v_row + i][v_col] = 1;
        printf("Vertical:   (%d,%d)\n", v_row + i, v_col);
    }

    /* Visualização */
    printf("\nTabuleiro %dx%d (0=vazio, 1=navio):\n", N, N);
    print_mat_int(&tabuleiro[0][0], N, N, 0);
}

/* ==================== NÍVEL AVENTUREIRO ==================== */
#define NA 10

void marca_horizontal(int m[NA][NA], int lin, int col_ini, int tam) {
    for (int j = 0; j < tam && col_ini + j < NA; j++) m[lin][col_ini + j] = 3;
}
void marca_vertical(int m[NA][NA], int lin_ini, int col, int tam) {
    for (int i = 0; i < tam && lin_ini + i < NA; i++) m[lin_ini + i][col] = 3;
}
void marca_diag_dr(int m[NA][NA], int lin, int col, int tam) { /* ↓→ */
    for (int k = 0; k < tam && lin + k < NA && col + k < NA; k++) m[lin + k][col + k] = 3;
}
void marca_diag_ur(int m[NA][NA], int lin, int col, int tam) { /* ↑→ */
    for (int k = 0; k < tam && lin - k >= 0 && col + k < NA; k++) m[lin - k][col + k] = 3;
}

void nivel_aventureiro(void) {
    int b[NA][NA] = {0};

    /* Quatro navios: 1 horizontal, 1 vertical, 2 diagonais */
    marca_horizontal(b, 1, 1, 4);
    marca_vertical  (b, 0, 6, 3);
    marca_diag_dr   (b, 2, 2, 3);
    marca_diag_ur   (b, 9, 1, 4);

    printf("Tabuleiro %dx%d (0=vazio, 3=ocupado):\n", NA, NA);
    print_mat_int(&b[0][0], NA, NA, 0);
}

/* ====================== NÍVEL MESTRE ======================= */
#define S 5

void limpa(int m[S][S]) {
    for (int i = 0; i < S; i++) for (int j = 0; j < S; j++) m[i][j] = 0;
}

void padrao_cruz(int out[S][S]) {
    limpa(out);
    int cx = S/2, cy = S/2;
    for (int k = 0; k < S; k++) { out[cx][k] = 1; out[k][cy] = 1; }
}

void padrao_octaedro(int out[S][S]) {
    limpa(out);
    int cx = S/2, cy = S/2, r = 1;
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < S; j++) {
            int di = (i > cx) ? i - cx : cx - i;
            int dj = (j > cy) ? j - cy : cy - j;
            if (di + dj <= r) out[i][j] = 1;
        }
    }
}

void padrao_cone(int out[S][S]) {
    limpa(out);
    int apex_col = S/2;
    for (int i = 0; i < S; i++) {
        int left  = apex_col - i;
        int right = apex_col + i;
        if (left  < 0) left  = 0;
        if (right >= S) right = S - 1;
        for (int j = left; j <= right; j++) out[i][j] = 1;
    }
}

void nivel_mestre(void) {
    int m[S][S];

    printf("Cone:\n");
    padrao_cone(m);
    print_mat_int(&m[0][0], S, S, 1);

    printf("Octaedro:\n");
    padrao_octaedro(m);
    print_mat_int(&m[0][0], S, S, 1);

    printf("Cruz:\n");
    padrao_cruz(m);
    print_mat_int(&m[0][0], S, S, 1);
}

/* =========================== MAIN ========================== */
int main(void) {
    printf("=== Nivel Novato ===\n");
    nivel_novato();

    printf("\n=== Nivel Aventureiro ===\n");
    nivel_aventureiro();

    printf("\n=== Nivel Mestre ===\n");
    nivel_mestre();

    return 0;
}