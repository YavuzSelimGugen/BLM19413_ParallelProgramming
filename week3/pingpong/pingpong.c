#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10
#define NADAL 0
#define FEDERER 1
#define TAG 666
int main(int argc, char const *argv[])
{
    int rank, size;

    MPI_Init(NULL, NULL);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int a;
    if(size != 2) {
        MPI_Abort(MPI_COMM_WORLD,0);
    }
    // Initial
    if(rank == NADAL) {
        a =2;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank == NADAL) {
        MPI_Send(&a, 1, MPI_INT, FEDERER, TAG, MPI_COMM_WORLD);
        MPI_Recv(&a, 1, MPI_INT, FEDERER, TAG+1, MPI_COMM_WORLD, &status);
        a++;
    } else {
        //MPI_Send(&a, 1, MPI_INT, NADAL, TAG+1, MPI_COMM_WORLD); order of sned and recieve is important
        MPI_Recv(&a, 1, MPI_INT, NADAL, TAG, MPI_COMM_WORLD, &status);
        a++;
        MPI_Send(&a, 1, MPI_INT, NADAL, TAG+1, MPI_COMM_WORLD);
    }
    if(rank == NADAL)
        printf("a = %d\n", a);
    MPI_Finalize();
    return 0;
}
