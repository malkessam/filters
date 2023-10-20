#include <iostream>
#include <cstring>
#include "bmplib.cpp"
#include<cmath>

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image1[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char ans[SIZE][SIZE];
unsigned char newimage[SIZE][SIZE];
unsigned char edged[SIZE][SIZE];

void loadImage ();
void loadImage1 ();
void getimg();
void saveImage ();
void saveImageE();
void merge();
void darklight();
void shrink();
void blur();
void skew_vertical();


int main()
{
    int number;
    cout<<"select a filter: "<<endl
        <<"3-merge"<<endl
        <<"6-darken and lighten image"<<endl
        <<"7-shrink"<<endl
        <<"8-blur"<<endl;
        <<"15-skew vertical"
    cout<<"enter a number:";
    cin>>number;
    if(number==3) {
        loadImage();
        loadImage1();
        merge();
        saveImage();
    }

    if(number==6) {
        loadImage();
        darklight();
        saveImage();
    }
    if(number==9){
        getimg();
        shrink();
        saveImage();
    }
    if (number==12){
        loadImage();
        blur();
        saveImage();
    }
    if (number==15){
        loadImage();
        skew_vertical();
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
    readGSBMP(imageFileName, image);
}
void getimg(){
    char imageFileName[100];
    cout<<"enter the image u want to shrink:";
    cin>>imageFileName;
    strcat(imageFileName,".bmp");
    readGSBMP(imageFileName,newimage);
}
void loadImage1 () {
    char imageFileName1[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName1;

    // Add to it .bmp extension and load image
    strcat (imageFileName1, ".bmp");
    readGSBMP(imageFileName1, image1);
}


//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}


//_________________________________________



void merge() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            image[i][j]=(image[i][j]+image1[i][j])/2;

        }

    }
}


void darklight() {
    int value;
    cout<<"if you want darken->1 lighten->2:"<<" ";
    cin>>value;
    if(value==1){

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {

                image[i][j] *= 0.5;
            }

        }if (value==2){ for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {

                    image[i][j] += (255 - image[i][j]) * 0.5; /*in this we add the difference between tha max value and the current value
                  *  and multiply it by 0.5 to increase the brightness of the entire image.
                */
                }

            }

        }

    }
}


//_________________________________________
void shrink() {
    int choice;
    cout << "for 1/4 ->1\nfor 1/3 ->2\nfor 1/2 ->3\nenter:";
    cin >> choice;
    if (choice == 1) {
        for (int i = 0; i < SIZE; i += 2) {
            for (int j = 0; j < SIZE; j += 2) {
                image[i / 2][j / 2] = newimage[i][j];
            }

        }

    } else if (choice == 2) {
        for (int i = 0; i < SIZE; i += 3) {
            for (int j = 0; j < SIZE; j += 3) {
                image[i / 3][j / 3] = newimage[i][j];
            }
        }
    } else if (choice == 3) {
        for (int i = 0; i < SIZE; i += 4) {
            for (int j = 0; j < SIZE; j += 4) {
                image[i / 4][j / 4] = newimage[i][j];
            }
        }
    }
}


void blur() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++)
            image[i + 1][j + 1] =
                    (image[i][j] + image[i][j + 1] + image[i][j + 2] + image[i + 1][j] + image[i + 1][j + 1] +
                        image[i + 1][j + 2] + image[i + 2][j] + image[i + 2][j + 1] + image[i + 2][j + 2]) / 9;

    }
}


void skew_vertical() {
    cout << "Enter Skew angle: ";
    double angle;
    cin >> angle;
    unsigned char tmp[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            tmp[i][j] = 255;
        }
    }

    double l = tan(angle * 3.14 / 180.0) * SIZE;
    double cmprs = SIZE / (SIZE - l);
    double step = l / 256;
    double taken = 0;
    for (int j = 0; j < SIZE; j++) {
        double current = 0;
        for (int i = l
                    - taken; i < SIZE - taken; i++) {
            int average = 0;
            int px = 0;
            for (int k = max(0, (int) ceil(current - cmprs)); k < min(SIZE, (int) ceil(current + cmprs)); k++, ++px) {
                average += image[k][j];
            }
            average /= max(1, px);
            tmp[i][j] = average;
            current += cmprs;
        }
        taken += step;
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            image[i][j]=tmp[i][j];
}
