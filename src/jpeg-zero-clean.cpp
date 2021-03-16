
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main (int argc, char *argv[])
{
  if ((argc < 2) || (argc > 3))
  {
    cerr << "Usage: "  << argv[0] << " infile.jpg [outfile.jpg]" << endl;
    return 1;
  }

  string inFileName = argv[1];
  ifstream inFile;
  
  inFile.open (inFileName, ios::in | ios::app | ios::binary);
  if (!inFile.is_open())
  {
    cerr << "failed to open \""  << inFileName << "\"" <<  endl;
    return 1;
  }
  
  inFile.seekg(0, std::ios_base::end);
  streampos inFileSize = inFile.tellg();
  
  char* fileContent = new char [inFileSize];
  inFile.seekg (0, ios::beg);
  inFile.read (fileContent, inFileSize);
  if (inFile.bad())
  {
    cerr << "error reading from \""  << inFileName << "\"" <<  endl;
    return 1;
  }
  inFile.close();
 
  int zeroCnt=0;
  int pos = (int)inFileSize - 1;
  
  while (pos > 0 && fileContent[pos] == 0)
  {
    pos--;
    zeroCnt ++;
  }
  
  bool endFound = false;
  if (pos>1)
  {
    endFound = ((unsigned char)(fileContent[pos]) == 0xD9) && ((unsigned char)(fileContent[pos-1]) == 0xFF);
  }
  
  if (argc == 3)
  {
    // write output file, if two arguments given
    if (endFound)
    {
      string outFileName = argv[2];
      ofstream outFile;

      if ((inFileName == outFileName) && (zeroCnt == 0))
      {
        cout << "No trailing zeros found, not overwriting input " << inFileName << endl;
      }
      else
      {
        outFile.open(outFileName, ios::out | ios::binary);
        if (!outFile.is_open())
        {
          cerr << "failed to open \"" << outFileName << "\"" << endl;
          return 1;
        }

        outFile.write(fileContent, pos + 1);
        if (outFile.bad())
        {
        cerr << "error writing to \"" << outFileName << "\"" << endl;
        return 1;
        }
        outFile.close();
        cout << "Saved " << zeroCnt << " bytes in \"" << outFileName << "\"" << endl;
      }
    }
    else
    {
      cerr << "EOI tag not found in \"" << inFileName << "\". Not writing to output file. Maybe no JFIF file." <<  endl;
    }
  }
  else
  {
    // print some info
    if (endFound)
    {
      cout << "File size       : "  << setw(10) << inFileSize << " bytes" <<  endl;
      cout << "Number of zeros : "  << setw(10) << zeroCnt <<  endl;
    }
    else
    {
      cerr << "EOI tag not found in \"" << inFileName << "\". Maybe no JFIF file." <<  endl;
    }
  }
 
  delete[] fileContent;
  return 0;

}

