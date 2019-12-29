#include <iostream>
#include <vector>
#include <string>

/* we keep the left and right ends of the most right z-block.
   what is z-block? having an array of z-values Z, a z-block is an
   array starting at some ind i of size Z[i].
   if the current index is smaller than the right end, there are two
   things we can do:
   1. look at previously found Z[i - left]. if it's < remaining size of the Z-block (right - i),
      then we don't need to calculate anything. otherwise, we just keep comparing elements further.
   2. if we are outside of the Z-block just keep comparing. */
std::vector<int> get_z(const std::string& str) {
    const size_t len = str.size();
    std::vector<int> Z(len);
    Z[0] = len;
    for (size_t icurr = 1, left = 0, right = 1; icurr < len; ++icurr) {
        if (icurr < right) {
            size_t same_z_ind = icurr - left;
            if (Z[same_z_ind] < right - icurr) {
                Z[icurr] = Z[same_z_ind];
            } else {
                size_t shift = 0;
                while (right + shift < len && 
                       str[right - icurr + shift] == str[right + shift]){
                           ++shift;
                       }
                Z[icurr] = right - icurr + shift;
                left = icurr;
                right += shift;
            }
        } else {
            size_t shift = 0;
            while (icurr + shift < len && \
                   str[icurr + shift] == str[shift]) {
                       ++shift;
                   }
            Z[icurr] = shift;
            left = icurr;
            right = icurr + Z[icurr];
        }
    }
    return Z;
}

int main() {
    std::string sub, str;
    std::cin >> sub >> str;
    const size_t size = sub.size();
    std::string s = sub + "$" + str;
    std::vector<int> Z = get_z(s);
    for (size_t ind = 1; ind < Z.size(); ++ind) {
        if (Z[ind] == size) 
          std::cout << ind - size - 1 << " ";
    }
    std::cout << std::endl;
}
