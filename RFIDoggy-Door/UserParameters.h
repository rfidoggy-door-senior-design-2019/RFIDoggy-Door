/*  
    UserParameters.h

    object to store user parameters read from mobile app
*/


class UserParameters
{
private:
  float lowTemp;
  float highTemp;
  bool moistEnable;

public:

  UserParameters()
  {
    lowTemp     = 32;
    highTemp    = 99;    
    moistEnable = false;
  }

  void setLowTemp(const float val)    { lowTemp     = val; }
  void setHighTemp(const float val)   { highTemp    = val; }
  void setMoistEnable(const bool val) { moistEnable = val; }

  float getLowTemp()    { return lowTemp;     }
  float getHighTemp()   { return highTemp;    }
  bool getMoistEnable() { return moistEnable; }

};
