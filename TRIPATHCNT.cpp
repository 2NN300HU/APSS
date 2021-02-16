/*문제
9
5 7
1 3 2
3 5 5 6
위 형태와 같이 삼각형 모양으로 배치된 자연수들이 있습니다. 맨 위의 숫자에서 시작해, 한 번에 한 칸씩 아래로 내려가 맨 아래 줄로 내려가는 경로를 만들려고 합니다. 경로는 아래 줄로 내려갈 때마다 바로 아래 숫자, 혹은 오른쪽 아래 숫자로 내려갈 수 있습니다.
이 때 숫자의 합이 가장 큰 경로는 하나가 아니라 여러 개일 수 있습니다. 예를 들어 위 삼각형에서는 {9, 7, 2, 6}과 {9, 7, 3, 5}의 합이 모두 최대인 24이고, {9, 7, 3, 5}는 두 번 등장하거든요.
삼각형이 주어질 때 최대 경로의 수를 세는 프로그램을 작성하세요.

입력
입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 삼각형의 크기 n(2 <= n <= 100)이 주어지고, 그 후 n줄에는 각 1개~n개의 숫자로 삼각형 각 가로줄에 있는 숫자가 왼쪽부터 주어집니다. 각 숫자는 1 이상 100000 이하의 자연수입니다.

출력
각 테스트 케이스마다 한 줄에 최대 경로의 수를 출력합니다.
경로의 수는 230 이하라고 가정해도 좋습니다.

예제 입력
2
4
1
1 1
1 1 1
1 1 1 1
4
9
5 7
1 3 2
3 5 5 6

예제 출력
8
3
*/

#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
int cache[100][100];
int map[100][100], n;

int maxCount(int x, int y) {
    if (y == n - 1) return 1;
    int ret = 0;
    if (cache[y + 1][x] >= cache[y + 1][x + 1]) ret += maxCount(x, y + 1);
    if (cache[y + 1][x] <= cache[y + 1][x + 1]) ret += maxCount(x + 1, y + 1);
    return ret;
}

int maxLen(int x, int y) {
    int &tg = cache[y][x];
    if (tg != -1) {
        return tg;
    }
    if (y == n - 1) {
        return tg = map[y][x];
    }
    return tg = map[y][x] + max(maxLen(x, y + 1), maxLen(x + 1, y + 1));
}

int main() {
    int cases;
    cin >> cases;
    for (int c = 0; c < cases; c++) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i + 1; j++) {
                cin >> map[i][j];
            }
        }
        memset(cache, -1, sizeof(cache));
        maxLen(0, 0);
        cout << maxCount(0, 0) << endl;
    }
    return 0;
}