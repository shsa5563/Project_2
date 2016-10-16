The project2 : To display data on RealTerm/Putty console using UART with LED Control Feature.  The Project is made architecure independent ; and cross verified in BeagleBone and FRDM Boards 

The Project includes the following:

UART.C : 
	UART0_init():Initialization of UART with timers and enabling the clocks, Interrupts
	UART0_IRQHandler(): Handles Interrupts for transmit and recieve buffer full/empty status 
	send_string(char s[]): sends the string to the console through UART
	send_char(char _value): sends single characters to the console through UART
	put_data_with_Interrupt(uint8_t *c): Sends the Data to the console through UART using the concept of Interrupts.

CIRC_BUFF.C:

	buff_full(circular_buff_t *circ_buff): Checks if the buffer is full
	buff_empty(circular_buff_t *circ_buff):Checks if the buffer is empty
	put_item_tobuffer(circular_buff_t *circ_buff, uint8_t data):puts the data typed by the user to the buffer
	read_delete_item_frombuffer(circular_buff_t *circ_buff):reads the data 	from the buffer and stores it for displaying on console through UARTand deletes the read value from the buffer.
	* allocate_memory(circular_buff_t *circ_buff): allocates the memory for the circular buffer through malloc function 
	free_buff(circular_buff_t *circ_buff):free's the allocated memory for the circular buffer 

CIRCULAR_BUFFER_TEST.C:
	initialize_test(void):Tests if the circular buffer is allocated and initialised with proper values 
	buff_full_test(void): Test the functioality of buffer full 
	buff_empty_test(void):Test the functionality of buffer empty
	put_item_tobuffer_test(uint8_t itemtoadd):tests the functionality of adding an item to the buffer 
	read_delete_item_frombuffer_test(void):tests the functionality of readnig and deleting the added value from the circular buffer 

LED.C:
	Initialize_LED():Initilalises the LED with TPM clocks for enabling the PWM generation 
	Change_LEDColor(uint8_t Value):Routine which changes the color of the LED depening upon the user input
	Intensty_Modify(Colour_LED Colour, uint16_t Brightness):Routine to modify the Colour and the intensity of the LED 

LOG.C
	LOG_0(uint8_t * data, uint32_t len):Routine to display the string value of the predefined input
	LOG_1(uint8_t * data, float param,uint32_t point): Routine to display the float value of the predefined Input
	reverse(uint8_t *str, uint32_t len):Reverse Routine is used to reverse the array of ASCI values which are stored after the conversion of ftoa
	intToStr(uint32_t val_data, uint8_t str[], uint32_t len):Routine to convert the integer value to string for displaying it on the consloe 
	ftoa(float _float_val, uint8_t *res, uint32_t afterdecimal): Routine which converst float to ASCII

Two functions for profiler timer requirements - To check the time taken by the program to execute the given chunck of code.
