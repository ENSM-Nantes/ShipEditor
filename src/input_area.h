#ifndef AREA_H
#define AREA_H

#include <string>
#include <gtkmm.h>

using namespace Gtk;

#define MAX_ENTRY_VECTOR 10

class InputArea {
public:
  enum variable_type {
    TYPE_NULL = 0,
    TYPE_STRING,
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_VECTOR,
    TYPE_BOOL
  };

  InputArea();
  ~InputArea();

  void initLayout(void) ;
  
  void init(std::string str, std::string *ref_var);
  void init(std::string str, int *ref_var);
  void init(std::string str, float *ref_var);
  void init(std::string str, double *ref_var);
  void init(std::string str, float *ref_var, int size);
  void init(std::string str, bool *ref_var);

  void set(std::string *ref_var);
  void set(int *ref_var);
  void set(double *ref_var);
  void set(float *ref_var, bool aIsVector=false);
  void set(bool *ref_var);

  Box& getBox(void); 
  void update();
  void refresh();

protected:

  Box mBox;
  int mSizeVector;
  int mType;
  std::string *var_str;
  int *var_int;
  float *var_float;
  double *var_double;
  float *var_vector;
  bool *var_bool;

  Label mLabel;
  Entry mOneEntry;
  Entry mVectorEntry[MAX_ENTRY_VECTOR];

  CheckButton  m_checkbutton;
}; 




#endif
