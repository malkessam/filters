#include <iostream>
#include <cstring>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image1[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE];
unsigned char ans[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE][RGB];


void loadImage ();
void loadImage1 ();
void getimg();
void saveImage ();
void blackWhite();
void merge();
void darklight();
void shrink();
void blur();


int main() {
    int number;
    cout << "select a filter from 1 to 6:" << endl
         << "1-black and white:" << endl
         << "2-invert" << endl
         << "3-merge" << endl
         << "4-flip image" << endl
         << "5-rotate image" << endl
         << "6-darken and lighten image" << endl
         << "7-shrink" << endl
         << "8-blur" << endl;
    cout << "enter a number:";
    cin >> number;


    if (number == 6) {
        loadImage();
        darklight();
        saveImage();
    }
    if (number == 7) {
        loadImage();
        loadImage1();
        merge();
        saveImage();
    }if (number == 8) {
        loadImage();
        blur();
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
    readRGBBMP(imageFileName,image);

}
void getimg(){
    char imageFileName[100];
    cout<<"enter the image u want to shrink:";
    cin>>imageFileName;
    strcat(imageFileName,".bmp");
    readRGBBMP(imageFileName,newimage);
}
void loadImage1 () {
    char imageFileName1[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName1;

    // Add to it .bmp extension and load image
    strcat (imageFileName1, ".bmp");
    readRGBBMP(imageFileName1,image1);
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

void merge(){
    for (int k = 0; k < RGB; k++)
    {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                image[i][j][k]= (image [i][j][k] + image1[i][j][k]) /2;
            }
        }
    }

}

void darklight(){int value;
    cout<<"if you want darken->1 lighten->2:"<<" " ;cin>>value;
    if(value==1){

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++){

                    image[i][j][k]*=0.5;
                }

            }     }}if (value==2){for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++){

                    image[i][j][k] += (255 - image[i][j][k]) * 0.5;
                }

            }

        }
    }
}
void shrink(){
    int choice;
    cout<<"for 1/4 ->1\nfor 1/3 ->2\nfor 1/2 ->3\nenter:" ;
    cin>>choice;
    for (int k = 0; k < RGB; k++)
    {
        if (choice==1){
            for (int i = 0; i < SIZE ; i+=2)
            {
                for (int j = 0; j < SIZE; j+=2)
                {
                    image[i/2][j/2][k]=newimage[i][j][k];
                }

            }

        }else if (choice == 2)
        {
            for (int i = 0; i < SIZE; i+=3)
            { for (int j = 0; j < SIZE; j+=3)
                {
                    image[i/3][j/3][k] = newimage[i][j][k];
                }
            }
        }else if (choice == 3)
        {
            for (int i = 0; i < SIZE; i+=4)
            { for (int j = 0; j < SIZE; j+=4)
                {
                    image[i/ 4][j/4][k] = newimage[i][j][k];
                }
            }
        }
    }

}
void blur(){
    for (int k = 0; k < RGB; k++)
    {
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){//getting the averge to blur each pixel.
                image[i+1][j+1][k]=(image[i][j][k]+image[i][j+1][k]+image[i][j+2][k]+image[i+1][j][k]+image[i+1][j+1][k]+image[i+1][j+2][k]+image[i+2][j][k]+image[i+2][j+1][k]+image[i+2][j+2][k])/9;
            }
        }
    }
}