module main;
integer x, y;
initial
begin
    x = $pyeval("from math import sin");
    y = $pyeval("500*sin(.5)");
    $display(x, y);
end
endmodule
