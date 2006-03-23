#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;
#include <assert.h>

#include <plush.h>


void read_float(const string &txt, pl_Float &out, pl_Float def) {
	string buffer;
	cerr << txt << " [" << setprecision(1) << std::fixed << def << "] = "; cerr.flush();
	getline(cin, buffer);
	if (buffer.empty()) {
          out = def;
          return;
	}
	double val;
	istringstream istr(buffer);
	assert(!istr.fail());
	istr >> val;
	assert(!istr.fail());
	out = val;
}

int main() {
	const pl_sInt keyWidth = 2;
	pl_Float data[] = {1.0, 0.0, 0.0, 1.0, -1.0, 0.0, 0.0, -1.0, 1.0, 0.0};
	
	pl_Spline spline = { data, keyWidth, sizeof(data) / sizeof(data[0]) / keyWidth, 0.0, 0.0, 0.0};
	cerr << "Kochanek-Bartels-Spline (TCB)" << endl;
	read_float("Tension", spline.tens, 0.0);
	read_float("Continuity", spline.cont, 0.0); spline.cont = -spline.cont; // Korrektur
	read_float("Bias", spline.bias, 0.0);

	pl_Float val[2];
	cout << "Frame\tValue1\tValue2\n";
	for (pl_Float f = 0.0; f < spline.numKeys - 1; f += 0.1f) {
		plSplineGetPoint(&spline, f, val);
		cout << f << "\t" << val[0] << '\t' << val[1] << endl;
	}
	return 0;
}
