# Test-Delete
Delete does not set the pointer to null.
  
TEST1 delete\
Allocate and assign\
pointer: 0xb81180\
content: 42\
Deallocate\
pointer: 0xb81180\
content: 42\
NOTE: delete does not update the content of the pointer to NULL automatically\
This means that you can use ip again without knowing the memory is no longer valid\
-------------------------------------------

TEST2 macro to clear pointer\
Allocate and assign\
pointer: 0xb81090\
content: 42\
Deallocate\
pointer: 0\
-------------------------------------------

TEST3 function to clear pointer | pointer argument\
Allocate and assign\
pointer: 0xb80fe0\
content: 42\
Deallocate\
pointer: 0\
NOTE: the function must have access to the address of the pointer to clear it\
-------------------------------------------

TEST4 function to clear pointer | reference argument\
Allocate and assign\
pointer: 0xb81040\
content: 42\
Deallocate\
pointer: 0\
Same as above, but the argument is a reference instead of a pointer\
interface is the same as delete but the function can alter the original value!
