// -------------------------------
//  Name:           CString.pp
//  Author:         J.R.Shannon
//  Language:       C++
//  Date:           6/11/92
//  Revison:        2.0
//  Last revision:  27/5/93
//  Licence:        Public Domain
//  Purpose:        Generic string handling package
// -------------------------------

#include "CString.h"

size_t const CString::chunk_size = 16;

CString& CString::operator+=(const CString& from)
{
  if (chunk < length + from.length + 1)
    {
      chunk = chunkRound(length + from.length + 1);
      char* newdata = new char[chunk];
      memcpy(newdata, data, length);
      memcpy(newdata+length, from.data, from.length+1);
      delete [] data;
      data = newdata;
    }
  else
    {
      memcpy(data+length, from.data, from.length + 1);
    }
  length += from.length;

  return *this;
}

CString& CString::operator+=(const char* from)
{
  const size_t fromLen = strlen(from);

  if (chunk < length + fromLen + 1)
    {
      chunk = chunkRound(length + fromLen + 1);
      char* newdata = new char[chunk];
      memcpy(newdata, data, length);
      memcpy(newdata+length, from, fromLen+1);
      delete [] data;
      data = newdata;
    }
  else
    {
      memcpy(data+length, from, fromLen + 1);
    }
  length += fromLen;

  return *this;
}

CString& CString::operator+=(const char from)
{
  const size_t fromLen = sizeof(from);

  if (chunk < length + fromLen + 1)
    {
      chunk = chunkRound(length + fromLen + 1);
      char* newdata = new char[chunk];
      memcpy(newdata, data, length);
      newdata[length] = from;
      newdata[length+1] = '\0';
      delete [] data;
      data = newdata;
    }
  else
    {
      data[length] = from;
      data[length+1] = '\0';
    }
  length += fromLen;

  return *this;
}

CString::CString(const CString& from)
{
  length = from.length;
  chunk = from.chunk;
  data = new char[chunk];
  memcpy(data, from.data, length + 1);
}

CString::CString(const char* from)
{
  length = strlen(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  memcpy(data, from, length + 1);
}

CString::CString(const char from)
{
  length = sizeof(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  data[0] = from;
  data[1] = '\0';
}

CString::CString(const unsigned int from)
{
  length = 16;
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  sprintf(data, "%u", from);
}

CString& CString::operator=(const CString& from)
{
  if (this != &from)
    {
      delete [] data;
      length = from.length;
      chunk = from.chunk;
      data = new char[chunk];
      memcpy(data, from.data, length + 1);
    }
  return *this;
}

CString& CString::operator=(const char* from)
{
  delete [] data;
  length = strlen(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  memcpy(data, from, length + 1);
  return *this;
}

CString& CString::operator=(const char from)
{
  delete [] data;
  length = sizeof(from);
  chunk = chunkRound(length + 1);
  data = new char[chunk];
  data[0] = from;
  data[1] = '\0';
  return *this;
}

