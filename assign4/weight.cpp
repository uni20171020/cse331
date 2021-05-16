#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char*argv[])
{

	vector<int> weight;
	string input;
	ifstream inputfile(argv[1]);
	
	getline(inputfile, input);

	int start = 0;
	int stop = 0;
	int ipsize = input.length();
	while (stop != -1)
	{
		stop = input.find(' ', start);
		weight.push_back(stoi(input.substr(start, stop - start)));
		start = stop + 1;
		if (start >= ipsize) break;
	}

	//cout << weight.size() << endl;
	//for (int i = 0; i < weight.size(); i++)
	//{
	//	cout << weight.at(i) << " ";
	//}

	int* A, *B, *C;
	int size = weight.size() / 2;
	A = new int[size + 1];
	B = new int[size + 1];
	C = new int[size + 1];
	A[0] = 0;
	B[0] = 0;
	C[0] = 0;

	for (int i = 1; i < size + 1; i++)
	{
		A[i] = weight.at(2 * i - 2) + max(B[i - 1], C[i - 1]);
		B[i] = weight.at(2 * i - 1) + max(A[i - 1], C[i - 1]);
		C[i] = max(A[i - 1], B[i - 1]);
	}

	int output = max(A[size], B[size]);
	cout << output << endl;

	return 0;
}
