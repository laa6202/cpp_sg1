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

	//fn0 = "t8/Mon May 22 16-41-07.png";
	//fn0 = "t8/Mon May 22 16-41-07.png";
	fn0 = "t9/Tue May 23 16-49-54.png";
	cout << "...get back file:" << fn0 <<endl;
	return 0;
}

int getFontFn2(String & fn0){
	//fn0 = "t8/Mon May 22 16-40-33.png";
	//fn0 = "t8/Mon May 22 16-42-01.png";
	//fn0 = "t9/Tue May 23 16-49-48.png";
	//fn0 = "t9/Tue May 23 17-28-40.png";
	//fn0 = "t9/Tue May 23 17-32-09.png";
	//fn0 = "t9/Tue May 23 16-55-16.png";
	//fn0 = "t9/Tue May 23 17-43-39.png";
	//fn0 = "t9/Tue May 23 17-50-18.png";
	fn0 = "t9/Tue May 23 17-55-50.png";
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
	for(int i=0;i<num ;i++){
		pyDown[i] = 0;
		searchDownCore(C,pxLeg[i],th_down,pyDown[i]);
		//cout << "pyDown["<< i << "] = " <<pyDown[i] << endl;
	}

	int diff[num];
	int num_val = 0;
	int sum_pyDown =0;
	for(int i=0;i<num-1;i++){
		diff[i] = abs(pyDown[i] - pyDown[i+1]);
		if(diff[i] <= 30){
			num_val ++;
			sum_pyDown += pyDown[i];
//			cout << "pyUp["<<i<<"] = " << pyUp[i] << "\t";
//			cout << "sum = " << sum_pyUp<<endl;
		}
	}
	if(num_val ==0){
		return -1;
	}
//	py = sum_pyDown / num_val;
	py = pyDown[4];
	cout << "...searchDown2 : \t num_val = "<<num_val<<"\t py = " <<py <<endl;
	return 0;
}


int searchDownCore(Mat C, int pxLeg, int th_down, int &py){
	int height = C.rows;
	int diff[height-1];
	int max_diff=0;
	for(int i=0;i<height-4;i++){
		diff[i] = abs(C.at<uchar>(i,pxLeg) - C.at<uchar>(i+3,pxLeg));
		max_diff = (diff[i] > max_diff) ? diff[i] : max_diff;
//		cout << "diff[" << i<<"] = " << diff[i] <<" \t";
//		cout << "C[pxleg]["<<i<<"] = " <<C.at<uchar>(i,pxLeg)+0.0 <<endl;
	}

	int now_th = (th_down <= max_diff*2/3) ?th_down : max_diff*2/3;
	int pyDown = C.rows;
	for(int i=C.rows-10;i>height/2;i--){
		if(pyDown == C.rows){
			pyDown = (diff[i] >= now_th) ? i : pyDown;
		}
	}
	py = pyDown;
	cout << "......searchDownCore : \t max_diff = "<< max_diff <<"\t";
	cout << "th_down = "<< th_down <<"\t now_th = "<< now_th << "\t";
	cout << "pyDown =  "<<pyDown <<endl;
	return 0;
}


int drawDLine(Mat &D , int pxLeg[],int pyDown,int pyUp,int num){
	for(int i=0;i<num;i++){
		line(D, Point(pxLeg[i],100), Point(pxLeg[i],D.rows-100), Scalar(255,0,0), i+0.3);
	}


	line(D, Point(20,pyDown), Point(D.cols-20,pyDown), Scalar(255,0,0), 1);
	line(D, Point(20,pyUp), Point(D.cols-20,pyUp), Scalar(255,0,0), 3);
	return 0;
}






int searchUp3(Mat D, int pxLeg[], int pyDown,int th_up,int & py,int num){

	searchUpCore(D,pxLeg[4],pyDown,th_up,py);
	return 0;
}

int searchUp4(Mat D, int pxLeg[], int pyDown,int th_up,int & py,int num){
	int pyUp[num];
	for(int i=0;i<num;i++){
		pyUp[i]=0;
		searchUpCore(D,pxLeg[i],pyDown,th_up,pyUp[i]);
	}

	int diff[num];
	int num_val = 0;
	int sum_pyUp =0;
	for(int i=0;i<num-1;i++){
		diff[i] = abs(pyUp[i] - pyUp[i+1]);
		if(diff[i] <= 30){
			num_val ++;
			sum_pyUp += pyUp[i];
//			cout << "pyUp["<<i<<"] = " << pyUp[i] << "\t";
//			cout << "sum = " << sum_pyUp<<endl;
		}
	}
	if(num_val ==0){
		return -1;
	}
	//py = sum_pyUp / num_val;
	py = pyUp[3];
	cout << "...searchUp4 : \t num_val = " << num_val <<"\t";
	cout << "py_Up = " << py<<endl;

	return 0;
}


int searchUpCore(Mat D, int pxLeg,int pyDown,int th_up,int &py){
	int height = (pyDown > 50) ? (pyDown - 50) : pyDown;
	int diff[height],max_diff = 0;
	int tmp_py=0;
	for(int i=1;i<height;i++){
		diff[i] = abs(D.at<uchar>(i,pxLeg) - D.at<uchar>(i+5,pxLeg));
		max_diff = (diff[i] >= max_diff) ? diff[i] : max_diff;
//		cout << "diff [" << i <<"] = " << diff[i] <<"\t";
//		cout << "\t D[pxLeg]["<<i<<"] = " <<D.at<uchar>(i,pxLeg)+0.0 <<endl;
	}

	int now_th = (th_up <= max_diff *2/3) ? th_up : max_diff *2/3;
	for(int i=height-1;i>=1;i--){
		if(tmp_py ==0){
			tmp_py = (diff[i] >= now_th) ? i: tmp_py;
			//tmp_py = (diff >= max_diff *2/3) ? i: tmp_py;
		}
	}
	py = tmp_py + 5;
	cout << "......searchUpCore : \t th_up = " << th_up << "\t ";
	cout << "max_diff = " << max_diff << "\t";
	cout << "now_th = " << now_th << "\t";
	cout << "py_up = " << py+0.0 << endl;


	return 0;

}
