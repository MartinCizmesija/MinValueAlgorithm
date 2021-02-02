#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <list>

typedef unsigned int uint;

uint16_t min(uint16_t x, uint16_t y)
{
    if (x < y)
        return x;
    else
        return y;
}

//[N][M]
uint solve(const uint N, const uint M, uint16_t* const problem, std::vector<std::pair<uint, uint>>& solution) {
    if (N == 0 || M == 0) return 0;

    uint** costArray = new uint * [N];
    for (int i = 0; i < N; i++)
    {
        costArray[i] = new uint[M];
    }

    bool end = false;
    uint counter = 0;
    uint16_t row = N - 1;
    uint16_t column = M - 1;

    costArray[0][0] = problem[0];

    for (int a = 1; a < N; ++a)
    {
        costArray[a][0] = costArray[a - 1][0] + problem[a*M];
    }

    for (int b = 1; b < M; ++b)
    {
        costArray[0][b] = costArray[0][b - 1] + problem[b];
    }

    for (int a = 1; a < N; ++a) {
        for (int b = 1; b < M; ++b) {
            costArray[a][b] = min(costArray[a - 1][b], costArray[a][b - 1]) + problem[(a*M)+b];
        }
    }

    solution.insert(solution.begin(), std::pair<uint, uint>(row, column));
    while (!end) {
        if (row > 0 && column > 0) {
            if (costArray[row][column - 1] <= costArray[row - 1][column]) --column;
            else --row;
        }
        else if (row == 0) {
            --column;
        }
        else --row;
        solution.insert(solution.begin(), std::pair<uint, uint>(row, column));
        if (row == 0 && column == 0) end = true;
    }

    counter = costArray[N - 1][M - 1];

    for (int i = 0; i < N; ++i) {
        delete[] costArray[i];
    }
    delete[] costArray;

    return counter;
}

// [N-row][M-column]
int main() {
    //uint16_t polje[] = {1, 7, 9, 2, 8, 6, 6, 7, 1, 3, 2, 8};

    uint16_t polje[] = { 100, 200, 1000, 0,
                        200, 100,  600, 0,
                        300, 1600, 100, 0 };
    uint16_t* ptr;
    ptr = polje;
    std::vector<std::pair<uint, uint>> solution;

    uint16_t brCvijeca = solve(3, 4, ptr, solution);

    std::cout << "Kolicina cvijeca: " << brCvijeca;
    std::cout << "\n";

    for (int i = 0; i < solution.size(); ++i) {
        std::cout << "(" << solution[i].first << ", " << solution[i].second << ")" << std::endl;
    }

    return 0;
}