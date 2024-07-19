#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

class VulkanDemo {
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *m_window_ { nullptr };
    VkInstance instance_;

    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_window_ = glfwCreateWindow(WIDTH, HEIGHT, "vulkan demo", nullptr, nullptr);
        if (!m_window_) {
            throw std::runtime_error("Failed");
        }
    }

    void initVulkan()
    {
        VkApplicationInfo appinfo = {};
        appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appinfo.pApplicationName = "vulkan demo";
        appinfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appinfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appinfo;

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledExtensionCount = glfwExtensionCount;

        if (vkCreateInstance(&createInfo, nullptr, &instance_) != VK_SUCCESS) {

        }
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(m_window_)) {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        vkDestroyInstance(instance_, nullptr);
        glfwDestroyWindow(m_window_);
        glfwTerminate();
    }
};

int main ()
{
    VulkanDemo demo;

    demo.run();

    return 0;
}
