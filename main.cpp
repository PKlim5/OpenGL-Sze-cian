#include <windows.h>
#include <gl\gl.h>	
#include <gl\glu.h>	
#include <gl\glaux.h>

//--------------------------------------------------------------------------------------------------------------------------------------
HDC			hDC = NULL;
HGLRC		hRC = NULL;
HWND		hWnd = NULL;
HINSTANCE	hInstance;

// Zmienne globalne
bool	keys[256];
bool	active = TRUE;

int trybAnimacji = 1;					
GLint iloscSzescianow = 3;				
GLfloat katObrotuCalosci = 0.0f;		
GLfloat katPojednczy = 0.0f;			
GLfloat odleglosc = 1.6f;				
GLfloat odlegloscMin = 1.4f;			
GLfloat odlegloscMax = 2.1f;			
GLfloat rozmiar = 1.0f;					
bool trybPowiekszania = true;				
GLfloat kolory[3] = { 0.0f,1.0f,0.0f };												
bool k1 = true;							
bool k2 = true;
GLfloat odlegloscObserwacji = -12.0f;      
GLfloat predkoscObrotuCalosci = -0.5f;		
GLfloat predkoscObrotuPojedynczego = -1.0f;	
GLfloat predkoscZmianyOdleglosci = 0.04f;		
GLfloat predkoscZmianyKoloru = 0.01f;			

// Parametry oświetlenia
GLfloat LightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { -10.0f, 0.0f, -10.0f, -1.0f };
//----------------------------------------------------------------------------------------------------------------------------------------

void DrawCube(GLfloat rozmiar, GLfloat rotation) { //rysowanie pojedynczego szescianu
	rozmiar = rozmiar / 2;
	glPushMatrix();									//wrzucenie macierzy przeksztalcen na stos
	glRotatef(rotation, 0.0f, 1.0f, 0.0f);			//obrot pojedynczego szescianu
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, -1.0f);					//ustawienie normalniej

	glVertex3f(-rozmiar, rozmiar, -rozmiar);		//rysowanie przedniej sciany
	glVertex3f(rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, -rozmiar, -rozmiar);
	glVertex3f(-rozmiar, -rozmiar, -rozmiar);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-rozmiar, rozmiar, rozmiar);			//rysowanie tylnej sciany
	glVertex3f(-rozmiar, -rozmiar, rozmiar);
	glVertex3f(rozmiar, -rozmiar, rozmiar);
	glVertex3f(rozmiar, rozmiar, rozmiar);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-rozmiar, -rozmiar, rozmiar);		// rysowanie dolnej sciany
	glVertex3f(rozmiar, -rozmiar, rozmiar);
	glVertex3f(rozmiar, -rozmiar, -rozmiar);
	glVertex3f(-rozmiar, -rozmiar, -rozmiar);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-rozmiar, rozmiar, rozmiar);			//rysowanie gornej sciany
	glVertex3f(-rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, rozmiar);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-rozmiar, -rozmiar, rozmiar);	//rysowanie lewej sciany
	glVertex3f(-rozmiar, rozmiar, rozmiar);
	glVertex3f(-rozmiar, rozmiar, -rozmiar);
	glVertex3f(-rozmiar, -rozmiar, -rozmiar);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(rozmiar, -rozmiar, rozmiar);		//rysowanie prawej sciany
	glVertex3f(rozmiar, -rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, -rozmiar);
	glVertex3f(rozmiar, rozmiar, rozmiar);

	glEnd();
	glPopMatrix();
	return;
}

int DrawGLScene(GLvoid)								
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();									

	glTranslatef(0.0f, 0.0f, odlegloscObserwacji);		
	glRotatef(25, 1.0f, 0.0f, 0.0f);					


	glRotatef(katObrotuCalosci, 0.0f, 1.0f, 0.0f);				//obroc caly szyk o katObrotuCalosci

	glTranslatef(-(iloscSzescianow - 1) * odleglosc / 2, -(iloscSzescianow - 1) * odleglosc / 2, -(iloscSzescianow - 1) * odleglosc / 2);  //przesun calosc tak, zeby srodek szyku byl w srodku obrotu

	for (int x = 0; x < iloscSzescianow; x++)
	{
		glPushMatrix();									
		glTranslatef(x * odleglosc, 0.0f, 0.0f);		
		for (int y = 0; y < iloscSzescianow; y++)
		{
			glPushMatrix();								
			glTranslatef(0.0f, y * odleglosc, 0.0f);		
			for (int z = 0; z < iloscSzescianow; z++)
			{	
				glPushMatrix();							
				glTranslatef(0.0f, 0.0f, z * odleglosc);	

				if (x == 0 && z == 0 && y == iloscSzescianow-1)						
					glColor3f(kolory[1], kolory[1], kolory[2]);
				else if (x == 1 && z == 1 && y == iloscSzescianow - 1)
					glColor3f(kolory[1], kolory[0], kolory[2]);
				else if (x == 2 && z == 2 && y == iloscSzescianow - 1)
					glColor3f(kolory[0], kolory[1], kolory[2]);
				else
					glColor3f(0.0f, 0.0f, 1.0f);					
				DrawCube(rozmiar, katPojednczy);					//rysuj szescian
				glPopMatrix();						//sciagnij polozenie ze stosu
			}
			glPopMatrix();							//sciagnij polozenie ze stosu
		}
		glPopMatrix();								//sciagnij polozenie ze stosu
	}

	if (trybAnimacji == 1)													
	{
		katObrotuCalosci = katObrotuCalosci + predkoscObrotuCalosci;					
		if (katObrotuCalosci > 360)										
			katObrotuCalosci = katObrotuCalosci - 360;
		if (katObrotuCalosci < 0)										    
			katObrotuCalosci = katObrotuCalosci + 360;
	}
	else if (trybAnimacji == 2)												
	{
		katPojednczy = katPojednczy + predkoscObrotuPojedynczego;		
		if (katPojednczy > 360)										
			katPojednczy = katPojednczy - 360;
		if (katPojednczy < 0)										
			katPojednczy = katPojednczy + 360;
	}
	else if (trybAnimacji == 3)												
	{
		if (trybPowiekszania)											
			odleglosc = odleglosc + predkoscZmianyOdleglosci;
		else														
			odleglosc = odleglosc - predkoscZmianyOdleglosci;

		if (odleglosc >= odlegloscMax || odleglosc <= odlegloscMin)  
			trybPowiekszania = !trybPowiekszania;
	}
	else if (trybAnimacji == 4)	
	{

		if (k1)
		{
			kolory[1] = kolory[1] + predkoscZmianyKoloru;
			if (kolory[1] > 1.0f)
			{
				kolory[1] = 1.0f;
				k1 = !k1;
			}
		}
		else
		{
			kolory[1] = kolory[1] - predkoscZmianyKoloru;
			if (kolory[1] < 0.0f)
			{
				kolory[1] = 0.0f;
				k1 = !k1;
			}
		}

		if (k2)
		{
			kolory[2] = kolory[2] + predkoscZmianyKoloru;
			if (kolory[2] > 1.0f)
			{
				kolory[2] = 1.0f;
				k2 = !k2;
			}
		}
		else
		{
			kolory[2] = kolory[2] - predkoscZmianyKoloru;
			if (kolory[2] < 0.0f)
			{
				kolory[2] = 0.0f;
				k2 = !k2;
			}
		}
	}
	return TRUE;
}

int InitGL(GLvoid)										// Inicjacja OpenGL
{
	glShadeModel(GL_SMOOTH);							// cieniowanie gladkie
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// czarny kolor tla
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);							// wylaczenie bufora glebi
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// skladowa otoczenia
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// skladowa rozproszona
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// polozenie zrodla swiatla

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	return TRUE;
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);					

	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();									

	// wyznaczenie proporcji obrazu i ustawienie rzutowania perspektywicznego
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							
	glLoadIdentity();									
}

LRESULT CALLBACK WndProc(HWND	hWnd, UINT	uMsg, WPARAM	wParam, LPARAM	lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:								// Zamkniecie okna
	{
		PostQuitMessage(0);						
		return 0;
	}

	case WM_KEYDOWN:							
	{
		keys[wParam] = TRUE;
		return 0;
	}

	case WM_KEYUP:								
	{
		keys[wParam] = FALSE;
		return 0;
	}

	case WM_SIZE:								
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  
		return 0;
	}
	}


	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GLvoid KillGLWindow(GLvoid)	
{

}

BOOL CreateGLWindow(char* title, int width, int height, int bits)
{
	GLuint		PixelFormat;
	WNDCLASS	wc;						// klasa okna
	DWORD		dwExStyle;				// rozszerzony styl okna
	DWORD		dwStyle;				// styl okna
	RECT		WindowRect;				// rozmiar okna


	// struktura okreslajaca rozmiary okna
	WindowRect.left = (long)0;
	WindowRect.right = (long)width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)height;

	hInstance = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);				// domyslna ikona
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// domyslny kursor
	wc.hbrBackground = NULL;							// bez tla
	wc.lpszMenuName = NULL;								// bez menu
	wc.lpszClassName = "OpenGL";

	if (!RegisterClass(&wc))	// zarejestrowanie klasy okna
	{
		return 0;
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// definicja klasy okna
	dwStyle = WS_OVERLAPPEDWINDOW;							// styl okna
	

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// skorygowanie rozmiaru okna

	// Utworzenie okna
	if (!(hWnd = CreateWindowEx(dwExStyle,							// styl rozszerzony
		"OpenGL",							// nazwa klasy
		title,								// nazwa aplikacji
		dwStyle | WS_CLIPSIBLINGS |
		WS_CLIPCHILDREN,
		0, 0,								// wsporzedne x,y
		WindowRect.right - WindowRect.left,
		WindowRect.bottom - WindowRect.top,	// szerokosc, wysokosx
		NULL,								// uchwyt okna nadrzednego
		NULL,								// uchwyt menu
		hInstance,							// instancja aplikacji
		NULL)))
	{
		KillGLWindow();
		MessageBox(NULL, "Nie udało się otwrzyć okna!", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),			// rozmiar struktury
		1,										// domyslna wersja
		PFD_DRAW_TO_WINDOW |					// grafika w oknie
		PFD_SUPPORT_OPENGL |					// grafika OpenGL 
		PFD_DOUBLEBUFFER,						// podwojne buforowanie
		PFD_TYPE_RGBA,							// tryb kolorow RGBA 
		bits,									// Glebia kolorow
		0, 0, 0, 0, 0, 0,						// nie specyfikuje bitow kolorow
		0,										// bez bufora alfa
		0,										// nie specyfikuje bitu przesuniecia
		0,										// bez bufora akumulacji
		0, 0, 0, 0,								// ignoruje bity akumulacji
		16,										// 16-bitowy bufor Z
		0,										// bez bufora powielania
		0,										// bez buforow pomocniczych
		PFD_MAIN_PLANE,							// glowna plaszczyzna rysowania
		0,										// zarezerwowane
		0, 0, 0									// ignoruje maski warstw
	};

	if (!(hDC = GetDC(hWnd)))						// pobiera kontekst urzadzenia dla okna
	{
		KillGLWindow();								// zresetuj wyswietlanie
		return FALSE;
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Czy system Windows znalazl pasujacy format pikseli?
	{
		KillGLWindow();
		return FALSE;
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// okresla format pikseli dla danego kontekstu urzadzenia
	{
		KillGLWindow();
		return FALSE;
	}

	if (!(hRC = wglCreateContext(hDC)))				// tworzy kontekst grafiki i czyni go biezacym
	{
		KillGLWindow();
		return FALSE;
	}

	if (!wglMakeCurrent(hDC, hRC))					// usuwa kontekst renderowania okna
	{
		KillGLWindow();
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOW);						// wyswietlenie okna
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);

	if (!InitGL())									// Zainicjuj nasze nowo utworzone okno GL
	{
		KillGLWindow();
		MessageBox(NULL, "Inicjalizacja nieudana", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;									// komunikat
	BOOL	done = FALSE;							// znacznik zakonczenia aplikacji

	// Informacja przed programem
	MessageBox(NULL, "Sterowanie klawiszami: 1,2,3,4", "Sterowanie", MB_OK | MB_ICONINFORMATION);


	// Create Our OpenGL Window
	if (!CreateGLWindow("Animacja sześcianów", 600, 600, 32))
	{
		return 0;									// Zakoncz, jesli okno nie zostalo utworzone
	}
	int lastTick = 0;
	while (!done)	// petla przetwarzania komunikatow
	{

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)				// aplikacja otrzymala komunikat WM_QUIT?
			{
				done = TRUE;						// jezli tak, to konczy dzialanie
			}
			else
			{										// jezeli nie to renderuje scene,
				TranslateMessage(&msg);				// tlumaczy komunikat i wysyla do systemu
				DispatchMessage(&msg);
			}
		}

		else
		{

			if (active)	// Czy program jest aktywny?
			{

				int tick = GetTickCount64();
				if (tick - lastTick >= 20)
				{
					DrawGLScene();					// Narysuj scene
					SwapBuffers(hDC);				// Przelaczenie buforow
					lastTick = tick;
				}
			}

			if (keys['1'])
			{
				keys['1'] = false;
				trybAnimacji = 1;
			}
			if (keys['2'])
			{
				keys['2'] = false;
				trybAnimacji = 2;
			}
			if (keys['3'])
			{
				keys['3'] = false;
				trybAnimacji = 3;
			}
			if (keys['4'])
			{
				keys['4'] = false;
				trybAnimacji = 4;
			}
		}
	}


	KillGLWindow();
	return (msg.wParam);
}
