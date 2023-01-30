#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
    /* Your code here */
    // Set it as undefined
    number_type = IMAGINARY;
    magnitude = 0.0;
    phase = 0.0;
    imaginary_component = 0.0;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    /* Your code here */
	number_type = IMAGINARY;
    imaginary_component = rval;
	// update magnitude and phase
	magnitude = sqrt(pow(imaginary_component, 2));
	phase = calculate_phase(0, imaginary_component);
}

ImaginaryNumber::ImaginaryNumber(const ImaginaryNumber& other)
{
    /* Your code here */
	// assign attributes from other to this one
	number_type = IMAGINARY;
    magnitude = other.magnitude;
    phase = other.phase;
    imaginary_component = other.imaginary_component;
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    /* Your code here */
	imaginary_component = rval;
	// update magnitude and phase
	magnitude = sqrt(pow(imaginary_component, 2));
	phase = calculate_phase(0, imaginary_component);
}

double ImaginaryNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    /* Your code here */
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
	double img = get_imaginary_component() + arg.get_imaginary_component();
    return ImaginaryNumber(img);
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
	double img = get_imaginary_component() - arg.get_imaginary_component();
    return ImaginaryNumber(img);
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
	double real = - (get_imaginary_component() * arg.get_imaginary_component());
    return RealNumber(real);
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)	// I'm not sure about this one
{
    /* Your code here */
	double real = get_imaginary_component() / arg.get_imaginary_component();
    return RealNumber(real);
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a + arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a - arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a * arg;	// perform the calculation
    return ImaginaryNumber(a.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a / arg;	// perform the calculation
    return ImaginaryNumber(a.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a + arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a - arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a * arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
	ComplexNumber a = ComplexNumber(0, get_imaginary_component());	// change the original real number to a complex number
	a = a / arg;	// perform the calculation
	return ComplexNumber(a.get_real_component(), a.get_imaginary_component());
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}
