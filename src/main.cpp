#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include "CalculationClass.h"
#include "WebSocketClass.h"
#include "ConfigManager.h"

int main()
{
   std::cout << "=====================================================\n"
             << "| OKX EXCHANGE CONNECTOR WITH CONFIGURATION SYSTEM |\n"
             << "=====================================================\n" << std::endl;

   // Test Configuration Manager
   try {
       std::cout << "Testing Configuration Manager..." << std::endl;
       
       // Load demo configuration
       ConfigManager configManager("demo");
       configManager.loadConfig();
       
       // Get OKX configuration
       auto okxConfig = configManager.getOKXConfig();
       
       std::cout << "Configuration loaded successfully!" << std::endl;
       std::cout << "Mode: " << configManager.getMode() << std::endl;
       std::cout << "Public URL: " << okxConfig.url_pub << std::endl;
       std::cout << "Private URL: " << okxConfig.url_private << std::endl;
       std::cout << "API Key: " << okxConfig.API_key.substr(0, 8) << "..." << std::endl;
       std::cout << std::endl;
       
       // Use the configuration for WebSocket connection
       std::string uri = okxConfig.url_pub;
       
       srand(time(0));
       std::atomic<bool> flag(false);
       std::atomic<int> WebSocketRequestsCount(0);
       std::atomic<int> heavyTasksCount(0);
       std::mutex mutex;
       CalculationClass Calculation(1000);

       WebSocketClass webSocket(uri, WebSocketRequestsCount, mutex);

       std::cout << "=====================================================\n"
                 << "| ORDER BOOK FOR BTC-USDT AND INVERSE MATRIX AX = E |\n"
                 << "=====================================================\n";

       std::thread webSocketThread([&]()
                                   { webSocket.wsrun(flag); });

       std::thread calculationThread([&]()
                                     { Calculation.run(flag, heavyTasksCount, mutex); });

       std::this_thread::sleep_for(std::chrono::seconds(60));
       flag.store(true);

       calculationThread.join();
       webSocketThread.join();

       std::cout << "Total WebSocket requests made: " << webSocket.m_WebSocketRequestsCount << std::endl;
       std::cout << "Total calculations completed: " << heavyTasksCount << std::endl;
       
   } catch (const std::exception& e) {
       std::cerr << "Configuration Error: " << e.what() << std::endl;
       std::cerr << "Falling back to hardcoded configuration..." << std::endl;
       
       // Fallback to original hardcoded behavior
       srand(time(0));
       std::atomic<bool> flag(false);
       std::atomic<int> WebSocketRequestsCount(0);
       std::atomic<int> heavyTasksCount(0);
       std::mutex mutex;
       CalculationClass Calculation(1000);

       std::string uri = "wss://ws.okx.com:8443/ws/v5/public";
       WebSocketClass webSocket(uri, WebSocketRequestsCount, mutex);

       std::cout << "=====================================================\n"
                 << "| ORDER BOOK FOR BTC-USDT AND INVERSE MATRIX AX = E |\n"
                 << "=====================================================\n";

       std::thread webSocketThread([&]()
                                   { webSocket.wsrun(flag); });

       std::thread calculationThread([&]()
                                     { Calculation.run(flag, heavyTasksCount, mutex); });

       std::this_thread::sleep_for(std::chrono::seconds(60));
       flag.store(true);

       calculationThread.join();
       webSocketThread.join();

       std::cout << "Total WebSocket requests made: " << webSocket.m_WebSocketRequestsCount << std::endl;
       std::cout << "Total calculations completed: " << heavyTasksCount << std::endl;
   }

   return 0;
}
