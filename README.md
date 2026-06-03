# system-programming-lab

A collection of Linux system programming experiments written in C.

This repository contains small low-level projects created for learning and practicing concepts such as:

- process creation and control
- system call tracing
- process memory inspection
- socket programming
- event-driven server design
- Linux-specific system interfaces

## Projects

### 1. process-monitor
A basic process monitoring experiment using Linux system programming APIs such as `fork()`, `execvp()`, `wait()`, and `ptrace()`.

**Topics explored:**
- creating child processes
- tracing system calls
- observing process execution
- understanding low-level debugging and monitoring concepts

### 2. visual-memory-scanner
A simple memory inspection tool that reads `/proc/<pid>/maps` and prints executable memory regions for a given process.

**Topics explored:**
- Linux `/proc` filesystem
- process memory layout
- executable memory regions
- parsing memory map information

### 3. mini-nginx
A lightweight experimental HTTP server prototype inspired by event-driven server architecture.

**Topics explored:**
- sockets
- non-blocking I/O
- epoll
- file descriptors
- basic HTTP handling
- static file serving design

> Note: this project is currently a study prototype and not a complete production-ready web server.

## Purpose

This repository is intended for:

- practicing Linux system programming in C
- understanding low-level operating system concepts
- experimenting with process, memory, and networking internals
- building small educational prototypes

## Technologies

- C
- Linux system calls
- POSIX APIs
- `/proc` filesystem
- sockets and epoll

## Notes

These projects are primarily educational and experimental. Some parts are incomplete by design and are kept as learning exercises rather than finished tools.
