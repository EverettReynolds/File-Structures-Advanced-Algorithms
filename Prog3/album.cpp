#include <iostream>
#include "album.h"

Album::Album() 
{
  strcpy(UPC, "\0");
  strcpy(Artist, "\0");
  strcpy(Title, "\0");
}
Album::Album(const Album& copyAlbum)
{
  strcpy(UPC, copyAlbum.UPC);
  strcpy(Artist, copyAlbum.Artist);
  strcpy(Title, copyAlbum.Title);
}
Album::Album(String upc, String artist, String title)
{
  strcpy(UPC,upc);
  strcpy(Artist,artist);
  strcpy(Title, title);
}

Album& Album::operator = ( const Album& nextAlbum )
{
  strcpy(UPC,nextAlbum.UPC);
  strcpy(Artist,nextAlbum.Artist);
  strcpy(Title,nextAlbum.Title);
  return *this;
}

bool operator < ( const Album& x, const Album& y)
{
  if( strcmp(x.UPC, y.UPC) < 0 )
  {
    return true;
  }
  else
  {
    return false;
  }
}

istream& operator >> ( istream& stream, Album& Z)
{
  return stream >> Z.UPC >> Z.Artist >> Z.Title;
}

ostream& operator << ( ostream& stream, Album& Z)
{
  cout << Z.UPC << " " << Z.Artist << " " << Z.Title << endl;
  return stream << Z.UPC << Z.Artist << Z.Title;
}


string Album::getUPC()
{
  return string(UPC);
}
string Album::getArtist()
{
  return string(Artist);
}
string Album::getTitle()
{
  return string(Title);
}
int Album:: recordSize()
{
  return ( strlen(UPC) + strlen(Artist) + strlen(Title) );
}