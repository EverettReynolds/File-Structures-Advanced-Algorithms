#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[])
{
  string file,option,screen,output;
  bool lines,words,bytes; // true false flags to denote what needs to be output onto user screen
  int lineCount,wordCount,byteCount;
  char curr;
  char prev = '\n';
  stringstream ss;
  // interpretation of command line statement has commenced
  if (argc == 1)
  {
    cout << " Enter your command in the correct format. Refer to 'man wc' for further details." << endl;
    return -1;
  }
  if (argc > 2)
  {
    for( int i = 1; i < argc; i++)
    {
      if ( i == (argc-1) )
      {
        file = argv[i];
        option = argv[i];
        break;
      }
    }
    option = option.substr(1,option.length());
    if(option == "c")
    {
      bytes = true;
    }
    else if(option == "l")
    {
      lines = true;
    }
    else if(option == "w")
    {
      words = true;
    }
    else
    {
      cout << "Invalid Command"<< "\n Your options are -c, -l, and -w." <<  "\ninfo can be provided without these commands as well." <<  "\nEnter Correct Commands Please." << endl;
      
    }
  }
  else
  {
    file = argv[1];
    lines,words,bytes = true;
    
  }
  //file parsing has commenced
  fstream in(file.c_str(), ios::in); // file opened read mode
  in.seekg(0,ios::beg); // starting at the beginning of said file
  
  while(in.get(curr))
  {
    if(prev != '\n' && prev != '\t' && prev != ' ' && curr == '\n') // This counts nl in the word count bc it is technically a char/word
    {
      lineCount++;
      wordCount++;
    }
    else if(prev != '\n' && prev != '\t' && prev != ' ' && curr == '\t') // tabs count as a word
    {
      wordCount++;
    }
    else if(prev != '\n' && prev != '\t' && prev != ' ' && curr == ' ') // this is the conditions which shows an actual word is present
    {
      wordCount++;
    }
    else if( curr == '\n' && prev == '\n' ) // this is the condition which shows a new line is present
    {
      lineCount++;
    }
    
    
    
    byteCount++; // bytes always need updated
    prev = curr;
  }
  
  in.close(); // file reading mode is over
  // screen output section
  if(lines) // all flags need to be checked, therefore , ifs are necessary
  {
    screen = screen + "\t";
    ss << " ";
    ss << lineCount;
  }
  if(words)
  {
    screen = screen + "\t";
    ss << " ";
    ss << wordCount;
  }
  if(bytes)
  {
    screen = screen + "\t";
    ss << " ";
    ss << byteCount;
  }
  ss << " ";
  ss << file;
  output = ss.str();
  cout << output << endl;
  return 0;
}