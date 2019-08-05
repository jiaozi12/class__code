module SRAM(address,datain,dataout,cs,wr); 
	input wr,cs; 
	input[5:0]address; 
	input[15:0]datain; 
	output[15:0]dataout;
	reg[15:0]dataout;
	reg[15:0]mem[(1<<6)-1:0];
	
	initial//要用到00_0000_0000~00_0000_0111，7个数
		begin
			mem[6'b00_0000]=16'b0100_0010_0011_0101;//a+1,4235
			mem[6'b00_0001]=16'b0111_1111_1110_0011;//a-1,7FE3
			mem[6'b00_0010]=16'b0111_1111_0001_0010;//与,7F12
			mem[6'b00_0011]=16'b0100_0001_0011_1110;//413E
			mem[6'b00_0100]=16'b0001_0100_0010_0110;//或,1426
			mem[6'b00_0101]=16'b0001_0001_0000_0001;//1101
			mem[6'b00_0110]=16'b0001_0001_1111_0000;//求反,11F0
		end

	always@(address) 
		begin
			if(cs&&wr==0)
				//wr为0时执行写操作
				mem[address]=datain;
			if(cs&&wr)
				//wr为1时执行读操作
				dataout=mem[address];
		end

endmodule 
