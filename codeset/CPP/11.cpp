#include<sys/time.h>
#include<stdio.h>
#include<stdlib.h>

#include<openacc.h>

//================================================
// ppmFile.h
//================================================
#include <sys/types.h>
typedef struct Image
{
  int width;
  int height;
  unsigned char *data;
} Image;
Image *ImageRead(char *filename);
void   ImageWrite(Image *image, char *filename);
int    ImageWidth(Image *image);
int    ImageHeight(Image *image);
void   ImageSetPixel(unsigned char *data, int width, int x, int y, int chan, unsigned char val);
unsigned char ImageGetPixel(unsigned char *data, int width, int x, int y, int chan);


//================================================
// The Blur Filter
//================================================
void ProcessImageACC(Image **data, int filterRad, Image **output){
    //process the image
    int width = (*data)->width;
    int height = (*data)->height;
    unsigned char *arrIn = (*data)->data;
    unsigned char *arrOut = (*output)->data;
    int minX, maxX, minY, maxY;
    int blurWidth, blurHeight;
    int numPixel;
    long redTotal, greenTotal, blueTotal;
    unsigned char newRed, newGreen, newBlue;
    int m, n;

    #pragma acc parallel loop copyin(arrIn[0:(width*height*3)]) copy(arrOut[0:(width*height*3)])
        for(int j = 0; j < height; j++){
            #pragma acc loop
            for(int i = 0; i < width; i++){

                redTotal = 0;
                greenTotal = 0;
                blueTotal = 0;

                //compute blur radius, keeping in mind boundaries of picture
                maxX = (((i + filterRad)/width)*width) + ((1-((i + filterRad)/width))*(i + filterRad));
                maxY = (((j + filterRad)/height)*height) + ((1-((j + filterRad)/height))*(j + filterRad));
                minX = (i - filterRad > 0) ? i - filterRad : 0;
                minY = (j - filterRad > 0) ? j - filterRad : 0;
                //maxX = (i + filterRad < width) ? i + filterRad : width;
                //maxY = (j + filterRad < height) ? j + filterRad : height;
                blurWidth = maxX-minX+1;
                blurHeight = maxY-minY+1;
                numPixel = blurWidth * blurHeight;

                #pragma acc loop reduction(+: redTotal) reduction(+: greenTotal) reduction(+: blueTotal)
                for (int k = 0; k < numPixel; k++) {
                    //calculate totals for each RGB colour iterating through pixels in blur radius column by column
                    m = minX + (k%blurHeight);
                    n = minY + (int)(k/blurHeight); //only want integer portion of k/blurHeight, round down
                    redTotal += (int)ImageGetPixel(arrIn, width, m, n, 0);
                    greenTotal += (int)ImageGetPixel(arrIn, width, m, n, 1);
                    blueTotal += (int)ImageGetPixel(arrIn, width, m, n, 2);
                }

                //compute blurred RGB values and set pixels in output image
                newRed = redTotal/numPixel;
                newGreen = greenTotal/numPixel;
                newBlue = blueTotal/numPixel;
                ImageSetPixel(arrOut, width, i, j, 0, newRed);
                ImageSetPixel(arrOut, width, i, j, 1, newGreen);
                ImageSetPixel(arrOut, width, i, j, 2, newBlue);
            }
        }

    //copy blurred data array into output Image struct
    (*output)->data = arrOut;
}


//================================================
// Main Program
//================================================
int main(int argc, char* argv[]){
    //vars used for processing:
    Image *data, *result;
    int dataSize;
    int filterRadius = atoi(argv[1]);
    struct timeval start, end;
    double time;

    //===read the data===
    data = ImageRead(argv[2]);

    //===send data to nodes===
    //send data size in bytes
    dataSize = sizeof(unsigned char)*data->width*data->height*3;

    //===process the image===
    //allocate space to store result
    result = (Image*)malloc(sizeof(Image));
    result->data = (unsigned char*)malloc(dataSize);
    result->width = data->width;
    result->height = data->height;

    //initialize all to 0
    for(int i = 0; i < (result->width*result->height*3); i++){
        result->data[i] = 0;
    }

    gettimeofday(&start, NULL);
    //apply the filter
    ProcessImageACC(&data, filterRadius, &result);
    gettimeofday(&end, NULL);
    time = end.tv_sec-start.tv_sec+(end.tv_usec-start.tv_usec)*1e-6;

    //===save the data back===
    ImageWrite(result, argv[3]);

    printf("%f\n", time);

    return 0;
}


//================================================
// ppmFile.c
//================================================
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/************************ private functions ****************************/
/* die gracelessly */
static void die(char *message){
  fprintf(stderr, "ppm: %s\n", message);
  exit(1);
}
/* check a dimension (width or height) from the image file for reasonability */
static void checkDimension(int dim){
  if (dim < 1 || dim > 4000) 
    die("file contained unreasonable width or height");
}
/* read a header: verify format and get width and height */
static void readPPMHeader(FILE *fp, int *width, int *height){
  char ch;
  int  maxval;
  if (fscanf(fp, "P%c\n", &ch) != 1 || ch != '6') 
    die("file is not in ppm raw format; cannot read");
  /* skip comments */
  ch = getc(fp);
  while (ch == '#')
    {
      do {
	ch = getc(fp);
      } while (ch != '\n');	/* read to the end of the line */
      ch = getc(fp);            /* thanks, Elliot */
    }
  if (!isdigit(ch)) die("cannot read header information from ppm file");
  ungetc(ch, fp);		/* put that digit back */
  /* read the width, height, and maximum value for a pixel */
  fscanf(fp, "%d%d%d\n", width, height, &maxval);
  if (maxval != 255) die("image is not true-color (24 bit); read failed");
  checkDimension(*width);
  checkDimension(*height);
}
Image *ImageRead(char *filename){
  int width, height, num, size;
  unsigned  *p;
  Image *image = (Image *) malloc(sizeof(Image));
  FILE  *fp    = fopen(filename, "r");
  if (!image) die("cannot allocate memory for new image");
  if (!fp)    die("cannot open file for reading");
  readPPMHeader(fp, &width, &height);
  size          = width * height * 3;
  image->data   = (unsigned  char*) malloc(size);
  image->width  = width;
  image->height = height;
  if (!image->data) die("cannot allocate memory for new image");
  num = fread((void *) image->data, 1, (size_t) size, fp);
  if (num != size) die("cannot read image data from file");
  fclose(fp);
  return image;
}
void ImageWrite(Image *image, char *filename){
  int num;
  int size = image->width * image->height * 3;
  FILE *fp = fopen(filename, "w");
  if (!fp) die("cannot open file for writing");
  fprintf(fp, "P6\n%d %d\n%d\n", image->width, image->height, 255);
  num = fwrite((void *) image->data, 1, (size_t) size, fp);
  if (num != size) die("cannot write image data to file");
  fclose(fp);
} 
int ImageWidth(Image *image){
  return image->width;
}
int ImageHeight(Image *image){
  return image->height;
}
#pragma acc routine
void ImageSetPixel(unsigned char *data, int width, int x, int y, int chan, unsigned char val){
  int offset = (y * width + x) * 3 + chan;
  data[offset] = val;
}
#pragma acc routine
unsigned char ImageGetPixel(unsigned char *data, int width, int x, int y, int chan){
  int offset = (y * width + x) * 3 + chan;
  return data[offset];
}