cmake_minimum_required(VERSION 3.5)
project(assignment2_rt_part2)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED) # Necessario per i servizi

# Aggiungi la generazione delle interfacce per i servizi
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/VelService.srv"
  DEPENDENCIES std_msgs
)

# Aggiungi l'eseguibile
add_executable(moving_controller src/moving_controller.cpp)

# Collegalo alle dipendenze
ament_target_dependencies(moving_controller
  rclcpp
  std_msgs
  geometry_msgs
  nav_msgs
)

# Collega i tipi generati al tuo eseguibile
rosidl_get_typesupport_target(cpp_typesupport_target ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(moving_controller ${cpp_typesupport_target})

# Installazione dei file necessari
install(DIRECTORY launch urdf config worlds DESTINATION share/${PROJECT_NAME}/)
install(TARGETS moving_controller DESTINATION lib/${PROJECT_NAME})

# Sezione per i test (non modificata)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

