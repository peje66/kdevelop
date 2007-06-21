/***************************************************************************
   copyright            : (C) 2006 by David Nolden
   email                : david.nolden.kdevelop@art-master.de
***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef HASHED_STRING_H
#define HASHED_STRING_H

#include<QString>
#include<ksharedptr.h>
#include<set>
#include <ext/hash_map>
#include <string>
#include "cppparserexport.h"

class QDataStream;


///A simple class that stores a string together with it's appropriate hash-key
class KDEVCPPPARSER_EXPORT HashedString {
  public:
    HashedString() : m_hash( 0 ) {}

    HashedString( const QString& str ) : m_str( str ) {
      initHash();
    }
    
    HashedString( const char* str ) : m_str( str ) {
      initHash();
    }

    inline unsigned int hash() const {
      return m_hash;
    }

    QString str() const {
      return m_str;
    }

    bool operator == ( const HashedString& rhs ) const {
      if ( m_hash != rhs.m_hash )
        return false;
      return m_str == rhs.m_str;
    }

    ///Does not compare alphabetically, uses the hash-key for ordering.
    bool operator < ( const HashedString& rhs ) const {
      if ( m_hash < rhs.m_hash )
        return true;
      if ( m_hash == rhs.m_hash )
        return m_str < rhs.m_str;
      return false;
    }

    static unsigned int hashString( const QString& str );

  private:
    void initHash();

    QString m_str;
    unsigned int m_hash;

    friend QDataStream& operator << ( QDataStream& stream, const HashedString& str );
    friend QDataStream& operator >> ( QDataStream& stream, HashedString& str );
};

QDataStream& operator << ( QDataStream& stream, const HashedString& str );

QDataStream& operator >> ( QDataStream& stream, HashedString& str );

class HashedStringSetData;
class HashedStringSetGroup;

///This is a reference-counting string-set optimized for fast lookup of hashed strings
class KDEVCPPPARSER_EXPORT HashedStringSet {
  public:
    HashedStringSet();

    ~HashedStringSet();

    ///Constructs a string-set from one single file
    HashedStringSet( const HashedString& file );

    HashedStringSet( const HashedStringSet& rhs );

    int size() const;

    HashedStringSet& operator = ( const HashedStringSet& rhs );
    ///@return whether the given file-name was included
    bool operator[] ( const HashedString& rhs ) const;

    void insert( const HashedString& str );

    HashedStringSet& operator +=( const HashedStringSet& );
    
    HashedStringSet& operator -=( const HashedStringSet& );

    ///intersection-test
    ///Returns true if all files that are part of this set are also part of the given set
    bool operator <= ( const HashedStringSet& rhs ) const;

    bool operator == ( const HashedStringSet& rhs ) const;

    void read( QDataStream& stream );
    void write( QDataStream& stream ) const;

    std::string print() const;

  unsigned int hash() const;
  private:
    friend class HashedStringSetGroup;
    void makeDataPrivate();
    KSharedPtr<HashedStringSetData> m_data; //this implies some additional cost because KShared's destructor is virtual. Maybe change that by copying KShared without the virtual destructor.
    friend HashedStringSet operator + ( const HashedStringSet& lhs, const HashedStringSet& rhs );
};

HashedStringSet operator + ( const HashedStringSet& lhs, const HashedStringSet& rhs );

namespace __gnu_cxx {
template<>
struct KDEVCPPPARSER_EXPORT hash<HashedString> {
  unsigned int operator () ( const HashedString& str ) const {
    return str.hash();
  }
};
}

///Used to find all registered HashedStringSet's that contain all strings given to findGroups(..)
class KDEVCPPPARSER_EXPORT HashedStringSetGroup {
  public:
    typedef std::set<unsigned int> ItemSet;
    void addSet( unsigned int id, const HashedStringSet& set );
    void enableSet( unsigned int id );
    bool isDisabled( unsigned int id ) const;
    void disableSet( unsigned int id );
    void removeSet( unsigned int id );

    //Writes the ids of all registered and not disabled HashedStringSet's that are completely included in the given HashedStringSet efficiently)
    void findGroups( HashedStringSet strings, ItemSet& target ) const;

  private:
    typedef __gnu_cxx::hash_map<HashedString, ItemSet> GroupMap;
    typedef __gnu_cxx::hash_map<unsigned int, unsigned int> SizeMap;
    GroupMap m_map;
    SizeMap m_sizeMap;
    ItemSet m_disabled;
    ItemSet m_global;
};
#endif
