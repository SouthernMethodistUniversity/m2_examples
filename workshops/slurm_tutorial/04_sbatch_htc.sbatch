#!/bin/bash
#SBATCH -J python
#SBATCH -o python_%j.out
#SBATCH -p development,htc
#SBATCH -c 1
#SBATCH --mem=6G 

module purge
module load python

time python pi_monte_carlo.py 1000

