#include <iostream>
#include <vector>
#include <string>
/*void print()
 *
{
    for(size_t i = 0; i < M; ++i)
    {
        for(size_t j = 0; j < M; ++j)
        {
            std::cout << matrix[i][j] <<" ";
        }
        std::cout << "\n";
    }
    return;
}
void TGraph::input()
{
    //N - vertexes, M - edges, start point
    std::cin >> N >> M;
    matrix(N,std::vector<int> (M));
    int dot1, dot2; // for edges adding.
    for(size_t i = 0; i < N; ++i)
    {
         std::cin >> dot1 >> dot2;
         matrix[dot1][dot2] = 1;
         matrix[dot2][dot1] = 1;
    }
}
*/

void DFS(int currPoint, const std::vector<std::vector<int> >& matrix, std::vector<bool>& used)
{
    std::cout << currPoint + 1 << " ";
    used[currPoint] = true;
    for(size_t k = 0; k < matrix.size(); ++k)
    {
        if(matrix[currPoint][k] != 0 && !used[k])
            DFS(k, matrix, used);
    }
}
void BFS(int currPoint, const std::vector<std::vector<int> >& matrix, std::vector<bool>& used)
{
    used[currPoint] = true;
    std::vector<int> reachable;
    for(size_t k = 0; k < matrix.size(); ++k)
    {
        if(matrix[currPoint][k] != 0 && !used[k])
        {
            reachable.push_back(k);
            std::cout << k + 1 << " ";
        }
    }
    for(size_t j = 0; j < reachable.size(); ++j)
        BFS(reachable[j], matrix, used);
}
int main()
{   int N, M, start;
    //N - vertexes, M - edges, start point
    std::cin >> N >> M >> start;
    std::vector<bool> used(N);
    std::vector<std::vector<int> > matrix(N,std::vector<int> (N));
    int dot1, dot2; // for edges adding.
    for(size_t i = 0; i < M; ++i)
    {
         std::cin >> dot1 >> dot2;
         matrix[dot1 - 1][dot2 - 1] = 1;
         matrix[dot2 - 1][dot1 - 1] = 1;
    }
    std::cout << start << " ";
    BFS(start - 1, matrix, used);
    return 0;
}
