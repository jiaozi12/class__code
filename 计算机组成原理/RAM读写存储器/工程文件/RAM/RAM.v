module RAM(clk,choose,cin,address,dataout,clk_out);
input clk;
input[15:0]cin;
input[1:0]choose;
output[15:0]dataout;
output[11:0]address;
output clk_out;
wire[15:0]dainout1;
wire[15:0]dainout2;  
wire[15:0]dainout3;
reg[15:0]datain;
reg[11:0]address;
reg[15:0]dataout;
reg[2:0]e;
reg wr,clk_out;
always@(clk) begin clk_out=clk;end
always@(posedge clk)
	begin
		if(choose==2'b00)
			begin
				wr=1;
				datain=cin;
			end
		if(choose==2'b01)
			begin
				wr=1;
				address=cin[11:0];
			end
		if(choose==2'b10)
			begin
				address=address+1;
				datain=cin;
			end
		if(choose==2'b11)
			begin
				if(cin[3:0]==4'b0011) begin wr=1;end
				if(cin[3:0]==4'b0100) begin wr=0;end
			end
		case(address[11:10])
			2'b00: begin  e=3'b001;
			dataout=dainout1;end			
			2'b01: begin  e=3'b010; 
			dataout=dainout2;end		
			2'b10: begin  e=3'b100;   
			dataout=dainout3;end
		endcase
	end
SRAM SRAM_1(clk,address[9:0],datain,dainout1,e[0],wr);
SRAM SRAM_2(clk,address[9:0],datain,dainout2,e[1],wr);
SRAM SRAM_3(clk,address[9:0],datain,dainout3,e[2],wr);
endmodule
