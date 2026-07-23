# 📦 File Compression Utility using Huffman Coding

A **File Compression Utility** developed in **C++** that uses the **Huffman Coding** algorithm to compress and decompress text files without losing any data. The project demonstrates the implementation of data structures such as **Binary Trees**, **Priority Queues (Min Heaps)**, and **Maps**, along with efficient file handling..

---

## 📖 Overview

This project implements **lossless file compression** using Huffman Coding. The application reads a text file, calculates the frequency of each character, constructs a Huffman Tree, generates unique binary codes, compresses the file into a binary format, and later restores it to its original form through decompression.

---

## ✨ Features

* 📄 Read input text files
* 📊 Calculate character frequencies
* 🌳 Construct Huffman Tree
* 🔢 Generate Huffman Codes
* 📦 Compress files into binary format
* 🔓 Decompress files back to the original content
* ⚡ Efficient file handling
* 📈 Display compression statistics
* 💻 Command Line Interface (CLI)

---

## 🛠️ Technologies Used

* **Language:** C++
* **Compiler:** GCC / G++
* **IDE:** Visual Studio Code
* **Version Control:** Git & GitHub

---

## 📂 Project Structure

```text
FileCompressor/
│
├── main.cpp
├── huffman.cpp
├── huffman.h
├── input.txt
├── compressed.bin
├── output.txt
├── README.md
└── Makefile (Optional)
```

---

## 🧠 Algorithm Used

### Huffman Coding

Huffman Coding is a **lossless data compression algorithm** that assigns shorter binary codes to frequently occurring characters and longer codes to less frequent characters.

### Workflow

```text
Input File
     │
     ▼
Read Characters
     │
     ▼
Count Frequency
     │
     ▼
Build Huffman Tree
     │
     ▼
Generate Huffman Codes
     │
     ▼
Compress File
     │
     ▼
Save Binary File
     │
     ▼
Read Binary File
     │
     ▼
Rebuild Huffman Tree
     │
     ▼
Decode Data
     │
     ▼
Restore Original File
```

---

## 📚 Data Structures Used

* Map (`std::map`)
* Priority Queue (`std::priority_queue`)
* Binary Tree
* Strings
* File Streams (`ifstream`, `ofstream`)

---

## 🚀 Getting Started

### Prerequisites

* C++ Compiler (GCC/G++)
* Visual Studio Code (or any C++ IDE)
* Git (Optional)

### Clone the Repository

```bash
git clone https://github.com/your-username/FileCompressor.git
cd FileCompressor
```

### Compile

```bash
g++ main.cpp huffman.cpp -o compressor
```

### Run

```bash
./compressor
```

On Windows:

```bash
compressor.exe
```

---

## 📌 How It Works

1. Read the input file.
2. Count the frequency of each character.
3. Build the Huffman Tree using a Min Heap.
4. Generate unique Huffman codes.
5. Encode the original data.
6. Save the compressed data to a binary file.
7. Read the compressed file during decompression.
8. Decode the binary data using the Huffman Tree.
9. Restore the original file.

---

## 📊 Example

### Input

```text
HELLO HUFFMAN
```

### Frequency Table

```text
H : 2
E : 1
L : 2
O : 1
F : 2
M : 1
A : 1
N : 1
Space : 1
U : 1
```

### Output

* `compressed.bin`
* `output.txt` (matches the original input)

---

## 📈 Future Enhancements

* Support binary files
* Compress multiple files
* Folder compression
* Archive format support
* Password-protected archives
* Encryption (AES)
* Cross-platform compatibility
* Graphical User Interface (GUI)
* Performance benchmarking
* Multi-threaded compression

---

## 🎯 Learning Outcomes

Through this project, you will gain practical experience with:

* File Handling in C++
* Huffman Coding Algorithm
* Binary Trees
* Priority Queues (Min Heap)
* Maps (Frequency Counting)
* Binary File Operations
* Dynamic Memory Allocation
* Command-Line Application Development
* Algorithm Optimization
* Git and GitHub Workflow

---

## 👨‍💻 Author

**Shivram Parkhi** AND **Ishaan Jog**

Computer Engineering Student

If you found this project helpful, consider giving it a ⭐ on GitHub.