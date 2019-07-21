module Alu16(T,M,F,C,Z,N,OV); 
	parameter bit_width=16; 
	input[bit_width-1:0]T;
	input[1:0]M;
	output[bit_width:0]F;
	output Z,C,N,OV; 
	reg[bit_width:0]A,B,d;
	reg[bit_width:0]F; 
	reg[3:0]S; 
	reg[16:0]F1; 
	reg C,Z,N,OV; 
	initial C=0;
	always@(T,M) 
		case(M) 
		2'b00:A={T[15],T}; 
 		2'b01:B={T[15],T}; 
		2'b11:S=T[3:0];  
 		endcase 
	always@(A,B,S) 
		begin 
		OV=0;
		case(S) 
		4'b0001:begin {C,F1}=A+B;OV=F1[16]^F1[15];end  
 		4'b0010:begin d=~B;{C,F1}=A+d+1;OV=F1[16]^F1[15];end	
		4'b0011:begin {C,F1}=A+1;OV=F1[16]^F1[15];end  
		4'b0100:begin {C,F1}=A-1;OV=F1[16]^F1[15];end  
		4'b0101:begin F1=A&B;F1[16]=0;end   
		4'b0110:begin F1=A|B;F1[16]=0;end   
		4'b0111:begin F1=~A;F1[16]=0;end    
		4'b1000:begin F1[15:0]={A[14:0],1'b0};F1[16]=0;end  
		4'b1001:begin F1[15:0]={1'b0,A[15:1]};F1[16]=0;end    
		4'b1010:begin {C,F1}={A[15],A[15:0],1'b0};OV=F1[16]^F1[15];N=F1[16];end   
		4'b1011:begin {C,F1}={A[0],A[16],A[16:1]};OV=F1[16]^F1[15];N=F1[16];end  
		default:begin F1=0; end
		endcase 
	F=F1[16:0];
 	if(F[15:0]==16'b0000000000000000) Z=1;
	else Z=0;
	N=F[16];
	end 
endmodule