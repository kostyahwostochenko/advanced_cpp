#include <algorithm>
#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

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

template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, T init, T& result) {
    result = std::accumulate(first, last, init);
}

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init, int cnt) {

    auto length = std::distance(first, last);
    if (length < 1'000'000) {
        return std::accumulate(first, last, init);
    }

    auto num_workers = cnt;

    auto length_per_thread = (length + num_workers - 1) / num_workers;

    std::vector<std::thread> threads;
    std::vector<T> results(num_workers - 1);

    for(auto i = 0u; i < num_workers - 1; i++) {
        auto beginning = std::next(first, i * length_per_thread);
        auto ending = std::next(first, (i + 1) * length_per_thread);

        threads.push_back(std::thread(
            accumulate_block<Iterator, T>,
            beginning, ending, 0, std::ref(results[i])));
    }

    auto main_result = std::accumulate(std::next(first, (num_workers - 1) * length_per_thread),
                                       last, init);

    std::for_each(std::begin(threads), std::end(threads), std::mem_fun_ref(&std::thread::join));

    return std::accumulate(std::begin(results), std::end(results), main_result);
}

int main() {
    int cnt = 2;
    std::vector<int> test_sequence(1'000'000);
    std::iota(test_sequence.begin(), test_sequence.end(), 0);
    {
        Timer<microseconds> t;
        t.start();
        parallel_accumulate(std::begin(test_sequence), std::end(test_sequence), 0, cnt);
        t.stop();
    }
    std::cout << std::thread::hardware_concurrency();


}
