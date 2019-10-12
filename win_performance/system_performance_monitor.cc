//
// @file system_performance_monitor.cc
// @brief System performance monitor.
// @author Mamoru Kaminaga
// @date 2019-10-12 14:31:37
// Copyright 2019 Mamoru Kaminaga
//
#include "./system_performance_monitor.h"
#include <windows.h>
#include <numeric>
#include <vector>
#include "./util.h"

SystemPerformaceMonitor::SystemPerformaceMonitor() { cpu_history.resize(3); }

SystemPerformaceMonitor::~SystemPerformaceMonitor() {}

bool SystemPerformaceMonitor::Sample() {
  // Save last sampling result.
  memcpy(&last_idle_time, &idle_time, sizeof(idle_time));
  memcpy(&last_kernel_time, &kernel_time, sizeof(kernel_time));
  memcpy(&last_user_time, &user_time, sizeof(user_time));

  // Get system times.
  FILETIME ft_idle, ft_kernel, ft_user;
  if (GetSystemTimes(&ft_idle, &ft_kernel, &ft_user) == 0) {
    return false;
  }
  idle_time = FILETIME_to_ULARGE_INTEGER(ft_idle);
  kernel_time = FILETIME_to_ULARGE_INTEGER(ft_kernel);
  user_time = FILETIME_to_ULARGE_INTEGER(ft_user);

  // Get interval times since last sampling.
  LONGLONG idle = idle_time.QuadPart - last_idle_time.QuadPart;
  LONGLONG kernel = kernel_time.QuadPart - last_kernel_time.QuadPart;
  LONGLONG user = user_time.QuadPart - last_user_time.QuadPart;
  LONGLONG system = kernel + user;

  // Get CPU percentage.
  double this_time = (system - idle) / static_cast<double>(system) * 100.0;

  // Update moving average.
  for (int i = 0; i < static_cast<int>(cpu_history.size() - 1); i++) {
    cpu_history[i] = cpu_history[i + 1];
  }
  cpu_history[cpu_history.size() - 1] = this_time;

  // Calculate moving average for CPU percentage.
  cpu_percentage =
      std::accumulate(cpu_history.begin(), cpu_history.end(), 0.0L) /
      static_cast<double>(cpu_history.size());

  return true;
}

double SystemPerformaceMonitor::GetCPUPercentage() { return cpu_percentage; }

ULARGE_INTEGER SystemPerformaceMonitor::GetUserTime() { return user_time; }

ULARGE_INTEGER SystemPerformaceMonitor::GetKernelTime() { return kernel_time; }

ULARGE_INTEGER SystemPerformaceMonitor::GetIdleTime() { return idle_time; }
