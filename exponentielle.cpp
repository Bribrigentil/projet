#include<iostream>
#include<cmath>
using namespace std;

void expo(double a, double b, double & re, double & im)
{
  re = exp(a)*cos(b);
  im = exp(a)*sin(b);
  cout << re << " " << im <<endl;
}

int main()
{
  double a = 2.0;
  double b = 5.0;
  double re, im;
  expo(a, b, re, im);
  cout << "bisou squeezie";

}
