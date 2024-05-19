Waxe=50;
Daxe=8.3;
E=2;
L=30;
W=(Waxe+Daxe+2*E);
H=Daxe+2*E;
$fn=100;
echo("W=",W);
module rcube(x,y,z,d)
{
    union()
    {
        translate([d/2,d/2,0]) cube([x-d,y-d,z]);
        translate([d/2,0,0]) cube([x-d,d,z]);
        translate([d/2,y-d,0]) cube([x-d,d,z]);
        translate([0,d/2,0]) cube([d,y-d,z]);
         translate([x-d,d/2,0]) cube([d,y-d,z]);
        translate([d/2,d/2,0]) cylinder(h=z,d=d);
        translate([x-d/2,d/2,0]) cylinder(h=z,d=d);
         translate([d/2,y-d/2,0]) cylinder(h=z,d=d);
        translate([x-d/2,y-d/2,0]) cylinder(h=z,d=d);
    }
    
}

difference()
{
    
    rcube(L,W,H,5);
    // sup axe
    translate([L-15,(W-Waxe)/2,H/2]) rotate([0,90,0]) cylinder(d=Daxe,h=40);
    translate([L-15,(W-Waxe)/2+Waxe,H/2]) rotate([0,90,0]) cylinder(d=Daxe,h=40);
    // sup axe de rotation
    translate([5,-1,H/2]) rotate([-90,0,0]) cylinder(d=5.3,h=W+10);
    // Vis capteur
    translate([L-5,W/2-5,-1])  cylinder(d=3.6,h=H+10);
    translate([L-5,W/2+5,-1])  cylinder(d=3.6,h=H+10);
    translate([L-5,W/2-5,-1])  cylinder(d=7,h=4,$fn=6);
    translate([L-5,W/2+5,-1])  cylinder(d=7,h=4,$fn=6);
    
    
}