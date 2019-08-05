module CPU(clk,clr,address,result,c,z,n,ov);
	input clk,clr;
	output [7:0]address;
	output [15:0]result;
	output c,z,n,ov;
	reg [15:0]result;
	reg c,z,n,ov;
	wire [15:0]a,b,F;
	wire [3:0]op;
	wire C,Z,N,OV;
	integer pc=0;
	reg [7:0]address;
	
	always@(posedge clr)
		begin
			address=pc;pc=pc+3;
		end
	
	always@(a or b)
		begin
			result=F;
			c=C;
			z=Z;
			n=N;
			ov=OV;
		end
		
	Instruction_system(clk,clr,address,a,b,op);
	Alu16(a,b,op,F,C,Z,N,OV);
	
endmodule
