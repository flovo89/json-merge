#include "FileReader.hpp"

#include <filesystem>
#include <fstream>

namespace merge_json {

//--------------------------------------------------------------------------------------------
FileReader::FileReader() {}

//--------------------------------------------------------------------------------------------
FileReader::~FileReader() {}

//--------------------------------------------------------------------------------------------
int FileReader::readFile(const std::string& path, std::string& data) {
  std::ifstream f(path, std::ios::in);
  if (f.is_open()) {
    std::copy(std::istreambuf_iterator<char>(f),
              std::istreambuf_iterator<char>(), std::back_inserter(data));
  } else {
    f.close();
    return -1;
  }
  f.close();
  return 0;
}

}  // namespace merge_json
