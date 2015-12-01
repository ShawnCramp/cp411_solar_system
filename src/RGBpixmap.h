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
    void setTexture(GLuint textureName);
    void parseFile();
};


void RGBpixmap :: setTexture(GLuint textureName)
{
    glBindTexture(GL_TEXTURE_2D,textureName);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,nCols,nRows,0, GL_RGB,
             GL_UNSIGNED_BYTE, pixel);
}

/**
* parseFile - reads "params.txt" and store its contents into a[i], b[i]... p[i]
*/
void RGBpixmap::parseFile() {
	string line;
	string delimeter = ",";
	ifstream myfile("images/pixels.txt");
	string token;
	double t;
	long i=0; //line count
	long counter=0;
	int r=0;
	int g=0;
	int b=0;


	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			size_t pos = 0;
			int columns = 1;

			while ((pos = line.find(delimeter)) != string::npos) {
				token = line.substr(0, pos);
				//read image dimension if i==0/1
				if (i==0) {
					t = atoi(token.c_str());
					nRows = t;
				} else if (i==1) {
					t = atoi(token.c_str());
					nCols = t;
					pixel = new RGB[3 * nRows * nCols];
				} else { //parse the rest
					t = atoi(token.c_str());
					if (columns%3==1) {
						r=t;
					} else if (columns%3==2) {
						g=t;
					} else if (columns%3==0) {
						b=t;
						pixel[counter].r=r;
						pixel[counter].g=g;
						pixel[counter++].b= b;
						columns=0;
					}
					columns++;
				}
				i++;
				line.erase(0, pos + delimeter.length());
			}
		}
		myfile.close();
	}

	else cout << "Error-cannot open file";
}

