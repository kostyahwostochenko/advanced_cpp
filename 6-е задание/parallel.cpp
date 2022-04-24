#include <thread>
#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>

const int process = 2;

template <typename Iterator, typename T>
void accumulate_block(Iterator first, Iterator last, std::atomic<T>& init){
    for(auto i = first; i != last; i++){
        init += *i;
    }
}

template <typename Iterator, typename T>
void parallel_accumulate(Iterator first, Iterator last, std::atomic<T>& init){
    auto length = std::distance(first, last);
    if (length < 32){
        accumulate_block(first, last, init);
    }
    else{
        int length_per_thread = (length + process - 1) / process;
        std::vector<std::thread> threads;
        for(int i = 0; i < process - 1; i ++){
            auto beginning = std::next(first, i * length_per_thread);
            auto ending = std::next(first, (i + 1) * length_per_thread);
            threads.push_back(std::thread(accumulate_block<Iterator, T>, beginning, ending, std::ref(init)));
        }
        accumulate_block(std::next(first, (process - 1) * length_per_thread), last, init);
        std::for_each(std::begin(threads), std::end(threads), std::mem_fun_ref(&std::thread::join));
    }
}

int main(){
    std::atomic<int> init = 0;
    std::vector<int> test_sequence(100);
    std::iota(test_sequence.begin(), test_sequence.end(), 1);
    parallel_accumulate(test_sequence.begin(), test_sequence.end(), init);
    std::cout << init;
    return 0;
}
