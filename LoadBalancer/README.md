# Load Balancer Simulation

A C++ simulation of a dynamic load balancer with automatic server scaling, firewall protection, and colored console output.

## Features

- Dynamic server scaling (50-80 requests/server thresholds)
- IP blocking with CIDR range support (firewall)
- Colored console output and file logging
- Multiple test configurations
- Time measured in clock cycles (integers)

## Building

### Windows (MSVC)
```cmd
build.bat                # Easy build
clean.bat                # Clean artifacts
```
Or manually:
```cmd
cl /EHsc /W3 /Fe:loadbalancer.exe main.cpp LoadBalancer.cpp Webserver.cpp Request.cpp RequestGenerator.cpp Firewall.cpp Logger.cpp Colors.cpp
```

### Linux/Mac (using makefile)
```bash
make                     # Build
make clean               # Clean
make help                # Show all targets
```

## Running

```bash
.\loadbalancer.exe config.txt              # Windows
./loadbalancer config.txt                  # Linux/Mac
.\loadbalancer.exe configs\minimal.txt     # Run specific config
```

## Configuration Files

Located in `configs/`:
- **config.txt** - Default balanced scenario
- **minimal.txt** - Minimal workload (2 servers)
- **high_load.txt** - Heavy traffic (150 max servers)
- **firewall_test.txt** - CIDR blocking test
- **dos_attack.txt** - DDoS simulation
- Plus 4 more test scenarios

### Example Config
```ini
initialServers=10
maxServers=50
simulationLength=10000
seed=42
requestDelayMin=2
requestDelayMax=6
requestProcessingMin=10
requestProcessingMax=100
queueLowThreshold=50
queueHighThreshold=80
serverAdjustmentDelay=10
blockedIPs=192.168.1.1,10.0.0.0/8
```

## Documentation

Generate HTML documentation:
```bash
doxygen Doxyfile        # Creates docs/html/index.html
make docs              # Linux/Mac alternative
```

## Project Structure

```
LoadBalancer/
├── main.cpp              # Simulation entry point
├── LoadBalancer.h/cpp    # Queue and scaling logic
├── Webserver.h/cpp       # Request processor
├── Request.h/cpp         # Data structures
├── RequestGenerator.h/cpp # Random request generation
├── Firewall.h/cpp        # IP/CIDR blocking
├── Logger.h/cpp          # File logging
├── Colors.h/cpp          # Colored console output
├── build.bat             # Windows build script
├── clean.bat             # Windows clean script
├── Makefile              # Linux/Mac build
└── configs/              # Test scenarios
```

## How It Works

- **Clock Cycles**: All time values are integers (not floats)
- **Scaling**: Adds servers when `queue > 80 × servers`, removes when `queue < 50 × servers`
- **Firewall**: Blocks exact IPs (`192.168.1.1`) or CIDR ranges (`10.0.0.0/8`)
- **Random Requests**: Seeded RNG generates IPs (0.0.0.0-255.255.255.255) and processing times

## Output

**Console Colors:**
- Cyan: Configuration info
- Green: Server added
- Red: Server removed
- Yellow: Status updates
- Magenta: Final summary

**Log File (`simulation.txt`):**
- Timestamps
- Scaling events (cycle, server count, queue size)
- Summary (total cycles, servers, queue, blocked requests)
