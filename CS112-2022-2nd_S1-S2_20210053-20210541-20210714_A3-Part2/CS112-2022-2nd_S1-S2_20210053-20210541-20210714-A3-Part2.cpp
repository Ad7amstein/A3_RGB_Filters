
/***************************************************************
 Purpose: Invert and rotate (90,180,270) RGB images.

 Program load a RGB image and store in another file, then give the user an option of
 12 functions to choose from that all work on RGB images.

 Author1:  Abdullah Mohammed Abdullah Farg
 ID: 20210541

 Author2:  Adham Mohamed sayed Allam
 ID: 20210053

 Author3:  Selsabeel Asim Ali Elbagir
 ID: 20210714


 Section: S1 & S2
 Date:    20 April 2022
 Version: 1.0
****************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image [SIZE][SIZE][RGB];
unsigned char image2 [SIZE][SIZE][RGB];
unsigned char newimage2 [SIZE/2][SIZE/2][RGB];
unsigned char newimage3[SIZE/3][SIZE/3][RGB];
unsigned char newimage4[SIZE/4][SIZE/4][RGB];


void loadImage ();
void saveImage ();
void selection_menu();
void BW_Image ();
void RGB_merger();
void RGB_blur();
void RGB_shrink();
void RGB_darkenlight();

int main(){

    selection_menu();

}
//_________________________________________
void selection_menu(){
    char filter='1';

    while (filter != '0')
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
        else if (filter == '3' ){
            RGB_merger();
            saveImage();
            break;}
        else if (filter == '4' )
            ;
        else if (filter == '5' )
            ;
        else if (filter == '6' )
            RGB_darkenlight();
        else if (filter == '7' )
            ;
        else if (filter == '8' )
            ;
        else if (filter == '9' )
            RGB_shrink();
        else if (filter == 'a' )
            ;
        else if (filter == 'b' )
            ;
        else if (filter == 'c' )
            RGB_blur();
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

void RGB_merger() {
    char imageFileName2[100];
    // Get colored image file name
    cout << "Enter the source image (that you want to merge with) file name: ";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat (imageFileName2, ".bmp");
    readRGBBMP(imageFileName2, image2);


    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k=0;k<RGB; k++) {
                image[i][j][k] = (image[i][j][k] + image2[i][j][k])/2;
            }
        }
    }

}
void RGB_shrink() {
    int choice;
    cout << "Would you like to shrink the image by a factor of 2, 3, or 4?\n";
    cout << "Please input your choice as 2 if you want the dimensions to be 1/2, \n";
    cout << "Please input your choice as 3 if you want the dimensions to be 1/3, \n";
    cout << "Please input your choice as 4 if you want the dimensions to be 1/4, \n";
    cin >> choice;
    if ((choice != 2) && (choice != 3) && (choice != 4)) {
        cout << "Invalid entry.";
    }
    else {
        int x=0,y=0,z=0;
        for (int i = 0; i < SIZE; i+=choice) {
            for (int j = 0; j < SIZE; j+=choice) {
                for (int k=0;k<RGB;k++) {
                    if (choice == 2) {
                        newimage2[x][y][z] = image[i][j][k];
                    }
                    if (choice == 3) {
                        newimage3[x][y][z] = image[i][j][k];
                    }
                    if (choice == 4) {
                        newimage4[x][y][z] = image[i][j][k];
                    }
                    z++;
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k=0; k<RGB; k++) {
                    image[i][j][k] = 255;
                }
            }
        }
        for (int i = 0; i < SIZE/choice; i++) {
            for (int j = 0; j < SIZE/choice; j++) {
                for (int k=0;k<RGB; k++) {
                    if (choice==2){
                        image[i][j][k] = newimage2[i][j][k];
                    }
                    if (choice==3){
                        image[i][j][k] = newimage3[i][j][k];
                    }
                    if (choice==4){
                        image[i][j][k] = newimage4[i][j][k];
                    }

                }
            }
        }
    }
}

void RGB_blur() {
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            for (int k=0; k<RGB;k++) { // we don't change k in this loop since we don't want to change/blur the  colors of the image
                image[i][j][k] = ( image[i][j][k] + image[i][j+1][k] + image[i][j-1][k] + image[i+1][j][k] +image[i+1][j+1][k] +
                                   + image[i+1][j-1][k] + image[i-1][j][k] + image[i-1][j+1][k] + image[i-1][j-1][k] ) / 9;
            }
        }
    }
}

void RGB_darkenlight() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> choice;
    if (choice=='d'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k=0;k<RGB;k++) {
                    image[i][j][k] *= 0.5;
                }
            }
        }
    }
    else if (choice=='l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<RGB;k++) {
                    image[i][j][k] = 0.5*(image[i][j][k]+SIZE);
                }
            }

        }
    }
    else{
        cout << "Invalid entry.";
    }

}

