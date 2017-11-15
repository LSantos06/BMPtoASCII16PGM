/*
 * Software that converts a bpm image file into a image pgm file
 * Lucas Santos 2017
 */ 


/* 
 * The plain pgm format is:
 *
 *   - There is exactly one image in a file.
 *   - The magic number is P2 instead of P5.
 *   - Each pixel in the raster is represented as an ASCII decimal number between 0 and 65535.
 *   - Each pixel in the raster has white space before and after it. There must be at least one character of white space between any two pixels, but there is no maximum.
 *   - No line should be longer than 70 characters. 
 *
 * Here is an example of a small image in the plain PGM format.
 *
 * P2
 * # feep.pgm
 * 24 7
 * 15
 * 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 * 0  3  3  3  3  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15 15 15 15  0
 * 0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0 15  0
 * 0  3  3  3  0  0  0  7  7  7  0  0  0 11 11 11  0  0  0 15 15 15 15  0
 * 0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0  0  0
 * 0  3  0  0  0  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15  0  0  0  0
 * 0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
 *
 * There is a newline character at the end of each of these lines.
 *
 */

#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iterator>

using namespace std;

// https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
unsigned char* ReadBMP(char* filename) {
    // file pointer
    int i;
    FILE* f = fopen(filename, "rb");

    if(f == NULL)
        throw "Argument Exception";

    // header
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    // print 
    cout << endl;
    cout << "  Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << "Height: " << height << endl;

    // padding the row
    int row_padded = (width*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    // bottom to top order
    if (height > 0) {
        // ascendent
        for(int i = 0; i < height; i++) {
            fread(data, sizeof(unsigned char), row_padded, f);
            for(int j = 0; j < width*3; j += 3) {
                // Convert (B, G, R) to (R, G, B)
                tmp = data[j];
                data[j] = data[j+2];
                data[j+2] = tmp;

                //cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
            }
        }
    }
    // top to bottom order
    if (height < 0) {
        height = -height;
        // descendent
        for(int i = height; i > 0; i--) {
            fread(data, sizeof(unsigned char), row_padded, f);
            for(int j = 0; j < width*3; j += 3) {
                // Convert (B, G, R) to (R, G, B)
                tmp = data[j];
                data[j] = data[j+2];
                data[j+2] = tmp;

                //cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
            }
        }
    }

    // close pointer and return data
    fclose(f);
    return data;
}

/*inline void Save(const std::string& filename, const Image1ui16& img) {
	if(!boost::algorithm::ends_with(filename, ".pgm")) {
		throw IoException(filename, "Save for 1ui16 images can only handle PGM files");
	}
	std::ofstream ofs(filename);
	ofs << "P2" << std::endl;
	ofs << img.width() << " " << img.height() << std::endl;
	ofs << "65535" << std::endl;
	for(unsigned int y=0; y<img.height(); y++) {
		for(unsigned int x=0; x<img.width(); x++) {
			ofs << img(x,y);
			if(x+1 < img.width()) {
				ofs << " ";
			}
		}
		if(y+1 < img.height()) {
			ofs << std::endl;
		}
	}
}*/

int main() {
    unsigned char* pixels;
    char* filename;

    filename = "KinectScreenshot-Depth-03-36-42.bmp";

    pixels = ReadBMP(filename);

    return 0;
}