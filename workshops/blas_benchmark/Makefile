CXX = icpc
OPT = -O3
EXE = blas_cpu blas_gpu blas_mic

all : $(EXE)

blas_cpu : blas.cpp
	$(CXX) $(OPT) -xCORE-AVX2 $^ -o $@ -lafcpu

blas_gpu : blas.cpp
	$(CXX) $(OPT) -xCORE-AVX2 $^ -o $@ -lafcuda

blas_mic : blas.cpp
	$(CXX) $(OPT) -xMIC-AVX512 $^ -o $@ -lafcpu

clean :
	rm -rf $(EXE)

