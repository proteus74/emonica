#pragma once

void Set_Key_Adaptive_Expression_Min()
{
	int seltemp = -1;
	int temp = Presets[CurrentPreset].Key_AdaptiveExpressionMin;
	const int MinVal = 0;
	const int MaxVal = 127;

	display.clearDisplay();
	DisplayPresetNumber();
	display.setFont(NULL);
	printCentered(" Adap. Expr. ", 0);
	printCentered("Min Value", 9);
	display.drawBitmap(0, 0, Harmonic_Icon, 26, 16, 1);
	display.fillRect(0, 18, 127, 38, 0);
	display.setFont(&FreeSansBold18pt7b);
	DrawProgressbar(temp, MinVal, MaxVal);
	printCentered(String(temp), 48);
	display.display();
	delay(PAUSE_BETWEEN_SCREENS);

	AdaptiveButton Next = AdaptiveButton(Pin_NextScreen, &seltemp, 1, 0, 2);
	AdaptiveButton Prev = AdaptiveButton(Pin_PrevScreen, &seltemp, -1, 0, 2);
	AdaptiveButton	ValueUp = AdaptiveButton(Pin_ValueUp, &temp, 1, MinVal, MaxVal);
	AdaptiveButton	ValueDown = AdaptiveButton(Pin_ValueDown, &temp, -1, MinVal, MaxVal);


	boolean exit = false;
	LastTimer = millis();
	while (exit == false)
	{
		if (ValueUp.Update() || ValueDown.Update())
		{
			flagSaveConfig = true;
			LastTimer = millis();
			display.fillRect(0, 20, 127, 38, 0);
			display.setFont(&FreeSansBold18pt7b);
			Presets[CurrentPreset].Key_AdaptiveExpressionMin = temp;
			printCentered(String(temp), 48);
			display.display();
		}

		if (Prev.Update())
		{
			exit = true;
			currentScreen = Page_Set_Key_Adaptive_Expression;
		}
		if (Next.Update())
		{
			exit = true;
			currentScreen = Page_Set_Key_Adaptive_Expression_Max;
		}
		if (abs(millis() - LastTimer) > TIME_TO_RETURN_TO_MAIN_PAGE)
		{
			exit = true;
			currentScreen = Page_Main;
		}
	}
}

