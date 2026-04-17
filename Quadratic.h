#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>

class Quadratic {
    friend Quadratic add(Quadratic& q1, Quadratic& q2);
    friend Quadratic subtract(Quadratic& q1, Quadratic& q2);

public:
    Quadratic(double a, double b, double c); 
    std::string toString();  // 이차방정식을 문자열 형태로 만들어 반환. ax^2+bx+c=0 이런 꼴
	void solve();  //이차방정식의 해를 구해서 출력, 판별식에 따라 해의 개수와 형태를 구분해서 출력

private:
    double a{ 1 };  // 계수인데 2차항의 계수는 0 불가
    double b{ 0 };
    double c{ 0 };
};

#endif


// D=b2−4ac 으로 두는데 
// 이 D 값에 따라 해 출력이 달라짐.
// 애초에 이 문제는 알고리즘 자체보다도 그냥 출력입력 형식을 맞추는게 더 관건