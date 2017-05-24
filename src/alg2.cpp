/*
 * alg2.cpp
 *
 *  Created on: 2017Äê5ÔÂ22ÈÕ
 *      Author: Administrator
 */

#include "alg.h"
#include "alg2.h"
#include "imgCheck.h"
#include "tools.h"


int getBackFn2(String & fn0){

	//fn0 = "t8/Mon May 22 16-41-07.png";
	//fn0 = "t8/Mon May 22 16-41-07.png";
	fn0 = "t9/Tue May 23 16-49-54.png";
	cout << "...get back file:" << fn0 <<endl;
	return 0;
}

int getFontFn2(String & fn0){
	//fn0 = "t8/Mon May 22 16-40-33.png";
	//fn0 = "t8/Mon May 22 16-42-01.png";
	//fn0 = "t9/Tue May 23 16-49-48.png";
	//fn0 = "t9/Tue May 23 17-28-40.png";
	//fn0 = "t9/Tue May 23 17-32-09.png";
	//fn0 = "t9/Tue May 23 16-55-16.png";			//head
	//fn0 = "t9/Tue May 23 17-43-39.png";
	//fn0 = "t9/Tue May 23 17-50-18.png";		//error
	fn0 = "t9/Tue May 23 17-55-50.png";
	cout << "...get font file:" << fn0 <<endl;
	return 0;
}


int getLeg2(Mat C, int pxLeg[], int num){
	for(int i=0;i<num;i++)
		pxLeg[i] = C.cols /(num+1) * (i+1);

	return 0;
}


int searchDown2(Mat C, int pxLeg[], int th_down,int pyDown[],int num){
	for(int i=0;i<num ;i++){
		pyDown[i] = 0;
		searchDownCore(C,pxLeg[i],th_down,pyDown[i]);
		//cout << "pyDown["<< i << "] = " <<pyDown[i] << endl;
	}


	return 0;
}


int selPyDown(int pyDown[],int sel_diff,int &py,int num){
	int max_py = 0;
	int max_id = -1;
	int sec_py = 0;
	int sec_id = -1;
	int num_val = 0;
	int diff = 0;
	int sum_pyDown =0;

	for(int i=0;i<num;i++){
		max_py = (pyDown[i] >= max_py) ? pyDown[i] : max_py;
		max_id = (pyDown[i] >= max_py) ? i : max_id;
	}
	for(int i=0;i<num;i++){
		if(i!=max_id){
			sec_py = (pyDown[i] >= sec_py) ? pyDown[i] : sec_py;
			sec_id = (pyDown[i] >= sec_py) ? i : sec_id;
		}
	}
	cout << "...selPyDown : \t max_id = "<< max_id << "\t sec_id = " << sec_id <<endl;

	for(int i=0;i<num;i++){
		if(i!= max_id){
			diff = abs(pyDown[i] - pyDown[max_id]);
			if(diff <= sel_diff){
				num_val ++;
				sum_pyDown += pyDown[i];
			}
		}
	}
	if(num_val != 0){
		num_val ++;
		sum_pyDown += max_py;
		py = sum_pyDown / num_val;
		cout << "\t num_val = "<<num_val<<"\t py = " <<py <<endl;
		return 0;
	}



	if(num_val ==0){
		py = pyDown[1];
		cout << "\t num_val = "<<num_val<<"\t py = " <<py <<endl;
		return -1;
	}

//	py = pyDown[4];


	return 0;
}


int searchDownCore(Mat C, int pxLeg, int th_down, int &py){
	int height = C.rows;
	int diff[height-1];
	int max_diff=0;
	for(int i=0;i<height-1;i++){
		diff[i] = 0;
	}

	for(int i=C.rows/2;i<height-10;i++){
		diff[i] = abs(C.at<uchar>(i,pxLeg) - C.at<uchar>(i+10,pxLeg));
		max_diff = (diff[i] > max_diff) ? diff[i] : max_diff;
//		cout << "diff[" << i<<"] = " << diff[i] <<" \t";
//		cout << "C[pxleg]["<<i<<"] = " <<C.at<uchar>(i,pxLeg)+0.0 <<endl;
	}

	int now_th = (th_down <= max_diff*2/3) ?th_down : max_diff*2/3;
	int pyDown = 0;
	for(int i=C.rows-10;i>height/2;i--){
		if(pyDown == 0){
			pyDown = (diff[i] >= now_th) ? i : pyDown;
		}
	}
	py = pyDown-5;
//	cout << "......searchDownCore : \t max_diff = "<< max_diff <<"\t";
//	cout << "th_down = "<< th_down <<"\t now_th = "<< now_th << "\t";
//	cout << "pyDown =  "<<pyDown <<endl;
	return 0;
}


int drawDLine(Mat &D , int pxLeg[],int pyFoot,int pyHead,int num){
	for(int i=0;i<num;i++){
		line(D, Point(pxLeg[i],100), Point(pxLeg[i],D.rows-100), Scalar(255,0,0), 0.2*i+1);
	}


	line(D, Point(20,pyFoot), Point(D.cols-20,pyFoot), Scalar(255,0,0), 1);
	line(D, Point(20,pyHead), Point(D.cols-20,pyHead), Scalar(255,0,0), 3);
	return 0;
}






int searchUp3(Mat D, int pxLeg[], int pyDown,int th_up,int & py,int num,int pyMask[]){
	searchUpCore(D,pxLeg[4],pyDown,th_up,py,pyMask);
	return 0;
}

int searchUp4(Mat D, int pxLeg[], int pyDown,int th_up,int pyUp[],int num,int pyMask[]){
	for(int i=0;i<num;i++){
		pyUp[i]=0;
		searchUpCore(D,pxLeg[i],pyDown,th_up,pyUp[i],pyMask);
	}


	return 0;
}


int selPyUp(int pyUp[],int &py,int num){

	int diff[num];
	int num_val = 0;
	int sum_pyUp =0;
	for(int i=0;i<num-1;i++){
		diff[i] = abs(pyUp[i] - pyUp[i+1]);
		if(diff[i] <= 30){
			num_val ++;
			sum_pyUp += pyUp[i];
//			cout << "pyUp["<<i<<"] = " << pyUp[i] << "\t";
//			cout << "sum = " << sum_pyUp<<endl;
		}
	}
	if(num_val ==0){
		return -1;
	}
	//py = sum_pyUp / num_val;
	py = pyUp[3];
	cout << "...searchUp4 : \t num_val = " << num_val <<"\t";
	cout << "py_Up = " << py<<endl;
	return 0;
}

int searchUpCore(Mat D, int pxLeg,int pyDown,int th_up,int &py, int pyMask[]){
	int height = (pyDown > 50) ? (pyDown - 50) : pyDown;
	int diff[height],max_diff = 0;
	int tmp_py=0;
	for(int i=pyMask[pxLeg];i<height;i++){
		diff[i] = abs(D.at<uchar>(i,pxLeg) - D.at<uchar>(i+5,pxLeg));
		max_diff = (diff[i] >= max_diff) ? diff[i] : max_diff;
//		cout << "diff [" << i <<"] = " << diff[i] <<"\t";
//		cout << "\t D[pxLeg]["<<i<<"] = " <<D.at<uchar>(i,pxLeg)+0.0 <<endl;
	}


	if(max_diff <= 50)
		max_diff = 300;

	int now_th = (th_up <= max_diff *2/3) ? th_up : max_diff *2/3;
	for(int i=height-1;i>=pyMask[pxLeg];i--){
		if(tmp_py ==0){
			tmp_py = (diff[i] >= now_th) ? i: tmp_py;
			//tmp_py = (diff >= max_diff *2/3) ? i: tmp_py;
		}
	}
	py = tmp_py + 5;
	cout << "......searchUpCore : \t th_up = " << th_up << "\t ";
	cout << "max_diff = " << max_diff << "\t";
	cout << "now_th = " << now_th << "\t pxLeg = " << pxLeg << "\t";
	cout << "py_up = " << py+0.0 << endl;


	return 0;

}



int drawDCircle(Mat &D,int pxLeg[],int pyDown[],int pyUp[],int num){
	//circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0);
	for(int i=0;i<num;i++){
		circle(D,Point(pxLeg[i],pyDown[i]),10,Scalar(255,0,0),2);
		circle(D,Point(pxLeg[i],pyUp[i]),15,Scalar(255,0,0),3);
	}
	return 0;
}


int xorImg2(Mat Ab, Mat Bf, Mat &C,int th_xor){
	C = Bf - Bf;	//build C
	int diff = 0;
	for(int i=0;i<C.rows;i++){
		for(int j=0;j<C.cols;j++){
			diff = abs(Bf.at<uchar>(i,j) - Ab.at<uchar>(i,j));
			if(diff >= th_xor)
				C.at<uchar>(i,j) = 255;
			else
				C.at<uchar>(i,j) = 0;
		}
	}

	return 0;
}


int getUpMask(Mat C, int pyMask[], int mask_width){
	int isWhite;
	for(int i=0;i<C.cols;i++){
		for(int j=0;j<C.rows-mask_width;j++){
			checkLineWhite(C, j,i,mask_width, isWhite);
			if(isWhite){
				pyMask[i] = j + mask_width;
				break;
			}
		}
		//cout << "pyMask["<<i<<"] = "<< pyMask[i] << endl;
	}

	return 0;
}


