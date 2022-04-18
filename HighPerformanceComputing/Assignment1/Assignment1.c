#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// count the number of lines in a file
int count_file_lines(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 0;
    }
    int count = 0;
    char ch;
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
        {
            count++;
        }
    }
    fclose(fp);
    return count;
}

int sendedMessagesGrades[100];
int sendedMessagesIds[100];

// Temporary array for slave process
int receivedMessagesGrades[100];
int receivedMessagesIds[100];

void readData(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }
    char line[50];
    int i = 0;
    while (fgets(line, 50, fp) != NULL)
    {

        int grade;
        int id;
        char *token = strtok(line, " ");
        id = atoi(token);
        token = strtok(NULL, " ");
        grade = atoi(token);
        sendedMessagesGrades[i] = grade;
        sendedMessagesIds[i] = id;
        i++;
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{

    int rank;
    int process_count;
    int elements_assigned_per_process;
    int elements_remaining;
    int elements_received_per_process;
    int index;
    int i;

    MPI_Status status;

    // initialize MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);          // get process rank
    MPI_Comm_size(MPI_COMM_WORLD, &process_count); // get the number of processes

    // master process
    if (rank == 0)
    {
        int numberOfStudents = count_file_lines("student.txt");

        readData("student.txt");

        // assign work to slave processes only not master process
        process_count -= 1;

        // calculate the number of elements assigned to each process
        elements_assigned_per_process = numberOfStudents / process_count;

        // check if more than 1 processes are run
        if (process_count > 1)
        {
            // divide the work among the processes
            for (i = 0; i < process_count - 1; i++)
            {
                index = i * elements_assigned_per_process;

                MPI_Send(&elements_assigned_per_process,
                         1, MPI_INT, i + 1, 0,
                         MPI_COMM_WORLD);

                MPI_Send(&sendedMessagesIds[index], elements_assigned_per_process, MPI_INT, i + 1, 0,
                         MPI_COMM_WORLD);

                MPI_Send(&sendedMessagesGrades[index], elements_assigned_per_process, MPI_INT, i + 1, 0,
                         MPI_COMM_WORLD);
            }

            // last process takes the remaining elements
            index = i * elements_assigned_per_process;
            elements_remaining = numberOfStudents - index;

            MPI_Send(&elements_remaining,
                     1, MPI_INT,
                     i + 1, 0,
                     MPI_COMM_WORLD);
            MPI_Send(&sendedMessagesIds[index], elements_remaining, MPI_INT, i + 1, 0,
                     MPI_COMM_WORLD);

            MPI_Send(&sendedMessagesGrades[index], elements_remaining, MPI_INT, i + 1, 0,
                     MPI_COMM_WORLD);
        }

        // receive the succsseded students from the processes

        int succssededStudents = 0;
        int partialResult;
        for (i = 1; i <= process_count; i++)
        {

            MPI_Recv(&partialResult, 1, MPI_INT,
                     i, 0,
                     MPI_COMM_WORLD,
                     &status);
            int sender = status.MPI_SOURCE;

            succssededStudents += partialResult;
        }

        // print the number of succsseded students
        printf("Total number of student passed the exam is %d out of %d\n", succssededStudents, numberOfStudents);
    }
    // slave processes
    else
    {
        MPI_Recv(&elements_received_per_process,
                 1, MPI_INT, 0, 0,
                 MPI_COMM_WORLD,
                 &status);
        // stores the received array segment
        // in local array receivedMessages
        MPI_Recv(&receivedMessagesIds, elements_received_per_process,
                 MPI_INT, 0, 0,
                 MPI_COMM_WORLD,
                 &status);

        MPI_Recv(&receivedMessagesGrades, elements_received_per_process,
                 MPI_INT, 0, 0,
                 MPI_COMM_WORLD,
                 &status);

        // calculates its partial sum
        int partial_sum = 0;
        for (int i = 0; i < elements_received_per_process; i++)
        {

            if (receivedMessagesGrades[i] >= 60)
            {
                printf("%d Passed The Exam\n", receivedMessagesIds[i]);
                partial_sum++;
            }
            else
            {
                printf("%d Failed. Please Repeat The Exam\n", receivedMessagesIds[i]);
            }
        }

        // sends the partial sum to the master process
        MPI_Send(&partial_sum, 1, MPI_INT,
                 0, 0, MPI_COMM_WORLD);
    }

    // shutdown MPI
    MPI_Finalize();

    return 0;
}
