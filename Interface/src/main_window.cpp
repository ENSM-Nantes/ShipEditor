#include <iostream>
#include "main_window.h"




MainWindow::MainWindow():
m_button("Hello World"),
m_button_update("Update"),
m_button_reset("Reset"),
m_box(Gtk::Orientation::VERTICAL),
m_area0("String", &test_var_string),
m_area1("Integer", &test_var_int),
m_area2("Float", &test_var_float),
m_area3("Bool", &test_var_bool)
{
	// Configure this window:
	this->set_default_size(600, 400);

	// Connect the 'click' signal and make the button visible:
	m_button.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::buttonClick));
	m_button.show();

	m_button_update.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::buttonClickUpdate));
	m_button_update.show();

	m_button_reset.signal_clicked().connect(
		sigc::mem_fun(*this, &MainWindow::buttonClickReset));
	m_button_reset.show();
	
	m_area0.show();
	m_area1.show();
	m_area2.show();
	m_area3.show();
	


	//Box b(Gtk::ORIENTATION_HORIZONTAL);
	//area = new EditArea(&b);
	
	// Pack all elements in the box:
	m_box.append(m_button);
	m_box.append(m_button_update);
	m_box.append(m_button_reset);
	

	m_box.append(m_area0);
	m_box.append(m_area1);
	m_box.append(m_area2);
	m_box.append(m_area3);

	// Add the box in this window:
	set_child(m_box);
	
	// Make the box visible:
	m_box.show();
}

void MainWindow::buttonClick() {
	std::cout << "Hello World" << std::endl;
	std::cout << "Variable string: " << test_var_string << std::endl;
	std::cout << "Variable int   : " << test_var_int << std::endl;
	std::cout << "Variable float : " << test_var_float << std::endl;
	std::cout << "Variable bool  : " << test_var_bool << std::endl;
}

void MainWindow::buttonClickUpdate() {
	std::cout << "Updating entries" << std::endl;
	m_area0.update();
	m_area1.update();
	m_area2.update();
	m_area3.update();
}

void MainWindow::buttonClickReset() {
	std::cout << "Updating entries" << std::endl;
	m_area0.reset();
	m_area1.reset();
	m_area2.reset();
	m_area3.reset();
}