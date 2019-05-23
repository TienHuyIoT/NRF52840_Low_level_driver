/**	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#include "tm_stdio.h"

/* stdio.h related function */
int fputc(int ch, FILE* f) {
	/* Check if it was called from printf or fprintf */
	
	if (f != stdout) {
		/* Call user custom function */
		return f->outputFuncPointer(ch, f);
	}
	
	/* Printf was called probably = stdout */
	return TM_STDIO_StdoutHandler(ch, f);
}

int fgetc(FILE* f) {
	/* Check if user want data from custom stream */
	
	if (f != stdout) {
		/* Call user custom function */
		return f->inputFuncPointer(f);
	}
	
	/* Standard stream (stdin) check */
	return TM_STDIO_StdinHandler(f);
}

void TM_STDIO_SetOutputFunction(FILE* f, int (*funcPointer)(int, FILE *)) {
	/* Set pointer to output function for specific file pointer */
	f->outputFuncPointer = funcPointer;
}

void TM_STDIO_SetInputFunction(FILE* f, int (*inputFuncPointer)(FILE *)) {
	/* Set pointer to input function for specific file pointer */
	f->inputFuncPointer = inputFuncPointer;
}

__weak int TM_STDIO_StdoutHandler(int c, FILE* f) {
	/* NOTE : This function Should not be modified, when the callback is needed,
            the TM_STDIO_StdoutHandler could be implemented in the user file
	*/
	return 0;
}

__weak int TM_STDIO_StdinHandler(FILE* f) {
	/* NOTE : This function Should not be modified, when the callback is needed,
            the TM_STDIO_StdoutHandler could be implemented in the user file
	*/
	return 0;
}