#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>

using namespace std;

int main() {

	string input;
	vector<double> num;
	double x = 0.0, sum = 0.0;
	int flag = 1;

	while (flag && getline(cin, input))
	{
		istringstream in(input);
		while (in >> x)
		{
			num.push_back(x);
			sum = sum + x;
		}
		flag = 0;
	}
	double average = 0.0, double_num = 0.0;
	int count_int = num.size();
	double count = static_cast<double>(num.size());
	average = sum / count;
	double deviation = 0.0;
	for (int i = 0; i < count_int; i++)
		double_num = double_num + (num[i] * num[i]);
	deviation = sqrt(double_num / count - average*average);


	cout << deviation << endl;
	system("pause");
	return 0;
}
