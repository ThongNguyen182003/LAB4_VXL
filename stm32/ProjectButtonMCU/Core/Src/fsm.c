
#include "fsm.h"

int TimeOfGreen = 3 ;
int TimeOfYellow  = 1;
int TimeOfRed = 5;  // TimeOfRed = TimeOfGreen + TimeOfYellow +
int statusLane = 0;

int newTimeGreen = 3;
int newTimeRed = 5;
int newTimeYellow = 1;

int status2HZ = 0;


void fsm_run(){
	switch(status){
		case INIT:

			status = LED_GREEN_LANE1;
			TurnOnLedGreenLane1();
			TurnOnLedRedLane2();
		break;
		case LED_GREEN_LANE1 :
			if(timer1_flag == 1)
			{
				if(TimeOfGreen >= 0)
				{
					TimeOfGreen--;
					TimeOfRed--;
					if(TimeOfGreen < 0)
					{
						status = LED_YELLOW_LANE1;
						TimeOfGreen = newTimeGreen;
						TurnOnLedYellowLane1();
						TurnOnLedRedLane2();
					}
				}
				setTimer1(100);
			}

			/*------------ --- Scan 7SEG --- -----------------*/
			  if(timer2_flag == 1)
			  {
				  // Display 7Seg lane 1
				  if(statusLane == 0)
				  {
					  display7SEGFS(TimeOfGreen/10);
					  display7SEGTS(TimeOfRed/10);
					  update7SEG(0);
					  statusLane = 1;
				  } else if(statusLane == 1){
					  display7SEGFS(TimeOfGreen%10);
					  display7SEGTS(TimeOfRed%10);
					  update7SEG(1);
					  statusLane = 0;
				  }
				  setTimer2(20);
			  }
				/*-----------------------------------------*/

			if(isButton1Pressed())
			{
				status = MAN_RED;
			}
		break;

		case LED_YELLOW_LANE1:
			if(timer1_flag == 1)
			{
				if(TimeOfYellow >= 0)
				{
					TimeOfYellow--;
					TimeOfRed--;
					if(TimeOfYellow < 0)
					{
						status = LED_GREEN_LANE2;
						TimeOfYellow = newTimeYellow;
						TimeOfRed = newTimeRed;
						TurnOnLedGreenLane2();
						TurnOnLedRedLane1();
					}
				}
				setTimer1(100);
			}

			/*------------ --- Scan 7SEG --- -----------------*/
			  if(timer2_flag == 1)
			  {
				  // Display 7Seg lane 1
				  if(statusLane == 0)
				  {
					  display7SEGFS(TimeOfYellow/10);
					  display7SEGTS(TimeOfRed/10);
					  update7SEG(0);
					  statusLane = 1;
				  } else if(statusLane == 1){
					  display7SEGFS(TimeOfYellow%10);
					  display7SEGTS(TimeOfRed%10);
					  update7SEG(1);
					  statusLane = 0;
				  }
				  setTimer2(20);
			  }
				/*-----------------------------------------*/
			if(isButton1Pressed())
			{
				status = MAN_RED;
				setTimer1(25);
			}
		break;

		case LED_GREEN_LANE2:
			if(timer1_flag == 1)
			{
				if(TimeOfGreen >= 0)
				{
					TimeOfGreen--;
					TimeOfRed--;
					if(TimeOfGreen < 0)
					{
						status = LED_YELLOW_LANE2;
						TimeOfGreen = newTimeGreen;
						TurnOnLedYellowLane2();
						TurnOnLedRedLane1();
					}
				}
				setTimer1(100);
			}
			/*------------ --- Scan 7SEG --- -----------------*/
			  if(timer2_flag == 1)
			  {
				  // Display 7Seg lane 1
				  if(statusLane == 0)
				  {
					  display7SEGFS(TimeOfRed/10);
					  display7SEGTS(TimeOfGreen/10);
					  update7SEG(0);
					  statusLane = 1;
				  } else if(statusLane == 1){
					  display7SEGFS(TimeOfRed%10);
					  display7SEGTS(TimeOfGreen%10);
					  update7SEG(1);
					  statusLane = 0;
				  }
				  setTimer2(20);
			  }
				/*-----------------------------------------*/
			if(isButton1Pressed())
			{
				status = MAN_RED;
			}
		break;

		case LED_YELLOW_LANE2:
			if(timer1_flag == 1)
			{
				if(TimeOfYellow >= 0)
				{
					TimeOfYellow--;
					TimeOfRed--;
					if(TimeOfYellow < 0)
					{
						status = LED_GREEN_LANE1;
						TimeOfYellow = newTimeYellow;
						TimeOfRed = newTimeRed;
						TurnOnLedGreenLane1();
						TurnOnLedRedLane2();
					}
				}
				setTimer1(100);
			}
			/*------------ --- Scan 7SEG --- -----------------*/
			  if(timer2_flag == 1)
			  {
				  // Display 7Seg lane 1
				  if(statusLane == 0)
				  {
					  display7SEGFS(TimeOfRed/10);
					  display7SEGTS(TimeOfYellow/10);
					  update7SEG(0);
					  statusLane = 1;
				  } else if(statusLane == 1){
					  display7SEGFS(TimeOfRed%10);
					  display7SEGTS(TimeOfYellow%10);
					  update7SEG(1);
					  statusLane = 0;
				  }
				  setTimer2(20);
			  }
				/*-----------------------------------------*/
			if(isButton1Pressed())
			{
				status = MAN_RED;
			}
		break;

		case MAN_RED:
		// LED red blink 2hz
		if(timer1_flag == 1)
		{
			if(status2HZ == 0){
				TurnOnLedRedLane1();
				TurnOnLedRedLane2();
				status2HZ = 1;
			} else {
				TurnOfAllLed();
				status2HZ = 0;
			}
			setTimer1(25);
		}


		if(isButton2Pressed())
		{
			newTimeRed++;
			if(newTimeRed > 99)
			{
				newTimeRed = 1;
			}
		}
		/*------------ --- Scan 7SEG --- -----------------*/
		  if(timer2_flag == 1)
		  {
			  // Display 7Seg lane 1
			  if(statusLane == 0)
			  {
				  display7SEGFS(newTimeRed/10);
				  update7SEG(0);
				  statusLane = 1;
			  } else if(statusLane == 1){
				  display7SEGFS(newTimeRed%10);
				  update7SEG(1);
				  statusLane = 0;
			  }
			  setTimer2(20);
		  }
			/*-----------------------------------------*/
		if(isButton3Pressed())
		{
			TimeOfRed = newTimeRed;
		}
		if(isButton1Pressed())
		{
			status = MAN_YELLOW;
		}
		break;

		case MAN_YELLOW:
		// LED red blink 2hz
		if(timer1_flag == 1)
		{
			if(status2HZ == 0){
				TurnOnLedYellowLane1();
				TurnOnLedYellowLane2();
				status2HZ = 1;
			} else {
				TurnOfAllLed();
				status2HZ = 0;
			}
			setTimer1(25);
		}

		if(isButton2Pressed())
		{
			newTimeYellow++;
			if(newTimeYellow > 99)
			{
				newTimeYellow = 1;
			}
		}
		/*------------ --- Scan 7SEG --- -----------------*/
		  if(timer2_flag == 1)
		  {
			  // Display 7Seg lane 1
			  if(statusLane == 0)
			  {
				  display7SEGFS(newTimeYellow/10);
				  update7SEG(0);
				  statusLane = 1;
			  } else if(statusLane == 1){
				  display7SEGFS(newTimeYellow%10);
				  update7SEG(1);
				  statusLane = 0;
			  }
			  setTimer2(20);
		  }
			/*-----------------------------------------*/
		if(isButton3Pressed())
		{
			TimeOfYellow = newTimeYellow;
		}
		if(isButton1Pressed())
		{
			status = MAN_GREEN;
		}
		break;

		case MAN_GREEN:
			// LED red blink 2hz
			if(timer1_flag == 1)
			{
				if(status2HZ == 0){
					TurnOnLedGreenLane1();
					TurnOnLedGreenLane2();
					status2HZ = 1;
				} else {
					TurnOfAllLed();
					status2HZ = 0;
				}
				setTimer1(25);
			}
			TurnOnLedGreenLane1();
			TurnOnLedGreenLane2();
			if(isButton2Pressed())
			{
				newTimeGreen++;
				if(newTimeGreen > 99)
				{
					newTimeGreen = 1;
				}
			}
			/*------------ --- Scan 7SEG --- -----------------*/
			  if(timer2_flag == 1)
			  {
				  // Display 7Seg lane 1
				  if(statusLane == 0)
				  {
					  display7SEGFS(newTimeGreen/10);
					  update7SEG(0);
					  statusLane = 1;
				  } else if(statusLane == 1){
					  display7SEGFS(newTimeGreen%10);
					  update7SEG(1);
					  statusLane = 0;
				  }
				  setTimer2(20);
			  }
				/*-----------------------------------------*/
			if(isButton3Pressed())
			{
				TimeOfGreen = newTimeGreen;
			}
			if(isButton1Pressed())
			{
				setTimer1(25);
				status = LED_GREEN_LANE1;
				TurnOnLedGreenLane1();
				TurnOnLedRedLane2();
			}
		break;
		default:
			break;

	}
}
