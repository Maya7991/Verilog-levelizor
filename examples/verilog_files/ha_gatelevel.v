module half_adder_structural (a,b,s,c);
input a;  // Input 'a'
input b;  // Input 'b'
output s;   // Output 's' (Sum)
output c;  // Output 'c' (Carry)
  
xor (s, a, b);  
and (c, a, b);
endmodule
