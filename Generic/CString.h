// -------------------------------
//  Name:           CString.h
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.0
//  Last revision:  27/5/93
//  Licence:        Public Domain
//  Purpose:        Generic string handling package
// -------------------------------

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//
// INTERFACE
//

class CString
{
public:
  CString();
  CString(const CString&);
  CString(const char*);
  CString(const char);
  CString(const unsigned int);
  ~CString();

  CString& operator=(const CString&);
  CString& operator=(const char*);
  CString& operator=(const char);
  CString& operator+=(const CString&);
  CString& operator+=(const char*);
  CString& operator+=(const char);
  CString operator+(const CString&) const;
  friend ostream& operator<<(ostream&, const CString&);

  operator char*() const;
  operator size_t() const;

private:
  char*               data;
  size_t              length;
  size_t              chunk;
  static const size_t chunk_size;

protected:
  size_t  chunkRound(size_t) const;
};

//
// IMPLEMENTATION (see CCString.cpp as well)
//

inline
size_t CString::chunkRound(size_t from) const
{
  return ((from / chunk_size) + 1) * chunk_size;
}

inline
CString::CString()
{
  length = 0;
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  data[0] = '\0';
}

inline
CString::~CString()
{
  delete [] data;
}

inline
CString CString::operator+(const CString& from) const
{
  CString temp = *this;
  temp += from;
  return temp;
}

inline
ostream& operator<<(ostream& out, const CString& show)
{
  out << show.data;
  return out;
}

inline
CString::operator char*() const
{
  return data;
}

inline
CString::operator size_t() const
{
  return length;
}

// End.
