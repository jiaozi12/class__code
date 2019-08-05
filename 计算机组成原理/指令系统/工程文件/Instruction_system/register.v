module register(address,data_in,data_out,wr,cs);
input [3:0]address;
input [15:0]data_in;
input wr,cs;
output [15:0]data_out;
reg [15:0]data_out;
reg [15:0] mem [(1<<4)-1:0];
//通用寄存器，用于存放a+b和a-b的数据
initial
begin
	mem[4'b0000] = 16'b1000_0000_0001_0001;//8011		
	mem[4'b0001] = 16'b1000_0000_0010_0010;//8022
	mem[4'b0010] = 16'b1000_0001_0010_0011;//8123
	mem[4'b0011] = 16'b0001_0001_0010_0100;//1124
	mem[4'b0100] = 16'b0000_0000_0000_0001;//变址寻址第一个偏移量
	mem[4'b0101] = 16'b0000_0000_0000_0010;//变址寻址第二个偏移量
	mem[4'b0110] = 16'b0000_0000_0000_0011;//变址寻址第三个偏移量
	mem[4'b0111] = 16'b0000_0000_0000_0100;//变址寻址第四个偏移量
	mem[4'b1000] = 16'b0000_0000_0000_0101;//变址寻址第五个偏移量
end

always@(address)
	begin
		if(cs)
			begin
				if(wr) begin mem[address]=data_in;end
				if(!wr) begin data_out=mem[address];end
			end
	end

endmodule 