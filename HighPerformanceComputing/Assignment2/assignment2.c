// Ahmed Essam 2019050
// Aballah Fadl 20190305
// Mostafa Nasser	20190537
// Youssuf Adel
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#define THREADS 4
#define CHUNKSIZE 2
#define MAX 20
///////////////////////////////////////////////////////////////////
struct Point
{
    int x;
    int y;
    int cluster;
};
///////////////////////////////////////////////////////////////////
int calculateNumberOfPoints()
{
    int numOfPoints = 0;
    char line[15];
    FILE *fptr;
    fptr = fopen("points.txt", "r");
    if (fptr == NULL)
    {
        printf("Error,File Not Found!");
        exit(1);
    }
    else
    {
        while (fgets(line, sizeof(line), fptr))
        {
            numOfPoints++;
        }
    }
    return numOfPoints;
}
///////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));

    char line[50];
    int numberOfPoints = calculateNumberOfPoints();
    struct Point points[numberOfPoints];
    int index = 0;
    FILE *fptr;
    //////////////////////////////////////////
    fptr = fopen("points.txt", "r");
    if (fptr == NULL)
    {
        printf("Error,File Not Found!");
        exit(1);
    }
    while (fgets(line, 50, fptr) != NULL)
    {
        points[index].x = atoi(strtok(line, ","));
        points[index].y = atoi(strtok(NULL, ","));
        index++;
    }
    fclose(fptr);
    struct Point centers[THREADS];
    int centIndex = 0;
    // choosing First n points as centers for n clusters.
    for (centIndex; centIndex < THREADS; centIndex++)
    {
        points[centIndex].cluster = centIndex + 1;
        int randx = rand() % MAX;
        int randy = rand() % MAX;
        centers[centIndex].x = randx;
        centers[centIndex].y = randy;
        centers[centIndex].cluster = points[centIndex].cluster;
    }
    int distance[numberOfPoints][THREADS];
    int i;
#pragma omp parallel num_threads(THREADS) shared(points, centers, distance) private(i)
    {

#pragma omp for schedule(static)
        for (i = centIndex; i < numberOfPoints; i++)
        {
            struct Point p;
            p.x = centers[0].x;
            p.y = centers[0].y;
            p.cluster = 1;
            int j;

            for (j = 0; j < THREADS; j++)
            {
                distance[i][j] = sqrt(pow((points[i].x - centers[j].x), 2) + pow(points[i].y - centers[j].y, 2));
                // p.x = centers[j].x;
                // p.y = centers[j].y;
                // p.cluster = j + 1;
                // points[i].cluster = j + 1;
            }

            int MIN = 10000;
            int cluster_index = 0;
            for (int j = 0; j < THREADS; j++)
            {
                if (distance[i][j] < MIN)
                {
                    MIN = distance[i][j];
                    points[i].cluster = j + 1;
                }
            }

            int sumX = 0, sumY = 0, n = 0, k;
            for (k = 0; k < THREADS; k++)
            {
                if (points[k].cluster == points[i].cluster)
                {
                    sumX += points[k].x;
                    sumY += points[k].y;
                    n++;
                }
            }
            centers[points[i].cluster - 1].x = sumX / n;
            centers[points[i].cluster - 1].y = sumY / n;
        }
    }
    /* end of parallel region */

    int m1, m2;
    for (m1 = 1; m1 <= THREADS; m1++)
    {
        printf("Cluster %d:\n", m1);
        for (m2 = 0; m2 < numberOfPoints; m2++)
        {

            if (points[m2].cluster == m1)
            {
                printf("(%d,%d)\n", points[m2].x, points[m2].y);
            }
        }
        printf("\n");
    }
    return 0;
}
