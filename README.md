# 🍽️ Philosophers

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr/)
[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Threading](https://img.shields.io/badge/Threading-pthreads-green.svg)](https://en.wikipedia.org/wiki/POSIX_Threads)

## 📋 Descripción

**Philosophers** es una implementación del clásico problema de **los filósofos comensales** de Edsger Dijkstra. Este proyecto forma parte del curriculum de **42 Málaga** y tiene como objetivo enseñar conceptos fundamentales de programación concurrente, sincronización de hilos y prevención de deadlocks.

### El Problema de los Filósofos Comensales

Varios filósofos están sentados alrededor de una mesa circular. Entre cada par de filósofos hay exactamente un tenedor. Para comer, un filósofo debe tomar ambos tenedores adyacentes (izquierdo y derecho). El desafío consiste en diseñar un algoritmo que evite:
- **Deadlock**: Todos los filósofos toman su tenedor izquierdo simultáneamente
- **Starvation**: Un filósofo nunca puede comer
- **Race conditions**: Acceso no sincronizado a recursos compartidos

## 🛠️ Compilación

```bash
# Compilar la versión principal
cd philo
make

# Compilar la versión bonus (con semáforos)
cd philo_bonus
make

# Limpiar archivos objeto
make clean

# Limpiar todo
make fclean

# Re-compilar completamente
make re
```

## 🚀 Uso

### Versión Principal (Threads + Mutex)
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parámetros
- **number_of_philosophers**: Número de filósofos y tenedores (≥ 1)
- **time_to_die**: Tiempo máximo sin comer antes de morir (ms)
- **time_to_eat**: Tiempo que tarda un filósofo en comer (ms)
- **time_to_sleep**: Tiempo que tarda un filósofo en dormir (ms)
- **[number_of_times_each_philosopher_must_eat]**: (Opcional) Número de comidas requeridas por filósofo

### Ejemplos de Uso

```bash
# 4 filósofos, mueren en 410ms, comen en 200ms, duermen en 200ms
./philo 4 410 200 200

# 5 filósofos con 3 comidas obligatorias cada uno
./philo 5 800 200 200 3

# Caso extremo: 1 filósofo (debería morir)
./philo 1 800 200 200

# Test de rendimiento: muchos filósofos
./philo 200 410 200 200
```

## 🎨 Salida del Programa

El programa muestra las acciones de cada filósofo en tiempo real con colores:
```
[timestamp] [philosopher_id] [action]
```

### Acciones
- 🟢 **Verde**: `has taken a fork`
- 🟡 **Amarillo**: `is eating`
- 🟣 **Magenta**: `is sleeping`
- 🔵 **Azul**: `is thinking`
- 🔴 **Rojo**: `died`

## 🏗️ Arquitectura

### Estructuras Principales

```c
typedef struct s_table {
    pthread_mutex_t table;          // Mutex principal
    pthread_t control;              // Hilo controlador
    t_philo *arr_p;                 // Array de filósofos
    long n_philo;                   // Número de filósofos
    long die_to_time;               // Tiempo para morir
    long eat_to_time;               // Tiempo para comer
    long sleep_to_time;             // Tiempo para dormir
    int is_dead;                    // Flag de muerte
    // ... más campos
} t_table;

typedef struct s_philo {
    pthread_mutex_t l_fork;         // Tenedor izquierdo
    pthread_mutex_t *r_fork;        // Tenedor derecho
    pthread_t thread;               // Hilo del filósofo
    t_table *t;                     // Referencia a la mesa
    long last_eat;                  // Último tiempo de comida
    int index;                      // ID del filósofo
    int meals;                      // Comidas realizadas
} t_philo;
```

## 🔄 Algoritmo de Sincronización

### Prevención de Deadlock
1. **Offset temporal**: Los filósofos pares esperan 1ms antes de empezar
2. **Orden de toma**: Siempre tenedor izquierdo primero, luego derecho
3. **Liberación atómica**: Ambos tenedores se liberan simultáneamente

### Rutina del Filósofo
```
BUCLE INFINITO:
├── Tomar tenedor izquierdo 🍴
├── Tomar tenedor derecho 🍴
├── Comer 🍝 (actualizar último tiempo de comida)
├── Liberar ambos tenedores
├── Dormir 😴
├── Pensar 🤔
└── Verificar condiciones de finalización
```

### Hilo Controlador
- Monitorea continuamente el estado de todos los filósofos
- Detecta si algún filósofo ha muerto de hambre
- Verifica si todos han completado las comidas requeridas

## 📁 Estructura del Proyecto

```
Philosopher_/
├── philo/                          # Versión principal (threads + mutex)
│   ├── include/
│   │   └── philo.h                 # Headers y definiciones
│   ├── src/
│   │   ├── philo.c                 # Función main e inicialización
│   │   ├── utils_simulator.c       # Lógica del simulador
│   │   ├── utils_rutine.c          # Rutinas de los filósofos
│   │   ├── utils_phtreads.c        # Manejo de hilos
│   │   ├── utils_philo.c           # Utilidades generales
│   │   ├── utils_extras.c          # Funciones auxiliares
│   │   └── leaks.c                 # Gestión de memoria
│   ├── obj/                        # Archivos objeto
│   ├── Makefile                    # Compilación
│   └── esquema.excalidraw          # Diagrama del algoritmo
└── philo_bonus/                    # Versión bonus (procesos + semáforos)
    └── ...
```

## 🧪 Testing

### Tests Básicos
```bash
# Test básico de funcionamiento
./philo 4 410 200 200

# Test sin muertes
./philo 4 800 200 200

# Test con comidas limitadas
./philo 5 800 200 200 7
```

### Tests de Edge Cases
```bash
# Un solo filósofo (debe morir)
./philo 1 800 200 200

# Tiempos muy ajustados
./philo 4 310 200 100

# Muchos filósofos
./philo 200 410 200 200
```

### Herramientas de Debug
```bash
# Verificar memory leaks
valgrind --tool=memcheck --leak-check=full ./philo 4 410 200 200

# Detectar race conditions
valgrind --tool=helgrind ./philo 4 410 200 200

# Profiling de rendimiento
valgrind --tool=callgrind ./philo 4 410 200 200
```

## 🎯 Objetivos de Aprendizaje

- **Programación concurrente** con pthreads
- **Sincronización** usando mutex
- **Prevención de deadlocks** y race conditions
- **Gestión de memoria** en entornos multi-hilo
- **Timing preciso** con `gettimeofday()`
- **Algoritmos de scheduling** y fairness

## 📊 Casos de Uso Típicos

| Filósofos | Tiempo Muerte | Come | Duerme | Resultado Esperado |
|-----------|---------------|------|--------|--------------------|
| 1         | 800           | 200  | 200    | Muerte inmediata   |
| 2         | 800           | 200  | 200    | Simulación infinita |
| 4         | 410           | 200  | 200    | Simulación estable |
| 5         | 800           | 200  | 200    | Simulación estable |
| 4         | 310           | 200  | 100    | Muerte por timing  |

## 🚨 Condiciones de Finalización

1. **Muerte por hambre**: Un filósofo no come a tiempo
2. **Comidas completadas**: Todos han comido el número requerido
3. **Error crítico**: Fallo en el sistema de hilos

## 👨‍💻 Autor

**Rubén Delicado** - [@rdelicado](https://github.com/rdelicado)
- 📧 rdelicad@student.42.com
- 🏫 42 Málaga
- 📅 Septiembre 2023

## 📜 Licencia

Este proyecto es parte del curriculum de 42 School y está destinado únicamente para fines educativos.

## 🎓 42 School

Este proyecto forma parte del **Common Core** de 42 School, específicamente del módulo de **programación concurrente**. El objetivo es dominar conceptos fundamentales de sistemas operativos y programación paralela.

### Recursos Adicionales
- [Documentación oficial de pthreads](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [El problema original de Dijkstra](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Norma de 42](https://github.com/42School/norminette)

---

*"In computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them."* - Edsger Dijkstra
