/* kardinal/integration.c
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*
*  Functions that integrate Kardinal with C, such as map to C variables,
*  should be defined here
*
*  This project is under the GNU General GPL version 3.0 license. For more 
*  information about the license, refer the LICENCE file in the root directory 
*  or go online to <http://www.gnu.org/licenses>
*  
*  Any redistribution of this code must contain this header in its entirety
*/

#include"kardinal.h"

#define EQSTR(a,b) (strcmp(a,b)==0)

void map_to_C(char * varname, void * buffer){
	/* Function that maps a kardinal variable already existing in the symbol-
	 * table to a C variable. The point of this is to enable Kardinal to serve
	 * as a general purpose input-processing scripting language
	 */
}

