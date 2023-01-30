#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    /* Your code here */
    // initialize it
    number_type = COMPLEX;
    magnitude = 0.0;
    phase = 0.0;
    real_component = 0.0;
    imaginary_component = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    /* Your code here */
    number_type = COMPLEX;
	real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
	// update magnitude and phase
	magnitude = sqrt(pow(real_component, 2)+pow(imaginary_component, 2));
	phase = calculate_phase(real_component, imaginary_component);
}

ComplexNumber::ComplexNumber(const ComplexNumber& other)
{
    /* Your code here */
	// assign attributes from other to this one
	number_type = COMPLEX;
    magnitude = other.magnitude;
    phase = other.phase;
    real_component = other.real_component;
    imaginary_component = other.imaginary_component;
}

void ComplexNumber::set_real_component (double rval)
{
    /* Your code here */
	real_component = rval;
	// update magnitude and phase
	magnitude = sqrt(pow(real_component, 2)+pow(imaginary_component, 2));
	phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
	imaginary_component = rval;
	// update magnitude and phase
	magnitude = sqrt(pow(real_component, 2)+pow(imaginary_component, 2));
	phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
	double real = get_real_component() + arg.get_real_component();
	double img = get_imaginary_component() + arg.get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    double real = get_real_component() - arg.get_real_component();
	double img = get_imaginary_component() - arg.get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
	double real = get_real_component() * arg.get_real_component() - get_imaginary_component() * arg.get_imaginary_component();
	double img = get_real_component() * arg.get_imaginary_component() + get_imaginary_component() * arg.get_real_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
	double denominator = pow(arg.get_real_component(), 2) + pow(arg.get_imaginary_component(), 2);
	double real = (get_real_component() * arg.get_real_component() + get_imaginary_component() * arg.get_imaginary_component()) / denominator;
	double img = (get_imaginary_component() * arg.get_real_component() - get_real_component() * arg.get_imaginary_component()) / denominator;
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	double real = get_real_component() + arg.get_real_component();
	double img = get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    double real = get_real_component() - arg.get_real_component();
	double img = get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	double real = get_real_component() * arg.get_real_component();
	double img = get_imaginary_component() * arg.get_real_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	double denominator = pow(arg.get_real_component(), 2);
	double real = (get_real_component() * arg.get_real_component()) / denominator;
	double img = (get_imaginary_component() * arg.get_real_component()) / denominator;
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
	double real = get_real_component();
	double img = get_imaginary_component() + arg.get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    double real = get_real_component();
	double img = get_imaginary_component() - arg.get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
	double real = - (get_imaginary_component() * arg.get_imaginary_component());
	double img = get_real_component() * arg.get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
	double denominator = pow(arg.get_imaginary_component(), 2);
	double real = (get_imaginary_component() * arg.get_imaginary_component()) / denominator;
	double img = - (get_real_component() * arg.get_imaginary_component()) / denominator;
    return ComplexNumber(real, img);
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}
