#include <iostream>
#include <fstream> // for ifstream
#include <string>
using namespace std;

/*
int convertToBin(int n){

  int i = 0;
  string temp = "";
    while (n > 0) {

        // storing remainder in binary array
        temp += to_string(n % 2);
        n = n / 2;
        i++;
    }

    return i;

}
*/

string reverseString(string s)
{
  string out = "";
  for (int i = s.size() - 1; i >= 0; i--)
  {
    out += s[i];
  }
  return out;
}

char getCharacterFrom7Bits(string s)
{
  int backtodec = 0;

  if (s[6] == '1')
    backtodec += 64;
  if (s[5] == '1')
    backtodec += 32;
  if (s[4] == '1')
    backtodec += 16;
  if (s[3] == '1')
    backtodec += 8;
  if (s[2] == '1')
    backtodec += 4;
  if (s[1] == '1')
    backtodec += 2;
  if (s[0] == '1')
    backtodec += 1;
  int ascii = stoi(s);
  return (char)backtodec;
}

int main(int argc, char **argv)
{

  // ofstream w;
  // w.open("output_5.txt");
  // cout << "argc: " << argc << endl;
  // ifstream ifs;

  // if(argc == 1) ifs.open("chall2.orc");
  // else ifs.open(argv[1]);

  // if(!ifs){
  //   cout << "IFS didn't open correctly" << endl;
  //   return 0;
  // }

  // string line;
  // string stream = "";
  // getline(ifs,line);

  // for(int i = 0; i < line.length(); i++){
  //   stream += std::bitset<8>(line[i]).to_string();
  // }

  // //cout << "stream = " << stream.substr(0,300) << endl;

  // // for(int j = 0; j < stream.length(); j++){
  // //   string temp = "";
  // //   if(j != 0 && j % 7 == 0){
  // //     cout << "this is temp: " << temp << endl;
  // //     cout << getCharacterFrom7Bits(temp) << endl;
  // //     temp = "";
  // //   }
  // //   else{
  // //     temp.append(stream[j]);
  // //   }
  // // }

  // //string temp = stream.substr(0,7);
  // //cout << "temp: " << temp << endl;
  // string res = "";
  // int linenum = 0;
  // while(true){
  //   string temp = stream.substr(0,7);
  //   //cout << getCharacterFrom7Bits(temp) << " , " << "temp: " << reverseString(temp) << endl;
  //   cout << linenum << ": " << reverseString(temp)  << endl;
  //   //cout << endl;
  //   linenum++;
  //   w << reverseString(temp) << endl;
  //   res += getCharacterFrom7Bits(temp);
  //   if(stream.length() < 7) break;
  //   stream = stream.substr(7);
  // }

  // ifs.close();

  // //cout << "test: " << getCharacterFrom7Bits("1100001") << endl;

  // //cout << "res: " << res << endl;
  // //w << "res: " << res << endl;
  // w.close();
  ofstream w;
  ifstream ifs;

  ifs.open("chall2.orc");
  w.open("output_7.txt");
  string stream;

  char c;
  while(ifs.get(c)){
    stream += std::bitset<8>(c).to_string();
    //w << c << endl;
  }
  int linenum = 0;
  while(true){
    string temp = stream.substr(0,7);
    //cout << getCharacterFrom7Bits(temp) << " , " << "temp: " << reverseString(temp) << endl;
    cout << linenum << ": " << reverseString(temp)  << endl;
    //cout << endl;
    linenum++;
    w << reverseString(temp) << endl;
    //res += getCharacterFrom7Bits(temp);
    if(stream.length() < 7) break;
    stream = stream.substr(7);
  }
  //cout << stream << endl;
  //w << stream;
  //}

  ifs.close();
  w.close();
  // // if (argc == 1) ifs.open("chall2.orc");
  // if (argc == 1) ifs.open("chall2.orc");
  // if (!ifs)
  // {
  //   cout << "IFS didn't open correctly" << endl;
  //   return 0;
  // }
  // w.open("output_6.txt");
  // string line = "";
  // string stream;
  // int linenum = 0;
  // bool first = true;
  // while (ifs)
  // {
  //   getline(ifs, line);
  //   stream = "";
  //   if (!first) line += "\n";
  //   else first = false;
  //   for (int i = 0; i < line.length(); i++)
  //   {
  //     stream += std::bitset<8>(line[i]).to_string();
  //   }
  //   stream += "00001010";
  //     string res = "";
  //     cout << "stream: " << stream << endl;
      
  //     while (true)
  //     {
  //       if (stream.length() < 7) break;
  //       string temp = stream.substr(0, 7);
  //       cout << linenum << ": " << reverseString(temp) << endl;
  //       //cout << linenum << ": " << temp << endl;
  //       linenum++;
  //       w << reverseString(temp) << endl;
  //       stream = stream.substr(7);
  //     }
  //   }
  

  return 0;
}
