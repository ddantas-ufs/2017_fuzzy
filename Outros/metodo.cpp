#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>
#define __OPENCL__
#include <visiongl.h>

int jan1 = 3;
int jan2 = 3;
int val1 = 1;
int val2 = 3;
float tsy = 3.0;
int b = 1.0;

void mDilate(VglImage *src, VglImage *dst, float element[], int type, int x, int y, int iterations){

  int i;
  VglImage *tmp = vglCreateImage(src);

  if(iterations > 0){
    if(type > 0){
    	vglClFuzzyDilate(src,tmp,element,x,y,type);
    }else{
        vglClDilate(src,tmp,element,x,y); 
    }
    for(int i = 1; i < iterations; i++){
      if (i % 2 == 0){
	if(type > 0){
		vglClFuzzyDilate(dst,tmp,element,x,y,type);
	}else{
		vglClDilate(dst,tmp,element,x,y);
	}
      }else{
	if(type > 0){
		vglClFuzzyDilate(tmp, dst,element,x,y,type);
	}else{
		vglClDilate(tmp,dst,element,x,y);
	}
      }
    }
    if (iterations % 2 == 1){
      vglClCopy(tmp,dst);
    }
  }
  vglClDownload(dst);
  vglReleaseImage(&tmp);
}

void mErode(VglImage *src, VglImage *dst, float element[], int type, int x, int y, int iterations){

  int i;
  VglImage *tmp = vglCreateImage(src);

  if(iterations > 0){
    if(type > 0){
    	vglClFuzzyErode(src,tmp,element,x,y,type);
    }else{
        vglClErode(src,tmp,element,x,y); 
    }
    for(int i = 1; i < iterations; i++){
      if (i % 2 == 0){
	if(type > 0){
		vglClFuzzyErode(dst,tmp,element,x,y,type);
	}else{
		vglClErode(dst,tmp,element,x,y);
	}
      }else{
	if(type > 0){
		vglClFuzzyErode(tmp, dst,element,x,y,type);
	}else{
		vglClErode(tmp,dst,element,x,y);
	}
      }
    }
    if (iterations % 2 == 1){
      vglClCopy(tmp,dst);
    }
  }
  vglClDownload(dst);
  vglReleaseImage(&tmp);
}

void closingImage(VglImage *src, VglImage *dst,float element[],int x, int y, int iterations, int type){

  int i;
  VglImage *tmp = vglCreateImage(src);

  mDilate(src, tmp, element, type, x, y, iterations);
  mErode(tmp, dst, element, type, x, y, iterations);

  vglReleaseImage(&tmp);

}

void openingImage(VglImage *src, VglImage *dst,float element[],int x, int y, int iterations, int type){

  int i;
  VglImage *tmp = vglCreateImage(src);

  mErode(src, tmp, element, type, x, y, iterations);
  mDilate(tmp, dst, element, type, x, y, iterations);

  vglReleaseImage(&tmp);

}

void blackHat (VglImage *src, VglImage *dst,float element[], int x, int y, int interations, int type){

  VglImage *tmp = vglCreateImage(src);
  VglImage *tmp2 = vglCreateImage(src);
	
  closingImage(src, tmp, element, x, y, interations, type);

  vglClSub(tmp, src, tmp2);
  vglClCopy(tmp2, dst);
  vglClDownload(dst);

  vglReleaseImage(&tmp);
  vglReleaseImage(&tmp2);

}

void gaussianBlurImage (IplImage *src, IplImage *dst, int Kwidth, int Kheight, int x, int y = 0){

  using namespace cv;

  Mat temp = cvarrToMat(src);
  GaussianBlur(temp, temp, Size(Kwidth,Kheight),x,y);
  *dst = temp;
}

float* gaussianFunction2D(int sizeX, int sizeY, float sigma){
	int i, centro, limX, limY, x, y;
	limX = (sizeX - 1) / 2;
	limY = (sizeY - 1) / 2;
        //sigma = limX / sigma;
	float t = 2*( pow(sigma,2) );
	float m = 1 / (M_PI*t);
	float fator, *element = NULL;
	
	if ( (sizeX % 2 == 0) || (sizeY % 2 == 0) ){
		printf("[Error] Valor de X e Y nao podem ser par\n");
		exit(1);
	}
	
	if (sigma <= 0){
		printf("[Error] Valor de sigma deve ser positivo nao nulo\n");
		exit(1);
	}
	

	element = (float*)malloc( (sizeX*sizeY)*sizeof(float) );
	
	centro = ( (sizeX*sizeY) - 1) / 2;
	
	//Calculando o valor para o centro e calculando o fator de normalização
	element[centro] = m * ( pow(M_E, 0) );
	fator = 1 / element[centro];
	element[centro] = 1;
	
	//Calculando os valores das demais coordenadas utilizando no final o fator de normalização
	x = -limX;
	y = -limY;
	
	for(i=0; i<(sizeX*sizeY); i++){
		
		 if(i != centro ){
		 	
		 	float n = ( -( pow(x,2) + pow(y,2) ) ) / t;
		 	element[i] = (m * ( pow(M_E, n)) )*fator;
		 	
		 }
		 y++;
		 
		 if( y == (limY+1) ){
		 	y = - limY;
		 	x++;
		 }
	}
	
	return element;
};

void aplicarMask(IplImage *src, IplImage *mask, IplImage *dst){
  IplImage *tmp = cvCloneImage(mask);

  cvMin(src,mask,tmp);
  cvCopy(tmp,dst);

  cvReleaseImage(&tmp);
}

void printElement(float element[], int x, int y){
	int i,j;
	for(i=0;i<y;i++){
		for(j=0;j<x;j++){
			printf("%f ", element[i*x+j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void metodo(int type,int tam, char nome[], char sup[] ){
  int i;
  char diret[100] = "Entradas/01_test.tif";

  vglClInit();
  vglInit();

    VglImage *vTest;
    VglImage *vImage = vglLoadImage(diret);
    IplImage *tmp = cvCreateImage(cvGetSize(vImage->ipl),vImage->ipl->depth, 1);

    //float *element = gaussianFunction2D( tam, tam, ( (tam - 1) / 2) * (1.0/(5.0*tam)) );
    tam = 7	;
    float *element = gaussianFunction2D( tam, tam, ( (tam) / 2.0)  );
    printElement(element,tam, tam);

    cvSplit(vImage->ipl, NULL, tmp, NULL, NULL);
    vglReleaseImage(&vImage);
/*
    IplImage *mask = cvCreateImage(cvGetSize(tmp),tmp->depth, tmp->nChannels);
    cvThreshold(tmp,mask, 20, 255, CV_THRESH_BINARY);
    aplicarMask(tmp,mask,tmp);
*/
 //   IplImage *imagem = cvCreateImage(cvGetSize(tmp), tmp->depth, 3);
  //  cvMerge(tmp,tmp,tmp,NULL, imagem);

    vImage = vglCopyCreateImage( tmp );
    vTest =  vglCopyCreateImage( tmp );  
 //   vglImage3To4Channels(vImage);
 //   vglImage3To4Channels(vTest);
    
    mDilate(vImage, vTest, element, type, tam, tam, 1);
 //   vglImage4To3Channels(vTest);
    strcpy( diret, sup );
    strcat(diret, "dilate");
    strcat(diret, nome);
    cvSaveImage(diret, vTest->ipl);

 //   vglImage3To4Channels(vTest);
    mErode(vImage, vTest, element, type, tam, tam, 1);
 //   vglImage4To3Channels(vTest);
    strcpy(diret, sup);
    strcat(diret,"erode");
    strcat(diret, nome);
    cvSaveImage(diret, vTest->ipl);

 //   vglImage3To4Channels(vTest);
    closingImage(vImage, vTest, element, tam, tam, 1, type);
 //   vglImage4To3Channels(vTest);
    strcpy(diret, sup);
    strcat(diret, "closing");
    strcat(diret, nome);
    cvSaveImage(diret, vTest->ipl);

 //   vglImage3To4Channels(vTest);
    openingImage(vImage, vTest, element, tam, tam, 1, type);
    strcpy(diret, sup);
    strcat(diret,"opening");
    strcat(diret, nome);
    cvSaveImage(diret, vTest->ipl);
    
  //  vglImage3To4Channels(vTest);
    blackHat( vImage, vTest, element, tam, tam, 1, type);
 //   vglImage4To3Channels(vTest);
    strcpy(diret, sup);
    strcat(diret,"bh");
    strcat(diret, nome);
    cvSaveImage(diret, vTest->ipl);

}

int main(int argc, char** argv){
  int ident;
  char nome[28];
  char sup[50];
 
  strcpy(sup, argv[3]);

  switch ( atoi(argv[1]) ){
      case 1:
         strcpy(nome,"STANDARD");
	 ident = VGL_CL_FUZZY_STANDARD;
 	 break;
      case 2:
    	 strcpy(nome,"ALGEBRAIC");
	 ident = VGL_CL_FUZZY_ALGEBRAIC;
    	 break;
      case 3:
    	 strcpy(nome,"BOUNDED");
	 ident = VGL_CL_FUZZY_BOUNDED;
    	 break;
      case 5:
	 strcpy(nome,"DaP");
	 ident = VGL_CL_FUZZY_DAP;
    	 break;
      case 6:
	 strcpy(nome,"HAMACHER");
	 ident = VGL_CL_FUZZY_HAMACHER;
    	 break;
      case 9:
	 strcpy(nome,"CLASSIC");
	 ident = 0;
    	 break;
      default:
    	 printf("*** [Erro] Metodo nao criado\n");
    	 exit(1);
  }
  strcat(nome, ".tif");
  metodo(ident, atoi(argv[2]), nome, argv[3] );

  return 0;
}
