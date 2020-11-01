
#include <asf.h>
#include "driver.h"

int main (void)
{
	init_bargraph();

	bargraph_write(1);
	bargraph_write(0);
	
	// Insert application code here, after the board has been initialized.
}
