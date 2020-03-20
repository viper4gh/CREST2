/*This is not the fine way, but Global Variables are needed in multiple files, because:
For implementing integrity checks like Slightly Mad recommends it in their SMS_MemMapSample.txt example, 
you have to copy Shared Memory data to a local copy first to reduce the possibility of reading data while pcars writes the data at the same moment, which can lead to inconsistent readed data.
In the main function (CRESTServer.cpp) is the while loop where the function ns_mgr_poll() is called only, which is part of the fossa framework. 
The reading of the Shared Memory data happens in the HttpMessageHandler (HttpMessageHandler.cpp) renderResponse function, which runs each while loop pass. 
In the SMS_MemMapSample.txt example the memory for the local copy is allocated outside the while loop, because then it must be allocated only one time and the local copy data is overwritten each while loop pass only.
Without global variables there are only 2 solutions:
1. Allocate memory for the local copy in the HttpMessageHandler where the reading happens, but then it happens every while loop pass and you have to allocate and free it each pass. Further you loose the local copy data between the loop passes. If something fails in one loop pass you will have no data. 
   With a global allocated copy you will have the data in the next loop till it is overwritten with new data. In case something fails the local copy data from the the previous loop pass can be used.
2. State of the art would be to pass the local copy variable via the ns_mgr_poll() function as parameter, but then you have to customize the complete framework, because you have to change it on multiple locations in code. And if the framework should be updated or replaced later you have to customize it again.

In result none of the 2 solutions makes sense in my eyes, which leads me to use global variables.

Same problem for the "index" variables, because you need the updateIndex value from the prevoius while loop pass for example
*/
#include "sharedmemory.h"

#ifndef GLOBALS_H_
#define GLOBALS_H_
extern unsigned int updateIndex;
extern unsigned int indexChange;
extern SharedMemory* localCopy;
extern SharedMemory* localCopyTmp;
extern int debug_level;  //Debug Mode
#endif
