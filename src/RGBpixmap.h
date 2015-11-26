#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class RGB{ // holds a color triple, each with 256 possible intensities
    public: unsigned char r,g,b;
};

// The RGBpixmap class stores the number of rows and columns in
// the pixmap, as well as the address of the first pixel in memory:

class RGBpixmap{
  public:
    int nRows, nCols;       // dimensions of the pixmap
    RGB* pixel;             // array of pixels
    int readBMPFile(char* fname);       // read BMP file into this pixmap
    void makeCheckerboard();
    void makeCheckerboard1();
    void makeCheckerboard2();
    void setTexture(GLuint textureName);
};

void RGBpixmap:: makeCheckerboard()
{  // make checkerboard patten
    nRows = nCols = 64;
    pixel = new RGB[3 * nRows * nCols];
    if(!pixel) {cout << "out of memory!"; return;}
    long count = 0;
    for(int i = 0; i < nRows; i++)
        for(int j = 0; j < nCols; j++)
        {
            int c = (((i/8) + (j/8)) %2) * 255;
            pixel[count].r = c; 	// red
            pixel[count].g = c; 	// green
            pixel[count++].b = 0; 	// blue
        }
}

void RGBpixmap:: makeCheckerboard1()
{  // make checkerboard patten
    nRows = nCols = 64;
    pixel = new RGB[3 * nRows * nCols];
    if(!pixel) {cout << "out of memory!"; return;}
    long count = 0;
    for(int i = 0; i < nRows; i++)
        for(int j = 0; j < nCols; j++)
        {
            int c = (((i/8) + (j/8)) %2) * 255;
            pixel[count].r = c; 	// red
            pixel[count].g = c; 	// green
            pixel[count++].b = c; 	// blue ****
        }
}

void RGBpixmap:: makeCheckerboard2()
{  // make checkerboard patten
    nRows = nCols = 64;
    pixel = new RGB[3 * nRows * nCols];
    if(!pixel) {cout << "out of memory!"; return;}
    long count = 0;
    for(int i = 0; i < nRows; i++)
        for(int j = 0; j < nCols; j++)
        {
            int c = (((i/8) + (j/8)) %2) * 255;
            pixel[count].r = 0; 	// red ****
            pixel[count].g = c; 	// green
            pixel[count++].b = c; 	// blue ****
        }
}


void RGBpixmap :: setTexture(GLuint textureName)
{
    glBindTexture(GL_TEXTURE_2D,textureName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,nCols,nRows,0, GL_RGB,
             GL_UNSIGNED_BYTE, pixel);
}

//
// RGBpixmap.cpp - routines to read a BMP file
//#include "RGBpixmap.h"
//
typedef unsigned short ushort;
typedef unsigned long ulong;
fstream inf; // global in this file for convenience
//<<<<<<<<<<<<<<<<<<<<< getShort >>>>>>>>>>>>>>>>>>>>
ushort getShort() //helper function
{ //BMP format uses little-endian integer types
  // get a 2-byte integer stored in little-endian form
    char ic;
    ushort ip;
    inf.get(ic); ip = ic;  //first byte is little one
    inf.get(ic);  ip |= ((ushort)ic << 8); // or in high order byte
    return ip;
}
//<<<<<<<<<<<<<<<<<<<< getLong >>>>>>>>>>>>>>>>>>>
ulong getLong() //helper function
{  //BMP format uses little-endian integer types
   // get a 4-byte integer stored in little-endian form
    ulong ip = 0;
    char ic = 0;
    unsigned char uc = ic;
    inf.get(ic); uc = ic; ip = uc;
    inf.get(ic); uc = ic; ip |=((ulong)uc << 8);
    inf.get(ic); uc = ic; ip |=((ulong)uc << 16);
    inf.get(ic); uc = ic; ip |=((ulong)uc << 24);
    return ip;
}
//<<<<<<<<<<<<<<<<<< RGBPixmap:: readBmpFile>>>>>>>>>>>>>
//int RGBpixmap:: readBMPFile(string fname)
int RGBpixmap:: readBMPFile(char* fname)
{  // Read into memory an RGB image from an uncompressed BMP file.
   // return 0 on failure, 1 on success
    fstream inf;

    //inf.open(fname.c_str(), ios::in|ios::binary); //read binary char's
    inf.open(fname, ios::in|ios::binary); //read binary char's
    if(!inf){ cout << inf << " can't open file: " << fname << endl; return 0;}
    cout << "here0" << endl;
    int k, row, col, numPadBytes, nBytesInRow;
    // read the file header information
    char ch1, ch2;
    inf.get(ch1); inf.get(ch2); //type: always 'BM'
    ulong fileSize = getLong();
    ushort reserved1 = getShort();    // always 0
    ushort reserved2 = getShort();    // always 0
    ulong offBits = getLong();    // offset to image - unreliable
    ulong headerSize = getLong(); // always 40
    ulong numCols = getLong();    // number of columns in image
    ulong numRows = getLong();    // number of rows in image
    ushort planes = getShort();      // always 1
    ushort bitsPerPixel= getShort();    //8 or 24; allow 24 here
    ulong compression = getLong();      // must be 0 for uncompressed
    ulong imageSize = getLong();       // total bytes in image
    ulong xPels = getLong();    // always 0
    ulong yPels = getLong();    // always 0
    ulong numLUTentries = getLong();    // 256 for 8 bit, otherwise 0
    ulong impColors = getLong();       // always 0
    cout << "here1" << bitsPerPixel << endl;
    if(bitsPerPixel != 24)
    { // error - must be a 24 bit uncompressed image
        cout << "not a 24 bit/pixelimage, or is compressed!\n";
        inf.close(); return 0;
    }
    cout << "here1.1" << endl;
    cout << numRows << numCols << endl;
    //add bytes at end of each row so total # is a multiple of 4
    // round up 3*numCols to next mult. of 4
    nBytesInRow = ((3 * numCols + 3)/4) * 4;
    numPadBytes = nBytesInRow - 3 * numCols; // need this many
    nRows = numRows; // set class's data members
    nCols = numCols;
    pixel = new RGB[nRows * nCols]; //make space for array
    if(!pixel) {cout << "pls" << endl; return 0;} // out of memory!
    long count = 0;
    char dum;
    cout << "here2" << endl;

    for(row = 0; row < nRows; row++) // read pixel values
    {
        for(col = 0; col < nCols; col++)
        {
            char r,g,b;
            inf.get(b); inf.get(g); inf.get(r); //read bytes
            pixel[count].r = r; //place them in colors
            pixel[count].g = g;
            pixel[count++].b = b;
        }
        for(k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
            inf >> dum;
    }
    inf.close(); return 1; // success
}

