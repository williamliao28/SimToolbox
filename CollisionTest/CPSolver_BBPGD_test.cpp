#include "CPSolver_BBPGD.hpp"
#include <mpi.h>

#include <vector>

int main(int argc, char **argv) {
    int threadnum;
    
    #pragma omp parallel
    {
        int rank = omp_get_thread_num();
        threadnum = omp_get_num_threads();
        if (rank == 0)
        {
            printf("Number of threads: %d\n",threadnum);
        }
    }
    //printf("Number of threads (outside parallel): %d\n",threadnum);

    MPI_Init(&argc, &argv);
    {

        const int globalSize = argc > 1 ? atoi(argv[1]) : 500;
        const double diagonal = argc > 2 ? atof(argv[2]) : 0.0;
        CPSolver lcptest(globalSize, threadnum, diagonal);

        double tol = 1e-5;

        //lcptest.test_LCP(tol, globalSize, 0); // mmNewton
        //lcptest.test_LCP(tol, globalSize, 1); // APGD
        lcptest.test_LCP(tol, globalSize, 2); // BBPGD
        //lcptest.test_LCP(tol, globalSize, 3); // APGD+Newton
        //lcptest.test_LCP(tol, globalSize, 4); // BBPGD+mmNewton
    }

    MPI_Finalize();
    return 0;
}