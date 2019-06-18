#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc/imgproc_c.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	Mat img,dst;
RNG rng(12345);
	img= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	//threshold(img,dst, 0, 255, THRESH_BINARY);
	imshow("janela",img);
	waitKey();
    CvChain* chain=0;
CvMemStorage* storage=0;
storage=cvCreateMemStorage(0);

IplImage tmp = img;
cvFindContours( &tmp, storage, (CvSeq**)(&chain), sizeof(*chain), CV_RETR_EXTERNAL, CV_CHAIN_CODE);
cout<<"\nAte aqui ok?\n";

for(;chain!=NULL;chain=(CvChain*)chain ->h_next) 
{   
    //chain=(CvChain*)chain ->h_next; 
    //if(chain==NULL){break;}
    CvSeqReader reader; 
    int i, total = chain->total; 
    cvStartReadSeq((CvSeq*)chain,&reader,0);
    printf("--------------------chain\n"); 

    for(i=0;i<total;i++) 
    { 
        char code; 
        CV_READ_SEQ_ELEM(code, reader); 
        printf("%d",code); 
    } 
}

  return 0;
}
