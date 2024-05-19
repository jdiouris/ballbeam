//W=62.3;
W=40;
H=10;
$fn=100;

difference()
{
    cube([W,H,H]);
    translate([-1,5,5]) rotate([0,90,0]) cylinder(h=13,d=2.8);
    translate([W-12,5,5]) rotate([0,90,0]) cylinder(h=13,d=2.8);
    translate([15,5,-1]) cylinder(h=15,d=4.5);
    translate([W-15,5,-1]) cylinder(h=15,d=4.5);
}