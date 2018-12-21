#include <iostream>
#include <vector>

void backpack(const int N, const int W, const std::vector<int> &w, const std::vector<int> &c)
{
    // N - ���-�� ���������, W - ������������ ���, w - ������ �����, c - ������ ����������
    std::vector<std::vector<std::vector<uint32_t> > > a(N + 1, std::vector<std::vector<uint32_t> >(N + 1, std::vector<uint32_t>(W + 1)));
    /* ������ ������ - ��������, �������� ����� ������� �� ����
     * ������ - ���������� ��������� � ���������
     * ������ - ���������
     */
    for(size_t i = 1; i <= N; i++)
    {
        for(size_t j = 1; j <= i; j++)
        {
            for(size_t k = 1; k <= W; k++)
            {
                // ���� ��� ��������������� �������� ������ ���� ����� �����������
                if( w[i-1] <= k )
                {
                    /* a[i][j][k] ������������ �� �������� �������� ������ ��� ������ �� ���������� ��������� �
                     * ��������� (�. �. �� �� ������ ������� �������) � �������� a[i-1][j-1][k-w[i-1]] + c[i-1], �.�.
                     * ��������� �� ����������� ���� ������� ��� �������� � ������ ��������� �� 1 ������
                     * � ����� k � ������� �������� ��������� ��������������� ��������
                     */
                    a[i][j][k] = std::max(a[i-1][j][k], a[i-1][j-1][k-w[i-1]] + c[i-1]);
                    
					if( !a[i-1][j-1][k-w[i-1]] && j != 1 && a[i][j][k] == c[i-1])
                        a[i][j][k] = a[i-1][j][k];
                }
                // ���� ���, ������� �� �������� � �������� ��������� ������� ����� �� ��� ��� ���������� ��������
                else
                    a[i][j][k] = a[i-1][j][k];

            }
        }
    }
    int total_cost = 0;
    int res_idx = 0;
    // ������������ ������� ����� ���-�� � a[N][i][W], ��� N - ���-�� ���������, � [W] - ����. ���
    for(size_t i = 0; i <= N; i++)
        if( a[N][i][W] * i > total_cost ) 
		{
            total_cost = a[N][i][W] * i;
            res_idx = i;
        }
    std::cout << total_cost << std::endl;

    std::vector<int> ans;
    int i = N;
    int j = res_idx;
    int k = W;
    while (a[i][j][k] != 0) 
	{
        if( a[i][j][k] == a[i-1][j][k] ) 
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
    	if(i > 0)
    		std::cout << " ";
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
