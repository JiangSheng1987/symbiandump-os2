/*
 * Portions Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 *
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
// WARNING: This is an internal header file, included by other C++
// standard library headers.  You should not attempt to use this header
// file directly.


#ifndef _STLP_INTERNAL_NUM_PUT_H
#define _STLP_INTERNAL_NUM_PUT_H

#ifndef _STLP_INTERNAL_NUMPUNCT_H
# include <stl/_numpunct.h>
#endif

#ifndef _STLP_INTERNAL_CTYPE_H
# include <stl/_ctype.h>
#endif

#ifndef _STLP_INTERNAL_OSTREAMBUF_ITERATOR_H
# include <stl/_ostreambuf_iterator.h>
#endif

#ifndef _STLP_INTERNAL_IOSTREAM_STRING_H
# include <stl/_iostream_string.h>
#endif

_STLP_BEGIN_NAMESPACE

//----------------------------------------------------------------------
// num_put facet

#if defined (_STLP_LIMITED_DEFAULT_TEMPLATES)
template <class _CharT, class _OutputIter>
#else
template <class _CharT, class _OutputIter = ostreambuf_iterator<_CharT, char_traits<_CharT> > >
#endif
class num_put: public locale::facet {
  friend class _Locale_impl;
public:
  typedef _CharT      char_type;
  typedef _OutputIter iter_type;

  explicit num_put(size_t __refs = 0) : locale::facet(__refs) {}

#if !defined (_STLP_NO_BOOL)
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                bool __val) const {
    return do_put(__s, __f, __fill, __val);
  }
#endif
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
               long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                unsigned long __val) const {
    return do_put(__s, __f, __fill, __val);
  }

#if defined (_STLP_LONG_LONG)
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                _STLP_LONG_LONG __val) const {
    return do_put(__s, __f, __fill, __val);
  }

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                unsigned _STLP_LONG_LONG __val) const {
    return do_put(__s, __f, __fill, __val);
  }
#endif

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                double __val) const {
    return do_put(__s, __f, __fill, (double)__val);
  }

#if !defined (_STLP_NO_LONG_DOUBLE)
  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                long double __val) const {
    return do_put(__s, __f, __fill, __val);
  }
#endif

  iter_type put(iter_type __s, ios_base& __f, char_type __fill,
                const void * __val) const {
    return do_put(__s, __f, __fill, __val);
  }

#if defined(__SYMBIAN32__WSD__) 
  static _STLP_STATIC_MEMBER_DECLSPEC locale::id& GetFacetLocaleId();
#elif defined (__SYMBIAN32__NO_STATIC_IMPORTS__)    
  static _STLP_STATIC_MEMBER_DECLSPEC locale::id& GetFacetLocaleId();
  static locale::id id;         
#else
  // NOTE: Symbian doesn't support exporting static data.  
  // Users of this class should use GetFacetLocaleId() to access the data member id  
  static _STLP_STATIC_MEMBER_DECLSPEC locale::id id;
#endif

protected:
  ~num_put() {}
#if !defined (_STLP_NO_BOOL)
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, bool __val) const;
#endif
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, unsigned long __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, double __val) const;
#if !defined (_STLP_NO_LONG_DOUBLE)
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, long double __val) const;
#endif

#if defined (_STLP_LONG_LONG)
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, _STLP_LONG_LONG __val) const;
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill,
                           unsigned _STLP_LONG_LONG __val) const ;
#endif
  virtual _OutputIter do_put(_OutputIter __s, ios_base& __f, _CharT __fill, const void* __val) const;
};

#if defined (_STLP_USE_TEMPLATE_EXPORT)
_STLP_EXPORT_TEMPLATE_CLASS num_put<char, ostreambuf_iterator<char, char_traits<char> > >;
// _STLP_EXPORT_TEMPLATE_CLASS num_put<char, char*>;
#  if !defined (_STLP_NO_WCHAR_T)
_STLP_EXPORT_TEMPLATE_CLASS num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >;
// _STLP_EXPORT_TEMPLATE_CLASS num_put<wchar_t, wchar_t*>;
#  endif
#endif

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION)

_STLP_MOVE_TO_PRIV_NAMESPACE

template <class _Integer>
char* _STLP_CALL
__write_integer_backward(char* __buf, ios_base::fmtflags __flags, _Integer __x);

/*
 * Returns the position on the right of the digits that has to be considered
 * for the application of the grouping policy.
 */
_STLP_DECLSPEC size_t _STLP_CALL __write_float(__iostring&, ios_base::fmtflags, int, double); //RVCT 3.1 export issue: _STLP_DECLSPEC added. 
#  if !defined (_STLP_NO_LONG_DOUBLE)
_STLP_DECLSPEC size_t _STLP_CALL __write_float(__iostring&, ios_base::fmtflags, int, long double);
#  endif

/*
 * Gets the digits of the integer part.
 */
_STLP_DECLSPEC void _STLP_CALL __get_floor_digits(__iostring&, _STLP_LONGEST_FLOAT_TYPE);

template <class _CharT>
void _STLP_CALL __get_money_digits(_STLP_BASIC_IOSTRING(_CharT)&, ios_base&, _STLP_LONGEST_FLOAT_TYPE);

#  if !defined (_STLP_NO_WCHAR_T)
_STLP_DECLSPEC void _STLP_CALL __convert_float_buffer(__iostring const&, __iowstring&, const ctype<wchar_t>&, wchar_t, bool = true);
#  endif
extern void _STLP_CALL __adjust_float_buffer(__iostring&, char);

extern char* _STLP_CALL
__write_integer(char* buf, ios_base::fmtflags flags, long x);

_STLP_DECLSPEC ptrdiff_t _STLP_CALL __insert_grouping(char* first, char* last, const string&, char, char, char, int);
_STLP_DECLSPEC void _STLP_CALL __insert_grouping(__iostring&, size_t, const string&, char, char, char, int);
#  if !defined (_STLP_NO_WCHAR_T)
_STLP_DECLSPEC ptrdiff_t _STLP_CALL __insert_grouping(wchar_t*, wchar_t*, const string&, wchar_t, wchar_t, wchar_t, int);
_STLP_DECLSPEC void _STLP_CALL __insert_grouping(__iowstring&, size_t, const string&, wchar_t, wchar_t, wchar_t, int);
#  endif

_STLP_MOVE_TO_STD_NAMESPACE

#endif /* _STLP_EXPOSE_STREAM_IMPLEMENTATION */

_STLP_END_NAMESPACE

#if defined (_STLP_EXPOSE_STREAM_IMPLEMENTATION) && !defined (_STLP_LINK_TIME_INSTANTIATION)
#  include <stl/_num_put.c>
#endif

#endif /* _STLP_INTERNAL_NUMERIC_FACETS_H */

// Local Variables:
// mode:C++
// End: