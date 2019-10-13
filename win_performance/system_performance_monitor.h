//
// @file system_performance_monitor.h
// @brief System performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:31:37
// Copyright 2019 Mamoru Kaminaga
//
#ifndef SYSTEM_PERFORMANCE_MONITOR_H_
#define SYSTEM_PERFORMANCE_MONITOR_H_

#include <windows.h>
#include <vector>
#include "./performance_monitor.h"

class SystemPerformaceMonitor : public PerformaceMonitor {
 public:
  SystemPerformaceMonitor();
  ~SystemPerformaceMonitor();
  bool Sample();
  double GetTotalCPU() const;
  double GetUserCPU() const;
  double GetKernelCPU() const;
  void GetCPUTime(ULARGE_INTEGER* idle, ULARGE_INTEGER* user,
                  ULARGE_INTEGER* kernel) const;

 private:
  // This sampling.
  ULARGE_INTEGER idle_time;
  ULARGE_INTEGER kernel_time;
  ULARGE_INTEGER user_time;

  // Last sampling.
  ULARGE_INTEGER last_idle_time;
  ULARGE_INTEGER last_kernel_time;
  ULARGE_INTEGER last_user_time;
};

#endif  // SYSTEM_PERFORMANCE_MONITOR_H_
