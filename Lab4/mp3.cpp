
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <set>
using namespace std;

class Song {
public:
  string title;
  int time;
  int track;      // Primary key
  bool operator < (Song another) const { return title < another.title;}
};

ostream & operator << (ostream& out, Song & l) {     
        cout << l.track << ".  " << l.title << " " << l.time/60 << ":";
        if ((l.time % 60) < 10) cout << "0";
        cout << l.time % 60;
        return out;
}

class Album {
  public :
    map<int, Song> songs;
    string name;  // Album's name
    string artist;
    string genre;
    int time;     // Total time of all songs on album
    int nsongs;   // Total number of songs on album
    bool operator < (Album another) const { return name < another.name;}
};

class Artist {
   public :
     string name; // Artist's name
     int time;    // Total time of all songs on all albums by this artist
     int nsongs;
     vector<Album> albums;  // Total number of songs on all albums by this artist
     bool operator < (Artist another) const { return name < another.name;}
};

bool artistCheck(vector<Artist> &artist , string &tempArt);
bool albumCheck(vector<Artist> &artist , string &tempAlb);
void addSong(vector<Artist> &art, string &tempAlb, Song &song);
void addAlbum(vector<Artist> &art, string &tempArt, Album &album);
void printArtists(vector<Artist> &artist);
void printSongs(map<int, Song> &song);
string removeUnderscore(string &name);


int main(int argc, char* argv[]) 
{
  if( argc < 2 )
  {
    cout << "Missing Your Mp3 File Name. " << endl;
  }
  
  
  
  
	return 0;
}

string removeUnderscore(string &name) // method removes _ delimiters in original song title listings
{
  replace(name.begin(),name.end(),'_',' ');
  return name;

}

void printSongs(map<int, Song> &song) // this method prints songs using operator overloading
{
  map<int,Song> :: iterator s;
  for(s = song.begin(); s != song.end(); ++s)
  {
    Song t = s -> second;
    cout << "\t\t" << t << endl;
  }
}

void printArtists(vector<Artist> &artist)
{
  vector<Artist> :: iterator art;
  vector<Album> :: iterator al;
  
  for( art = artist.begin(); art != artist.end(); ++art ) // go through artist vector
  {
    // convert time from sec to mins plus secs
    cout << art -> name << ": " << art -> nsongs << ", " << (art -> time)/60 << ":";
    if( art -> time % 60 < 10)
    {
      cout << "0";
    }
    cout << (art -> time) % 60 << endl;
    
    for( al = art -> albums.begin(); al != art->albums.end(); al++)
    {
      cout << "\t" << al -> name <<": " << al -> nsongs << ", " <<(al->time)/60<<":";
      if(al -> time%60 < 10)
      {
        cout << "0";
      }
      cout << (al -> time) % 60 << endl;
      printSongs(al -> songs); 
     
    }
   }
}

bool artistCheck(vector<Artist> &artist , string &tempArt)
{
  
  vector<Artist> :: iterator ar;
  vector<Album> :: iterator al;
  bool search = false;
  
  for( ar = artist.begin(); ar != artist.end(); ++ar )
  {
    for( al = ar -> albums.begin(); al != ar->albums.end(); al++)
    {
      if(al -> name == tempArt)
      {
        search = true;
      }
    }
  }
  return search;
}

bool albumCheck(vector<Artist> &artist , string &tempAlb)
{
  vector<Artist> :: iterator ar;
  vector<Album> :: iterator al;
  bool search = false;
  for( ar = artist.begin(); ar != artist.end(); ++ar )
  {
    for( al = ar -> albums.begin(); al != ar->albums.end(); al++)
    {
      if(al -> name == tempAlb)
      {
        search = true;
      }
    }
  }
  return search;
} 

void addSong(vector<Artist> &art, string &tempAlb, Song &song)
{
  vector<Artist> :: iterator ar;
  vector<Album> :: iterator al;
  for( ar = art.begin(); ar != art.end(); ++ar )
  {
    for( al = ar -> albums.begin(); al != ar->albums.end(); al++)
    {
      if(al -> name == tempAlb ) // album info update
      {
        al -> songs[song.track] = song;
        al -> time += song.time;
        al -> nsongs += 1;
        ar -> time += song.time; //updating total time + num songs for a specified artist
        ar -> nsongs+=1;
      }
    }
  }
}

void addAlbum(vector<Artist> &art, string &tempArt, Album &album)
{
  vector<Artist> :: iterator ar;
  for( ar = art.begin(); ar != art.end(); ++ar )
  {
    if(ar -> name == tempArt )
    {
      ar -> albums.push_back(album); //adds album object to vector
      ar-> nsongs += 1; //updates to total songs and time 
      ar -> time += album.time;
      sort(ar->albums.begin(), ar->albums.end() ); //sorts Album vector
    }
  }
}
