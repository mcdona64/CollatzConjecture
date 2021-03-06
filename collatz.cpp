#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

int collatz(int start, int end) {
	//set the counter
	long long int n = (long long int)start;
	
	while (n <= end) {
		//run the function untill it is zero
		long long int mut = n;
		
		//printf("s:%d e:%d n: %llum:%llu\n",start, end,n,mut);
		while (mut != 1 && !(start < mut && mut < n)) { // if the second condition is true then we know that it will work
			if (mut % 2 == 0){
	 			mut = mut / 2;
			} else if (mut % 2 == 1){
				mut = mut * 3 + 1;
			}
			if(mut < 1) {
				printf("error: negative number");
				return 1;
			}
			//printf("%llu\t%d\n",mut,(mut != 1));
		}
		n++;

	}
	return 0;
}

int main(int argc, char* argv[]) {
	//make sure that there was the correct numbers entered
	if (argc < 4) {
		printf("ussage error type the range of numbers you want to check and the number of threads\n");
		return 0;
	}
	
	//make nessicarly local variables 
	int start = atoi(argv[1]);
	int end = atoi(argv[2]);
	int numFork = atoi(argv[3]);
	//clock_t sclock, eclock;
	struct timespec s, f;
	double time;
	int status;

	//start the clock to time the program
	//sclock = clock();
	clock_gettime(CLOCK_MONOTONIC, &s);
	
	//start the correct number of threads
	for (int i = 1; i < numFork + 1; i++) {
		int pid = fork();
		if (pid == 0) {
			if (collatz(i*((end - start)/(numFork+1)), (i+1)*((end - start)/(numFork+1))) != 0) {
				printf("error in fork\n");
			}
			return 0;		
		} 
	}

	//join the threads
	if (numFork > 0) {
		wait(&status);
	} else {
		if (collatz(start, end) != 0) {
			printf("error\n");
		}
	}

	//end the clock
	//eclock = clock();
	clock_gettime(CLOCK_MONOTONIC, &f);
	time = (f.tv_sec - s.tv_sec);
	time += (f.tv_nsec - s.tv_nsec) / 1000000000.0;
	//double time = eclock - sclock;
	//time = time / (CLOCKS_PER_SEC/1000);

	//print results to the screan and file
	printf("it worked\n");
	std::ofstream highscore;
	highscore.open("highscores.txt", std::fstream::app);
	highscore << "start: " << start << "\t|\tend: " << end << "\t|\t time: " 
		<< time << "\t|\t Threads: "
		<< numFork << "\n";
	highscore.close();
	return 0;
}
