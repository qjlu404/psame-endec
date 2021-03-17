#pragma once

#ifdef ENCODER_EXPORTS
#define ENCODER __declspec(dllexport)
#else
#define ENCODER __declspec(dllimport)
#endif

/// <summary>
/// Changes the console foreground color to an RGB value
/// </summary>
/// <param name="R"> Red (0-255) </param>
/// <param name="G"> Green (0-255) </param>
/// <param name="B"> Blue (0-255) </param>
extern "C" ENCODER void SetForegroundColorRGB(int r, int g, int b);
/// <summary>
/// Changes the console background color to an RGB value
/// </summary>
/// <param name="R"> Red (0-255) </param>
/// <param name="G"> Green (0-255) </param>
/// <param name="B"> Blue (0-255) </param>
extern "C" ENCODER void SetBackgroundColorRGB(int r, int g, int b);
/// <summary>
/// Resets the console colors to default
/// </summary>
extern "C" ENCODER void ResetColors();
/// <summary>
/// Clears the console
/// </summary>
extern "C" ENCODER void ClearConsole();

