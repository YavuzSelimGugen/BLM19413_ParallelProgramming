#include <stdio.h>
#include <mpi.h>
int main(void) 
{
	
	MPI_Init(NULL,NULL);
// MPI_COMM_WORLD oluşturuluyor.
//İçinde P0, P1, P2, P3 (0-1-2-3 rank'dır) oluşturur. (np- 4 için)
	int size, rank;
	int counter = 0;
	MPI_Comm_size(MPI_COMM_WORLD, &size);	//MPI_COMM'un içinde kaç tane comm var (4 tane var şuanda).
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	//Çalışan processin rankını verir.
	counter++;
	MPI_Barrier(MPI_COMM_WORLD);		// Bütün processler bu satıra gelene kadar tüm processler bekler.	
	printf("Rank= %d\t Counter:%d \n",rank, counter);
	MPI_Finalize();	
	return 0;
}
