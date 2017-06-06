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
#include "alg2.h"
#include "alg3.h"
#include "tools.h"
#include "imgCheck.h"

using namespace std;
using namespace cv;


int save_file = 0;
	//String fr0 = "t11/Sat Jun 03 15-32-54.png";	//No shoe
//String fn0 = "t11/Sat Jun 03 15-41-34.png";
//String fn0 = "t11/Sat Jun 03 15-41-56.png";
//String fn0 = "t11/Sat Jun 03 15-42-22.png";
//String fn0 = "t11/Sat Jun 03 15-44-02.png";
	String fr0 = "t11/Sat Jun 03 15-44-21.png";	//No shoe
//String fn0 = "t11/Sat Jun 03 15-45-49.png";
//String fn0 = "t11/Sat Jun 03 15-46-08.png";
//String fn0 = "t11/Sat Jun 03 15-47-07.png";
	//String fr1 = "t11/Sat Jun 03 15-48-29.png";	//ruler
//String fn0 = "t11/Sat Jun 03 15-49-28.png";
//String fn0 = "t11/Sat Jun 03 15-49-50.png";
String fn0 = "t11/Sat Jun 03 15-50-06.png";


int main1() {
	cout << "!!!Hello SG1  alg1!!!" << endl; // prints !!!Hello World!!!

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


int main2(){
	cout << "!!!Hello SG1  alg2!!!" << endl; // prints !!!Hello World!!!
	int save_file = 0;
	int num = 9;
	int bline = 10; //para : blance line for judge
	int th_xor = 50;	//thershold of xor image
	int mask_width = 20;	//pix width of py mask
	int th_down = 150;
	int th_up = 150;
	int sel_diff =20;
	float pix_cm_ratio =  0.01428;
	int searchRange = 500;
	float forceRatio = 4.0;

//--------- step ----------
	String fn0,fn1;
	getBackFn2(fn0);
	getFontFn2(fn1);

	Mat Ab,Af;
	if(loadImg(Ab,fn0))	exit(-2);
	if(loadImg(Af,fn1)) exit(-2);

	Mat Bf0,Bf;

	blanceAf(Ab,Af,Bf0,bline);
	blanceAf(Ab,Bf0,Bf,bline);

	Mat C;
	xorImg2(Ab,Bf,C,th_xor);
	int pyMask[C.cols];
	int max_pyMask;
	getUpMask(C,pyMask,mask_width,max_pyMask);


	int pxLeg[num];
	getLeg2(C,pxLeg,num);

	int pyDown[num],pyUp[num];
	int pyFoot=0, pyHead=0;

	searchDown2(C,pxLeg,th_down,pyDown,num);
	selPyDown(pyDown,sel_diff,pyFoot,num);


	Mat D = Af.clone();
	searchUp4(D,pxLeg,pyFoot,th_up,pyUp,num,max_pyMask);
	//selPyUp(pyUp,sel_diff,pyHead,num);
	selPyUp2(pyUp,sel_diff,pyHead,num);
	modifyPyHead(pyHead,pyFoot,max_pyMask,searchRange,forceRatio);

	drawDCircle(D,pxLeg,pyDown,pyUp,num);
	drawDLine(D , pxLeg,pyFoot,pyHead,num);

	int pix_shoe_height =pyFoot -  pyHead;
	float cm_shoe_height = pix_shoe_height * pix_cm_ratio;
	cout << "...result : \t pix_shoe_height = " << pix_shoe_height << "\t";
	cout << "CM shoe height = "<<cm_shoe_height << endl;

	imshow("main2",D);
	while(1){
		uchar key =  waitKey(50);
		if(key == 'q')
			break;
	}

	if(save_file == 1){
		imwrite("Ab.jpg",Ab);
		imwrite("Af.jpg",Af);
		imwrite("Bf0.jpg",Bf0);
		imwrite("Bf.jpg",Bf);
		imwrite("C.jpg",C);
		imwrite("D.jpg",D);
	}
	return 0;
}



int main3(){
	cout << "--- SG1 main3 ---" << endl;

	int pyFoot = 578;
	int aveGold = 230;

//----------- search FOOT --------
	Mat R;
	if(loadImg3(R,fr0,0)) exit(-2);

	searchPyFoot(R,pyFoot,20);
	cout <<endl;

//------------ main ----------
	Mat A;
	if(loadImg3(A,fn0,1))	exit(-2);

	Mat B;
	cvtColor(A,B,CV_BGR2GRAY);

	Mat C;
	blanceAll(C,A,B,aveGold);


	Mat D0,D1,D2,D;
	separateImg(D0,D1,D2,D,C);
	showPxLinePixel(D1,240,pyFoot,1);


//----------- draw line for debug ---------
	Mat Z0,Z1,Z2,Z;
	Z0 = D0.clone();
	Z1 = D1.clone();
	Z2 = D2.clone();
	Z  = D.clone();
	drawYLine(Z0,Z1,Z2,Z);
	drawXYCircle(Z0,Z1,Z2,Z,Z.cols/2,pyFoot,2);
	drawXYCircle(Z0,Z1,Z2,Z,Z.cols/2,454,2);

	//drawXYCircleCore(R,240,pyFoot,3);



//----------- show and save --------
	imshow("main3",Z1);
	while(1){
		uchar key =  waitKey(50);
		if(key == 'q')
			break;
	}

	if(save_file == 1){
		imwrite("R.jpg",R);
		imwrite("A.jpg",A);
		imwrite("B0.jpg",Z0);
		imwrite("B1.jpg",Z1);
		imwrite("B2.jpg",Z2);
		imwrite("B.jpg",Z);

	//	imwrite("Bf0.jpg",Bf0);
	//	imwrite("Bf.jpg",Bf);
	//	imwrite("C.jpg",C);
	//	imwrite("D.jpg",D);
	}


	cout << "--- end ---" << endl;
	return 0;
}


int main(){
	main3();
	return 0;
}





