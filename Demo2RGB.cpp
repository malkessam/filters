// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
unsigned char result[SIZE][SIZE][RGB];
unsigned char edged[SIZE][SIZE][RGB];


void loadImage ();
void saveImage ();
void saveImageE();
void blackAwhite ();
void FlipImage ();
void EDGING();
void Mirror();
void cropImage();

int main()
{
    int num;
    cout<<"enter a number:";
    cin>>num;
    if(num ==1){
        loadImage();
        blackAwhite();
        saveImage();
    }
    if (num==2){
        loadImage();
        FlipImage();
        saveImage();
    }
    if(num==3){
        loadImage();
        EDGING();
        saveImageE();
    }
    if(num==4){
        loadImage();
        Mirror();
        saveImage();

    }
    if(num==5){
        loadImage();
        cropImage();
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
void saveImageE () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, edged);
}

//_________________________________________
/*void blackAwhite() {
    int sum;
    for(int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            sum = 0;

            for (int k= 0; k < RGB; k++)
            {
                image1[i][j][k] = image[i][j][k];
                sum += image1[i][j][k];
            }

            sum = sum/3;

            if (sum > 127) {
                for (int k = 0; k < RGB; k++) {
                    image1[i][j][k] = 255;
                }
            }
            else {
                for (int k = 0; k < RGB; k++) {

                    image1[i][j][k] = 0;
                }
            }

        }
    }


   /* for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                //scaling up every bit more than 127 to 255(white)
                if (image[i][j][k] > 127)
                    image[i][j][k] = 255;
                else
                    //scalling down every bit less than 127 to 0(black)
                    image[i][j][k] = 0;

            }
        }

    }*/

void FlipImage()
{
    char choice;
    cout << "Press (h) to flip horizontally , (v) to flip vertically " << endl;
    cin >> choice;
    if (choice == 'h') {
        for (int k = 0; k < SIZE; k++) {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    result[i][j][k] = image[SIZE - i][SIZE - j][k];
                }
            }
        }
    }
        else if (choice == 'v') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    result[j][i][k] = image[j][SIZE - i][k];

                }
            }
        }
    }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < SIZE; k++) {
                    image[i][j][k] = result[i][j][k];
                }
            }
        }
    }

void EDGING() {
    //1- convert greyscale to black and white
    for (int k = 0; k < SIZE; k++) {
        for (int i = 1; i < SIZE - 1; i++) {
            for (int j = 1; j < SIZE - 1; j++) {
                //convert to black and white
                if (image[i][j][k] > 127)
                    image[i][j][k] = 255;
                else
                    image[i][j][k] = 0;
            }
        }
        for (int k = 0; k < SIZE; k++) {
            for (int i = 1; i < SIZE - 1; i += 1) {
                for (int j = 1; j < SIZE - 1; j += 1) {
                    //2- check detection of current pixel against before/after pixels
                    if (image[i][j][k] == image[i][j + 1][k] and image[i][j][k] == image[i][j - 1][k]) {
                        //set value to white
                        edged[i][j][k] = 255;
                    } else {
                        //set value to black
                        edged[i][j][k] = 0;
                    }
                }
            }
        }
    }
void Mirror() {
    char c1, c2;

    cout << "Choose whether you want to mirror the image horizontally (enter 'h') or vertically (enter 'v')" << endl;
    cin >> c1;
    if (c1 == 'v') {
        cout << "Choose either the left part (l) or the right part (r)" << endl;
        cin >> c2;
        if (c2 == 'l') {
            for (int k = 0; k < SIZE; k++) {
                for (int i = 0; i < SIZE; i++) {
                    // half size of vertical mirror
                    for (int j = 0; j < SIZE / 2; j++) {
                        int temp = image[i][j][k];
                        //check if first half
                        if (j < SIZE / 2)
                            image[i][SIZE - j][k] = temp;
                    }
                }
            }
            if (c2 == 'r') {
                for (int k = 0; k < SIZE; k++) {
                    for (int i = 0; i < SIZE; i++) {
                        // half size of vertical mirror
                        for (int j = 0; j < SIZE / 2; j++) {
                            image[i][j][k] = image[i][SIZE - j][k];

                        }
                    }
                }

            }
            if (c1 == 'h') {
                cout << "Choose either the upper part (enter 'u') or the lower part (enter 'l')" << endl;
                cin >> c2;
                if (c2 == 'u') {
                    for (int k = 0; k < SIZE; k++) {
                        // half size of horizontal mirror
                        for (int i = 0; i < SIZE / 2; i++) {
                            for (int j = 0; j < SIZE; j++) {
                                int temp = image[i][j][k];
                                image[SIZE - i][j][k] = temp;
                            }
                        }
                    }
                    if (c2 == 'l') {
                        for (int k = 0; k < SIZE; k++) {
                            // half size of horizontal mirror
                            for (int i = 0; i < SIZE / 2; i++) {
                                for (int j = 0; j < SIZE; j++) {
                                    image[i][j][k] = image[SIZE - i][j][k];
                                }
                            }
                        }

                    }
                }
void cropImage() {
    int x, y;
    cout << "Enter vertical cropping value: "<<endl;
    cin >> x;
    cout << "Enter horizontal cropping value: "<<endl;
    cin >> y;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++)
            {
            image[i][j][k] = 255;
        }
    }
    for (int i = SIZE - x; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++)
            {
            image[i][j][k] = 255;
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < SIZE; k++)
            {
            image[i][j][k] = 255;

        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - y; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++)
            {
            image[i][j][k] = 255;
        }
    }
}
            }