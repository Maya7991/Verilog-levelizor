// Benchmark "main" written by ABC on Wed Apr 10 12:33:41 2024

module main ( 
    a, b, cin,
    carry, sum  );
  input  a, b, cin;
  output carry, sum;
  wire new_n6, new_n7, new_n8, new_n9, new_n10, new_n11, new_n12, new_n13,
    new_n14, new_n16;
  INVX1 g01 (.A(b), .Y(new_n7));
  NOR2X1 g02(.A(new_n7), .B(new_n6), .Y(new_n16));
  NOR2X1 g11(.A(new_n16), .B(new_n13), .Y(sum));
endmodule


