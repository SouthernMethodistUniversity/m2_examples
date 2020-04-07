#!/bin/bash
#SBATCH -J pi
#SBATCH -o pi_%j.out
#SBATCH -p development,htc
#SBATCH --mem=6G
#SBATCH -N 1
#SBATCH -c 2

module purge
module load python

time python pi_monte_carlo_shared.py 10000000 ${SLURM_NTASKS}

