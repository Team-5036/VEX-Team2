#pragma config(Motor,  port1,           conveyor,      tmotorVex393, openLoop)
#pragma config(Motor,  port2,           left,          tmotorVex393, openLoop)
#pragma config(Motor,  port3,           right,         tmotorVex393, openLoop)
#pragma config(Motor,  port4,           back,          tmotorVex393, openLoop)
#pragma config(Motor,  port5,           shooterLeft,   tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port6,           shooterRight,  tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port7,           liftLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port8,           liftRight,     tmotorVex393, openLoop)
#pragma config(Motor,  port9,           intakeLeft,    tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port10,          intakeRight,   tmotorVex393HighSpeed, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void gyroInit();
void updateDrive();
void shooter(int speed);
void intake();
void lift();

//Public Variables
int defAngle = 0;
int angle;

// Controller 1/2, Stick L/R, Axis X/Y
#define C1LX vexRT[Ch4]
#define C1LY vexRT[Ch3]
#define C1RX vexRT[Ch1]
bFloatDuringInactiveMotorPWM = true;
//-------------------------------------------------Main Task--------------------------------------------------------
task main()
{
	gyroInit();
	while(1){
		updateDrive();
		shooter(127);
		intake();
		lift();
		//Wait so motors can update
		wait1Msec(20);
	}
}
//--------------------------------------------------Functions-------------------------------------------------------
void gyroInit(){
 //Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[in8] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[in8] = sensorGyro;
 wait1Msec(2000);
 //Adjust SensorScale to correct the scaling for your gyro
 //SensorScale[in8] = 260;
 //Adjust SensorFullCount to set the "rollover" point. 3600 sets the rollover point to +/-3600
 //SensorFullCount[in8] = 3600;
 //Specify the number of degrees for the robot to turn (1 degree = 10, or 900 = 90 degrees)
}
void updateDrive(){
	//Set motors
	if (C1RX != 0){
		angle = SensorValue[in8] - defAngle;
		motor[left] = C1LY + (angle/5);
		motor[right] = -C1LY + (angle/5);
		motor[back] = C1LX + (angle/5);
 }
 else{
    motor[left] = C1LY + C1RX;
	  motor[right] = -C1LY + C1RX;
		motor[back] = C1LX + C1RX;
		defAngle = SensorValue[in8];
 }
}
void shooter(int speed){
	motor[shooterLeft] = speed;
	motor[shooterRight] = -speed;
}
void intake(){
	if(vexRT[Btn6U]){
		motor[conveyor] = -127;
	}
	else {
		motor[conveyor] = 0;
	}

	if(vexRT[Btn5U]){
		motor[intakeLeft] = 127;
		motor[intakeRight] = -127;
	}
	else{
		motor[intakeLeft] = 0;
		motor[intakeRight] = 0;
	}
}
void lift(){
	if (vexRT[Btn8U]){
		motor[liftLeft] = 127;
		motor[liftRight] = -127;
	}
	else if(vexRT[Btn8D]){
		motor[liftLeft] = -127;
		motor[liftRight] = 127;
	}
	else{
		motor[liftLeft] = 0;
		motor[liftRight] = 0;
	}
}