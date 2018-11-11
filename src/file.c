#include "file.h"
#include <stdio.h>

unsigned char *load_IMG(char *filename)
{
    FILE *imgFile;
	unsigned char *buffer;
	unsigned long fileLen;

    // Open the image file
    imgFile = fopen(filename,"r");
    // Verify if open
    if (imgFile != NULL)
    {
        // If not stop the operation
		fprintf(stderr, "Unable to open file %s", filename);
        fclose(imgFile);
        return NULL;
    }
	//Get file length
	fseek(imgFile, 0, SEEK_END);
	fileLen = ftell(imgFile);
	fseek(imgFile, 0, SEEK_SET);

	//Allocate memory
	buffer=(unsigned char *)malloc(fileLen);
	if (!buffer)
	{
		fprintf(stderr, "Memory error!");
		fclose(imgFile);
		return NULL;
	}
    // Copy the data
	fread(buffer,fileLen,sizeof(unsigned char),imgFile);
    // Close the file
    fclose(imgFile);
    return buffer;
}

bool write_IMG(char *filename, char *buffer, int buffer_size) 
{
    // Open
    FILE *imgFile;
	int index;

	imgFile = fopen(filename, "w");
    // Verify if open
    if (imgFile != NULL)
    {
        // If not stop the operation
        fclose(imgFile);
        return false;
    }

    // Write the buffer to the file
    index = 0;
	while(index < buffer_size)
        fputc(*(buffer + index++), imgFile);

    // Close the file
    fclose(imgFile);
    return true;
}

/*

unsigned char imagIn[16384];
unsigned char imagOut[16384];
float imagAnaliza[16384];
float imagSinteza[16384];
float fil[16384];
float dec_2[16384];
float  dec_2_2[16384];
float fil_dec_2[16384];
float im1_exp2[16384];
float im1_exp2_fil[16384];
float im2_exp2[16384];
float im2_exp2_fil[16384];
float temp1_exp_fil2[16384];
float temp2_exp_fil2[16384];

#include <DWT.h>

void Analiza_DWT (unsigned char * ent1, float * iesire, int latime, int inaltime)
{
	int i, j;
	
	///////////////////////LL/////////////////////////////////////////////////
	//Filtrare  pe linii filtru H0
	for (i=1; i<latime;i++)
		for (j=0; j<inaltime;j++)
			fil[i+j*latime]=(ent1[i+j*latime]+ent1[(i-1)+j*latime])*0.707106781;
	
	//Decimare coloane
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime;j++)
			dec_2[i+j*latime]=fil[2*i+j*latime];
	
	//Filtrare coloane cu filtru H0
	for (i=0; i<latime/2;i++)
		for (j=1; j<inaltime;j++)
			fil_dec_2[i+j*latime]=(dec_2[i+j*latime]+dec_2[i+(j-1)*latime])*0.707106781;
	
	//Decimare linii
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			dec_2_2[i+j*latime]=fil_dec_2[i+2*j*latime];

	// Construire imagine iesire
	for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
			iesire[i+j*latime]=dec_2_2[i+j*latime];

	// Golire imagini temporare
		for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
		{
			fil[i+j*latime]=0;
			fil_dec_2[i+j*latime]=0;
			dec_2[i+j*latime]=0;
			dec_2_2[i+j*latime]=0;
		}
	///////////////////////LH/////////////////////////////////////////////////
	//Filtrare  pe linii filtru H0
	for (i=1; i<latime;i++)
		for (j=0; j<inaltime;j++)
			fil[i+j*latime]=(ent1[i+j*latime]+ent1[(i-1)+j*latime])*0.707106781;
	
	//Decimare coloane
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime;j++)
			dec_2[i+j*latime]=fil[2*i+j*latime];
	
	//Filtrare coloane cu filtru H1
	for (i=0; i<latime/2;i++)
		for (j=1; j<inaltime;j++)
			fil_dec_2[i+j*latime]=(dec_2[i+j*latime]-dec_2[i+(j-1)*latime])*0.707106781;
	
	//Decimare linii
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			dec_2_2[i+j*latime]=fil_dec_2[i+2*j*latime];

	// Construire imagine iesire
	for (i=latime/2; i<latime;i++)
		for (j=0; j<inaltime;j++)
			iesire[i+j*latime]=dec_2_2[i-latime/2+j*latime];

	// Golire imagini temporare
		for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
		{
			fil[i+j*latime]=0;
			fil_dec_2[i+j*latime]=0;
			dec_2[i+j*latime]=0;
			dec_2_2[i+j*latime]=0;
		}
	///////////////////////HL/////////////////////////////////////////////////
	//Filtrare  pe linii filtru H1
	for (i=1; i<latime;i++)
		for (j=0; j<inaltime;j++)
			fil[i+j*latime]=(ent1[i+j*latime]-ent1[(i-1)+j*latime])*0.707106781;
	
	//Decimare coloane
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime;j++)
			dec_2[i+j*latime]=fil[2*i+j*latime];
	
	//Filtrare coloane cu filtru H0
	for (i=0; i<latime/2;i++)
		for (j=1; j<inaltime;j++)
			fil_dec_2[i+j*latime]=(dec_2[i+j*latime]+dec_2[i+(j-1)*latime])*0.707106781;
	
	//Decimare linii
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			dec_2_2[i+j*latime]=fil_dec_2[i+2*j*latime];

	// Construire imagine iesire
	for (i=0; i<latime;i++)
		for (j=inaltime/2; j<inaltime;j++)
			iesire[i+j*latime]=dec_2_2[i+(j-inaltime/2)*latime];

	// Golire imagini temporare
		for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
		{
			fil[i+j*latime]=0;
			fil_dec_2[i+j*latime]=0;
			dec_2[i+j*latime]=0;
			dec_2_2[i+j*latime]=0;
		}

	///////////////////////HH/////////////////////////////////////////////////
	//Filtrare  pe linii filtru H1
	for (i=1; i<latime;i++)
		for (j=0; j<inaltime;j++)
			fil[i+j*latime]=(ent1[i+j*latime]-ent1[(i-1)+j*latime])*0.707106781;
	
	//Decimare coloane
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime;j++)
			dec_2[i+j*latime]=fil[2*i+j*latime];
	
	//Filtrare coloane cu filtru H0
	for (i=0; i<latime/2;i++)
		for (j=1; j<inaltime;j++)
			fil_dec_2[i+j*latime]=(dec_2[i+j*latime]-dec_2[i+(j-1)*latime])*0.707106781;
	
	//Decimare linii
	for (i=0;i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			dec_2_2[i+j*latime]=fil_dec_2[i+2*j*latime];

	// Construire imagine iesire
	for (i=latime/2; i<latime;i++)
		for (j=inaltime/2; j<inaltime;j++)
			iesire[i+j*latime]=dec_2_2[i-latime/2+(j-inaltime/2)*latime];
			
	//////////////////////////DOAR PT VIZUALIZARE//////////////////////////
	for (i=0;i<latime;i++)
	for (j=0;j<inaltime;j++)
	{
		if (iesire[i+j*latime]>255)
			iesire[i+j*latime]=255;
		if (iesire[i+j*latime]<0)
			iesire[i+j*latime]=0;
		imagOut[i+j*latime]= (unsigned char)iesire[i+j*latime];
	}//////////////////////// SFARSIT VIZUALIZARE//////////////////////////
}


void Sinteza_DWT (float * ent1, float * iesire, int latime, int inaltime)
{
	long i, j;
	//////////////////////// DEFINIRE COEFICIENTI//////////////////////////
	float g0_0 =1;
	float g0_1 =1;
	float g1_0 =1;
	float g1_1 =1;
	
	//////////////////////// SFARSIT DEFINIRE//////////////////////////////
		
	for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
		{
		im1_exp2[i+j*latime]=0;
		im1_exp2_fil[i+j*latime]=0;
		im2_exp2[i+j*latime]=0;
		im2_exp2_fil[i+j*latime]=0;
		temp1_exp_fil2[i+j*latime]=0;
		temp2_exp_fil2[i+j*latime]=0;

		}
	
	//EXPANDARE LINII*FILTRARE LINII 
	
	//Expandare LL linii - valori de zero pt. ordonate impare

	for (i=0; i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			im1_exp2[i+2*j*latime]=(ent1[i+j*latime]);
	
	//Filtrare G0 pe coloane
	for (i=0; i<latime/2;i++)
	for (j=1; j<inaltime;j++)
			im1_exp2_fil[i+j*latime]=(g0_0*im1_exp2[i+j*latime]+g0_1*im1_exp2[i+(j-1)*latime]);
	

	//Expandare LH linii - valori de zero pt. ordonate impare
	for (i=0; i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			im2_exp2[i+2*j*latime]=ent1[i+latime/2+(j)*latime];
	
	//Filtrare G1 pe coloane
	for (i=0; i<latime/2;i++)
	for (j=1; j<inaltime;j++)
			im2_exp2_fil[i+j*latime]=(g1_0*im2_exp2[i+j*latime]+g1_1*im2_exp2[i+(j-1)*latime]);


	//Adunare imagini temporare 
	for (i=0; i<latime/2;i++)
	for (j=0; j<inaltime;j++)
			temp1_exp_fil2[i+j*latime]=im1_exp2_fil[i+j*latime]+im2_exp2_fil[i+j*latime];

	//Golire imagini temporare
	for (i=0; i<latime;i++)
	for (j=0; j<inaltime;j++)
		{
			im1_exp2[i+j*latime]=0;
			im1_exp2_fil[i+j*latime]=0;
			im2_exp2[i+j*latime]=0;
			im2_exp2_fil[i+j*latime]=0;
		}

	//Expandare HL -valori de zero pt. ordonate impare
	for (i=0; i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			im1_exp2[i+2*j*latime]=(ent1[i+(j+latime/2)*latime]);
	
	//Filtrare G0 pe coloane
	for (i=0; i<latime/2;i++)
	for (j=1; j<inaltime;j++)
			im1_exp2_fil[i+j*latime]=(g0_0*im1_exp2[i+j*latime]+g0_1*im1_exp2[i+(j-1)*latime]);


	//Expandare HH coloane -valori de zero pt. ordonate impare
	for (i=0; i<latime/2;i++)
		for (j=0; j<inaltime/2;j++)
			im2_exp2[i+2*j*latime]=(ent1[i+latime/2+(j+latime/2)*latime]);
	
	//Filtrare G1 pe coloane
	for (i=0; i<latime/2;i++)
	for (j=1; j<inaltime;j++)
			im2_exp2_fil[i+j*latime]=(g1_0*im2_exp2[i+j*latime]+g1_1*im2_exp2[i+(j-1)*latime]);
	
	//Adunare imagini temporare
	for (i=0; i<latime/2;i++)
	for (j=0; j<inaltime;j++)
			temp2_exp_fil2[i+j*latime]=im1_exp2_fil[i+j*latime]+im2_exp2_fil[i+j*latime];

	// Golire imagini intermediare
		for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
		{
			im1_exp2[i+j*latime]=0;
			im2_exp2[i+j*latime]=0;
			im1_exp2_fil[i+j*latime]=0;
			im2_exp2_fil[i+j*latime]=0;
		}


	//EXPANDARE pe coloane - valori de zero pentru abscise imparre


	for (i=0; i<latime/2;i++)
		for (j=0; j<inaltime;j++)
			im1_exp2[2*i+j*latime]=(temp1_exp_fil2[i+j*latime]);

	//Filtrare G0 pe linii
	for (i=1; i<latime;i++)
	for (j=0; j<inaltime;j++)
			im1_exp2_fil[i+j*latime]=(g0_0*im1_exp2[i+j*latime]+g0_1*im1_exp2[i-1+(j)*latime]);
	


	//EXPANDARE pe coloane - valori de zero pentru abscise impare
	for (i=0; i<latime/2;i++)
		for (j=0; j<inaltime;j++)
			im2_exp2[2*i+j*latime]=(temp2_exp_fil2[i+j*latime]);

	//Filtrare G1 pe linii
	for (i=1; i<latime;i++)
	for (j=0; j<inaltime;j++)
			im2_exp2_fil[i+j*latime]=(g1_0*im2_exp2[i+(j)*latime]+g1_1*im2_exp2[i-1+j*latime]);

	for (i=0; i<latime;i++)
		for (j=0; j<inaltime;j++)
					iesire[i+j*latime]=im1_exp2_fil[i+j*latime]+im2_exp2_fil[i+j*latime];
					
		for (i=0;i<latime;i++)
	for (j=0;j<inaltime;j++)
	{
		if (iesire[i+j*latime]>255)
			iesire[i+j*latime]=255;
		if (iesire[i+j*latime]<0)
			iesire[i+j*latime]=0;
		imagOut[i+j*latime]= (unsigned char)iesire[i+j*latime];
	}
}


void main(){
	Analiza_DWT (imagIn, imagAnaliza, 128,128);
//	Sinteza_DWT (imagAnaliza, imagSinteza, 128,128);
	while (1);
}
*/