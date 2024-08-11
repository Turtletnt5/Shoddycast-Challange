/*

This is my submission for Challenge: beat Austin's python code that took 8 days to run 1 billion sample dice rolls 

You will find to consetent varibles bellow one for the total rolls and one for number of threads used.
I am testing this on an intel i9-11980hk which has a max thread count of 16.
So for max preformance lookup your processors max thread count and ajust acordinlly 

The time it took was 3004743 miliseconds

By Turtletnt5



*/

//Number of dice rolls total Edit this
const int TotalRolls = 1000000000;
//total threads to make expect one extra for non even dividsion
const int TotalThreads = 16;



//Multithreding
#include "thread"
//So we dont blow up the program with multithreading
#include "shared_mutex"
//random number generator
#include "random"
//vector class
#include "vector"
//code to time the hole task
#include "Timing.h"

//make it look cleaner
using namespace std;


//HighestRoll
int HigherstProcs = 0;

//rolls completed
int rollsComplete = 0;

//mutex used for multithreading
shared_mutex m;

//create vector to store threads
vector<thread> threads;


void RollSession(int totalRolls) {

	//multithreading safty
	unique_lock<shared_mutex> Ulock(m);
	Ulock.unlock();

	for (int rolls = 0; rolls < totalRolls; rolls++) {
		// number of times rand hits 1
		int totalProcs = 0;

		//initialize randomnise
		std::random_device r;
		default_random_engine e1(r());
		uniform_int_distribution<int> uniform_dist(1, 4);

		//loop through 231 turns
		for (int i = 0; i < 231; i++) {


			// if rand is equal to 1
			if (uniform_dist(e1) == 1) {
				totalProcs++;
			}

		}

		//test code uncomment below to print each roll
		//printf("total was %d \n", totalProcs);

		Ulock.lock();

		//set hightreoll to current roll if current is higher
		if (totalProcs > HigherstProcs) {
			HigherstProcs = totalProcs;
		}

		//ups complete total
		rollsComplete++;
		//unlocks memory
		Ulock.unlock();

	}

}






void main() {

	//start a timer that will print the time taken at the end of the program runtime
	Timing timer("Total Time Elapsed in microseconds: ");

	//print total number of soll sessions
	printf("Number of roll sessions: %d \n\n", TotalRolls);
	
	//make threads for rolls
	for (int i = 0; i < TotalThreads; i++) {
		threads.push_back(thread(RollSession,TotalRolls/TotalThreads));
	}
	//mkae extra thread for uneven divides
	if (TotalRolls % TotalThreads > 0) {
		threads.push_back(thread(RollSession, TotalRolls % TotalThreads));
	}

	while (rollsComplete < TotalRolls) {

		//print total finshed rolls
		printf("Total rolls completed: %d \n", rollsComplete);
	}
	
	printf("Total rolls completed: %d \n", rollsComplete);
	printf("Highest total Procs: %d \n", HigherstProcs);

	//stops timer
	timer.~Timing();

	//cleanup threads
	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}

	

}