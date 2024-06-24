# Airport Management System

The Airport Management System is a C++ application designed to efficiently manage flights, passengers, and luggage using advanced data structures. This system utilizes linked lists, circular lists, stacks, and queues to handle various operations and processes within an airport setting.

## Features

- **Dynamic Memory Management:** Proper use of pointers and dynamic memory allocation in C++.
- **Data Structures:** Implementation of linear data structures to handle different airport operations.
- **Graphviz Integration:** Visualization of data structures through generated reports.
- **JSON Parsing:** Reading input data for airplanes and passengers from JSON files.

## Installation

### Prerequisites

- C++ compiler (g++ recommended)
- Graphviz
- Make

### Windows

1. Install [MinGW](https://sourceforge.net/projects/mingw/) and ensure `mingw32-gcc-g++` is selected.
2. Add `C:\MinGW\bin` to your system PATH.
3. Install [Graphviz](https://graphviz.org/download/).

### Linux (Ubuntu)

```sh
sudo apt-get update
sudo apt-get install g++
sudo apt-get install graphviz
```

### macOS

1. Install Xcode from the App Store.
2. Install the Xcode command line tools:

```sh
xcode-select --install
```
3. Install Graphviz using Homebrew:

```sh
brew install graphviz
```

## Usage

1. Clone the repository:

```sh
git clone https://github.com/DominicRuano/202200075_EDD_Practica.git
cd ..../202200075_EDD_Practica
```

2. Build the project:

```sh
c++ .\main.cpp -o .\main
```

3. Run the application:

```sh
.\main.exe
```

4. Load input files (JSON format) for airplanes and passengers through the application menu.

## Input File Format

### Airplanes

The airplanes' information should be provided in a JSON file with the following format:

```json
[
    {
        "vuelo": "A100",
        "numero_de_registro": "N12345",
        "modelo": "Boeing 737",
        "fabricante": "Boeing",
        "ano_fabricacion": 2015,
        "capacidad": 180,
        "peso_max_despegue": 79000,
        "aerolinea": "Airlinex",
        "estado": "Mantenimiento"
    },
    {
        "vuelo": "A102",
        "numero_de_registro": "A54321",
        "modelo": "Airbus A320",
        "fabricante": "Airbus",
        "ano_fabricacion": 2018,
        "capacidad": 150,
        "peso_max_despegue": 77000,
        "aerolinea": "Airlinex",
        "estado": "Mantenimiento"
    }
]
```

### Passengers

The passengers' information should be provided in a JSON file with the following format:

```json
[
    {
        "nombre": "John Doe",
        "nacionalidad": "Estados Unidos",
        "numero_de_pasaporte": "A12345678",
        "vuelo": "A100",
        "asiento": 10,
        "destino": "New York",
        "origen": "Los Angeles",
        "equipaje_facturado": 2
    },
    {
        "nombre": "Jane Smith",
        "nacionalidad": "Reino Unido",
        "numero_de_pasaporte": "B98765432",
        "vuelo": "A200",
        "asiento": 1,
        "destino": "Londres",
        "origen": "Paris",
        "equipaje_facturado": 0
    }
]
```

## Report Generation

Reports are generated using Graphviz and can be accessed through the application menu. Ensure Graphviz is properly installed and added to your system PATH.

## Contributing

Contributions are welcome! Please fork this repository and submit a pull request for any improvements or bug fixes.