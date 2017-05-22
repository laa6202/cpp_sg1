//============================================================================
// Name        : TC1.cpp
// Author      : alu
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "alg.h"
#include "imgCheck.h"

using namespace std;
using namespace cv;

//String fn0 = "t5/31_br103_con125_st110.jpg";

int main1() {
	cout << "!!!Hello SG1!!!" << endl; // prints !!!Hello World!!!

	String fn0,fn1;
	getBackFn(fn0);
	getFontFn(fn1);

	Mat Ab,Af;
	if(loadImg(Ab,fn0))	exit(-2);
	if(loadImg(Af,fn1)) exit(-2);

	Mat Bf0,Bf;
	int bline = 10; //para : blance line for judge
	blanceAf(Ab,Af,Bf0,bline);
	blanceAf(Ab,Bf0,Bf,bline);

	Mat C;
	int th_xor = 0;	//thershold of xor image
	xorImg(Ab,Bf,C,th_xor);

	int pleft,pright;
	//searchLeft(C,pleft,800);
	//searchRight(C,pright,300);
	searchLeft2(C,pleft,3);		//ratio = th / max
	searchRight2(C,pright,6);	//ratio = th / max

	int pxLeg = getLeg(C, pleft, pright);
	int lenShoe = pright - pleft;
	int pyDown,pyUp;
	searchDown(C,pxLeg,150,pyDown);
	if(searchUp2(C,pxLeg,pyDown,lenShoe,pyUp))
		searchUp(C,pxLeg,pyDown,lenShoe,pyUp);

	Mat D = C.clone();
	line(D, Point(pleft,200), Point(pleft,450), Scalar(255,0,0), 1);
	line(D, Point(pright,200), Point(pright,450), Scalar(255,0,0), 1);
	line(D, Point(pxLeg,100), Point(pxLeg,450), Scalar(255,0,0), 1);
	line(D, Point(40,pyDown), Point(600,pyDown), Scalar(255,0,0), 1);
	line(D, Point(40,pyUp), Point(600,pyUp), Scalar(255,0,0), 1);

	imshow("main1",D);
	while(1){
		uchar key =  waitKey(50);
		if(key == 'q')
			break;
	}

	imwrite("D.jpg",D);

	return 0;

}


int main(){
	main1();
}





