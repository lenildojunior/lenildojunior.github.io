#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
  int nClusters = 6;
  Mat rotulos;
  int nRodadas = 1;
  Mat centros;

  
  Mat img = imread( argv[1], CV_LOAD_IMAGE_COLOR);
  Mat samples(img.rows * img.cols, 3, CV_32F);

  for( int y = 0; y < img.rows; y++ ){
    for( int x = 0; x < img.cols; x++ ){
      for( int z = 0; z < 3; z++){
        samples.at<float>(y + x*img.rows, z) = img.at<Vec3b>(y,x)[z];
	  	}
		}
  }
  for(int t=0;t<10;t++){
  	kmeans(samples,
		 	nClusters,
		 	rotulos,
		 	TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001),
		 	nRodadas,
		 	KMEANS_RANDOM_CENTERS, //centros aleatórios
		 	centros );


  	Mat rotulada( img.size(), img.type() );
  	for( int y = 0; y < img.rows; y++ ){
    	for( int x = 0; x < img.cols; x++ ){ 
	  		int indice = rotulos.at<int>(y + x*img.rows,0);
	  		rotulada.at<Vec3b>(y,x)[0] = (uchar) centros.at<float>(indice, 0);
	  		rotulada.at<Vec3b>(y,x)[1] = (uchar) centros.at<float>(indice, 1);
	  		rotulada.at<Vec3b>(y,x)[2] = (uchar) centros.at<float>(indice, 2);
			}
  	}
  //imshow( "clustered image", rotulada );
		switch(t){
			case 0:
  			imwrite("k_figure1.jpg", rotulada);
				break;
			case 1:
  			imwrite("k_figure2.jpg", rotulada);
				break;
			case 2:
  			imwrite("k_figure3.jpg", rotulada);
				break;
			case 3:
  			imwrite("k_figure4.jpg", rotulada);
				break;
			case 4:
  			imwrite("k_figure5.jpg", rotulada);
				break;
			case 5:
  			imwrite("k_figure6.jpg", rotulada);
				break;
			case 6:
  			imwrite("k_figure7.jpg", rotulada);
				break;
			case 7:
  			imwrite("k_figure8.jpg", rotulada);
				break;
			case 8:
  			imwrite("k_figure9.jpg", rotulada);
				break;
			case 9:
  			imwrite("k_figure10.jpg", rotulada);
				break;
			default:
				cout<<"nao foi";
				break;
		}
	}
  waitKey( 0 );
}
