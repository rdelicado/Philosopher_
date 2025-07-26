# 🍽️ Philosophers

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr/)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Threading](https://img.shields.io/badge/Threading-pthreads-green.svg)](https://en.wikipedia.org/wiki/POSIX_Threads)

## 📋 Description

**Philosophers** is an implementation of the classic **Dining Philosophers Problem** by Edsger Dijkstra. This project is part of the **42 Málaga** curriculum and aims to teach fundamental concepts of concurrent programming, thread synchronization, and deadlock prevention.

### The Dining Philosophers Problem

Several philosophers are sitting around a circular table. Between each pair of philosophers, there is exactly one fork. To eat, a philosopher must take both adjacent forks (left and right). The challenge is to design an algorithm that avoids:
- **Deadlock**: All philosophers take their left fork simultaneously
- **Starvation**: A philosopher never gets to eat
- **Race conditions**: Unsynchronized access to shared resources

## 🛠️ Compilation

```bash
# Compile main version
cd philo
make

# Compile bonus version (with semaphores)
cd philo_bonus
make

# Clean object files
make clean

# Clean everything
make fclean

# Re-compile completely
make re
```

## 🚀 Usage

### Main Version (Threads + Mutex)
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters
- **number_of_philosophers**: Number of philosophers and forks (≥ 1)
- **time_to_die**: Maximum time without eating before dying (ms)
- **time_to_eat**: Time it takes for a philosopher to eat (ms)
- **time_to_sleep**: Time it takes for a philosopher to sleep (ms)
- **[number_of_times_each_philosopher_must_eat]**: (Optional) Number of meals required per philosopher

### Usage Examples

```bash
# 4 philosophers, die in 410ms, eat in 200ms, sleep in 200ms
./philo 4 410 200 200

# 5 philosophers with 3 mandatory meals each
./philo 5 800 200 200 3

# Edge case: 1 philosopher (should die)
./philo 1 800 200 200

# Performance test: many philosophers
./philo 200 410 200 200
```

## 🎨 Program Output

The program shows each philosopher's actions in real-time with colors:
```
[timestamp] [philosopher_id] [action]
```

### Actions
- 🟢 **Green**: `has taken a fork`
- 🟡 **Yellow**: `is eating`
- 🟣 **Magenta**: `is sleeping`
- 🔵 **Blue**: `is thinking`
- 🔴 **Red**: `died`

## 🏗️ Architecture

### Main Structures

```c
typedef struct s_table {
    pthread_mutex_t table;          // Main mutex
    pthread_t control;              // Controller thread
    t_philo *arr_p;                 // Array of philosophers
    long n_philo;                   // Number of philosophers
    long die_to_time;               // Time to die
    long eat_to_time;               // Time to eat
    long sleep_to_time;             // Time to sleep
    int is_dead;                    // Death flag
    // ... more fields
} t_table;

typedef struct s_philo {
    pthread_mutex_t l_fork;         // Left fork
    pthread_mutex_t *r_fork;        // Right fork
    pthread_t thread;               // Philosopher thread
    t_table *t;                     // Reference to table
    long last_eat;                  // Last eating time
    int index;                      // Philosopher ID
    int meals;                      // Meals completed
} t_philo;
```

## 🔄 Synchronization Algorithm

### Deadlock Prevention
1. **Time offset**: Even philosophers wait 1ms before starting
2. **Taking order**: Always left fork first, then right
3. **Atomic release**: Both forks are released simultaneously

### Philosopher Routine
```
INFINITE LOOP:
├── Take left fork 🍴
├── Take right fork 🍴
├── Eat 🍝 (update last eating time)
├── Release both forks
├── Sleep 😴
├── Think 🤔
└── Check termination conditions
```

### Controller Thread
- Continuously monitors the state of all philosophers
- Detects if any philosopher has died of starvation
- Verifies if all have completed the required meals

## 📁 Project Structure

```
Philosopher_/
├── philo/                          # Main version (threads + mutex)
│   ├── include/
│   │   └── philo.h                 # Headers and definitions
│   ├── src/
│   │   ├── philo.c                 # Main function and initialization
│   │   ├── utils_simulator.c       # Simulator logic
│   │   ├── utils_rutine.c          # Philosopher routines
│   │   ├── utils_phtreads.c        # Thread management
│   │   ├── utils_philo.c           # General utilities
│   │   ├── utils_extras.c          # Auxiliary functions
│   │   └── leaks.c                 # Memory management
│   ├── obj/                        # Object files
│   ├── Makefile                    # Compilation
│   └── esquema.excalidraw          # Algorithm diagram
└── philo_bonus/                    # Bonus version (processes + semaphores)
    └── ...
```

## 🧪 Testing

### Basic Tests
```bash
# Basic functionality test
./philo 4 410 200 200

# Test without deaths
./philo 4 800 200 200

# Test with limited meals
./philo 5 800 200 200 7
```

### Edge Case Tests
```bash
# Single philosopher (should die)
./philo 1 800 200 200

# Very tight timing
./philo 4 310 200 100

# Many philosophers
./philo 200 410 200 200
```

### Debug Tools
```bash
# Check memory leaks
valgrind --tool=memcheck --leak-check=full ./philo 4 410 200 200

# Detect race conditions
valgrind --tool=helgrind ./philo 4 410 200 200

# Performance profiling
valgrind --tool=callgrind ./philo 4 410 200 200
```

## 🎯 Learning Objectives

- **Concurrent programming** with pthreads
- **Synchronization** using mutex
- **Prevention of deadlocks** and race conditions
- **Memory management** in multi-threaded environments
- **Precise timing** with `gettimeofday()`
- **Scheduling algorithms** and fairness

## 📊 Typical Use Cases

| Philosophers | Death Time | Eat | Sleep | Expected Result |
|--------------|------------|-----|-------|-----------------|
| 1            | 800        | 200 | 200   | Immediate death |
| 2            | 800        | 200 | 200   | Infinite simulation |
| 4            | 410        | 200 | 200   | Stable simulation |
| 5            | 800        | 200 | 200   | Stable simulation |
| 4            | 310        | 200 | 100   | Death by timing |

## 🚨 Termination Conditions

1. **Death by starvation**: A philosopher doesn't eat in time
2. **Meals completed**: All have eaten the required number
3. **Critical error**: Failure in thread system

## 👨‍💻 Author

**Rubén Delicado** - [@rdelicado](https://github.com/rdelicado)
- 📧 rdelicad@student.42.com
- 🏫 42 Málaga
- 📅 September 2023

## 📜 License

This project is part of the 42 School curriculum and is intended for educational purposes only.

## 🎓 42 School

This project is part of the **Common Core** of 42 School, specifically the **concurrent programming** module. The goal is to master fundamental concepts of operating systems and parallel programming.

### Additional Resources
- [Official pthreads documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Dijkstra's original problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [42 Norm](https://github.com/42School/norminette)

---

*"In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them."* - Edsger Dijkstra
