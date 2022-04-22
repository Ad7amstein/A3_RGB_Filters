/***************************************************************
 Purpose: Invert, rotate (90,180,270), Flip, Merge, Enlarge,
 Shuffle, Shrink(1/2 dimension,1/3 dimension, 1/4 dimension), Blur, Darken&lighten, Detect Edges, Black&White RGB images.
 The program loads a RGB image, gives the user an option of
 12 functions, each that gives a different filter effect, and then saves it
 to a new image (in the same program's file directory) that the user chooses the name of.

 Author1:  Abdullah Mohammed Abdullah Farg
 ID: 20210541

 Author2:  Adham Mohamed sayed Allam
 ID: 20210053

 Author3:  Selsabeel Asim Ali Elbagir
 ID: 20210714

 Section: S1 & S2
 Date:    22 April 2022
 Version: 2.0
****************************************************************/
//include libraries to use
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
//initialize image to work on it
unsigned char image [SIZE][SIZE][RGB];
unsigned char image2 [SIZE][SIZE][RGB];
unsigned char newimage2 [SIZE/2][SIZE/2][RGB]; //initializing an image for the shrink (1/2 dimension) filter
unsigned char newimage3[86][86][RGB]; //initializing an image for the shrink (1/3 dimension) filter
unsigned char newimage4[SIZE/4][SIZE/4][RGB]; //initializing an image for the shrink (1/4 dimension) filter

//Functions that work on images
void loadImage ();
void saveImage ();
void saveImage2 ();
void selection_menu();
void BW_Image ();
void RGB_Flip ();
void RGB_EdgeDetective ();
void RGB_Mirror ();
void RGB_merger();
void RGB_blur();
void RGB_shrink();
void RGB_darkenlight();
void Invert_Filter();
void Rotate_Image();
void Enlarge_Image();
void the_order (int& a , int& b  ,char q);
void Shuffle_Filter();

int main(){

    selection_menu();

}
//_________________________________________
void selection_menu(){
    char filter='1'; // this ensures the selection menu loops continually

    while (filter != '0')
    {
        loadImage();
        //display the selection minu
        cout <<"Please select a filter to apply or 0 to exit:" << endl;
        cout << "1.Black & White Image.\n" << "2.Invert Image.\n"
             << "3.Merge Images.\n"        << "4.Flip Image.\n"
             << "5.Rotate Image.\n"        << "6.Darken and Lighten Image.\n"
             << "7.Detect Image Edges.\n"  << "8.Enlarge Image.\n"
             << "9.Shrink Image.\n"        << "a.Mirror Image.\n"
             << "b.Shuffle Image.\n"       << "c.Blur Image.\n"
             <<"0.exit.\n";
        cin >> filter;
        //check the filter that the user input it
        if (filter == '1' )
            BW_Image();
        else if (filter == '2' )
            Invert_Filter();
        else if (filter == '3' )
            RGB_merger();
        else if (filter == '4' )
            RGB_Flip();
        else if (filter == '5' )
            Rotate_Image() ;
        else if (filter == '6' )
            RGB_darkenlight();
        else if (filter == '7' )
            RGB_EdgeDetective();
        else if (filter == '8' )
            Enlarge_Image() ;
        else if (filter == '9' )
            RGB_shrink();
        else if (filter == 'a' )
            RGB_Mirror();
        else if (filter == 'b' )
           Shuffle_Filter() ;
        else if (filter == 'c' )
            RGB_blur();
        //if the user input 0 then end the program
        else if (filter == '0' ){
            cout << "M3 elsalamh ya user ya habibi \n"  ;
            break;
        }
        //if the user input filter 7,8,b then continue without save the image
       if ((filter == '7')||(filter == '8')||(filter == 'b'))
            continue;
        else
            saveImage();

    }
}

//_________________________________________
//function reads the image that user inputs it
void loadImage () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Ahlan ya user ya habibi \n""Please enter file name of the image to process \n";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);
}
//_________________________________________
//function saves the changes in the image
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
//function saves the changes in a new image
void saveImage2 () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image2);
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
//_____________________________________________________
void RGB_merger() {
    char imageFileName2[100];
    // Get colored image file name
    cout << "Enter the source image (that you want to merge with) file name: ";
    cin >> imageFileName2;

    // Add to it .bmp extension and load image
    strcat (imageFileName2, ".bmp");
    readRGBBMP(imageFileName2, image2);

// since we need two images for merge to occur, we ask the user to input a file name and then read the filename.bmp

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            for (int k=0;k<RGB; k++) { //loop through the image pixel by pixel
                image[i][j][k] = (image[i][j][k] + image2[i][j][k])/2;
		    // this takes the average of both images
            }
        }
    }
}
//_____________________________________________________
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
                for (int k=0;k<RGB;k++) { // this loops through the entire image pixel by pixel
                    if (choice == 2) {
                        newimage2[x][y][z] = image[i][j][k]; //saves the original image to an image half the original size
                    }
                    if (choice == 3) {
                        newimage3[x][y][z] = image[i][j][k]; //saves the original image to an image one third the original size
                    }
                    if (choice == 4) {
                        newimage4[x][y][z] = image[i][j][k]; //saves the original image to an image a quarter the original size
                    }
                    z++;
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k=0; k<RGB; k++) { // this loops through the entire image pixel by pixel
                    image[i][j][k] = 255; // makes the original image all white so that we can overwrite the smaller image on top of it
                }
            }
        }
        for (int i = 0; i < SIZE/choice; i++) {
            for (int j = 0; j < SIZE/choice; j++) {
                for (int k=0;k<RGB; k++) { // this loops through the entire image pixel by pixel
                    if (choice==2){
                        image[i][j][k] = newimage2[i][j][k]; //overwriting the smaller image on top
                    }
                    if (choice==3){
                        image[i][j][k] = newimage3[i][j][k]; // also overwriting here but for 1/3 dimension
                    }
                    if (choice==4){
                        image[i][j][k] = newimage4[i][j][k]; // also overwriting here but for 1/4 dimension
                    }

                }
            }
        }
    }
}
//_____________________________________________________
void RGB_blur() {
    for (int i = 1; i < SIZE-1; i++) {
        for (int j = 1; j < SIZE-1; j++) {
            for (int k=0; k<RGB;k++) { // this loops through the entire image pixel by pixel
                image[i][j][k] = ( image[i][j][k] + image[i][j+1][k] + image[i][j-1][k] + image[i+1][j][k] +image[i+1][j+1][k] +
                                   + image[i+1][j-1][k] + image[i-1][j][k] + image[i-1][j+1][k] + image[i-1][j-1][k] ) / 9;
		    // takes the average of all the 9 pixels around the pixel itself, including the pixel itself
		    // we don't average k in this loop since we don't want to change/blur the  colors of the image
            }
        }
    }
}
//_____________________________________________________
void RGB_darkenlight() {
    char choice;
    cout << "Do you want to (d)arken or (l)ighten?\n";
    cout << "Please enter d or l.\n";
    cin >> choice;
    if (choice=='d'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for (int k=0;k<RGB;k++) { // loops through the entire image pixel by pixel
                    image[i][j][k] *= 0.5; // halving the value of each pixel to make it closer to 0 (black)
                }
            }
        }
    }
    else if (choice=='l'){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0;k<RGB;k++) { // loops through the entire image pixel by pixel
                    image[i][j][k] = 0.5*(image[i][j][k]+SIZE);
			// taking the average of the value of each pixel with white (255/SIZE) to make it closer to 255 (white)
			// we can't multiply by 2 because that would give a value greater than 255 at times.

                }
            }

        }
    }
    else{
        cout << "Invalid entry.";
    }

}
//_____________________________________________________
void Invert_Filter()
{

	for (int i = 0; i < SIZE; i++)//Invert image
	    	{
					for (int j = 0; j< SIZE; j++)
					{
						for (int x = 0 ; x < 3 ; x++ )
							image[i][j][x] = 256 - image[i][j][x*2];//Invert image

					}

	      	}
}
//_____________________________________________________
void Rotate_Image()

{
	char choose ;
	cout <<  "choose the degree of rotate please : "<< endl;
	cout << "a.90"<<endl<<"b.180"<<endl<<"c.270"<<endl;
	cin >> choose ;
	if (choose == 'a' )     //Rotate 90
		{
			for (int i = 0; i < SIZE; i++)
    		{
				for (int j = 0; j< SIZE; j++)
				{
					for (int k = 0 ; k < 3 ; k ++)
						image[i][j][k] =  image[j-(340)][i-(96)][2*k-1];    //Rotate 90
				}
      		}
		}
	else if (choose == 'b')     //Rotate 180
		{
			for (int i = 0; i < SIZE; i++)
    		{
				for (int j = 0; j< SIZE; j++)
				{
					for (int x = 0 ; x < 3 ; x++ )
						image[i][j][x] =  image[i-(340)][-j-96][2*x-1];     //Rotate 180
				}
      		}
		}
		else if (choose == 'c')  //Rotate 270
		{
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j< SIZE; j++)
				{
					for (int x = 0 ; x < 3 ; x++ )

						image[i][j][x] =  image[-j-86][-i-96][2*x-1];       //Rotate 270
				}
		  	}

		}

}
//_____________________________________________________
void Enlarge_Image()
{
    char choice ;
    cout << "please enter the number of the quarter to enlarge(1,2,3,4) :";
    cin >> choice ;
   // first quarter
  if (choice == '1')    // if the user choose first quarter to enlarge
  {
      for (int i = 0 , x = 0  ; i< SIZE; x++ , i+=2)
	{ for (int j = 0 ,y = 0  ;j< SIZE; y++ , j +=2)
		{
		    for (int k = 0 ; k < 7 ; k+=2)
               {
                   //copy every pixel in first quarter in  four pixels to enlarge it
                    image2[i][j][k]=  image[x][y][k];
                    image2[i+1][j][k] = image[x][y][k];
                    image2[i][j+1][k] = image[x][y][k];
                    image2[i+1][j+1][k] = image[x][y][k];
               }
		}
    }
  }

  // second quarter
  else if (choice == '2')   // if the user choose second quarter to enlarge
  {
      for (int i = 0 , x = 0  ; i< SIZE; x++ , i+=2)
	  {
	    for (int j = 0 ,y = 128  ;j< SIZE; y++ , j +=2)
		  for (int k = 0 ; k < 7 ; k+=2)
          {
              //copy every pixel in second quarter in  four pixels to enlarge it
                image2[i][j][k]=  image[x][y][k];
                image2[i+1][j][k] = image[x][y][k];
                image2[i][j+1][k] = image[x][y][k];
                image2[i+1][j+1][k] = image[x][y][k];
          }
      }
  }
    // third quarter
  else if (choice == '3')       // if the user choose third quarter to enlarge
  {
      for (int i = 0 , x = 128  ; i< SIZE; x++ , i+=2)
	  {
        for (int j = 0 ,y = 0  ;j< SIZE; y++ , j +=2)
		  for (int k = 0 ; k < 7 ; k+=2)
          {
              //copy every pixel in third quarter in  four pixels to enlarge it
                image2[i][j][k]=  image[x][y][k];
                image2[i+1][j][k] = image[x][y][k];
                image2[i][j+1][k] = image[x][y][k];
                image2[i+1][j+1][k] = image[x][y][k];
          }
    }
  }

    // forth quarter
    else if (choice == '4')     // if the user choose forth quarter to enlarge
    {
       for (int i = 0 , x = 128 ; i< SIZE; x++ , i+=2)
       {
            for (int j = 0 ,y = 128  ;j< SIZE; y++ , j +=2)
              for (int k = 0 ; k < 7 ; k+=2)
              {
                  //copy every pixel in forth quarter in  four pixels to enlarge it

                 image2[i][j][k]=  image[x][y][k];
                 image2[i+1][j][k] = image[x][y][k];
                 image2[i][j+1][k] = image[x][y][k];
                 image2[i+1][j+1][k] = image[x][y][k];
              }
        }
    }
 saveImage2 ();
}
//_________________________________________
void the_order (int& a , int& b  ,char q)
{
    /*
    this function take number of the quarter of image1 from the user
        and return the start of loop to take this quarter and insert it
        in the new image (image2)
    */
        if (q == '1')
        a = 0 , b = 0 ;     //the start of loop
    else if (q == '2')
        a = 0 , b = 128;    //the start of loop
    else if (q == '3')
        a = 128 , b = 0 ;   //the start of loop
    else if (q == '4')
        a = 128 , b = 128 ; //the start of loop


}
//_____________________________________________________
void Shuffle_Filter()
{
    //  take the order of the quarters form the user
    char q1 , q2 ,q3 ,q4 ;
    int a = 0 , b = 0 ;
    cout << "what is the order wold you like : ";
    cin  >> q1 >> q2 >> q3 >> q4 ;
//--------------------

    the_order(a,b,q1);//chose the number of the first quarter
	for (int i = 0  , x = a; i < SIZE/2; x++ , i++)//wright the first quarter
        {
            for (int j =0 , y = b ; j< SIZE/2 ; y++ , j++)
                for (int k = 0 ; k < 6 ; k +=2)
							(image2[i][j][k]=image[x][y][k]);
        }
//--------------------
    the_order(a,b,q2);//chose the number of the first quarter
	for (int i = 0  , x = a; i < SIZE/2; x++ , i++)//wright the first quarter
        {
            for (int j =128 , y = b ; j< SIZE ; y++ , j++)
                        for (int k = 0 ; k < 6 ; k +=2)
							(image2[i][j][k]=image[x][y][k]);
        }
//--------------------

    the_order(a,b,q3);//chose the number of the third quarter
	for (int i = 128  , x = a; i < SIZE; x++ , i++)//wright the third quarter
        {
            for (int j =0 , y = b ; j< SIZE/2 ; y++ , j++)
                    for (int k = 0 ; k < 6 ; k +=2)
							(image2[i][j][k]=image[x][y][k]);
        }
//--------------------

    the_order(a,b,q4);//chose the number of the forth quarter
	for (int i = 128  , x = a; i < SIZE; x++ , i++)//wright the forth quarter
        {
            for (int j =128 , y = b ; j< SIZE ; y++ , j++)
                    for (int k = 0 ; k < 6 ; k +=2)
							(image2[i][j][k]=image[x][y][k]);
        }
    saveImage2 ();
}
//_________________________________________________________
void RGB_Flip (){
    cout << "Flip (h)orizontally or (v)ertically ? " << endl;
    char option;
    cin >> option;
    if(option == 'h'){
      for (int i = 0; i < SIZE; i++){
        for (int j = 0; j< (SIZE/2); j++){
          for(int k = 0; k < RGB; k++)
            swap(image[i][j][k] , image[i][SIZE - j][k]);
        }
      }
    }
    else if(option == 'v'){
      for (int i = 0; i < (SIZE/2); i++){
        for (int j = 0; j < SIZE; j++){
          for(int k = 0; k < RGB; k++)
            swap(image[i][j][k] , image[SIZE - i][j][k]);
        }
      }
    }
}
//_________________________________________________________
void RGB_EdgeDetective(){
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
  for(int i = 0; i < SIZE; i++){
    for(int j = 0; j < (SIZE - 1); j++){
      if(image[i][j][0] == 255){
        if(image[i][j][0] != image[i][j + 1][0]){
          for(int k = 0; k < RGB; k++){
            image2[i][j][k] = 255;
            image2[i][j + 1][k] = 0;
          }
          j += 1;
        }
        else if(image[i][j][0] == image[i][j + 1][0])
            for(int k = 0; k < RGB; k++){
              image2[i][j][k] = 255;
            }
      }
      else if(image[i][j][0] == 0){
        if((image[i][j][0] == image[i][j + 1][0]) && (image[i][j][0] == image[i - 1][j][0]) && (image[i][j][0] == image[i + 1][j][0])){
            for(int k = 0; k < RGB; k++){
              image2[i][j][k] = 255;
            }
        }
        else
          for(int k = 0; k < RGB; k++){
            image2[i][j][k] = 0;
          }
      }
    }
  }
  saveImage2();
}
//_____________________________________________________
void RGB_Mirror(){
  cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?" << endl;
  char option;
  cin >> option;
  if(option == 'l'){
    for (int i = 0; i < (SIZE); i++){
      for (int j = 0; j < SIZE/2; j++){
        for(int k = 0; k < RGB; k++){
            image[i][j][k] = image[i][SIZE - j][k];
        }
      }
    }
  }
  else if(option == 'r'){
    for (int i = 0; i < (SIZE); i++) {
      for (int j = 0; j< SIZE/2; j++) {
        for(int k = 0; k < RGB; k++){
          image[i][SIZE - j][k] = image[i][j][k];
        }
      }
    }
  }
  else if(option == 'u'){
    for (int i = 0; i < (SIZE/2); i++) {
      for (int j = 0; j< SIZE; j++) {
        for(int k = 0; k < RGB; k++){
          image[i][j][k] = image[SIZE - i][j][k];
        }
      }
    }
  }
  else if(option == 'd'){
    for (int i = 0; i < (SIZE/2); i++) {
      for (int j = 0; j< SIZE; j++) {
        for(int k = 0; k < RGB; k++){
          image[SIZE - i][j][k] = image[i][j][k];
        }
      }
    }
  }
}
