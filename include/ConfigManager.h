#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <nlohmann/json.hpp>
#include <stdexcept>

/**
 * @brief Configuration management class for loading JSON-based configurations
 * 
 * This class provides functionality to load configuration files for different
 * environments (demo, prod) and access configuration values in a type-safe manner.
 * 
 * Configuration files are expected to be in the config/ directory with names:
 * - demo.json for demo/sandbox environment
 * - prod.json for production environment
 */
class ConfigManager {
public:
    /**
     * @brief Configuration structure for OKX Data Source
     */
    struct OKXConfig {
        std::string url_pub;        // Public WebSocket URL
        std::string url_private;    // Private WebSocket URL
        std::string API_key;        // API Key
        std::string API_secret;     // API Secret
        std::string API_passphrase; // API Passphrase
    };

    /**
     * @brief Configuration container for all connectors
     */
    struct ConnectorConfig {
        OKXConfig OKXDataSrc;
    };

private:
    nlohmann::json m_config;
    std::string m_mode;
    std::string m_configPath;

public:
    /**
     * @brief Constructor
     * @param mode Configuration mode ("demo" or "prod")
     * @param configPath Path to configuration directory (default: "config/")
     */
    explicit ConfigManager(const std::string& mode = "demo", 
                          const std::string& configPath = "config/");

    /**
     * @brief Load configuration from JSON file
     * @throws std::runtime_error if file cannot be loaded or parsed
     */
    void loadConfig();

    /**
     * @brief Get the current configuration mode
     * @return Current mode ("demo" or "prod")
     */
    const std::string& getMode() const { return m_mode; }

    /**
     * @brief Get OKX configuration
     * @return OKXConfig structure with all OKX settings
     * @throws std::runtime_error if configuration is not loaded or malformed
     */
    OKXConfig getOKXConfig() const;

    /**
     * @brief Get all connector configurations
     * @return ConnectorConfig structure with all connector settings
     * @throws std::runtime_error if configuration is not loaded or malformed
     */
    ConnectorConfig getConnectorConfig() const;

    /**
     * @brief Check if configuration is loaded
     * @return true if configuration is loaded, false otherwise
     */
    bool isLoaded() const { return !m_config.empty(); }

    /**
     * @brief Validate configuration structure
     * @return true if configuration has required fields, false otherwise
     */
    bool validateConfig() const;

    /**
     * @brief Get raw JSON configuration (for debugging)
     * @return Reference to the loaded JSON configuration
     */
    const nlohmann::json& getRawConfig() const { return m_config; }

private:
    /**
     * @brief Construct configuration file path
     * @return Full path to configuration file
     */
    std::string getConfigFilePath() const;

    /**
     * @brief Validate OKX configuration section
     * @param okxSection JSON object containing OKX configuration
     * @return true if valid, false otherwise
     */
    bool validateOKXConfig(const nlohmann::json& okxSection) const;
};

#endif // CONFIG_MANAGER_H 