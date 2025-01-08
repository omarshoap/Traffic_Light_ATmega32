# Traffic_Light_ATmega32

---

# **Traffic Light Control System with Pedestrian Crossing Feature (FSM-Based)**

## **Project Overview**

This project implements a traffic light control system for a four-way intersection, integrating a pedestrian crossing mechanism. The system is designed to optimize vehicle traffic management while ensuring pedestrian safety using a state-machine-based design. Key highlights include:
- **State machine implementation** for efficient light sequencing.
- **Interrupt-driven pedestrian mode**, activated via external buttons.
- Alternating traffic flow between **North-South (NS)** and **East-West (EW)** directions.

---

## **Features**

1. **Traffic Light State Management**:
   - Standard traffic light sequences for NS and EW directions.
   - Safety intervals during transitions (e.g., Yellow phase).

2. **Pedestrian Mode**:
   - Activates pedestrian crossing signals dynamically.
   - Adjusts traffic sequences to ensure safe pedestrian crossing.

3. **Interrupt-Driven Design**:
   - pedestrian mode activation via external interrupts (INT0 and INT1).

4. **Fail-Safe Mechanism**:
   - Automatically switches to a default safe state during unexpected errors.

---

## **Hardware Requirements**

- **Microcontroller**: AVR ATmega32 operating at 8 MHz.
- **Traffic Lights**: LEDs for Red, Yellow, and Green signals.
- **Pedestrian Signals**: LEDs for pedestrian crossings.
- **Pedestrian Buttons**: Push-buttons to trigger pedestrian mode.
- **Power Supply**: 5V DC.

---

## **Software Details**

- **Programming Language**: C
- **Development Environment**: ECLIPSE, AVR-GCC, PROTEUS
- **Key Libraries**:
  - `<util/delay.h>` for delay handling.
  - `<avr/interrupt.h>` for interrupt management.

---

## **Functional Description**

### **Traffic Light State Machine**

The system operates as follows:
1. **NS Green, EW Red**: North-South traffic moves; East-West is stopped.
2. **NS Yellow, EW Red**: North-South prepares to stop.
3. **NS Red, EW Green**: East-West traffic moves; North-South is stopped.
4. **NS Red, EW Yellow**: East-West prepares to stop.
5. The sequence repeats.

### **Pedestrian Mode**

When activated:
- Normal traffic light sequencing is interrupted.
- Traffic lights adjust dynamically for pedestrian safety.
- Pedestrian green signals activate, allowing safe crossing.
- Normal traffic resumes after pedestrian crossing.

![state machine](https://github.com/user-attachments/assets/cb638393-f2d0-4149-bb1c-73255f667e62)

---

## **Files and Functions**

### **Key Source Files**
1. `main.c`: Contains the main logic, including FSM traffic and pedestrian management.
2. `DIO.h`: Digital I/O abstractions for easy microcontroller pin manipulation.

### **Functions Overview**

#### Traffic Light Management
- `NS_GREEN_EW_RED()`: Manages NS green, EW red state.
- `NS_YELLOW_EW_RED()`: Manages NS yellow, EW red state.
- `NS_RED_EW_GREEN()`: Manages NS red, EW green state.
- `NS_RED_EW_YELLOW()`: Manages NS red, EW yellow state.

#### Pedestrian Management
- `PedestrianSignal()`: Activates pedestrian signals.
- `Ped_Button_Init()`: Configures buttons and enables interrupts.

#### Initialization
- `TrafficLight_Init()`: Initializes traffic light pins.
- `Ped_Button_Init()`: Sets up pedestrian button pins and external interrupts.

---

## **Hardware Connections**

![image](https://github.com/user-attachments/assets/d9a3a9ae-cdb9-458c-9003-e5625790acd0)


| **Component**              | **MCU Port** | **Pin** | **Description**                     |
|----------------------------|--------------|---------|-------------------------------------|
| NS Green Light             | PORTB        | PIN0    | North-South green traffic signal    |
| NS Yellow Light            | PORTB        | PIN1    | North-South yellow traffic signal   |
| NS Red Light               | PORTB        | PIN2    | North-South red traffic signal      |
| EW Green Light             | PORTB        | PIN3    | East-West green traffic signal      |
| EW Yellow Light            | PORTB        | PIN4    | East-West yellow traffic signal     |
| EW Red Light               | PORTB        | PIN5    | East-West red traffic signal        |
| Pedestrian Green Signal 1  | PORTC        | PIN2    | Pedestrian crossing signal 1 (green)|
| Pedestrian Green Signal 2  | PORTC        | PIN3    | Pedestrian crossing signal 2 (green)|
| Pedestrian Button 1        | PORTD        | PIN2    | Pedestrian button 1 for crossing    |
| Pedestrian Button 2        | PORTD        | PIN3    | Pedestrian button 2 for crossing    |

---

## **Usage Instructions**

1. **Setup**:
   - Connect LEDs and buttons to microcontroller pins based on the hardware connection table.

2. **Compile and Flash**:
   - Use an AVR-compatible programmer to upload the compiled firmware to the ATmega32.

3. **Operation**:
   - Normal operation starts with alternating NS and EW traffic.
   - Activate pedestrian mode by pressing the pedestrian button.

---

## **Project Workflow**

1. **Initialization**:
   - Configures pins for traffic lights and buttons.
   - Enables external and global interrupts.

2. **State Machine Execution**:
   - Cycles through the traffic light sequence continuously.
   - Switches to pedestrian mode upon button press.

3. **Error Handling**:
   - Defaults to a safe state during unexpected events.



## **Folder Structure**

```
TrafficLightProject/
├── README.md
├── StateDiagram.png
├── HardwareDiagram.png
├── DesignDocument
├── TestingDocument
├── SourceCode/
│   ├── main.c
│   └── (Other necessary files)
└── DemoVideo.mp4 
```

---

