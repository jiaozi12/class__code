module decoder_24(in,out);
	input [1:0]in;
	output [3:0]out;
	reg [3:0]out;
	always@(in)
		begin
			case(in)
				2'b00:begin out=0;out[0]=1;end
				2'b01:begin out=0;out[1]=1;end
				2'b10:begin out=0;out[2]=1;end
				2'b11:begin out=0;out[3]=1;end
			endcase
		end
endmodule
