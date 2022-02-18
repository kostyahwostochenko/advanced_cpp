#include <iostream>
#include <string>
#include <ostream>

#include <random>
#include <chrono>

#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class directory{
public:
    directory() {
        gen.seed(time(nullptr));}

    void add(string name, string phone){
        mp[name] = phone;
        ump[name] = phone;
        v.push_back(name);}

    const map<string, string>& get_phone(){
        return mp;
    }


    pair<string, string> get_random(){
        uniform_int_distribution<int> distr(0, v.size()-1);

        random_number = distr(gen);
        p.first = v[random_number];
        p.second = mp[p.first];

        return p;
    }

    string find_phone(string name){
        return ump[name];
    }

    friend ostream& operator<<(ostream &os, const directory& source){
        for(auto i : source.mp){
            cout << i.first << " " << i.second << '\n'; }
        return os;
    }

private:
    map<string, string> mp;
    unordered_map<string, string> ump;
    vector<string> v;
    pair<string, string> p;
    int random_number;

    mt19937_64 gen;
};


int main(){
    setlocale(0, "");
    pair<string, string> p;
    map<string, string> mp;
    directory dict;

    dict.add("Иванов","890-743");
    dict.add("Сидоров","657-731");
    dict.add("Петров","860-903");
    dict.add("Семенов","980-111");
    dict.add("Большевиков","876-985");

    cout << "Вывод отсортированных по фамилии данных: " << '\n';
    cout << dict << '\n';


    mp = dict.get_phone();
    cout << "Проверка получения ссылки на map:" << '\n';
    cout << mp["Иванов"] << '\n' << '\n';

    cout << "Проверка получения случайных данных из справочника:" << '\n';
    p = dict.get_random();
    cout << p.first << " "<< p.second << '\n';
    p = dict.get_random();
    cout << p.first << " "<< p.second << '\n';

    cout << '\n';
    cout << "Быстрый поиск по фамилии Сидоров: " << dict.find_phone("Сидоров") << '\n';


    return 0;
}
