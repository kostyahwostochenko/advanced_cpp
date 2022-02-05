#include <iostream>
#include <chrono>
#include <cmath>

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
        cout<<duration_cast<T>(time).count()<<endl;
    }

private:
    steady_clock::time_point beg;
    steady_clock::duration time;
    bool is_stop;
};

int main(){
    double result = 0;
    {
    Timer<microseconds> t;
    t.start();
    for(auto i=0;i<10000;i++){
        result += sin(i) + cos(i);}

    t.stop();
    for(auto i=0;i<10000;i++){
        result += sin(i) + cos(i);}

    t.start();
    for(auto i=0;i<10000;i++){
        result += sin(i) + cos(i);}
    }

    return 0;
}
