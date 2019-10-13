//
// @file system_performance_monitor.cc
// @brief System performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:31:37
// Copyright 2019 Mamoru Kaminaga
//
#include "./system_performance_monitor.h"
#include <assert.h>
#include <windows.h>
#include <numeric>
#include <vector>
#include "./util.h"

SystemPerformaceMonitor::SystemPerformaceMonitor() { return; }

SystemPerformaceMonitor::~SystemPerformaceMonitor() { return; }

bool SystemPerformaceMonitor::Sample() {
  // Save last sampling result.
  last_idle_time.QuadPart = idle_time.QuadPart;
  last_kernel_time.QuadPart = kernel_time.QuadPart;
  last_user_time.QuadPart = user_time.QuadPart;

  // Get system times.
  FILETIME ft_idle, ft_kernel, ft_user;
  if (GetSystemTimes(&ft_idle, &ft_kernel, &ft_user) == 0) {
    return false;
  }
  idle_time = FILETIME_to_ULARGE_INTEGER(ft_idle);
  kernel_time = FILETIME_to_ULARGE_INTEGER(ft_kernel);
  user_time = FILETIME_to_ULARGE_INTEGER(ft_user);
  return true;
}

double SystemPerformaceMonitor::GetTotalCPU() const {
  const LONGLONG idle = idle_time.QuadPart - last_idle_time.QuadPart;
  const LONGLONG user = user_time.QuadPart - last_user_time.QuadPart;
  const LONGLONG kernel = kernel_time.QuadPart - last_kernel_time.QuadPart;
  const LONGLONG system = user + kernel;
  return (kernel + user - idle) / static_cast<double>(kernel + user) * 100.0;
}

double SystemPerformaceMonitor::GetUserCPU() const {
  const LONGLONG idle = idle_time.QuadPart - last_idle_time.QuadPart;
  const LONGLONG user = user_time.QuadPart - last_user_time.QuadPart;
  const LONGLONG kernel = kernel_time.QuadPart - last_kernel_time.QuadPart;
  const LONGLONG system = user + kernel;
  return (user / static_cast<double>(system)) * (system - idle) /
         static_cast<double>(system) * 100.0;
}

double SystemPerformaceMonitor::GetKernelCPU() const {
  const LONGLONG idle = idle_time.QuadPart - last_idle_time.QuadPart;
  const LONGLONG user = user_time.QuadPart - last_user_time.QuadPart;
  const LONGLONG kernel = kernel_time.QuadPart - last_kernel_time.QuadPart;
  const LONGLONG system = user + kernel;
  return (kernel / static_cast<double>(system)) * (system - idle) /
         static_cast<double>(system) * 100.0;
}

void SystemPerformaceMonitor::GetCPUTime(ULARGE_INTEGER* idle,
                                         ULARGE_INTEGER* user,
                                         ULARGE_INTEGER* kernel) const {
  assert(idle);
  assert(user);
  assert(kernel);
  *idle = idle_time;
  *user = user_time;
  *kernel = kernel_time;
}
