#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <optional>
#include <set>
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_VERSION_1_0

class VulkanInit
{
private:
	GLFWwindow* window;												// ������ ����
	VkInstance instance;											// ���������� ����������
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;				// ���������� ����������
	VkDebugUtilsMessengerEXT debugMessenger;						// ���������� ����������� �����������
	VkDevice device;												// ���������� ����������� ����������
	VkQueue graphicsQueue;											// ���������� ����������� ��������
	VkQueue presentQueue;											// ���������� ������� �����������
	VkSurfaceKHR surface;											// ���������� ��� ������ ������������� �����������
	VkSwapchainKHR swapChain;										// ���������� swap chain
	VkFormat swapChainImageFormat;									// ������ ����������� � swap chain
	VkExtent2D swapChainExtent;										// ���������� ����������� � swap chain
	VkRenderPass renderPass;										// ������ �������
	VkPipelineLayout pipelineLayout;								// Layout ���������
	VkPipeline graphicsPipeline;									// ����������� ��������
	VkCommandPool commandPool;										// ��� ������
	std::vector<VkImageView> swapChainImageViews;					// ������������� VkImage, ����������� ��� ��� ���������
	std::vector<VkFramebuffer> swapChainFramebuffers;				// �����������
	std::vector<VkCommandBuffer> commandBuffers;					// ������ ������
	const uint32_t WIDTH = 800;										// ������ ����
	const uint32_t HEIGHT = 600;									// ������ ����
	const std::vector<const char*> validationsLayers = {			// ������, �������� ���� ���������, ������� ����� ��������
		"VK_LAYER_KHRONOS_validation"
	};				
	const std::vector<const char*> deviceExtension = {				// ������, �������� ������ ��������� ����������
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	std::vector<VkImage> swapChainImage;							// ������ ��� �������� ����������� �� swap chain

#ifdef NDEBUG														// ����������, ������� ���������� ���������� ����������� ����� ���������, � 
	const bool enableValidationsLayers = false;						
#else																// ����������� �� ������ ������
	const bool enableValidationsLayers = true;
#endif
	struct QueueFamilyIndices										// ��������� ��� �������� �������� �������� ������� ��� ������� ����������
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct SwapChainSupportDetails {								// ��������� ��� �������� ���������� ��� ��������� swap chain
		VkSurfaceCapabilitiesKHR capabilities;						// ������� ���������� surface
		std::vector<VkSurfaceFormatKHR> formats;					// ������ surface
		std::vector<VkPresentModeKHR> presentModes;					// ��������� ������ ������
	};

	void initWindow();												// ������������� ����
	void initVulkan();												// ������������� Vulkan
	void mainLoop();												// ������� �����, � ������� ��� ���������� �����������
	void cleanup();													// �������� ���� ��������� � ��������
	void createInstance();											// �������� ���������� ����������
	void pickPhysicalDevice();										// ����� ����������
	void createLogicalDevice();										// ������� �������� ����������� ����������
	void createSurface();											// �������� surface
	void createSwapChain();											// �������� swap chain
	void createImageViews();										// �������� image view
	void createGraphicsPipeline();									// �������� ������������ ���������
	void createRenderPass();										// �������� ������� �������
	void createFramebuffers();										// �������� �����������
	void createCommandPool();										// �������� ���� ������
	void createCommandBuffers();									// �������� ������ ������
	VkShaderModule createShaderModule(const std::vector<char>& code);			// �������� ShaderModule
	bool checkValidationsLayerSupport();							// ������� �������� ����������� ����� ���������
	bool isDeviceSuitable(VkPhysicalDevice device);					// �������� �������� �� ����������
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);		// �������� ��������� ���������� �����������
	QueueFamilyIndices findQueueFamily(VkPhysicalDevice device);	// ������� ������ ��������� �������, �������������� �����������
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);// ������� ���������� ��������� SwapChainSupportDetails
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);	// ������� ������ ��������� ������� �����
	VkPresentModeKHR shooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);		// ������� ������ ���������� ������ ������
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);								// ������� ������ ���������� ����������
	std::vector<const char*> getRequiredExtensions();				// ������� ���������� ��������� ������ ����������
	static std::vector<char> readFile(const std::string& filename);	// ������� ������ ������ �������
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData,
		void* pUserData);											// ������� ��������� ���������� ���������
public:
	void run();														// ����� ������� ���������
};

