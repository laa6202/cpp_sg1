/*
 * alg2.h
 *
 *  Created on: 2017Äê5ÔÂ22ÈÕ
 *      Author: Administrator
 */

#ifndef ALG2_H_
#define ALG2_H_



#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


int getBackFn2(String & fn0);
int getFontFn2(String & fn0);

int getLeg2(Mat C, int pxLeg[], int num);

int searchDown2(Mat C, int pxLeg[], int th_down,int pyDown[],int num);
int selPyDown(int pyDown[],int sel_diff,int &py,int num);
int searchDownCore(Mat C, int pxLeg, int th_down, int &py);
int searchUp3(Mat D, int pxLeg[], int pyDown,int th_up,int & py,int num);
int searchUp4(Mat D, int pxLeg[], int pyDown,int th_up,int pyUp[],int num);
int searchUpCore(Mat D, int pxLeg,int pyDown,int th_up,int &py);


int drawDLine(Mat &D , int pxLeg[],int pyFoot,int pyHead,int num);
int drawDCircle(Mat &D, int pxLeg[],int pyDown[],int pyUp[],int num);

#endif /* ALG2_H_ */
