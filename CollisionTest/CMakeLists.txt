# Example of how to compile and link target_compile_options
# target_include_directories target_link_libraries

add_executable(CPSolver_BBPGD_test CPSolver_BBPGD_test.cpp CPSolver_BBPGD.cpp
                             ${PROJECT_SOURCE_DIR}/Trilinos/TpetraUtil.cpp)
target_compile_options(CPSolver_BBPGD_test PRIVATE ${OpenMP_CXX_FLAGS})
target_include_directories(
  CPSolver_BBPGD_test PRIVATE ${PROJECT_SOURCE_DIR} ${Trilinos_INCLUDE_DIRS}
                        ${TRNG_INCLUDE_DIR})
target_link_libraries(
  CPSolver_BBPGD_test PRIVATE ${Trilinos_LIBRARIES} ${Trilinos_TPL_LIBRARIES}
                        ${TRNG_LIBRARY} OpenMP::OpenMP_CXX MPI::MPI_CXX)
add_test(NAME CPSolver_BBPGD COMMAND CPSolver_BBPGD_test)
