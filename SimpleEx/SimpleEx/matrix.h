#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef vector<double> mat1;
typedef vector<mat1> mat2;
typedef vector<mat2> mat3;
typedef vector<mat3> mat4;

void randMat(mat2& a,double init,double fin){
	int n = a.size(); int m = a[0].size();
	//srand((unsigned int)time(NULL));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			a[i][j]=(init-fin)*((double)rand() / (double)RAND_MAX) +fin;
		}
	}
}

void randMat(mat4& a, double init, double fin){
	//srand((unsigned int)time(NULL));

	int n = a.size(); int m = a[0].size(); int p = a[0][0].size(); int q = a[0][0][0].size();
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			for (int k = 0; k < p; k++){
				for (int l = 0; l < q; l++){
					a[i][j][k][l] = (init - fin)*((double)rand() / (double)RAND_MAX) + fin;
				}
			}
		}
	}
}

void randConn(mat4& a,double input_density){
	//srand((unsigned int)time(NULL));

	int n = (int)a.size(); int m = (int)a[0].size(); int p = (int)a[0][0].size(); int q = (int)a[0][0][0].size();
	double dx, dy, drsq;
	int normF;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			normF = 0;
			for (int k = 0; k < p; k++){
				for (int l = 0; l < q; l++){
					dx = ((i + 0.5) / n - (k + 0.5) / p);
					dy = ((j + 0.5) / m - (l + 0.5) / q);
					drsq = dx*dx + dy*dy;
					if (drsq<0.0625){
						a[i][j][k][l] = 2.*((double)rand() / (double)RAND_MAX)-1.;
						normF++;
					}
				}
			}
			for (int k = 0; k < p; k++){
				for (int l = 0; l < q; l++){
					if (a[i][j][k][l]>0){
						a[i][j][k][l] =input_density* a[i][j][k][l] / (double)normF;
					}
				}
			}
		}
	}
}

void randConnSmall(mat4& a,mat2& b){
	//srand((unsigned int)time(NULL));

	int n = (int)a.size(); int m = (int)a[0].size(); int p = (int)a[0][0].size(); int q = (int)a[0][0][0].size();
	double dx, dy, drsq, minL;
	int normF;
	minL = 2.01 / ((double)(n*m));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			normF = 0;
			for (int k = 0; k < p; k++){
				for (int l = 0; l < q; l++){
					dx = ((i + 0.5) / n - (k + 0.5) / p);
					dy = ((j + 0.5) / m - (l + 0.5) / q);
					drsq = dx*dx + dy*dy;
					if (drsq<minL){
						a[i][j][k][l] = 2.* ((double)rand() / (double)RAND_MAX) -1.;
						normF++;
					}
				}
			}
			b[i][j] = 1. / (double)normF;
			for (int k = 0; k < p; k++){
				for (int l = 0; l < q; l++){
					if (a[i][j][k][l]>0){
						a[i][j][k][l] = a[i][j][k][l]*b[i][j];
					}
				}
			}
		}
	}
}

void newrandConnSmall(mat4& a,const mat2& b){
	//srand((unsigned int)time(NULL));

	int n = (int)a.size(); int m = (int)a[0].size(); int p = (int)a[0][0].size(); int q = (int)a[0][0][0].size();
	double dx, dy, drsq, minL;
	minL = 2.01 / ((double)(n*m));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			for (int k = 0; k < p; k++){
				for (int l = 0; l < q; l++){
					dx = ((i + 0.5) / n - (k + 0.5) / p);
					dy = ((j + 0.5) / m - (l + 0.5) / q);
					drsq = dx*dx + dy*dy;
					if (drsq<minL){
						a[i][j][k][l] = 2.*b[i][j]*( ((double)rand() / (double)RAND_MAX) - .5);
					}
				}
			}
		}
	}
}



void product(const mat4& a, const mat2& b,mat2& c){
	int i = (int)a.size();
	int j = (int)a[0].size();
	int k = (int)a[0][0].size();
	int l = (int)a[0][0][0].size();

	for (int p = 0; p < i; p++){
		for (int q = 0; q < j; q++){
			c[p][q] = 0;
			for (int r = 0; r < k; r++){
				for (int s = 0; s < l; s++){
					if (a[p][q][r][s]>-2.){
						c[p][q] += a[p][q][r][s] * b[r][s];
					}
				}
			}
		}
	}
}


void showMat(const mat1& a){
	int l = (int)a.size();
	cout << "[ ";
	for (int i = 0; i <l; i++){
		cout << a[i] << ", ";
	}
	cout << "]"<<endl;
}

void showMat(const mat2& a){
	int l = (int)a.size();
	for (int i = 0; i <l; i++){
		showMat(a[i]);
	}
}