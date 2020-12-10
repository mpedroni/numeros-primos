#include <iostream>

using namespace std;

#define QTDE_PRIMOS 1000

int is_primo(int suposto_primo) {
    for(int i = (int)(suposto_primo / 2); i > 1; i--)
        if(suposto_primo % i == 0) 
            return false;

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
    int soma = 216;

    int primos[QTDE_PRIMOS];

    primos[0] = 2;
    primos[1] = 3;

    for(int i = 2; i < QTDE_PRIMOS; i++)
        primos[i] = encontrar_proximo_primo(primos[i - 1]);

    for(int i = 0; i < QTDE_PRIMOS - 1; i++) {
        for(int j = i; j < QTDE_PRIMOS; j++) {
            if(primos[i] + primos[j] > soma) break;

            if(primos[i] + primos[j] == soma) {
                cout << primos[i] << " + " << primos[j] << " = " << soma << endl;
            }
        }

        if(primos[i] > soma) break;
    };

    return 0;
}
