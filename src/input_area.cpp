#include "input_area.h"
#include <iostream>

/**
 * Constructor for the input of a string
 * 
 */
InputArea::InputArea(): mBox(Orientation::HORIZONTAL)
{
  mType = TYPE_NULL;
}

InputArea::~InputArea()
{
  
}

void InputArea::initLayout(void) 
{
  // Layout
  mBox.set_margin_top(2);
  mBox.set_margin_bottom(2);
  mBox.set_margin_start(2);
  mBox.set_margin_end(2);

  mOneEntry.set_margin_start(5);
  mOneEntry.add_css_class("gray-entry");
  
  // Display the content
  mLabel.show();
  mOneEntry.show();

  // Create the box
  mBox.append(mLabel);
  mBox.append(mOneEntry);
}

void InputArea::set(std::string *ref_var) 
{  
  // Save the pointer to the target variable
  mType = TYPE_STRING;
  var_str = ref_var;
  if (ref_var == nullptr) mType = TYPE_NULL;
}

void InputArea::init(std::string str, std::string *ref_var) 
{  
  set(ref_var);
  
  // Set the label name
  mLabel.set_text(str);

  // Show the variable mType in the placeholder (when it's empty)
  mOneEntry.set_placeholder_text("string");

  initLayout();
}

void InputArea::set(int *ref_var) 
{   
  // Save the pointer to the target variable
  mType = TYPE_INTEGER;
  var_int = ref_var;
  if (ref_var == nullptr) mType = TYPE_NULL;
}

void InputArea::init(std::string str, int *ref_var) 
{
  set(ref_var);
  
  // Set the label name
  mLabel.set_text(str);

  // Show the variable mType in the placeholder (when it's empty)
  mOneEntry.set_placeholder_text("integer");

  initLayout();
}

void InputArea::set(float *ref_var, bool aIsVector)
{
  // Save the pointer to the target variable

  if(!aIsVector)
    {
      mType = TYPE_FLOAT;
      var_float = ref_var;
    }
  else
    {
      mType = TYPE_VECTOR;
      var_vector = ref_var;
    }
  
  if (ref_var == nullptr) mType = TYPE_NULL;
}

void InputArea::init(std::string str, float *ref_var)
{
  set(ref_var);
  
  // Set the label name
  mLabel.set_text(str);

  // Show the variable mType in the placeholder (when it's empty)
  mOneEntry.set_placeholder_text("float");

  initLayout();
}

void InputArea::set(double *ref_var)
{   
  // Save the pointer to the target variable
  mType = TYPE_DOUBLE;
  var_double = ref_var;
  if (ref_var == nullptr) mType = TYPE_NULL;
}

void InputArea::init(std::string str, double *ref_var)
{
  set(ref_var);
    
  // Set the label name
  mLabel.set_text(str);

  // Show the variable mType in the placeholder (when it's empty)
  mOneEntry.set_placeholder_text("float");

  initLayout();
}


void InputArea::init(std::string str, float *ref_var, int aSize) 
{
  set(ref_var, true);

  mSizeVector = aSize;
    
  // Set the label name
  mLabel.set_text(str);

  mVectorEntry[0].set_margin_start(5);
  
  for(int i=0; i<mSizeVector;i++)
    {
      mVectorEntry[i].set_placeholder_text("Entry n° " + std::to_string(i));
      mVectorEntry[i].show();
      mVectorEntry[i].add_css_class("gray-entry");
    }
   // Layout
  mBox.set_margin_top(2);
  mBox.set_margin_bottom(2);
  mBox.set_margin_start(2);
  mBox.set_margin_end(2);

  // Display the content
  mLabel.show();

  // Create the box
  mBox.append(mLabel);
  for(int i=0; i<mSizeVector;i++)
    {
      mBox.append(mVectorEntry[i]);
    }
}

void InputArea::set(bool *ref_var)
{
  // Save the pointer to the target variable
  mType = TYPE_BOOL;
  var_bool = ref_var;
  if (ref_var == nullptr) mType = TYPE_NULL;
}

void InputArea::init(std::string str, bool *ref_var)
{
  set(ref_var);
  
  // Set the label name
  mLabel.set_text(str);

  // Layout
  mBox.set_margin_top(2);
  mBox.set_margin_bottom(2);
  mBox.set_margin_start(2);
  mBox.set_margin_end(2);
  m_checkbutton.set_margin_start(5);
	
  // Display the content
  mLabel.show();
  m_checkbutton.show();

  // Create the box
  mBox.append(mLabel);
  mBox.append(m_checkbutton);
}


/**
 * Copy the value in the entry into the corresponding pointer
 */
void InputArea::update()
{
  if (mType == TYPE_BOOL) {
    // Copy the value
    *var_bool = m_checkbutton.get_active();
  } else if (mType == TYPE_VECTOR) {
    std::string raw_text;
    for (int i = 0; i < mSizeVector; i++) {
      raw_text = mVectorEntry[i].get_buffer()->get_text();
      var_vector[i] = std::stof(raw_text);
    }
  } else if (mType != TYPE_NULL) {
    // Convert the EntryBuffer into a string
    std::string raw_text = mOneEntry.get_buffer()->get_text();
    if(!raw_text.empty())
      {
	switch(mType) {
	case TYPE_STRING:
	  // Copy the value
	  *var_str = raw_text;
	  break;
	case TYPE_INTEGER:
	  // Convert then copy the value
	  *var_int = std::stoi(raw_text);
	  break;
	case TYPE_FLOAT:
	  // Convert then copy the value
	  *var_float = std::stof(raw_text);
	  break;
	case TYPE_DOUBLE:
	  // Convert then copy the value
	  *var_double = std::stod(raw_text);
	default:
	  // TODO: create an error
	  break;
	}
		  
      }
  }
}

/**
 * Refresh the value from the right pointer into the entry
 */
void InputArea::refresh()
{
  std::string raw_text;
  if (mType == TYPE_BOOL) {
    m_checkbutton.set_active(*var_bool);
  } else if (mType == TYPE_VECTOR) {  
    for (int i = 0; i < mSizeVector; i++) {
      raw_text = std::to_string(var_vector[i]);
      mVectorEntry[i].get_buffer()->set_text(raw_text);
    }
  } else if (mType != TYPE_NULL) {
    std::string raw_text;
    switch(mType) {
    case TYPE_STRING:
      raw_text = *var_str;
      break;
    case TYPE_INTEGER:
      raw_text = std::to_string(*var_int);
      break;
    case TYPE_FLOAT:
      raw_text = std::to_string(*var_float);
      break;
    case TYPE_DOUBLE:
      raw_text = std::to_string(*var_double);
    default:
      // TODO: create an error
      break;
    }

    if (raw_text.length()) {
      mOneEntry.get_buffer()->set_text(raw_text);
    }
  }
}

Box& InputArea::getBox(void)
{
  return mBox;
}
