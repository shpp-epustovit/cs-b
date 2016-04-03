#include<iostream>
#include "gwindow.h"
#include "gobjects.h"
#include "gbufferedimage.h"

using namespace std;

/* Сonstants */
const int BACKGROUND = 14474460; // Gainsboro color for background

/* Function prototypes */
static void printHelp();
void getPixelFromImage(int **pixelMap, int height, int width, GBufferedImage* imgBuffer);
void putMask(int y, int x, int newMask, int baseMask, int **pixelMap, int height, int width);
int howManySilhouettes(string filename);

char sourceFileName[50] = "";



int main() {

    char operation;
    printHelp();

    while (true){
        cout << endl << "Enter the operation: ";
        cin >> operation;
        if(operation == 'q' || operation == 'Q'){
            cout << "Goodbye. Pres Alt+F4 to close the window.";
            exit(EXIT_SUCCESS);
        }else if (operation == 'd' || operation == 'D'){
            cout << "Enter file name: ";
            cin >> sourceFileName;
            cout << "Result: " << howManySilhouettes(sourceFileName) << " silhouettes in the image " << sourceFileName<< endl;
        }else{
            cout << "\nYou made a mistake. Please try again." << endl;
        }
    }

    return 0;
}

/**
 * Function: printHelp
 * Usage: printHelp()
 * ------------------------------------------------------------------------------------------
 * The function prints the prompt to use the program
 */
static void printHelp()
{
    cout << "This is a simple program to determine the number of silhouettes on a black and white image.\n\n" << endl;
    cout << "Select the operation:\n";
    cout << "D - to determine the number of silhouettes\n";
    cout << "Q - to exit \n\n";
}


/**
 * Function: getPixelFromImage
 * Usage: getPixelFromImage(int **bitMap, int imgHeight, int imgWidth, GBufferedImage* imgBuffer)
 * @param pixelMap - a pixelmap of image
 * @param height - height of the image
 * @param width - width of the image
 * @param imgBuffer -  matrix of colored pixels
 * ------------------------------------------------------------------------------------------
 * Separate silhouettes from background
 */
void getPixelFromImage(int **pixelMap, int height, int width, GBufferedImage* imgBuffer){
    int pixelRGB = 0;
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            pixelRGB = imgBuffer->getRGB(x, y);
            if(pixelRGB > BACKGROUND){
                pixelMap[y][x] = 0;
            }
            else {
                pixelMap[y][x] = 1;
            }
        }
    }
}



/**
 * Function: putMask
* Usage: putMask(y, x, newMask, baseMask, pixelMap, height, width);
 * @param y - "y" coordinates of the pixelmap
 * @param x - "x" coordinates of the pixelmap
 * @param newMask - used for separation pixels of the silhouettes
 * @param baseMask - used for marking pixels of the silhouettes
 * @param pixelMap - a pixelmap of image
 * @param height - height of the image
 * @param width - width of the image
 * ------------------------------------------------------------------------------------
 * the function recursively builds a mask image
 */
void putMask(int y,int x,int newMask,int baseMask,int **pixelMap,int height,int width){
    if(x >= 0 && x < width && y >= 0 && y < height && pixelMap[y][x] == baseMask && pixelMap[y][x] != newMask){
        pixelMap[y][x] = newMask;
        putMask(y, x+1, newMask, baseMask, pixelMap, height, width);
        putMask(y, x-1, newMask, baseMask, pixelMap, height, width);
        putMask(y-1, x, newMask, baseMask, pixelMap, height, width);
        putMask(y+1, x, newMask, baseMask, pixelMap, height, width);
    }
}

/**
 * Function: howManySilhouettes
 * Usage: howManySilhouettes(string filename)
 * @param filename - name of the input file
 * @return number of silhouettes
 * ---------------------------------------------------
 * Function counting silhuettes
 */
int howManySilhouettes(string filename){

    GImage* image;
    image = new GImage(filename);


    GWindow gw(image->getWidth(),image->getHeight());   // open image
    gw.add(image);

    GBufferedImage* BuffImage = new GBufferedImage(0, 0, image->getWidth(), image->getHeight());
    BuffImage->load(filename);
    int height = (int)BuffImage->getHeight();
    int width = (int)BuffImage->getWidth();


    int **pixelMap = new int *[height];
    for(int y = 0; y < height; y++){
        pixelMap[y] = new int[width];
    }


    getPixelFromImage(pixelMap, height, width, BuffImage);

    int result = 0;
    int newMask = 1;
    int baseMask = 1;

    /*search silhouettes*/
    for(int y = 1; y < height; y++){
        for(int x = 1; x < width; x++){
            if(pixelMap[y][x] == 1){
                newMask++;
                result++;
                putMask(y, x, newMask, baseMask, pixelMap, height, width);
            }
        }
    }

    for(int y = 0; y < height; y++){
        delete[]pixelMap[y];
    }



    delete []pixelMap;
    delete image;
    delete BuffImage;

    return result;
}
