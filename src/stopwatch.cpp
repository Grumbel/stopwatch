#include <boost/format.hpp>
#include <iostream>
#include <stdint.h>
#include <sys/time.h>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <stdexcept>

uint64_t get_sys_time()
{
  struct timeval  tv;

  if (gettimeofday(&tv, NULL) < 0)
  {
    std::ostringstream str;
    str << strerror(errno);
    throw std::runtime_error(str.str());
  }
  else
  {
    return static_cast<uint64_t>(tv.tv_sec) * 1000000 + static_cast<uint64_t>(tv.tv_usec);
  }
}

const uint64_t microsec_to_hours   = 1000ul * 1000ul * 60ul * 60ul;
const uint64_t microsec_to_minutes = 1000ul * 1000ul * 60ul;
const uint64_t microsec_to_seconds = 1000ul * 1000ul;
const uint64_t microsec_to_milisec = 1000ul;

void print_time(uint64_t time)
{
  int hours    = time / microsec_to_hours;   time -= hours   * microsec_to_hours;
  int minutes  = time / microsec_to_minutes; time -= minutes * microsec_to_minutes;
  int seconds  = time / microsec_to_seconds; time -= seconds * microsec_to_seconds;
  int milisec  = time / microsec_to_milisec; time -= milisec * microsec_to_milisec;
  //int microsec = time;

  //std::cout << hours << ":" << minutes << ":" << seconds << "." << milisec << "'" << microsec << std::endl;

  //std::cout << boost::format("%02d:%02d:%02d'%03d'%03d") % hours % minutes % seconds % milisec % microsec << std::endl;
  std::cout << boost::format("Time: %02d:%02d:%02d'%03d") % hours % minutes % seconds % milisec << '\r' << std::flush;
}

int main(int argc, char** argv)
{
  uint64_t start_time = get_sys_time();
  uint64_t last_time = ~0ul;

  while(true)
  {
    uint64_t t = get_sys_time() - start_time;

    if (t/1000 != last_time/1000)
    {
      print_time(t);
      last_time = t;
    }
    usleep(10000);
  }

  return 0;
}

/* EOF */
