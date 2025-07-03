#include "ConfigManager.h"
#include <fstream>
#include <iostream>
#include <filesystem>

ConfigManager::ConfigManager(const std::string& mode, const std::string& configPath)
    : m_mode(mode), m_configPath(configPath) {
    // Validate mode
    if (mode != "demo" && mode != "prod") {
        throw std::invalid_argument("Invalid mode: " + mode + ". Must be 'demo' or 'prod'");
    }
}

void ConfigManager::loadConfig() {
    std::string configFile = getConfigFilePath();
    
    // Check if file exists
    if (!std::filesystem::exists(configFile)) {
        throw std::runtime_error("Configuration file not found: " + configFile);
    }
    
    // Load and parse JSON file
    std::ifstream file(configFile);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + configFile);
    }
    
    try {
        file >> m_config;
    } catch (const nlohmann::json::exception& e) {
        throw std::runtime_error("Failed to parse JSON configuration: " + std::string(e.what()));
    }
    
    // Validate configuration structure
    if (!validateConfig()) {
        throw std::runtime_error("Invalid configuration structure in file: " + configFile);
    }
    
    std::cout << "ConfigManager: Successfully loaded configuration for mode: " << m_mode << std::endl;
}

ConfigManager::OKXConfig ConfigManager::getOKXConfig() const {
    if (!isLoaded()) {
        throw std::runtime_error("Configuration not loaded. Call loadConfig() first.");
    }
    
    if (!m_config.contains("OKXDataSrc")) {
        throw std::runtime_error("OKXDataSrc configuration not found");
    }
    
    const auto& okxSection = m_config["OKXDataSrc"];
    
    OKXConfig config;
    try {
        config.url_pub = okxSection.at("url_pub").get<std::string>();
        config.url_private = okxSection.at("url_private").get<std::string>();
        config.API_key = okxSection.at("API_key").get<std::string>();
        config.API_secret = okxSection.at("API_secret").get<std::string>();
        config.API_passphrase = okxSection.at("API_passphrase").get<std::string>();
    } catch (const nlohmann::json::exception& e) {
        throw std::runtime_error("Failed to parse OKX configuration: " + std::string(e.what()));
    }
    
    return config;
}

ConfigManager::ConnectorConfig ConfigManager::getConnectorConfig() const {
    ConnectorConfig config;
    config.OKXDataSrc = getOKXConfig();
    return config;
}

bool ConfigManager::validateConfig() const {
    if (m_config.empty()) {
        return false;
    }
    
    // Check if OKXDataSrc section exists
    if (!m_config.contains("OKXDataSrc")) {
        std::cerr << "ConfigManager: Missing OKXDataSrc section" << std::endl;
        return false;
    }
    
    return validateOKXConfig(m_config["OKXDataSrc"]);
}

std::string ConfigManager::getConfigFilePath() const {
    std::string filename = m_mode + ".json";
    
    // Handle both relative and absolute paths
    if (m_configPath.back() == '/') {
        return m_configPath + filename;
    } else {
        return m_configPath + "/" + filename;
    }
}

bool ConfigManager::validateOKXConfig(const nlohmann::json& okxSection) const {
    // Required fields for OKX configuration
    const std::vector<std::string> requiredFields = {
        "url_pub", "url_private", "API_key", "API_secret", "API_passphrase"
    };
    
    for (const auto& field : requiredFields) {
        if (!okxSection.contains(field)) {
            std::cerr << "ConfigManager: Missing required field in OKXDataSrc: " << field << std::endl;
            return false;
        }
        
        if (!okxSection[field].is_string()) {
            std::cerr << "ConfigManager: Field must be string in OKXDataSrc: " << field << std::endl;
            return false;
        }
        
        if (okxSection[field].get<std::string>().empty()) {
            std::cerr << "ConfigManager: Empty value for required field in OKXDataSrc: " << field << std::endl;
            return false;
        }
    }
    
    // Validate URL format (basic check)
    std::string url_pub = okxSection["url_pub"].get<std::string>();
    std::string url_private = okxSection["url_private"].get<std::string>();
    
    if (url_pub.substr(0, 6) != "wss://" && url_pub.substr(0, 5) != "ws://") {
        std::cerr << "ConfigManager: Invalid public URL format: " << url_pub << std::endl;
        return false;
    }
    
    if (url_private.substr(0, 6) != "wss://" && url_private.substr(0, 5) != "ws://") {
        std::cerr << "ConfigManager: Invalid private URL format: " << url_private << std::endl;
        return false;
    }
    
    return true;
} 