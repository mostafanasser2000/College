// Mostafa Nasser Mohamed 20190537
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>
#include <math.h>

int myPoints[1000];
int ranges[1000];

int main(int argc, char *argv[])
{

    int rank;
    int process_count;
    int elements_assigned_per_process;
    int elements_remaining;
    int elements_received_per_process;
    int index;
    int numberOfBars;
    int numberOfPointes;
    int MAX, MIN, *local_max, local_min;
    int range;
    int barSize;

    // initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);          // get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &process_count); // get the number of processes
    MPI_Status status;

    // master process
    if (rank == 0)
    {
        // taking points and number of bars as input
        printf("Enter the number of points: ");
        scanf("%d", &numberOfPointes);
        printf("\nEnter the number of bars: ");
        scanf("%d", &numberOfBars);
        int points[numberOfPointes];

#pragma omp for
        for (int i = 0; i < numberOfPointes; i++)
        {
            points[i] = 0;
        }

        // readData from file
        FILE *fp;
        fp = fopen("txt/dataset.txt", "r");
        if (fp == NULL)
        {
            printf("File not found\n");
            return 1;
        }
        char line[50];
        int i = 0;
        MAX = 0;
        MIN = 1000;
        while (fgets(line, 50, fp) != NULL)
        {
            points[i] = atoi(line);

            MAX = points[i] > MAX ? points[i] : MAX;
            MIN = points[i] < MIN ? points[i] : MIN;
            i++;
        }
        fclose(fp);
        // send MAX element to all processes
        MPI_Bcast(&MAX, 1, MPI_INT, 0, MPI_COMM_WORLD);

        // calculate the bar size
        range = MAX - MIN;
        barSize = (range + 1) / numberOfBars;

        // assign work to slave processes only not master process
        process_count -= 1;
        elements_assigned_per_process = numberOfPointes / process_count;

        for (i = 0; i < process_count - 1; i++)
        {
            index = i * elements_assigned_per_process;
            MPI_Send(&elements_assigned_per_process,
                     1, MPI_INT, i + 1, 0,
                     MPI_COMM_WORLD);
            MPI_Send(&points[index], elements_assigned_per_process, MPI_INT, i + 1, 0,
                     MPI_COMM_WORLD);
        }
        // send the remaining elements to the last process
        index = i * elements_assigned_per_process;
        elements_remaining = numberOfPointes - index;
        MPI_Send(&elements_remaining,
                 1, MPI_INT,
                 i + 1, 0,
                 MPI_COMM_WORLD);
        MPI_Send(&points[index], elements_remaining, MPI_INT, i + 1, 0,
                 MPI_COMM_WORLD);

        // receive the results from all processes
        int results[process_count][MAX + 1];
        for (i = 0; i < process_count; i++)
        {
            MPI_Recv(&results[i], MAX + 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        }

// print the results
#pragma omp for
        for (int i = 1; i <= numberOfBars; ++i)
        {
            int higher = barSize * i;
            int lower = barSize * (i - 1) + 1;
            int count = 0;
            for (int j = 0; j < process_count; ++j)
            {
                for (int k = 0; k <= MAX; ++k)
                {
                    if (results[j][k] > 0 && k >= lower && k <= higher)
                    {
                        count++;
                    }
                }
            }
            if (i == 1)
            {
                lower--;
            }
            printf("The range start with %d, end with %d with count %d\n", lower, higher, count);
        }
    }

    else
    {

        // receive MAX element from master process
        MPI_Bcast(&MAX, 1, MPI_INT, 0, MPI_COMM_WORLD);

        MPI_Recv(&elements_received_per_process,
                 1, MPI_INT,
                 0, 0,
                 MPI_COMM_WORLD,
                 &status);
        MPI_Recv(&myPoints,
                 elements_received_per_process, MPI_INT,
                 0, 0,
                 MPI_COMM_WORLD,
                 &status);
        int myRanges[MAX + 1];
#pragma omp parallel
        {
#pragma omp for
            for (int i = 0; i < MAX + 1; i++)
            {
                myRanges[i] = 0;
            }
#pragma omp for
            for (int i = 0; i < elements_received_per_process; i++)
            {
                myRanges[myPoints[i]]++;
            }
        }

        MPI_Send(&myRanges, MAX + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    // shutdown MPI
    MPI_Finalize();

    return 0;
}
