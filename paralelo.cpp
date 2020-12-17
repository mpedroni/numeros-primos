#include <iostream>
using namespace std;

#include <time.h>
#include <omp.h>

#define QTDE_PRIMOS 1600

int is_primo(int suposto_primo) {
    for(int i = (int)(suposto_primo / 2); i > 1; i--)
        if(suposto_primo % i == 0) return false;

    return true;
}

int encontrar_proximo_primo(int n) { // n == ultimo primo encontrado
    bool achou = false;

    do {
        n += 2;
        if(is_primo(n)) achou = true;
    } while(!achou);

    return n;
}

int main() {
    int soma = 15828;

    int primos[QTDE_PRIMOS];

    primos[0] = 2;
    primos[1] = 3;

    for(int i = 2; i < QTDE_PRIMOS; i++)
        primos[i] = encontrar_proximo_primo(primos[i - 1]);

    clock_t tempo;
    tempo = clock();

    omp_set_num_threads(4);

    int range;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        #pragma omp single
        range = QTDE_PRIMOS / omp_get_num_threads();

        int inicio = thread_id * range;
        int fim = inicio + range;

        for(int i = inicio; i < fim; i++) {
            if(primos[i] > soma) break;

            for(int j = i + 1; j < QTDE_PRIMOS; j++) {
                if(primos[i] + primos[j] > soma) break;

                if(primos[i] + primos[j] == soma)
                    printf("%i + %i = %i\n", primos[i], primos[j], soma);
            }
        }
    }

    tempo = clock() - tempo;
    double tempo_execucao = ((double)tempo)/(CLOCKS_PER_SEC/1000);

    printf("\nTempo de execução: %f ms\n", tempo_execucao);

    return 0;
}
