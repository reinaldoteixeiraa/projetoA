#include <stdio.h>

//Função recursiva para solucionar o problema da torre de hanoi
void hanoi(int n, int orig,int dest,int aux){
    if (n == 1){
        printf("Move Disco 1 da torre %d para a torre %d\n",orig,dest);
        return;
    }
    hanoi(n-1,orig,aux,dest);
    printf("Move Disco %d da torre %d para a torre %d\n", n,dest,orig);
    hanoi(n-1,aux,dest,orig);
}

int main(){
    int discos;

        printf("informe a quantidade de discos: ");
            scanf("%d", &discos);

        printf("\n");

    hanoi(discos,1,2,3);

return 0;

}
