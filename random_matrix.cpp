#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<string>
using namespace std;

int main() {
	int times = 20;
	while(times >= 1) {
		srand(time(0));
		fstream f,g,q;
		int r=times,c=times;
		int a[r*c];
		string input = "Rand_input_matrix_" + to_string(c) + ".txt";
		string weight = "Rand_weight_matrix_" + to_string(c) + ".txt";
		string bias = "Rand_bias_matrix_" + to_string(c) + ".txt";

		f.open(input, ios::out);
		g.open(weight, ios::out);
		q.open(bias, ios::out);

		f << r << "\n" << c << "\n";
		g << r << "\n" << c << "\n";
		q << r << "\n" << c << "\n";

		float X = 1000.99;

		for(int i = 0; i < r*c; i++) {
			float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));
			f << r2 << "\n";
		}
		for(int i = 0; i < r*c; i++) {
			float r3 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));
			g << r3 << "\n";
		}
		for(int i = 0; i < r*c; i++) {
			float r4 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/X));
			q << r4 << "\n";
		}
		
		times--;
		f.close();
		g.close();
		q.close();
	}

	return 0;
}

