#include<bits/stdc++.h>
using namespace std;
const int MAX = 50 ;
class infix
{
	private :
		char target[MAX], stack[MAX] ;
		char *s, *t ;
		int top, l ;
	public :
		infix( ) ;
		void setexpr ( char *str ) ;
		void push ( char c ) ;
		char pop( ) ;
		void convert( ) ;
		int priority ( char c ) ;
		void show( ) ;
} ;
infix :: infix( )
{
	top = -1 ;
	strcpy ( target, "" ) ;
	strcpy ( stack, "" ) ;
	l = 0 ;
}
void infix :: setexpr ( char *str )
{
	s = str ;
	strrev ( s ) ;
	l = strlen ( s ) ;
	* ( target + l ) = '\0' ;
	t = target + ( l - 1 ) ;
}
void infix :: push ( char c )
{
	if ( top == MAX - 1 )
		cout << "\nStack is full\n" ;
	else
	{
		top++ ;
		stack[top] = c ;
	}
}
char infix :: pop( )
{
	if ( top == -1 )
	{
		cout << "Stack is empty\n" ;
		return -1 ;
	}
	else
	{
		char item = stack[top] ;
		top-- ;
		return item ;
	}
}
void infix :: convert( )
{
	char opr ;

	while ( *s )
	{
		if ( *s == ' ' || *s == '\t' )
		{
			s++ ;
			continue ;
		}

		if ( isdigit ( *s ) || isalpha ( *s ) )
		{
			while ( isdigit ( *s ) || isalpha ( *s ) )
			{
				*t = *s ;
				s++ ;
				t-- ;
			}
		}

		if ( *s == ')' )
		{
			push ( *s ) ;
			s++ ;
		}

		if ( *s == '*' || *s == '+' || *s == '/' ||
				*s == '%' || *s == '-' || *s == '$' )
		{
			if ( top != -1 )
			{
				opr = pop( ) ;

				while ( priority ( opr ) > priority ( *s ) )
				{
					*t = opr ;
					t-- ;
					opr = pop( ) ;
				}
				push ( opr ) ;
				push ( *s ) ;
			}
			else
				push ( *s ) ;
			s++ ;
		}

		if ( *s == '(' )
		{
			opr = pop( ) ;
			while ( ( opr ) != ')' )
			{
				*t = opr ;
				t-- ;
				opr =  pop ( ) ;
			}
			s++ ;
		}
	}

	while ( top != -1 )
	{
		opr = pop( ) ;
		*t = opr ;
		t-- ;
	}
	t++ ;
}
int infix :: priority ( char c )
{
	if ( c == '$' )
		return 3 ;
	if ( c == '*' || c == '/' || c == '%' )
		return 2 ;
	else
	{
		if ( c == '+' || c == '-' )
			return 1 ;
		else
			return 0 ;
	}
}
void infix :: show( )
{
	while ( *t )
	{
		cout << " " << *t ;
		t++ ;
	}
}

int main( )
{
	char expr[MAX] ;
	infix q ;

	cout << "\nEnter an expression in infix form: " ;
	cin.getline ( expr, MAX ) ;

	q.setexpr( expr ) ;
	q.convert( ) ;

	cout << "The Prefix expression is: " ;
	q.show( ) ;
}
