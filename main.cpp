#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "Quadratic.h"

using namespace std;

Quadratic::Quadratic(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

string Quadratic::toString() {  // 이차방정식을 문자열로 만들어 반환
    double ta = a;
    double tb = b; 
    double tc = c;

	if (fabs(ta) < 1e-10) ta = 0;  // 계수가 0에 가까운 경우 0으로 처리
    if (fabs(tb) < 1e-10) tb = 0;
    if (fabs(tc) < 1e-10) tc = 0;

	string sa = to_string(ta); // to_string은 double을 문자열로 바꿔주는 함수. 일반함수임 
    string sb = to_string(tb); // 근데 실수타입의 숫자를 문자열로 바꾸면 뒤에 0이 많이 붙음.
    string sc = to_string(tc); // 애초에 실수타입의 숫자는 정확히 정수가 아니라 2.00000000001 같은 근사값이기 때문

    while (!sa.empty() && sa[sa.size() - 1] == '0') {    // 문자열 맨 뒤에 붙은 쓸데없는 0들을 하나씩 지우는 것
		sa.erase(sa.size() - 1, 1);             // erase는 문자열에서 특정 위치의 문자를 지우는 함수. 첫 번째 인자는 지울 문자의 위치, 두 번째 인자는 지울 문자 수
    }
    if (!sa.empty() && sa[sa.size() - 1] == '.') {   // 만약 뒤의 0을 모두 지웠는데
        sa.erase(sa.size() - 1, 1);               // 문자열 맨 끝이 .만 덩그러니 있으면 그것도 지워라
    }

    while (!sb.empty() && sb[sb.size() - 1] == '0') {
        sb.erase(sb.size() - 1, 1);
    }
    if (!sb.empty() && sb[sb.size() - 1] == '.') {
        sb.erase(sb.size() - 1, 1);
    }

    while (!sc.empty() && sc[sc.size() - 1] == '0') {
        sc.erase(sc.size() - 1, 1);
    }
    if (!sc.empty() && sc[sc.size() - 1] == '.') {
        sc.erase(sc.size() - 1, 1);
    }

    string result = sa + "x^2";      // string은 + 연산으로 문자열을 이어붙일 수 있음

    if (tb >= 0) {           // 상수와 대소관계를 비교해야 하므로 tb(이 함수의 지역변수)를 사용
        result += "+" + sb + "x";    // 숫자버전의 계수가 0이상이면 문자버전의 계수를 형식에 맞춰 result 라는
    }                                // result 라는 string 객체에 누적
    else {
        result += sb + "x"; // 숫자버전 계수가 음수면 sb는 -를 가지고 있을 것. + 를 문자로 안붙임
    }

    if (tc >= 0) {
        result += "+" + sc;
    }
    else {
        result += sc;
    }

    result += "=0";

    return result;
}

void Quadratic::solve() {                
    double d = b * b - 4 * a * c;     // 이 d를 갖고 출력방식을 결정

    if (fabs(d) < 1e-10) {            // d가 사실상 0에 가깝게 작은 수라면 d는 0이라고 침
        d = 0;
    }

    cout << "Solution of " << toString() << ": ";    // solve는 결과를 바로 출력함. 
                                                     // 근데 이 뒤에 뭐가 올지를 d로 결정
    if (d < 0) {
        cout << "No real roots";
    }
    else if (d == 0) {
        double x = -b / (2 * a);      // 중근이면 -b / (2 * a)로 근 구하면 됨

        if (fabs(x) < 1e-10) {              // 만일, 구한 근이 0에 매우 근접한 수라면 0으로 침
            x = 0;
        }

        cout << fixed << setprecision(2) << "x=" << x;
    }
    else {
        double x1 = (-b + sqrt(d)) / (2 * a);         // 중근이 아닐 경우 근의 공식 그대로 적용
        double x2 = (-b - sqrt(d)) / (2 * a);         // +버전 과 -버전 구함.

        if (fabs(x1) < 1e-10) {                 
            x1 = 0; 
        }
        if (fabs(x2) < 1e-10) {                 // 두 근 모두 0에 근접한지 검사
            x2 = 0;
        }

        cout << fixed << setprecision(2) << "x=" << x1 << " or " << x2;
    }

    cout << endl;
}

Quadratic add(Quadratic& q1, Quadratic& q2) {
    Quadratic q3(q1.a + q2.a, q1.b + q2.b, q1.c + q2.c);
    return q3;      // 이건 연산자 오버로딩은 아님 
}

Quadratic subtract(Quadratic& q1, Quadratic& q2) {
    Quadratic q3(q1.a - q2.a, q1.b - q2.b, q1.c - q2.c);
    return q3;
}

int main() {
    double a, b, c;

    while (true) {   
        cin >> a >> b >> c;

        if (a == 0) {
            cout << "Input 'a' cannot be zero. Please input again." << endl;  
        }
        else {
            break;
        }
    }

    // a가 잘못된 입력이 들어오면 계속 루프
    // a==0이 깨지면 입력이 제대로 들어왔다는 뜻 -> 루프 탈출


    Quadratic q1(a, b, c);
    cout << q1.toString() << endl;

    while (true) {
        cin >> a >> b >> c;

        if (a == 0) {
            cout << "Input 'a' cannot be zero. Please input again." << endl;
        }
        else {
            break;
        }
    }

    Quadratic q2(a, b, c);
    cout << q2.toString() << endl;
    cout << endl;

    q1.solve();
    q2.solve();
    cout << endl;

    Quadratic sum = add(q1, q2);
    Quadratic diff = subtract(q1, q2);

    cout << "(" << q1.toString() << ")+(" << q2.toString() << ")=" << sum.toString() << endl;
    cout << "(" << q1.toString() << ")-(" << q2.toString() << ")=" << diff.toString() << endl;

    return 0;

}