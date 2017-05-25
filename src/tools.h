/*
 * tools.h
 *
 *  Created on: 2017Äê4ÔÂ16ÈÕ
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
int checkLineWhite(Mat C, int y,int x,int len,int & whiteOrNot);
int bubbleSort(int res[],int index[],int src[],int num);



#endif /* TOOLS_H_ */
