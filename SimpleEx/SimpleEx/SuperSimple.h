#include "matrix.h"
#include <math.h>

class sSimple{
public:
	vector<mat4> conn;
	vector<mat2> thsd;
	vector<bool> ans;
	vector<mat2> layer;

	sSimple(){
		layer.reserve(3);
		layer.push_back(mat2(3, mat1(3, 0.)));
		layer.push_back(mat2(2, mat1(2, 0.)));
		layer.push_back(mat2(1, mat1(1, 0.)));

		thsd.reserve(3);
		thsd.push_back(mat2(3, mat1(3, 0.)));
		thsd.push_back(mat2(2, mat1(2, 0.)));
		thsd.push_back(mat2(1, mat1(1, 0.)));

		ans.reserve(512);
		mat2 t(3, mat1(3, 1));
		for (int i = 0; i < 512; i++){
			intToMat2(i, t);
			if (t[1][0] == 1 && t[0][1] == 1 && t[2][1] == 1 && t[1][2] == 1){
				ans.push_back(true);
			}
			else{
				if (i == 27 || i == 54 || i == 216 || i == 432){
					ans.push_back(true);
				}
				else{
					ans.push_back(false);
				}
			}
		}

	}

	void intToMat2(int a,mat2& b){
		int i, j;
		i = 0;
		while (i<9){
			j = 0;
			while (j < 9){
				b[i][j] = a % 2;
				a = a / 2;
				j++;
			}
			i++;
		}
	}


};