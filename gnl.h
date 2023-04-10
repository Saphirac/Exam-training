#ifndef GNL_H
 #define GNL_H
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <unistd.h>
 #include <fcntl.h>

 #ifndef BUFFER_SIZE
  #define BUFFER_SIZE 4096LU
 #endif

 enum	e_ret
 {
 	RETURN_THE_LINE,
 	CONTINUE_TO_READ,
 	ERROR_OCCURED,
 };
#endif
