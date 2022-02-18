#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

using namespace std;

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
        cout<<duration_cast<T>(time).count()/25<<endl;
    }

private:
    steady_clock::time_point beg;
    steady_clock::duration time;
    bool is_stop;
};





int main(){

    array<int, 10000> a;
    vector<int> v(5'000'00);
    deque<int> d(500'000);
    list<int> l;
    forward_list<int> fl;

    std::mt19937_64 gen;
    gen.seed(time(nullptr));
    std::uniform_int_distribution<int> distr(0, 1'000'000'000);


     /*{Timer<microseconds> t;

    for(int j=0;j<25;j++){

    for(int i=0; i<a.size(); i++){
        a[i] = distr(gen);}

    t.start();
    sort(a.begin(), a.end());
    t.stop();
    }
     }*/
        /*{Timer<microseconds> t;

    for(int j=0;j<25;j++){

    for(int i=0; i<v.size(); i++){
        v[i] = distr(gen);}

    t.start();
    sort(v.begin(), v.end());
    t.stop();
    }
     }*/

    /*{Timer<microseconds> t;

    for(int j=0;j<25;j++){

    for(int i=0; i<d.size(); i++){
        d[i] = distr(gen);}

    t.start();
    sort(d.begin(), d.end());
    t.stop();
    }
     }*/

    /*{Timer<microseconds> t;

    for(int j=0;j<25;j++){

    for(int i=0; i<100'000; i++){
        l.push_back(distr(gen));}

    t.start();
    l.sort();
    t.stop();
    l.clear();
    }
     }*/

    {Timer<microseconds> t;

    for(int j=0;j<25;j++){

    for(int i=0; i<100'000; i++){
        fl.push_front(distr(gen));}

    t.start();
    fl.sort();
    t.stop();
    fl.clear();
    }
     }

return 0;
}
