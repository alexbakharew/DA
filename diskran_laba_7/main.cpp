#include <iostream>
#include <vector>
#include <algorithm>
class TItem
{
public:
    size_t index;
    int weight;
    int cost;
};
bool cmp(const TItem& i1, const TItem& i2)
{
    if(i1.cost == i2.cost)
    {
        return i1.weight < i2.weight;
    }
    else
        return i1.cost > i2.cost;
}

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<TItem> array(N);
    for(size_t i = 0; i < N; ++i)
    {
        array[i].index = i;
        std::cin >> array[i].weight;
        std::cin >> array[i].cost;
    }
    std::sort(array.begin(), array.end(), cmp);
    std::cout<<"i w c\n";
    for(size_t i = 0; i < N; ++i)
    {
        std::cout<<array[i].index<<" "<<array[i].weight<<" "<<array[i].cost<<"\n";
    }
    return 0;
}
