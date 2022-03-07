#ifndef MERGE_JSON_FILE_READER_HPP_
#define MERGE_JSON_FILE_READER_HPP_

#include <string>

namespace merge_json {

class FileReader {
 public:
  FileReader();
  virtual ~FileReader();

  int readFile(const std::string& path, std::string& data);
};

}  // namespace merge_json

#endif
