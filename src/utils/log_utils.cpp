#include "log_utils.h"

#include <iostream>
#include <chrono>

#ifdef NDEBUG
#define cerr \
  if (0)     \
  std::cerr
#else
using std::cerr;
#endif  // NDEBUG

static void LogStatus(Status* status) {
  auto delay_start_time = std::chrono::high_resolution_clock::now();
  while (status->running) {
    auto cur_time = std::chrono::high_resolution_clock::now();
    int delta = (int)std::chrono::duration<float, std::chrono::milliseconds::period>(cur_time - delay_start_time).count();
    if (delta < 1000) {
      continue;
    }
    delay_start_time = cur_time;
    cerr << "Frame time: " << status->delta_time << " FPS: ";
    if ((int)status->delta_time == 0) {
      cerr << "inf";
    } else {
      cerr << 1000 / (int)status->delta_time;
    }
    cerr << '\n';
  }
}

std::thread LogUtils::thread_status(Status* status) {
  return std::thread(LogStatus, status);
}