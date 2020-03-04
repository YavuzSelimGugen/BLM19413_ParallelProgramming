/*

variance  = E(Xi - X~)^2 x 1/N

1) N=10^6 -> float *data[N]
2) In each process -> float *local_data[chunk]
3) Scatter
4) Local computation for avarage
5) Reduce -> x~
6) BCAST (X~)
7) local computation for variance
8) Reduce -> Variance
9) Master calculate std and prints

*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define N 1000000
#define MASTER 0

float *create1DArray(int n)
{
    float *T = (float *)malloc(n * sizeof(float));
    return T;
}

int main(int argc, char const *argv[])
{
    int rank, size, i;
    double t1, t2;

    MPI_Init(0, 0);
    t1 = MPI_Wtime();
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int chunk = N / size;

    // Initialization
    float local_toplam = 0.0;
    float toplam = 0.0;
    float ort = 0.0;
    float *dizi;
    float *local_dizi;
    float local_sub = 0.0;
    float sub;
    // FIND AVARAGE
    if (rank == MASTER)
    {
        dizi = create1DArray(N);
        local_dizi = create1DArray(chunk);

        for (i = 0; i < N; i++)
            dizi[i] = 1.0;
    }
    else
    {
        local_dizi = create1DArray(chunk);
    }
    // Scatter (data distribution)
    MPI_Scatter(dizi, chunk, MPI_FLOAT, local_dizi, chunk, MPI_FLOAT, MASTER, MPI_COMM_WORLD);

    // Local computation
    for (i = 0; i < chunk; i++)
        local_toplam += local_dizi[i];

    // Gather data with reduction
    MPI_Reduce(&local_toplam, &toplam, 1, MPI_FLOAT, MPI_SUM, MASTER, MPI_COMM_WORLD);

    // MASTER prints out the average
    if (rank == MASTER){
        ort = toplam / N;
        printf("Ortalama = %f\n", ort);
        
    }
    ort = toplam / N;
        
    //BROADCAST ORT
    MPI_Bcast(&ort, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    //printf("ORT Brodcast: %f\n",ort);


    // FIND VARIANCE (E Xi-X~)
    MPI_Barrier(MPI_COMM_WORLD);
    for (i = 0; i < chunk; i++)
    {
        // KARE AL
        //printf("%f - %f\n", local_dizi[i], ort);
        local_sub += (local_dizi[i] - ort) * (local_dizi[i] - ort);
    }
    MPI_Reduce(&local_sub, &sub, 1, MPI_FLOAT, MPI_SUM, MASTER, MPI_COMM_WORLD);
    if(rank == MASTER) {
        printf("sub/N: %f\n", (sub/N));
        printf("E: %d", sqrt(sub/N));
    }

    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();

    printf("MPI_Wtime measured a 1 second sleep to be: %1.4f\n", t2-t1);
    fflush(stdout);
    MPI_Finalize();
    return 0;
}
