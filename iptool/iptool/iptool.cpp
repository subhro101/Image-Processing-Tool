/************************************************************
 *															*
 * This sample project include three functions:				*
 * 1. Add intensity for gray-level image.					*
 *    Input: source image, output image name, value			*
 *															*
 * 2. Image thresholding: pixels will become black if the	*
 *    intensity is below the threshold, and white if above	*
 *    or equal the threhold.								*
 *    Input: source image, output image name, threshold		*
 *															*
 * 3. Image scaling: reduction/expansion of 2 for 			*
 *    the width and length. This project uses averaging 	*
 *    technique for reduction and pixel replication			*
 *    technique for expansion.								*
 *    Input: source image, output image name, scale factor	*
 *															*
 ************************************************************/

#include "./iptools/core.h"
#include <string.h>
#include <fstream>

using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	ifstream fp(argv[1]);
	char str[MAXLEN];
	rsize_t strmax = sizeof str;
	char outfile[MAXLEN];
	char *pch, *next_pch;
	int nOP;
	if (!fp.is_open()) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	fp >> nOP;
	for (int OP = 0; OP < nOP; OP++) {
		fp >> str;
		src.read(str);

		fp >> str;
		strcpy_s(outfile, MAXLEN, str);

		fp >> str;
        if (strncmp(str,"add",3)==0) {
			/* Add Intensity */
			fp >> str;
        	utility::addGrey(src,tgt,atoi(str));
        }

        else if (strncmp(str,"binarize",8)==0) {
			/* Thresholding */
			fp >> str;
		int t1 = atoi(str);
		fp >> str;
		int t2 = atoi(str);
			utility::binarize(src,tgt,t1,t2);
		}
		

		else if (strncmp(str,"scale",5)==0) {
			/* Image scaling */
			fp >> str;
			utility::scale(src,tgt,atof(str));
		}

		else {
			printf("No function: %s\n", str);
			continue;
		}
       
		tgt.save(outfile);
	}
	//fclose(fp);
	fp.close();
	return 0;
}

