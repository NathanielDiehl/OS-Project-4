#!/bin/bash

#SBATCH --mem-per-cpu=1G
##300M

#SBATCH --time=1:00:00

##SBATCH --gres=gpu:1

#SBATCH --cpus-per-task=5
#SBATCH --nodes=1 --tasks-per-node=1
#SBATCH --tasks=1

#SBATCH --constraint=moles

#SBATCH --output=PTHREADS.out
##SBATCH --error=PTHREADS.err

#SBATCH -J 1

/homes/yourusesname/hw/hw4/pthreads/main