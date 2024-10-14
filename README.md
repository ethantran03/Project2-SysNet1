# Project2-SysNet1

## Multi-Threaded Collatz Stopping Time generator

### Descrrption:
This project computes the stopping time for the Collatz sequence between 1 to 100,000 using differing multiple threads. The program generates a histogram of the stopping times and measuring the runtime with different thread counts.

#### How to Build:
To run the program type "make" into the terminal

Next to generate the histogram and measure the run time type "./mt-collatz <100000> <any number of threads you want> [-nolock] 2> result.csv"
This will generate the number text file with the number of elements which is 100000, number of threads, and the runtime.

##### Example
An example command that you could use would be "./mt-collatz 100000 4 [-nolock] 2> result.csv"
This will run it with mutex functions off and generate the runtime value

Another example command could be "./mt-collatz 100000 4 > histogram.csv 2> runtime.csv"
This would generate two text files with one containing the values of the histogram and the frequency of stopping. The other would create a the element of the array, number of threads and runtime.

After the program creates the file you can check them by running the "cat" command following the files name to see the results inside.
