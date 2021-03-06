/*
 * alg3.cpp
 *
 *  Created on: 2017��6��5��
 *      Author: Administrator
 */

#include "alg3.h"
#include "tools.h"


int loadImg3(Mat &A,String fn,int flag){
	Mat A0;
	A0 = imread(fn,flag);
	if(A0.empty()){
		cout << "fn = " << fn << " load failed!" << endl;
		return -2;
	}
	//A0.convertTo(A,CV_8UC1);
	A = A0.clone();
	int height = A.size().height;
	int width  = A.size().width;
	cout << "...loadImg3: \t"<<fn <<" done.\t height = " << height <<"\t";
	cout << "width = " << width << endl;
	return 0;
}



int separateImg(Mat &B0,Mat &B1,Mat &B2,Mat &B,Mat A){
	B0 = A.clone();
	B1 = A.clone();
	B2 = A.clone();
	cvtColor(A,B,CV_BGR2GRAY);
	for(int i=0;i<A.rows;i++){
		for(int j=0;j<A.cols;j++){
			B0.at<Vec3b>(i,j)[1] = 0;
			B0.at<Vec3b>(i,j)[2] = 0;
			B1.at<Vec3b>(i,j)[0] = 0;
			B1.at<Vec3b>(i,j)[2] = 0;
			B2.at<Vec3b>(i,j)[1] = 0;
			B2.at<Vec3b>(i,j)[0] = 0;
		}
	}
	cout << "...separateImg : \t finish." << endl;
	return 0;
}


int drawYLineCore(Mat &D , int px,int width){
	line(D, Point(px,20), Point(px,D.rows-20), Scalar(255,255,255), width);
	return 0;
}



int drawYLine(Mat &Z0, Mat &Z1, Mat &Z2, Mat &Z,int px,int width){
	drawYLineCore(Z0,px,width);
	drawYLineCore(Z1,px,width);
	drawYLineCore(Z2,px,width);
	drawYLineCore(Z,px,width);
	return 0;
}



int drawXYCircleCore(Mat &Z,int px,int py,int width){
	circle(Z,Point(px,py),15,Scalar(255,255,255),width);
	return 0;
}


int drawXYCircle(Mat & Z0,Mat &Z1, Mat &Z2, Mat & Z,int px,int py,int width){
	drawXYCircleCore(Z0,px,py,width);
	drawXYCircleCore(Z1,px,py,width);
	drawXYCircleCore(Z2,px,py,width);
	drawXYCircleCore(Z,px,py,width);
	return 0;
}


int searchPyFoot(Mat R,int &pyFoot,int thPyFoot){
	int minPixel = 255, minIndex = 640;
	int nowPixel;
	for(int i=20;i<100;i++){
		nowPixel = R.at<uchar>(R.rows-i,240);
		minIndex = (nowPixel < minPixel) ? (R.rows-i) : minIndex;
		minPixel = (nowPixel < minPixel) ? nowPixel : minPixel;
		//cout << "R[240]["<< R.rows-i << "] = " << R.at<uchar>(R.rows-i,240)+0.0 <<endl;
	}
	pyFoot = minIndex;
	cout << "...searchPyFoot : \t pyFoot = " << minIndex+0.0 << "\tminPixel = "<< minPixel+0.0 << endl;
	return 0;
}



int blanceAll(Mat &C,Mat A,Mat B,int aveGold){
	float sumB = getSumAll(B);
	float aveB = sumB / B.cols / B.rows;
	float aveRatio = aveGold / aveB;
	cout << "...blanceAll :\t aveB = " << aveB << "\t aveRatio =  " << aveRatio << "\t";
	cout << "aveGold = " << aveGold << endl;
	C = A * aveRatio ;

	Mat D;
	cvtColor(C,D,CV_BGR2GRAY);
	float sumD = getSumAll(D);
	float aveD = sumD / D.cols / D.rows;
	cout << "......aveC = " << aveD << endl;
	return 0;
}



int aveBefor(Mat M,int px,int py,int len,float &aveNoise,int channel){
	int sum = 0;

	for(int i=py;i<py+len;i++){
		if(M.channels() == 3)
			sum += M.at<Vec3b>(i,px)[channel];
		else
			sum += M.at<uchar>(i,px);
	}
	aveNoise = (sum+0.0) / len;

	return 0;
}




int rmsBefor(Mat M,int px,int py,int len,float aveNoise,float &rmsNoise,int channel){
	float sumDiff =0;
	float diff=0;
	for(int i=py;i<py+len;i++){
		if(M.channels() == 3){
			diff = M.at<Vec3b>(i,px)[channel] - aveNoise;
			//sumDiff += (diff * diff);
			sumDiff += abs(diff) ;
		}
		else{
			diff = M.at<uchar>(i,px) - aveNoise;
			//sumDiff += diff * diff;
			sumDiff += abs(diff);
		}
	}
	//rmsNoise = sqrt(sumDiff) / len;
	rmsNoise = sumDiff / len;

	return 0;
}


int absBlack(Mat &B, Mat A, int th){
	B = A.clone();
	for(int i=0;i<A.rows;i++)
		for(int j=0;j<A.cols;j++){
			if(A.channels() == 3){
				B.at<Vec3b>(i,j)[0] = (A.at<Vec3b>(i,j)[0] >= th) ? 255:0;
				B.at<Vec3b>(i,j)[1] = (A.at<Vec3b>(i,j)[1] >= th) ? 255:0;
				B.at<Vec3b>(i,j)[2] = (A.at<Vec3b>(i,j)[2] >= th) ? 255:0;
			}
			else {
				B.at<uchar>(i,j) = (A.at<uchar>(i,j) >= th) ? 255:0;
			}
		}
	return 0;
}



int diffLen(Mat M,int px,int len,int different[],int ch){
	int now;
	for(int i=0;i<M.rows;i++){
		now = M.at<Vec3b>(i,px)[ch];
		different[i] = now;
	}
	for(int i=20;i<M.rows-20;i++){
		different[i] = abs(M.at<Vec3b>(i,px)[ch] - M.at<Vec3b>(i+len,px)[ch]);
	}
	return 0;
}



int searchMask(Mat M, int px,int pyFoot,int thNum,int &pyMask,int ch){
	int sumHit = 0;
	for(int i=0;i<pyFoot-50;i++){
		int now = M.at<Vec3b>(pyFoot-50-i,px)[ch];
		if(now == 255)
			sumHit++;
		else
			sumHit = 0;
		if(sumHit >= thNum){
			pyMask = pyFoot-50-i + thNum;
			break;
		}
	}
	cout << "...searchMask : \t pyMask = " << pyMask <<endl;
	return 0;
}
