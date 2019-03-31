#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
	Mat newImage;
	

  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
	newImage= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu bolhas.png" << endl;
	//Criando as regiões de interesse
	Rect regA(0,0,image.cols/2,image.rows/2);
	Rect regB(image.cols/2,0,image.cols,image.rows/2);
	Rect regC(0,image.rows/2,image.cols/2,image.rows);
	Rect regD(image.cols/2,image.rows/2,image.cols,image.rows);
	
	//Realizando ajustes para os retângulos
	regA = regA & Rect(0,0,image.cols,image.rows);
	regB = regB & Rect(0,0,image.cols,image.rows);
	regC = regC & Rect(0,0,image.cols,image.rows);
	regD = regD & Rect(0,0,image.cols,image.rows);

	//Nomeando as regiões e interesse
	Mat roiA(image,regA);
	Mat roiB(image,regB);
	Mat roiC(image,regC);
	Mat roiD(image,regD);

	//Trocando as posições (A com D, B com C)

	Rect whereRecA(image.cols/2,image.rows/2,image.cols,image.rows);
	Rect whereRecB(0,image.rows/2,image.cols/2,image.rows);
	Rect whereRecC(image.cols/2,0,image.cols,image.rows/2);
	Rect whereRecD(0,0,image.cols/2,image.rows/2);

	whereRecA = whereRecA & Rect(0,0,image.cols,image.rows);
	whereRecB = whereRecB & Rect(0,0,image.cols,image.rows);
	whereRecC = whereRecC & Rect(0,0,image.cols,image.rows);
	whereRecD = whereRecD & Rect(0,0,image.cols,image.rows);

	roiA.copyTo(newImage(whereRecA));
	roiB.copyTo(newImage(whereRecB));
	roiC.copyTo(newImage(whereRecC));
	roiD.copyTo(newImage(whereRecD));

	
  namedWindow("janela",WINDOW_AUTOSIZE);
	
  imshow("janela", newImage);  
  waitKey();
  return 0;
}
