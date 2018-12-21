#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
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
    std::vector<TItem> array(N);// array of items
    for(size_t i = 0; i < N; ++i)
    {
        array[i].index = i;
        std::cin >> array[i].weight;
        std::cin >> array[i].cost;
    }
    std::vector<TItem> choise;// choise of items, which in backpack
    std::vector<int> caps(1);// the best sum of vals of items in backpack with capacity i
    caps[0] = 0; //If backback capacity is 0
    int currWeight = 0;//weight for chosen items
    for(size_t i = 1; i <= M; ++i)//through the caps array
    {
        if(array.size() == 0)
            break;

        TItem maxItem = array[0]; // Initialize maxItem
        size_t pos = 0; //Initialize position of maxItem
        for(size_t j = 0; j < N; ++j)
        {
            if(array[j].cost > maxItem.cost &&
               currWeight + array[j].weight <= M)
            {
                maxItem = array[j];
                pos = j;
            }
        }
        caps.push_back(caps[i - 1] + maxItem.cost);
        choise.push_back(maxItem);// choose our item
        currWeight += maxItem.weight;// increase wight on current iteration
        array.erase(array.begin() + pos);// delete item from availible items
    }
    std::cout << caps[caps.size() - 1] * choise.size() << std::endl;
    for(size_t k = 0; k < choise.size(); ++k)
    {
        std::cout <<choise[k].index + 1;
        if(k != choise.size() - 1)
            std::cout << " ";
    }
    std::cout << "\n";
    return 0;
}
