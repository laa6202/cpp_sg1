/*
 * tools.cpp
 *
 *  Created on: 2017��4��16��
 *      Author: Administrator
 */

#include "tools.h"


int showMatInf(Mat M){
	if(M.empty()){
		cout << "Mat is empty" << endl;
		return -2;
	}
	int height = M.rows;
	int width = M.cols;
	int channel = M.channels();
	cout << endl;
	cout << "channel = "<< channel <<"\theight = " << height << "\twidth = " << width <<endl;
	return 0;
}

float getSumLine(Mat M,int lineNo){
	float sum = 0.0;
	uchar *dp = M.ptr<uchar>(lineNo);
	for(int i=0;i<M.cols;i++){
		sum += dp[i];
	}
	return sum;
}



int checkLineWhite(Mat C, int y,int x,int len,int & isWhite){
	isWhite = 0;
	for(int i=y;i<y+len;i++){
		if(C.at<uchar>(i,x) == 255){
			isWhite = 1;
			break;
		}
	}

	return 0;
}
