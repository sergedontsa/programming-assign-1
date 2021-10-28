/**
 * Created by Serge Dontsa on 2021-10-18.
 * COMP-428 ASSIGNMENT -1 PROGRAMMING QUESTION
 * Concordia University
 */




#include "mpi.h"
#include <cstdio>
#include <cmath>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <ctime>
#include <cstdint>
#include <sys/time.h>
#include <iostream>


double func(double a )
{
    return (4.0 / (1.0 + a*a));
}

/**
 * Parallel version
 */

int main( int argc, char *argv[])
{
    int done = 0, n, myid, numprocs, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;
    double startwtime = 0.0, endwtime;
    int  namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);

    fprintf(stderr,"Process %d on %s\n",
            myid, processor_name);

    n = 0;
    while (!done)
    {
        if (myid == 0)
        {

            if (n==0) {
                n = 1024 * numprocs;
            }
            else {
                n = 0;
            }

            startwtime = MPI_Wtime();
        }
        MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (n == 0)
            done = 1;
        else
        {
            h   = 1.0 / (double) n;
            sum = 0.0;
            for (i = myid + 1; i <= n; i += numprocs)
            {
                x = h * ((double)i - 0.5);
                sum += func(x);
            }
            mypi = h * sum;

            MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

            if (myid == 0)
            {
                printf("pi is approximately %.16f, Error is %.16f\n",
                       pi, fabs(pi - PI25DT));
                endwtime = MPI_Wtime();
                printf("wall clock time = %func\n",
                       endwtime-startwtime);
            }
        }
    }
    MPI_Finalize();

    return 0;
}






/**
 *Serial version
 */

// int main(int argc, char *argv[])
//{
//    int done = 0, n, i;
//    double PI25DT = 3.141592653589793238462643;
//    double mypi, pi, h, sum, x;
//    double startwtime, endwtime;
//    struct timeval tv;
//
//    n = 0;
//    while (!done)
//    {
//        printf("Enter the number of user: (0 quits) ");
//        scanf("%d",&n);
//
//        if (n!=0)
//        {
//            if (gettimeofday(&tv, nullptr) == 0)
//                startwtime = tv.tv_sec*1000000+tv.tv_usec;
//            else
//                startwtime = 0;
//
//            h   = 1.0 / (double) n;
//            sum = 0.0;
//            for (i = 1; i <= n; i += 1)
//            {
//                x = h * ((double)i - 0.5);
//                sum += func(x);
//            }
//            mypi = h * sum;
//
//            printf("PI: %.16f, Error: %.16f\n Number of intervals: %5d\n", mypi, fabs(mypi - PI25DT),n);
//
//            if (gettimeofday(&tv, nullptr) == 0)
//                endwtime = tv.tv_sec*1000000+tv.tv_usec;
//            else
//                endwtime = 0;
//
//            printf("wall clock time: %.0f usecs \n", (endwtime-startwtime));
//        }
//        else
//
//            return 0;
//    }
//}