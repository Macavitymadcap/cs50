# CS50

This is my attempt at taking Harvard's CS50 course, based on material found [here](https://cs50.harvard.edu/x/2023/). 

Week 0 on Scratch has been skipped, so this repository covers from Week 1 on C to Week 10 on emojis.

# Set up 
Multiple languages are used in the course: building and compiling the programs contained herein depends on the given langugage or langauges involved.

## (C Programs)

Download the cs50 lib [here](https://github.com/cs50/libcs50) and install locally at `/usr/local/`.

Some programs are bundled with Makefiles using `clang` to build them. For programs without Makefiles do the following: 

1. Copy the `Makefile.template` from the base directory into the folder containing the c files you want to compile.
2. Replace `[file]` with the name of the file to make. (Copy/paste for all files in folder if desired)
3. Run `make [file]` to make the given file.
4. Run `./[file]` to run the compiled code.