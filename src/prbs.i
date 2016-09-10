 %include "stdint.i"

 %module prbs
 %{
 /* Includes the header in the wrapper code */
 #include "prbs.h"
 #include "lfsr.h"
 #include "sg.h"
 %}

 /* Parse the header file to generate wrappers */
 %include "prbs.h"
 %include "lfsr.h"
 %include "sg.h"
