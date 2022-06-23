// stopwatch - Stopwatch for the command line
// Copyright (C) 2022 Ingo Ruhnke <grumbel@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <chrono>
#include <iostream>
#include <thread>

#include <fmt/format.h>

uint64_t const microsec_to_hours    = 1000ul * 60ul * 60ul;
uint64_t const microsec_to_minutes  = 1000ul * 60ul;
uint64_t const microsec_to_seconds  = 1000ul;
uint64_t const microsec_to_millisec = 1ul;

void print_time(std::chrono::milliseconds usec)
{
  std::chrono::milliseconds::rep time = usec.count();

  int const hours    = time / microsec_to_hours;    time -= hours    * microsec_to_hours;
  int const minutes  = time / microsec_to_minutes;  time -= minutes  * microsec_to_minutes;
  int const seconds  = time / microsec_to_seconds;  time -= seconds  * microsec_to_seconds;
  int const millisec = time / microsec_to_millisec; time -= millisec * microsec_to_millisec;

  std::cout << fmt::format("Time: {:02d}:{:02d}:{:02d}'{:03d}\r", hours, minutes, seconds, millisec) << std::flush;
}

int main(int argc, char** argv)
{
  std::chrono::steady_clock::time_point const start_time = std::chrono::steady_clock::now();

  while(true)
  {
    auto const duration = std::chrono::steady_clock::now() - start_time;

    print_time(std::chrono::duration_cast<std::chrono::milliseconds>(duration));

    std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(10));
  }

  return 0;
}

/* EOF */
