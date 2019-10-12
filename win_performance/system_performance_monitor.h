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
  SystemPerformaceMonitor(int cpu_history_size);
  ~SystemPerformaceMonitor();
  bool Sample();
  double GetCPUPercentage();
  ULARGE_INTEGER GetUserTime();
  ULARGE_INTEGER GetKernelTime();

  ULARGE_INTEGER GetIdleTime();

 private:
  // This sampling.
  ULARGE_INTEGER idle_time;
  ULARGE_INTEGER kernel_time;
  ULARGE_INTEGER user_time;

  // Last sampling.
  ULARGE_INTEGER last_idle_time;
  ULARGE_INTEGER last_kernel_time;
  ULARGE_INTEGER last_user_time;

  // Misc.
  double cpu_percentage;
  std::vector<double> cpu_history;
};

#endif  // SYSTEM_PERFORMANCE_MONITOR_H_
