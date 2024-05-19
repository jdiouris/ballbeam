$fn=100;
Lm=101.6;
Wm=53.34;
el=15;
L=Lm+2*el;
e=2;
xv1=13.97;
yv1=2.54;
xv2=15.24;
yv2=50.8;
xv3=90.17;
yv3=50.8;
xv4=96.52;
yv4=2.54;
hplot=4;
dv=3;
dec=5;

Lp=L-20;
Wp=Wm-20;


difference()
{
    union()
    {
        cube([L,Wm,e]);
        translate([el+xv1+dec,yv1,0]) cylinder(d=6,h=hplot+e);
        translate([el+xv2+dec,yv2,0]) cylinder(d=6,h=hplot+e);
        translate([el+xv3+dec,yv3,0]) cylinder(d=6,h=hplot+e);
        translate([el+xv4+dec,yv4,0]) cylinder(d=6,h=hplot+e);
    }
        translate([el+xv1+dec,yv1,-1]) cylinder(d=2.4,h=hplot+e+5);
        translate([el+xv2+dec,yv2,-1]) cylinder(d=2.4,h=hplot+e+5);
        translate([el+xv3+dec,yv3,-1]) cylinder(d=2.4,h=hplot+e+5);
        translate([el+xv4+dec,yv4,-1]) cylinder(d=2.4,h=hplot+e+5);
    
        translate([dv,dv,-1]) cylinder(d=3.6,h=e+2);
       translate([L-dv,dv,-1]) cylinder(d=3.6,h=e+2);
    translate([L-dv,Wm-dv,-1]) cylinder(d=3.6,h=e+2);
    translate([dv,Wm-dv,-1]) cylinder(d=3.6,h=e+2);
    
    translate([(L-Lp)/2,(Wm-Wp)/2,-1]) cube([Lp,Wp,10]);
    
}
