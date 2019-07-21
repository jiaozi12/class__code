module ROM(clk,address,data_out,cs_rom);
input cs_rom,clk;
input[9:0]address;
output[15:0]data_out;
reg[15:0]data_out;
wire [15:0]rom[0:(1<<10)-1];
	assign rom[10'b0000000000]=16'b00_0000110_1001111;//13 
	assign rom[10'b0000000001]=16'b00_0000110_1100110;//14
	assign rom[10'b0000000010]=16'b00_0111000_0111111;//LO
	assign rom[10'b0000000011]=16'b00_0111110_1111001;//VE
	assign rom[10'b0000000100]=16'b00_0000000_1101110;//_Y
	assign rom[10'b0000000101]=16'b00_0111111_0111110;//OU
	
always@(posedge clk)
    begin
	     if(cs_rom) data_out=rom[address];
    end
endmodule
