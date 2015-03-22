#include "utils.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<double> nums;

    nums.push_back(10);
    nums.push_back(10.4);
    nums.push_back(11.4);
    double avg = gdm::getAverage(nums);

    std::cout << "avg:" << avg << std::endl;

    double f1 = 1.213437;
    double f2 = 1.213437;

    std::cout << gdm::doubleComparer(f1, f2) << std::endl;

    return 0;
}
