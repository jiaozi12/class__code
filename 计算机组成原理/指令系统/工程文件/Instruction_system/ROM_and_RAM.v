module ROM_and_RAM(address,data_in,data_out,wr);
	input wr;
	input [7:0]address;
	input [15:0]data_in;
	output [15:0]data_out;
	reg [15:0]data_out,data_in_ram;
	reg cs_rom;
	reg [2:0]cs_ram;
	wire [15:0]sram1,sram2,sram3,srom;
	wire [3:0]sign;
	always@(srom or sram1 or sram2 or sram3)
		begin
			case(sign)
				4'b0001:begin data_out=srom;end
				4'b0010:begin data_out=sram1;end
				4'b0100:begin data_out=sram2;end
				4'b1000:begin data_out=sram3;end
			endcase
		end
	decoder_24 decoder(address[7:6],sign);
	SROM SROM_1(address[5:0],srom[15:8],sign[0]);
	SROM2 SROM_2(address[5:0],srom[7:0],sign[0]);
	SRAM SRAM_1(address[5:0],data_in_ram,sram1,sign[1],wr);
	SRAM SRAM_2(address[5:0],data_in_ram,sram2,sign[2],wr);
	SRAM SRAM_3(address[5:0],data_in_ram,sram3,sign[3],wr);
endmodule
