// accelerometer.h - gets angle from acceleromter
// TODO: allow use to use multiple accelerometers with same API

/*!
	Enum to select which accelerometer to setup
 */
typedef enum {
	ACCELEROMETER_LIS3DSH,
	ACCELEROMETER_9DOFMEMS
} ACCELEROMETER;


/*!
	Makes system calls for setting up accelerometer
	
	@return 0 on success, else negative
 */
int accelerometer_setup(ACCELEROMETER which);

/*!
	Gets the actual angle
	@param *angle the angle measured by the accelerometer
	@return 0 on success, else negative
 */
int get_angle(int* angle);
