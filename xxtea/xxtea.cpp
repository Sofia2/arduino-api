/* xxt encryptor by aliver               */
/* Version 2.0                           */
/*                                       */
/* An implementation of xxtea encryption */
/* A very small (code wise) secure block */
/* cipher. Supposedly faster than btea   */
/* and for files of any non-trival size  */
/* it's gonna be way faster than TEA or  */
/* IDEA. At worst it's something like 4x */
/* the speed of DES, and more secure by  */
/* a factor of 2^72 ~ 4.7 x 10^21        */
/* My tests seemed to indicate that xxt  */
/* is about 3x the speed of mcrypt with  */
/* the same options. Not that mcrypt is  */
/* not a great piece of work. It is.     */
/*                                       */
/* The xxtea algorithm was designed by:  */
/* David Wheeler and Roger Needham. Some */
/* code from their publications was used */
/* for some of the encryption portions.  */
/* However it was altered to be 64 bit   */
/* architecture friendly.                */
/*                                       */
/* Rain Forest Puppy, Zen Parse, Steven  */
/* M. Christey, Hank Leininger, Daniel   */
/* Hartmeier, and anyone I forgot who    */
/* provided me with feedback, bugfixes,  */
/* or pointed out errors in the original */
/* release of xxt                        */
/*****************************************/
/* CHANGE LOG - CHANGE LOG - CHANGE LOG  */
/* Version 2                             */
/* o Tried to mitigate race condition in */
/*   -g by wiping the environment var as */
/*   soon as it's copied.                */
/* o Checked for NULL pointer on -g      */
/* o Added use of O_EXCL for opening the */
/*   output file.                        */
/* o Fixed problem whereby the hash of   */
/*   the key was being reduced to 64bits */
/*   since I was using a char array that */
/*   was being populated with ascii hex  */
/*   values rather than just binary      */
/* o Moved the argv trashing loop up so  */
/*   that it happens before any file I/O */
/* o Fixed an issue whereby someone may  */
/*   create a malicious xxt crypted file */
/*   with a bad filesize header. Now I   */
/*   check for this.                     */
/* o Checked for access to read & write  */
/*   to file in case someone is dumb     */
/*   enough to make this setuid root     */
/* o Added the -f functionality to use a */
/*   whole file as the key. The file is  */
/*   hashed to a 128 bit key.            */
/*****************************************/
/* Compile with cc -O3 -o xxt xxt.c      */
/* "xxt -h" for help, after that         */
/* tested on IRIX, Solaris, Linux        */
/* NetBSD, and AIX                       */

/*****************************************/
/* CHANGE LOG - CHANGE LOG - CHANGE LOG  */
/* Anagha Mudigonda version 3*/
/* I used most alivers logic as is but I */
/* removed main and a lot of functions I */
/* do not need for kamaelia. Also I use  */
/* my own keygen function so I removed   */
/* the MD5 related code                  */
/*****************************************/
#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <time.h>
//#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include "xxtea.h"
#include <Arduino.h>




#define XXTEA_MX (z >> 5 ^ y << 2) + (y >> 3 ^ z << 4) ^ (sum ^ y) + (k[p & 3 ^ e] ^ z)
#define XXTEA_DELTA 0x9e3779b9


// this function will return the number of bytes currently free in RAM
static int memoryTest() {
  int byteCounter = 0; // initialize a counter
  byte *byteArray; // create a pointer to a byte array
  // More on pointers here: http://en.wikipedia.org/wiki/Pointer#C_pointers

  // use the malloc function to repeatedly attempt allocating a certain number of bytes to memory
  // More on malloc here: http://en.wikipedia.org/wiki/Malloc
  while ( (byteArray = (byte*) malloc (byteCounter * sizeof(byte))) != NULL ) {
    byteCounter++; // if allocation was successful, then up the count for the next try
    free(byteArray); // free memory after allocating it
  }
  
  free(byteArray); // also free memory after the function finishes
  return byteCounter; // send back the highest number of bytes successfully allocated
}

void xxtea_long_encrypt(xxtea_long *v, xxtea_long len, xxtea_long *k) {
	xxtea_long n = len - 1;
    xxtea_long z = v[n], y = v[0], p, q = 6 + 52 / (n + 1), sum = 0, e;
    if (n < 1) {
        return;
    }
    while (0 < q--) {
        sum += XXTEA_DELTA;
        e = sum >> 2 & 3;
        for (p = 0; p < n; p++) {
            y = v[p + 1];
            z = v[p] += XXTEA_MX;
        }
        y = v[0];
        z = v[n] += XXTEA_MX;
    }
}

void xxtea_long_decrypt(xxtea_long *v, xxtea_long len, xxtea_long *k) {
	//Serial.println("xxtea_long_decrypt -1");
    xxtea_long n = len - 1;
	//Serial.println("xxtea_long_decrypt -2");
    xxtea_long z = v[n], y = v[0], p, q = 6 + 52 / (n + 1), sum = q * XXTEA_DELTA, e;
	//Serial.println("xxtea_long_decrypt -3");
    if (n < 1) {
		//Serial.println("xxtea_long_decrypt -4");
        return;
    }
    while (sum != 0) {
		//Serial.println("xxtea_long_decrypt -5");
        e = sum >> 2 & 3;
        for (p = n; p > 0; p--) {
            z = v[p - 1];
            y = v[p] -= XXTEA_MX;
        }
        z = v[n];
        y = v[0] -= XXTEA_MX;
        sum -= XXTEA_DELTA;
    }
	//Serial.println("xxtea_long_decrypt -6");
}


//hacer pruebas ya directamente sobre esta funcion para ver porque no se traga los datos.
static xxtea_long *xxtea_to_long_array(const unsigned char *data, xxtea_long len, int include_length, xxtea_long *ret_len) {
	xxtea_long i, n, *result;
	n = len >> 2;
	n = (((len & 3) == 0) ? n : n + 1);
	
    if (include_length) {
	    result = (xxtea_long *)malloc((n + 1) << 2);
		if(result==NULL){
			Serial.println("Nulo en 2");
		}
		
		//Serial.print("Inserta: ");
		//Serial.print(len);
		//Serial.print(" En la posicion: ");
		//Serial.println(n);
        
		result[n] = len;
		*ret_len = n + 1;
	} else {
        result = (xxtea_long *)malloc(n << 2);
		if(result == NULL) {
			Serial.println("Malloc nulo");
		}
		*ret_len = n;
    }
	memset(result, 0, n << 2);
	for (i = 0; i < len; i++) {
        result[i >> 2] |= (xxtea_long)data[i] << ((i & 3) << 3);
    }
	
    return result;
}

static unsigned char *xxtea_to_byte_array(xxtea_long *data, xxtea_long len, int include_length, xxtea_long *ret_len, int d, unsigned char *result) {
    xxtea_long i, n, m;
    //unsigned char *result;
	//Serial.println("1");
    n = len << 2;
	//Serial.println("2");
    if (include_length) {
		//Serial.println("2.1");
        m = data[len - 1];
		
		//Serial.print("Recupera: ");
		//Serial.print(m);
		//Serial.print(" De la posicion: ");
		//Serial.println(len-1);
		
		//Serial.println("2.2");
        if ((m < n - 7) || (m > n - 4)){
			//Serial.print("m: ");
			//Serial.println(m);
			//Serial.print("n: ");
			//Serial.println(n);
			Serial.println("va a retornar nulo");
			return NULL;
		}
		//Serial.println("2.3");
        n = m;
    }
	
	//Serial.println("tamaño del malloc");
	//Serial.println(n+1);
	//Serial.println(memoryTest());
    //result = (unsigned char *)malloc((n + 1)*sizeof(unsigned char));
	//result=new unsigned char[n+1];
	
	if(result==NULL){
		Serial.println("Nulo en 1");
	}
	
	//if(!d){
	
	/*Serial.println("################################");
	for(int i=0;i<=n;i++){
		Serial.print((char)result[i]);
	}
	Serial.println("################################");*/
	
	
	
	//Serial.println("4");
	for (i = 0; i < n; i++) {
		
			result[i] = (unsigned char)((data[i >> 2] >> ((i & 3) << 3)) & 0xff);
	/*	Serial.print((int)result[i]);
		Serial.print(" ");
		Serial.print((int)((unsigned char)((data[i >> 2] >> ((i & 3) << 3)) & 0xff)));
		Serial.println("");*/
    }
	//Serial.println();
	result[n] = (unsigned char)'\0';
	
	Serial.println((char*)result);

	
	*ret_len = n;
	if(!d){
		return result;
	}
}

unsigned char *xxtea_encrypt(const unsigned char *data, xxtea_long len, unsigned char *key, xxtea_long keyLen, xxtea_long *ret_len, unsigned char *resultp)
{
    unsigned char *result;
    xxtea_long *v, *k, v_len, k_len;
    v = xxtea_to_long_array(data, len, 1, &v_len);
    k = xxtea_to_long_array(key, keyLen, 0, &k_len);
    xxtea_long_encrypt(v, v_len, k);

    result = xxtea_to_byte_array(v, v_len, 0, ret_len, 0, resultp);
    free(v);
    free(k);
    return result;
}




unsigned char *xxtea_decrypt(const unsigned char *data, xxtea_long len, unsigned char *key, xxtea_long keyLen, xxtea_long *ret_len, unsigned char *resultp)
{		
	//Serial.print("#########################################################");
	
	unsigned char *result;
    xxtea_long *v, *k, v_len, k_len;
	
	Serial.println("cadena");
	v = xxtea_to_long_array(data, len, 0, &v_len); 
	Serial.println("clave");
	k = xxtea_to_long_array(key, keyLen, 0, &k_len);
	
	Serial.println("descifrado");
	xxtea_long_decrypt(v, v_len, k);

	Serial.println("conversion");
	result = xxtea_to_byte_array(v, v_len, 1, ret_len , 1, resultp);
	Serial.println("liberar punteros");
	free(k);
	free(v);
	
	
	Serial.println("retorna");
	//Serial.print("#########################################################");
    return result;
}





