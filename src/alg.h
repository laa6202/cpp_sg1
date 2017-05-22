/*
 * alg.h
 *
 *  Created on: 2017Äê4ÔÂ15ÈÕ
 *      Author: Administrator
 */

#ifndef ALG_H_
#define ALG_H_

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int getBackFn(String & fn0);
int getFontFn(String & fn0);

int loadImg(Mat & A,String fn);

float blanceAf(Mat Ab,Mat Af,Mat & Bf,int blines);

int xorImg(Mat Ab,Mat Bf,Mat & C, int thershold);

int searchLeft(Mat C, int &px, int th_diff);
int searchRight(Mat C, int &px,int th_diff);
int searchLeft2(Mat C, int &px, int ratio);
int searchRight2(Mat C, int &px,int ratio);

int getLeg(Mat C, int pxLeft,int pxRight);
int searchDown(Mat C, int pxLeg, int th_down,int & py);
int searchUp(Mat C, int pxLeg, int pyDown,int lenShoe,int & py);
int searchUp2(Mat C, int pxLeg, int pyDown,int lenShoe,int & py);




#endif /* ALG_H_ */
