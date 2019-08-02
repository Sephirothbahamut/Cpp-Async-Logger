# Cpp-Async-Logger
A simple logger that performs file writes in another threads, making "log(string);" calls from the main thread really quick and unexpensive.

It's not optimized for when multiple threads are trying to log data, while it will still work properly in that case, there can be delays since logging a message will lock the queue.
By default there's a global logger instance.
The destructor takes care of flushing any remaining message.

Usage:
```
#include "Logger.h"
namespace engine {extern logger Logger;}

int main()
  {
  logger.log("Hello world!");
  return(0);
  }
```
