// Benchmark "main" written by ABC on Wed Apr 10 12:33:41 2024

module main ( 
    a, b, cin,
    carry, sum  );
  input  a, b, cin;
  output carry, sum;
  wire new_n6, new_n7, new_n8, new_n9, new_n10, new_n11, new_n12, new_n13,
    new_n14, new_n16;
    
  INVX1  g00(.A(a), .Y(new_n6));
  INVX1  g01(.A(b), .Y(new_n7));
  NOR2X1 g02(.A(new_n7), .B(new_n6), .Y(new_n8));
  INVX1  g03(.A(cin), .Y(new_n9));
  NOR2X1 g04(.A(b), .B(a), .Y(new_n10));
  NOR2X1 g05(.A(new_n10), .B(new_n8), .Y(new_n11));
  INVX1  g06(.A(new_n11), .Y(new_n12));
  NOR2X1 g07(.A(new_n12), .B(new_n9), .Y(new_n13));
  NOR2X1 g08(.A(new_n13), .B(new_n8), .Y(new_n14));
  INVX1  g09(.A(new_n14), .Y(carry));
  NOR2X1 g10(.A(new_n11), .B(cin), .Y(new_n16));
  NOR2X1 g11(.A(new_n16), .B(new_n13), .Y(sum));
endmodule


