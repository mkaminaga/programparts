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
#include "./process_performance_monitor.h"

class SystemPerformaceMonitor : public PerformaceMonitor {
 public:
  SystemPerformaceMonitor();
  ~SystemPerformaceMonitor();
  bool Sample();
  double GetTotalCPU() const;
  double GetUserCPU() const;
  double GetKernelCPU() const;
  void GetCPUTime(ULONGLONG* user, ULONGLONG* kernel) const;
  void GetCPUDeltaTime(ULONGLONG* user, ULONGLONG* kernel) const;

  void GetCPUIdleTime(ULONGLONG* idle) const;
  void GetCPUIdleDeltaTime(ULONGLONG* idle_delta) const;
  ProcessPerformaceMonitor* CreateProcessPerformanceMonitor();

 private:
  ULONGLONG idle_time;
  ULONGLONG kernel_time;
  ULONGLONG user_time;
  ULONGLONG last_idle_time;
  ULONGLONG last_kernel_time;
  ULONGLONG last_user_time;
};

#endif  // SYSTEM_PERFORMANCE_MONITOR_H_
