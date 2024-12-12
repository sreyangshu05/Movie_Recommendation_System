#include <iostream>
#include <vector>
#include <algorithm>

int longestCommonSubsequence(const std::string& s1, const std::string& s2) {
    int m = s1.length(), n = s2.length();
    std::vector<int> prev(n+1, 0), curr(n+1, 0);

    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(s1[i-1] == s2[j-1])
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = std::max(prev[j], curr[j-1]);
        }
        std::swap(prev, curr);
    }

    return prev[n];
}

int main() {
    std::string s1, s2;
    std::cout << "Enter first string: ";
    std::cin >> s1;
    std::cout << "Enter second string: ";
    std::cin >> s2;

    int lcsLength = longestCommonSubsequence(s1, s2);
    std::cout << "Length of Longest Common Subsequence: " << lcsLength << std::endl;

    return 0;
}
