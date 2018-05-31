#include <iostream>
#include <vector>
#include <string>
struct word
{
    int begin;
    int n;
    int line;
};
int main()
{
    std::vector<int> arr = {1,2,3,4,5,6,7,8,9,0};
    int i = 0;
    for(;;)
    {
        std::cout<<arr[i]<<std::endl;
    }
    return 0;
}