#ifndef MATH_HPP
#define MATH_HPP
/*	

Linear Algerbra math library 
github.com/138paulmiller

*/

#include <iostream>
#include <exception>
#include <array>
#include <initializer_list>
#include <assert.h>
#include <math.h>
#include <iomanip>
#include <string>

namespace lamath{
/******************************************** Forward Decls *********************************************/
	static long precision = 10;			//variable 
	static double epsilon = 0.001f;			 
	template <typename ELEM_T, int DIM>
	class Vec;
	template <typename ELEM_T, int DIM_H, int DIM_W>
	class Mat;
	template <typename ELEM_T, int DIM>
	class Ray;

/********************************************* Common Types *******************************************/			
	template <typename T> using Vec2 = Vec<T, 2>;
	template <typename T> using Vec3 = Vec<T, 3>;
	template <typename T> using Vec4 = Vec<T, 4>;

	template <typename T> using Ray2 = Ray<T, 2>;
	template <typename T> using Ray3 = Ray<T, 3>;
	template <typename T> using Ray4 = Ray<T, 4>;

	template <typename T> using Mat2x2 = Mat<T, 3, 3>;
	template <typename T> using Mat3x3 = Mat<T, 3, 3>;
	template <typename T> using Mat4x4 = Mat<T, 4, 4>;

	using Vec2i = Vec2<int>;
	using Vec2f = Vec2<double>;

	using Vec3i = Vec3<int>;
	using Vec3f = Vec3<double>;

	using Vec4i = Vec4<int>;
	using Vec4f = Vec4<double>;

	using Ray3i = Ray3<int>;
	using Ray3f = Ray3<double>;

	using Mat3x3i = Mat3x3<int>;
	using Mat3x3f = Mat3x3<double>;

	using Mat4x4i = Mat4x4<int>;
	using Mat4x4f = Mat4x4<double>;
	
/**************************************  Helper Macros  **************************************************/
	#define VEC_TYPE Vec<ELEM_T, DIM>
	#define MAT_TYPE Mat<ELEM_T, DIM_H, DIM_W>
	#define RAY_TYPE Ray<ELEM_T, DIM>

	//test if almost equal 
	inline bool almost_equal(double a, double b){ return fabs(b-a) < epsilon; }

/****************************** Overloaded Friend operators **************************************************/
	
	template <typename ELEM_T, int DIM>
	std::ostream & operator<<(std::ostream & os, const VEC_TYPE & vec);

	template <typename ELEM_T, int DIM_H, int DIM_W>
	std::ostream& operator<<(std::ostream & oss, const MAT_TYPE& mat);

/***************************************************** Vec **************************************************/
	class MathException : public std::exception{
	public:
		MathException(const std::string & msg ):msg(msg){}
		std::string what(){return msg;}
		std::string msg;
	};


	template <typename ELEM_T, int DIM>
	class Vec{
		private:
			std::array<ELEM_T, DIM> _elements;
		public:

			Vec(ELEM_T value =0);
			Vec(std::initializer_list<ELEM_T> ilist);
			Vec(const VEC_TYPE &other);
	
			// Accessors 
			inline ELEM_T& operator[](const int & index);
			inline const ELEM_T& operator[](const int & index)const ;
			inline ELEM_T magnitude()const;
			inline ELEM_T magnitude2()const;
			inline VEC_TYPE normal()const ;
			// Modifiers
			inline VEC_TYPE operator=(const VEC_TYPE & rhs);
			inline void normalize(); 
			inline void fill(ELEM_T value); 

			//unary operators
			inline VEC_TYPE operator-()const;

			// Binary Vector operations
			inline ELEM_T dot(const VEC_TYPE & rhs)const;
			inline VEC_TYPE cross(const VEC_TYPE & rhs)const;
			inline VEC_TYPE operator+(const VEC_TYPE & rhs) const;
			inline VEC_TYPE operator-(const VEC_TYPE & rhs)const;
			inline VEC_TYPE operator*(const VEC_TYPE & scalar)const;
			inline VEC_TYPE operator/(const VEC_TYPE & scalar)const;
			inline VEC_TYPE operator+(const ELEM_T & scalar) const;
			inline VEC_TYPE operator-(const ELEM_T & scalar)const;
			inline VEC_TYPE operator*(const ELEM_T & scalar)const;
			inline VEC_TYPE operator/(const ELEM_T & scalar)const;

			inline VEC_TYPE operator+=(const VEC_TYPE & rhs);
			inline VEC_TYPE operator-=(const VEC_TYPE & rhs);
			inline VEC_TYPE operator*=(const VEC_TYPE & rhs);
			inline VEC_TYPE operator/=(const VEC_TYPE & rhs);


			inline VEC_TYPE operator+=(const ELEM_T & scalar);
			inline VEC_TYPE operator-=(const ELEM_T & scalar);
			inline VEC_TYPE operator*=(const ELEM_T & scalar);
			inline VEC_TYPE operator/=(const ELEM_T & scalar);

			inline bool operator==(const VEC_TYPE & rhs)const;
			inline bool operator!=(const VEC_TYPE & rhs)const;
									
			//Friends
			template <typename _ELEM_T, int _DIM>
			friend std::ostream & operator<< (std::ostream & os, const Vec<_ELEM_T, _DIM> & vec);
	};

/********************************************* Ray ********************************************************/
	template <typename ELEM_T, int DIM>
	class Ray{
		private:
			Vec<ELEM_T, DIM> _origin, _dir;
		public:
			Ray();
			Ray(const Vec<ELEM_T, DIM> &origin, const Vec<ELEM_T, DIM> & dir);
			
			inline void set(const Vec<ELEM_T, DIM> & origin, const Vec<ELEM_T, DIM> & dir);
	
			inline const Vec<ELEM_T, DIM> & origin() const ;
			inline const Vec<ELEM_T, DIM> & direction() const ;
	
			inline void setOrigin(const Vec<ELEM_T, DIM> & origin);
			inline void setDirection(const Vec<ELEM_T, DIM> & dir);
			const Vec<ELEM_T, DIM> point(ELEM_T t) const; //return point at dist t from origin toward dir 
	};

/************************************************ Mat ******************************************************/
	template <typename ELEM_T, int DIM_H, int DIM_W>
	class Mat{
		/*
			Mat<int, M,N> has M rows and N columns.
		*/
		private:
			using Vec_T = Vec<ELEM_T, DIM_W>;
			std::array<Vec_T, DIM_H> _elements;
		public:
			Mat(ELEM_T value=ELEM_T(0));
			Mat(std::initializer_list<ELEM_T> ilist);
			Mat(const MAT_TYPE & other);

			inline MAT_TYPE operator=(const MAT_TYPE & rhs ); 
			static constexpr bool isSquare();

			inline const Vec<ELEM_T, DIM_W> row(const int & i)const;
			inline const Vec<ELEM_T, DIM_H> col(const int & j)const;
			inline Mat<ELEM_T, DIM_W, DIM_H> transpose()const;
			inline ELEM_T determinant()const;
			inline void fill(ELEM_T value);
			template <int RESULT_H, int RESULT_W>
			inline Mat<ELEM_T, RESULT_H, RESULT_W> submatrix(int top, int left)const ;
			template <int RESULT_H, int RESULT_W>
			inline Mat<ELEM_T, RESULT_H, RESULT_W> grow(int row, int col) const;
	
			inline bool operator==(const MAT_TYPE & rhs );
			inline bool operator!=(const MAT_TYPE & rhs );
			inline Vec_T& operator[](const int &index);
			inline const Vec_T& operator[](const int &index)const;

			inline MAT_TYPE operator-()const;			
			inline MAT_TYPE operator+(MAT_TYPE rhs)const;
			inline MAT_TYPE operator-(MAT_TYPE rhs)const;
			inline MAT_TYPE operator*(const ELEM_T & scalar)const;
			inline MAT_TYPE operator/(const ELEM_T & scalar)const;
			inline Vec<ELEM_T, DIM_H> solveSystem(const Vec<ELEM_T, DIM_H> &b)const;


			template <int RESULT_W> 
			inline Mat<ELEM_T, DIM_H, RESULT_W> operator*(Mat<ELEM_T, DIM_W, RESULT_W> rhs)const;

			template <typename _ELEM_T, int _DIM_H, int _DIM_W>
			friend std::ostream& operator<<(std::ostream & oss, 
								const Mat<_ELEM_T, _DIM_H, _DIM_W> & mat);			
	};

/******************************************* Vec Definitions *************************************************/

	template <typename ELEM_T, int DIM>
	VEC_TYPE::Vec(ELEM_T value){
		fill(value);	
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE::Vec(std::initializer_list<ELEM_T> ilist){
		auto it = ilist.begin();
		for(int i =0; i < DIM && it != ilist.end(); ++i, ++it)
			_elements[i] = *it;	

	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE::Vec(const Vec<ELEM_T, DIM> &other):
		_elements(other._elements){	
	}

	template <typename ELEM_T, int DIM>
	ELEM_T& VEC_TYPE::operator[](const int & index){
		if(index>=DIM || index < 0)
			throw MathException("Vector[] index = " + std::to_string(index) +" out of bounds [0," + std::to_string(DIM) + ")");
		
		return _elements[index];
	}


	template <typename ELEM_T, int DIM>
	const ELEM_T& VEC_TYPE::operator[](const int & index)const {
		if(index>=DIM || index < 0)
			throw MathException("Vector[] index = " + std::to_string(index) +" out of bounds [0," + std::to_string(DIM) + ")");
		
		return _elements[index];
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator=(const VEC_TYPE & rhs) {
		_elements = rhs._elements;	
		return *this;
	}
	template <typename ELEM_T, int DIM>
	void VEC_TYPE::normalize(){
		*this = normal();

	} 

	template <typename ELEM_T, int DIM>
	void VEC_TYPE::fill(ELEM_T value){
		for(auto & e : _elements)
			e = value;
	}

	template <typename ELEM_T, int DIM>
	ELEM_T VEC_TYPE::magnitude2()const{
		ELEM_T sum = ELEM_T(0);
		for(auto & e : _elements)
			sum += e*e;
		return sum;
	}

	template <typename ELEM_T, int DIM>
	ELEM_T VEC_TYPE::magnitude()const{
		return sqrt(magnitude2());
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::normal()const{
		VEC_TYPE result;
		auto mag = magnitude();
		for(int i =0; i < _elements.size(); ++i)
			result[i] = _elements[i]/mag;
		return result;
	}


	template <typename ELEM_T, int DIM>
	ELEM_T VEC_TYPE::dot(const VEC_TYPE & rhs) const{
		ELEM_T sum = 0;
		for(int i =0; i < DIM; ++i)
			sum += _elements[i] * rhs._elements[i];	
		return sum;
	}
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::cross(const VEC_TYPE & rhs) const{
 		static_assert(DIM == 3, "Cross Product defined only on Vec3");
		VEC_TYPE result;
		result._elements[0] = _elements[1]*rhs._elements[2] - _elements[2]*rhs._elements[1];	
		result._elements[1] = _elements[2]*rhs._elements[0] - _elements[0]*rhs._elements[2];	
		result._elements[2] = _elements[0]*rhs._elements[1] - _elements[1]*rhs._elements[0];	
		return result;
	}			

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator+(const VEC_TYPE & rhs) const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] + rhs._elements[i];	
		return result;
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator-(const VEC_TYPE & rhs)const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] - rhs._elements[i];	
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator+(const ELEM_T & scalar) const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] + scalar;	
		return result;
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator-(const ELEM_T & scalar)const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] - scalar;	
		return result;
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator-()const{
		Vec<ELEM_T, DIM> result;
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i]*ELEM_T(-1);	
		return result;
	}	

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator*(const VEC_TYPE & rhs)const{
		VEC_TYPE result(*this);
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] * rhs[i];
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator/(const VEC_TYPE & rhs)const{
		VEC_TYPE result(*this);
		for(int i =0; i < DIM; ++i)
			result._elements[i] = _elements[i] / rhs[i];		
		return result;
	}
	

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator*(const ELEM_T & scalar)const{
		VEC_TYPE result(*this);
		for(auto & e : result._elements)
			e = e * scalar;	
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator/(const ELEM_T & scalar)const{
		VEC_TYPE result(*this);
		for(auto & e : result._elements)
			e = e/ scalar;
		return result;
	}
	
	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator+=(const VEC_TYPE & rhs){
		for(int i =0; i < DIM; ++i)
			_elements[i] +=rhs._elements[i];	
		return (*this);
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator-=(const VEC_TYPE & rhs){
		for(int i =0; i < DIM; ++i)
			_elements[i] -= rhs._elements[i];	
		return (*this);
	}

		template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator*=(const VEC_TYPE & rhs){
		for(int i =0; i < DIM; ++i)
			_elements[i] *= rhs._elements[i];	
		return (*this);
	}

		template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator/=(const VEC_TYPE & rhs){
		for(int i =0; i < DIM; ++i)
			_elements[i] /= rhs._elements[i];	
		return (*this);
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator+=(const ELEM_T & scalar){
		for(int i =0; i < DIM; ++i)
			_elements[i] +=scalar;	
		return (*this);
	}

	template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator-=(const ELEM_T & scalar){
		for(int i =0; i < DIM; ++i)
			_elements[i] -= scalar;	
		return (*this);
	}

		template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator*=(const ELEM_T & scalar){
		for(int i =0; i < DIM; ++i)
			_elements[i] *= scalar;	
		return (*this);
	}

		template <typename ELEM_T, int DIM>
	VEC_TYPE VEC_TYPE::operator/=(const ELEM_T & scalar){
		for(int i =0; i < DIM; ++i)
			_elements[i] /= scalar;	
		return (*this);
	}

	template <typename ELEM_T, int DIM>
	bool VEC_TYPE::operator==(const VEC_TYPE & rhs)const{
		for(int i =0; i < DIM; ++i)
			if(! almost_equal(_elements[i], rhs._elements[i]))
				return false;	
		return true;
	}
	
	template <typename ELEM_T, int DIM>
	bool VEC_TYPE::operator!=(const VEC_TYPE & rhs)const{
		return !(*this == rhs);
	}
							
	template <typename ELEM_T, int DIM>
	std::ostream & operator<< (std::ostream & os, const VEC_TYPE & vec){
		os << "< ";
		for(int i =0; i < DIM; ++i)
			os <<std::setprecision(precision)<< vec._elements[i] << (i!=DIM-1? ", " : " ");	
		return os << '>';
	}


/************************************************ Ray Definitions **************************************************/

	template <typename ELEM_T, int DIM>
	RAY_TYPE::Ray(){
	}

	template <typename ELEM_T, int DIM>
	RAY_TYPE::Ray(const Vec<ELEM_T, DIM> &origin, const Vec<ELEM_T, DIM> & dir):
		_origin(origin), _dir(dir){

	}
	template <typename ELEM_T, int DIM>
	const Vec<ELEM_T, DIM> & RAY_TYPE::origin() const {
		return _origin;
	}

	template <typename ELEM_T, int DIM>
	const Vec<ELEM_T, DIM> & RAY_TYPE::direction() const {
		return _dir;
	}

	template <typename ELEM_T, int DIM>

 	void RAY_TYPE::set(const Vec<ELEM_T, DIM> & origin, const Vec<ELEM_T, DIM> & dir){
 		_origin = origin;
		_dir = dir;
 	}

	template <typename ELEM_T, int DIM>
	void RAY_TYPE::setOrigin(const Vec<ELEM_T, DIM> & origin){
		_origin = origin;
	}

	template <typename ELEM_T, int DIM>
	void RAY_TYPE::setDirection(const Vec<ELEM_T, DIM> & dir){
		_dir = dir;
	}

	template <typename ELEM_T, int DIM>
	const Vec<ELEM_T, DIM> RAY_TYPE::point(ELEM_T t) const{
		return _origin+(_dir*t); 
	} 


/*************************************************** Mat Defintions **************************************************/

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE::Mat(ELEM_T value){
		fill(value);
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE::Mat(std::initializer_list<ELEM_T> ilist){
		/*
			{ 0 1 ... N	 }
			| M 1 ... NxM|
		*/
		auto it = ilist.begin();
		for(int i =0; i < DIM_H ; ++i)
		 	for(int j=0; j < DIM_W && it != ilist.end(); ++j)
		 		_elements[i][j] = *(it++);					
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE::Mat(const MAT_TYPE & other){
		for(int i =0; i < DIM_H ; ++i){
			_elements[i] = other._elements[i];					
		}
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator=(const MAT_TYPE & rhs ){
		for(int i =0; i < DIM_H ; ++i){
			_elements[i] = rhs._elements[i];					
		}
	} 

	template <typename ELEM_T, int DIM_H, int DIM_W>
	bool constexpr MAT_TYPE::isSquare(){
		return DIM_W == DIM_H;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	typename MAT_TYPE::Vec_T& MAT_TYPE::operator[](const int &index){
		if(index>=DIM_H|| index < 0)
			throw MathException("Matrix[] index = " + std::to_string(index) +" out of bounds [0," + std::to_string(DIM_H) + ")");
		
		return _elements[index];
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	const typename MAT_TYPE::Vec_T& MAT_TYPE::operator[](const int & index)const{
		if(index>=DIM_H || index < 0)
			throw MathException("Matrix[] index = " + std::to_string(index) +" out of bounds [0," + std::to_string(DIM_H) + ")");

		return _elements[index];
	}
	
	template <typename ELEM_T, int DIM_H, int DIM_W>
	const Vec<ELEM_T, DIM_W> MAT_TYPE::row(const int & i)const{
		//return row as vec
		return (*this)[i];
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	const Vec<ELEM_T, DIM_H> MAT_TYPE::col(const int & j) const{
		//return col as vec
		if(j >=DIM_W || j < 0)
			throw MathException("Column index =" +  std::to_string(j) + "out of bounds:" + "[0," +std::to_string(DIM_W) +")");
		Vec<ELEM_T, DIM_H> column;
		for(int i =0; i < DIM_H; ++i){
			column[i] = _elements[i][j];
		}
		return column;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	void MAT_TYPE::fill(ELEM_T value){
		for(int i =0; i < DIM_H ; ++i)
	 		_elements[i].fill(value);					
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	template <int RESULT_H, int RESULT_W>
	Mat<ELEM_T, RESULT_H, RESULT_W> MAT_TYPE::submatrix(int top, int left) const{
		static_assert(RESULT_H <= DIM_H && RESULT_W <= DIM_W,"submatrix: result matrix must be less than H x W");
		Mat<ELEM_T, RESULT_H, RESULT_W> result;
		for(int i = 0; i < RESULT_H; ++i)
			for(int j = 0; j < RESULT_W; ++j)
				result[i][j] = (*this)[i+top][j+left];
		return result;				
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	template <int RESULT_H, int RESULT_W>
	Mat<ELEM_T, RESULT_H, RESULT_W> MAT_TYPE::grow(int row, int col) const{
		static_assert(RESULT_H >= DIM_H &&  RESULT_W >= DIM_W,"grow: result matrix must be greater than H x W");
		Mat<ELEM_T, RESULT_H, RESULT_W> result;
		for(int i = 0; i < DIM_H; ++i)
			for(int j = 0; j < DIM_H; ++j)
				result[i][j] = (*this)[i][j];
		return result;				
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	bool MAT_TYPE::operator==(const MAT_TYPE & rhs ){
		for(int i =0; i < DIM_H ; ++i)
			if(_elements[i] != rhs._elements[i]) 
				return false;					
		return true;
	} 

	template <typename ELEM_T, int DIM_H, int DIM_W>
	bool MAT_TYPE::operator!=(const MAT_TYPE & rhs ){
		return !(*this == rhs);
	} 


	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator-()const{
		MAT_TYPE result;
		for(int i = 0; i < _elements.size(); ++i)
			result[i] = -_elements[i];
		return result;
	}			
	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator+(MAT_TYPE rhs)const{
		MAT_TYPE result;
		for(int i = 0; i < _elements.size(); ++i)
			result[i] = _elements[i]+rhs[i];
		return result;

	}
	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator-(MAT_TYPE rhs)const{
		MAT_TYPE result;
		for(int i = 0; i < _elements.size(); ++i)
			result[i] = _elements[i]-rhs[i];
		return result;

	}
	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator*(const ELEM_T & scalar)const{
		MAT_TYPE result;
		for(int i = 0; i < _elements.size(); ++i)
			result[i] = _elements[i]*scalar;
		return result;

	}
	template <typename ELEM_T, int DIM_H, int DIM_W>
	MAT_TYPE MAT_TYPE::operator/(const ELEM_T & scalar)const{
		MAT_TYPE result;
		for(int i = 0; i < _elements.size(); ++i)
			result[i] = _elements[i]/scalar;
		return result;

	}


	template <typename ELEM_T, int DIM_H, int DIM_W>
	template <int RESULT_W> Mat<ELEM_T, DIM_H, RESULT_W>
	MAT_TYPE::operator*(Mat<ELEM_T, DIM_W, RESULT_W> rhs)const{
		// if A is an n × m matrix and B is an m × p matrix, their matrix product AB is an n × p
		Mat<ELEM_T, DIM_H, RESULT_W> result;
		for(int i =0; i < DIM_H; ++i){
			for(int j =0; j < RESULT_W; ++j){
				result[i][j] = row(i).dot(rhs.col(j));
			}
		}
		return result;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	Mat<ELEM_T, DIM_W, DIM_H> MAT_TYPE::transpose()const{
		// if A is an n × m matrix and B is an m × p matrix, their matrix product AB is an n × p
		Mat<ELEM_T, DIM_W, DIM_H> result;
		for(int i =0; i < DIM_H; ++i){
			for(int j =0; j < DIM_W; ++j){
				result[j][i] = (*this)[i][j];
			}
		}
		return result;
	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	ELEM_T MAT_TYPE::determinant()const{
		static_assert(isSquare(), "determinant: only defined for square matrices");
		static_assert((DIM_W == 2) || (DIM_W == 3), "determinant: only implemented for 2x2 and 3x3 matrices");
		/*
		Since there are only two possible conditions solve each explicitly
		 | a b |
		 | c d |  
		DET(2x2) = ad-bc
		 | a b c |
		 | d e f |          | e f |          | b c |           | b e |
		 | g h i |  = a*det(| h i |) - d*det(| h i |) + g*det (| c f |)  
		DET(3x3) = a(ei - fh) - d(bi - ch) + g(bf-ce) 
		*/
		if(DIM_W == 2)
			return (*this)[0][0]*(*this)[1][1] - (*this)[0][1]*(*this)[1][0];
		else if(DIM_W == 3)
			return (*this)[0][0]* ((*this)[1][1]*(*this)[2][2] - (*this)[1][2]*(*this)[2][1] ) 
				-  (*this)[1][0]* ((*this)[0][1]*(*this)[2][2] - (*this)[0][2]*(*this)[2][1] ) 
				+  (*this)[2][0]* ((*this)[0][1]*(*this)[1][2] - (*this)[0][2]*(*this)[1][1] ) ;
		else //should never execute	
			return 0;

	}

	template <typename ELEM_T, int DIM_H, int DIM_W>
	Vec<ELEM_T, DIM_H> MAT_TYPE::solveSystem(const Vec<ELEM_T, DIM_H> &b)const{
		/*
		Solves linear system Ax=b for x given A and b*/
		Vec<ELEM_T, DIM_H> x; 
		ELEM_T d = determinant();
		for (int i = 0; i < DIM_W; i++){
			MAT_TYPE new_matrix(*this);
			for (int j = 0; j < DIM_H; j++){ 
				new_matrix[j][i] = b[j]; 
            }
			x[i] = new_matrix.determinant() / d;
		}
		return x;
	}


	template <typename ELEM_T, int DIM_H, int DIM_W>
	std::ostream& operator<<(std::ostream & oss, const MAT_TYPE& mat){
		oss << "[\n";
		for(int i =0; i < DIM_H; ++i){
	 		for(int j=0; j < DIM_W; ++j){
	 			oss << " " << mat[i][j];
	 			if(j < DIM_H-1 || i < DIM_W-1)
	 				oss << ",";
	 		}
 			oss << "\n";
	 	}
		return oss << "]";	
	}

};	

#endif


