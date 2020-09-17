
void cartesianToPolar(double x, double y, double a1, double a2){
  //Finding Distance from Point
  double hyp = sqrt(pow(x, 2) + pow(y, 2));
  Serial.println("Hypothenus");
  Serial.println(hyp);

  //Alpha
  double alpha = pow(a1, 2) + pow(a2, 2) - pow(x, 2) - pow(y, 2);
  alpha = alpha / (2 * a1 * a2);
  alpha = acos(alpha);
  alpha = (alpha / PI) * 180;
  Serial.println("Alpha");
  Serial.println(alpha);

  //Q2
  double q2 = 180 - alpha;
  Serial.println("Q2");
  Serial.println(q2);

  //Beta
  q2 = q2 * PI/180;
  double beta = a2 * sin(q2);
  beta = beta / (a1 + a2 * cos(q2));
  beta = atan(beta);
  beta = (beta / PI) * 180;
  Serial.println("Beta");
  Serial.println(beta);

  //Gamma
  double gamma = atan(y/x);
  gamma = (gamma / PI) * 180;
  Serial.println("Gamma");
  Serial.println(gamma);

  //Q1
  double q1 = gamma + beta;
  Serial.println("Q1");
  Serial.println(q1);
  
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  cartesianToPolar(5, -5, 5, 5);
  delay(30000);
}
