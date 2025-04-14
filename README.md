# Crux - A High-Performance Command Line Tool

**Crux** is a lightweight, high-performance command line tool designed to provide users with powerful utilities while keeping it simple, efficient, and fast. Crux is designed to be easily extensible and ideal for users looking for a fast and flexible command-line solution.

## Features

- **Fast**: Optimized for speed and performance.
- **Modular**: Designed with modularity in mind, so you can extend or modify functionality easily.
- **Cross-Platform**: Runs on Linux and WSL on Windows.
- **Customizable**: Easily modify behavior through configuration or by adding custom modules.
- **Package Management**: Install and update easily via package managers like APT.

## Installation

### Option 1: Build from Source

If you prefer to build Crux from source, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/crux.git
   cd crux
   ```

2. Build the project:

   ```bash
   make
   ```

3. Install Crux:

   ```bash
   sudo make install
   ```

### Option 2: Install via .deb Package

If you have a `.deb` package, you can install it manually:

```bash
sudo dpkg -i crux.deb
sudo apt-get install -f  # To fix missing dependencies
```

## Usage

Once installed, you can use the Crux command-line tool to access its features. Here's how you can use it:

```bash
crux <command> [options]
```

### Common Commands
Usage: crux <command> [options]

Commands:
  - uptimewatch     :     Show system uptime
  - sysmon     :     Monitor system resources
  - procstat   :     Display process statistics
  - procpeek   :     Peek into process details
  - pingspy    :     Monitor network connectivity with ping
  - netspy     :     Monitor network activity
  - logspy     :     Watch system logs in real time
  - fswatch    :     Monitor filesystem changes
  - diskspy    :     Monitor disk usage and status
  - cpuheat    :     Monitor CPU temperature
  - cmdspy      :    Spy on system commands

For more details on each command, use:
  crux <command> help


## Uninstallation

To remove Crux from your system, use the following command:

```bash
sudo apt remove crux
```

Or if you installed via `.deb` package:

```bash
sudo dpkg -r crux
```

## Contributing

We welcome contributions to Crux! If you'd like to contribute, please fork the repository and submit a pull request with your changes. Here's how you can contribute:

1. Fork the repository on GitHub.
2. Create a new branch.
3. Make your changes.
4. Commit and push your changes.
5. Create a pull request.

Please make sure your code adheres to the existing style and includes tests if applicable.

## License

Crux is open-source and released under the [MIT License](LICENSE).

## Acknowledgments

- Thanks to all contributors who make Crux better every day.
- Special thanks to the communities and libraries that helped Crux become what it is today.
