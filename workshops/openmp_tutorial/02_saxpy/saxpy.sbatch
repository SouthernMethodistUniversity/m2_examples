#!/bin/bash
#SBATCH -J saxpy
#SBATCH -o saxpy.out
#SBATCH -p mic
#SBATCH --mem=374G
#SBATCH --exclusive
#SBATCH -N 1
#SBATCH --ntasks-per-node=1

module purge
module load intel-18.0.1

# --- Intel affinity controls ---

# Launch 64 threads, one per physical core
export KMP_HW_SUBSET=64c,1t
export KMP_AFFINITY=compact,granularity=core

# Launch 256 threads, four per physical core
#export KMP_HW_SUBSET=64c,4t
#export KMP_AFFINITY=compact,granularity=core

# --- OpenMP affinity controls ---

# Launch 64 threads, one per physical core
#export OMP_NUM_THREADS=64
#export OMP_PLACES="cores(64)"
#export OMP_PROC_BIND=spread

# Launch 256 threads, four per physical core
#export OMP_NUM_THREADS=256
#export OMP_PLACES={0,68,136,204}:64
#export OMP_PROC_BIND=close

srun ./saxpy 

