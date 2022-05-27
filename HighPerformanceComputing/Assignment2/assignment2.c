// Mostafa Nasser Mohamed 20190537

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <omp.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define INT_MAX 1000000

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

struct Point
{
    int x;
    int y;
    int preClusterId;
    int currentClusterId;
};

struct Cluster
{
    int id;
    int pre_size;
    int current_size;
    struct Point centroid;
};

// get the max x and min x of the data set
struct Point get_x_MaxMin(struct Point points[], int size)
{
    int i;
    int x_max = points[0].x;
    int x_min = points[0].x;
    for (i = 0; i < size; i++)
    {
        if (points[i].x > x_max)
        {
            x_max = points[i].x;
        }
        if (points[i].x < x_min)
        {
            x_min = points[i].x;
        }
    }
    struct Point x_max_min;
    x_max_min.x = x_max;
    x_max_min.y = x_min;
    return x_max_min;
}

// get the max y and min y of the data set
struct Point get_y_MaxMin(struct Point points[], int size)
{
    int i;
    int y_max = points[0].y;
    int y_min = points[0].y;
    for (i = 0; i < size; i++)
    {
        if (points[i].y > y_max)
        {
            y_max = points[i].y;
        }
        if (points[i].y < y_min)
        {
            y_min = points[i].y;
        }
    }
    struct Point y_max_min;
    y_max_min.x = y_max;
    y_max_min.y = y_min;
    return y_max_min;
}

int main(int argc, char *argv[])
{
    time_t t;
    /* Intializes random number generator */
    srand((unsigned)time(&t));

    FILE *fp = fopen("txt/points.txt", "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    char line[50];
    int i = 0;
    int numberOfPoints = count_file_lines("txt/points.txt"), THREADS;
    struct Point points[numberOfPoints];
    while (fgets(line, 50, fp) != NULL)
    {
        int x, y;
        char *token = strtok(line, ",");
        x = atoi(token);
        token = strtok(NULL, ",");
        y = atoi(token);
        points[i].x = x;
        points[i].y = y;
        i++;
    }
    fclose(fp);

#pragma omp parallel
    {
        THREADS = omp_get_num_threads();
    }

    struct Cluster clusters[THREADS]; // create clusters for the number of given threads

    struct Point Min_Max_x = get_x_MaxMin(points, numberOfPoints); // get max and min x
    struct Point Min_Max_y = get_y_MaxMin(points, numberOfPoints); // get max and min y

    int x_max = Min_Max_x.x;
    int x_min = Min_Max_x.y;
    int y_max = Min_Max_y.x;
    int y_min = Min_Max_y.y;

    // first assign the random centroids for each cluster
    for (int i = 0; i < THREADS; i++)
    {
        clusters[i].id = i + 1;
        clusters[i].pre_size = 0;
        clusters[i].current_size = 0;
        clusters[i].centroid.x = (rand() % (x_max - x_min + 1)) + x_min; // random centroid x between min and max x
        clusters[i].centroid.y = (rand() % (y_max - y_min + 1)) + y_min; // random centroid y between min and max y
    }

    // get the nearest cluster for each point
    int min_dist = INT_MAX;
    int min_cluster = 0;
    for (int i = 0; i < numberOfPoints; ++i)
    {
#pragma omp parallel
        {
            int local_min_dist = INT_MAX;
            int local_min_cluster = 0;
#pragma omp for nowait
            for (int j = 0; j < THREADS; ++j)
            {
                int x_diff = abs(points[i].x - clusters[j].centroid.x);
                int y_diff = abs(points[i].y - clusters[j].centroid.y);
                int dist = sqrt(x_diff * x_diff + y_diff * y_diff);
                if (dist < local_min_dist)
                {
                    local_min_dist = dist;
                    local_min_cluster = j;
                }
            }
#pragma omp critical
            {
                if (local_min_dist < min_dist)
                {
                    min_dist = local_min_dist;
                    min_cluster = local_min_cluster;
                }
            }
        }
        points[i].currentClusterId = min_cluster + 1;
        clusters[min_cluster].current_size++;
    }
    struct Point sums[THREADS];
    for (int i = 0; i < THREADS; ++i)
    {
        sums[i].x = 0;
        sums[i].y = 0;
    }
// update the centroids of each cluster using mean equation
#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < THREADS; ++i)
        {
            for (int j = 0; j < numberOfPoints; ++j)
            {
                if (points[j].currentClusterId == i + 1)
                {
                    sums[i].x += points[j].x;
                    sums[i].y += points[j].y;
                }
            }
        }

#pragma omp barrier
        for (int i = 0; i < THREADS; ++i)
        {
            if (sums[i].x != 0 && sums[i].y != 0)
            {
                clusters[i].centroid.x = sums[i].x / clusters[i].current_size;
                clusters[i].centroid.y = sums[i].y / clusters[i].current_size;
            }
        }
    }

    // check if the clusters are stable
    bool stable = false;
    int max_iterations = 50;
    // do this until the clusters are stable or reach the maximum iteration

    while (true)
    {
        if (stable || max_iterations == 0)
        {
            break;
        }

        stable = true;
        for (int i = 0; i < THREADS; ++i)
        {
            clusters[i].pre_size = clusters[i].current_size;
            clusters[i].current_size = 0;
        }

        for (int i = 0; i < numberOfPoints; ++i)
        {
            points[i].preClusterId = points[i].currentClusterId;
            points[i].currentClusterId = -1;
        }

        // update the cluster for each point based on the new centroids
        for (int i = 0; i < numberOfPoints; ++i)
        {
            int min_dist = INT_MAX;
            int min_cluster = 0;
            for (int j = 0; j < THREADS; ++j)
            {
                int x_diff = abs(points[i].x - clusters[j].centroid.x);
                int y_diff = abs(points[i].y - clusters[j].centroid.y);
                int dist = sqrt(x_diff * x_diff + y_diff * y_diff);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    min_cluster = j;
                }
            }
            points[i].currentClusterId = min_cluster + 1;
            clusters[min_cluster].current_size++;
        }

        // check if clustering is not change from the previous iteration
        for (int i = 0; i < numberOfPoints; ++i)
        {
            if (points[i].currentClusterId != points[i].preClusterId)
            {
                stable = false;
                break;
            }
        }

        // update the centroids of each cluster if clustering is change
        if (!stable)
        {
            for (int i = 0; i < THREADS; ++i)
            {
                int x_sum = 0;
                int y_sum = 0;
                for (int j = 0; j < numberOfPoints; ++j)
                {
                    if (points[j].currentClusterId == i + 1)
                    {
                        x_sum += points[j].x;
                        y_sum += points[j].y;
                    }
                }
                if (x_sum != 0 && y_sum != 0)
                {
                    clusters[i].centroid.x = x_sum / clusters[i].current_size;
                    clusters[i].centroid.y = y_sum / clusters[i].current_size;
                }
            }
        }
        max_iterations--;
    }

    // print the final clusters
    for (int i = 0; i < THREADS; ++i)
    {
        printf("Cluster %d: ", i + 1);
        for (int j = 0; j < numberOfPoints; ++j)
        {
            if (points[j].currentClusterId == i + 1)
            {
                printf("(%d, %d) ", points[j].x, points[j].y);
            }
        }
        printf("\n");
    }
}