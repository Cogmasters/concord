all:
	$(CC) -static bot-echo.cpp -o bot-echo.exe -lcurl -lbearssl -ldiscord
