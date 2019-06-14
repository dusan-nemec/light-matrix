#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <cstdlib>
#include <vector>
#include <iostream>

// Size of the matrix
struct Size
{
	int rows;
	int cols;

	Size() : rows(0), cols(0) {}
	Size(int _rows) : rows(_rows), cols(1) {}
	Size(int _rows, int _cols) : rows(_rows), cols(_cols) {}

	// Returns count of elements
	int count() const { return (rows * cols); }

	// Comparison operators
	bool operator == (const Size& sz) const { return (rows == sz.rows && cols == sz.cols); }
	bool operator != (const Size& sz) const { return (rows != sz.rows || cols != sz.cols); }
};

// Implements 2D matrix of real numbers (float)
class Matrix
{
private:
	float* _data;
	int* _usage;
	int _rows;
	int _cols;
	int _rInc;
	int _cInc;

	// Makes current storage unique (e.g. on change)
	void _unique();

public:
	// Creates empty matrix
	Matrix();

	// Copies matrix
	Matrix(const Matrix&);

	// Creates matrix with given dimensions. Leaves all elements uninitialized.
	Matrix(int rows, int cols);

	// Creates matrix with given size. Leaves all elements uninitialized.
	Matrix(Size sz);

	// Creates matrix from vector of floats (column vector)
	Matrix(const std::vector<float>& vec);

	// Destructor
	~Matrix();

	// Sums two matrices
	Matrix operator + (const Matrix& ptR) const;
	const Matrix& operator += (const Matrix& ptR);

	// Sum of matrix and scalar
	Matrix operator + (float val) const;
	const Matrix& operator += (float val);

	// Subtracts two matrices
	Matrix operator - (const Matrix& ptR) const;
	const Matrix& operator -= (const Matrix& ptR);

	// Subtracts scalar from matrix
	Matrix operator - (float val) const;
	const Matrix& operator -= (float val);

	// Unary minus
	Matrix operator -() const;

	// Multiplies two matrices
	Matrix operator * (const Matrix& ptR) const;

	// Multiplies matrix by scalar
	Matrix operator * (float val) const;
	const Matrix& operator *= (float val);

	// Divides matrix by scalar
	Matrix operator / (float val) const;
	const Matrix& operator /= (float val);

	// Converts matrix to scalar if possible.
	explicit operator float() const;

	// Transposes matrix
	Matrix t() const;

	// Inverts matrix
	Matrix inv() const;

	// Solves system A * X = B
	// Note: trans(X) * trans(A) = trans(B) is equivalent
	static Matrix solve(const Matrix& matA, const Matrix& matB);

	// Multiplies matrix by matrix element by element
	static Matrix elemProd(const Matrix& ptL, const Matrix& ptR);

	// Divides matrix by matrix element by element
	static Matrix elemDiv(const Matrix& ptL, const Matrix& ptR);

	// Returns number of rows
	int rows() const { return _rows; }

	// Returns number of columns
	int columns() const { return _cols; }

	// Returns true when empty
	bool empty() const { return (_data == NULL); }

	// Returns size of the matrix in struct
	Size size() const { return Size(_rows, _cols); }

	// Returns count of elements
	int count() const { return (_rows * _cols); }

	// Returns given row as a matrix
	Matrix row(int idx) const;

	// Returns given column as a matrix
	Matrix column(int idx) const;

	// Returns sum of all elements
	float sum() const;

	// Element access. UNSAFE, check indices boundaries. 
	float at(int row, int col) const { return _data[row * _rInc + col * _cInc]; }
	float& at(int row, int col) { _unique(); return _data[row * _rInc + col * _cInc]; }

	// Converts matrix to vector (if possible)
	operator std::vector<float>() const;

	// Returns unit matrix.
	static Matrix eye(int size);

	// Sets all elements to zero.
	void clear();

	// Sets all elements to uniformly distributed random numbers from given interval.
	void rand(float min = 0.0f, float max = 1.0f);

	// Assign operator
	const Matrix& operator = (const Matrix& ptR);

	// Reshapes matrix to given size row by row.
	Matrix reshape(int newRows, int newCols) const;
	Matrix reshape(Size sz) const { return reshape(sz.rows, sz.cols); }

	// Changes dimensions of the matrix. Keeps contents within possible indices. Excess fields initializes to zero.
	void resize(int newRows, int newCols);
	void resize(Size sz) { resize(sz.rows, sz.cols); }
	
	// Comparison operators between two matrices. Returns binary matrix with elements {0.0, 1.0}.
	Matrix operator >  (const Matrix& ptR) const;
	Matrix operator >= (const Matrix& ptR) const;
	Matrix operator <  (const Matrix& ptR) const;
	Matrix operator <= (const Matrix& ptR) const;
	Matrix operator == (const Matrix& ptR) const;
	Matrix operator != (const Matrix& ptR) const;

	// Comparison operators between matrix and scalar. Returns binary matrix with elements {0.0, 1.0}.
	Matrix operator >  (float val) const;
	Matrix operator >= (float val) const;
	Matrix operator <  (float val) const;
	Matrix operator <= (float val) const;
	Matrix operator == (float val) const;
	Matrix operator != (float val) const;

	// Returns binary matrix with elements {0.0, 1.0}. Element is set when it is between given boundaries.
	Matrix isBetween(float minVal, float maxVal) const;

	// Returns binary matrix with elements {0.0, 1.0}. Element is set when it is NaN.
	Matrix isNaN() const;

	// Global operators and functions
	friend std::istream& operator >> (std::istream& str, Matrix& mat);
	friend std::ostream& operator << (std::ostream& str, const Matrix& mat);
	friend Matrix min(const Matrix& matA, const Matrix& matB);
	friend Matrix max(const Matrix& matA, const Matrix& matB);
	friend Matrix min(const Matrix& mat, float val);
	friend Matrix max(const Matrix& mat, float val);
	friend Matrix abs(const Matrix& mat);
	friend Matrix sqrt(const Matrix& mat);
	friend Matrix log(const Matrix& mat);
	friend Matrix exp(const Matrix& mat);
	friend Matrix softplus(const Matrix& mat);
	friend Matrix sigmoid(const Matrix& mat);
	friend Matrix tanh(const Matrix& mat);
	friend Matrix operator / (float val, const Matrix& mat);

private:
	// Element access. _unique() has to be called before but only once.
	float& _at(int row, int col) { return _data[row*_rInc + col*_cInc]; }
};

// Global operators for convenience
Matrix operator * (float val, const Matrix& mat);
Matrix operator + (float val, const Matrix& mat);
Matrix operator - (float val, const Matrix& mat);
Matrix operator / (float val, const Matrix& mat);

// Stream read operator
std::istream& operator >> (std::istream& str, Matrix& mat);

// Stream write operator
std::ostream& operator << (std::ostream& str, const Matrix& mat);

// Returns minimum of two matrices (elementwise).
Matrix min(const Matrix& matA, const Matrix& matB);

// Returns maximum of two matrices (elementwise).
Matrix max(const Matrix& matA, const Matrix& matB);

// Returns minimum of matrix and given value (elementwise).
Matrix min(const Matrix& mat, float val);

// Returns maximum of matrix and given value (elementwise).
Matrix max(const Matrix& mat, float val);

// Returns absolute value of the matrix (elementwise).
Matrix abs(const Matrix& mat);

// Returns square root of the matrix (elementwise).
Matrix sqrt(const Matrix& mat);

// Returns natural logarithm of the matrix (elementwise).
Matrix log(const Matrix& mat);

// Returns exponential function of the matrix (elementwise).
Matrix exp(const Matrix& mat);

// Returns softplus function of the matrix (elementwise).
Matrix softplus(const Matrix& mat);

// Returns sigmoid function of the matrix (elementwise).
Matrix sigmoid(const Matrix& mat);

// Returns hyperbolic tangent of the matrix (elementwise).
Matrix tanh(const Matrix& mat);

#endif // _MATRIX_H_