module main;
integer status, x, y;
initial
begin
    status = $pyeval("from math import sin, radians");
    x = 30;
    y = $pyeval("1000*sin(radians(", x, "))");
    $display(status, x, y);
end
endmodule
