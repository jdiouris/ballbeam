W=5;
L=67;
$fn=100;

difference()
{   cube([L,W,W]);
    translate([L/2,-1,W/2]) rotate([-90,0,0]) cylinder(d=3.6,h=10);
    translate([(L-50)/2+50,-1,W/2]) rotate([-90,0,0]) cylinder(d=3.6,h=10);
}
translate([W*sin(60),W/2,0])  
rotate([0,0,60]) 
difference()
{   cube([L,W,W]);
    translate([(L-50)/2,-1,W/2]) rotate([-90,0,0]) cylinder(d=2.7,h=10);
    translate([(L-50)/2+50,-1,W/2]) rotate([-90,0,0]) cylinder(d=2.7,h=10);
}