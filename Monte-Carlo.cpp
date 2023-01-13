#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
using namespace std;

int main() {
	
	double R;
	int count = 0;
	int i;
	double rez;
	const double pi = 3.141592653589793;
	cout << "Enter the radius: ";
	cin >> R;
	cout << "Enter the number of iterations: ";
	cin >> i;
	for (int a = 0; a < i; a++) {
		double x = 2 * a * R / i - R;
		for (int b = 0; b < i; b++) {
			double y = 2 * b * R / i - R;
			for (int c = 0; c < i; c++) {
				double z = 2 * c * R / i - R;
				if ((sqrt(x * x + y * y + z * z)) <= R)
					count = count + 1;
			}
		}
	}
	rez = (count / i) * 8 * R * R * R;
	double vol = pi * R * R * R * (4 / 3);
	double err = vol - rez;
	cout << "The volume is " << rez << endl;
	cout << "The volume is " << vol << endl;
	cout << "The margin of error is " << err;
} 
#include <iostream>
#include <cmath>
using namespace std;
int main() {
	const double pi = 3.1415;
	double R, H, V, V0, x, y, z;
	int N = 1500, n = 0;
	cout << "Enter R = ";
	cin >> R;
	cout << "Enter H = ";
	cin >> H;
	V0 = 4 * R * R * (H + R);
	for (int i = 0;i <= N;i++) {
		x = 2 * i * R / N - R;
		for (int j = 0;j <= N;j++) {
			y = 2 * j * R / N - R;
			for (int k = 0;k <= N;k++) {
				z = k * (H + R) / N;
				if (((sqrt(x * x + y * y + z * z) <= R)
					n++;
			}
		}
	}
	V = n/N*8*R*R*R;
	cout << "V = " << V << " : " << pi * R * R * H / 3 + 2 * pi * pow(R, 3) / 3 << endl;
	return 0;
}
