#include <getopt.h>

#include <csignal>
#include <iostream>
#include <memory>

#include "file/FileReader.hpp"
#include "file/FileWriter.hpp"
#include "merger/NlohmannMerger.hpp"
#include "version.hpp"

/* constants */
const int MANDATORY_ARGUMENTS_COUNT = 3;

/* Locals */
std::string file1Path;
std::string file2Path;
std::string outputPath;

//--------------------------------------------------------------------------------------------
void printVersions() {
  std::cout << "(C) 2022 flovo89" << std::endl << std::endl;
  std::cout << "merge-json : " << merge_json::VERSION_MAJOR << "."
            << merge_json::VERSION_MINOR << "." << merge_json::VERSION_BUGFIX
            << " (" << merge_json::GIT_HASH << " / "
            << merge_json::VERSION_BUILD_TIME << ")" << std::endl;
}

//--------------------------------------------------------------------------------------------
void printHelp(const char* const appName) {
  std::cout << appName << ":" << std::endl;
  std::cout << "\t-h|--help         Shows this help and quit" << std::endl;
  std::cout << "\t-v|--version      Print version and quit" << std::endl;
  std::cout << "\t-a|--file1        Path for first file" << std::endl;
  std::cout << "\t-b|--file2        Path for second file" << std::endl;
  std::cout << "\t-o|--output       Path for generated file" << std::endl;
  std::cout << std::endl;
  std::cout << "Mandatory options:" << std::endl;
  std::cout << "\t--file1 abc.json" << std::endl;
  std::cout << "\t--file2 xyz.json" << std::endl;
  std::cout << "\t--output abc_xyz.json" << std::endl;
}

//--------------------------------------------------------------------------------------------
bool parseArgs(int argc, char* argv[], int& retCode) {
  static struct option long_options[] = {
      {"help", no_argument, NULL, 'h'},
      {"version", no_argument, NULL, 'v'},
      {"file1", required_argument, NULL, 'a'},
      {"file2", required_argument, NULL, 'b'},
      {"output", required_argument, NULL, 'o'},
      {0, 0, 0, 0}};
  int option_index = 0;
  int argCount = 0;

  while (1) {
    int c = getopt_long(argc, argv, "hva:b:o:", long_options, &option_index);

    if (c == -1) {
      break;
    }

    switch (c) {
      case 'h':
        printHelp(argv[0]);
        retCode = 0;
        return false;
      case 'v':
        printVersions();
        retCode = 0;
        return false;
      case 'a':
        file1Path = optarg;
        argCount++;
        break;
      case 'b':
        file2Path = optarg;
        argCount++;
        break;
      case 'o':
        outputPath = optarg;
        argCount++;
        break;
      default:
        printHelp(argv[0]);
        retCode = -1;
        return false;
    }
  }

  // Check for mandatory arguments
  bool r = argCount == MANDATORY_ARGUMENTS_COUNT;

  if (!r) {
    retCode = -1;
    std::cout << "Invalid number of arguments!" << std::endl;
    std::cout << std::endl;
    printHelp(argv[0]);
  }

  return r;
}

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  int ret;
  std::unique_ptr<merge_json::FileReader> reader(new merge_json::FileReader());
  std::unique_ptr<merge_json::FileWriter> writer(new merge_json::FileWriter());
  std::unique_ptr<merge_json::IMerger> merger(new merge_json::NlohmannMerger());
  std::string content1;
  std::string content2;
  std::string output;

  // Parse args
  if (!parseArgs(argc, argv, ret)) return ret;

  // Read file contents
  if (reader->readFile(file1Path, content1)) {
    std::cout << "Cannot read " << file1Path << std::endl;
    return -1;
  }
  if (reader->readFile(file2Path, content2)) {
    std::cout << "Cannot read " << file2Path << std::endl;
    return -1;
  }

  // Merge json files
  try {
    merger->merge(content1, content2, output);
  } catch (std::exception& e) {
    std::cout << "Cannot merge " << file1Path << " with " << file2Path
              << std::endl;
    return -1;
  }

  // Write output to file
  if (writer->writeFile(outputPath, output)) {
    std::cout << "Cannot write to " << outputPath << std::endl;
    return -1;
  }

  // Merge json files
  return ret;
}
