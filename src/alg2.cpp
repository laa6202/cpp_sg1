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

	fn0 = "t9/Tue May 23 16-49-54.png";
	cout << "...get back file:" << fn0 <<endl;
	return 0;
}

int getFontFn2(String & fn0){
	//fn0 = "t8/Mon May 22 16-40-33.png";			//one line skew litter
	//fn0 = "t8/Mon May 22 16-42-01.png";			//liang xie

	//fn0 = "t9/Tue May 23 16-49-48.png";
	//fn0 = "t9/Tue May 23 16-55-16.png";			//head  3 point error
	//fn0 = "t9/Tue May 23 17-28-40.png";			//two big skew
	//fn0 = "t9/Tue May 23 17-32-09.png";			//one big skew
	//fn0 = "t9/Tue May 23 17-32-00.png";			//head
	//fn0 = "t9/Tue May 23 17-43-39.png";			//you gen
	//fn0 = "t9/Tue May 23 17-50-18.png";			//wuxian
	fn0 = "t9/Tue May 23 17-55-50.png";			//tuoxie	caizhi
	//fn0 = "t9/Tue May 23 17-43-57.png";			//head
	//fn0 = "t9/Tue May 23 18-03-00.png";

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
	//searchUpCore(D,pxLeg[4],pyDown,th_up,py,pyMask);
	return 0;
}

int searchUp4(Mat D, int pxLeg[], int pyDown,int th_up,int pyUp[],int num,int max_pyMask){
	for(int i=0;i<num;i++){
		pyUp[i]=0;
		searchUpCore(D,pxLeg[i],pyDown,th_up,pyUp[i],max_pyMask);
	}


	return 0;
}


int selPyUp(int pyUp[],int sel_diff,int &py,int num){

	int pyUpSort[num];
	int index[num];
	bubbleSort(pyUpSort,index,pyUp,num);

	int diff;
	int ave[num-1];
	int num_val = 0;
	int sum_pyUp =0;
	for(int i=0;i<num-1;i++){
		diff = (pyUpSort[i+1] - pyUpSort[i]);
		ave[i] = 0;
		if(diff <= sel_diff){
			ave[i] = (pyUpSort[i] + pyUpSort[i+1])/2;
			num_val ++;
		}
		cout << "......selPyUp : pyUpSort["<<i<<"] = " << pyUpSort[i] << "\t";
		cout << "["<<i+1<<"] = " << pyUpSort[i+1] << "\t";
		cout << "index = " << index[i] <<"  "<<index[i+1]<< "\t";
		cout << "ave["<<i<<"] = " << ave[i] << endl;
	}
	if(num_val ==0){
		cout << "...selPyUp ; \t No group of 2 points! return -1" << endl;
				return -1;
	}

	//step 2
	int aveSort[num-1],index2[num-1];
	bubbleSort(aveSort,index2,ave,num-1);

	int ave2[num-1];
	int num_val2 = 0;

	for(int i=0;i<num-2;i++){
		ave2[i] = 0;
		if(aveSort[i] !=0){
			diff = aveSort[i+1] - aveSort[i];
			if(diff < sel_diff){
				ave2[i] = (aveSort[i] + aveSort[i+1])/2;
				num_val2 ++;
			}
		}
//		cout << "ave2["<<i<<"] = "<< ave2[i]<< "\tindex2 = " << index2[i] <<endl;
	}

	if(num_val2 == 0){
		cout << "...selPyUp ; \t No group of 3 point! return -2" << endl;
		return -2;
	}




	for(int i=0 ;i < num-2;i++){
		if(ave2[i] != 0)
		sum_pyUp +=  ave2[i];
	}

	py = sum_pyUp / num_val2;
	//py = pyUp[3];
	cout << "...selPyUp : \t num_val2 = " << num_val2 <<"\t";
	cout << "py_Up = " << py<<endl;
	return 0;
}



int searchUpCore(Mat D, int pxLeg,int pyDown,int th_up,int &py, int max_pyMask){
	int height = (pyDown > 80) ? (pyDown - 80) : pyDown;
	int pyMask = max_pyMask + 50;
	int diff[height],max_diff = 0;
	int tmp_py=0;
//	for(int i=pyMask[pxLeg];i<height;i++){
	for(int i=pyMask;i<height;i++){
		diff[i] = abs(D.at<uchar>(i,pxLeg) - D.at<uchar>(i+5,pxLeg));
		max_diff = (diff[i] >= max_diff) ? diff[i] : max_diff;
//		cout << "diff [" << i <<"] = " << diff[i] <<"\t";
//		cout << "\t D[pxLeg]["<<i<<"] = " <<D.at<uchar>(i,pxLeg)+0.0 <<endl;
	}


//	if(max_diff <= 50)
//		max_diff = 300;

	int now_th = (th_up <= max_diff *2/3) ? th_up : max_diff *2/3;
	for(int i=height-1;i>=pyMask;i--){
		if(tmp_py ==0){
			tmp_py = (diff[i] >= now_th) ? i: tmp_py;
			//tmp_py = (diff >= max_diff *2/3) ? i: tmp_py;
		}
	}
	py = tmp_py + 5;
//	cout << "......searchUpCore : \t py_up = " << py + 0.0 << "\t ";
//	cout << "max_diff = " << max_diff << "\t";
//	cout << "now_th = " << now_th << "\t pxLeg = " << pxLeg << "\t";
//	cout << endl;


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


int getUpMask(Mat C, int pyMask[], int mask_width,int &max_pyMask){
	int isWhite;
	max_pyMask = 0;
	for(int i=0;i<C.cols;i++){
		for(int j=0;j<C.rows-mask_width;j++){
			checkLineWhite(C, j,i,mask_width, isWhite);
			if(isWhite){
				pyMask[i] = j + mask_width;
				break;
			}
		}
		max_pyMask = (pyMask[i] > max_pyMask) ? pyMask[i] : max_pyMask;
		//cout << "pyMask["<<i<<"] = "<< pyMask[i] << endl;
	}
	cout << "...getUpMask : \t max_mask = " << max_pyMask << endl;
	return 0;
}



int selPyUp2(int pyUp[],int sel_diff,int &py,int num){
	int dist[num];
	for(int i=0;i<num;i++){
		dist[i] = 0;
		for(int j=0;j<num;j++){
			if(pyUp[j] < 20)
				continue;
			dist[i] += abs(pyUp[i] - pyUp[j]);
		}
		//cout << "distance of pyUp[" << i <<"] = "<< dist[i] <<endl;
	}
	int min_index = 0;
	int min_dist = 999999;
	for(int i=0;i<num;i++){
		min_dist  = (dist[i] <= min_dist) ? dist[i] : min_dist;
		min_index = (dist[i] <= min_dist) ? i : min_index;
	}
	cout << "...selPyUp2 : \t min_dist = " << min_dist << "\tmin_index =" << min_index <<endl;

	py = pyUp[min_index];
	return 0;
}


int modifyPyHead(int &pyHead, int pyFoot, int max_pyMask, int searchRange,float forceRatio){
	int disHead = pyFoot - pyHead;
	int disMask = (max_pyMask < 30) ? searchRange : pyFoot - max_pyMask;
	if(disHead > disMask/2){
		cout << "...modifyPyHead : \t modified! Force pyHead!"<<endl;
		disHead = (int)(disMask / forceRatio);
		pyHead = pyFoot - disHead;
	}
	else{
		cout <<"...modifyPyHead : \t Keep pyHead ="<<pyHead<<endl;
	}

//	cout << "disHead = "<< disHead <<"\tdisMask = " << disMask <<endl;

	return 0;
}
