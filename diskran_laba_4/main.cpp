#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <deque>
#include <string>
#include <time.h>

void ParsePattern(std::vector<std::string>& pattern);
std::vector<size_t> ComputeSP(const std::vector<std::string>& pattern);
std::vector<size_t> ComputeZFunction(const std::vector<std::string>& pattern);
std::vector<size_t> ComputeFailFunction(const std::vector<size_t>& sp);
bool ParseText(std::deque< std::pair< std::string, std::pair< size_t, size_t > > >& text, std::pair<size_t, size_t>& pos, size_t shift);

int main()
{
    std::vector<std::string> pattern;

    ParsePattern(pattern);

    std::vector<size_t> sp = ComputeSP(pattern);
    std::vector<size_t> fail_function = ComputeFailFunction(sp);

    std::deque< std::pair< std::string, std::pair< size_t, size_t > > > text;

    std::pair<size_t, size_t> pos;
    pos.first = 1;
    pos.second = 1;

    size_t c = 0;
    size_t p = 0;


    bool check = ParseText(text, pos, pattern.size());
//    size_t i
    while (check)
    {
        while (text[c].first == pattern[p] && p < pattern.size())
        {
            ++c;
            ++p;
        }

        if (p == pattern.size())
        {
            printf("%zu, %zu\n", text[0].second.first, text[0].second.second);
        }

        if (p == 0)
        {
            ++c;
        }

        p = fail_function[p];
        check = ParseText(text, pos , c - p);
        c = p;
    }

    // clock_t end  = clock();

    // float time = (float) (end - start) / CLOCKS_PER_SEC;

    // printf("KMP time: %f\n", time);

    return 0;
}

void ParsePattern(std::vector<std::string>& pattern)
{
    char ch;
    std::string buffer;
    bool zero = false;
    while ((ch = getchar()) != '\n')
    {
        if (ch == ' ' || ch == '\t')
        {
            if (buffer.length() > 0)
            {
                pattern.push_back(buffer);

                while (buffer.length() > 0)
                {
                    buffer.pop_back();
                }
            }
        }
        else
        {
            if(ch == '0')
            {
                int tmpCh;
                while(tmpCh = getchar() == '0'){}
                if(tmpCh == ' ' || tmpCh == '\t' || tmpCh == '\n')
                {
                    buffer.push_back('0');
                }

                ungetc(tmpCh, stdin);
            }
            buffer.push_back(tolower(ch));
        }
    }

    if (buffer.length() > 0)
    {
        pattern.push_back(buffer);
    }
}

std::vector<size_t> ComputeSP(const std::vector<std::string>& pattern)
{
    std::vector<size_t> z_func = ComputeZFunction(pattern);
    std::vector<size_t> sp(z_func.size());
    size_t j;

    for (size_t i = z_func.size() - 1; i > 0; --i)
    {
        j = i + z_func[i] - 1;
        sp[j] = z_func[i];
    }

    return sp;
}

std::vector<size_t> ComputeFailFunction(const std::vector<size_t>& sp)
{
    std::vector<size_t> f(sp.size() + 1);

    f[0] = 0;

    for (size_t k = 1; k < sp.size(); ++k)
    {
        f[k] = sp[k - 1];
    }

    f[sp.size()] = sp[sp.size() - 1];

    return f;
}

std::vector<size_t> ComputeZFunction(const std::vector<std::string>& pattern)
{
    std::vector<size_t> z_func(pattern.size());
    size_t l = 0;
    size_t r = 0;

    for (size_t i = 1; i < pattern.size(); ++i)
    {
        if (i <= r)
        {
            z_func[i] = std::min(r - i + 1, z_func[i - l]);
        }

        while (pattern[z_func[i]] == pattern[i + z_func[i]] && i + z_func[i] < pattern.size())
        {
            ++z_func[i];
        }

        if (i + z_func[i] - 1 > r)
        {
            l = i;
            r = i + z_func[i] - 1;
        }
    }

    return z_func;
}

bool ParseText(std::deque< std::pair< std::string, std::pair< size_t, size_t > > >& text, std::pair<size_t, size_t>& pos, size_t shift)
{
    std::pair<std::string, std::pair<size_t, size_t>> tmp;

    int ch;

    if (shift <= text.size())
    {
        for (size_t i = 0; i < shift; ++i)
        {
            text.pop_front();
        }
    }

    while (shift > 0)
    {
        while (!isdigit(ch = getchar()))
        {
            if (ch == '\n')
            {
                ++pos.first;
                pos.second = 1;
            }
            else
            {
                if (ch == EOF)
                {
                    return false;
                }
            }
        }

        do
        {
            if(ch == '0')
            {
                int tmpCh;
                while(tmpCh = getchar() == '0'){}
                ungetc(tmpCh, stdin);
            }
            tmp.first.push_back(tolower(ch));
        }
        while (isdigit(ch = getchar()));

        tmp.second = pos;

        text.push_back(tmp);

        if (ch == '\n')
        {
            ++pos.first;
            pos.second = 1;
        }
        else
        {
            ++pos.second;
        }

        while (tmp.first.length() > 0)
        {
            tmp.first.pop_back();
        }

        --shift;
    }

    return true;
}

