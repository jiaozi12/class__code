module SRAM(clk,address,datain,dataout,cs,wr); 
input clk,wr,cs; 
input[9:0]address; 
input[15:0]datain; 
output[15:0]dataout;
reg[15:0]dataout;
reg[0:15]mem[0:(1<<10)-1];
reg[0:10]i;
always@(posedge clk) 
begin
if(cs&&wr==0)
//wr为0时执行写操作
 mem[address]=datain;
if(cs&&wr)
//wr为1时执行读操作
 dataout=mem[address];
end

endmodule 
