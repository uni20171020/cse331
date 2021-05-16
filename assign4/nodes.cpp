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


	int* A, * B, * C;
	int size = weight.size() / 2;
	A = new int[size + 1];
	B = new int[size + 1];
	C = new int[size + 1];
	A[0] = 0;
	B[0] = 0;
	C[0] = 0;

	vector<int> nodesa;// each vector get nodes from each process
	vector<int> nodesb;
	vector<int> nodesc;
	vector<int> tempa;// temp vector for updating nodesc
	vector<int> tempb;

	// case for i = 1 in above 'for'
	A[1] = weight.at(0);
	B[1] = weight.at(1);
	C[1] = 0;
	nodesa.push_back(1);
	nodesb.push_back(2);

	int a, b, c;
	for (int i = 2; i < size + 1; i++)
	{
		a = A[i - 1];
		b = B[i - 1];
		c = C[i - 1];
		A[i] = weight.at(2 * i - 2) + max(b, c);
		B[i] = weight.at(2 * i - 1) + max(a, c);
		C[i] = max(a, b);

		tempa.clear();
		tempa.resize(nodesa.size());
		copy(nodesa.begin(), nodesa.end(), tempa.begin());//copy nodesa to tempa
		tempb.clear();
		tempb.resize(nodesb.size());
		copy(nodesb.begin(), nodesb.end(), tempb.begin());//copy nodesb to tempb
		nodesa.swap(nodesb);
		/*I use swap function, because if resulf of max(b,c) and max(a,c) is not c,
		we can just push_back after swap!*/

		if (b < c)
		{
			nodesa.clear();
			nodesa.resize(nodesc.size());
			copy(nodesc.begin(), nodesc.end(), nodesa.begin());
		}
		if (a < c)
		{
			nodesb.clear();
			nodesb.resize(nodesc.size());
			copy(nodesc.begin(), nodesc.end(), nodesb.begin());
		}
		nodesa.push_back(2 * i - 1);
		nodesb.push_back(2 * i);

		nodesc.clear();
		if (a >= b)
		{
			nodesc.resize(tempa.size());
			//we need temp value because we use value of before updating
			copy(tempa.begin(), tempa.end(), nodesc.begin());
		}
		else
		{
			nodesc.resize(tempb.size());
			copy(tempb.begin(), tempb.end(), nodesc.begin());
		}
		//nodesc.pop_back();

	}

	int output = max(A[size], B[size]);

	if (output == A[size])
	{
		for (size_t i = 0; i < nodesa.size(); i++)
		{
			cout << nodesa.at(i) << " ";
		}
	}
	else
	{
		for (size_t i = 0; i < nodesb.size(); i++)
		{
			cout << nodesb.at(i) << " ";
		}
	}
	cout << endl;

	return 0;
}
