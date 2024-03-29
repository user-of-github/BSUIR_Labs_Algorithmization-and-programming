// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cmath>
#include "Unit1.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {
}

// ---------------------------------------------------------------------------
class Numbers {
public:
	double a;
	double b;

	Numbers(const double &aa, const double &bb) : a(aa), b(bb) {
	}

	void Sqr() {
		long double tmp = (a * a) - (b * b);
		this->b = 2.0 * a * b;
		this->a = tmp;
	}

	double Magn() {
		return sqrt((a * a) + (b * b));
	}

	void Add(const Numbers &c) {
		this->a += c.a;
		this->b += c.b;
	}

};

double kWX = 0;
double kWY = 0;

double kSpeed = 5;
double kZoom = 2;
double kZoomSpeed = 0.3;
double kResolution = 2;

int kMouseX = 0, kMouseY = 0;

void DrawIt() {
	int width = Form1->Image1->Width;
	int height = Form1->Image1->Height;

	if (kResolution <= 0)
		kResolution = 2;

	Graphics::TBitmap *frame = new TBitmap();

	frame->SetSize(width / kResolution, height / kResolution);

	for (int x = 0; x < width / kResolution; ++x) {
		for (int y = 0; y < height / kResolution; ++y) {
			double a =
				(double)((x + (kWX / kResolution / kZoom)) -
				((width / 2) / kResolution)) / (double)
				(width / kZoom / kResolution);
			double b =
				(double)((y + (kWY / kResolution / kZoom)) -
				((height / 2) / kResolution)) / (double)
				(height / kZoom / kResolution);

			auto c = Numbers(a, b);
			auto z = Numbers(0, 0);

			int it = 0;

			do {
				++it;
				z.Sqr();
				z.Add(c);
				if (z.Magn() > 2.0)
					break;
			}
			while (it < 100);

			auto col = (unsigned char)(it * 2.55f);
			frame->Canvas->Pixels[x][y] = TColor(RGB(col, col, col));
		}
	}

	Form1->Image1->Canvas->StretchDraw(Rect(0, 0, width, height), frame);
}

void __fastcall TForm1::FormCreate(TObject * Sender) {
	Image1->Width = this->Width;
	Image1->Height = this->Height;

	DrawIt();
}
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
	TShiftState Shift)

{

	switch (Key) {
	case 37: {
			kWX -= kSpeed * (5 - abs(kZoom));
			DrawIt();
			break;
		}
	case 38: {
			kWY -= kSpeed * (5 - abs(kZoom));
			DrawIt();
			break;
		}
	case 39: {
			kWX += kSpeed * (5 - abs(kZoom));
			DrawIt();
			break;
		}
	case 40: {
			kWY += kSpeed * (5 - abs(kZoom));
			DrawIt();
			break;
		}
	case 109: {
			kZoom += kZoomSpeed / kZoom;
			DrawIt();
			break;
		}
	case 107: {
			kZoom -= kZoomSpeed / kZoom;
			kWX += (kMouseX - Form1->Image1->Width / 2);
			kWY += (kMouseY - Form1->Image1->Height / 2);
			DrawIt();
			break;
		}

	}
}
// ---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y) {
	kMouseX = X;
	kMouseY = Y;
}
// ---------------------------------------------------------------------------
