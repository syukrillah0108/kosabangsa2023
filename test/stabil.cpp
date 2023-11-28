#include <iostream>
#include <ctime>

int main() {
  // Get the current time in UTC
  std::time_t now = std::time(nullptr);

  // Get the time zone for Bandung, Indonesia
  std::string zone_name = "Asia/Jakarta";
  std::time_zone zone = std::time_zone::from_zone_name(zone_name);

  // Get the UTC time in the Bandung time zone
  std::time_t bandung_time = std::timegm(std::localtime(&now, &zone));

  // Convert the UTC time to local time
  std::tm *local_time = std::localtime(&bandung_time);

  // Print the local time
  std::cout << "The local time in Bandung is " << std::put_time(local_time, "%H:%M:%S") << std::endl;

  return 0;
}

