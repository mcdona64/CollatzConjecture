#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>

int main(int argc, char* argv[]) {
	if (argc < 0) {
		printf("ussage error type the range of numbers you want to check");
		return 0;
	}
	bool faild = 0;
	int start = atoi(argv[1]);
	double n = (double)start;
	int end = atoi(argv[2]);
	clock_t sclock, eclock;
	sclock = clock();
	while (faild == 0 && n <= end) {
		double mut = n;
		while (mut != 1 && !(start < mut && mut < n)) {
			if ((int)mut % 2 == 0){
	 			mut = mut / 2;
			} else if ((int)mut % 2 == 1){
				mut = mut * 3 + 1;
			}
			//printf("%lf\n",mut);
		}
		n++;
	}
	eclock = clock();
	if (faild != 0){
		printf("it faild at %lf\n", n);
	} else {
		printf("it worked\n");
		std::ofstream highscore;
		highscore.open("highscores.txt", std::fstream::app);
		highscore << "start: " << start << "\t|\tend: " << end << "\t|\t time: " << (double)((eclock - sclock)/CLOCKS_PER_SEC) << "\n";
		highscore.close();
	}
	return 0;
}
