#include <stdio.h>
//Função recursiva para solucionar o problema da torre de hanoi
void hanoi(int n, char orig,char dest,char aux){
    if (n == 1){
        printf("Move Disco 1 da torre %c para a torre %c\n",orig,dest);
        return;
    }
    hanoi(n-1,orig,aux,dest);
    printf("Move Disco %d da torre %c para a torre %c\n", n,dest,orig);
    hanoi(n-1,aux,dest,orig);
}

int main(){
    int discos;
    printf("digite a quantidade de discos:");
    scanf("%d", &discos);
    printf("\n");
    hanoi(discos,'A','B','C');
    return 0;
}