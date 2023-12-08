// Angelina Toste

/*
 * this program will open an image file, determine how many bytes it has, extract the hidden msg by determining
 * if the LSB of each set of 8 bits of the img are 1s or 0s.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef unsigned char uchar;

/****************************************/
/* Clear PGM (XV) comments.             */
/****************************************/
void pgmCommentClear(FILE *disk){
uchar  ch;
   fread(&ch, 1, 1, disk);
   if (ch != '#') {
      fseek(disk, -1, SEEK_CUR);
      return;
   }
   do {
      while (ch != '\n') fread(&ch, 1, 1, disk);
   } while (ch == '#');
   pgmCommentClear(disk);
}

/****************************************/
/* Read PGM formatted image (1D array). */  // note that Image is an array
/****************************************/
uchar *PGM_FILE_READ_1D(char *FileName, int *Width, int *Height, int *color) {
int   pmax;
char  ch;
char  type[3];
uchar *Image;
FILE *disk;
   // open file for reading binary
   if ((disk = fopen(FileName, "rb")) == NULL) {
      return NULL; // if file is not found
   }
   fscanf(disk, "%s", type); // reading the magic number
   if (!strcmp(type, "P6")) *color = 1;
                       else *color = 0;
   fread(&ch, 1, 1, disk);
   pgmCommentClear(disk);
   fscanf(disk, "%d", Width);
   fscanf(disk, "%d", Height);
   fscanf(disk, "%d", &pmax);
   fread(&ch, 1, 1, disk);
   if (*color == 1) {
      Image = (uchar *)calloc(*Height * *Width * 3, sizeof(uchar)); // allocate memory for the unsigned char array
      fread(Image, 1, (*Height * *Width * 3), disk);
   } else {
      Image = (uchar *)calloc(*Height * *Width, sizeof(uchar)); // allocate space for uchar array greyscale
      fread(Image, 1, (*Height * *Width), disk); // read the whole file and put it into Image
  }
   fclose(disk);
   return Image;
}

/****************************************/
/* Write PGM formatted image (1D array).*/
/****************************************/
void PGM_FILE_WRITE_1D(char *FileName, uchar *Image, int Width, int Height, int color) {
FILE *disk;
   disk = fopen(FileName, "wb");
   if (color == 1) fprintf(disk, "P6\n");
              else fprintf(disk, "P5\n");
   fprintf(disk, "%d %d\n", Width, Height);
   fprintf(disk, "255\n");
   if (color == 1) {
      fwrite(Image, 1, (Height * Width * 3), disk);
   } else {
      fwrite(Image, 1, (Height * Width), disk);
   }
   fclose(disk);
}

/****************************************/
/* DEC to BIN converter function +new   */
/****************************************/
void DECIMAL_TO_BINARY(int decimalNum, int binaryNum[8])
{
    // note: could modify this more tobe more useful, could specify a bit amount and use it to calc bit value by performing power of 2
	int bitValue = 128; // this value will determine which bit will be changed

	// checks if decimal number is too big for 8-bit
    if (decimalNum >= 256){printf("%d cannot be put into 8-bit binary.", decimalNum); return; }

    // moving from MSB to the LSB
	for (int x = 0; x < 8; x++)
	{
		if ((decimalNum - bitValue) >= 0)
		{
			decimalNum = decimalNum - bitValue;
			binaryNum[x] = 1;
		}
		else
		{
			binaryNum[x] = 0;

		}

		bitValue = bitValue / 2; // this will get the next place value
	}

	// print binary
	for (int x = 0; x < 8; x++)
		{
			printf("%d", binaryNum[x]);
		}
	printf("\n");

	//return (*binaryNum);
}


/****************************************/
/* BIT SHIFTER +new                     */
/****************************************/
uchar BIT_SHIFTER(uchar decimalValue, int shift, char direction)
{ //shifts a bit in a decimalValue shift amount of times in the specified direction
  //returns the shiftedValue or decimalValue that results from the shift
	uchar shiftedValue;
    if (direction == 'l')
    {
    	shiftedValue = decimalValue << shift;
    }
    else if (direction == 'r')
    {
    	shiftedValue = decimalValue >> shift;
    }
    else
    {
    	printf("Please enter a valid direction \n'l' left\n 'r' right\n");
    }
    return shiftedValue;
}

/****************************************/
/* BIT EXTRACTER +new                     */
/****************************************/
uchar LSB_EXTRACTER(uchar decimalValue)
{ // uses bit and-ing to extract the LSB of the specified decimalValue
	uchar lsb;
    lsb = decimalValue & 1;
    return lsb;
}

int main (int argv,char **argc)
{
	int isColor = 0;

    if (argv < 2)
    {
        printf("\n/*********************************************/\n/* HW8 usage:                               */\n/* ./hw8 normal <-- Normal operation        */\n/*********************************************/\n");
        exit(1);
    }
    else
    {
		if(strcmp(argc[1], "normal") == 0)
        {
			char normalImageFileName[] = "hw8.pgm";
			FILE *image;
		    char magicNumber[3];
		    int width = 0, height = 0, maxColorValue = 0;
		    uchar *imageFile;
		    int numOfBytes;
		    uchar codeword = 0;

			image  = fopen(normalImageFileName, "r");

			if (image == NULL)
			{
				printf("error: file not found\n");
			}
			else
			{
			    fscanf(image, "%s\n", magicNumber );
			    fscanf(image, "%d %d\n", &width, &height);
			    fscanf(image, "%d", &maxColorValue);
			}

			fclose(image);

			// P1, P4, P2, P5 are all greyscale/ black and white images
			if(strcmp(magicNumber, "P1") || strcmp(magicNumber, "P2") || strcmp(magicNumber, "P4") || strcmp(magicNumber, "P5") )
			{
				// the image is greyscale, not color

				imageFile = PGM_FILE_READ_1D(normalImageFileName, &width, &height, &isColor);

				// determine the number of bytes
				numOfBytes = strlen(imageFile); // strlen returns the number of bytes in the string returned by imageFile

				int byteCounter = 0, Xfound = 0;
				uchar prev1 = 0, prev2 = 0;

				for(int n = 0; n < numOfBytes; n++)
				{

                	// shift the lsb of the codeword left  by 1 using bit shifting (x << 1)
                	codeword = BIT_SHIFTER(codeword, 1, 'l');

                	// extract the lsb of the byte using AND (byte and mask)
                	    // note: to extract the LSB, the mask needs to be 1, or 00000001 in binary
                	uchar lsb = LSB_EXTRACTER(imageFile[n]);

                	// put the LSB of the byte on the end of the codeword using OR, (codeword or lsb)
                	codeword = codeword | lsb;

                	byteCounter++;

                    if (byteCounter == 8) //after 8 bytes are counted, print the codeword character
                    {
                    	printf("%c", codeword);
                    	byteCounter = 0;
                    	if (codeword == 'x') // if the codeword is x, check prev codewords
                    	{
                    		if (prev1==0)
                    		{
                    			prev1 = codeword;
                    		}
                    		else if (prev2 ==0)
                    		{
                    			prev2 = codeword;
                    		}
                    		else if (prev1 == 'x' && prev2 =='x' && codeword == 'x') // if 3 xs have occurred
                    		{
                    			Xfound = 1;
                    		}
                    		else
                    		{
                    			prev1 = 0;
                    			prev2 = 0;
                    		}


                    	}
                    }
                    if (Xfound==1) // if 3 Xs are found, the message is done.
                    {
                    	break;
                    }

				}

			}
			else if (strcmp(magicNumber, "P3") || strcmp(magicNumber, "P6"))
			{
				isColor = 1;
				// the image is color
			}


        }
		/*
		else if (strcmp(argc[1], "extra") == 0)
		{
			//int binaryNumber[8] = {0,0,0,0,0,0,0,0};
			char extraImageFileName[] = "hw8-Extra.pgm";
			char hiddenMessageFileName[] = "hw8-Extra.text";
			uchar *extraImage;
			char magicNumber[3];
			int Width = 0, Height = 0, maxColorValue = 0;
			int numOfBytes;
			//uchar *image;
			extraImage = (uchar *)calloc(Height * Width, sizeof(uchar));

			FILE *eImage  = fopen(extraImageFileName, "r");

			if (eImage == NULL)
			{
			    printf("error: file %s not found\n", extraImageFileName);
			}
			else
			{
				fscanf(eImage , "%s\n", magicNumber );
				fscanf(eImage , "%d %d\n", &Width, &Height);
				fscanf(eImage, "%d", &maxColorValue);
			}

			fclose(eImage);

			FILE *hiddenMessage = fopen(hiddenMessageFileName, "r");

			// P1, P4, P2, P5 are all greyscale/ black and white images
			if(strcmp(magicNumber, "P1") || strcmp(magicNumber, "P2") || strcmp(magicNumber, "P4") || strcmp(magicNumber, "P5") )
			{
				// the image is greyscale, not color
				extraImage = PGM_FILE_READ_1D(extraImageFileName, &Width, &Height, &isColor);

				// determine the number of bytes
				numOfBytes = strlen(extraImage); // strlen returns the number of bytes in the string returned by imageFile


				//int byteCounter = 0;
				uchar msgChar = getc(hiddenMessage);
				uchar temp = 0;

				for(int n = 0; n < numOfBytes; n++)
				{
                    for (int m = 0; m < 8; m++)
                    {
                    	temp = msgChar >> 7;
                    	//temp = BIT_SHIFTER(msgChar, 7, 'r'); // keeps the current msb of msgChar
                    	extraImage[n] = extraImage[n] & 254; // gets the first 7 bits of the extraImage
                    	extraImage[n] = extraImage[n] | temp; // sets the lsb to a bit from the msgChar
                    	//msgChar = BIT_SHIFTER(msgChar, 1, 'l');
                        msgChar = msgChar << 1;

                        n++;
                    }
                    // get the next char
					msgChar = getc(hiddenMessage);

					//saving this change to move next bit in line to the front

				}
				PGM_FILE_WRITE_1D(extraImageFileName, extraImage, Width, Height, isColor);

			}
			else if (strcmp(magicNumber, "P3") || strcmp(magicNumber, "P6"))
			{
				isColor = 1;
				// the image is color
			}
			fclose(hiddenMessage);
			free(extraImage);
		}
		*/



	}
}
