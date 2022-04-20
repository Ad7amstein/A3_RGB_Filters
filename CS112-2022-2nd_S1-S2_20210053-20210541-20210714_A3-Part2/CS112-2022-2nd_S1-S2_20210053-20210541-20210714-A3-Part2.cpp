/***************************************************************
 Purpose: Invert and rotate (90,180,270) RGB images.
 Purpose: Merge and darken/ligthen grayscale images.
 Purpose: Flip and black/white grayscale images.
 Program load a RGB image and store in another file

 Author1:  Abdullah Mohammed Abdullah Farg
 ID: 20210541

 Author2:  Adham Mohamed sayed Allam
 ID: 20210053

 Author3:  Selsabeel Asim Ali Elbagir
 ID: 20210714


 Section: S1 & S2
 Date:    7 April 2022
 Version: 1.0
****************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image [SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];

void loadImage ();
void saveImage ();
void selection_menu();
void BW_Image ();
void BW_merger();

int main(){

  selection_menu();

}
//_________________________________________
void selection_menu(){
  char filter='1';

  while (filter != 0)
  {
  	loadImage();

  	cout <<"Please select a filter to apply or 0 to exit:" << endl;
  	cout << "1.Black & White Image.\n" << "2.Invert Image.\n"
         << "3.Merge Images.\n"        << "4.Flip Image.\n"
  	     << "5.Rotate Image.\n"        << "6.Darken and Lighten Image.\n"
  	     << "7.Detect Image Edges.\n"  << "8.Enlarge Image.\n"
  	     << "9.Shrink Image.\n"        << "a.Mirror Image.\n"
  	     << "b.Shuffle Image.\n"       << "c.Blur Image.\n"
  	     <<"0.exit.\n";
  	cin >> filter;

  	if (filter == '1' )
  		BW_Image();
  	else if (filter == '2' )
  		;
  	else if (filter == '3' )
  	    ;
  	else if (filter == '4' )
  	    ;
  	else if (filter == '5' )
  	    ;
  	else if (filter == '6' )
  	    ;
    else if (filter == '7' )
        ;
    else if (filter == '8' )
        ;
    else if (filter == '9' )
        ;
    else if (filter == 'a' )
        ;
    else if (filter == 'b' )
        ;
    else if (filter == 'c' )
        ;
  	else if (filter == '0' ){
  		cout << "M3 elsalamh ya user ya habibi \n"  ;
  		break;
  	}
  	saveImage();

  }
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}
//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeRGBBMP(imageFileName, image);
}
//_________________________________________
void BW_Image(){
  long sum = 0;
  double avg = 0;

  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      for(int n = 0; n < RGB; n++){
        sum += image[i][j][n];
      }
      avg = sum / RGB;
      if(avg > 128){
        for(int m = 0; m < RGB; m++){
            image[i][j][m] = 255;
        }
      }
      else{
        for(int m = 0; m < RGB; m++){
            image[i][j][m] = 0;
        }
      }
    sum = 0;
    avg = 0;
    }
  }
}

void BW_merger() {
    char imageFileName2[100];
    // Get colored image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat (imageFileName2, ".bmp");
    readRGBBMP(imageFileName2, image2);


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
                for (int k=0;k<RGB; k++) {
            image[i][j][k] = 0.5*( image[i][j][k] + image2[i][j][k] );
                }
        }
    }

}



