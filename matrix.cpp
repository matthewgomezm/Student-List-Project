#include <iostream>
#include <iomanip>
#include "matrix.h"
using namespace std;


const int DEFAULTMAXROW = 6;	//created maximum values to follow assumption that invalid sizes default to 6
const int DEFAULTMAXCOL = 6;



namespace COP3330
{
	Matrix_Class::Matrix_Class()
	{
		matrix = nullptr;
		rowsize = 0;
		colsize = 0;
	}

// **********************************************************************
// Function Name: Matrix_Class()					*
// Description: Default constructor; sets columns and rows to zero.	*
// Date: 02/25/25							*
// Author: Matthew Gomez						*
// **********************************************************************


	Matrix_Class::Matrix_Class (const int r, const int c)
	{
		if (r < 2 || r > DEFAULTMAXROW)
		{
			rowsize = DEFAULTMAXROW;
		}
		else
		{
			rowsize = r;
		}


		if (c < 2 || c > DEFAULTMAXCOL)
		{
			colsize = DEFAULTMAXCOL;
		}
		else
		{
			colsize = c;
		}

		matrix = new int*[rowsize];
		for (int i = 0; i < rowsize; i++)
		{
			matrix[i] = new int[colsize];
		}

		Zero();
	}


// ******************************************************
// Function Name: Matrix_Class (const int r, const int c)
// Description: Parameterized constructor; checks to see if
// matrix has valid dimensions (2 - 6), and if not	*
// it is default to 6.					*
// Date: 02/25/25					*
// Author: Matthew Gomez				*
// ******************************************************


	Matrix_Class::~Matrix_Class()
	{
		Clear();
	}


// **********************************************
// Function Name: ~Matrix_Class()		*
// Description: Destructor; Call Clear(),	*
// sets the column and row sizes to zero.	*
// Date: 02/25/25				*
// Author: Matthew Gomez			*
// **********************************************


	void Matrix_Class::Clear()
	{
		if (matrix != nullptr)
		{
			for (int i = 0; i < rowsize; i++)
			{
				delete [] matrix[i];
			}

			delete [] matrix;
			matrix = nullptr;
		}
		
		rowsize = 0;
		colsize = 0;
	}

// **********************************************
// Function Name: Clear()			*
// Description: Deletes the current array 	*
// and sets dimensions to zero.			*
// Date: 02/25/25				*
// Author: Matthew Gomez			*
// **********************************************


	void Matrix_Class::Zero()
	{

		for (int i = 0; i < rowsize; i++)
		{
			for (int ii = 0; ii < colsize; ii++)
			{
				matrix [i][ii] = 0;
			}
		}
		
	}


// ******************************************************
// Function Name: Zero()				*
// Description: Sets all entries of the matrix to zero. *
// Date: 02/25/25					*
// Author: Matthew Gomez				*
// ******************************************************





	void Matrix_Class::Print (string msg) const	
	{
		cout << msg << endl;
		for (int i = 0; i < rowsize; i++)
		{
			for (int ii = 0; ii < colsize; ii++)
			{
				cout << matrix [i][ii] << " ";
			}
			cout << endl;
		}
		
	}
		

// **********************************************
// Function Name: Print (string msg)		*
// Description: Prints the matrix alongside 	*
// a message that is passed in from 		*
// the function call.				*
// Date: 02/25/25				*
// Author: Matthew Gomez			*
// **********************************************



	void Matrix_Class::Input ()
	{
		cout << "Please enter numbers for the following matrix: ";
		for (int i = 0; i < rowsize; i++)
		{
			for (int ii = 0; ii < colsize; ii++)
			{
				cin >> matrix [i][ii];
			}
		}
	}
		

// **********************************************
// Function Name: Input()			*
// Description: Prompts a message to the user 	*
// and takes in their input to the matrix.	*
// Date: 02/25/25				*
// Author: Matthew Gomez			*
// **********************************************


	void Matrix_Class::Resize (const int r, const int c)
	{
		if (r < 2 || r > DEFAULTMAXROW || c < 2 || c > DEFAULTMAXCOL)
		{
			cout << "No changes made; Dimensions unknown." << endl;
			return;
		}
		
		Clear();
		rowsize = r;
		colsize = c;
		matrix = new int*[rowsize];
		
		for (int i = 0; i < rowsize; i++)
		{
			matrix[i] = new int[colsize];
			for (int ii = 0; ii < colsize; ii++)
			{
				matrix[i][ii] = 0;
			}
		}

	}

// ******************************************************
// Function Name: Resize(const int r, const int c)	*
// Description: Resizes the matrix. Checks to see	*
// if parameters are valid, if not, no changes are made	*
// and function returns original matrix.		*
// Date: 02/25/25					*
// Author: Matthew Gomez				*
// ******************************************************


	Matrix_Class & Matrix_Class::operator = (const Matrix_Class &m)
	{
		if (this == &m)
		return *this;
		
		Clear();
		rowsize = m.rowsize;
		colsize = m.colsize;
		
		if (rowsize > 0 && colsize > 0)
		{
			matrix = new int*[rowsize];
			for (int i = 0; i < rowsize; i++)
			{
				matrix[i] = new int[colsize];
				for (int ii = 0; ii < colsize; ii++)
				{
					matrix [i][ii] = m.matrix[i][ii];
				}
			}
		}

		return *this;
	}


// **********************************************************************
// Function Name: Matrix_Class & operator = (const Matrix_Class &m)	*
// Description: Right Hand Side assignment operator. Allows for 	*
// the operator to copy one matrix's contents to another, and checks if *
// they are the same before it continues.				*
// Date: 02/25/25							*
// Author: Matthew Gomez						*
// **********************************************************************


	Matrix_Class & Matrix_Class::operator * (Matrix_Class &m1)
	{
		if (colsize != m1.Getrowsize())
		{
			cout << "Invalid dimensions for multiplication.";
			return *this;
			
		}
		
		int m = rowsize;
		int n = colsize;
		int l = m1.Getcolsize();

		int ** C = new int *[m];
		for (int i = 0; i < m; i++)
		{
			C[i] = new int [l];
		}
		
		for (int i = 0; i < m; i++)
		{
			for (int ii = 0; ii < l; ii++)
			{
				C[i][ii] = 0;
				for (int j = 0; j < n; j++)
				{
					C[i][ii] += matrix[i][j] * m1.matrix[j][ii];
				}
			}
		}
			

		Clear();
		rowsize = m;
		colsize = l;
		matrix = C;
		
		return *this;
	}
		

// **********************************************************************
// Function Name:  Matrix_Class & operator * (Matrix_Class &m1)		*
// Description: Multiplies the two matrices and returns the product.	*
// (Referenced from Dr. Gaitros' C program on canvas) Function also	*
// checks if the dimensions are invalid between the two. 		*
// Date: 02/25/25							*
// Author: Matthew Gomez						*
// **********************************************************************
		






}

