# ACR
**A** set of **C** functions in a git **R**epository

## Quick start

### Project Settings
- Add public.h and public.c to your project
- Add [your ACR path]/include to your include paths

### Code
- Add #include "ACR/public.h" to the top of your C file
- Call the ACR_Test() function as follows:
```
if(ACR_Test() == ACR_INFO_OK)
{
    // OK, ACR library is ready for use
}
```
