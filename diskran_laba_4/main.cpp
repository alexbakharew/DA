#include <iostream>
#include <vector>
#include <string>
void Kmp(std::vector<std::string>& pat);
std::vector<int> Zfunc(std::vector<std::string>& pat);
std::vector<int> CalcSP(std::vector<int>& z, std::vector<std::string>& pat);
std::vector<int> FailFunction(std::vector<std::string>& pattern);
std::vector<std::string> PatternParse();
int main()
{
    std::vector<std::string> pattern = PatternParse();
    Kmp(pattern);
    return 0;
}
std::vector<std::string> PatternParse() 
{
    char c;
    std::string buf;
    std::vector<std::string> pattern;
    while (true) 
    {
        c = getchar_unlocked();// The reason that getchar_unlocked() seems faster is that it doesn't 
                               //check for any locks on the input stream from where it is supposed to fetch a character.
        if (c == ' ') 
        {
            if (!buf.empty())
                pattern.push_back(buf);
            buf.clear();
        }
        else if (c == '\n' || c == EOF) 
        {
            if (!buf.empty())
                pattern.push_back(buf);
            break;
        }
        else
            buf.push_back(c);
    }
    return pattern;
}
std::vector<int> Zfunc(std::vector<std::string>& pat) 
{
    const unsigned long n = pat.size();
    std::vector<int> zArray(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) 
    {
        if (i <= r)
            zArray[i] = std::min(r - i + 1, zArray[i - l]);
        while (i + zArray[i] < n && pat[zArray[i]] == pat[i + zArray[i]])
            ++zArray[i];
        if (i + zArray[i] - 1 > r) 
        {
            l = i; 
            r = i + zArray[i] - 1;
        }
    }
    return zArray;
}
std::vector<int> CalcSP(std::vector<int>& zArray, std::vector<std::string>& pat) 
{
    const unsigned long n = pat.size();
    std::vector<int> spArray(n);
    for (unsigned long j = n - 1; j > 0; --j) 
    {
        unsigned long i = j + zArray[j] - 1;
        spArray[i] = zArray[j];
    }
    return spArray;
}
std::vector<int> FailFunction(std::vector<std::string>& pattern) 
{
    unsigned long n = pattern.size();
    std::vector<int> zArray = Zfunc(pattern);
    std::vector<int> spArray = CalcSP(zArray, pattern);
    std::vector<int> f(n + 1);
    f[0] = 0;
    for (int k = 1; k < n; ++k) 
        f[k] = spArray[k - 1];
    
    f[n] = spArray[n - 1];
    return f;
}
void Kmp(std::vector<std::string>& pat) 
{
    std::vector<std::pair<std::pair<int, int>, std::string>> text;

    char c = '$';                                       // default value
    bool wordAdded = true;                              // True if last action was to add the word into the vector
    std::pair<std::pair<int, int>, std::string> temp;   // current word
    const unsigned long n = pat.size();                 // Pattern size
    temp.first.first = 1;                               // Row counter
    temp.first.second = 1;                              // Word counter
    int p = 0;                                          // Pattern pointer
    int t = 0;                                          // Text pointer
    std::vector<int> f = FailFunction(pat);
    do 
    {
        while (text.size() < pat.size() && c != EOF) 
        {
            c = getchar_unlocked();
            if (c == '\n') 
            {
                if (!wordAdded) 
                {
                    text.push_back(temp);
                    temp.second.clear();
                    wordAdded = true;
                }
                ++temp.first.second;
                temp.first.first = 1;
            } 
            else if (c == ' ' || c == '\t' || c == EOF) 
            {
                //skip spaces
                if (wordAdded)
                    continue;
                text.push_back(temp);
                temp.second.clear();
                ++temp.first.first;
                wordAdded = true;
            } 
            else 
            {
                // Deletes unnecessary zeros in the number
                if (temp.second.front() == '0')
                    temp.second.erase(temp.second.begin());
                temp.second.push_back(c);
                wordAdded = false;
            }
        }
        // There are no possible matches
        if (text.size() < pat.size())
            return;

        // KMP begins
        while (p < n && pat[p] == text[t].second ) 
        { // We are checking if pattern suits or not
            ++p;
            ++t;
        }
        if (p == n) 
        { // We found match
            printf("%d, %d\n", text[0].first.second, text[0].first.first);
        }
        if (p == 0) 
            ++t;
        
        p = f[p];
        text.erase(text.begin(), text.begin() + t - p);
        t = p;
    } 
    while (c != EOF);
}