#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "json.hpp"

using nlohmann::json;

class Person{
public:
    std::string name;
    int age;
    std::string city;
    int height;
    int weight;
    std::string document_number;

    friend std::istream& operator>>(std::istream &is, Person& src){
        is >> src.name >> src.age >> src.city >> src.height >> src.weight >> src.document_number;
        return is;
    }
};

int main(){
    Person person1;
    Person person2;

    // Vasya 19 Dolgopa 179 67 qwer123
    // Pety 18 Moscow 174 64 sxdf678
    std::cin >> person1;
    std::cin >> person2;

    json object1;
    json object2;

    object1["name"] = person1.name;
    object1["age"] = person1.age;
    object1["city"] = person1.city;
    object1["height"] = person1.height;
    object1["weight"] = person1.weight;
    object1["document_number"] = person1.document_number;

    object2["name"] = person2.name;
    object2["age"] = person2.age;
    object2["city"] = person2.city;
    object2["height"] = person2.height;
    object2["weight"] = person2.weight;
    object2["document_number"] = person2.document_number;

    const std::filesystem::path x{"../fyle1"};
    std::filesystem::create_directory(x);

    std::ofstream file1;
    std::ofstream file2;

    file1.open(x/"object1.json");
    file1 << object1;
    file1.close();

    file2.open(x/"object2.json");
    file2 << object2;
    file2.close();

    return 0;
}
