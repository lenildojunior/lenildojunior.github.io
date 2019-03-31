#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image, mask;
  int width, height;
  int nobjects,nobjectsborder,nobjectsholes;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

	//Mudar a cor de fundo para diferenciar objetos com e sem buraco
	p.x=0;
	p.y=0;
	floodFill(image,p,175);


  imshow("image", image);
  imwrite("trocafundo.png", image);
  waitKey();
  return 0;
}
