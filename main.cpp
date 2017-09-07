#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>

#include "plf_colony.h"

using namespace std::chrono;

struct Data{
    int x,y,z, sum;

    Data(){}

    Data(int sum)
        :sum(sum)
    {}
};

int capacity = 1'000'000;
float erase_probability = 90;

void benchmark_colony(){
    plf::colony<Data> list;

    for(int i=0;i<capacity;i++){
        list.emplace(i);
    }

    std::srand(std::time(0)); // use current time as seed for random generator


    const int break_point = std::round(RAND_MAX * erase_probability / 100.0);
    auto iter = list.begin();
    for(int i=0;i<capacity;i++){
        const int random_variable = std::rand();
        if (random_variable < break_point){
            iter = list.erase(iter);
		} else {
			iter++;
		}
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
        long long sum = 0;
		//int size = 0;
        for(const Data& data: list){
            sum += data.sum;
			//size++;
        }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::cout 
		<< " [" << list.size() << "] "
		<< duration << " (" << sum << ")"<< std::endl;
}

void benchmark_vector(){
    const unsigned int size = std::round(capacity * (1.0 - erase_probability/100.0));

    std::vector<Data> list;

    for(int i=0;i<size;i++){
        list.emplace_back(i);
    }


    high_resolution_clock::time_point t1 = high_resolution_clock::now();
        long long sum = 0;
        for(const Data& data: list){
            sum += data.sum;
        }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    std::cout 
		<< " [" << size << "] "
		<< duration << " (" << sum << ")"<< std::endl;
}

int main() {
    std::cout << "colony "<< std::endl;
    benchmark_colony();

    std::cout << "vector "<< std::endl;
    benchmark_vector();

#ifdef _MSC_VER
	char ch;
	std::cin >> ch;
#endif

    return 0;
}