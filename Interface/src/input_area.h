#ifndef AREA_H
#define AREA_H

#include <string>
#include <gtkmm.h>

using namespace Gtk;

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
  
  void init(const Glib::ustring &str, std::string *ref_var);
  void init(const Glib::ustring &str, int *ref_var);
  void init(const Glib::ustring &str, float *ref_var);
  void init(const Glib::ustring &str, double *ref_var);
  void init(const Glib::ustring &str, float *ref_var, bool vector);
  void init(const Glib::ustring &str, bool *ref_var);

  void set(std::string *ref_var);
  void set(int *ref_var);
  void set(float *ref_var);
  void set(double *ref_var);
  void set(float *ref_var, bool vector);
  void set(bool *ref_var);

  Box& getBox(void); 
  void update();
  void refresh();

protected:

  Box mBox;
  int type;
  std::string *var_str;
  int *var_int;
  float *var_float;
  double *var_double;
  float *var_vector;
  bool *var_bool;

  Label m_label;
  Entry m_entry;
  Entry m_entry_x;
  Entry m_entry_y;
  Entry m_entry_z;
  Entry *vector_entry[3];
  CheckButton  m_checkbutton;
}; 




#endif
