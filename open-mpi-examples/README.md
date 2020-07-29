## parallel programming with OPEN MPI

* install openmpi library in ubuntu:

> sudo apt install libopenmpi-dev

* compile openmpi file:

> mpicc (source_filename)
>
> -o rename output filename
>
> -O2 run optimize process in compiler

* run with this command:

> mpirun -np (number_of_threads) (output_file_name)
