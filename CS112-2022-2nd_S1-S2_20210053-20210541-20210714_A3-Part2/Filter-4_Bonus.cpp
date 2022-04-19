// Program: Filter-4.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Adham Allam
// Date:    4 Apr. 2022
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];

void loadImage ();
void saveImage ();
void Option();
void FlipHrizontal();
void FlipVertical();

int main()
{
  loadImage();
  Option();
  saveImage();
  return 0;
}
//_________________________________________
void Option(){
    cout << "Flip (h)orizontally or (v)ertically ? " << endl;
    char option;
    cin >> option;
    if(option == 'h'){
        FlipHrizontal();
    }
    else if(option == 'v'){
        FlipVertical();
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
void FlipHrizontal() {
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j< (SIZE/2); j++){
        for(int k = 0; k < RGB; k++){
            swap(image[i][j][k] , image[i][SIZE - j][k]);
      }
    }
  }
}
//_________________________________________
void FlipVertical(){
  for (int i = 0; i < (SIZE/2); i++){
    for (int j = 0; j < SIZE; j++){
        for(int k = 0; k < RGB; k++)
        swap(image[i][j][k] , image[SIZE - i][j][k]);
    }
  }
}
