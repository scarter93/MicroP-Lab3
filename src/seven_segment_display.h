// seven_segment_display.h - displays numbers

#ifndef __INCLUDE_SEVEN_SEGMENT_H__
#define __INCLUDE_SEVEN_SEGMENT_H__

/*!
	Makes system calls for setting up GPIO for 7 segment display
	
	@return 0 on success, else negative
 */
int seven_segment_setup(void);

/*!
	displays a number on the seven segment display
	@param to_display number to display
	
	@return 0 on success, else negative
 */
int display(float to_display);

extern unsigned int wait;
#endif // __INCLUDE_SEVEN_SEGMENT_H__
