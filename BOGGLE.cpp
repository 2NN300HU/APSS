/*보글(Boggle) 게임은 그림 (a)와 같은 5x5 크기의 알파벳 격자인
게임판의 한 글자에서 시작해서 펜을 움직이면서 만나는 글자를 그 순서대로 나열하여 만들어지는 영어 단어를 찾아내는 게임입니다. 펜은 상하좌우, 혹은 대각선으로 인접한 칸으로 이동할 수 있으며 글자를 건너뛸 수는 없습니다. 지나간 글자를 다시 지나가는 것은 가능하지만, 펜을 이동하지않고 같은 글자를 여러번 쓸 수는 없습니다.
예를 들어 그림의 (b), (c), (d)는 각각 (a)의 격자에서 PRETTY, GIRL, REPEAT을 찾아낸 결과를 보여줍니다.
보글 게임판과 알고 있는 단어들의 목록이 주어질 때, 보글 게임판에서 각 단어를 찾을 수 있는지 여부를 출력하는 프로그램을 작성하세요.
주의: 알고리즘 문제 해결 전략 6장을 읽고 이 문제를 푸시려는 분들은 주의하세요. 6장의 예제 코드는 이 문제를 풀기에는 너무 느립니다. 6장의 뒷부분과 8장을 참조하세요.

입력
입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 각 5줄에 5글자로 보글 게임판이 주어집니다. 게임판의 모든 칸은 알파벳 대문자입니다.
그 다음 줄에는 우리가 알고 있는 단어의 수 N(1 <= N <= 10)이 주어집니다. 그 후 N줄에는 한 줄에 하나씩 우리가 알고 있는 단어들이 주어집니다. 각 단어는 알파벳 대문자 1글자 이상 10글자 이하로 구성됩니다.

출력
각 테스트 케이스마다 N줄을 출력합니다. 각 줄에는 알고 있는 단어를 입력에 주어진 순서대로 출력하고, 해당 단어를 찾을 수 있을 경우 YES, 아닐 경우 NO를 출력합니다.

예제 입력
1
URLPM
XPRET
GIAET
XTNZY
XOQRS
6
PRETTY
GIRL
REPEAT
KARA
PANDORA
GIAZAPX

예제 출력
PRETTY YES
GIRL YES
REPEAT YES
KARA NO
PANDORA NO
GIAZAPX YES
*/

#include <iostream>
#include <string>


bool check(std::string find_word, char map[][5], int x, int y) {
    if (find_word.length() == 0) {
        return true;
    }
    char temp = find_word.back();
    find_word.pop_back();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0 || x + i < 0 || x + i > 4 || y + j < 0 || y + j > 4) {
                continue;
            }
            if (map[x + i][y + j] == temp) {
                if (check(find_word, map, x + i, y + j)) {
                    return true;
                }
            }
        }
    }
    find_word.push_back(temp);
    return false;
}

bool check_start(std::string find_word, char map[][5]) {
    char temp = find_word.back();
    find_word.pop_back();
    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++) {
            if (map[k][j] == temp) {
                if (check(find_word, map, k, j)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int cases;
    std::cin >> cases;
    for (int k = 0; k < cases; k++) {
        char map[5][5];
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                std::cin >> map[i][j];
            }
        }
        int find;
        std::cin >> find;
        std::string find_word;
        for (int i = 0; i < find; i++) {
            std::cin >> find_word;
            std::cout << find_word;
            if (check_start(find_word, map)) {
                std::cout << " YES" << std::endl;
            } else {
                std::cout << " NO" << std::endl;
            }
        }
    }
    return 0;
}
