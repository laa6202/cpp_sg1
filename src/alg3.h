/*
 * alg3.h
 *
 *  Created on: 2017��6��5��
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

#endif /* ALG3_H_ */