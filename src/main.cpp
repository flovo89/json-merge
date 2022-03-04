#include <getopt.h>

#include <csignal>
#include <iostream>

#include "version.hpp"

/* constants */

/* Locals */

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
  std::cout << "-h|--help         Shows this help and quit" << std::endl;
  std::cout << "-v|--version      Print version and quit" << std::endl;
}

//--------------------------------------------------------------------------------------------
bool parseArgs(int argc, char* argv[], int& retCode) {
  static struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                         {"version", no_argument, NULL, 'v'},
                                         {0, 0, 0, 0}};
  int option_index = 0;

  while (1) {
    int c = getopt_long(argc, argv, "hv", long_options, &option_index);

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
      default:
        printHelp(argv[0]);
        retCode = -1;
        return false;
    }
  }

  return true;
}

//--------------------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  int ret;

  // Parse args
  if (!parseArgs(argc, argv, ret)) return ret;

  return ret;
}
