# graphs

I have grown weary of failing to build environments in HPC clusters.
I have grown weary of bad experience with LSPs attempting to inference types.

The broad goal of this repo is to experiment in building networks in C for production-ready data science use.

The sub-goals are thus:

- Make it so that I don't have to worry much about building python environments in HPC systems.
- Build extremely efficient code.
- Understand what is happening on the backend of packages like `python-igraph`, `pandas`, etc.
- Learn some C.
- Ideally build up to something that can be used as a daily-driver toolbox of data science functions, structs, etc.

## Motivation

I find myself often getting OOM errors in python after wasting hours in HPC jobs. The idea is that I can pre-allocate all memory before running any complex functions. That way, if I run out of memory, I will know in the first seconds rather than after hours.
