#ifndef UTREF_H
#define UTREF_H
#include <assert.h>

class UTRefCount{
	mutable int refCount;
public:
	UTRefCount() {
		refCount = 0;
	}
	UTRefCount(const UTRefCount&) {
		refCount = 0;
}
	~UTRefCount() {
		assert(refCount == 0);
	}
	UTRefCount& operator = (const UTRefCount& r){ return *this; }
	int AddRef() const { return ++ refCount; }
	int DelRef() const {
		assert(refCount > 0);
		return -- refCount;
	}
	int RefCount() const { return refCount; }
};

/**	Smart pointer for reference counter. Automatically increase / decrease the reference counter,
	When the counter reaches 0, delete the object.	*/
template <class T>
class UTRef{
	T* obj;
	T*& Obj() const {return (T*&) obj;}
public:
	UTRef(T* t = NULL){
		Obj() = t;
		if (Obj()) Obj()->AddRef();
	}
	template <class E>
	UTRef(const UTRef<E>& r){
		Obj() = (T*)(E*)r;
		if (Obj()) Obj()->AddRef();
	}
	UTRef(const UTRef<T>& r){
		Obj() = r.Obj();
		if (Obj()) Obj()->AddRef();
	}
	~UTRef(){ if (Obj() && Obj()->DelRef() == 0) delete Obj(); obj=NULL;}
	template <class E>
	UTRef& operator =(const UTRef<E>& r){
		if (Obj() != r){
			if (Obj() && Obj()->DelRef() == 0) delete Obj();
			Obj() = r;
			if (Obj()) Obj()->AddRef();
		}
		return *this;
	}
	UTRef& operator =(const UTRef<T>& r){
		if (Obj() != r.Obj()){
			if (Obj() && Obj()->DelRef() == 0) delete Obj();
			Obj() = r;
			if (Obj()) Obj()->AddRef();
		}
		return *this;
	}
	operator T*() const {return Obj();}
	T* operator->() const {return Obj();}
	bool operator <(const UTRef& r) const { return Obj() < r.Obj(); }
};

#endif
