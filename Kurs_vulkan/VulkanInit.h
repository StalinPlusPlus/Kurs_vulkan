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
	GLFWwindow* window;												// Объект окна
	VkInstance instance;											// Дескриптор экземпляра
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;				// Дескриптор видеокарты
	VkDebugUtilsMessengerEXT debugMessenger;						// Дескриптор отладочного мессенджера
	VkDevice device;												// Дескриптор логического устройства
	VkQueue graphicsQueue;											// Дескриптор графических очередей
	VkQueue presentQueue;											// Дескриптор очереди отображения
	VkSurfaceKHR surface;											// Расширение для показа отрендеренных изображений
	VkSwapchainKHR swapChain;										// Дескриптор swap chain
	VkFormat swapChainImageFormat;									// Формат изображений в swap chain
	VkExtent2D swapChainExtent;										// Разрешение изображений в swap chain
	VkRenderPass renderPass;										// Проход рендера
	VkPipelineLayout pipelineLayout;								// Layout конвейера
	VkPipeline graphicsPipeline;									// Графический конвейер
	VkCommandPool commandPool;										// Пул команд
	std::vector<VkImageView> swapChainImageViews;					// Интерпретатор VkImage, необходимый для его просмотра
	std::vector<VkFramebuffer> swapChainFramebuffers;				// Фреймбуферы
	std::vector<VkCommandBuffer> commandBuffers;					// Буферы команд
	const uint32_t WIDTH = 800;										// Ширина окна
	const uint32_t HEIGHT = 600;									// Высота окна
	const std::vector<const char*> validationsLayers = {			// Вектор, хранящий слои валидации, которые нужно включить
		"VK_LAYER_KHRONOS_validation"
	};				
	const std::vector<const char*> deviceExtension = {				// Вектор, хранящий список требуемых расширений
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	std::vector<VkImage> swapChainImage;							// Вектор для хранения изображений из swap chain

#ifdef NDEBUG														// Переменная, которая определяет разрешение подключение слоев валидации, в 
	const bool enableValidationsLayers = false;						
#else																// зависимости от режима сборки
	const bool enableValidationsLayers = true;
#endif
	struct QueueFamilyIndices										// Структура для хранения индексов семейств очереди для данного устройства
	{
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete()
		{
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};
	struct SwapChainSupportDetails {								// Структура для хранения информации для настройки swap chain
		VkSurfaceCapabilitiesKHR capabilities;						// Базовые требования surface
		std::vector<VkSurfaceFormatKHR> formats;					// Формат surface
		std::vector<VkPresentModeKHR> presentModes;					// Доступные режими работы
	};

	void initWindow();												// Инициализация окна
	void initVulkan();												// Инициализация Vulkan
	void mainLoop();												// Главный метод, в котором все циклически выполняется
	void cleanup();													// Удаление всех элементов и объектов
	void createInstance();											// Создание экземпляра библиотеки
	void pickPhysicalDevice();										// Выбор видеокарты
	void createLogicalDevice();										// Функция создания логического устройства
	void createSurface();											// Создание surface
	void createSwapChain();											// Создание swap chain
	void createImageViews();										// Создание image view
	void createGraphicsPipeline();									// Создание графического конвейера
	void createRenderPass();										// Создание прохода рендера
	void createFramebuffers();										// Создание фреймбуфера
	void createCommandPool();										// Создание пула команд
	void createCommandBuffers();									// Создание буфера команд
	VkShaderModule createShaderModule(const std::vector<char>& code);			// Создание ShaderModule
	bool checkValidationsLayerSupport();							// Функция проверки доступности слоев валидации
	bool isDeviceSuitable(VkPhysicalDevice device);					// Проверка подходит ли видеокарта
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);		// Проверка поддержки расширений устройством
	QueueFamilyIndices findQueueFamily(VkPhysicalDevice device);	// Функции поиска семейства очереди, поддерживаемых видеокартой
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);// Функция заполнения структуры SwapChainSupportDetails
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);	// Функция выбора наилучшей глубины цвета
	VkPresentModeKHR shooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);		// Функция выбора наилучшего режима работы
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);								// Функция выбора наилучшего разрешение
	std::vector<const char*> getRequiredExtensions();				// Функция возвращает требуемый список расширений
	static std::vector<char> readFile(const std::string& filename);	// Функция чтения файлов шейдера
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData,
		void* pUserData);											// Функция перехвата отладочных сообщений
public:
	void run();														// Метод запуска программы
};

