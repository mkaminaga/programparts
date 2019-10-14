//
// @file process_performance_monitor.h
// @brief Process performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:31:37
// Copyright 2019 Mamoru Kaminaga
//
#ifndef PROCESS_PERFORMANCE_MONITOR_H_
#define PROCESS_PERFORMANCE_MONITOR_H_

#include <windows.h>
#include <vector>
#include "./performance_monitor.h"

class ProcessPerformaceMonitor : public PerformaceMonitor {
 public:
  ProcessPerformaceMonitor(PerformaceMonitor* system_performance_monitor,
                           HANDLE hProcess);
  ~ProcessPerformaceMonitor();
  bool Sample();
  ULONGLONG GetUserTime() const;
  ULONGLONG GetKernelTime() const;
  double GetTotalCPU() const;
  double GetUserCPU() const;
  double GetKernelCPU() const;
  void GetCPUTime(ULONGLONG* user, ULONGLONG* kernel) const;
  void GetCPUDeltaTime(ULONGLONG* user, ULONGLONG* kernel) const;

  void GetCPUCreationTime(ULONGLONG* creation_time) const;
  void GetCPUExitTime(ULONGLONG* exit_time) const;
  void ResetTarget(HANDLE hProcess);

 private:
  HANDLE hTragetProcess;
  PerformaceMonitor* system_performance_monitor;
  ULONGLONG creation_time;
  ULONGLONG exit_time;
  ULONGLONG kernel_time;
  ULONGLONG user_time;
  ULONGLONG last_kernel_time;
  ULONGLONG last_user_time;
};

#endif  // PROCESS_PERFORMANCE_MONITOR_H_
