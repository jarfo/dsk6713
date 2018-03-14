#include <math.h>
#include <stdlib.h>

struct complex
{
  float real;
  float imag;
};

void fftc(float f[], int N, int forward)
/* Fourier transform of an array of N complex numbers.

PARAMETERS
	f:		 At the input, the array is of length 2*N and contains the real part of the input
			 signal on the odd-numbered elements, and the imaginary part on the even-numbered elements
			 At the output, it contains the samples of the DFT, ordered as follows:
				f[0]	Real(DFT(0))
				f[1]	Imag(DFT(0))
				f[2]	Real(DFT(1))
				f[3]	Imag(DFT(1))
				...
				f[2*N-2]	Real(DFT(N-2))
				f[2*N-1]	Imag(DFT(N-1))
	N:		 Number of real samples. Must be a power of 2
	forward: Determines whether to do a forward transform (1) or an inverse one(-1)
*/

{
  int b,index1,index2,trans_size,trans;
  float pi2 = 4.*asin(1.);
  float pi2n,cospi2n,sinpi2n; 	/* Used in recursive formulas for Re(W^b) and Im(W^b) */
  struct complex wb; 			/* wk = W^k = e^(2 pi i b/N) in the Danielson-Lanczos formula for a transform of length N */
  struct complex temp1,temp2; 	/* Buffers for implementing recursive formulas */
  struct complex *c = (struct complex *)f; /* Treat f as an array of N complex numbers */

  /* Place the elements of the array c in bit-reversed order */
  for(index1=1,index2=0;index1<N;index1++) /* Loop through all elements of c */
  {
    for(b=N/2;index2>=b;b/=2) 	/* To find the next bit reversed array index subtract leading 1's from index2 */
      index2-=b;
    index2+=b; 					/* Next replace the first 0 in index2 with a 1 and this gives the correct next value */
    if(index2>index1) 			/* Swap each pair only the first time it is found */
    {
      temp1 = c[index2];
      c[index2] = c[index1];
      c[index1] = temp1;
    }
  }

  /* Next perform successive transforms of length 2,4,...,N using the Danielson-Lanczos formula */
  for(trans_size=2;trans_size<=N;trans_size*=2) /* trans_size = size of transform being computed */
  {
    pi2n = forward*pi2/(float)trans_size; 	/* +- 2 pi/trans_size */
    cospi2n = cos(pi2n); 					/* Used to calculate W^k in D-L formula */
    sinpi2n = sin(pi2n);
    wb.real = 1.; 							/* Initialize W^b for b=0 */
    wb.imag = 0.;
    for(b=0;b<trans_size/2;b++) 			/* Step over half of the elements in the transform */
    {
      for(trans=0;trans<N/trans_size;trans++) /* Iterate over all transforms of size trans_size to be computed */
      {
	index1 = (trans*trans_size+b);		 	/* Index of element in first half of transform being computed */
	index2 = index1 + trans_size/2;			/* Index of element in second half of transform being computed */
	temp1 = c[index1];
	temp2 = c[index2];
	c[index1].real = temp1.real + wb.real*temp2.real - wb.imag*temp2.imag; /* Implement D-L formula */
	c[index1].imag = temp1.imag + wb.real*temp2.imag + wb.imag*temp2.real;
	c[index2].real = temp1.real - wb.real*temp2.real + wb.imag*temp2.imag;
	c[index2].imag = temp1.imag - wb.real*temp2.imag - wb.imag*temp2.real;
      }
      temp1 = wb;
      wb.real = cospi2n*temp1.real - sinpi2n*temp1.imag; /* Real part of e^(2 pi i b/trans_size) used in D-L formula */
      wb.imag = cospi2n*temp1.imag + sinpi2n*temp1.real; /* Imaginary part of e^(2 pi i b/trans_size) used in D-L formula */
    }
  }

  /* For an inverse transform divide by the number of grid points */
  if(forward<0.)
    for(index1=0;index1<N;index1+=1)
    {
      c[index1].real /= N;
      c[index1].imag /= N;
    }
}

void fftr(float f[], int N, int forward)
/* Fourier transform of an array of N complex numbers.

PARAMETERS
	f:		 At the input, the array contains N real samples
			 At the output, it contains the samples of the DFT, ordered as follows:
				f[0]	DFT(0)
				f[1]	DFT(N/2)
				f[2]	Real(DFT(1))
				f[3]	Imag(DFT(1))
				...
				f[N-2]	Real(DFT(N/2-1))
				f[N-1]	Imag(DFT(N/2-1))
	N:		 Number of real samples. Must be a power of 2
	forward: Determines whether to do a forward transform (1) or an inverse one(-1)
*/

{
  int b;
  float pi2n = 4.*asin(1.)/N,cospi2n=cos(pi2n),sinpi2n=sin(pi2n); /* pi2n = 2 Pi/N */
  struct complex wb; 						/* wb = W^b = e^(2 pi i b/N) in the Danielson-Lanczos formula for a transform of length N */
  struct complex temp1,temp2; 				/* Buffers for implementing recursive formulas */
  struct complex *c = (struct complex *)f; 	/* Treat f as an array of N/2 complex numbers */

  if(forward==1)
    fftc(f,N/2,1); 							/* Do a transform of f as if it were N/2 complex points */

  wb.real = 1.; 							/* Initialize W^b for b=0 */
  wb.imag = 0.;
  for(b=1;b<N/4;b++) 						/* Loop over elements of transform. See documentation for these formulas */
  {
    temp1 = wb;
    wb.real = cospi2n*temp1.real - sinpi2n*temp1.imag; /* Real part of e^(2 pi i b/N) used in D-L formula */
    wb.imag = cospi2n*temp1.imag + sinpi2n*temp1.real; /* Imaginary part of e^(2 pi i b/N) used in D-L formula */
    temp1 = c[b];
    temp2 = c[N/2-b];
    c[b].real = .5*(temp1.real+temp2.real + forward*wb.real*(temp1.imag+temp2.imag) + wb.imag*(temp1.real-temp2.real));
    c[b].imag = .5*(temp1.imag-temp2.imag - forward*wb.real*(temp1.real-temp2.real) + wb.imag*(temp1.imag+temp2.imag));
    c[N/2-b].real = .5*(temp1.real+temp2.real - forward*wb.real*(temp1.imag+temp2.imag) - wb.imag*(temp1.real-temp2.real));
    c[N/2-b].imag = .5*(-temp1.imag+temp2.imag - forward*wb.real*(temp1.real-temp2.real) + wb.imag*(temp1.imag+temp2.imag));
  }
  temp1 = c[0];
  c[0].real = temp1.real+temp1.imag; 		/* Set b=0 term in transform */
  c[0].imag = temp1.real-temp1.imag; 		/* Put b=N/2 term in imaginary part of first term */

  if(forward==-1)
  {
    c[0].real *= .5;
    c[0].imag *= .5;
    fftc(f,N/2,-1);
  }
}

