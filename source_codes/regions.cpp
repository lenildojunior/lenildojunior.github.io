#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int, char**){
  Mat image;
  Vec3b val;
	int p1x,p1y,p2x,p2y;


  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu bolhas.png" << endl;

	cout<< "Digite as coordenadas do ponto 1 (X e y)\n";
	cin>>p1x;
	cin>>p1y;
	cout<<"\nDigite as coordenadas do ponto 2 (x e y)\n";
	cin>>p2x;
	cin>>p2y;
  namedWindow("janela",WINDOW_AUTOSIZE);

  for(int i=p1x;i<p2x;i++){
    for(int j=p1y;j<p2y;j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j);
    }
  }
  
  

  imshow("janela", image);  
  waitKey();
  return 0;
}
