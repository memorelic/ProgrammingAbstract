#define MinArea 0.5
#define MinEdge 0.15

void SubdivideCanvas(double x, double y, double width, double height)
{
	double divider;

	if (width * height >= MinArea)
	{
		if (width > height)
		{
			divider = width * RandomReal(MinEdge, 1 - MinEdge);
			MovePen(x + divider, y);
			DrawLine(0, height);
			SubdivideCanvas(x, y, divider, height);
			SubdivideCanvas(x + divider, y, width - divider, height);
		}
		else
		{
			divider = height * RandomReal(MinEdge, 1 - MinEdge);
			MovePen(x, y + divider);
			DrawLine(width, 0);
			SubdivideCanvas(x, y, width, divider);
			SubdivideCanvas(x, y + divider, width, height - divider);
		}
	}
}

#define pi 3.1415926535

void DrawPolarLine(double r, double theta)
{
	double radians = theta / 180 * pi;
	DrawLine(r * cos(radians), r * sin(radians));
}

void DrawFractalLine(double len, double theta, int order)
{
	if (order == 0)
	{
		DrawPolarLine(len, theta);
	}
	else
	{
		DrawFractalLine(len / 3, theta, order - 1);
		DrawFractalLine(len / 3, theta - 60, order - 1);
		DrawFractalLine(len / 3, theta + 60, order - 1);
		DrawFractalLine(len / 3, theta, order - 1);
	}
}

void KochFractal(double size, int order)
{
	double x0, y0;

	x0 = GetWindowWidth() / 2 - size / 2;
	y0 = GetWindowHeight() / 2 - sqrt(3) * size / 6;

	MovePen(x0, y0);

	DrawFractalLine(size, 0, order);
	DrawFractalLine(size, 120, order);
	DrawFractalLine(size, 240, order);
}

int main(void)
{
	/*
	InitGraphics();
	Randomize();
	SubdivideCanvas(0, 0, GetWindowWidth(), GetWindowHeight());
	*/

	InitGraphics();
	double size = 8;
	int order = 4;

	KochFractal(size, order);

	return 0;
}