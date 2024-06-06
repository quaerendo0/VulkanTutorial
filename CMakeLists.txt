cmake_minimum_required(VERSION 3.28)
project(VulkanTutorial)

set(CMAKE_CXX_STANDARD 17)

add_executable(VulkanTutorial main.cpp)

find_package(Vulkan REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)