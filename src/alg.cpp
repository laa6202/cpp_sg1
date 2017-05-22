//alg.cpp

#include "alg.h"
#include "imgCheck.h"
#include "tools.h"



int getBackFn(String & fn0){
	//fn0 = "t5/31_br103_con125_st110.jpg";
	//fn0 = "t3/37_br98_con165_st110.jpg";
	fn0 = "t5/31_br103_con125_st110.jpg";
	cout << "...get back file:" << fn0 <<endl;
	return 0;
}

int getFontFn(String & fn0){
	//fn0 = "t5/30_br103_con125_st110.jpg";
	//fn0 = "t3/30_br98_con165_st185.jpg";
	fn0 = "t7/44_br128_con130_st125.jpg";
	cout << "...get font file:" << fn0 <<endl;
	return 0;
}

int loadImg(Mat &A,String fn){
	Mat A0;
	A0 = imread(fn,0);
	if(A0.empty()){
		cout << "fn = " << fn << " load failed!" << endl;
		return -2;
	}
	A0.convertTo(A,CV_8UC1);
	int height = A.size().height;
	int width  = A.size().width;
	cout << "...loadImg: "<<fn <<" done.\t height = " << height <<"\t";
	cout << "width = " << width << endl;
	return 0;
}

float blanceAf(Mat Ab,Mat Af,Mat & Bf,int blines){
	int height = Ab.size().height;
//	int width  = Ab.size().width;
	Mat Ablow = Ab.rowRange(height-blines,height);
	Mat Aflow = Af.rowRange(height-blines,height);

	float sumLineAb[blines];
	float sumLineAf[blines];
	float sumAb=0.0,sumAf=0.0;
	float bRatio;	//blance ration = Ab / Af;
	for (int i=0;i<blines;i++){
		sumLineAb[i] = getSumLine(Ablow,i);
		sumLineAf[i] = getSumLine(Aflow,i);
		sumAb += sumLineAb[i];
		sumAf += sumLineAf[i];
		//cout << "Ab : sum of line " << i << " = " << sumLineAb[i] << endl;
		//cout << "Af : sum of line " << i << " = " << sumLineAf[i] << endl;
	}
	bRatio = sumAb / sumAf;
//	cout << "sumAb = " <<sumAb << "\tsumAf = " << sumAf << "\tbRatio = " <<bRatio<<endl;

	Bf = Af.clone() * bRatio;
	cout << "...blanceAf for Bf done." << "\t";
	cout << "blance ratio (Ab/Af) = " << bRatio << endl;
	return bRatio;
}


int xorImg(Mat Ab,Mat Bf,Mat & C, int thershold){
	C =   Bf - Bf;
	for(int i =0;i<C.rows;i++){
		uchar *ptrAb = Ab.ptr<uchar>(i);
		uchar *ptrBf = Bf.ptr<uchar>(i);
		uchar *ptrC  = C.ptr<uchar>(i);
		for(int j=0;j<C.cols;j++){
			if(ptrAb[j] >= ptrBf[j])
				ptrC[j] = ptrAb[j] -  ptrBf[j];
			else
				ptrC[j] = ptrBf[j] -  ptrAb[j];
		}
		for(int j=0;j<C.cols;j++){
			if(ptrC[j] < thershold)
				ptrC[j] = 0;
		}
	}

	return 0;
}



int searchLeft(Mat C, int & px,int th_diff){
	int sumHigh[C.cols/2];
	int sum;
	for(int i=0;i<C.cols/2;i++){
		sum =0;
		for(int j=0;j<C.rows;j++){
			sum += C.at<uchar>(j,i);
		}
		sumHigh[i] = sum;
	}

	int max =0;
	int diff;
	px=0;
	for(int i=0;i<C.cols/2-1;i++){
		diff = abs(sumHigh[i] - sumHigh[i+1]);
		//cout << "diff ["<< i<<"]= " << diff <<endl;
		max = (diff >= max) ? diff : max;
		if(px==0)
			px  = (diff >= th_diff) ? i : px;
	}
	cout << "...Search Left :\t max left diff = " << max << " \t";
	cout << "th_left = " << th_diff << " \t";
	cout << "point of left = " << px << endl;
	return 0;
}



int searchRight(Mat C, int & px,int th_diff){
	int sumHigh[C.cols/2];
	int sum;
	for(int i=0;i<C.cols/2;i++){
		sum =0;
		for(int j=0;j<C.rows;j++){
			sum += C.at<uchar>(j,i+C.cols/2);
		}
		sumHigh[i] = sum;
	}

	int max =0;
	int diff;
	px=0;
	for(int i=C.cols/2-1;i>=1;i--){
		diff = abs(sumHigh[i] - sumHigh[i-1]);
		//cout << "diff ["<< i<<"]= " << diff <<endl;
		max = (diff >= max) ? diff : max;
		if(px==0)
			px  = (diff >= th_diff) ? i : px;
	}
	px = px + C.cols/2;
	cout << "...Search Right : \t max right diff = " << max << " \t";
	cout << "th_right = " << th_diff << " \t";
	cout << "point of right = " << px << endl;
	return 0;
}


int searchLeft2(Mat C, int & px,int ratio){
	int sumHigh[C.cols/2];
	int sum;
	for(int i=0;i<C.cols/2;i++){
		sum =0;
		for(int j=0;j<C.rows;j++){
			sum += C.at<uchar>(j,i);
		}
		sumHigh[i] = sum;
	}

	int max =0;
	int diff;
	px=0;
	for(int i=0;i<C.cols/2-1;i++){
		diff = abs(sumHigh[i] - sumHigh[i+1]);
		//cout << "diff ["<< i<<"]= " << diff <<endl;
		max = (diff >= max) ? diff : max;
	}
	int th_diff = max / ratio;
	for(int i=0;i<C.cols/2-1;i++){
		diff = abs(sumHigh[i] - sumHigh[i+1]);
		if(px==0)
			px  = (diff >= th_diff) ? i : px;
	}


	cout << "...Search Left :\t max left diff = " << max << " \t";
	cout << "th_left = " << th_diff << " \t";
	cout << "point of left = " << px << endl;
	return 0;
}



int searchRight2(Mat C, int & px,int ratio){
	int sumHigh[C.cols/2];
	int sum;
	for(int i=0;i<C.cols/2;i++){
		sum =0;
		for(int j=0;j<C.rows;j++){
			sum += C.at<uchar>(j,i+C.cols/2);
		}
		sumHigh[i] = sum;
	}

	int max =0;
	int diff;
	px=0;
	for(int i=C.cols/2-1;i>=1;i--){
		diff = abs(sumHigh[i] - sumHigh[i-1]);
		//cout << "diff ["<< i<<"]= " << diff <<endl;
		max = (diff >= max) ? diff : max;
	}
	int th_diff = max / ratio;
	for(int i=C.cols/2-1;i>=1;i--){
		diff = abs(sumHigh[i] - sumHigh[i-1]);
		if(px==0)
			px  = (diff >= th_diff) ? i : px;
	}

	px = px + C.cols/2;
	cout << "...Search Right : \t max right diff = " << max << " \t";
	cout << "th_right = " << th_diff << " \t";
	cout << "point of right = " << px << endl;
	return 0;
}




int getLeg(Mat C, int pxLeft,int pxRight){
	int len_shoe = pxRight - pxLeft;
	int pxLeg = pxLeft + len_shoe / 4;
	cout << "...length of shoe = "<<len_shoe<< " \t";
	cout << "point of Leg = " << pxLeg << endl;
	return pxLeg;
}


int searchDown(Mat C, int pxLeg, int th_down,int &py){
	for(int i=C.rows-1;i>=300;i--){
		//cout << "point ["<< i<<"]= " << C.at<uchar>(i,pxLeg)+0.0 <<endl;
		if(py == 0){
			py = (C.at<uchar>(i,pxLeg) >= th_down) ? i: py;
		}
	}
	cout << "...Search Down : \t th_down = " << th_down << " \t";
	cout << "py_down = " << py <<endl;

	return 0;
}



int searchUp(Mat C, int pxLeg, int pyDown,int lenShoe,int & py){
	py = pyDown -  lenShoe / 12;
	cout << "...Search UP : \t lenShoe = " << lenShoe << " \t";
	cout << "py_up = " << py <<endl;
	return 0;
}



int searchUp2(Mat C, int pxLeg, int pyDown,int lenShoe,int &py){
	py = 0;
	int th_diff = 10;
	for(int i=pyDown-10;i>=pyDown - 100;i--){
		uchar now = C.at<uchar>(i,pxLeg);
		uchar up = C.at<uchar>(i-1,pxLeg);
		uchar down = C.at<uchar>(i+1,pxLeg);
		//cout << "point [" << i << "] = " << now + 0.0 << endl;
		if(py == 0){
			if((now > up + th_diff) & (now > down + th_diff))
				py = i;
		}
	}
	if(py == 0){
		cout << "...Search UP 2 failed. \t to do Search UP 1"<<endl;
		return -1;
	}

	cout << "...Search UP 2 : \t lenShoe = " << lenShoe << " \t";
	cout << "py_up = " << py <<endl;
	return 0;
}




