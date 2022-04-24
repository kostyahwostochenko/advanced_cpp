#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

using std::cout;
using std::lock_guard;

template <typename T>
class Queue{
private:
    std::queue<T> my_queue;
    std::mutex my_mutex;
public:
    Queue() = default;

    T back(){
        lock_guard guard(my_mutex);
        return my_queue.back();
    }

    bool empty(){
        lock_guard guard(my_mutex);
        return my_queue.empty();
    }

    T front(){
        lock_guard guard(my_mutex);
        return my_queue.front();
    }

    void pop(){
        lock_guard guard(my_mutex);
        my_queue.pop();
    }

    void push(const T& val){
        lock_guard guard(my_mutex);
        my_queue.push(val);
    }

    size_t size(){
        lock_guard guard(my_mutex);
        return my_queue.size();
    }
};

void add_n_times(Queue<int>& q, int n){
    for(size_t i = 0; i < n; i ++){
        q.push(n+i);
    }
}

int main(){
    Queue<int> q;
    size_t n = 100;
    //add additional elements so that a non-existent element is not deleted
    for(size_t i = 0; i < n; i++){
        q.push(i);
    }
    cout << q.size() << '\n';
    std::thread other(add_n_times, std::ref(q), n);
    for(size_t i = 0; i < n; i++){
        cout << q.size() << " ";
        q.pop();
        cout << q.size() << '\n';
    }
    other.join();
    cout << "Front " << q.front() << ", back " << q.back() << ", is empty " << q.empty() << '\n';
    return 0;
}
