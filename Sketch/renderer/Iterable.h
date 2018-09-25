#ifndef ITERABLE_H
#define	ITERABLE_H

//Iterator Interface
template <typename Type>
struct IFIterator
{
	virtual ~IFIterator() = 0;
	virtual Type &		operator*() = 0;
	virtual Type &		operator++() = 0;
	virtual Type &		operator--() = 0;

};

//Iterable:
//		Iterable Data Structure
template <typename Type>
class Iterable //:public Iterable
{
public:
	struct Exception
	{
		Exception(const char * msg) : _msg(msg) {}
		const std::string &  what() { return _msg; }
		std::string _msg;
	};
	Iterable(Type * begin, Type * end) : _begin(begin), _end(end) {}
	virtual ~Iterable() {}

	//To override
	inline virtual void				resize(int n)						{ throw Exception("void Iterable::resize(int) Not Implemented");	}
	inline virtual const Type &		get(int index) const				{ throw Exception("const Type & Iterable::get(int) Not Implemented");		}
	inline virtual void				set(int index, const Type & data)	{ throw Exception("void Iterable::set(int) Not Implemented");		}
	 
	inline IFIterator<Type>			begin() { return IFIterator<Type>(*_begin); }
	inline IFIterator<Type>			end() { return IFIterator<Type>(*_end); }

	Type * _begin, *_end;

};




#endif