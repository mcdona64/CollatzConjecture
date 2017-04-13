#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

int collatz(int start, int end) {
	//set the counter
	double n = (double)start;
	
	while (n <= end) {
		//run the function untill it is zero
		double mut = n;
		while (mut != 1 && !(start < mut && mut < n)) { // if the second condition is true then we know that it will work
			if ((int)mut % 2 == 0){
	 			mut = mut / 2;
			} else if ((int)mut % 2 == 1){
				mut = mut * 3 + 1;
			}
			printf("%d\n",mut);
		}
		n++;

	}
}

int main(int argc, char* argv[]) {
	//make sure that there was the correct numbers entered
	if (argc < 0) {
		printf("ussage error type the range of numbers you want to check");
		return 0;
	}
	
	//make nessicarly local variables 
	int start = atoi(argv[1]);
	int end = atoi(argv[2]);
	clock_t sclock, eclock;
	int status;

	//start the clock to time the program
	sclock = clock();
	int pid = fork();

	//devide the work into two threads
	if (pid == 0) {
		collatz(start, end / 2);
		
	} else {
		collatz(end / 2, end);
	}

	//join the threads
	if (pid == 0) {
		return 0;
	}
	wait(&status);
	

	//end the clock
	eclock = clock();

	//print results to the screan and file
	printf("it worked\n");
	std::ofstream highscore;
	highscore.open("highscores.txt", std::fstream::app);
	highscore << "start: " << start << "\t|\tend: " << end << "\t|\t time: " << (double)((eclock - sclock)/CLOCKS_PER_SEC) << "\n";
	highscore.close();
	return 0;
}
