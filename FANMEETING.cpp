/*문제
가장 멤버가 많은 아이돌 그룹으로 기네스 북에 올라 있는 혼성 팝 그룹 하이퍼시니어가 데뷔 10주년 기념 팬 미팅을 개최했습니다. 팬 미팅의 한 순서로, 멤버들과 참가한 팬들이 포옹을 하는 행사를 갖기로 했습니다. 하이퍼시니어의 멤버들은 우선 무대에 일렬로 섭니다. 팬 미팅에 참가한 M명의 팬들은 줄을 서서 맨 오른쪽 멤버에서부터 시작해 한 명씩 왼쪽으로 움직이며 멤버들과 하나씩 포옹을 합니다. 모든 팬들은 동시에 한 명씩 움직입니다. 아래 그림은 행사 과정의 일부를 보여줍니다. a~d는 네 명의 하이퍼시니어 멤버들이고, 0~5는 여섯 명의 팬들입니다.
하지만 하이퍼시니어의 남성 멤버들이 남성 팬과 포옹하기가 민망하다고 여겨서, 남성 팬과는 포옹 대신 악수를 하기로 했습니다. 줄을 선 멤버들과 팬들의 성별이 각각 주어질 때 팬 미팅이 진행되는 과정에서 하이퍼시니어의 모든 멤버가 동시에 포옹을 하는 일이 몇 번이나 있는지 계산하는 프로그램을 작성하세요.

입력
첫 줄에 테스트 케이스의 개수 C (C≤20)가 주어집니다. 각 테스트 케이스는 멤버들의 성별과 팬들의 성별을 각각 나타내는 두 줄의 문자열로 구성되어 있습니다. 각 문자열은 왼쪽부터 오른쪽 순서대로 각 사람들의 성별을 나타냅니다.
M은 해당하는 사람이 남자, F는 해당하는 사람이 여자임을 나타냅니다. 멤버의 수와 팬의 수는 모두 1 이상 200,000 이하의 정수이며, 멤버의 수는 항상 팬의 수 이하입니다.

출력
각 테스트 케이스마다 한 줄에 모든 멤버들이 포옹을 하는 일이 몇 번이나 있는지 출력합니다.

예제 입력
4
FFFMMM
MMMFFF
FFFFF
FFFFFFFFFF
FFFFM
FFFFFMMMMF
MFMFMFFFMMMFMF
MMFFFFFMFFFMFFFFFFMFFFMFFFFMFMMFFFFFFF

예제 출력
1
6
2
2
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

std::vector<int> multiply(std::vector<int> a, std::vector<int> b) {
    auto result = std::vector<int>(a.size() + b.size() - 1,0);
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            result[i + j] += a[i] * b[j];
        }
    }
    return result;
}

std::vector<int> sum(std::vector<int> a, std::vector<int> b, int k) {
    auto result = std::vector<int>(std::max(a.size() , b.size()+k),0);
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i];
    }
    for (int i = 0; i < b.size(); i++) {
        result[i+k] += b[i];
    }
    return result;
}

std::vector<int> sub(std::vector<int> a, std::vector<int> b) {
    auto result = std::vector<int>(std::max(a.size() , b.size()),0);
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i];
    }
    for (int i = 0; i < b.size(); i++) {
        result[i] -= b[i];
    }
    return result;
}

std::vector<int> karatsuba(std::vector<int> a, std::vector<int> b) {
    if (a.size() > b.size()) {
        return karatsuba(b, a);
    }
    if (a.size() < 100) {
        return multiply(a, b);
    }
    if (a.size() == 0) {
        return std::vector<int>();
    }

    int half = b.size() / 2;
    std::vector<int> a0(a.begin(), a.begin() + std::min<int>(a.size(), half));
    std::vector<int> a1(a.begin() + std::min<int>(a.size(), half), a.end());
    std::vector<int> b0(b.begin(), b.begin() + half);
    std::vector<int> b1(b.begin() + half, b.end());

    std::vector<int> z1 = karatsuba(a0, b0);
    std::vector<int> z2 = karatsuba(a1, b1);
    std::vector<int> z3 = karatsuba(sum(a0, a1, 0), sum(b0, b1, 0));
    z3 = sub(sub(z3,z1),z2);
    return sum(sum(z1,z2,half*2),z3,half);
}

int hug(std::string member, std::string fan) {
    auto menberVector = std::vector<int>(member.length());
    auto fanVector = std::vector<int>(fan.length());
    for (int i = 0; i < menberVector.size(); i++) {
        if (member[i] == 'M') {
            menberVector[member.length() - i - 1] = true;
        } else {
            menberVector[member.length() - i - 1] = false;
        }

    }
    for (int i = 0; i < fanVector.size(); i++) {
        if (fan[i] == 'M') {
            fanVector[i] = true;
        } else {
            fanVector[i] = false;
        }

    }
    std::vector<int> resultint = karatsuba(menberVector, fanVector);
    int count = 0;
    for (int i = menberVector.size() - 1; i < fanVector.size(); i++) {
        if (resultint[i]==0) {
            count++;
        }
    }


    return count;
}

int main() {
    int cases;
    std::cin >> cases;
    for (int c = 0; c < cases; c++) {
        std::string member, fan;
        std::cin >> member >> fan;
        std::cout << hug(member, fan) << std::endl;
    }
    return 0;
}