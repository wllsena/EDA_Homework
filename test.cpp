#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <vector>
#include <iostream>

using namespace std;
namespace bio = boost::iostreams;

int main() {
  int numberOfElements = 1000;

  //criar
  bio::mapped_file_params params;
  params.path          = "text.txt";
  params.new_file_size = numberOfElements*sizeof(int);
  params.flags         = bio::mapped_file::mapmode::readwrite;

  bio::mapped_file_sink out(params);
  int *data = (int *)out.data();
  data[0] = 100;

  //usar
  /*
  bio::mapped_file_params params;
  params.path          = "text.txt";
  params.new_file_size = numberOfElements*sizeof(int);
  bio::mapped_file_source out(params);

  int *data = (int *)out.data();
  cout << data[0] << endl;
  */
  return 0;
}
