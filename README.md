# cppngrok
a cpp wrapper for ngrok


<br/>
##### not implemented yet, read the code!
### basic usage
```cpp
#include <cppngrok.h> // or "cppngrok.h" if locally

void main(){
  CppngrokHandler cppn_handler;
  cppn_handler.bind() // http tunnel on default port (8080)
  cppn_handler.bind("tcp", 1337) // tcp tunnel in port 1337
  
  // see documentation for full guide

}
```
### requeriments

```
https://ngrok.com/
```

### simple static build

```
make
g++ your_project.cpp build/cppngrok_lib.a
make clean
```

#### based in pyngrok
```
https://github.com/alexdlaird/pyngrok
```
