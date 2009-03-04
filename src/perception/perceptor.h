
#ifndef _PERCEPTOR_H_
#define _PERCEPTOR_H_

class Perceptor {

 public:
  Perceptor(){
    /*
      ExampleLocator * loc = new ExampleLocator();
      locators[loc] = 0.2;

      ExampleOrientator * or = new ExampleOrientator();
      orientators[or] = 0.2;
    */
  }

  float getOrientation() {
    float orientation = 0.0f;
    for(std::map<ILocator *, float>::iterator iter = orientators.begin(); 
	iter != orientators.end(); iter++) {
      location += (*iter).first()->getOrientation() * (*iter).second();
    }
    return location;
  }

  Vector2df getLocation() {
    Vector2df location = new Vector2df();
    for(std::map<ILocator *, float>::iterator iter = locators.begin();
	iter != locators.end(); iter++) {
      orientators += (*iter).first()->getOrientation() * (*iter).second();
    }
    return location;
  }
  
 private:
  std::map<ILocator *, float> locators;
  std::map<IOrientator *, float> orientators;

}

#endif //_PERCEPTOR_H
