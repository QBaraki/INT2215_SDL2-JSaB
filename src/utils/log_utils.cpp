#include "log_utils.h"

#include <iostream>
#include <chrono>

static void LogStatus(Status* status) {
  auto delay_start_time = std::chrono::high_resolution_clock::now();
  while (status->running) {
    auto cur_time = std::chrono::high_resolution_clock::now();
    int delta = std::chrono::duration<float, std::chrono::milliseconds::period>(cur_time - delay_start_time).count();
    if (delta < 1000) {
      continue;
    }
    delay_start_time = cur_time;
    std::cerr << "Frame time: " << status->delta_time << " FPS: ";
    if ((int)status->delta_time == 0) {
      std::cerr << "inf";
    } else {
      std::cerr << 1000 / (int)status->delta_time;
    }
    std::cerr << '\n';
  }
}

std::thread LogUtils::thread_status(Status* status) {
  return std::thread(LogStatus, status);
}