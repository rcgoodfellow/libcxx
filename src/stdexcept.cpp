//===------------------------ stdexcept.cpp -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "stdexcept"
#include "new"
#include "string"
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include "system_error"

#ifndef __has_include
#define __has_include(inc) 0
#endif

#ifdef __APPLE__
#include <cxxabi.h>
#elif defined(LIBCXXRT) || __has_include(<cxxabi.h>)
#include <cxxabi.h>
#endif

// Note:  optimize for size

#if ! defined(_LIBCPP_MSVC)
#pragma GCC visibility push(hidden)
#endif

namespace
{

class __libcpp_nmstr
{
private:
    const char* str_;

    typedef std::size_t unused_t;
    typedef std::ptrdiff_t count_t;

    static const std::ptrdiff_t offset = static_cast<std::ptrdiff_t>(2*sizeof(unused_t) +
                                                                       sizeof(count_t));

    count_t& count() const _NOEXCEPT {return *const_cast<count_t *>(reinterpret_cast<const count_t *>(str_ - sizeof(count_t)));}
public:
    explicit __libcpp_nmstr(const char* msg);
    __libcpp_nmstr(const __libcpp_nmstr& s) _NOEXCEPT;
    __libcpp_nmstr& operator=(const __libcpp_nmstr& s) _NOEXCEPT;
    ~__libcpp_nmstr();
    const char* c_str() const _NOEXCEPT {return str_;}
};

__libcpp_nmstr::__libcpp_nmstr(const char* msg)
{
    std::size_t len = strlen(msg);
    str_ = new char[len + 1 + offset];
    unused_t* c = reinterpret_cast<unused_t*>(const_cast<char *>(str_));
    c[0] = c[1] = len;
    str_ += offset;
    count() = 0;
    std::memcpy(const_cast<char*>(c_str()), msg, len + 1);
}

inline
__libcpp_nmstr::__libcpp_nmstr(const __libcpp_nmstr& s) _NOEXCEPT
    : str_(s.str_)
{
    __sync_add_and_fetch(&count(), 1);
}

__libcpp_nmstr&
__libcpp_nmstr::operator=(const __libcpp_nmstr& s) _NOEXCEPT
{
    const char* p = str_;
    str_ = s.str_;
    __sync_add_and_fetch(&count(), 1);
    if (__sync_add_and_fetch(reinterpret_cast<const count_t*>(p-sizeof(count_t)), count_t(-1)) < 0)
        delete [] (p-offset);
    return *this;
}

inline
__libcpp_nmstr::~__libcpp_nmstr()
{
    if (__sync_add_and_fetch(&count(), count_t(-1)) < 0)
        delete [] (str_ - offset);
}

}

#if ! defined(_LIBCPP_MSVC)
#pragma GCC visibility pop
#endif

namespace std  // purposefully not using versioning namespace
{

logic_error::logic_error(const string& msg)
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    ::new(s) __libcpp_nmstr(msg.c_str());
}

logic_error::logic_error(const char* msg)
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    ::new(s) __libcpp_nmstr(msg);
}

logic_error::logic_error(const logic_error& le) _NOEXCEPT
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    const __libcpp_nmstr *s2 = reinterpret_cast<const __libcpp_nmstr *>(&le.__imp_);
    ::new(s) __libcpp_nmstr(*s2);
}

logic_error&
logic_error::operator=(const logic_error& le) _NOEXCEPT
{
    __libcpp_nmstr *s1 = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    const __libcpp_nmstr *s2 = reinterpret_cast<const __libcpp_nmstr *>(&le.__imp_);
    *s1 = *s2;
    return *this;
}

#if !defined(_LIBCPPABI_VERSION) && !defined(LIBSTDCXX)

logic_error::~logic_error() _NOEXCEPT
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    s->~__libcpp_nmstr();
}

const char*
logic_error::what() const _NOEXCEPT
{
    const __libcpp_nmstr *s = reinterpret_cast<const __libcpp_nmstr *>(&__imp_);
    return s->c_str();
}

#endif

runtime_error::runtime_error(const string& msg)
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    ::new(s) __libcpp_nmstr(msg.c_str());
}

runtime_error::runtime_error(const char* msg)
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    ::new(s) __libcpp_nmstr(msg);
}

runtime_error::runtime_error(const runtime_error& le) _NOEXCEPT
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    const __libcpp_nmstr *s2 = reinterpret_cast<const __libcpp_nmstr *>(&le.__imp_);
    ::new(s) __libcpp_nmstr(*s2);
}

runtime_error&
runtime_error::operator=(const runtime_error& le) _NOEXCEPT
{
    __libcpp_nmstr *s1 = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    const __libcpp_nmstr *s2 = reinterpret_cast<const __libcpp_nmstr *>(&le.__imp_);
    *s1 = *s2;
    return *this;
}

#if !defined(_LIBCPPABI_VERSION) && !defined(LIBSTDCXX)

runtime_error::~runtime_error() _NOEXCEPT
{
    __libcpp_nmstr *s = reinterpret_cast<__libcpp_nmstr *>(&__imp_);
    s->~__libcpp_nmstr();
}

const char*
runtime_error::what() const _NOEXCEPT
{
    const __libcpp_nmstr *s = reinterpret_cast<const __libcpp_nmstr *>(&__imp_);
    return s->c_str();
}

domain_error::~domain_error() _NOEXCEPT {}
invalid_argument::~invalid_argument() _NOEXCEPT {}
length_error::~length_error() _NOEXCEPT {}
out_of_range::~out_of_range() _NOEXCEPT {}

range_error::~range_error() _NOEXCEPT {}
overflow_error::~overflow_error() _NOEXCEPT {}
underflow_error::~underflow_error() _NOEXCEPT {}

#endif

}  // std
