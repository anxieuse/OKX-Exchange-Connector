# OKX WebSocket Connector 🚀

A high-performance C++ application that demonstrates parallel processing by simultaneously:
- 📡 **Real-time WebSocket connection** to OKX Exchange for BTC-USDT order book data
- 🧮 **Intensive matrix calculations** for solving AX = E equations using Gauss-Jordan elimination

## ✨ Features

- **Low-latency WebSocket streaming** from OKX Exchange API (<100ms)
- **Best-Bid-Offer (BBO) data extraction** for BTC-USDT trading pair
- **Parallel matrix inverse calculations** with configurable matrix size
- **Thread-safe atomic counters** for performance monitoring
- **Modern C++17 implementation** with clean architecture

## 🏗️ Architecture

```
OKX-Exchange-Connector/
├── src/                    # Source files
│   ├── main.cpp           # Application entry point & threading logic
│   ├── WebSocketClass.cpp # OKX WebSocket client implementation
│   └── CalculationClass.cpp # Matrix calculation engine
├── include/               # Header files
│   ├── WebSocketClass.h   # WebSocket client interface
│   └── CalculationClass.h # Matrix calculation interface
├── CMakeLists.txt        # Modern CMake build configuration
├── conanfile.txt        # Dependency management
└── docs/               # Documentation
    └── architecture.md # Detailed technical documentation
```

## 🔧 Dependencies

- **websocketpp**: WebSocket++ library for real-time connectivity
- **nlohmann_json**: Modern JSON parsing and manipulation
- **OpenSSL**: TLS/SSL support for secure connections
- **Boost**: System and threading components
- **libcurl**: HTTP client capabilities

## 🚀 Quick Start

### Prerequisites
```bash
# Install Conan package manager
pip install conan

# Install CMake (3.15 or higher)
sudo apt-get install cmake  # Ubuntu/Debian
```

### Build & Run
```bash
# Clone and navigate
git clone <repository-url>
cd OKX-Exchange-Connector

# Create build directory
mkdir build && cd build

# Install dependencies
conan install .. --output-folder=. --build=missing

# Configure and build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Run the application
./websocket_client
```

## 🎯 Usage

The application runs for 60 seconds by default, displaying:
- Real-time BTC-USDT order book updates
- Matrix calculation progress and results
- Performance metrics for both operations

### Sample Output
```
=====================================================
| ORDER BOOK FOR BTC-USDT AND INVERSE MATRIX AX = E |
=====================================================

WebSocketClass: Timestamp: 2024-01-15 10:30:45.123
WebSocketClass: Asks:
  Depth Price: 42350.5
  Quantity: 0.15
...

CalculationClass: Matrix 1000 by 1000 filled successfully.
CalculationClass: Gauss-Jordan completed.
CalculationClass: L2 Norm ||AX - E|| = 1.234567e-12
CalculationClass: Calculation #0
CalculationClass: Calculation time in seconds: 2.45670

Total WebSocket requests made: 342
Total calculations completed: 12
```

## ⚙️ Configuration

### Matrix Size
Modify the matrix size in `main.cpp`:
```cpp
CalculationClass Calculation(1000);  // Change 1000 to desired size
```

### Runtime Duration
Adjust the execution time:
```cpp
std::this_thread::sleep_for(std::chrono::seconds(60));  // Change 60 to desired seconds
```

### WebSocket Endpoint
The OKX WebSocket endpoint is configured in `main.cpp`:
```cpp
std::string uri = "wss://ws.okx.com:8443/ws/v5/public";
```

## 📊 Performance

- **WebSocket latency**: <100ms for real-time market data
- **Matrix calculations**: Configurable size (default 1000x1000)
- **Memory usage**: Scales with matrix size (~8MB for 1000x1000)
- **Thread safety**: Atomic counters and mutex-protected output

## 🔍 Technical Details

### WebSocket Implementation
- Secure TLS connection to OKX Exchange
- Subscribes to BBO (Best-Bid-Offer) channel for BTC-USDT
- JSON parsing of real-time market data
- Asynchronous message handling

### Matrix Calculations
- Gauss-Jordan elimination for matrix inversion
- Partial pivoting for numerical stability
- Accuracy validation using L2 norm
- Memory-efficient dynamic allocation

### Concurrency
- Two independent threads for WebSocket and calculations
- Atomic variables for thread-safe counting
- Mutex-protected console output
- Graceful shutdown with atomic flags

## 🧪 Testing

The application demonstrates correctness through:
- Real-time data reception verification
- Matrix inversion accuracy validation (L2 norm)
- Thread-safe operation counting
- Performance timing measurements

## 📚 Further Reading

See [`docs/architecture.md`](docs/architecture.md) for detailed technical documentation including:
- Complete API reference
- Method-by-method code analysis
- Threading and synchronization details
- Performance optimization strategies

## 🤝 Contributing

1. Study the architecture documentation
2. Follow the existing code patterns
3. Ensure thread safety in any modifications
4. Test with various matrix sizes
5. Validate WebSocket connectivity

## 📄 License

This project demonstrates educational concepts in parallel processing, WebSocket connectivity, and numerical computation. 