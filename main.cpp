#include <QCoreApplication>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <math.h>
#include <unordered_map>

using namespace std;

typedef std::vector<std::string> dict_t;
typedef vector<int> pattern_t;

pattern_t getPattern(std::string pattern)
{
    unordered_map<char,int> cmap;
    pattern_t patternlst;
    for (size_t i=0; i<pattern.size(); i++)
    {
        char c = pattern[i];
        auto itc = cmap.find(c);
        if (itc == cmap.end())
            cmap[c] = 1;
        else
            itc->second++;
        patternlst.push_back(cmap.at(c));
    }
    return patternlst;
}

std::vector<std::string> findMatchedWords(std::vector<std::string> dict,
                             std::string pattern)
{
    pattern_t plst = getPattern(pattern);
    std::vector<std::string> out;

    for (auto d : dict)
    {
        if (d.size() != pattern.size())
            break;
        else
        {
            bool found = true;
            pattern_t tmp = getPattern(d);
            for (size_t i=0; i<plst.size(); i++)
            {
                if (plst[i] != tmp[i])
                {
                    found = false;
                    break;
                }
            }
            if (found)
                out.push_back(d);
        }
    }
    return out;
}

int main(int argc, char *argv[])
{
    using namespace std;
    QCoreApplication a(argc, argv);

    dict_t dict;
    dict.push_back("abb");
    dict.push_back("abc");
    dict.push_back("xyz");
    dict.push_back("xyy");

    string pattern = "foo";

    dict_t match = findMatchedWords(dict,pattern);

    for (auto it: match)
        cout << it << endl;

    return a.exec();
}
