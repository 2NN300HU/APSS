/*문제

H*W 크기의 게임판이 있습니다. 게임판은 검은 칸과 흰 칸으로 구성된 격자 모양을 하고 있는데 이 중 모든 흰 칸을 3칸짜리 L자 모양의 블록으로 덮고 싶습니다. 이 때 블록들은 자유롭게 회전해서 놓을 수 있지만, 서로 겹치거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안 됩니다. 위 그림은 한 게임판과 이를 덮는 방법을 보여줍니다.

게임판이 주어질 때 이를 덮는 방법의 수를 계산하는 프로그램을 작성하세요.

입력
입력의 첫 줄에는 테스트 케이스의 수 C (C <= 30) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 2개의 정수 H, W (1 <= H,W <= 20) 가 주어집니다. 다음 H 줄에 각 W 글자로 게임판의 모양이 주어집니다. # 은 검은 칸, . 는 흰 칸을 나타냅니다. 입력에 주어지는 게임판에 있는 흰 칸의 수는 50 을 넘지 않습니다.

출력
한 줄에 하나씩 흰 칸을 모두 덮는 방법의 수를 출력합니다.

예제 입력
3
3 7
#.....#
#.....#
##...##
3 7
#.....#
#.....#
##..###
8 10
##########
#........#
#........#
#........#
#........#
#........#
#........#
##########

예제 출력
0
2
1514
*/

#include <iostream>
#include <string>

int check(int pointer, const int blocks[4][2][2], std::string map[], int y) {
    int x = map[0].length();
    int count = 0;

    while (pointer < y * x && map[pointer / x][pointer % x] == '#') {
        pointer++;
    }
    if (pointer == y * x) {
        return 1;
    }
    int temp_x = pointer % x;
    int temp_y = pointer / x;

    map[temp_y][temp_x] = '#';
    for (int i = 0; i < 4; i++) {
        int block1_x = blocks[i][0][0];
        int block1_y = blocks[i][0][1];
        int block2_x = blocks[i][1][0];
        int block2_y = blocks[i][1][1];
        if (temp_y + block1_y == y || temp_x + block1_x == x || temp_x + block1_x < 0 || temp_y + block2_y == y ||
            temp_x + block2_x == x || temp_x + block2_x < 0) {
            continue;
        }
        if (map[temp_y + block1_y][temp_x + block1_x] == '.' &&
            map[temp_y + block2_y][temp_x + block2_x] == '.') {
            map[temp_y + block1_y][temp_x + block1_x] = '#';
            map[temp_y + block2_y][temp_x + block2_x] = '#';
            count += check(pointer, blocks, map, y);
            map[temp_y + block1_y][temp_x + block1_x] = '.';
            map[temp_y + block2_y][temp_x + block2_x] = '.';
        }
    }
    map[temp_y][temp_x] = '.';
    return count;
}

int main() {
    const int blocks[4][2][2] = {{{-1, 1}, {0, 1}},
                                 {{1,  0}, {0, 1}},
                                 {{1,  1}, {1, 0}},
                                 {{1,  1}, {0, 1}}};
    int cases;
    std::cin >> cases;
    for (int k = 0; k < cases; k++) {
        int h, w, count = 0;
        std::cin >> h >> w;
        auto *map = new std::string[h];
        for (int y = 0; y < h; y++) {
            std::cin >> map[y];
            for (int j = 0; j < w; j++) {
                if (map[y][j] == '.') {
                    count++;
                }
            }
        }
        if (count % 3 != 0) {
            std::cout << "0" << std::endl;
        } else {
            std::cout << check(0, blocks, map, h) << std::endl;
        }
    }
    return 0;
}