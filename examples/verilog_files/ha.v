module half_adder_behavioral (
  input a,    // Input 'a'
  input b,    // Input 'b'
  output s,   // Output 's' (Sum)
  output c    // Output 'c' (Carry)
);

  // Combinational logic equations for sum and carry
  always @(*) begin
    s = a ^ b;  // XOR operation for sum
    c = a & b;  // AND operation for carry
  end

endmodule
