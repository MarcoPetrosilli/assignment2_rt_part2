cmake_minimum_required(VERSION 3.5)
project(assignment2_rt_part2)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/StopService.srv"
)

add_executable(StopServiceNode src/stop_service.cpp)

ament_target_dependencies(StopServiceNode rclcpp rclcpp_action std_msgs geometry_msgs nav_msgs)

rosidl_target_interfaces(stop_service_node
  ${PROJECT_NAME} "rosidl_typesupport_cpp"
)

install(TARGETS stop_service_node DESTINATION lib/${PROJECT_NAME})

ament_package()

