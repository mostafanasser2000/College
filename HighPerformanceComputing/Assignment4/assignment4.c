// Mohamed adel 2019451
// Abdallah Fadl 20190305
// Mostafa Nasser 20190537

#include <string.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int main(int argc, char *argv[]) {
    int rank, numOfProcesses, numbersPerProcess, remainingNumbers;
    int n, s = 3;
    int  myStartNum, i;
    double mySum = 0, totalSum, expectedResult = 1.202056903159594;
    double startTime, endTime; double runtime;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numOfProcesses);
    if (rank == 0){
        scanf("%d", &n);
        startTime = MPI_Wtime();
        numbersPerProcess = ceil(n / (double) numOfProcesses);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numbersPerProcess, 1, MPI_INT, 0, MPI_COMM_WORLD);
    myStartNum = rank * numbersPerProcess + 1;
    /* if it is the last process */
    if (!(rank == numOfProcesses - 1)){
        remainingNumbers = n + 1 - myStartNum;
        while(remainingNumbers != 0){
            mySum += 1.0 / pow(myStartNum, s);
            myStartNum++;
            remainingNumbers--;
        }

    }
    else{
        for(i = 0; i < numbersPerProcess; i++, myStartNum++){
            mySum += 1.0 / pow(myStartNum, s);
        }
    }

    MPI_Reduce(&mySum, &totalSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank == 0)
	{
		printf("Result = %lf\n", totalSum);
        printf("Expected = %lf\n", expectedResult);
        printf("Error = %lf\n", expectedResult - totalSum);
        endTime = MPI_Wtime();
        runtime = (double) (endTime - startTime);
        printf("runTime = %lf\n", runtime);
	}

	MPI_Finalize();

    return 0;
}
