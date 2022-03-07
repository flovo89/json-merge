#ifndef MERGE_JSON_FILE_WRITER_HPP_
#define MERGE_JSON_FILE_WRITER_HPP_

#include <string>

namespace merge_json {

class FileWriter {
 public:
  FileWriter();
  virtual ~FileWriter();

  int writeFile(const std::string& path, const std::string& data);
};

}  // namespace merge_json

#endif
