/****************************************************************
**	DESCRIPTION
****************************************************************
**	Question:
**		Do the delete automatically update the content of the pointer to NULL?
**	Answer:
**		NO. The delete should know the address of the pointer p to delete its content
**		This means that your checks p!=NULl will pass unless p is explicitly set to null
**
**	Solution 1:
**		Use a macro as wrapper of delete
**	Solution 2:
**		Use a function as wrapper of delete
****************************************************************/

///--------------------------------------------------------------------------
///	Libraries
///--------------------------------------------------------------------------

#include <iostream>

///--------------------------------------------------------------------------
///	Macros
///--------------------------------------------------------------------------

//MACRO that adds an explicit line to clear out the pointer. Same structure as delete
#define MY_DELETE( ptr )	\
	delete( ptr ), ptr = nullptr;

///--------------------------------------------------------------------------
///	Namespaces
///--------------------------------------------------------------------------

using std::cout;

///--------------------------------------------------------------------------
///	Function prototypes
///--------------------------------------------------------------------------

//show the content of pointer p. Safety check.
extern bool show( int *p );

//function to clear the content of pointer after delete. Must know address of pointer. Change structure compared to delete.
template <typename T>
extern void my_delete( T **p );

//same as above but use references instead of pointers
template <typename T>
extern void my_delete( T &p );

///--------------------------------------------------------------------------
///	MAIN
///--------------------------------------------------------------------------

int main()
{
	///--------------------------------------------------------------------------
	///	local variabiles
	///--------------------------------------------------------------------------

	//Create pointer (disable optimization to prevent compiler from optimizing the variable away
	int *p = nullptr;

	///--------------------------------------------------------------------------
	///	TEST1
	///--------------------------------------------------------------------------

	cout << "TEST1 delete\n";

	cout << "Allocate and assign\n";
	p = new int;
	*p = 42;

	show( p );

	cout << "Deallocate\n";

	delete p;

	show( p );

	cout << "NOTE: delete does not update the content of the pointer to NULL automatically\n";
	cout << "This means that you can use ip again without knowing the memory is no longer valid\n";
	cout << "-------------------------------------------\n\n";

	///--------------------------------------------------------------------------
	///	TEST2
	///--------------------------------------------------------------------------

	cout << "TEST2 macro to clear pointer\n";

	cout << "Allocate and assign\n";
	p = new int;
	*p = 42;

	show( p );

	cout << "Deallocate\n";

	MY_DELETE( p );

	show( p );

	cout << "-------------------------------------------\n\n";

	///--------------------------------------------------------------------------
	///	TEST3
	///--------------------------------------------------------------------------

	cout << "TEST3 function to clear pointer | pointer argument\n";

	cout << "Allocate and assign\n";
	p = new int;
	*p = 42;

	show( p );

	cout << "Deallocate\n";

	my_delete( &p );
	show( p );

	cout << "NOTE: the function must have access to the address of the pointer to clear it\n";
	cout << "-------------------------------------------\n\n";

	///--------------------------------------------------------------------------
	///	TEST4
	///--------------------------------------------------------------------------

	cout << "TEST4 function to clear pointer | reference argument\n";

	cout << "Allocate and assign\n";
	p = new int;
	*p = 42;

	show( p );

	cout << "Deallocate\n";

	my_delete( p );
	show( p );

	cout << "Same as above, but the argument is a reference instead of a pointer\n";
	cout << "interface is the same as delete but the function can alter the original value!\n";

    return 0;
}

///--------------------------------------------------------------------------
///	show | int *
///--------------------------------------------------------------------------
//	show the address and the content of the pointer

bool show( int *p )
{
	cout << "pointer: " << p << "\n";

	if (p != NULL)
	{
		cout << "content: " << *p << "\n";
	}
	else
	{
		return true; //FAIL
	}

	return false; //OK
}

///--------------------------------------------------------------------------
///	my_delete | T**
///--------------------------------------------------------------------------
//	Wrapper to delete
//	Use pointer argument to modify the source variabile
//	Chenges the interface compared to delete

template <typename T>
inline void my_delete( T **p )
{
	delete( *p );
	*p = nullptr;
	return;	//OK
}

///--------------------------------------------------------------------------
///	my_delete | T &
///--------------------------------------------------------------------------
//	Wrapper to delete
//	Use reference argument
//	can change the source variabile without changing the interface compared to delete

template <typename T>
inline void my_delete( T &p )
{
	delete( p );
	p = nullptr;
	return;	//OK
}
