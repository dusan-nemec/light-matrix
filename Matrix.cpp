#include "Matrix.h"
#include <memory>

// Creates empty matrix
Matrix::Matrix()
	: _data(NULL), _usage(new int(1)), _rows(0), _cols(0), _rInc(0), _cInc(0) {}


// Copies matrix
Matrix::Matrix(const Matrix& ptR)
{
	// Plain copy of wrapper
	memcpy(this, &ptR, sizeof(Matrix));
	
	// Increase usage
	++(*_usage);
}

// Creates matrix with given dimensions. Leaves all elements uninitialized.
Matrix::Matrix(int rows, int cols)
	: _usage(new int(1))
{
	if (rows == 0 || cols == 0)
	{
		_data = NULL;
		_rows = 0;
		_cols = 0;
		_rInc = 0;
		_cInc = 0;
	}
	else
	{
		_data = new float[rows*cols];
		_rows = rows;
		_cols = cols;
		_rInc = cols;
		_cInc = 1;
	}
}

// Creates matrix with given size. Leaves all elements uninitialized.
Matrix::Matrix(Size sz) : Matrix(sz.rows, sz.cols) { }

// Creates matrix from vector of floats (column vector)
Matrix::Matrix(const std::vector<float>& vec)
	: Matrix((int)vec.size(), 1)
{
	if (!_data) // empty matrix
		return; 

	// copy plain
	memcpy(_data, vec.data(), _rows*sizeof(float));
}

// Destructor
Matrix::~Matrix()
{
	// Decrease usage and check
	if (--(*_usage) == 0)
	{
		// No more usage
		if (_data)
			delete[] _data;

		delete _usage;
	}

	
}

// Makes current storage unique (e.g. on change)
void Matrix::_unique()
{
	if ((*_usage) == 1 || _data == NULL)
		return; // already unique or empty

	// Allocate new space and copy content plain
	float* newData = new float[_rows*_cols];
	memcpy(newData, _data, _rows*_cols*sizeof(float));

	// Allocate new usage pointer
	int* newUsage = new int(1);

	// Decrease existing usage
	--(*_usage);

	// Assign new data and usage pointer
	_data = newData;
	_usage = newUsage;
}

// Sums two matrices
Matrix Matrix::operator + (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = this->at(r, c) + ptR.at(r, c);
	
	return res;
}

// Sums two matrices
const Matrix& Matrix::operator += (const Matrix& ptR)
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix: Dimension mismatch.");

	_unique();

	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			this->_at(r,c) += ptR.at(r, c);

	return (*this);
}

// Sum of matrix and scalar
Matrix Matrix::operator + (float val) const
{
	Matrix res(_rows, _cols);
	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = this->at(r, c) + val;

	return res;
}

const Matrix& Matrix::operator += (float val)
{
	_unique();

	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			this->_at(r, c) += val;

	return (*this);
}

// Subtracts two matrices
Matrix Matrix::operator - (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = this->at(r, c) - ptR.at(r, c);

	return res;
}


const Matrix& Matrix::operator -= (const Matrix& ptR)
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix: Dimension mismatch.");

	_unique();

	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			this->_at(r, c) -= ptR.at(r, c);

	return (*this);
}

// Subtracts scalar from matrix
Matrix Matrix::operator - (float val) const
{
	Matrix res(_rows, _cols);
	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = this->at(r, c) - val;

	return res;
}

const Matrix& Matrix::operator -= (float val)
{
	_unique();

	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			this->_at(r, c) -= val;

	return (*this);
}

// Unary minus
Matrix Matrix::operator -() const
{
	Matrix res(_rows, _cols);
	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = -this->at(r, c);

	return res;
}

// Multiplies two matrices
Matrix Matrix::operator * (const Matrix& ptR) const
{
	if (_cols != ptR._rows)
		throw std::invalid_argument("Matrix: Dimension mismatch.");

	const int resRows = _rows;
	const int resCols = ptR._cols;

	Matrix res(resRows, resCols);

	float* dst = res._data;
	for (int r = 0; r < resRows; r++)
	{
		for (int c = 0; c < resCols; c++)
		{
			float val = 0;

			for (int k = 0; k < _cols; k++)
				val += this->at(r, k) * ptR.at(k, c); 

			(*dst++) = val;
		}
	}

	return res;
}

// Multiplies matrix by scalar
Matrix Matrix::operator * (float val) const
{
	Matrix res(_rows, _cols);
	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = this->at(r, c) * val;

	return res;
}

const Matrix& Matrix::operator *= (float val)
{
	_unique();

	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			this->_at(r, c) *= val;

	return (*this);
}

// Divides matrix by a scalar
Matrix Matrix::operator / (float val) const
{
	Matrix res(_rows, _cols);
	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			(*dst++) = this->at(r, c) / val;

	return res;
}

const Matrix& Matrix::operator /= (float val)
{
	_unique();

	for (int r = 0; r < _rows; r++)
		for (int c = 0; c < _cols; c++)
			this->_at(r, c) /= val;

	return (*this);
}

Matrix::operator float() const
{
	if (_rows != 1 || _cols != 1)
		throw "Matrix: Matrix is not scalar.";

	return (*_data);
}

// Transposes matrix
Matrix Matrix::t() const
{
	// Copy matrix wrapper
	Matrix res(*this);

	// Swap rows and columns and their increments
	res._rows = _cols;
	res._cols = _rows;
	res._rInc = _cInc;
	res._cInc = _rInc;

	return res;
}

// Inverts matrix
Matrix Matrix::inv() const
{
	static const char* msg = "Matrix: Matrix is not invertible.";

	if (_rows != _cols)
		throw std::runtime_error(msg);
	
	const int n = _rows;
	const int n2 = 2 * _rows;

	// Fill tmp with A|E
	Matrix tmp(n, n2);

	float* dst = tmp._data;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < n; c++)
			(*dst++) = this->at(r, c);

		for (int c = 0; c < n; c++)
			(*dst++) = (r == c) ? 1.0f : 0.0f;
	}

	// first consollidate values bellow diagonal
	for (int r = 0; r < n; r++)
	{
		// ensure that row starts with nonzero value, else swap
		int r_new = r;
		while (r_new < n && tmp.at(r_new, r) == 0.0f)
			r_new++;

		if (r_new >= n)
			throw std::runtime_error(msg);

		if (r_new != r)
		{
			// swap rows. Since tmp is newly constructed, it has row-by-row memory order.
			float* row1 = tmp._data + r * n2;
			float* row2 = tmp._data + r_new * n2;

			for (int i = 0; i < n2; i++)
			{
				float x = row1[i];
				row1[i] = row2[i];
				row2[i] = x;
			}
		}

		// normalize row
		dst = tmp._data + r * n2 + r; // start at r-th element, prev elements are 0
		float coef = 1/(*dst);
		for (int i = r; i < n2; i++)
			(*dst++) *= coef;

		// eliminate elements below [r,r] position (k > r)
		// row[k] = row[k] - cell[k,r] * row[r];
		for (int k = r + 1; k < n; k++)
		{
			const float* src = tmp._data + r * n2 + r; // normalized row
			dst = tmp._data + k * n2 + r; // start at r-th element, prev elements are 0
			coef = -(*dst);
			for (int i = r; i < n2; i++)
				(*dst++) += coef * (*src++);
		}
	}

	// now eliminate values above diagonal
	for (int r = n-1; r >= 0; r--)
	{
		// eliminate elements above [r,r] position (k < r)
		// row[k] = row[k] - cell[k,r] * row[r]
		for (int k = r - 1; k >= 0; k--)
		{
			const float* src = tmp._data + r * n2 + r; // normalized row
			dst = tmp._data + k * n2 + r; // start at r-th element, prev elements are 0
			const float coef = -(*dst); // cell[k,r]
			for (int i = r; i < n2; i++)
				(*dst++) += coef * (*src++);
		}
	}

	// copy second half as result
	Matrix res(n, n);
	for (int r = 0; r < n; r++)
		memcpy(res._data + r*n, tmp._data + r*n2 + n, n * sizeof(float));
	
	return res;
}

// Solves system A * X = B
Matrix Matrix::solve(const Matrix& matA, const Matrix& matB)
{
	try
	{
		if (matA._rows == matA._cols)
		{
			// normal inversion
			return (matA.inv() * matB);
		}
		else
		{
			// pseudoinversion
			Matrix matAt = matA.t();
			return (matAt * matA).inv() * matAt * matB;
		}
	}
	catch (std::runtime_error)
	{
		return Matrix(); // system can not be solved
	}
}

// Multiplies matrix by matrix element by element
Matrix Matrix::elemProd(const Matrix& ptL, const Matrix& ptR)
{
	if (ptL._rows != ptR._rows || ptL._cols != ptR._cols)
		throw std::invalid_argument("Matrix::elemProd: Dimension mismatch.");

	Matrix res(ptL._rows, ptL._cols);

	float* dst = res._data;
	for (int r = 0; r < ptL._rows; r++)
		for (int c = 0; c < ptL._cols; c++)
			(*dst++) = ptL.at(r,c) * ptR.at(r,c);

	return res;
}

// Divides matrix by matrix element by element
Matrix Matrix::elemDiv(const Matrix& ptL, const Matrix& ptR)
{
	if (ptL._rows != ptR._rows || ptL._cols != ptR._cols)
		throw std::invalid_argument("Matrix::elemDiv: Dimension mismatch.");

	Matrix res(ptL._rows, ptL._cols);

	float* dst = res._data;
	for (int r = 0; r < ptL._rows; r++)
		for (int c = 0; c < ptL._cols; c++)
			(*dst++) = ptL.at(r,c) / ptR.at(r,c);

	return res;
}


// Returns given row as a matrix
Matrix Matrix::row(int idx) const
{
	if (idx >= _rows)
		throw std::out_of_range("Matrix: Index out of range.");

	Matrix res(1, _cols);

	float* dst = res._data;
	for (int c = 0; c < _cols; c++)
		(*dst++) = this->at(idx, c);

	return res;
}

// Returns given column as a matrix
Matrix Matrix::column(int idx) const
{
	if (idx >= _cols)
		throw std::out_of_range("Matrix: Index out of range.");

	Matrix res(_rows, 1);

	float* dst = res._data;
	for (int r = 0; r < _rows; r++)
		(*dst++) = this->at(r, idx);

	return res;
}

// Returns sum of all elements
float Matrix::sum() const
{
	float res = 0.0f;
	const float* src = _data;
	for (int i = 0; i < _rows*_cols; i++)
		res += (*src++);

	return res;
}

// Converts matrix to vector (if possible)
Matrix::operator std::vector<float>() const
{
	if (_cols != 1)
		throw std::runtime_error("Matrix: matrix is not a column vector.");

	std::vector<float> res(_rows);

	for (int r = 0; r < _rows; r++)
		res[r] = this->at(r, 0);

	return res;
}


// Returns unit matrix.
Matrix Matrix::eye(int size)
{
	Matrix res(size, size);

	float* dst = res._data;
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			(*dst++) = (r == c) ? 1.0f : 0.0f;

	return res;
}

// Sets all elements to zero.
void Matrix::clear()
{
	_unique();

	for (int i = 0; i < _rows * _cols; i++)
		_data[i] = 0.0f;
}

// Assign operator
const Matrix& Matrix::operator = (const Matrix& ptR)
{
	if (this == &ptR)
		return (*this); // nothing to do

	// Decrease existing usage
	if (--(*_usage) == 0)
	{
		// unique, delete existing storage
		if (_data)
			delete[] _data;

		delete _usage;
	}

	// copy wrapper
	memcpy(this, &ptR, sizeof(Matrix));

	// increase use counter
	++(*_usage);

	return (*this);
}

// Sets all elements to uniformly distributed random numbers from given interval.
void Matrix::rand(float min, float max)
{
	_unique();

	for (int i = 0; i < _rows * _cols; i++)
		_data[i] = (float)std::rand() * (max - min) / RAND_MAX + min;
}

// Reshapes matrix to given size row by row.
Matrix Matrix::reshape(int newRows, int newCols) const
{
	if (newRows * newCols != _rows * _cols)
		throw std::invalid_argument("Matrix: reshape dimensions invalid.");

	if (newRows * newCols == 0)
		return Matrix(); // nothing to do

	// change memory order
	if (_rInc == _cols && _cInc == 1)
	{
		// original has row-by-row order, copy wrapper and  change only dimensions
		Matrix res(*this);
		res._rows = newRows;
		res._cols = newCols;
		res._rInc = newCols;
		res._cInc = 1;

		return res;
	}
	else
	{
		// original has column-by-column order, copy content with changed memory order
		Matrix res(newRows, newCols);
		float* dst = res._data;
		for (int r = 0; r < _rows; r++)
			for (int c = 0; c < _cols; c++)
				(*dst++) = this->at(r, c);

		return res;
	}
}

// Changes dimensions of the matrix. Keeps contents within possible indices.
void Matrix::resize(int newRows, int newCols)
{
	if (newRows == _rows && newCols == _cols)
		return; // nothing to do

	// allocate new space
	float* newData;
	if (newRows * newCols > 0)
	{
		newData = new float[newRows*newCols];

		// copy content row by row
		float* dst = newData;
		for (int r = 0; r < newRows; r++)
		{
			for (int c = 0; c < newCols; c++)
			{
				if (r < _rows && c < _cols)
					(*dst++) = this->at(r, c);
				else
					(*dst++) = 0.0f;
			}
		}

		// set dimensions
		_rows = newRows;
		_cols = newCols;
		_rInc = newCols;
		_cInc = 1;
	}
	else
	{
		// set empty dimensions
		newData = NULL;
		_rows = 0;
		_cols = 0;
		_rInc = 0;
		_cInc = 0;
	}


	if ((*_usage) == 1)
	{
		// unique, delete old storage, keep unique usage
		if (_data)
			delete[] _data;
	}
	else
	{
		// decrease usage
		--(*_usage);

		// allocate new usage
		_usage = new int(1);
	}

	// assign new data
	_data = newData;
}


// Stream read operator
std::istream& operator >> (std::istream& str, Matrix& mat)
{
	int rows, cols;
	str >> rows >> cols;
	
	if (rows < 0 || cols < 0)
		throw std::runtime_error("Matrix stream read: Negative dimensions.");

	mat.resize(rows, cols);

	for (int r = 0; r < mat.rows(); r++)
		for (int c = 0; c < mat.columns(); c++)
			str >> mat._at(r, c);

	return str;
}

// Stream write operator
std::ostream& operator << (std::ostream& str, const Matrix& mat)
{
	str << mat.rows() << "\t" << mat.columns() << std::endl;
	for (int r = 0; r < mat.rows(); r++)
	{
		for (int c = 0; c < mat.columns(); c++)
			str << mat.at(r, c) << "\t";

		// write new line
		str << std::endl;
	}
	return str;
}

// Returns minimum of two matrices (elementwise).
Matrix min(const Matrix& matA, const Matrix& matB)
{
	if (matA._rows != matB._rows || matA._cols != matB._cols)
		throw std::invalid_argument("Matrix::min: Dimension mismatch.");

	Matrix res(matA._rows, matA._cols);
	
	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float A = matA.at(r, c);
			float B = matB.at(r, c);

			if (A < B)
				(*dst++) = A;
			else
				(*dst++) = B;
		}
	}

	return res;
}	

// Returns maximum of two matrices (elementwise).
Matrix max(const Matrix& matA, const Matrix& matB)
{
	if (matA._rows != matB._rows || matA._cols != matB._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(matA._rows, matA._cols);
	
	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float A = matA.at(r,c);
			float B = matB.at(r,c);

			if (A > B)	
				(*dst++) = A;
			else
				(*dst++) = B;
		}
	}

	return res;
}

// Comparison operators between two matrices. Returns binary matrix with elements {0.0, 1.0}.
Matrix Matrix::operator >  (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if(this->at(r, c) > ptR.at(r, c))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator >= (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) >= ptR.at(r, c))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator <  (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) < ptR.at(r, c))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator <= (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) <= ptR.at(r, c))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator == (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) == ptR.at(r, c))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator != (const Matrix& ptR) const
{
	if (_rows != ptR._rows || _cols != ptR._cols)
		throw std::invalid_argument("Matrix::max: Dimension mismatch.");

	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) != ptR.at(r, c))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

// Comparison operators between matrix and scalar. Returns binary matrix with elements {0.0, 1.0}.
Matrix Matrix::operator >  (float val) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) > val)
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator >= (float val) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) >= val)
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator <  (float val) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) < val)
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator <= (float val) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) <= val)
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator == (float val) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) == val)
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

Matrix Matrix::operator != (float val) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (this->at(r, c) != val)
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

// Returns binary matrix with elements {0.0, 1.0}. Element is set when it is between given boundaries.
Matrix Matrix::isBetween(float minVal, float maxVal) const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float x = this->at(r, c);
			if (x > minVal && x < maxVal)

				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

// Returns binary matrix with elements {0.0, 1.0}. Element is set when it is NaN.
Matrix Matrix::isNaN() const
{
	Matrix res(_rows, _cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			if (isnan(this->at(r, c)))
				(*dst++) = 1.0f;
			else
				(*dst++) = 0.0f;
		}
	}

	return res;
}

// Returns minimum of matrix and given value (elementwise).
Matrix min(const Matrix& mat, float val)
{
	Matrix res(mat._rows, mat._cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float x = mat.at(r, c);
			if (x < val)
				(*dst++) = x;
			else
				(*dst++) = val;
		}
	}

	return res;
}

// Returns maximum of matrix and given value (elementwise).
Matrix max(const Matrix& mat, float val)
{
	Matrix res(mat._rows, mat._cols);

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float x = mat.at(r, c);
			if (x > val)
				(*dst++) = x;
			else
				(*dst++) = val;
		}
	}

	return res;
}

// Returns absolute value of the matrix (elementwise).
Matrix abs(const Matrix& mat)
{
	Matrix res(mat.size());
	
	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
		for (int c = 0; c < res._cols; c++)
			(*dst++) = std::abs(mat.at(r,c));

	return res;
}

// Returns square root of the matrix (elementwise).
Matrix sqrt(const Matrix& mat)
{
	Matrix res(mat.size());
	
	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
		for (int c = 0; c < res._cols; c++)
			(*dst++) = std::sqrt(mat.at(r,c));

	return res;
}

// Returns natural logarithm of the matrix (elementwise).
Matrix log(const Matrix& mat)
{
	Matrix res(mat.size());

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
		for (int c = 0; c < res._cols; c++)
			(*dst++) = std::log(mat.at(r, c));

	return res;
}

// Returns exponential function of the matrix (elementwise).
Matrix exp(const Matrix& mat)
{
	Matrix res(mat.size());

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
		for (int c = 0; c < res._cols; c++)
			(*dst++) = std::exp(mat.at(r, c));

	return res;
}

// Returns softplus function of the matrix (elementwise).
Matrix softplus(const Matrix& mat)
{
	Matrix res(mat.size());

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float x = mat.at(r, c);
			if (x > 20.0f)			(*dst++) = x;
			else if (x < -20.0f)	(*dst++) = 0.0f;
			else					(*dst++) = std::log(std::exp(x) + 1.0f);
		}
	}

	return res;
}

// Returns sigmoid function of the matrix (elementwise).
Matrix sigmoid(const Matrix& mat)
{
	Matrix res(mat.size());

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
	{
		for (int c = 0; c < res._cols; c++)
		{
			float x = mat.at(r, c);

			if (x > 20.0f)			(*dst++) = 1.0f;
			else if (x < -20.0f)	(*dst++) = 0.0f;
			else					(*dst++) = 1.0f / (std::exp(-x) + 1.0f);
		}
	}

	return res;
}

// Returns hyperbolic tangent of the matrix (elementwise).
Matrix tanh(const Matrix& mat)
{
	Matrix res(mat.size());

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
		for (int c = 0; c < res._cols; c++)
			(*dst++) = std::tanh(mat.at(r, c));

	return res;
}

Matrix operator * (float val, const Matrix& mat) { return (mat * val); }
Matrix operator + (float val, const Matrix& mat) { return (mat + val); }
Matrix operator - (float val, const Matrix& mat) { return (-mat + val); }

Matrix operator / (float val, const Matrix& mat)
{
	Matrix res(mat.size());

	float* dst = res._data;
	for (int r = 0; r < res._rows; r++)
		for (int c = 0; c < res._cols; c++)
			(*dst++) = val / mat.at(r, c);

	return res;
}
