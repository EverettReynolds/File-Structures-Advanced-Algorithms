#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include "file.h"
#include <sstream>
#include <sys/types.h>
#include <cstdlib>
#include <vector>
#include <cstring>


using namespace std;
//using recursive_directory_iterator = filesystem::experimental::recursive_directory_iterator;
//namespace fs = std::filesystem::recursive_directory_iterator;
//namespace fs = std::experimental::filesystem;
//using recursive_directory_iterator = filesystem::recursive_directory_iterator;

File fileStats(string &file);
bool directoryCheck();
bool optionCheck(int argc, char* argv[], bool &cfOp, bool &tfOp, bool &xfOp, bool &helpOp);
void cf(char* argv[], string &tarFileName);
void tf(string & tarFileName);
void xf(string & tarFileName);




int main(int argc, char* argv[])
{
	char tarFile;
	int num;
	File file;
  string tarFileName;
	bool cfOp, tfOp, xfOp, helpOp = false;
	if(argc < 3 || argc > 6)
	{
		cerr << "Error: Invalid Number of Arguments. " << endl;
	}
	if( optionCheck(argc,argv,cfOp,tfOp,xfOp,helpOp) ) // This is where you want to be with no errors
	{
     tarFileName = argv[2];
    if(cfOp)
    {
      cf(argv,tarFileName);
    }
    if(tfOp)
    {
      tf(tarFileName);
    }
    if(xfOp)
    {
      xf(tarFileName);
    }
    else
    {
    
    }
	}

	else
	{
		cerr << "Error: Invalid Number of Arguments. " << endl;
		cout << "Correct Format: jtar [-cf] 'tarfile' fileName1 directoryName1 " << endl;
		cout << "Correct Format: jtar [-tf] 'tarfile' " << endl;
		cout << "Correct Format: jtar [-xf] 'tarfile' " << endl;
		cout << "Correct Format: jtar [--help] " << endl;

	}
	
	return 0;
	
}

File fileStats(string &file) // returns a file object that holds on necessary information
// on an input file. Uses code from utility.cpp
{
	struct stat buf;
	stringstream ss;
	char name[81], pmode[5], size[7], stamp[16];
	string fileName,filePmode,fileSize,fileStamp;
	bool isItDir;

	lstat(file.c_str(),&buf); // used to fill buffer with file stats

	strcpy(name,file.c_str()); // copies name to name array of chars

	ss << ((buf.st_mode & S_IRWXU) >> 6) << ((buf.st_mode & S_IRWXG) >> 3) << (buf.st_mode & S_IRWXO); // get pmode
	strcpy(pmode,ss.str().c_str()); // add found pmode value to stringstream and convert it into readable values

	fileSize = to_string(buf.st_size); //get file's size
	strcpy(size,fileSize.c_str()); // copy file size to size attribute

	strftime(stamp, 16, "%Y%m%d%H%M.%S", localtime(&buf.st_ctime)); // get's stamp

	
	File fileN(name,pmode,size,stamp);
	isItDir = S_ISDIR(buf.st_mode);

	if(isItDir)
	{
		fileN.flagAsDir();
	}
	return fileN;




	/*File fileR(name,pmode,size,stamp);
	return fileR;*/

}

bool directoryCheck(string dirFiles)
{
	struct stat buf;
	lstat(dirFiles.c_str(),&buf); 
	return S_ISDIR(buf.st_mode); // returns true or false based on files input

}

bool optionCheck(int argc, char* argv[], bool &cfOp, bool &tfOp, bool &xfOp, bool &helpOp)
{
	string str,tarFileName;
	str = argv[1];
	if(str == "-cf")
	{
		cfOp = true;
   
	}
	if(str == "-xf")
	{
		xfOp = true;
		
	}
	if(str == "-tf")
	{
		tfOp = true;
	}
	if(str == "--help")
	{
		printf("system cat help");
	}
	else if(str ==  "-")
	{
		return false;
	}
	return true;

}

void cf(char* argv[], string & tarFileName )
{
	vector<File>fileVectors;
	string fileName, posName;
	int fileTotal;
	fileName = argv[3];

	fileVectors.push_back(fileStats(fileName));
	/*for(auto p: recursive_directory_iterator(fileName)) // auto is a variable type which automatically places in a variable typing based on context of it's initializer, known about due to use in another language which derives much from C++, Java, and Python (Dart)
	{
		posName = p.path();
		fileVectors.push_back( fileStats(posName));
	} */
	fstream tarfile (tarFileName.c_str(), ios::out | ios::binary);
	fileTotal = fileVectors.size();
	tarfile.write( (char*) &fileTotal , sizeof(int) );

	for(int i  = 0; i < fileVectors.size(); i++)
	{
		tarfile.write( (char*) &fileTotal , sizeof(int) ); // Directory Status is checked before loop
		if(!fileVectors[i].isADir()) // Data is written out to the tar file once directory status is confirmed or denied
		{
			fstream tmpFile(fileVectors[i].getName().c_str(), ios::in);
			if(tmpFile) // if the file can be opened
			{
				char* token = new char[stoi(fileVectors[i].getSize())]; //this line creates an array of chars with the size of the file 
				tmpFile.read(token, stoi(fileVectors[i].getSize() ) );
				tarfile.write(token, stoi(fileVectors[i].getSize() ) );
			}
			else
			{
				cout << " The File Inputted: " << fileVectors[i].getName() << "Cannot Be Found." << endl;
			}
		}
	}



}

void tf(string &tarFileName)
{
	int fileTotal, x;
	File file;
	fstream tarfile (tarFileName.c_str(), ios::in | ios::binary);
	tarfile.read( (char*) &fileTotal , sizeof(fileTotal) );
	x = 0;

	while(x < fileTotal)
	{
		tarfile.read( (char*) &file , sizeof(file) );
		cout << file.getName() << endl;

		if( !file.isADir() )
		{
			tarfile.seekg( stoi (file.getSize() ), ios::cur);
		}
		x++;
	}
	tarfile.close();
}

void xf(string &tarFileName)
{
	File file;
	int x, fileTotal;
	fstream tarfile (tarFileName.c_str(), ios::in | ios::binary);
	tarfile.read( (char*) &fileTotal , sizeof(fileTotal) );

	while(x < fileTotal)
	{
		tarfile.read( (char*) &file, sizeof(file) );
		if(file.isADir() )
		{
			fstream tmpFile (file.getName().c_str(), ios::in );
			if(tmpFile)
			{
				cout << " The Directory " << file.getName() << " Already Exists." << endl;
				tmpFile.close();
				break;
			}
			else
			{
				system( ("mkdir " + file.getName() ).c_str() );
			}
			tmpFile.close();
		}
		else
		{
			fstream tmpFile(file.getName().c_str(), ios::out);
			char* token = new char[ stoi( file.getSize() ) ];
			tarfile.read(token, stoi( file.getSize() ) );
			tmpFile.write(token, stoi( file.getSize() ) );
			tmpFile.close();

		}

		system( ("chmod " + file.getPmode() + " " + file.getName()).c_str() ); //changes pmode
		system( ("touch -t " + file.getStamp() + " " + file.getName()).c_str() ); //changes stamp
		x++;
	}
	tarfile.close();
}

