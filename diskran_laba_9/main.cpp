#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
std::set<int> comps;
std::vector<bool> used;
void DFS(const int& currPoint, const std::vector<std::vector<int> >& matrix)
{
    comps.insert(currPoint);
    used[currPoint] = true;
    for(size_t k = 0; k < matrix.size(); ++k)
    {
        if(matrix[currPoint][k] != 0 && !used[k])
            DFS(k, matrix);
    }
}
int main()
{   int N, M;
    //N - vertexes, M - edges, start point
    scanf("%d %d", &N, &M);
    used.resize(N);
    std::vector<std::vector<int> > matrix(N,std::vector<int> (N));
    int dot1, dot2; // for edges adding.
    for(size_t i = 0; i < M; ++i)
    {
         scanf("%d %d", &dot1, &dot2);
         matrix[dot1 - 1][dot2 - 1] = 1;
         matrix[dot2 - 1][dot1 - 1] = 1;
    }
    for(size_t i = 0; i < used.size(); ++i)
    {
        if(!used[i])
        {
            comps.clear();
            DFS(i, matrix);
            auto endIt = comps.end();
            endIt--;
            for(auto i : comps)
            {
                printf("%d", i + 1);
                if(i != *endIt)
                    printf(" ");
            }
             printf("\n");
        }
    }

    return 0;
}
