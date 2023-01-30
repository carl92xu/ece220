#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    /* Your code here */
    // initialize it
    number_type = REAL;
    magnitude = 0.0;
    phase = 0.0;
    real_component = 0.0;
}

RealNumber::RealNumber(double rval)
{
    /* Your code here */
	number_type = REAL;
    real_component = rval;
	// update magnitude and phase
	//magnitude = sqrt(pow(real_component, 2));
	magnitude = abs(real_component);
	phase = calculate_phase(real_component, 0);
}

RealNumber::RealNumber(const RealNumber& other)
{
    /* Your code here */
	number_type = COMPLEX;
    magnitude = other.magnitude;
    phase = other.phase;
    real_component = other.real_component;
}

void RealNumber::set_real_component (double rval)
{
    /* Your code here */
	real_component = rval;
	// update magnitude and phase
	magnitude = abs(real_component);
	phase = calculate_phase(real_component, 0);
}

double RealNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	double real = get_real_component() + arg.get_real_component();
    return RealNumber(real);
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	double real = get_real_component() - arg.get_real_component();
    return RealNumber(real);
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	double real = get_real_component() * arg.get_real_component();
    return RealNumber(real);
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	double real = get_real_component() / arg.get_real_component();
    return RealNumber(real);
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	double real = get_real_component();
	double img = arg.get_imaginary_component();
    return ComplexNumber(real, img);
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
	double real = get_real_component();
	double img = - (arg.get_imaginary_component());
    return ComplexNumber(real, img);
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	ComplexNumber a = ComplexNumber(get_real_component(), 0);	// change the original real number to a complex number
	a = a * arg;	// perform the calculation
	return ImaginaryNumber(a.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
	ComplexNumber a = ComplexNumber(get_real_component(), 0);	// change the original real number to a complex number
	a = a / arg;	// perform the calculation
	return ImaginaryNumber(a.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
	ComplexNumber a = ComplexNumber(get_real_component(), 0);	// change the original real number to a complex number
	a = a + arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
	ComplexNumber a = ComplexNumber(get_real_component(), 0);	// change the original real number to a complex number
	a = a - arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	ComplexNumber a = ComplexNumber(get_real_component(), 0);	// change the original real number to a complex number
	a = a * arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
	ComplexNumber a = ComplexNumber(get_real_component(), 0);	// change the original real number to a complex number
	a = a / arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}
