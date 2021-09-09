#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out)
{
    std::stringstream ss(str);

    std::string s;

    while (std::getline(ss, s, delim)) 
    {
        out.push_back(s);
    }
}

int main()
{
    std::string s = "This           is java2blog";

    const char delim = ' ';

    std::vector<std::string> out;

    tokenize(s, delim, out);

    for (auto &s:out) {
        std::cout << s << "\n";
    }

    return 0;
}