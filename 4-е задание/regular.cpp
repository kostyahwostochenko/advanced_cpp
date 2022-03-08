#include <iostream>
#include <iterator>
#include <regex>
#include <vector>


std::vector<std::string> search(const std::regex& pattern, const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text), std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    return results;
}


int main(){

    std::regex regular1(R"((([0][1-9])|([1-2][0-9])|([3][0-1]))\.(([0][1-9])|([1][0-2]))\.[0-9]{4})");
    //std::regex pattern(R"((\+7|8)\s?(\([498][0-9]{2}\)|[498][0-9]{2})\s?[0-9]{3}(-?[0-9]{2}){2})");

    std::string test_sequence1 = "09.09.2000 \n"
                                "08.10.2022 \n"
                                "00.01.1998 \n"
                                "010.11.2021 \n" // Delete first 0
                                "34.07.3456 \n"
                                "21.21.2121 \n"
                                "123.123.3456 \n";
    auto result = search(regular1, test_sequence1);
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<std::string>(std::cout, " "));

    std::cout << '\n';

    std::regex regular2(R"((([0-1][0-9])|([2][0-3]))(:[0-5][0-9]){2})");

    std::string test_sequence2 = "00:00:00 \n"
                                "23:56:34 \n"
                                "24:34:12 \n"
                                "12:61:53 \n"
                                "11:11:11 \n"
                                "21:45:34 \n"
                                "24:24:60 \n";
    result = search(regular2, test_sequence2);
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<std::string>(std::cout, " "));

    return 0;
}
