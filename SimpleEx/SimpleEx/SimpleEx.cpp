// SimpleEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fIO.h"
#include "iostream"




int superSimple(){

	const int len = 4;

	vector<>
	
	for (int i = 0; i<len; i++){
		being[i].getScore(layer, trainInput);
		cout << i << "score: " << being[i].score << endl;
	}

	int alter = 100;
	int from, to;
	double foot = 0.5;
	while (alter>0){
		for (int i = 0; i<len; i++){
			being[i].copy(nbeing[i]);
		}
		while (alter > 0){
			alter--;
			if (alter % 100 == 0){ cout << ">>>>>>>>>>>>>>>>>" << (alter / 100) << endl; }
			for (int i = 0; i < len; i++){
				nbeing[i].perturb(foot);
				nbeing[i].getScore(layer, trainInput);
				if (nbeing[i].score < being[i].score){
					nbeing[i].copy(being[i]);
					cout << i << "score: " << being[i].score << endl;
				}
			}
		}
		for (int i = 0; i < len; i++){
			nbeing[i].perturb(foot);
			nbeing[i].getScore(layer, trainInput);
			if (nbeing[i].score < being[i].score){
				nbeing[i].copy(being[i]);
				cout << i << "score: " << being[i].score << endl;
			}
		}
		cout << "step number: ";
		cin >> alter;
		if (alter == -5){
			cout << "=========copy_mode=========" << endl;
			cout << "from:";
			cin >> from;
			cout << "to:";
			cin >> to;
			being[from].copy(being[to]);
			cout << "step number: ";
			cin >> alter;
		}
		cout << "foot size: ";
		cin >> foot;
	}

	txtOut("out.txt", being, len);

	return 0;
}


int test(){
	/*
	mat4 qwer(2, mat3(2, mat2(2, mat1(2, 1.))));
	mat2 asdf(2, mat1(2, 1.));
	mat2 as(2, mat1(2, 1.));

	product(qwer, asdf,as);

	showMat(as);
	*/


	/* time measure kit
	clock_t time_a = clock();
	clock_t time_b = clock();
	cout << "a to b: " << ((double)(time_b - time_a)) / CLOCKS_PER_SEC << endl;
	cout << "b to c: " << ((double)(time_c - time_b)) / CLOCKS_PER_SEC << endl;
	*/
	srand((unsigned int)time(NULL));

	vector<mat2> layer;
	layer.reserve(6);
	//layer.push_back(mat2(8, mat1(8, 0.)));
	//layer.push_back(mat2(16, mat1(16, 0.)));
	//layer.push_back(mat2(16, mat1(16, 0.)));
	layer.push_back(mat2(8, mat1(8, 0.)));
	layer.push_back(mat2(8, mat1(8, 0.)));
	layer.push_back(mat2(4, mat1(4, 0.)));
	layer.push_back(mat2(4, mat1(4, 0.)));
	layer.push_back(mat2(2, mat1(2, 0.)));
	layer.push_back(mat2(2, mat1(2, 0.)));
	layer.push_back(mat2(1, mat1(1, 0.)));


	mat3 trainInput=txtIn("TrainingList.txt");

	int v;
	indiv being = indiv();
	for (int aw = 0; aw < 10; aw++){
		being.newRand();
//		being.show();
		for (int rai = 0; rai < 99; rai++){
			layer[0] = trainInput[rai];
			being.propagate(layer);
		}
		showMat(layer[6]);
		//cin>>v;
	}
	//clock_t time_c = clock();
	//showMat(being.thsd[0]);

	return 0;
}


int _tmain(int argc, _TCHAR* argv[]){
	srand((unsigned int)time(NULL));

	return 0;

	vector<mat2> layer;
	layer.reserve(7);
	//layer.push_back(mat2(8, mat1(8, 0.)));
	//layer.push_back(mat2(16, mat1(16, 0.)));
	//layer.push_back(mat2(16, mat1(16, 0.)));
	layer.push_back(mat2(8, mat1(8, 0.)));
	layer.push_back(mat2(8, mat1(8, 0.)));
	layer.push_back(mat2(4, mat1(4, 0.)));
	layer.push_back(mat2(4, mat1(4, 0.)));
	layer.push_back(mat2(2, mat1(2, 0.)));
	layer.push_back(mat2(2, mat1(2, 0.)));
	layer.push_back(mat2(1, mat1(1, 0.)));


	mat3 trainInput = txtIn("TrainingList.txt");
	
	const int len = 16;

	indiv being[len];
	indiv nbeing[len];
	for (int i = 0; i<len; i++){
		being[i].getScore(layer,trainInput);
		cout << i << "score: " << being[i].score << endl;
	}

	int alter=100;
	int from, to;
	double foot = 0.5;
	while (alter>0){
		for (int i = 0; i<len; i++){
			being[i].copy(nbeing[i]);
		}
		while (alter > 0){
			alter--;
			if (alter % 100 == 0){ cout <<">>>>>>>>>>>>>>>>>"<< (alter / 100)<<endl; }
			for (int i = 0; i < len; i++){
				nbeing[i].perturb(foot);
				nbeing[i].getScore(layer, trainInput);
				if (nbeing[i].score < being[i].score){
					nbeing[i].copy(being[i]);
					cout << i << "score: " << being[i].score << endl;
				}
			}
		}
		for (int i = 0; i < len; i++){
			nbeing[i].perturb(foot);
			nbeing[i].getScore(layer, trainInput);
			if (nbeing[i].score < being[i].score){
				nbeing[i].copy(being[i]);
				cout << i << "score: " << being[i].score << endl;
			}
		}
		cout << "step number: ";
		cin >> alter;
		if (alter == -5){
			cout << "=========copy_mode=========" << endl;
			cout << "from:";
			cin >> from;
			cout << "to:";
			cin >> to;
			being[from].copy(being[to]);
			cout << "step number: ";
			cin >> alter;
		}
		cout << "foot size: ";
		cin >> foot;
	}
	
	txtOut("out.txt", being, len);

	return 0;
}