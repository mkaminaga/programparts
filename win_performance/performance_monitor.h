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
  virtual double GetTotalCPU() const = 0;
  virtual double GetUserCPU() const = 0;
  virtual double GetKernelCPU() const = 0;
  virtual void GetCPUTime(ULONGLONG* user, ULONGLONG* kernel) const = 0;
  virtual void GetCPUDeltaTime(ULONGLONG* user, ULONGLONG* kernel) const = 0;
};

#endif  // PERFORMANCE_MONITOR_H_
