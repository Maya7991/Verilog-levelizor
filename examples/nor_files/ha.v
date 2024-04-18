// Benchmark "half_adder_structural" written by ABC on Thu Apr 18 09:29:25 2024

module half_adder_structural ( 
    a, b,
    s, c  );
  input  a, b;
  output s, c;
  wire new_n5, new_n6, new_n8;
  INVX1  g0(.A(a), .Y(new_n5));
  INVX1  g1(.A(b), .Y(new_n6));
  NOR2X1 g2(.A(new_n6), .B(new_n5), .Y(c));
  NOR2X1 g3(.A(b), .B(a), .Y(new_n8));
  NOR2X1 g4(.A(new_n8), .B(c), .Y(s));
endmodule


