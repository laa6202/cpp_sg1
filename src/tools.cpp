/*
 * tools.cpp
 *
 *  Created on: 2017Äê4ÔÂ16ÈÕ
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



int bubbleSort(int res[],int index[],int src[],int num){
	for(int i=0;i<num;i++){
		res[i] = src[i];
		index[i] = i;
	}

	int temp;
	for(int i=0;i<num-1;i++){
		for(int j=0;j<num-1;j++){
			if(res[j] > res[j+1]){
				temp = res[j];
				res[j] = res[j+1];
				res[j+1] = temp;
				temp = index[j];
				index[j] = index[j+1];
				index[j+1] = temp;
			}
		}
	}


	return 0;
}
