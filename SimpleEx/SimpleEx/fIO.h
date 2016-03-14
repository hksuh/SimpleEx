#include "indiv.h"
//#include <sstream>
#include <fstream>
//#include <stdio.h>
//#pragma warning(disable:4996)

mat3 txtIn(char* name){
	mat3 testImg(99, mat2(8, mat1(8, 0)));
	/*
	FILE * fp;
	double var;
	int i, j, k;
	fp=fopen("TrainingList.txt", "r");
		i = 0; j = 0; k = 0;
		while(0 < fscanf(fp, "%lf", &var)){
			if (var < 0){
				if (var == -1){ j++; k=0; }
				else{
					if (var == -2){ i++; j = 0; }
				}
			}
			else{
				testImg[i][j][k] = var;
				j++;
			}
		}
		fclose(fp);
	
	*/

	/* Using stream code*/
	cout <<"Read file <"<< name <<">"<< endl;

	ifstream inFile(&name[0u]);
	//char inputstring[100000];
	int i, j, k;

	double var;
	i = 0; j = 0; k = 0;
	while (inFile >> var){
		if (var < 0){
			if (var == -1){ j++; k = 0; }
			else{
				if (var == -2){ i++; j = 0; }
			}
		}
		else{
			testImg[i][j][k] = 1.-var;
			k++;
		}
	}

	//while (!inFile.eof()){
	//	inFile.getline(inputstring, 10000);
	//	ind=inputstring[0]
	//	inFile.getline(inputstring, 100000);
//
	//}

	inFile.close();
	
	return testImg;
}

void txtOut(char* name,indiv obj[],int len){
	mat3 testImg(99, mat2(8, mat1(8, 0)));
	
	/* Using stream code*/
	cout << "Write file <" << name << ">" << endl;

	ofstream outFile(&name[0u]);
	
	for (int i1 = 0; i1 < len; i1++){
		outFile << i1 << endl;
		outFile << obj[i1].score << endl;
		outFile << obj[i1].depth << endl;

		outFile << "{";
		for (int i = 0; i < obj[i1].connect.size(); i++){
			if (i != 0){ outFile << " , "; }
			outFile << "{";
			for (int j = 0; j < obj[i1].connect[i].size(); j++){
				if (j != 0){ outFile << " , "; }
				outFile << "{";
				for (int k = 0; k < obj[i1].connect[i][j].size(); k++){
					if (k != 0){ outFile << " , "; }
					outFile << "{";
					for (int l = 0; l < obj[i1].connect[i][j][k].size(); l++){
						if (l != 0){ outFile << " , "; }
						outFile << "{";
						for (int m = 0; m < obj[i1].connect[i][j][k][l].size(); m++){
							if (m != 0){ outFile << " , "; }
							outFile << obj[i1].connect[i][j][k][l][m];
						}
						outFile << "}";
					}
					outFile << "}";
				}
				outFile << "}";
			}
			outFile << "}";
		}
		outFile << "}" << endl;

		outFile << "{";
		for (int i = 0; i < obj[i1].thsd.size(); i++){
			if (i != 0){ outFile << " , "; }
			outFile << "{";
			for (int j = 0; j < obj[i1].thsd[i].size(); j++){
				if (j != 0){ outFile << " , "; }
				outFile << "{";
				for (int k = 0; k < obj[i1].thsd[i][j].size(); k++){
					if (k != 0){ outFile << " , "; }
					outFile << obj[i1].thsd[i][j][k];
				}
				outFile << "}";
			}
			outFile << "}";
		}
		outFile << "}" << endl;
	}
	outFile.close();
}