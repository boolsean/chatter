#ifndef GDM_UTILS
#define GDM_UTILS

#include <vector>


namespace gdm {

static double getAverage(std::vector<double> nums)
{
    if(nums.empty()) return .0;
    double total = .0;

    for(std::vector<double>::const_iterator it = nums.begin(); it != nums.end(); it++) {
        total += *it;
    }

    return total/nums.size();
}

static bool doubleComparer(const double& lhs, const double& rhs) {
    const double ep = .00000000001;
    if(lhs > rhs && (lhs - rhs) > ep) {
        return false;
    }

    if(rhs > lhs && (rhs - lhs) > ep) {
        return false;
    }

    return true;
}
} // close namespace

#endif
