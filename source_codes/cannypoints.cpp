#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <cstdlib>

#define STEP 5
#define JITTER 3
#define RAIO 3

using namespace std;
using namespace cv;


char TrackbarName[50];

Mat image, border;


int main(int argc, char**argv){ 
	int width, height;
	int valorPixel;
	//variaveis para o pontilhismo
	vector<int> yrange;
  vector<int> xrange;
	Mat frame, points,newImage;
	int x, y, gray;

	srand(time(0));

  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  width=image.size().width;
  height=image.size().height;

  namedWindow("canny",1);
	Canny(image, border, 40, 120);
	imshow("canny", border);
  waitKey();
  imwrite("cannyborders.png", border);//Imagem que possui apenas as bordas brancas com fundo preto
	//fim algoritmo de canny

	//inicio algoritmo do pontilhismo
  xrange.resize(height/STEP);
  yrange.resize(width/STEP);
  
  iota(xrange.begin(), xrange.end(), 0); 
  iota(yrange.begin(), yrange.end(), 0);

  for(uint i=0; i<xrange.size(); i++){
    xrange[i]= xrange[i]*STEP+STEP/2;
  }

  for(uint i=0; i<yrange.size(); i++){
    yrange[i]= yrange[i]*STEP+STEP/2;
  }

  points = Mat(height, width, CV_8U, Scalar(255));

  random_shuffle(xrange.begin(), xrange.end());
  
  for(auto i : xrange){
    random_shuffle(yrange.begin(), yrange.end());
    for(auto j : yrange){
      x = i+rand()%(2*JITTER)-JITTER+1;
      y = j+rand()%(2*JITTER)-JITTER+1;
      gray = image.at<uchar>(x,y);
      circle(points,
             cv::Point(y,x),
             RAIO,
             CV_RGB(gray,gray,gray),
             -1,
             CV_AA);
    }
  }
  imwrite("pontos.jpg", points);
	//fim algortimo pontilhismo

	//inicio do ajuste da imagem pontilhista com canny
	newImage = points.clone();
  for(int i=0;i<height;i++){
    //random_shuffle(yrange.begin(), yrange.end());
    for(int j=0;j<width;j++){
			if(border.at<int> (i,j) !=0){//encontrou um pixel de borda
				valorPixel = image.at<uchar> (i,j);
				 circle(newImage,
             cv::Point(j,i),
             RAIO ,
             CV_RGB(valorPixel,valorPixel,valorPixel),
             -1,
  	           CV_AA);
			}
		}
	}
	imwrite("nova_arte.png",newImage);
  return 0;
}
