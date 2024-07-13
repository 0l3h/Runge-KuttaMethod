#include <iostream>
#include <cmath>
using namespace std;

class AbstractOdeSolver {
protected:
	double stepSize;
	double initialTime;
	double finalTime;
	double initialValue;
public:
	void SetStepSize(double h);
	void SetTimeInterval(double t0, double t1);
	void SetInitialValue(double y0);
	virtual double RightHandSide(double y, double t) = 0;
	virtual double SolveEquation() = 0;
};

double f(double t, double y)
{
	return 1 + t;
}

void AbstractOdeSolver::SetStepSize(double h)
{
	stepSize = h;
}

void AbstractOdeSolver::SetTimeInterval(double t0, double t1)
{
	initialTime = t0;
	finalTime = t1;
}

void AbstractOdeSolver::SetInitialValue(double y0)
{
	initialValue = y0;
}

class RKMethod : public AbstractOdeSolver
{
public:
	double RightHandSide(double t, double y);
	double SolveEquation();
};

double RKMethod::RightHandSide(double t, double y)
{
	double (*p_function)(double t, double y);
	p_function = &f;
	return p_function(t, y);
}

double RKMethod::SolveEquation()
{
	double y = initialValue, t = initialTime;

	for (int i = 0; t < finalTime; i++)
	{
		t = initialTime + i * stepSize;
		double k1 = stepSize * RightHandSide(t, y);
		double k2 = stepSize * RightHandSide(t + stepSize / 2, y + k1 / 2);
		double k3 = stepSize * RightHandSide(t + stepSize / 2, y + k2 / 2);
		double k4 = stepSize * RightHandSide(t + stepSize, y + k3);
		y = y + (k1 + (2 * k2) + (2 * k3) + k4) / 6;
		cout << y << " " << t << "\n";
	}

	return y;
}

int main()
{
	AbstractOdeSolver* solver = new RKMethod;
	solver->SetTimeInterval(0, 1);
	solver->SetStepSize(0.001);
	solver->SetInitialValue(2);
	solver->SolveEquation();
}