// Problem A. Magic Trick
// https://code.google.com/codejam/contest/2974486/dashboard

#include <iostream>
#include <set>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>


std::set<int> ReadNextRow() {
    std::set<int> cards;
    auto row = 0;
    std::string line;

    std::getline(std::cin, line);
    std::stringstream stream(line);
    stream >> row;
    for (int i = 1; i <= 4; ++i) {
        std::getline(std::cin, line);
        stream.clear();
        stream.str(line);
        if (i == row) {
            while (!stream.eof()) {
                int card;
                stream >> card;
                cards.insert(card);
            }
        }
    }

    return cards;
}

int main()
{
    int num_tests = 0;
    std::string line;

    std::getline(std::cin, line);
    std::stringstream stream(line);
    stream >> num_tests;

    for (int i = 0; i < num_tests; ++i)
    {
        auto set1 = ReadNextRow();
        auto set2 = ReadNextRow();
        auto set_overlap = std::vector<int>();

        std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(set_overlap));

        std::cout << "Case #" << i+1 << ": ";

        if (set_overlap.size() == 1) {
            std::cout << *(set_overlap.begin()) << std::endl;
        } else if (set_overlap.size() > 1) {
            std::cout << "Bad magician!" << std::endl;
        } else {
            std::cout << "Volunteer cheated!" << std::endl;
        }

    }
    return 0;
}
