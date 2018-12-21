#include <iostream>
#include <vector>

void backpack(const int N, const int W, const std::vector<int> &w, const std::vector<int> &c)
{

    std::vector<std::vector<std::vector<uint32_t> > > m(N + 1, std::vector<std::vector<uint32_t> >(N + 1, std::vector<uint32_t>(W + 1)));

    for(size_t i = 1; i <= N; i++)
    {
        for(size_t j = 1; j <= i; j++)
        {
            for(size_t k = 1; k <= W; k++)
            {
            	
                if( w[i-1] <= k )// k equal to weight
                {
                    m[i][j][k] = std::max(m[i-1][j][k], m[i-1][j-1][k-w[i-1]] + c[i-1]);
                    
					if( !m[i-1][j-1][k-w[i-1]] && j != 1 && m[i][j][k] == c[i-1])
                        m[i][j][k] = m[i-1][j][k];
                }

                else
                    m[i][j][k] = m[i-1][j][k]; // we don't take any items

            }
        }
    }
    int total_cost = 0;
    int res_idx = 0;
    // максимальный элемент лежит где-то в a[N][i][W], где N - кол-во элементов, а [W] - макс. вес
    for(size_t i = 0; i <= N; i++)
        if( m[N][i][W] * i > total_cost ) 
		{
            total_cost = m[N][i][W] * i;
            res_idx = i;
        }
    std::cout << total_cost << std::endl;

    std::vector<int> ans;
    int i = N;
    int j = res_idx;
    int k = W;
    while (m[i][j][k] != 0) 
	{
        if( m[i][j][k] == m[i-1][j][k] ) 
            i -= 1;
        else 
		{
            ans.push_back(i);
            k -= w[i - 1];
            i -= 1;
            j -= 1;
        }
    }

    for(i = ans.size() - 1; i >= 0; --i)
    {
    	std::cout << ans[i];
    	if(i != 0)
    		std::cout << " ";
    	if(i == 0)
    		std::cout << "\n";
	}
}

int main()
{
    int N, W;
    std::cin >> N >> W;
    std::vector<int > w(N);
    std::vector<int> c(N);
    for(size_t i = 0; i < N; i++)
        std::cin >> w[i] >> c[i];
        
    backpack(N, W, w, c);
    return 0;
}
