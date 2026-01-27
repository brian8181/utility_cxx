// File Name:  auto_ptr.hpp
// Build Date: Thu Oct 31 01:46:28 PM CDT 2024
// Version:    0.0.1

#ifndef _auto_ptr_HPP
#define _auto_ptr_HPP

#include <string>

using std::string;

template<class T>
class auto_ptr
{
public:
	// defered initialization
    auto_ptr() : ref_count( 0 ), pdata( 0 )
    {
    }

	// init with pointer, take ownership, reponsible for delete
	auto_ptr(T* pval) : ref_count(new long(1)),  pdata( pval )
    {
    }

	// init with value
    auto_ptr(T val) : ref_count(new long(1)),  pdata( new T(val) )
    {
    }

	// init with auto_ptr, copy construction
    auto_ptr(const auto_ptr<T>& aptr) : auto_ptr()
    {
        //aptr.free();
		aptr.get_ref(*this);
    }

    ~auto_ptr()
    {
        free();
    }

	void set_ref(auto_ptr<T>& aptr)
    {
		free();
        pdata = aptr.pdata;
        ref_count = aptr.ref_count;
    }

    //auto_ptr<T>& get_ref(auto_ptr<T>& aptr)
    //{
    //}

	// get ref counted
	auto_ptr<T>& get_ref(/* out */ auto_ptr<T>& aptr) const
    {
        aptr.free();
		++(*ref_count);
		aptr.pdata = pdata;
		aptr.ref_count = ref_count;
        return aptr;
    }

	// assigment // get ref counted
    auto_ptr<T>& operator =(auto_ptr<T>& aptr)
    {
		return get_ref(aptr);
    }

    T& operator *()
    {
        return *pdata;
    }

    T** operator &()
    {
        return &pdata;
    }

    T* operator->()
    {
        return pdata;
    }

    void set_val(const T& val)
    {
        *pdata = val;
    }

	T& get_val()
    {
        return *pdata;
    }

    void free()
    {
        deallocate();
    }

private:
    unsigned int NULL_PTR = 0;

private:
    auto_ptr<T>& allocate(const T& val)
    {
		free();
        this->pdata = new T(val);
        this->ref_count = new long(1);
        return *this;
    }

    void deallocate()
    {
        if(pdata != 0 && ref_count != 0)
        {
            --(*ref_count);
            if(*ref_count == 0)
            {
                delete ref_count;
                delete pdata;
                ref_count = 0;
                pdata = 0;
            }
        }
    }

private:
    long* ref_count = 0;
    T* pdata = 0;

};

typedef auto_ptr<int> auto_ptr_int;
typedef auto_ptr<std::string> auto_ptr_string;
typedef auto_ptr<char> auto_ptr_char;
typedef auto_ptr<std::pair<std::string, int>> auto_ptr_pair;

#endif
