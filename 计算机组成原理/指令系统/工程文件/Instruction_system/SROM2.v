module SROM2(address,data_out,cs);
	input cs;
	input [5:0]address;
	output [7:0]data_out;
	reg [7:0]data_out;
	wire [7:0]data[(1<<6)-1:0];
	assign data[6'b00_0000]=8'b0001_0000;//高4位0001表示a+b，低2位00表示操作数a使用寄存器直接寻址方式
	assign data[6'b00_0001]=8'b00_0000_00;//中间4位表示通用寄存器编号，低2位00表示操作数b使用寄存器直接寻址方式
	assign data[6'b00_0010]=8'b0000_0001;//低4位0001表示通用寄存器编号
	assign data[6'b00_0011]=8'b0010_0000;//a-b
	assign data[6'b00_0100]=8'b00_0010_00;
	assign data[6'b00_0101]=8'b0000_0011;
	assign data[6'b00_0110]=8'b0011_0100;//a+1,使用存储器直接寻址
	assign data[6'b00_0111]=8'b0000_0000;
	assign data[6'b00_1000]=8'b0000_0000;
	assign data[6'b00_1001]=8'b0100_0100;//a-1,使用存储器直接寻址
	assign data[6'b00_1010]=8'b0000_0000;
	assign data[6'b00_1011]=8'b0000_0000;
	assign data[6'b00_1100]=8'b0101_1000;//与,后面的1000中的10表示a操作数变址寻址
	assign data[6'b00_1101]=8'b0100_0010;//操作数a，高4位变址寻址寄存器编号，后面的1000中的10表示b操作数变址寻址
	assign data[6'b00_1110]=8'b0101_0000;//操作数b，高4位变址寻址寄存器编号
	assign data[6'b00_1111]=8'b0110_1000;//或
	assign data[6'b01_0000]=8'b0110_0010;
	assign data[6'b01_0001]=8'b0111_0000;
	assign data[6'b01_0010]=8'b0111_1000;//非，使用存储器变址方式
	assign data[6'b01_0011]=8'b1000_0000;//操作数a，高4位变址寻址寄存器编号
	assign data[6'b01_0100]=8'b0000_0000;
	assign data[6'b01_0101]=8'b1000_1100;//逻辑左移，使用立即数
	assign data[6'b01_0110]=8'b0000_0000;
	assign data[6'b01_0111]=8'b0000_0000;//16位立即数低8位
	assign data[6'b01_1000]=8'b1001_1100;//逻辑右移，使用立即数
	assign data[6'b01_1001]=8'b0000_0000;
	assign data[6'b01_1010]=8'b0011_1111;//16位立即数低8位
	assign data[6'b01_1011]=8'b1010_1100;//算术左移，使用立即数
	assign data[6'b01_1100]=8'b0000_0000;
	assign data[6'b01_1101]=8'b1000_1000;//16位立即数低8位
	assign data[6'b01_1110]=8'b1011_1100;//算术右移，使用立即数
	assign data[6'b01_1111]=8'b0000_0000;
	assign data[6'b10_0000]=8'b0101_0011;//16位立即数低8位
	
	always@(address)
		begin 
			if(cs) begin data_out=data[address];end
		end
			
endmodule
