#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>

#include <random>
#include <chrono>
#include <cmath>

bool prime_number(int n){
    if(n == 1){
        return false;}

    for(int i=2;i<std::floor(sqrt(n));i++){
        if(n % i == 0)
            return false;
    }
    return true;
}

int main(){

    std::vector<int> sequence(10);
    std::iota(std::begin(sequence), std::end(sequence), 1); // P1 create sequence

    int n = 2;
    int a = 0;
    //std::cin >> n;
    for(int i=0;i<n;i++){
        std::cin >> a;
        sequence.push_back(a);  // P2 adding numbers
    }

    std::mt19937_64 gen;
    gen.seed(time(nullptr));
    std::uniform_int_distribution<int> distr(0, 150); // create random generator

    for(int i=0;i<sequence.size();i++){
        std::swap(sequence[i], sequence[distr(gen)%sequence.size()]); // P3 shuffle elements
    }

    std::sort(std::begin(sequence), std::end(sequence));
    auto itt = std::unique(std::begin(sequence), std::end(sequence)); // P4 delete duplicates
    sequence.erase(itt, std::end(sequence));

    auto count_odd = std::count_if(std::begin(sequence), std::end(sequence), [](auto i){return i%2 != 0;}); // P5 count odd number

    int maximum, minimum;
    minimum = sequence[0];
    maximum = sequence[size(sequence) - 1]; // P6 maximum and minimum elements

    auto itt_prime_number = std::find_if(std::begin(sequence), std::end(sequence), prime_number); // P7 find iterator on prime number

    std::transform(std::begin(sequence), std::end(sequence), std::begin(sequence), [](auto i){return i*i;}); // P8 square elements

    std::vector<int> sequence_2(sequence.size());
    for(int i=0;i<sequence_2.size();i++){
        sequence_2[i] = distr(gen);    // P9 generate second sequence
    }

    int summ_sequence_2 = std::accumulate(std::begin(sequence_2), std::end(sequence_2), 0); // P10 summ of second sequence

    std::fill(std::begin(sequence_2), next(std::begin(sequence_2), 3), 1); // P11 replace the first 3 elements witn 1

    std::vector<int> sequence_3;
    std::transform(std::begin(sequence), std::end(sequence), std::begin(sequence_2),
                   std::back_inserter(sequence_3), [](auto lhs, auto rhs){return lhs - rhs;}); // P12 sequence difference

    std::sort(std::begin(sequence_3), std::end(sequence_3));
    auto it = std::find_if(std::begin(sequence_3), std::end(sequence_3), [](auto i){return i >= 0;}); // P13 change on negative
    std::fill(std::begin(sequence_3), it, 0);

    it = std::find_if(std::begin(sequence_3), std::end(sequence_3), [](auto i){return i > 0;}); // P14 delete 0
    sequence_3.erase(std::begin(sequence_3), it);

    std::reverse(std::begin(sequence_3), std::end(sequence_3)); // P15 change the order of elements

    int max1, max2, max3;        // P16 find top 3 maximum
    if(sequence_3.size() >= 3){
        max1 = sequence_3[0];
        max2 = sequence_3[1];
        max3 = sequence_3[2];}
    else{
        if(sequence_3.size() == 2){
            max1 = sequence_3[0];
            max2 = sequence_3[1];
            max3 = 0;}
            else{
                if(sequence_3.size() == 1){
                max1 = sequence_3[0];
                max2 = 0;
                max3 = 0;}
                else{
                    max1 = 0;
                    max2 = 0;
                    max3 = 0;}
            }
    }

    std::sort(std::begin(sequence), std::end(sequence));
    std::sort(std::begin(sequence_2), std::end(sequence_2)); // P17 sort sequence and sequence_2

    std::vector<int> sequence_4;

    std::merge(std::begin(sequence), std::end(sequence), std::begin(sequence_2),
               std::end(sequence_2), std::back_inserter(sequence_4)); // P18 merging elements

    {
    auto pair_it = std::equal_range(std::begin(sequence_4), std::end(sequence_4), 1); // P19 range for insert
    std::cout << std::distance(std::begin(sequence_4), pair_it.first)<< " "
    << std::distance(std::begin(sequence_4), pair_it.second) << '\n';

    //or

    auto it_1 = std::find_if(std::begin(sequence_4), std::end(sequence_4), [](auto i){return i != 1;});
    std::cout << 0 << " " << std::distance(std::begin(sequence_4), it_1) << '\n';
    }

        std::cout << '\n';
    for(auto i : sequence)
        std::cout<<i<<" ";

        std::cout << '\n';
    for(auto i : sequence_2)            // P20 cout sequences
        std::cout<<i<<" ";

    std::cout << '\n';
    std::copy(std::begin(sequence_3),std::end(sequence_3), std::ostream_iterator<int>(std::cout, " "));

    std::cout << '\n';
    std::copy(std::begin(sequence_4),std::end(sequence_4), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}
