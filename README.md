Project Title: 
- Controlling-a-car-using-hand-motion.

What the project does:
- Controling two dc motors direction and speed by fingers movements. 

Project Description:
- The project is about controlling two DC motors using fingers motions.
- At the first side we have hand gloves , atmega32 and five flexible sensors each connected via known resistance in series and attached to our five fingers using hand gloves.
- According to the position of the finger the resistance of the flexible sensor changes.
- As a resistance change result the analog voltage of the common node between the flexible sensor and the series known resistance changes. 
- The five nodes are connected to five ADC channels in the atmega32 and by calibration of the digital voltages after changing the resistance we have two digital ranges values for each finger to indicate if it is bent or not.
- So according to the position of the finger we send a character to the car side to indicate which action we want to execute on the two motors.
- Actions in the car side are moving forward , backward , right , left and controlling the speed of the two motor using the PWM. 
- the wireless communication between the two atmega32 not implemented in proteus but it is achieved in the real hardware with two esp32 using IP addresses.

how to use the project:
- open the HandGloves and Car folders then open the debug folder then you will find the hex files for both.
- hex files are already burned in proteus so open proteus. 
- check that all resistance of all poteniometers are in the unbent range (less that 25%).
- run the simulation. 
- expected that car will be moving forward.
- with Pot2 you can control the direction forward (less than 25%) or backward (greater than 25%).
- with Pot1 you can control the speed low (less than 25%) or high (greater than 25%).
- with Pot4 you can control the direction right (greater than 25%). 
- with Pot5 you can control the direction left (greater than 25%).
- to stop the car make them all in the bent range (greater than 25%).

SoftWare requirments to use the project: 
- Eclipse if you want to debug or add additional feature to the project.
- Proteus v8.13 at least. 

Technologies and librairies used:
- C programming.  
- Esp32 IDF.


![image](https://user-images.githubusercontent.com/84681597/158269266-7df9e782-c525-42f7-a1d3-73d09c54209d.png)
