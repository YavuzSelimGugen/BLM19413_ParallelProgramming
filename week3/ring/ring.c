#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


#define TAG 100


int main(int argc, char const *argv[])
{
    int rank, size, a;

    MPI_Init(NULL, NULL);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int first = 0;
    int last = size - 1 ;

    if (rank == first)
    {
        a+=rank;
        MPI_Send(&a, 1, MPI_INT, first+1, TAG, MPI_COMM_WORLD);
        MPI_Recv(&a, 1, MPI_INT, last, TAG, MPI_COMM_WORLD, &status);

    } else if (rank == last)
    {
        MPI_Recv(&a, 1, MPI_INT, last-1, TAG, MPI_COMM_WORLD, &status);
        a += rank;   
        MPI_Send(&a, 1, MPI_INT, first, TAG, MPI_COMM_WORLD);
    } else
    {
        MPI_Recv(&a, 1, MPI_INT, rank - 1, TAG, MPI_COMM_WORLD, &status);
        a += rank;
        MPI_Send(&a, 1, MPI_INT, rank + 1, TAG, MPI_COMM_WORLD);
    }
    
    if(rank == first) printf("");
    

    MPI_Finalize();
    return 0;
}
