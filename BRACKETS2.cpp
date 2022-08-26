/*문제

Best White is a mathematics graduate student at T1 University.
Recently, he finished writing a paper and he decided to polish it.
As he started to read it from the beginning, he realized that some of the formulas have problems: some of the brackets are mismatched! Since there are so many formulas in his paper, he decided to check their validity with a computer program.
The following kinds of brackets are included in Best White’s paper.

Round brackets are opened by a ( and closed by a ).
Curly brackets are opened by a { and closed by a }.
Square brackets are opened by a [ and closed by a ].

A formula is said well-matched when the following conditions are met:

Every bracket has a corresponding pair.
( corresponds to ), [ corresponds to ], et cetera.
Every bracket pair is opened first, and closed later.
No two pairs "*cross*" each other.
For example, [(]) is not well-matched.

Write a program to help Best White by checking if each of his formulas is well-matched.
To make the problem easier, everything other than brackets are removed from the formulas.

입력

The first line of the input will contain the number of test cases C\ (1 \le C \le 100).
Each test is given in a single line as a character string.
The strings will only include characters in "[](){}" (quotes for clarity).
The length of the string will not exceed 10,000.

출력

For each test case, print a single line "YES" when the formula is well-matched; print "NO" otherwise.
(quotes for clarity)

예제 입력
3
()()
({[}])
({}[(){}])

예제 출력
YES
NO
YES
*/

#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool brackets(string& input) {
    stack<char> temp;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(' || input[i] == '{' || input[i] == '[') {
            temp.push(input[i]);
        } else {
            if (temp.empty()) return false;
            char need;
            switch (input[i]) {
                case ')':
                    need = '(';
                    break;
                case '}':
                    need = '{';
                    break;
                case ']':
                    need = '[';
                    break;
            }
            if (temp.top() != need) {
                return false;
            } else {
                temp.pop();
            }
        }
    }
    if(temp.empty()) return true;
    return false;
}

int main() {
    int cases;
    cin >> cases;
    for (int c = 0; c < cases; c++) {
        string input;
        cin >> input;
        if (brackets(input)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}