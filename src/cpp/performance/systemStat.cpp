#include "systemStat.h"

#include <fstream>
#include <string>
#include <sstream>

#include <unistd.h>

// The definition of /proc/stat file
// refer to http://www.mjmwired.net/kernel/Documentation/filesystems/proc.txt#1212 1.8
typedef struct CPUStat {
  unsigned long long user;
  unsigned long long nice;
  unsigned long long system;
  unsigned long long idle;
  unsigned long long iowait;
  unsigned long long irq;
  unsigned long long softirq;

  unsigned long long getTotal() {
    return user + nice + system + idle + iowait + irq + softirq;
  }
} CPUStat;

int readCPUStat(CPUStat& stat) {
  using namespace std;

  const char* StatFile = "/proc/stat";

  ifstream procFile(StatFile);

  const string CPUPrefix = "cpu ";

  std::string line;
  while (getline(procFile, line)) {
    if(line.size() > CPUPrefix.size()
        && (line.compare(0, CPUPrefix.size(), CPUPrefix) == 0)) {
      break;
    }
  }

  if(line.size() == 0) {
    return -1;
  }

  string prefix;
  stringstream cpuLine(line);
  if(cpuLine) {
    cpuLine >> prefix;
  }

  if(cpuLine) {
    cpuLine >> stat.user;
  }

  if(cpuLine) {
    cpuLine >> stat.nice;
  }

  if(cpuLine) {
    cpuLine >> stat.system;
  }

  if(cpuLine) {
    cpuLine >> stat.idle;
  }

  if(cpuLine) {
    cpuLine >> stat.iowait;
  }

  if(cpuLine) {
    cpuLine >> stat.irq;
  }

  if(cpuLine) {
    cpuLine >> stat.softirq;
  }

  return 0;
}

int SystemStat::getCPUUsage() {
  CPUStat firstStat;
  CPUStat secondeStat;

  if( readCPUStat(firstStat) == -1) {
    return 0;
  }

  sleep(1);

  if( readCPUStat(secondeStat) == -1) {
    return 0;
  }

  unsigned long long totalDiff = secondeStat.getTotal() - firstStat.getTotal();
  unsigned long long idleDiff = secondeStat.idle - firstStat.idle;

  return ((totalDiff - idleDiff) * 1000 / totalDiff  + 5 ) / 10;
}
