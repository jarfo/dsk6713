/*========================================================================*/
/*                                  Codec.h                               */
/*========================================================================*/
typedef struct {
	 int *bits;            /* If cod_hdb3 is used bits[-3],..,bits[-1]
	                         store the value of previos symbols */
	 int nbits;
	 int lSymb;            /* Samples per symbol */
	 int V;                /* Output amplitude   */
	 struct {
		  int sgnOne;       /* Used to alternate polarity */
		  int dc;           /* Used in cod_hdb3 */
		  int zeroes;       /* Used in cod_hdb3 */
		  int lastBit;      /* Used in cod_dif  */
	 } state;
} USER;

void cod_rz     (USER *, int *out, int rz);
void cod_polar  (USER *, int *out);
void cod_bipolar(USER *, int *out);
void cod_ami    (USER *, int *out);
void cod_hdb3   (USER *, int *out);
void cod_cmi    (USER *, int *out);
void cod_manchester (USER *, int *out);
void cod_dif    (USER *);
