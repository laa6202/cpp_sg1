/*
 * alg3.h
 *
 *  Created on: 2017Äê6ÔÂ5ÈÕ
 *      Author: Administrator
 */

#ifndef ALG3_H_
#define ALG3_H_

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"
#include "alg.h"
#include "alg2.h"
#include "imgCheck.h"

using namespace std;
using namespace cv;

int loadImg3(Mat & A,String fn,int flag);
int separateImg(Mat &B0,Mat &B1,Mat &B2,Mat &B,Mat A);

int drawYLineCore(Mat &D , int px,int width=1);
int drawYLine(Mat &Z0, Mat &Z1, Mat &Z2, Mat &Z,int px=240,int width=1);
int drawXYCircleCore(Mat &Z,int px,int py,int width=1);
int drawXYCircle(Mat & Z0,Mat &Z1, Mat &Z2, Mat & Z,int px,int py,int width = 1);

int searchPyFoot(Mat R,int &pyFoot,int thPyFoot);

int blanceAll(Mat &C,Mat A,Mat B,int aveGold);
int aveBefor(Mat M,int px,int py,int len,float &aveNoise,int channel=0);
int rmsBefor(Mat M,int px,int py,int len,float aveNoise, float &rmsNoise,int channel=0);
int absBlack(Mat &B, Mat A, int th);
int diffLen(Mat M,int px,int len,int different[],int ch=0);
int searchMask(Mat M, int px,int pyFoot,int thNum,int &pyMask,int ch=0);

#endif /* ALG3_H_ */
