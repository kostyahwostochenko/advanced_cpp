#include <iostream>
#include <vector>
#include <algorithm>
#include <future>
#include <iterator>
#include <numeric>
#include <chrono>

using namespace std::chrono;


template<typename T>
class Timer{
public:
    Timer(): beg(steady_clock::now()), time{0}, is_stop{false}{}

    void start(){
       beg = steady_clock::now();
       is_stop = false;
    }

    void stop(){
        if(is_stop == false){
        time += steady_clock::now()-beg;}

        is_stop = true;
    }

    ~Timer(){
        stop();
        std::cout<<duration_cast<T>(time).count()<<'\n';
    }

private:
    steady_clock::time_point beg;
    steady_clock::duration time;
    bool is_stop;
};


template <typename it, typename ufunction>
ufunction for_each_block(it first, it last, ufunction funct)
{
    return std::for_each(first, last, funct);
}


template <typename itt, typename ufunction>
ufunction parallel_for_each(itt first, itt last, ufunction funct, int num_workers)
{
    auto length = std::distance(first, last);
    auto length_per_worker = (length + num_workers - 1) / num_workers;
    std::vector<std::future<ufunction>> v(num_workers);

    for(int i = 0; i < num_workers; ++ i){
        itt start = std::next(first, i * length_per_worker);
        itt finish = std::next(first, (i + 1) * length_per_worker);
        auto futures = std::async(std::launch::async, for_each_block<itt, ufunction>, start, finish, funct);
        v[i] = std::move(futures); // нельзя копировать
    }
    for(auto& futures: v){
        futures.get();}

    return funct;
}


int main(){
    std::vector<int> v(1'000'000);
    std::iota(v.begin(), v.end(), 0);
    parallel_for_each(v.begin(), v.end(), [](auto& i){i = i/2;}, 2);
    for(int i = 0; i < 10; i++){
        std::cout << v[i] << " ";}
    std::cout << '\n';
    return 0;
}
