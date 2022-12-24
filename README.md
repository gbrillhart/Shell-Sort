# Shell-Sort #

### Program Info: ###
Shell-Sort is an implementation of the Shell Sorting algorithm written by myself in C. The shell sorting can be done with an array of memory or with a linked list. The code reads in a file of size(long) integers, sorts the integers using an array or a linked list according to the runtime arguments, prints the number of comparisons, and stores the sorted list as a binary output file. Both methods of sorting follow standard Shell Sorting time complexity, with the worst case O(n^2), best case of O(n*log(n)) and average case complexity of O(n^1.25).
- - - - 
### Usage: ###
To compile, use 'gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic shell_array.c shell_list.c shellsort.c -o shellsort'.

To sort using an array: './shellsort -a inputfile.b outputfile.b'

To sort using a linked list: './shellsort -l inputfile.b outputfile.b'
- - - -
### Specifications: ###
 - The program reads in at most INTMAX long integers from a binary file and outputs the sorted integers as long integers ina  binary file.
 - If the input file is unable to be opened or is empty, it will be treated as a array of size 0 and an output file will still be created.
 - An invalid runtime arguement (i.e. not -a or -l) will result in no sorting being done.

- - - -
### Source Code Descriptions: ###
**shellsort.c** : the main file responsible for overall code flow and calling respective functions.
**shell_array.c** : source code responsible for loading, sorting, and writing the list of integers using an array.
**shell_list.c** : source code responsible for loading, sorting, and writing the list of integers using a linked list.
**shell_array.h** : header file for shell_array.c.
**shell_list.h** : header file for shell_list.c.
- - - -
### Test File Descriptions: ###
**Unsorted Test Files** :  Folder containing binary files with varying amounts of unsorted long integers.
 - 1K.b : contains 1000 unsorted long integers
 - 10K.b : contains 10,000 unsorted long integers
 - 100K.b : contains 100,000 unsorted long integers
 - 1M.b : contains 1,000,000 unsorted long integers
**Sorted Test Files** :  Folder containing binary files of the corresponding sorted long integers from Unsorted Test Files
 - 1Ks.b : contains 1000 sorted long integers
 - 10Ks.b : contains 10,000 sorted long integers
 - 100Ks.b : contains 100,000 sorted long integers
 - 1Ms.b : contains 1,000,000 sorted long integers
- - - -
Note: This code was developed for ECE 36800 with Professor Koh at Purdue University.
