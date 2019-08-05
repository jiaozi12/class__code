module SROM(address,data_out,cs);
	input cs;
	input [5:0]address;
	output [7:0]data_out;
	reg [7:0]data_out;
	wire [7:0]data[(1<<6)-1:0];
	assign data[6'b00_0000]=8'b0000_0000;//48位指令，空闲8位
	assign data[6'b00_0001]=8'b0000_0000;//a+b操作，寄存器直接寻址空闲位
	assign data[6'b00_0010]=8'b0000_0000;//空闲位
	assign data[6'b00_0011]=8'b0000_0000;//a-b
	assign data[6'b00_0100]=8'b0000_0000;
	assign data[6'b00_0101]=8'b0000_0000;
	assign data[6'b00_0110]=8'b0000_0000;//a+1
	assign data[6'b00_0111]=8'b0100_0000;//操作数a的8位存储器地址
	assign data[6'b00_1000]=8'b0000_0000;
	assign data[6'b00_1001]=8'b0000_0000;//a-1
	assign data[6'b00_1010]=8'b0100_0001;//操作数a的8位存储器地址
	assign data[6'b00_1011]=8'b0000_0000;
	assign data[6'b00_1100]=8'b0000_0000;//与
	assign data[6'b00_1101]=8'b0100_0001;//操作数a（变址寻址），初始地址8位
	assign data[6'b00_1110]=8'b0100_0001;//操作数b（变址寻址），初始地址8位
	assign data[6'b00_1111]=8'b0000_0000;//或
	assign data[6'b01_0000]=8'b0100_0001;
	assign data[6'b01_0001]=8'b0100_0001;
	assign data[6'b01_0010]=8'b0000_0000;//非
	assign data[6'b01_0011]=8'b0100_0001;//a,8位地址（变址寻址）
	assign data[6'b01_0100]=8'b0000_0000;
	assign data[6'b01_0101]=8'b0000_0000;//逻辑左移
	assign data[6'b01_0110]=8'b0000_0000;
	assign data[6'b01_0111]=8'b1110_0000;//16位立即数高8位
	assign data[6'b01_1000]=8'b0000_0000;//逻辑右移
	assign data[6'b01_1001]=8'b0000_0000;
	assign data[6'b01_1010]=8'b0100_0010;//16位立即数高8位
	assign data[6'b01_1011]=8'b0000_0000;//算术左移
	assign data[6'b01_1100]=8'b0000_0000;
	assign data[6'b01_1101]=8'b1000_1000;//16位立即数高8位
	assign data[6'b01_1110]=8'b0000_0000;//算术右移
	assign data[6'b01_1111]=8'b0000_0000;
	assign data[6'b10_0000]=8'b0101_0101;//16位立即数高8位
	
	always@(address)
		begin 
			if(cs) begin data_out=data[address];end
		end
			
endmodule
