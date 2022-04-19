// Program: Filter-1.cpp
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
unsigned char image [SIZE][SIZE][RGB];

void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
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
void doSomethingForImage() {
    long sum = 0, sum2 = 0;
    double avg = 0, avg2 = 0;
    for(int k = 0; k < SIZE; k++){
        for(int l = 0; l < SIZE; l++){
            for(int m = 0; m < RGB; m++){
                sum += image[k][l][m];
            }
        }
    }
    avg = sum / (SIZE * SIZE * RGB);
  for (int i = 0; i < SIZE; i++){
    for (int j = 0; j < SIZE; j++){
      for(int n = 0; n < RGB; n++){
        sum2 += image[i][j][n];
      }
      avg2 = sum2 / RGB;
      if(avg2 > 128){
        for(int m = 0; m < RGB; m++){
            image[i][j][m] = 255;
        }
      }
      else{
        for(int m = 0; m < RGB; m++){
            image[i][j][m] = 0;
        }
      }
    sum2 = 0;
    avg2 = 0;
    }
  }
}
