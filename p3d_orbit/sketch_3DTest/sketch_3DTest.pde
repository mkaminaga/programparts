/*
 2018/03/09
 3D orbital simulator
 Copyright 2018 Mamoru Kaminaga
 Released under the MIT License (https://opensource.org/licenses/mit-license.php)
 
 Units
 Internal calculation
 length : m
 angle : rad or rev
 time : day
 
 Debug output
 length : km
 angle : degree
 time : day
 */

/* Orbital elements
 See also http://jr1huo.my.coocan.jp/jr1huo_calsat32/Calsat32Sample.htm
 */
final float t0=52871.95303700;  /* epoch (MJD) */
final float w0=101.33480072*(PI/180);  /* Argument of perigee (rad) */
final float incl=98.5660*(PI/180);  /* Inclination angle (rad) */
final float omega0=359.5477*(PI/180);  /* Right ascension of ascending node (rad) */
final float e=0.0351513;  /* Eccentricity */
final float n0=13.52885;  /* Mean motion (rev/day) */
final float dndt=-0.00000056;  /* Change rate of Mean motion (rev/day^2) */
final float l0=262.7487/360.0;  /* Mean anomaly (rev) */

/* Other variables */
final int step_max=5000;  /* Time step_max number */
final float tmax=3.0;  /* The calculation time span */

/* Earth related constants */
final float mu=2.97553634804736E+24;  /* Gravitational constant (m^3/day^2) */
final float j2=0.00108262998905;  /* The zonal harmonic value */
final float ae=6378137.0;  /* The radiout of the earth (m) */
final float t_sun= 57832.0;/* MJD of vernal equinox, 2017/03/20 0:0:0 */

/* Set camera position */
final float[] e1={0, 0, 1};
final float[] e2={1, 0, 0};
final float[] e3={0, -1, 0};
final float[] cam={1.5, 1.5, 1.5};

/* Scaling bariables */
final float s1=100.0;  /* ScaleV factor for geometric measures */
final float s2=0.01;  /* ScaleV factor for orbit */

void CopyV(float[] source, float[] target) {
  target[0]=source[0];
  target[1]=source[1];
  target[2]=source[2];
}

void RotX_R(float theta, float[] v) {
  float c=cos(theta);
  float s=sin(theta);
  float[] u={0.0, 0.0, 0.0};
  u[0]=v[0];
  u[1]=v[1]*c+v[2]*s;
  u[2]=-v[1]*s+v[2]*c;
  CopyV(u, v);
}

void RotY_R(float theta, float[] v) {
  float c=cos(theta);
  float s=sin(theta);
  float[] u={0.0, 0.0, 0.0};
  u[0]=v[0]*c+v[2]*s;
  u[1]=v[1];
  u[2]=-v[0]*s+v[2]*c;
  CopyV(u, v);
}

void RotZ_R(float theta, float[] v) {
  float c=cos(theta);
  float s=sin(theta);
  float[] u={0.0, 0.0, 0.0};
  u[0]=v[0]*c+v[1]*s;
  u[1]=-v[0]*s+v[1]*c;
  u[2]=v[2];
  CopyV(u, v);
}

void Debug(String str, int x, int y) {
  pushMatrix();
  camera();
  hint(DISABLE_DEPTH_TEST);
  noLights();
  textMode(MODEL);
  fill(255, 255, 255);
  text(str, x, y);
  hint(ENABLE_DEPTH_TEST);
  popMatrix();
}

float WrapAngle(float theta) {
  float val=0.0;
  if (theta > 0.0) {
    float n=floor(theta/(2.0*PI));
    val=theta-2.0*PI*n;
  } else {
    float n=floor(-theta/(2.0*PI));
    val=2.0*PI*(n+1.0)+theta;
  }
  return val;
}

void setup() {
  size(960, 720, P3D);
  frameRate(30);
  smooth();
  background(0);
  colorMode(RGB, 255);
  textSize(16);
  hint(ENABLE_DEPTH_SORT);

  /* PSurface srf=this.getSurface(); */
  /* srf.setLocation(800,100); */
  float[] v1={
    e1[0]*cam[0]+e2[0]*cam[1]+e3[0]*cam[2], 
    e1[1]*cam[0]+e2[1]*cam[1]+e3[1]*cam[2], 
    e1[2]*cam[0]+e2[2]*cam[1]+e3[2]*cam[2], 
  };
  camera(v1[0]*s1, v1[1]*s1, v1[2]*s1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/* Satellite trace buffer */
float[] phi_buffer=new float[step_max+1];
float[] lambda_buffer=new float[step_max+1];

/* draw() function call counter */
int step=0;

void draw() {
  background(0);
  if (step>step_max) {
    Debug("Finish", 300, 30);
    exit();
    return;
  }
  float dt=step/((float)step_max)*tmax;

  /********************
   Orbital calculation
   ********************/
  Debug("dt="+dt+"(days)", 10, 30);

  /* Mean motion and axis */
  float n=n0+dndt*dt;  /* Mean anomaly (rev/day) */
  float a=pow(mu/(4.0*PI*PI*n*n), 1.0/3.0);  /* Semi-Major axis (m) */
  float b=sqrt(1-e*e)*a;  /* Semi-minor axis (m) */

  Debug("n="+n*180.0/PI+"(degree/day)", 10, 50);
  Debug("a="+a*0.001+"(km)", 10, 70);
  Debug("b="+b*0.001+"(km)", 10, 90);

  /* Mean anomaly and true anomaly */
  float l=WrapAngle((l0+n*dt)*2.0*PI);  /* Mean anomaly (rad) */
  Debug("l="+l*180.0/PI+"(degree)", 10, 110);

  float u=l;  /* Initial guess for true anomaly (rad) */
  float uo=0;  /* Tempolary variable for true anomaly (rad) */
  for (int i=0; abs(u-uo)>1.0E-6; ++i) {
    if (i>100) {
      Debug("Newton method failure", 300, 30);
      exit();
    }
    uo=u;
    u=uo-(uo-e*sin(uo)-l)/(1.0-e*cos(uo));
  }
  u=WrapAngle(u);
  Debug("u="+u*180.0/PI+"(degree)", 10, 130);

  /* Satellite position on the orbital plane */
  float[] x1={a*(cos(u)-e), b*sin(u), 0.0};
  Debug("x="+x1[0]*0.001+"(km)", 10, 150);
  Debug("y="+x1[1]*0.001+"(km)", 10, 170);

  /* Collection on argument og perigee and 
   righy accension of ascending node */
  Debug("i="+incl*180.0/PI+"(degree)", 10, 190);
  float cosi=cos(incl);
  float tmp=ae/(a*(1.0-e*e));
  float n2=(3.0/4.0)*j2*tmp*tmp*(n*2.0*PI)*(5.0*cosi*cosi-1.0);  /* (rad/day) */
  float n3=-1.5*j2*tmp*tmp*(n*2.0*PI)*cosi;  /* (rad/day) */
  Debug("n2="+n2*180.0/PI+"(degree/day)", 10, 210);
  Debug("n3="+n3*180.0/PI+"(degree/day)", 10, 230);

  float w=WrapAngle(w0+n2*dt);
  float omega=WrapAngle(omega0+n3*dt);
  Debug("w="+w*180.0/PI+"(degree)", 10, 250);
  Debug("omega="+omega*180.0/PI+"(degree)", 10, 270);

  /* Matric to convert satellite position from
   the orbital plane to the ECI system */
  float[] x2={0.0, 0.0, 0.0};
  CopyV(x1, x2);
  RotZ_R(-w, x2);
  RotX_R(-incl, x2);
  RotZ_R(-omega, x2);
  Debug("X="+x2[0]*0.001+"(km)", 10, 290);
  Debug("Y="+x2[1]*0.001+"(km)", 10, 310);
  Debug("Z="+x2[2]*0.001+"(km)", 10, 330);

  /* Longitude,altutude and distance is derived */
  float lambda=atan2(x2[1], x2[0]);  /* Longitude (rad) */
  float r=sqrt(x2[0]*x2[0]+x2[1]*x2[1]+x2[2]*x2[2]);  /* Distance (m) */
  float phi=0.0;
  tmp=0.0;
  tmp=sqrt(x2[0]*x2[0]+x2[1]*x2[1]);
  if (abs(tmp)<1.0E-6) {
    if (x2[2]>0.0) {
      phi=PI/2.0;
    } else {
      phi=-PI/2.0;
    }
  } else {
    phi=atan(x2[2]/tmp);  /* Altitude (rad) */
  }
  Debug("lambda="+lambda*180/PI+"(degree)", 10, 350);
  Debug("phi="+phi*180/PI+"(degree)", 10, 370);
  Debug("r="+r*0.001+"(km)", 10, 390);

  /* Greenwich sidereal */
  /* See also http://star.gs/nyumon/koseiji.htm */
  double tmp2=0.67239+1.00273781*dt+1.00273781*(t0-40000.0);
  tmp2=(float)tmp2-floor((float)tmp2);
  float theta_g=(float)tmp2*2.0*PI;
  Debug("theta_g="+theta_g*180/PI+"(degree)", 10, 410);

  /* Store relative longitude and altitude for plot drawing
   on earth surface */
  lambda_buffer[step]=WrapAngle(lambda-theta_g);
  phi_buffer[step]=phi;

  /* vernal equinox */
  float sun=WrapAngle((t0+dt-t_sun)/365.2422*2.0*PI);
  Debug("sun="+sun*180/PI+"(degree)", 10, 430);

  /********************
   3D rendering
   See also http://d.hatena.ne.jp/kougaku-navi/20160104/p1
   ********************/
  /* Draw axis of ECI system */
  {
    pushMatrix();
    scale(1.0, 1.0, -1.0);
    rotateZ(-PI/2.0);
    rotateY(PI/2.0);
    strokeWeight(3);
    // X axis
    stroke(255, 0, 0);
    fill(100, 0, 0);
    line(s1*1.5, 0.0, 0.0, -s1, 0.0, 0.0);
    // Y axis
    stroke(0, 100, 0);
    fill(0, 100, 0);
    line(0.0, s1, 0.0, 0.0, -s1, 0.0);
    // Z axis
    stroke(0, 0, 100);
    fill(0, 0, 100);
    line(0.0, 0.0, s1, 0.0, 0.0, -s1);
    // End axis setting
    strokeWeight(1);
    popMatrix();

    text("X", e1[0]*s1, e1[1]*s1, e1[2]*s1);  /* x label */
    text("Y", e2[0]*s1, e2[1]*s1, e2[2]*s1);  /* x label */
    text("Z", e3[0]*s1, e3[1]*s1, e3[2]*s1);  /* x label */
  }

  float weight=0.001*s2;  /* km -> m & scale adjustment */
  /* Draw satellite (Orbit calculation is done in the right-hand system,
   but the processing only supports left-hand system. It is necessary
   to transform right-described phisical orbit model into left-hand 
   model) */
  {
    pushMatrix();
    rotateX(PI/2);
    rotateZ(PI/2);
    rotateZ(-omega);
    rotateX(-incl);
    rotateZ(-w);
    translate(x1[0]*weight, -x1[1]*weight, 0.0);

    stroke(255, 255, 0);
    fill(255, 150, 100);
    sphere(4);
    popMatrix();
  }

  /* Draw orbit (Orbit calculation is done in the right-hand system,
   but the processing only supports left-hand system. It is necessary
   to transform right-described phisical orbit model into left-hand 
   model) */
  {
    pushMatrix();
    /* Orbital plane and trace */
    rotateX(PI/2);
    rotateZ(PI/2);
    rotateZ(-omega);
    rotateX(-incl);
    rotateZ(-w);
    /* Orbital plane */
    //hint(DISABLE_DEPTH_TEST);
    //stroke(255,255,255,200);
    //fill(255,255,255,100);
    //hint(ENABLE_DEPTH_TEST);
    //rectMode(CENTER);
    //rect(0.0,0.0,a*weight*2.5,b*weight*2.5);
    /* Draw axis of orbital plane */
    strokeWeight(2);
    // X* axis
    stroke(255, 128, 0);
    fill(255, 128, 0);
    line(s1, 0.0, 0.0, -s1*0.2, 0.0, 0.0);
    // Y* axis
    stroke(255, 0, 255);
    fill(255, 0, 255);
    line(0.0, s1*0.2, 0.0, 0.0, -s1, 0.0);
    // Z* axis
    stroke(0, 128, 255);
    fill(0, 128, 255);
    line(0.0, 0.0, -s1*0.2, 0.0, 0.0, s1);
    strokeWeight(1);

    /* Trace */
    translate(-a*e*weight, 0.0, 0.0);
    stroke(100, 100, 100);
    noFill();
    ellipseMode(RADIUS);
    strokeWeight(2);
    ellipse(0.0, 0.0, a*weight, b*weight);
    strokeWeight(1);
    popMatrix();
  }

  /* Draw the earth */
  {
    /* Body */
    noStroke();
    fill(100, 200, 100, 100);
    sphere(ae*weight);

    /* Line and track */
    {
      pushMatrix();
      /* Line */
      rotateY(theta_g);  /* Greenwich sidereal */
      for (int i=0; i<12; ++i) {
        {
          pushMatrix();
          rotateY(-PI/2.0);  /* Adjustment */
          if (i==0) {
            pushMatrix();
            {
              strokeWeight(2);
              stroke(255, 30, 30);
              noFill();
              rotateZ(-PI/2.0);
              arc(0.0, 0.0, ae*weight, ae*weight, 0.0, PI);
              strokeWeight(1);
            }
            popMatrix();
          } else {
            stroke(0, 50, 0);
            noFill();
            ellipse(0.0, 0.0, ae*weight, ae*weight);
          }
          popMatrix();
        }
        rotateY(2.0*PI/24.0);  /* Time zone */
      }
      /* Track */
      float px=0.0;
      float py=0.0;
      float pz=0.0;
      float p2x=0.0;
      float p2y=0.0;
      float p2z=0.0;
      rotateY(PI);  /* Adjustment */
      strokeWeight(2);
      stroke(255, 255, 0);
      int i0=step-500;
      if (i0<1) i0=1;
      for (int i=i0; i<=step; ++i) {
        px=ae*weight*cos(phi_buffer[i-1])*sin(lambda_buffer[i-1]);
        py=-ae*weight*sin(phi_buffer[i-1]);
        pz=ae*weight*cos(phi_buffer[i-1])*cos(lambda_buffer[i-1]);
        p2x=ae*weight*cos(phi_buffer[i])*sin(lambda_buffer[i]);
        p2y=-ae*weight*sin(phi_buffer[i]);
        p2z=ae*weight*cos(phi_buffer[i])*cos(lambda_buffer[i]);
        line(px, py, pz, p2x, p2y, p2z);
      }
      strokeWeight(1);
      /* Radious */
      stroke(255, 255, 0);
      float dist=sqrt(x2[0]*x2[0]+x2[1]*x2[1]+x2[2]*x2[2]);  /* (m) */
      line(0.0, 0.0, 0.0, p2x*dist/ae, p2y*dist/ae, p2z*dist/ae);
      popMatrix();
    }
  }

  /* Draw X-Y plane (Z=0) */
  {
    pushMatrix();  /* X-Y plane transformation start */
    noStroke();
    fill(100, 100, 255, 100);
    rectMode(CENTER);
    rotateX(-PI/2.0);
    rect(0.0, 0.0, a*weight*2.2, b*weight*2.2);
    /* Intersection of X-Y plane and the earth surface */
    stroke(255, 100, 100);
    noFill();
    ellipseMode(RADIUS);
    ellipse(0.0, 0.0, ae*weight, ae*weight);
    popMatrix();  /* X-Y plane transformation end */
  }

  /* Draw sun */
  {
    pushMatrix();
    float r_sun=s1*1.25;  /* Sun orbit radioud for draw, not an actual value */
    /* Sun orbit */
    strokeWeight(2);
    stroke(100, 30, 30);
    noFill();
    ellipseMode(RADIUS);
    rotateX(PI/2);
    rotateY(-23.4*PI/180.0);
    ellipse(0.0, 0.0, r_sun, r_sun);
    strokeWeight(1);
    /* Dummy sun */
    {
      pushMatrix();
      noStroke();
      translate(r_sun*cos(sun), -r_sun*sin(sun), 0.0);
      fill(255, 0, 0);
      sphere(8);
      popMatrix();
    }
    popMatrix();
  }

  /* Count UP! */
  ++step;

  /* This delay is here to reduce CPU usage, don't delete it */
  delay(10);
}