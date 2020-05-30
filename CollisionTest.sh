#!/bin/bash
module load cmake
module load intel-mkl

root="build/CollisionTest"
echo $root

testsize=500
echo "Test problem size: $testsize"
echo "-------------------------------------------------"

for k in {0..4}
do
  export OMP_NUM_THREADS=$((2**$k))
  echo "Number of OpenMP threads: $OMP_NUM_THREADS"
  echo "Executing command: $root/CPSolver_test $testsize ..."
  echo "------------------------------------------------------"
  $root/CPSolver_BBPGD_test $testsize
  echo "------------------------------------------------------"
done
export OMP_NUM_THREADS=24
echo "Number of OpenMP threads: $OMP_NUM_THREADS"
echo "Executing command: $root/CPSolver_test $testsize ..."
echo "------------------------------------------------------"
$root/CPSolver_BBPGD_test $testsize
echo "------------------------------------------------------"