
module lab1_sys (
	clk_clk,
	leds_external_connection_export,
	push_buttons_external_connection_export,
	reset_reset_n,
	switches_external_connection_export);	

	input		clk_clk;
	output	[9:0]	leds_external_connection_export;
	input	[1:0]	push_buttons_external_connection_export;
	input		reset_reset_n;
	input	[3:0]	switches_external_connection_export;
endmodule
