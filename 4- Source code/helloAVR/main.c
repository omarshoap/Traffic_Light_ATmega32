
/*******************************************************************************
 * Traffic Light Controller with Pedestrian Crossing
 *
 * MCU: AVR ATmega32 @ 8MHz
 * Purpose: Controls intersection traffic lights with pedestrian crossing support
 * Features:
 * - state machine implementation
 * - Interrupt-driven pedestrian crossing
 * - Four-way traffic light control (NS/EW)
 * Author: [Omar A. Shoaib]
 * Date: January 7, 2025
 ******************************************************************************/

#define F_CPU 8000000UL  // CPU clock frequency

/* Include Files */
#include "DIO.h"
#include <util/delay.h>
#include <avr/interrupt.h>

/* Timing Constants (all values in milliseconds) */
#define GREEN_TIME 3000        // Duration for green light state
#define YELLOW_TIME 1000       // Duration for yellow light state
#define RED_RED_ALL_TIME 100   // All-red safety interval
#define OFF_OFF_ALL_TIME 500   // All-off interval
#define PED_CROSS_TIME 3000    // Pedestrian crossing duration

/* Traffic Light States
 * NS: North-South direction
 * EW: East-West direction */
typedef enum {
	NS_Green_EW_Red,    // NS has green, EW has red
	NS_Yellow_EW_Red,   // NS transitioning to red
	NS_Red_EW_Green,    // EW has green, NS has red
	NS_Red_EW_Yellow    // EW transitioning to red
} TrafficState_t;

/* Global Variables */
volatile uint8_t pedestrianModeActive;  // Flag for active pedestrian crossing

/* Function Prototypes */
void long_delay(uint16_t time_ms);          // Non-blocking delay function
void TrafficLight_Init(void);               // Initialize traffic light pins
void NS_GREEN_EW_RED(void);                 // Handle NS green state
void NS_YELLOW_EW_RED(void);                // Handle NS yellow state
void NS_RED_EW_GREEN(void);                 // Handle EW green state
void NS_RED_EW_YELLOW(void);                // Handle EW yellow state
void PedestrianSignal(void);                // Control pedestrian signals
void Ped_Button_Init(void);                 // Initialize pedestrian button
void NS_RED_EW_RED(void);                   // All-red safety state

int main() {
	// Initialize all pins for traffic lights
	TrafficLight_Init();
	Ped_Button_Init();
	// vars definitions
	TrafficState_t currentState = NS_Green_EW_Red;
	pedestrianModeActive = 0; // Flag for pedestrian mode

	/*************************************
	 ***** Pedestrian Mode Sequence *****
	 **************************************
	 // This section outlines the traffic light system's response when pedestrian mode is activated.
	 // The system adapts based on the current state of the traffic light normal Mode to ensure pedestrian safety and smooth traffic flow
	 // Pedestrian Mode Sequence:
	 // - When pedestrian mode is activated, the traffic lights adjust their sequence based on whether the light is red, yellow, or green.
	 // - The following table indicate the pedestrian signal behavior during each traffic light state:
	 // |  Traffic Light State |   Pedestrian Mode Sequence                                                                            |
	 // |----------------------|-------------------------------------------------------------------------------------------------------|
	 // | NS -> Red            | Red light completes, pedestrian signal turns green immediately, then normal traffic cycle resumes.    |
	 // | NS -> Yellow         | Yellow light completes, then traffic light turns red, pedestrian signal turns green, cycle resumes.   |
	 // | NS -> Green          | Traffic light transitions to yellow, then red, pedestrian signal turns green, cycle resumes.          |
	 */

	while (1) {

		if (pedestrianModeActive == 1) {
			switch (currentState) {
			case NS_Green_EW_Red: // PED_STATE_1
				// we came here as [NS_Red_EW_Yellow()] = Step 4 [in normal mode] finished, which bring us here ,
				// so [NS_Green_EW_Red()] need to be executed but as we in PED mode we ignore the green part in
				// NS_Green_EW_Red by making it RED_RED transition to red All for pedestrian mode
				NS_RED_EW_RED(); // Set red for all directions
				PedestrianSignal(); // Activate pedestrian signal
				pedestrianModeActive = 0; // Reset pedestrian mode flag
				currentState = NS_Green_EW_Red;
				break;
			case NS_Yellow_EW_Red: // PED_STATE_2
				// we came here as [NS_Green_EW_Red()] = Step 1 [in normal mode] finished, which bring us here ,
				// so [NS_Yellow_EW_Red()] need to be excuted > and this comply with the adaption concept for ped mode pattern transition
				NS_YELLOW_EW_RED();
				NS_RED_EW_RED();
				PedestrianSignal();
				pedestrianModeActive = 0;
				currentState = NS_Red_EW_Green;
				break;
			case NS_Red_EW_Green: // PED_STATE_3
				// we came here as [NS_Yellow_EW_Red()] = Step 2 [in normal mode] finished, which bring us here ,
				// so [NS_Red_EW_Green()] need to be excuted but as we in PED mode we ignore the green part in
				// NS_Red_EW_Green by making it RED_RED transition to red All for pedestrian mode
				NS_RED_EW_RED();
				PedestrianSignal();
				pedestrianModeActive = 0;
				currentState = NS_Red_EW_Green;
				break;
			case NS_Red_EW_Yellow: // PED_STATE_4
				// we came here as [NS_Red_EW_Green()] = Step 3 [in normal mode] finished, which bring us here ,
				// so [NS_RED_EW_YELLOW()] need to be excuted > and this comply with the adaption concept for ped mode pattern transition
				NS_RED_EW_YELLOW();
				NS_RED_EW_RED();
				PedestrianSignal();
				pedestrianModeActive = 0;
				currentState = NS_Green_EW_Red;
				break;

			}
		} else {

			/*************************************
			 **** Normal Traffic Light Cycle *****
			 *************************************
			 // This section outlines the standard traffic light cycle for a North-South (NS) and East-West (EW) intersection.
			 // The cycle ensures traffic flow by alternating green, yellow, and red lights in a predefined sequence.
			 // - The cycle consists of four main steps, ensuring that traffic flows in both directions.
			 // - with yellow lights acting as a buffer between green and red states.

			 // | Step  |   Traffic Light State      |   Description                                                    |   Function Name    |
			 // |-------|----------------------------|------------------------------------------------------------------|--------------------|
			 // | Step 1| NS -> Green , EW -> Red    | North-South traffic flows while East-West traffic is stopped.    | NS_GREEN_EW_RED()  |
			 // | Step 2| NS -> Yellow, EW -> Red    | North-South traffic prepares to stop; East-West remains stopped. | NS_YELLOW_EW_RED() |
			 // | Step 3| NS -> Red   , EW -> Green  | East-West traffic flows while North-South traffic is stopped.    | NS_RED_EW_GREEN()  |
			 // | Step 4| NS -> Red   , EW -> Yellow | East-West traffic prepares to stop; North-South remains stopped. | NS_RED_EW_YELLOW() |
			 // | Step 5| NS -> Green , EW -> Red    | Cycle repeats from Step 1 to maintain continuous traffic flow.   | NS_GREEN_EW_RED()  |
			 */

			switch (currentState) {
			case NS_Green_EW_Red:
				// Step 1: North-South Green, East-West Red
				NS_GREEN_EW_RED();
				currentState = NS_Yellow_EW_Red;
				break;

			case NS_Yellow_EW_Red:
				// Step 2: North-South Yellow, East-West Red
				NS_YELLOW_EW_RED();
				currentState = NS_Red_EW_Green;
				break;

			case NS_Red_EW_Green:
				// Step 3: North-South Red, East-West Green
				NS_RED_EW_GREEN();
				currentState = NS_Red_EW_Yellow;
				break;

			case NS_Red_EW_Yellow:
				// Step 4: North-South Red, East-West Yellow
				NS_RED_EW_YELLOW();
				currentState = NS_Green_EW_Red;
				break;

			default:
				// Default to a safe state in case of unexpected errors
				currentState = NS_Green_EW_Red;
				break;

			}

		}
	}
}

// Initialize traffic light pins as output
void TrafficLight_Init(void) {
	DIO_PIN_DIRECTION(DIO_PORTB, 0, OUTPUT);
	DIO_PIN_DIRECTION(DIO_PORTB, 1, OUTPUT);
	DIO_PIN_DIRECTION(DIO_PORTB, 2, OUTPUT);

	DIO_PIN_DIRECTION(DIO_PORTB, 3, OUTPUT);
	DIO_PIN_DIRECTION(DIO_PORTB, 4, OUTPUT);
	DIO_PIN_DIRECTION(DIO_PORTB, 5, OUTPUT);

	DIO_PIN_DIRECTION(DIO_PORTC, 2, OUTPUT);
	DIO_PIN_DIRECTION(DIO_PORTC, 3, OUTPUT);

}
// Initialize pedestrian button pins as output
void Ped_Button_Init(void) {
	// Set INT0 (PD2) and INT1 (PD3) as input pins
	DIO_PIN_DIRECTION(DIO_PORTD, 2, INPUT);
	DIO_PIN_DIRECTION(DIO_PORTD, 3, INPUT);

	// Configure INT0 to trigger on the falling edge
	MCUCR |= (1 << ISC01);   // Set ISC01
	MCUCR &= ~(1 << ISC00);  // Clear ISC00

	// Configure INT1 to trigger on the falling edge
	MCUCR |= (1 << ISC11);   // Set ISC11
	MCUCR &= ~(1 << ISC10);  // Clear ISC10

	// Enable INT0 and INT1 interrupts in the GICR register
	GICR |= (1 << INT0);     // Enable INT0
	GICR |= (1 << INT1);     // Enable INT1

	// Enable global interrupts
	sei();

}

// Pedestrian mode function
void PedestrianSignal() {
// Turn on pedestrian signal (example: PORTD, pin 3)
	DIO_PIN_WRITE(DIO_PORTC, 2, HIGH); // Pedestrian green
	DIO_PIN_WRITE(DIO_PORTC, 3, HIGH); // Pedestrian green
	long_delay(PED_CROSS_TIME); // Allow pedestrians to cross
	DIO_PIN_WRITE(DIO_PORTC, 2, LOW);  // Pedestrian signal off
	DIO_PIN_WRITE(DIO_PORTC, 3, LOW); // Pedestrian green

}

// North-South Green, East-West Red
void NS_GREEN_EW_RED(void) {
// North-South: Green ON, Yellow OFF, Red OFF
	DIO_PIN_WRITE(DIO_PORTB, 0, HIGH);
	DIO_PIN_WRITE(DIO_PORTB, 1, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 2, LOW);

// East-West: Green OFF, Yellow OFF, Red ON
	DIO_PIN_WRITE(DIO_PORTB, 3, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 4, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 5, HIGH);

	long_delay(GREEN_TIME);
}

// North-South yellow, East-West Red
void NS_YELLOW_EW_RED(void) {
// North-South: Green OFF, Yellow ON, Red OFF
	DIO_PIN_WRITE(DIO_PORTB, 0, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 1, HIGH);
	DIO_PIN_WRITE(DIO_PORTB, 2, LOW);

// East-West: Green OFF, Yellow OFF, Red ON
	DIO_PIN_WRITE(DIO_PORTB, 3, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 4, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 5, HIGH);

	long_delay(YELLOW_TIME);
}

// North-South red, East-West green
void NS_RED_EW_GREEN(void) {
// North-South: Green OFF, Yellow OFF, Red ON
	DIO_PIN_WRITE(DIO_PORTB, 0, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 1, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 2, HIGH);

// East-West: Green ON, Yellow OFF, Red OFF
	DIO_PIN_WRITE(DIO_PORTB, 3, HIGH);
	DIO_PIN_WRITE(DIO_PORTB, 4, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 5, LOW);

	long_delay(GREEN_TIME);
}

// North-South red, East-West yellow
void NS_RED_EW_YELLOW(void) {

// North-South: Green OFF, Yellow OFF, Red ON
	DIO_PIN_WRITE(DIO_PORTB, 0, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 1, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 2, HIGH);

// East-West: Green OFF, Yellow ON, Red OFF
	DIO_PIN_WRITE(DIO_PORTB, 3, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 4, HIGH);
	DIO_PIN_WRITE(DIO_PORTB, 5, LOW);

	long_delay(YELLOW_TIME);
}

void NS_OFF_EW_OFF(void) {
// North-South: Green ON, Yellow OFF, Red OFF
	DIO_PIN_WRITE(DIO_PORTB, 0, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 1, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 2, LOW);

// East-West: Green OFF, Yellow OFF, Red OFF
	DIO_PIN_WRITE(DIO_PORTB, 3, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 4, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 5, LOW);
	long_delay(OFF_OFF_ALL_TIME);
}

void NS_RED_EW_RED(void) {
// North-South: Green OFF, Yellow OFF, Red ON
	DIO_PIN_WRITE(DIO_PORTB, 0, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 1, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 2, HIGH);

// East-West: Green OFF, Yellow OFF, Red ON
	DIO_PIN_WRITE(DIO_PORTB, 3, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 4, LOW);
	DIO_PIN_WRITE(DIO_PORTB, 5, HIGH);
	long_delay(RED_RED_ALL_TIME);
}

void long_delay(uint16_t time_ms) {
	while (time_ms > 100) {
		_delay_ms(100);
		time_ms -= 100;
	}
	_delay_ms(time_ms);  // Delay the remaining time
}

ISR(INT0_vect) {
	pedestrianModeActive = 1; // Activate pedestrian mode
}

ISR(INT1_vect) {
	pedestrianModeActive = 1; // Activate pedestrian mode
}
