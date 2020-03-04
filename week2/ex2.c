#include <stdio.h>
#include <mpi.h>

#define MASTER 0

void printArray(int *d, int n) {
    for (int i = 0; i < n; i++)
    {
        printf("%d\t", d[i]);
    }
    printf("\n");
    
}

int main(int argc, char const *argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;
    MPI_Status *stat;                                                   // Her bir worker process icin ayri stat tanimlanabilir. Durum bilgisini verir.

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int altdizi[15] = {0};
    if(rank == MASTER) {
        int dizi[60];
        for (int i = 0; i < 60; i++)
            dizi[i] = i+1;
        
        MPI_Send(&dizi[15], 15, MPI_INT, 1, 777, MPI_COMM_WORLD);
        MPI_Send(&dizi[30], 15, MPI_INT, 2, 778, MPI_COMM_WORLD);       //PARAMETLERI INCELE
        MPI_Send(&dizi[45], 15, MPI_INT, 3, 779, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(altdizi, 15, MPI_INT, 1, 777, MPI_COMM_WORLD,stat);
    } else if (rank == 2) {
        MPI_Recv(altdizi, 30, MPI_INT, 2, 778, MPI_COMM_WORLD, stat);
    } else if (rank == 3) {
        MPI_Recv(altdizi, 45, MPI_INT, 3, 779, MPI_COMM_WORLD, stat);
    }
    
    

    MPI_Finalize(); 
    return 0;
}