#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>


#define N 1000
#define PI acos(-1)

double f(double x){
    return 4.0/ (1.0 + x*x);
}
int main(int argc, char const *argv[])
{
    int i;
    double top = 0.0;
    double h = 1.0 / (double)N, localpi, pi;
    MPI_Status *stat;

    MPI_Init(NULL, NULL);
    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int chunk = N / size;

    for (int i = rank * chunk +1; i <= (rank+1) * chunk ; i++)
    {
        top += f(i * h);
    }
    top *= h;
    printf("Yaklasik pi: %.16f\n", top);

    if(rank != 0) {
        for (int i = 1; i <= 3; i++)
        {
            MPI_Send(&top, 1, MPI_DOUBLE, 0, 777+i, MPI_COMM_WORLD);
        } 
        
    }
    else {
        for (int i = 1; i <= 3; i++)
        {
                MPI_Recv(&localpi 1, MPI_DOUBLE, i, 777+i, MPI_COMM_WORLD, stat);
                pi += localpi;
        }
            
    }
/* 
    Serial Case
    for (int i = 0; i < N; i++)
    {
        top +=f(i*h);
    }
    top *= h;

    printf("Gercek pi: %.16f\n", PI);
    printf("Yaklasik pi: %.16f\n", top);
*/
    
    MPI_Finalize();
    return 0;
}
