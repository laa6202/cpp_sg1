/*
 * tools.h
 *
 *  Created on: 2017��4��16��
 *      Author: Administrator
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int showMatInf(Mat M);

float getSumLine(Mat M,int lineNo);
float getSumAll(Mat M);
int checkLineWhite(Mat C, int y,int x,int len,int & whiteOrNot);
int bubbleSort(int res[],int index[],int src[],int num);
int showPxLinePixel(Mat M,int px,int pyFoot,int channel=0);

uchar myMax(uchar a,uchar b);
uchar myMin(uchar a,uchar b);

#endif /* TOOLS_H_ */
