# CalculatorAbsoluteCinema
THIS IS CALCULATOR ABSOLUTE CINEMA(CAS)

### Grammar:
```
expr    → term ( ( "+" | "-" ) term )*
term    → power ( ( "*" | "/" ) power )*
power   → factor ( "^" power )?
factor  → "(" expr ")" | LITERAL
```