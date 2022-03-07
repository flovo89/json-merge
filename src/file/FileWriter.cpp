#include "FileWriter.hpp"

#include <filesystem>
#include <fstream>

namespace merge_json {

//--------------------------------------------------------------------------------------------
FileWriter::FileWriter() {}

//--------------------------------------------------------------------------------------------
FileWriter::~FileWriter() {}

//--------------------------------------------------------------------------------------------
int FileWriter::writeFile(const std::string& path, const std::string& data) {
  std::ofstream f(path, std::ios::in);
  if (f.is_open()) {
    f << data;
  } else {
    f.close();
    return -1;
  }
  f.close();
  return 0;
}

}  // namespace merge_json
