

W=15;
W2=10;
D=14;
E=4;
L2=90+D+4;
L1=110+D+4;
$fn=100;

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

module petitLevier()
{
    difference()
    {
        union()
        {
        rcube(L2,W,E,10);
            translate([D/2+2+90,W/2,E]) cylinder(h=E+0.5, d=7);
        }
        translate([D/2+2,W/2,E-1]) cylinder(h=2, d=D);
        translate([D/2+2,W/2,-1]) cylinder(h=20, d=3.8);
        translate([D/2+2+18,W/2,-1]) cylinder(h=20, d=3.4);
        translate([D/2+2+24,W/2,-1]) cylinder(h=20, d=3.4);
        translate([D/2+2+30,W/2,-1]) cylinder(h=20, d=3.4);
        
        translate([D/2+2+90,W/2,-1]) cylinder(h=20, d=3.8);
        
    } 
}

module grandLevier()
{
    difference()
    {
        union()
        {
        rcube(L1,W2,E,10);
            //translate([D/2+2+110,W/2,E]) cylinder(h=E+0.5, d=12);
            rcube(10,2*W2,E,10);
        }
        //translate([D/2+2,W/2+W,E-1]) cylinder(h=2, d=D);
        translate([5,W2/2+W2,-1]) cylinder(h=20, d=3.8);
        
        
        translate([D/2+2+110,W2/2,2]) cylinder(h=20, d=8.2);
        translate([D/2+2+110,W2/2,-1]) cylinder(h=20, d=3.8);
        
    } 
}
    
//petitLevier();
mirror([0,1,0]) grandLevier();