//
// @file performance_monitor.h
// @brief Base class for performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:31:37
// Copyright 2019 Mamoru Kaminaga
//
#ifndef PERFORMANCE_MONITOR_H_
#define PERFORMANCE_MONITOR_H_

#include <windows.h>

class PerformaceMonitor {
 public:
  virtual ~PerformaceMonitor() {}
  virtual bool Sample() = 0;
  virtual double GetCPU() = 0;
  virtual ULARGE_INTEGER GetUserTime() = 0;
  virtual ULARGE_INTEGER GetKernelTime() = 0;
};

ULARGE_INTEGER FILETIME_to_ULARGE_INTEGER(const FILETIME& file_time);

#endif  // PERFORMANCE_MONITOR_H_
