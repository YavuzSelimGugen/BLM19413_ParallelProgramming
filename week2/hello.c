#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
    MPI_Init(&argc, &argv);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        printf("arg count = &d\n", argc);
        printf("argv[0]  &s\n", argv[0]);
        printf("argv[0]  &s\n", argv[1]);
        printf("argv[0]  &s\n", argv[2]);
    }

    printf("rank = %d\t Hello world\n", rank);
    printf("\n");
    MPI_Finalize();
    return 0;
}
