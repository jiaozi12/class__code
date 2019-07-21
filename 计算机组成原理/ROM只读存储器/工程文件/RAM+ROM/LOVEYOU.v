module LOVEYOU(clk,DATAOUT);
	input clk;
	output [27:0]DATAOUT;
	reg [11:0]address;
	reg [27:0]DATAOUT;
	reg [90:0]word;
	reg [5:0]logo;
	reg cs_rom,wr;
	reg [2:0]cs_ram;
	integer j=0;
	integer clk_count=0;
	integer count=0;
	integer cnt=0;
	wire [15:0]dataout_rom;
	wire [15:0]dataout_ram1,dataout_ram2,dataout_ram3;
	initial 
		begin
			count=0;
			cs_ram=0;
			cs_rom=0;
			logo=0;
			cs_ram=0;
			wr=1;
			address=0;
		end
	always@(posedge clk)
		begin
			address[11:0]=j;
			if(address[11:10]==2'b00) begin cs_rom=1;cs_ram=3'b000;end
			if(address[11:10]==2'b01) begin cs_rom=0;cs_ram=3'b001;end
			if(address[11:10]==2'b10) begin cs_rom=0;cs_ram=3'b010;end
			if(address[11:10]==2'b11) begin cs_rom=0;cs_ram=3'b100;end
			if(address[9:0]==10'b0000000000) begin word[90:77]=dataout_rom[13:0];j=(j+1)%6;logo[0]=1;end
			if(address[9:0]==10'b0000000001) begin word[76:63]=dataout_rom[13:0];j=(j+1)%6;logo[1]=1;end
			if(address[9:0]==10'b0000000010) begin word[55:42]=dataout_rom[13:0];j=(j+1)%6;word[62:56]=7'b0000000;logo[2]=1;end
			if(address[9:0]==10'b0000000011) begin word[41:28]=dataout_rom[13:0];j=(j+1)%6;logo[3]=1;end
			if(address[9:0]==10'b0000000100) begin word[27:14]=dataout_rom[13:0];j=(j+1)%6;logo[4]=1;end
			if(address[9:0]==10'b0000000101) begin word[13:0]=dataout_rom[13:0];j=(j+1)%6;logo[5]=1;end
			
			
			if(logo[5:0]==6'b111111)
					begin
						if(count==0) begin DATAOUT[6:0]=word[90:84];count=1;end
						else if(count==1) begin DATAOUT[13:0]=word[90:77];count=2;end
						else if(count==2) begin DATAOUT[20:0]=word[90:70];count=3;end
						else if(count==3) begin DATAOUT[27:0]=word[90:63];count=4;end
						else if(count==4) begin DATAOUT[27:0]=word[83:56];count=5;end
						else if(count==5) begin DATAOUT[27:0]=word[76:49];count=6;end
						else if(count==6) begin DATAOUT[27:0]=word[69:42];count=7;end
						else if(count==7) begin DATAOUT[27:0]=word[62:35];count=8;end
						else if(count==8) begin DATAOUT[27:0]=word[55:28];count=9;end
						else if(count==9) begin DATAOUT[27:0]=word[48:21];count=10;end
						else if(count==10) begin DATAOUT[27:0]=word[41:14];count=11;end
						else if(count==11) begin DATAOUT[27:0]=word[34:7];count=12;end
						else if(count==12) begin DATAOUT[27:0]=word[27:0];count=13;end
						else if(count==13) begin DATAOUT[27:7]=word[20:0];DATAOUT[6:0]=0;count=14;end
						else if(count==14) begin DATAOUT[27:14]=word[13:0];DATAOUT[13:0]=0;count=15;end
						else if(count==15) begin DATAOUT[27:21]=word[6:0];DATAOUT[20:0]=0;count=16;end
						else if(count==16) begin DATAOUT[27:0]=0;count=17;end
						else if(count==17) begin clk_count=clk_count+1;DATAOUT=0;end
						if(clk_count==5) begin count=0;clk_count=0;end
					end
		end
ROM ROM_1(clk,address[9:0],dataout_rom,cs_rom);
SRAM SRAM_1(clk,address[9:0],data_in,dataout_ram1,cs_ram[0],wr);
SRAM SRAM_2(clk,address[9:0],data_in,dataout_ram2,cs_ram[1],wr);
SRAM SRAM_3(clk,address[9:0],data_in,dataout_ram3,cs_ram[2],wr);

endmodule
