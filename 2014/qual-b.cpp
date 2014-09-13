// Problem B. Cookie Clicker Alpha
// https://code.google.com/codejam/contest/2974486/dashboard#s=p1

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

std::stringstream ReadLine() {
    std::string tmp;
    std::getline(std::cin, tmp);
    return std::stringstream(tmp);
}

// compute the time to obtain cookies
double ComputeDuration(double num_cookies, double f, int farms) {
    return num_cookies / (2 + f*farms);
}

int main()
{
    int num_tests = 0;
    std::stringstream line = ReadLine();
    line >> num_tests;

    for(int case_num = 1; case_num <= num_tests; ++case_num) {
        double c, f, x, duration = 0.0;
        double time_to_win, time_to_new_farm, time_to_win_with_farm = 0.0;
        int farms = 0;

        std::stringstream line = ReadLine();
        line >> c >> f >> x;

        while(1) {
            time_to_win = ComputeDuration(x, f, farms);
            time_to_new_farm = ComputeDuration(c, f, farms);
            time_to_win_with_farm = time_to_new_farm + ComputeDuration(x, f, farms+1);

            if(time_to_win > time_to_win_with_farm) {
                duration += time_to_new_farm;
                ++farms;
            } else {
                duration += time_to_win;
                break;
            }
        }

        std::cout << "Case #" << case_num << ": ";
        std::cout << std::showpoint << std::fixed << std::setprecision(7) << duration << std::endl;

    }

    return 0;
}
