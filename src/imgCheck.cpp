/*
 * imgCheck.cpp
 *
 *  Created on: 2017Äê4ÔÂ16ÈÕ
 *      Author: Administrator
 */


#include "imgCheck.h"


int showInf(Mat M){
	if(M.empty()){
		cout << "Mat is empty" << endl;
		return -2;
	}
	int height = M.rows;
	int width = M.cols;
	int channel = M.channels();
	cout << endl;
	cout << "channel = "<< channel <<"\theight = " << height << "\twidth = " << width <<endl;
	return 0;
}


