module Alu16(a,b,op,F,C,Z,N,OV);  
	input [15:0]a,b;
	input[3:0]op;
	output[15:0]F;
	output C,Z,N,OV; 
	reg[16:0]A,B,d;
	reg[15:0]F; 
	reg[16:0]F1; 
	reg C,Z,N,OV; 
	initial C=0;
	always@(a,b) 
		begin 
		OV=0;
		A={a[15],a};
		B={b[15],b};
		case(op) 
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
	N=F1[16];
	end 
endmodule
