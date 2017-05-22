/*
 * alg2.cpp
 *
 *  Created on: 2017Äê5ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "alg.h"
#include "alg2.h"
#include "imgCheck.h"
#include "tools.h"


int getBackFn2(String & fn0){
	//fn0 = "t8/Mon May 22 16-37-00.bmp";
	//fn0 = "t8/Mon May 22 16-37-01.bmp";
	fn0 = "t8/Mon May 22 16-41-07.png";
	cout << "...get back file:" << fn0 <<endl;
	return 0;
}

int getFontFn2(String & fn0){
	fn0 = "t8/Mon May 22 16-40-33.png";
	//fn0 = "t8/Mon May 22 16-42-01.png";
	cout << "...get font file:" << fn0 <<endl;
	return 0;
}


int getLeg2(Mat C, int pxLeg[], int num){
	for(int i=0;i<num;i++)
		pxLeg[i] = C.cols /(num+1) * (i+1);

	return 0;
}


int searchDown2(Mat C, int pxLeg[], int th_down,int & py,int num){
	int pyDown[num];
	int sum =0;
	for(int i=0;i<num ;i++){
		pyDown[i] = 0;
		searchDown(C,pxLeg[i],150,pyDown[i]);
		//cout << "pyDown["<< i << "] = " <<pyDown[i] << endl;
		sum += pyDown[i];
	}
	py = sum/num;
	return 0;
}


int drawDLine(Mat &D , int pxLeg[],int pyDown,int pyUp,int num){
	for(int i=0;i<num;i++){
		line(D, Point(pxLeg[i],100), Point(pxLeg[i],D.rows-100), Scalar(255,0,0), 1);
	}


	line(D, Point(40,pyDown), Point(D.cols-40,pyDown), Scalar(255,0,0), 1);
	//line(D, Point(40,pyUp), Point(D.cols-40,pyUp), Scalar(255,0,0), 1);
}
