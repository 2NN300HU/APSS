/*문제
와일드카드는 다양한 운영체제에서 파일 이름의 일부만으로 파일 이름을 지정하는 방법이다. 와일드카드 문자열은 일반적인 파일명과 같지만, * 나 ? 와 같은 특수 문자를 포함한다.
와일드카드 문자열을 앞에서 한 글자씩 파일명과 비교해서, 모든 글자가 일치했을 때 해당 와일드카드 문자열이 파일명과 매치된다고 하자. 단, 와일드카드 문자열에 포함된 ? 는 어떤 글자와 비교해도 일치한다고 가정하며, * 는 0 글자 이상의 어떤 문자열에도 일치한다고 본다.
예를 들어 와일드 카드 he?p 는 파일명 help 에도, heap 에도 매치되지만, helpp 에는 매치되지 않는다. 와일드 카드 *p* 는 파일명 help 에도, papa 에도 매치되지만, hello 에는 매치되지 않는다.
와일드카드 문자열과 함께 파일명의 집합이 주어질 때, 그 중 매치되는 파일명들을 찾아내는 프로그램을 작성하시오.

입력
입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 10) 가 주어진다. 각 테스트 케이스의 첫 줄에는 와일드카드 문자열 W 가 주어지며, 그 다음 줄에는 파일명의 수 N (1 <= N <= 50) 이 주어진다. 그 후 N 줄에 하나씩 각 파일명이 주어진다. 파일명은 공백 없이 알파벳 대소문자와 숫자만으로 이루어져 있으며, 와일드카드는 그 외에 * 와 ? 를 가질 수 있다. 모든 문자열의 길이는 1 이상 100 이하이다.

출력
각 테스트 케이스마다 주어진 와일드카드에 매치되는 파일들의 이름을 한 줄에 하나씩 아스키 코드 순서(숫자, 대문자, 소문자 순)대로 출력한다.

예제 입력
2
he?p
3
help
heap
helpp
*p*
3
help
papa
hello

예제 출력
heap
help
help
papa
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int cache[101][101];
string wildcard, testCase;

bool checkString(int w, int t) {
    if (w == wildcard.size() && t == testCase.size()) {
        return true;
    }

    int &target = cache[w][t];
    if (target == 0) {
        return false;
    }
    target = 0;

    if (w == wildcard.size()) {
        return false;
    }
    if (t == testCase.size()) {
        if (wildcard[w] == '*') {
            return checkString(w + 1, t);
        }
        return false;
    }

    if (wildcard[w] == '?') {
        return checkString(w + 1, t + 1);
    } else if (wildcard[w] == '*') {
        return checkString(w + 1, t + 1) || checkString(w, t + 1) || checkString(w + 1, t);
    } else {
        if (wildcard[w] == testCase[t]) {
            return checkString(w + 1, t + 1);
        } else {
            return false;
        }
    }
}

int main() {
    int cases;
    cin >> cases;
    for (int c = 0; c < cases; c++) {
        cin >> wildcard;
        int stringCases;
        cin >> stringCases;
        vector<std::string> strings;
        for (int i = 0; i < stringCases; i++) {
            cin >> testCase;
            memset(cache, -1, sizeof(cache));
            if (checkString(0, 0)) {
                strings.push_back(testCase);
            }
        }
        sort(strings.begin(), strings.end());
        for (string &temp:strings) {
            cout << temp << endl;
        }
    }
    return 0;
}