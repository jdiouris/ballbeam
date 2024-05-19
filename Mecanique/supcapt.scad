L=25;
eb=5;
W=20;
ea=5;
La=(L-15.21)/2;
lvis=19;
$fn=100;
Lbarre=50;
difference()
{
    union()
    {
    cube([L,W,eb]);
    translate([0,W-2,0])cube([La,2+ea,15]);
    translate([L-La,W-2,0]) cube([La,2+ea,15]);
    translate([-(Lbarre-L)/2,W,0]) 
        {
            cube([Lbarre,5,eb]);
            cube([5,20,eb]);
            translate([Lbarre-5,0,0]) cube([5,20,eb]);
            translate([0,20,0]) cube([5,5,20]);
            translate([Lbarre-5,20,0]) cube([5,5,20]);
        }
        
    }
     translate([L/2-5,W/2,-1])  cylinder(d=3.7,h=eb+10);
    translate([L/2+5,W/2,-1])  cylinder(d=3.7,h=eb+10);
    
    // vis capteur
    translate([(L-lvis)/2,-1,15-3.5]) rotate([-90,0,0]) cylinder(d=2,h=50);
    translate([L-(L-lvis)/2,-1,15-3.5]) rotate([-90,0,0]) cylinder(d=2,h=50);
//   translate([La/2,-1,15-3.5]) rotate([-90,0,0]) cylinder(d=7,h=4,$fn=6);
//    translate([L-La/2,-1,15-3.5]) rotate([-90,0,0]) cylinder(d=7,h=4,$fn=6);
}