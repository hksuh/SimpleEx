#include "matrix.h"
#include <math.h>

void sigmoid(double& a, double b){
	a=b-a;
	//if (a > 8.){a = 0.;return;}
	//if (a < -8.){ a = 1.; return;}
	a = 1. / (1. + exp(27.*a));
}

void sigmoid(mat2& a, const mat2& b){
	int n1 = (int) a.size();
	int n2;
	while (n1>0){
		n1--;
		n2 = (int) a[n1].size();
		while (n2 > 0){
			n2--;
			sigmoid(a[n1][n2], b[n1][n2]);
		}
	}
}



class indiv{
public:
	vector<mat2> thsd;
	vector<mat4> connect;
	vector<mat2> normTable;
	int depth;
	double score;

	indiv(){
		score = -2.;
		//clock_t time_a = clock();
		
		depth = 7;
		thsd.reserve(depth-1);
		//thsd.push_back(mat2(16, mat1(16, 0.)));
		//thsd.push_back(mat2(16, mat1(16, 0.)));
		//thsd.push_back(mat2(8, mat1(8, 0.)));
		thsd.push_back(mat2(8, mat1(8, 0.)));
		thsd.push_back(mat2(4, mat1(4, 0.)));
		thsd.push_back(mat2(4, mat1(4, 0.)));
		thsd.push_back(mat2(2, mat1(2, 0.)));
		thsd.push_back(mat2(2, mat1(2, 0.)));
		thsd.push_back(mat2(1, mat1(1, 0.)));
		
		//clock_t time_b = clock();

		randMat(thsd[0], 0.7, -0.7);
		for (int i1 = 1; i1 < depth - 1; i1++){
			randMat(thsd[i1], 1.,-1.);
		}

		//clock_t time_c = clock();

		connect.reserve(depth - 1);
		//connect.push_back(mat4(16, mat3(16, mat2(8,mat1(8,-1.)))));
		//connect.push_back(mat4(16, mat3(16, mat2(16, mat1(16, -1.)))));
		//connect.push_back(mat4(8, mat3(8, mat2(16, mat1(16, -1.)))));
		connect.push_back(mat4(8, mat3(8, mat2(8, mat1(8, -4.)))));
		connect.push_back(mat4(4, mat3(4, mat2(8, mat1(8, -4.)))));
		connect.push_back(mat4(4, mat3(4, mat2(4, mat1(4, -4.)))));
		connect.push_back(mat4(2, mat3(2, mat2(4, mat1(4, -4.)))));
		connect.push_back(mat4(2, mat3(2, mat2(2, mat1(2, -4.)))));
		connect.push_back(mat4(1, mat3(1, mat2(2, mat1(2, -4.)))));
		
		//clock_t time_d = clock();

		normTable.reserve(depth - 1);
		//normTable.push_back(mat2(16, mat1(16, 0.)));
		//normTable.push_back(mat2(16, mat1(16, 0.)));
		//normTable.push_back(mat2(8, mat1(8, 0.)));
		normTable.push_back(mat2(8, mat1(8, 0.)));
		normTable.push_back(mat2(4, mat1(4, 0.)));
		normTable.push_back(mat2(4, mat1(4, 0.)));
		normTable.push_back(mat2(2, mat1(2, 0.)));
		normTable.push_back(mat2(2, mat1(2, 0.)));
		normTable.push_back(mat2(1, mat1(1, 0.)));

		//randConn(connect[0], 1.);
		int i22 = 0;
		//while (i22 < 5){
		//	randConn(connect[i22],1.);
		//	i22++;
		//}
		while (i22<depth-1){
			randConnSmall(connect[i22],normTable[i22]);
			i22++;
		}
		//clock_t time_e = clock();

		//cout << "a to b: " << ((double)(time_b - time_a)) / CLOCKS_PER_SEC << endl;
		//cout << "b to c: " << ((double)(time_c - time_b)) / CLOCKS_PER_SEC << endl;
		//cout << "c to d: " << ((double)(time_d - time_c)) / CLOCKS_PER_SEC << endl;
		//cout << "d to e: " << ((double)(time_e - time_d)) / CLOCKS_PER_SEC << endl;
		
	}


	void propagate(vector<mat2>& layer){
		for (int i = 4; i < depth-1; i++){
			//clock_t time_a = clock();
			product(connect[i], layer[i], layer[i + 1]);
			sigmoid(layer[i + 1], thsd[i]);
			//cout << i+1 << " layer" << endl;
			//showMat(layer[i + 1]);
			//clock_t time_b = clock();
			//cout << i << " layer:" << ((double)(time_b - time_a)) / CLOCKS_PER_SEC << endl;
		}
	}

	void show(){
		cout << "========connect========" << endl;
		for (int i = 5; i <depth-1; i++){
			for (int j = 0; j < connect[i].size(); j++){
				for (int k = 0; k < connect[i][j].size(); k++){
					cout << "(i,j) :" << j << ", " << k << endl;
					showMat(connect[i][j][k]);
				}
			}
		}
		cout << "========connect========" << endl;
		for (int i = 0; i <depth - 1; i++){
			showMat(thsd[i]);
		}
	}

	void newRand(){
		for (int i1 = 1; i1 < depth - 1; i1++){
			randMat(thsd[i1], 1., -1.);
		}
		int i22 = 0;
		while (i22<depth - 1){
			newrandConnSmall(connect[i22],normTable[i22]);
			i22++;
		}
	}

	void perturb(double foot){
		double foot2;
		for (int i = 0; i <connect.size(); i++){
			for (int j = 0; j < connect[i].size(); j++){
				for (int k = 0; k < connect[i][j].size(); k++){
					foot2 = 2.*foot*normTable[i][j][k];
					for (int l = 0; l < connect[i][j][k].size(); l++){
						for (int m = 0; m < connect[i][j][k][l].size(); m++){
							if (connect[i][j][k][l][m]>-2.){
								if (rand() % 5 == 0){
									connect[i][j][k][l][m] += foot2*(((double)rand() / (double)RAND_MAX) - .5);
								}
								if (connect[i][j][k][l][m]>normTable[i][j][k]){ connect[i][j][k][l][m] = normTable[i][j][k]; }
								if (connect[i][j][k][l][m]<-1.*normTable[i][j][k]){ connect[i][j][k][l][m] = -1.*normTable[i][j][k]; }
							}
						}
					}
				}
			}
		}
		foot2 = foot*2.;
		for (int i = 0; i <thsd.size(); i++){
			for (int j = 0; j < thsd[i].size(); j++){
				for (int k = 0; k < thsd[i][j].size(); k++){
					if (thsd[i][j][k]>-2.){
						if (rand() % 5 == 0){
							thsd[i][j][k] += foot2*(((double)rand() / (double)RAND_MAX) - .5);
						}
						if (thsd[i][j][k]>1.25){ thsd[i][j][k] = 1.25; }
						if (thsd[i][j][k]<-1.25){ thsd[i][j][k] = -1.25; }
					}
				}
			}
		}
	}

	void copy(indiv& that){
		that.score = score;
		that.depth = depth;
		for (int i = 0; i <connect.size(); i++){
			for (int j = 0; j < connect[i].size(); j++){
				for (int k = 0; k < connect[i][j].size(); k++){
					for (int l = 0; l < connect[i][j][k].size(); l++){
						for (int m = 0; m < connect[i][j][k][l].size(); m++){
							that.connect[i][j][k][l][m] = connect[i][j][k][l][m];
						}
					}
				}
			}
		}
		for (int i = 0; i <thsd.size(); i++){
			for (int j = 0; j < thsd[i].size(); j++){
				for (int k = 0; k < thsd[i][j].size(); k++){
					that.thsd[i][j][k] = thsd[i][j][k];
				}
			}
		}
	}

	void getScore(vector<mat2>& layer, mat3& trainInput){
		score = 0;
		for (int rai = 0; rai < 99; rai++){
			layer[0] = trainInput[rai];
			propagate(layer);
			if (rai % 2 == 0){
				score += layer[6][0][0] * layer[6][0][0];
			}
			else{
				score += (1. - layer[6][0][0]) * (1. - layer[6][0][0]);
			}
		}
		score = score / 99.;
	}

};