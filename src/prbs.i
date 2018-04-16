%include "stdint.i"

%module prbs
%{
 /* Includes the header in the wrapper code */
 #include "config.h"
 #include "prbs.h"
 #include "lfsr.h"
 #include "sg.h"
 #include "asg.h"
%}

/* Parse the header file to generate wrappers */
%include "config.h"
%include "prbs.h"
%include "lfsr.h"
%include "sg.h"
%include "asg.h"

%include "carrays.i"
%array_class(uint8_t, buffer);
 
%pythoncode %{
__version__ = PRBS_VERSION
%}

