module Instruction_system(clk,clr,addr,a,b,op);
	input clk,clr;
	input [7:0]addr;
	reg [7:0]address;
	output [15:0]a,b;
	output [3:0]op;
	reg [3:0]op;
	reg [15:0]data_in,a,b;
	reg [47:0]inst;
	reg [3:0]register_index;
	reg flag,cs_register;
	reg [2:0]sign;
	integer count1=0,count2=0;
	wire [15:0]rom_ram_out,register_out;
	initial sign=3'b000;
	always@(posedge clk)//读指令
		begin 
			if(clr==1)
				begin
					count1=0;
					count2=0;
				end
			else begin
			if(count1<9)
				begin
					if(flag) begin address=addr;flag=0;end
					if(address==addr) begin inst[47:32]=rom_ram_out;sign[0]=1;address=addr+1;end
					else if(address==addr+1) begin inst[31:16]=rom_ram_out;sign[1]=1;address=addr+2;end
					else if(address==addr+2) begin inst[15:0]=rom_ram_out;sign[2]=1;address=addr;end
					if(sign==3'b111) begin flag=1;sign=0;end
					count1=count1+1;
				end

			if(count1>=9&&count2<17)
				begin
					case(inst[35:34])
						2'b00:begin register_index=inst[21:18];a=register_out;end//寄存器直接寻址
						2'b01:begin address=inst[31:24];a=rom_ram_out;end//存储器直接寻址
						2'b10:begin register_index=inst[23:20];address=inst[31:24]+register_out;a=rom_ram_out;end//存储器变址寻址
						2'b11:begin a=inst[15:0];end//立即数
					endcase
					count2=count2+1;
				end
				
			if(count2>=17)
				begin
					case(inst[17:16])
						2'b00:begin register_index=inst[3:0];b=register_out;end//寄存器直接寻址
						2'b10:begin register_index=inst[7:4];address=inst[15:8]+register_out;b=rom_ram_out;end//存储器变址寻址
					endcase
					op=inst[39:36];
				end
			end
		end
		
	ROM_and_RAM ROM_RAM_1(address,data_in,rom_ram_out,1);
	register register_1(register_index,,register_out,0,1);
endmodule
