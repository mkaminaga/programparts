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
#include "./process_performance_monitor.h"
#include "./util.h"

SystemPerformaceMonitor::SystemPerformaceMonitor() { return; }

SystemPerformaceMonitor::~SystemPerformaceMonitor() { return; }

bool SystemPerformaceMonitor::Sample() {
  // Save last sampling result.
  last_idle_time = idle_time;
  last_kernel_time = kernel_time;
  last_user_time = user_time;

  // Get system times.
  FILETIME ft_idle, ft_kernel, ft_user;
  if (GetSystemTimes(&ft_idle, &ft_kernel, &ft_user) == 0) {
    return false;
  }

  idle_time = FILETIME_TO_ULONGLONG(ft_idle);
  kernel_time = FILETIME_TO_ULONGLONG(ft_kernel);
  user_time = FILETIME_TO_ULONGLONG(ft_user);
  return true;
}

double SystemPerformaceMonitor::GetTotalCPU() const {
  const ULONGLONG idle = idle_time - last_idle_time;
  const ULONGLONG user = user_time - last_user_time;
  const ULONGLONG kernel = kernel_time - last_kernel_time;
  const ULONGLONG system = user + kernel;
  if (system == 0LL) {
    return -1.0;
  }
  return (system - idle) / static_cast<double>(system) * 100.0;
}

double SystemPerformaceMonitor::GetUserCPU() const {
  const ULONGLONG user = user_time - last_user_time;
  const ULONGLONG kernel = kernel_time - last_kernel_time;
  const ULONGLONG system = user + kernel;
  if (system == 0) {
    return -1.0;
  }
  return user / static_cast<double>(system) * GetTotalCPU();
}

double SystemPerformaceMonitor::GetKernelCPU() const {
  const ULONGLONG user = user_time - last_user_time;
  const ULONGLONG kernel = kernel_time - last_kernel_time;
  const ULONGLONG system = user + kernel;
  if (system == 0) {
    return -1.0;
  }
  return kernel / static_cast<double>(system) * GetTotalCPU();
}

void SystemPerformaceMonitor::GetCPUTime(ULONGLONG* user,
                                         ULONGLONG* kernel) const {
  assert(user);
  assert(kernel);
  *user = user_time;
  *kernel = kernel_time;
}

void SystemPerformaceMonitor::GetCPUDeltaTime(ULONGLONG* user,
                                              ULONGLONG* kernel) const {
  assert(user);
  assert(kernel);
  *user = user_time - last_user_time;
  *kernel = kernel_time - last_kernel_time;
}

void SystemPerformaceMonitor::GetCPUIdleTime(ULONGLONG* idle) const {
  assert(idle);
  *idle = idle_time;
}

void SystemPerformaceMonitor::GetCPUIdleDeltaTime(ULONGLONG* delta_idle) const {
  assert(idle_time);
  *delta_idle = idle_time - last_idle_time;
}

ProcessPerformaceMonitor*
SystemPerformaceMonitor::CreateProcessPerformanceMonitor() {
  HINSTANCE hInstance = GetModuleHandle(NULL);  // Default is set .
  return new ProcessPerformaceMonitor(this, hInstance);
}
