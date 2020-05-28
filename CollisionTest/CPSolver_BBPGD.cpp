#include "CPSolver.hpp"
#include "Trilinos/TpetraUtil.hpp"

#include <mpi.h>
#include <omp.h>

#include <chrono>
#include <limits>
#include <random>

void CPSolver::clipZero(Teuchos::RCP<TV> &vecRcp) const {
    auto x_2d = vecRcp->getLocalView<Kokkos::HostSpace>(); // LeftLayout
    vecRcp->modify<Kokkos::HostSpace>();

    // int strides[2];
    // x_2d.stride(strides);
    // std::cout << strides[0] << " " << strides[1] << std::endl;
    // std::cout << std::is_same<decltype(x_2d)::array_layout, Kokkos::LayoutLeft>::value << std::endl;

    for (int c = 0; c < x_2d.dimension_1(); c++) {
#pragma omp parallel for
        for (int i = 0; i < x_2d.dimension_0(); i++) {
            const double temp = x_2d(i, c);
            x_2d(i, c) = temp < 0 ? 0 : temp;
        }
    }
    return;
}

void CPSolver::maxXY(const Teuchos::RCP<const TV> &vecXRcp, const Teuchos::RCP<const TV> &vecYRcp,
                     const Teuchos::RCP<TV> &vecZRcp) const {
#ifdef DEBUGLCPCOL
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecXRcp->getMap()->isSameAs(*(vecZRcp->getMap()))), std::invalid_argument,
                               "X and Z do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecYRcp->getMap()->isSameAs(*(vecZRcp->getMap()))), std::invalid_argument,
                               "Y and Z do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecXRcp->getNumVectors() == vecZRcp->getNumVectors()), std::invalid_argument,
                               "X and Z do not have the same Number of Vectors.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecYRcp->getNumVectors() == vecZRcp->getNumVectors()), std::invalid_argument,
                               "Y and Z do not have the same Number of Vectors.");
#endif

    auto x_2d = vecXRcp->getLocalView<Kokkos::HostSpace>();
    auto y_2d = vecYRcp->getLocalView<Kokkos::HostSpace>();
    auto z_2d = vecZRcp->getLocalView<Kokkos::HostSpace>();
    vecZRcp->modify<Kokkos::HostSpace>();
    for (int c = 0; c < x_2d.dimension_1(); c++) {
#pragma omp parallel for
        for (int i = 0; i < x_2d.dimension_0(); i++) {
            z_2d(i, c) = std::max(x_2d(i, c), y_2d(i, c));
        }
    }
    return;
}

void CPSolver::minXY(const Teuchos::RCP<const TV> &vecXRcp, const Teuchos::RCP<const TV> &vecYRcp,
                     const Teuchos::RCP<TV> &vecZRcp) const {
#ifdef DEBUGLCPCOL
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecXRcp->getMap()->isSameAs(*(vecZRcp->getMap()))), std::invalid_argument,
                               "X and Z do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecYRcp->getMap()->isSameAs(*(vecZRcp->getMap()))), std::invalid_argument,
                               "Y and Z do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecXRcp->getNumVectors() == vecZRcp->getNumVectors()), std::invalid_argument,
                               "X and Z do not have the same Number of Vectors.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecYRcp->getNumVectors() == vecZRcp->getNumVectors()), std::invalid_argument,
                               "Y and Z do not have the same Number of Vectors.");
#endif

    auto x_2d = vecXRcp->getLocalView<Kokkos::HostSpace>();
    auto y_2d = vecYRcp->getLocalView<Kokkos::HostSpace>();
    auto z_2d = vecZRcp->getLocalView<Kokkos::HostSpace>();
    vecZRcp->modify<Kokkos::HostSpace>();
    for (int c = 0; c < x_2d.dimension_1(); c++) {
#pragma omp parallel for
        for (int i = 0; i < x_2d.dimension_0(); i++) {
            z_2d(i, c) = std::min(x_2d(i, c), y_2d(i, c));
        }
    }
    return;
}

double CPSolver::checkResiduePhi(const Teuchos::RCP<const TV> &vecXRcp, const Teuchos::RCP<const TV> &vecYRcp,
                                 const Teuchos::RCP<TV> &vecTempRcp) const {
// Y=Ax+b
#ifdef DEBUGLCPCOL
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecXRcp->getMap()->isSameAs(*(vecTempRcp->getMap()))), std::invalid_argument,
                               "X and Z do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecYRcp->getMap()->isSameAs(*(vecTempRcp->getMap()))), std::invalid_argument,
                               "Y and Z do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecXRcp->getNumVectors() == vecTempRcp->getNumVectors()), std::invalid_argument,
                               "X and Z do not have the same Number of Vectors.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(vecYRcp->getNumVectors() == vecTempRcp->getNumVectors()), std::invalid_argument,
                               "Y and Z do not have the same Number of Vectors.");
#endif
    minXY(vecXRcp, vecYRcp, vecTempRcp);
    return static_cast<double>(vecTempRcp->norm2());
}

void CPSolver::hMinMap(const Teuchos::RCP<const TV> &xRcp, const Teuchos::RCP<const TV> &yRcp,
                       const Teuchos::RCP<TV> &hRcp, const Teuchos::RCP<TV> &maskRcp) const {
#ifdef DEBUGLCPCOL
    TEUCHOS_TEST_FOR_EXCEPTION(!(xRcp->getMap()->isSameAs(*(hRcp->getMap()))), std::invalid_argument,
                               "X and h do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(yRcp->getMap()->isSameAs(*(hRcp->getMap()))), std::invalid_argument,
                               "Y and h do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(xRcp->getNumVectors() == hRcp->getNumVectors()), std::invalid_argument,
                               "X and h do not have the same Number of Vectors.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(yRcp->getNumVectors() == hRcp->getNumVectors()), std::invalid_argument,
                               "Y and h do not have the same Number of Vectors.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(xRcp->getMap()->isSameAs(*(maskRcp->getMap()))), std::invalid_argument,
                               "X and mask do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(yRcp->getMap()->isSameAs(*(maskRcp->getMap()))), std::invalid_argument,
                               "Y and mask do not have the same Map.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(xRcp->getNumVectors() == maskRcp->getNumVectors()), std::invalid_argument,
                               "X and mask do not have the same Number of Vectors.");
    TEUCHOS_TEST_FOR_EXCEPTION(!(yRcp->getNumVectors() == maskRcp->getNumVectors()), std::invalid_argument,
                               "Y and mask do not have the same Number of Vectors.");
#endif
    // assume they are all of the same size, comm and map, do not check
    auto xView = xRcp->getLocalView<Kokkos::HostSpace>();
    auto yView = yRcp->getLocalView<Kokkos::HostSpace>();
    auto hView = hRcp->getLocalView<Kokkos::HostSpace>();
    auto maskView = maskRcp->getLocalView<Kokkos::HostSpace>();
    hRcp->modify<Kokkos::HostSpace>();
    maskRcp->modify<Kokkos::HostSpace>();

    for (int c = 0; c < xView.dimension_1(); c++) {
#pragma omp parallel for
        for (int i = 0; i < xView.dimension_0(); i++) {
            if (xView(i, c) < yView(i, c)) {
                hView(i, c) = xView(i, c);
                maskView(i, c) = 1;
            } else {
                hView(i, c) = yView(i, c);
                maskView(i, c) = 0;
            }
        }
    }

    return;
}

// constructor to set random A and b with given size
CPSolver::CPSolver(int localSize, double diagonal) {
    // set up comm
    commRcp = getMPIWORLDTCOMM();
    // set up row and col maps, contiguous and evenly distributed
    Teuchos::RCP<const TMAP> rowMapRcp = getTMAPFromLocalSize(localSize, commRcp);
    mapRcp = rowMapRcp;

    if (commRcp->getRank() == 0) {
        std::cout << "Total number of processes: " << commRcp->getSize() << std::endl;
        std::cout << "rank: " << commRcp->getRank() << std::endl;
        std::cout << "global size: " << mapRcp->getGlobalNumElements() << std::endl;
        std::cout << "local size: " << mapRcp->getNodeNumElements() << std::endl;
        std::cout << "map: " << mapRcp->description() << std::endl;
    }

    // make sure A and b match the map and comm specified
    // set A and b randomly. maintain SPD of A
    Teuchos::RCP<TV> btemp = Teuchos::rcp(new TV(rowMapRcp, false));
    btemp->randomize(-1, 1);
    bRcp = btemp.getConst();

    // generate a local random matrix

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0, 1);

    // a random matrix
    Teuchos::SerialDenseMatrix<int, double> BLocal(localSize, localSize, true); // zeroOut
    for (int i = 0; i < localSize; i++) {
        for (int j = 0; j < localSize; j++) {
            BLocal(i, j) = dis(gen);
        }
    }
    // a random diagonal matrix
    Teuchos::SerialDenseMatrix<int, double> ALocal(localSize, localSize, true);
    Teuchos::SerialDenseMatrix<int, double> tempLocal(localSize, localSize, true);
    Teuchos::SerialDenseMatrix<int, double> DLocal(localSize, localSize, true);
    for (int i = 0; i < localSize; i++) {
        DLocal(i, i) = fabs(dis(gen)) + 2;
    }

    // compute B^T D B
    tempLocal.multiply(Teuchos::NO_TRANS, Teuchos::NO_TRANS, 1.0, DLocal, BLocal, 0.0); // temp = DB
    ALocal.multiply(Teuchos::TRANS, Teuchos::NO_TRANS, 1.0, BLocal, tempLocal, 0.0);    // A = B^T DB

    for (int i = 0; i < localSize; i++) {
        ALocal(i, i) += diagonal;
    }

    // use ALocal as local matrix to fill TCMAT A
    // block diagonal distribution of A

    double droptol = 1e-7;
    Kokkos::View<size_t *> rowCount("rowCount", localSize);
    Kokkos::View<size_t *> rowPointers("rowPointers", localSize + 1);
    for (int i = 0; i < localSize; i++) {
        rowCount[i] = 0;
        for (int j = 0; j < localSize; j++) {
            if (fabs(ALocal(i, j)) > droptol) {
                rowCount[i]++;
            }
        }
    }

    rowPointers[0] = 0;
    for (int i = 1; i < localSize + 1; i++) {
        rowPointers[i] = rowPointers[i - 1] + rowCount[i - 1];
    }
    Kokkos::View<int *> columnIndices("columnIndices", rowPointers[localSize]);
    Kokkos::View<double *> values("values", rowPointers[localSize]);
    int p = 0;
    for (int i = 0; i < localSize; i++) {
        for (int j = 0; j < localSize; j++) {
            if (fabs(ALocal(i, j)) > droptol) {
                columnIndices[p] = j;
                values[p] = ALocal(i, j);
                p++;
            }
        }
    }

    const int myRank = commRcp->getRank();
    const int colIndexCount = rowPointers[localSize];
    std::vector<int> colMapIndex(colIndexCount);
#pragma omp parallel for
    for (int i = 0; i < colIndexCount; i++) {
        colMapIndex[i] = columnIndices[i] + myRank * localSize;
    }

    // sort and unique
    std::sort(colMapIndex.begin(), colMapIndex.end());
    colMapIndex.erase(std::unique(colMapIndex.begin(), colMapIndex.end()), colMapIndex.end());

    Teuchos::RCP<TMAP> colMapRcp = Teuchos::rcp(
        new TMAP(Teuchos::OrdinalTraits<int>::invalid(), colMapIndex.data(), colMapIndex.size(), 0, commRcp));

    // fill matrix Aroot
    Teuchos::RCP<TCMAT> Atemp = Teuchos::rcp(new TCMAT(rowMapRcp, colMapRcp, rowPointers, columnIndices, values));
    Atemp->fillComplete(rowMapRcp, rowMapRcp);
    this->ARcp = Teuchos::rcp_dynamic_cast<const TOP>(Atemp, true);
    // ARcp = Atemp;
    std::cout << "ARcp" << ARcp->description() << std::endl;

    // dump matrix
    dumpTCMAT(Atemp, "Amat");
    dumpTV(bRcp, "bvec");
}

// read A and b generated by the constructor from file
CPSolver::CPReadA(std::string filename) {
    // set up comm
    commRcp = getMPIWORLDTCOMM();
    // read file
    Tpetra::MatrixMarket::Reader<TCMAT> matDumper;
    Teuchos::RCP<TCMAT> Atemp = matDumper.readSparseFile(filename, commRcp, true, false, false);
    this->ARcp = Teuchos::rcp_dynamic_cast<const TOP>(Atemp, true);
    std::cout << "ARcp" << ARcp->description() << std::endl;
}

// read A and b generated by the constructor from file
CPSolver::CPReadb(std::string filename) {
    // set up comm
    commRcp = getMPIWORLDTCOMM();
    // read file
    Tpetra::MatrixMarket::Reader<TV> matDumper;
    this->bRcp = matDumper.readDenseFile(filename, commRcp, true, false, false);
}

int CPSolver::LCP_BBPGD(Teuchos::RCP<TV> &xsolRcp, const double tol, const int iteMax, IteHistory &history) const {
    int mvCount = 0; // count matrix-vector multiplications
    int iteCount = 0;
    if (commRcp->getRank() == 0) {
        std::cout << "solving BBPGD" << std::endl;
        std::cout << "ARcp" << ARcp->description() << std::endl;
    }
    // convention in the iteratin:

    // map must match
    TEUCHOS_TEST_FOR_EXCEPTION(!this->mapRcp->isSameAs(*(xsolRcp->getMap())), std::invalid_argument,
                               "xsolrcp and A operator do not have the same Map.");
    Teuchos::RCP<TV> xkRcp = Teuchos::rcp(new TV(*xsolRcp, Teuchos::Copy));   // deep copy, xk=x0
    Teuchos::RCP<TV> xkm1Rcp = Teuchos::rcp(new TV(*xsolRcp, Teuchos::Copy)); // deep copy, xkm1=x0

    Teuchos::RCP<TV> gradkRcp = Teuchos::rcp(new TV(this->mapRcp.getConst(), true));   // the grad vector
    Teuchos::RCP<TV> gradkm1Rcp = Teuchos::rcp(new TV(this->mapRcp.getConst(), true)); // the grad vector

    Teuchos::RCP<TV> gkdiffRcp = Teuchos::rcp(new TV(this->mapRcp.getConst(), true)); // gkdiff = gk - gkm1
    Teuchos::RCP<TV> xkdiffRcp = Teuchos::rcp(new TV(this->mapRcp.getConst(), true)); // xkdiff = xk - xkm1

    // compute grad
    ARcp->apply(*xkm1Rcp, *gradkm1Rcp); // gkm1 = A.dot(xkm1)
    mvCount++;
    gradkm1Rcp->update(1.0, *bRcp, 1.0); // gkm1 = A.dot(xkm1)+b

    // check if initial guess works, use xkdiffRcp as temporary space
    double resPhi = checkResiduePhi(xkm1Rcp, gradkm1Rcp, xkdiffRcp);
    history.push_back(std::array<double, 6>{{1.0 * iteCount, 0, 0, 0, resPhi, 1.0 * mvCount}});
    if (fabs(resPhi) < tol) {
        // initial guess works, return
        xsolRcp = xkm1Rcp;
        return 0;
    }

    // first step, simple Gradient Descent stepsize = g^T g / g^T A g
    // use xkdiffRcp as temporary space
    ARcp->apply(*gradkm1Rcp, *xkdiffRcp); // Avec = A * gkm1
    mvCount++;

    double gTAg = gradkm1Rcp->dot(*xkdiffRcp);
    double gTg = pow(gradkm1Rcp->norm2(), 2);

    if (fabs(gTAg) < 10 * std::numeric_limits<double>::epsilon()) {
        gTAg += 10 * std::numeric_limits<double>::epsilon(); // prevent div 0 error
    }

    double alpha = gTg / gTAg;

    while (iteCount < iteMax) {
        iteCount++;

        // update xk
        xkRcp->update(-alpha, *gradkm1Rcp, 1.0, *xkm1Rcp, 0.0); //  xk = xkm1 - alpha*gkm1
        clipZero(xkRcp);                                        // Projection xk >= 0

        // compute new grad with xk
        ARcp->apply(*xkRcp, *gradkRcp); // gk = A.dot(xk)
        mvCount++;
        gradkRcp->update(1.0, *bRcp, 1.0); // gk = A.dot(xk)+b

        // check convergence, use xkdiffRcp as temporary space
        double resPhi = checkResiduePhi(xkRcp, gradkRcp, xkdiffRcp);

#ifdef DEBUGLCPCOL
        // check convergence
        double resxMax = xkmxkm1Rcp->normInf();
        double resAxbMax = ykmykm1Rcp->normInf();
        history.push_back(std::array<double, 6>{{1.0 * iteCount, resxMax, resAxbMax, alphak, resPhi, 1.0 * mvCount}});
        if (fabs(resxMax) < tol && fabs(resAxbMax) < tol && fabs(resPhi) < tol) {
            break;
        }
#else
        // use simple phi tolerance check
        history.push_back(std::array<double, 6>{{1.0 * iteCount, 0, 0, alpha, resPhi, 1.0 * mvCount}});
        if (fabs(resPhi) < tol) {
            break;
        }
#endif
        xkdiffRcp->update(1.0, *xkRcp, -1.0, *xkm1Rcp, 0.0);       // xk - xkm1
        gkdiffRcp->update(1.0, *gradkRcp, -1.0, *gradkm1Rcp, 0.0); // gk - gkm1

        double a = 0, b = 0;
        // Barzilai-Borwein step size Choice 1
        a = pow(xkdiffRcp->norm2(), 2);
        b = xkdiffRcp->dot(*gkdiffRcp);

        // Barzilai-Borwein step size Choice 2
        // a = xkdiffRcp->dot(*gkdiffRcp);
        // b = pow(gkdiffRcp->norm2(),2);

        if (fabs(b) < 10 * std::numeric_limits<double>::epsilon()) {
            b += 10 * std::numeric_limits<double>::epsilon(); // prevent div 0 error
        }

        alpha = a / b; // new step size

        // prepare next iteration
        // swap the contents of pointers directly, be careful
        xkm1Rcp.swap(xkRcp);
        gradkm1Rcp.swap(gradkRcp);
    }

    xsolRcp = xkRcp; // return solution
    // Teuchos::TimeMonitor::summarize();

    return 0;
}