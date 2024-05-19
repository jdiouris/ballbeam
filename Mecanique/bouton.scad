D=23;
Da=6+0.5;
H=8;
$fn=100;

difference()
{
    cylinder(d=D,h=H,$fn=10);
    cylinder(d=Da,h=H-2);
    translate([0,0,(H-2)/2]) rotate([0,90,0]) cylinder(d=2.1,h=D/2);
    translate([D/2-2,0,(H-2)/2]) rotate([0,90,0]) cylinder(d=5,h=D/2);
}