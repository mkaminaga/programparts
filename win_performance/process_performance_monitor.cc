//
// @file process_performance_monitor.cc
// @brief Process performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:31:37
// Copyright 2019 Mamoru Kaminaga
//
#include "./process_performance_monitor.h"
#include <assert.h>
#include <windows.h>
#include <numeric>
#include <vector>
#include "./util.h"

ProcessPerformaceMonitor::ProcessPerformaceMonitor(
    PerformaceMonitor* performance_monitor, HANDLE hProcess)
    : system_performance_monitor(performance_monitor),
      hTragetProcess(hProcess) {}

ProcessPerformaceMonitor::~ProcessPerformaceMonitor() {}

bool ProcessPerformaceMonitor::Sample() {
  assert(hTragetProcess);

  // Save last sampling result.
  last_kernel_time = kernel_time;
  last_user_time = user_time;

  // Get process times.
  FILETIME ft_creation, ft_exit, ft_kernel, ft_user;
  if (GetProcessTimes(hTragetProcess, &ft_creation, &ft_exit, &ft_kernel,
                      &ft_user) == 0) {
    return false;
  }

  creation_time = FILETIME_TO_ULONGLONG(ft_creation);
  exit_time = FILETIME_TO_ULONGLONG(ft_exit);
  kernel_time = FILETIME_TO_ULONGLONG(ft_kernel);
  user_time = FILETIME_TO_ULONGLONG(ft_user);
  return true;
}

double ProcessPerformaceMonitor::GetTotalCPU() const {
  assert(system_performance_monitor);

  ULONGLONG system_user, system_kernel;
  system_performance_monitor->GetCPUDeltaTime(&system_user, &system_kernel);

  const ULONGLONG system = system_user + system_kernel;
  const ULONGLONG process =
      (user_time - last_user_time) + (kernel_time - last_kernel_time);

  if (system == 0) {
    return -1;
  }
  return (process) / static_cast<double>(system) * 100.0;
}

double ProcessPerformaceMonitor::GetUserCPU() const {
  const ULONGLONG delta_process_user = user_time - last_user_time;
  const ULONGLONG delta_process_kernel = kernel_time - last_kernel_time;
  const ULONGLONG process = delta_process_user + delta_process_kernel;
  if (process == 0) {
    return -1;
  }
  return delta_process_user / static_cast<double>(process) * GetTotalCPU();
}

double ProcessPerformaceMonitor::GetKernelCPU() const {
  const ULONGLONG user = user_time - last_user_time;
  const ULONGLONG kernel = kernel_time - last_kernel_time;
  const ULONGLONG process = user + kernel;
  if (process == 0) {
    return -1.0;
  }
  return kernel / static_cast<double>(process) * GetTotalCPU();
}

void ProcessPerformaceMonitor::ResetTarget(HANDLE hProcess) {
  hTragetProcess = hProcess;
  return;
}

void ProcessPerformaceMonitor::GetCPUTime(ULONGLONG* user,
                                          ULONGLONG* kernel) const {
  assert(user);
  assert(kernel);
  *user = user_time;
  *kernel = kernel_time;
  return;
}

void ProcessPerformaceMonitor::GetCPUDeltaTime(ULONGLONG* user,
                                               ULONGLONG* kernel) const {
  assert(user);
  assert(kernel);
  *user = user_time - last_user_time;
  *kernel = kernel_time - last_kernel_time;
  return;
}

void ProcessPerformaceMonitor::GetCPUCreationTime(ULONGLONG* creation) const {
  assert(creation);
  *creation = creation_time;
  return;
}

void ProcessPerformaceMonitor::GetCPUExitTime(ULONGLONG* exit) const {
  assert(exit);
  *exit = exit_time;
  return;
}
